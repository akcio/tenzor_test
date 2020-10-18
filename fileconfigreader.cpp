#include "fileconfigreader.h"

#include <QFile>
#include <QTextStream>

ConfigFromFile::ConfigFromFile(const QString &configFile) : IConfig()
{
    if ( not QFile::exists(configFile) )
    {
        m_hasError = true;
        m_errorString = QString{"File %1 not found"}.arg(configFile);
        return;
    }
    QFile file(configFile);
    if ( not file.open(QIODevice::ReadOnly) )
    {
        m_hasError = true;
        m_errorString = file.errorString();
        return;
    }
    QTextStream stream(&file);
    stream >> m_filePath >> m_nodePath >> m_attrPath;
}

QString ConfigFromFile::getFilePath() const
{
    return m_filePath;
}

QString ConfigFromFile::getNodePath() const
{
    return m_nodePath;
}

QString ConfigFromFile::getAttributePath() const
{
    return m_attrPath;
}

bool ConfigFromFile::hasError() const
{
    return m_hasError;
}

QString ConfigFromFile::errorString() const
{
    return m_errorString;
}
