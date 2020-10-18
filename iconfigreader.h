#ifndef ICONFIGREADER_H
#define ICONFIGREADER_H

#include <QString>

class IConfig
{
public:
    IConfig() = default;
    virtual ~IConfig() = default;

    virtual QString getFilePath() const = 0;
    virtual QString getNodePath() const = 0;
    virtual QString getAttributePath() const = 0;
    virtual bool hasError() const { return false; }
    virtual QString errorString() const { return QString{"No error"}; }
};

#endif // ICONFIGREADER_H
