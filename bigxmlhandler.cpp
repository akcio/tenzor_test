#include "bigxmlhandler.h"
#include <QFile>
#include <QFileInfo>
#include <QXmlStreamReader>
#include "handlers/linearhandler.h"
#include "handlers/threadhandler.h"

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

    if (xmlFile.size() > 1024*1024 ) {
        m_handler = std::make_shared<ThreadHandler>(m_config->getAttributePath());
    } else {
        m_handler = std::make_shared<LinearHandler>(m_config->getAttributePath());
    }
    QString currentPath {""};


    QXmlStreamReader xml(&xmlFile);
    while (not xml.atEnd()) {
        auto token = xml.readNext();
        switch (token) {
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
            break;
        }
        default:
            break;
        }
        m_handler->handleXMLItem(token, currentPath, &xml);
    }
    if (xml.hasError()) {
        return;
    }
}

bool BigXMLHandler::validateFilePath(const QString &path)
{
    return QFile::exists( path );
}

long double BigXMLHandler::getResult() const
{
    if (m_handler != nullptr) {
        return m_handler->getResult();
    }
    return 0;
}
