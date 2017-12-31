#include "mainwindow.h"
#include <QApplication>

#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug() << QApplication::style()->metaObject()->className();
    qDebug() << QStyleFactory::keys();
    a.setWindowIcon(QIcon("../SDMed/Iconos/gobernante.png"));
    qDebug()<<QDir::currentPath();
    qDebug()<<argv[0];
    MainWindow m;
    m.show();
    return a.exec();
}
