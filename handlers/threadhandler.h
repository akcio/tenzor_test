#ifndef THREADHANDLER_H
#define THREADHANDLER_H

#include "ihandler.h"
#include <QtConcurrent/QtConcurrent>
#include <QVector>

class ThreadHandler : public IXMLHandler
{
public:
    ThreadHandler(const QString &attributePath);

    // IXMLHandler interface
public:
    void handleXMLItem(const QXmlStreamReader::TokenType &type, const QString &currentPath, QXmlStreamReader *reader);
    long double getResult();
    static long double calcSum(const std::vector<long double> &vector);
protected:
    size_t maxBufferSize() const;
    std::vector<long double> m_tmpBuffer {};
    QThreadPool m_pool;
    QVector<QFuture<long double>> m_futureContainer {};

};

#endif // THREADHANDLER_H
