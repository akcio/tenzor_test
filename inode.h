#ifndef INODE_H
#define INODE_H

#include "iattr.h"
#include <memory>
#include <QString>
#include <QMap>
#include <QXmlStreamReader>

class INode {

public:
    INode(const QString &nodePath) : m_nodePath(nodePath) { }
    virtual ~INode() = default;
    virtual void processNodeElem(const QString &currentPath, QXmlStreamReader *reader) = 0;

protected:
    QString m_nodePath {""};
    QMap<QString, std::shared_ptr<IAttribute>> m_attributes;
};

#endif // INODE_H
