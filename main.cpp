#include <QCoreApplication>
#include <memory>
#include "fileconfigreader.h"
#include "bigxmlhandler.h"
#include <iostream>
#include <QDateTime>

ConfigFromFile* getConfigFromFile(const QString &pathToConfig) {
    return new ConfigFromFile(qMove(pathToConfig));
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::shared_ptr<IConfig> config(getConfigFromFile("input.txt"));
    BigXMLHandler handler(config);
    auto start = QDateTime::currentDateTime();
    handler.start();
    printf("%.2Lf\n", handler.getResult());
    if (argc > 1) {
        printf("Total time: %lld\n", start.msecsTo(QDateTime::currentDateTime()));
    }
    exit(0);
    return a.exec();
}
