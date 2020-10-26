#include "threadhandler.h"
#include <QtConcurrent/QtConcurrent>
#include <QThread>

ThreadHandler::ThreadHandler(const QString &attributePath) : IXMLHandler(attributePath)
{
    m_pool.setMaxThreadCount(QThread::idealThreadCount());
}

void ThreadHandler::handleXMLItem(const QXmlStreamReader::TokenType &type, const QString &currentPath, QXmlStreamReader *reader)
{
    if (m_tmpBuffer.size() >= maxBufferSize()) {
        m_futureContainer.append(QtConcurrent::run(&m_pool, &ThreadHandler::calcSum, m_tmpBuffer));
        m_tmpBuffer.clear();
    }
    switch (type) {
    case QXmlStreamReader::StartElement: {
        break;
    }
    case QXmlStreamReader::EndElement: {
        return;
    }
    case QXmlStreamReader::Characters: {
        if (currentPath == attributePath) {
            bool ok {true};
            auto value = reader->text().toDouble(&ok);
            if (ok) {
                m_tmpBuffer.push_back(value);
            }

        }
        return;
        break;
    }
    default:
        return;
    }
    if (currentPath == attributePrefix) {
        auto valueString = reader->attributes().value(lastParamName);
        if (not valueString.isEmpty()) {
            bool isOk {false};
            auto value = valueString.toDouble(&isOk);
            if (isOk) {
                m_tmpBuffer.push_back(value);
            }
        }
    }
}

long double ThreadHandler::getResult()
{
    for (auto &item : m_futureContainer) {
        item.waitForFinished();
        result += item.result();
    }
    return std::accumulate(m_tmpBuffer.begin(), m_tmpBuffer.end(), result);
}

long double ThreadHandler::calcSum(const std::vector<long double> &vector)
{
    return std::accumulate(vector.begin(), vector.end(), 0);
}

size_t ThreadHandler::maxBufferSize() const
{
    //TO 256 kB
    return 8 * IXMLHandler::maxBufferSize();
}
