#include "bigxmlhandler.h"
#include <QFile>
#include <QXmlStreamReader>

BigXMLHandler::BigXMLHandler(std::shared_ptr<IConfig> config, QObject *parent) :
    QObject(parent),
    m_config(config)
{

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
    QString paramName {""};
    for (auto &item : m_config->getAttributePath().split(".").mid(m_config->getNodePath().split(".").size())) {
        if (not paramName.isEmpty()) {
            paramName += ".";
        }
        paramName += item;
    }
    QXmlStreamReader xml(&xmlFile);
    while (not xml.atEnd()) {
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
        default:
            continue;
        }
//        if (not xml.readNextStartElement()) {
//            break;
//        }
        if (currentPath == m_config->getNodePath()) {
            auto name = xml.name();
            auto test = xml.namespaceUri();
            auto attributes = xml.attributes();
            auto val = attributes.value(paramName);
            auto b = 100;
        }

    }
    if (xml.hasError()) {

    }
}

bool BigXMLHandler::validateFilePath(const QString &path)
{
    return QFile::exists( path );
}
