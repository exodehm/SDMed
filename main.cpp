#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    //QApplication::setDesktopSettingsAware(false);
    //QApplication::setStyle("motif");
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon("../PruebasInterfazObra/Iconos/gobernante.png"));    
    MainWindow m;
    m.show();
    return a.exec();
}
