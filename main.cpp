#include "Address.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Address w;
    w.show();
    return a.exec();
}
