#include "linearhandler.h"

LinearHandler::LinearHandler(const QString &attributePath) : IXMLHandler(attributePath)
{
    m_tmpBuffer.reserve(maxBufferSize());
}

void LinearHandler::handleXMLItem(const QXmlStreamReader::TokenType &type, const QString &currentPath, QXmlStreamReader *reader)
{
    if (m_tmpBuffer.size() >= maxBufferSize()) {
        result = std::accumulate(m_tmpBuffer.begin(), m_tmpBuffer.end(), result);
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

long double LinearHandler::getResult()
{
    if (not m_tmpBuffer.empty()) {
        result = std::accumulate(m_tmpBuffer.begin(), m_tmpBuffer.end(), result);
        m_tmpBuffer.clear();
    }
    return result;
}
