#include "mainwindow.h"
#include <QApplication>
//#include <QtPlugin>

#include <QStyleFactory>

/*Q_IMPORT_PLUGIN(QXcbIntegrationPlugin)
Q_IMPORT_PLUGIN(QXcbGlxIntegrationPlugin)
Q_IMPORT_PLUGIN(QXcbEglIntegrationPlugin)*/


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug() << QApplication::style()->metaObject()->className();
    qDebug() << QStyleFactory::keys();
    a.setWindowIcon(QIcon("../SDMed/Iconos/gobernante.png"));
    MainWindow m;
    m.show();
    return a.exec();
}
