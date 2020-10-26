#ifndef IHANDLER_H
#define IHANDLER_H

#include <QXmlStreamReader>

class IXMLHandler {

public:
    IXMLHandler(const QString &attributePath) : attributePath(attributePath) {
        auto splitted = attributePath.split(".");
        for (auto &item : splitted.mid(0, splitted.size() - 1)) {
            if (not attributePrefix.isEmpty()) {
                attributePrefix += ".";
            }
            attributePrefix += item;
        }
        lastParamName = splitted.last();
    }
    virtual ~IXMLHandler() = default;
    virtual void handleXMLItem(const QXmlStreamReader::TokenType &type, const QString &currentPath, QXmlStreamReader *reader) {}
    virtual long double getResult() { return result; }
protected:
    long double result {0};
    QString attributePath {""};
    QString attributePrefix {""};
    QString lastParamName  {""};
    virtual size_t maxBufferSize() const
    {
        // 32kB is L1 cache size
        return 32 * 1024 / sizeof(result);
    }

};

#endif // IHANDLER_H
