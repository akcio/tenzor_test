#ifndef BIGXMLHANDLER_H
#define BIGXMLHANDLER_H

#include <QObject>
#include <memory>
#include <vector>
#include "iconfigreader.h"
#include "handlers/ihandler.h"

class BigXMLHandler : public QObject
{
    Q_OBJECT
public:
    BigXMLHandler(std::shared_ptr<IConfig> config, QObject *parent = nullptr);
    void start();
    long double getResult() const;

signals:

protected:
    std::shared_ptr<IConfig> m_config;
    bool validateFilePath(const QString &path);
    constexpr size_t maxBufferSize() const;
    std::shared_ptr<IXMLHandler> m_handler {};
};

#endif // BIGXMLHANDLER_H
