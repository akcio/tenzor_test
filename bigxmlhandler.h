#ifndef BIGXMLHANDLER_H
#define BIGXMLHANDLER_H

#include <QObject>
#include <memory>
#include "iconfigreader.h"

class BigXMLHandler : public QObject
{
    Q_OBJECT
public:
    BigXMLHandler(std::shared_ptr<IConfig> config, QObject *parent = nullptr);
    void start();
signals:

protected:
    std::shared_ptr<IConfig> m_config;
    bool validateFilePath(const QString &path);
};

#endif // BIGXMLHANDLER_H
