#ifndef FILECONFIGREADER_H
#define FILECONFIGREADER_H

#include "iconfigreader.h"

class ConfigFromFile : public IConfig
{
public:
    explicit ConfigFromFile(const QString &configFile);

    // IConfigReader interface
public:
    QString getFilePath() const override;
    QString getNodePath() const override;
    QString getAttributePath() const override;
    bool hasError() const override;
    QString errorString() const override;
protected:
    QString m_filePath {""};
    QString m_nodePath {""};
    QString m_attrPath {""};
    bool m_hasError {false};
    QString m_errorString {""};
};

#endif // FILECONFIGREADER_H
