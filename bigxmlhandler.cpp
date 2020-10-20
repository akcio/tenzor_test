#include "bigxmlhandler.h"
#include <QFile>
#include <QXmlStreamReader>

BigXMLHandler::BigXMLHandler(std::shared_ptr<IConfig> config, QObject *parent) :
    QObject(parent),
    m_config(config)
{
    m_tmpBuffer.reserve(maxBufferSize());
}

void BigXMLHandler::start()
{
    if ( m_config->hasError() ) {
        return;
    }
    if (not validateFilePath(m_config->getFilePath())) {
        return;
    }
    QFile xmlFile(m_config->getFilePath());
    if (not xmlFile.open(QIODevice::ReadOnly)) {
        return;
    }
    QString currentPath {""};
    QString attributePath = m_config->getAttributePath();
    auto splitted = attributePath.split(".");
    QString attributePrefix {""};
    for (auto &item : splitted.mid(0, splitted.size() - 1)) {
        if (not attributePrefix.isEmpty()) {
            attributePrefix += ".";
        }
        attributePrefix += item;
    }
    QString lastParamName = splitted.last();
//    QString paramName {""};
//    for (auto &item : m_config->getAttributePath().split(".").mid(m_config->getNodePath().split(".").size())) {
//        if (not paramName.isEmpty()) {
//            paramName += ".";
//        }
//        paramName += item;
//    }
    QXmlStreamReader xml(&xmlFile);
    while (not xml.atEnd()) {
        if (m_tmpBuffer.size() >= maxBufferSize()) {
            result = std::accumulate(m_tmpBuffer.begin(), m_tmpBuffer.end(), result);
            m_tmpBuffer.clear();
            if (m_tmpBuffer.capacity() != maxBufferSize()) {
                m_tmpBuffer.reserve(maxBufferSize());
            }
        }
        switch (xml.readNext()) {
        case QXmlStreamReader::StartElement: {
            if ( not currentPath.isEmpty() ) {
                currentPath += ".";
            }
            currentPath += xml.name();
            break;
        }
        case QXmlStreamReader::EndElement: {
            auto tmp = currentPath.split(".");
            tmp.removeLast();
            currentPath.clear();
            for (auto &item : tmp) {
                if (not currentPath.isEmpty()) {
                    currentPath += ".";
                }
                currentPath += item;
            }
            continue;
            break;
        }
        case QXmlStreamReader::Characters: {
            if (currentPath == attributePath) {
                bool ok {true};
                auto value = xml.text().toDouble(&ok);
                if (ok) {
                    m_tmpBuffer.push_back(value);
                }

            }
            continue;
            break;
        }
        default:
            continue;
        }
        if (currentPath == attributePrefix) {
            auto valueString = xml.attributes().value(lastParamName);
            if (not valueString.isEmpty()) {
                bool isOk {false};
                auto value = valueString.toDouble(&isOk);
                if (isOk) {
                    m_tmpBuffer.push_back(value);
                }
            }
        }
    }
    if (xml.hasError()) {
        return;
    }
    result = std::accumulate(m_tmpBuffer.begin(), m_tmpBuffer.begin()+m_tmpBuffer.size(), result);
    m_tmpBuffer.clear();
}

bool BigXMLHandler::validateFilePath(const QString &path)
{
    return QFile::exists( path );
}

constexpr size_t BigXMLHandler::maxBufferSize() const
{
    // 32kB is L1 cache size
    return 32 * 1024 / sizeof(result);
}

long double BigXMLHandler::getResult() const
{
    return result;
}
