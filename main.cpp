#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon("../PruebasInterfazObra/Iconos/gobernante.png"));
    MainWindow m;
    m.show();
    return a.exec();
}
