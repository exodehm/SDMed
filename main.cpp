#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //InterfazObra w("/home/david/programacion/cmasmas/PruebasObra/bin/Debug/CENZANO.bc3");
    MainWindow m;
    m.show();

    return a.exec();
}
