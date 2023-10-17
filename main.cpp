#include <QCoreApplication>

#include "Prototype.h"
#include "PrototypeFactory.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Prototype::runPrototype();
    PrototypeFactory::runPrototypeFactory();

    return a.exec();
}
