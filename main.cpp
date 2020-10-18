#include <QCoreApplication>
#include <memory>
#include "fileconfigreader.h"
#include "bigxmlhandler.h"

ConfigFromFile* getConfigFromFile(const QString &pathToConfig) {
    return new ConfigFromFile(qMove(pathToConfig));
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::shared_ptr<IConfig> config(getConfigFromFile("input.txt"));
    BigXMLHandler handler(config);
    handler.start();
    return a.exec();
}
