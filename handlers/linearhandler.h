#ifndef LINEARHANDLER_H
#define LINEARHANDLER_H

#include "ihandler.h"

class LinearHandler : public IXMLHandler
{
public:
    LinearHandler(const QString &attributePath);
    ~LinearHandler() = default;

    // IXMLHandler interface
public:
    void handleXMLItem(const QXmlStreamReader::TokenType &type, const QString &currentPath, QXmlStreamReader *reader);
    long double getResult();
protected:
    std::vector<long double> m_tmpBuffer {};
};

#endif // LINEARHANDLER_H
