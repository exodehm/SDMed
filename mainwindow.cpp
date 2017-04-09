#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupActions();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ActionNuevo()
{
    InterfazObra* w = new InterfazObra("/home/david/programacion/cmasmas/PruebasObra/bin/Debug/CENZANO.bc3");
    ui->tabPrincipal->addTab(w,"kk");
    //InterfazObra w("/home/david/programacion/cmasmas/PruebasObra/bin/Debug/CENZANO.bc3");
}

void MainWindow::ActionAbrir()
{

}

bool MainWindow::ActionGuardar()
{

}

bool MainWindow::ActionGuardarComo()
{

}

void MainWindow::ActionCerrar()
{

}

void MainWindow::ActionSalir()
{

}

void MainWindow::ActionImportarBC3()
{

}

void MainWindow::ActionExportarBC3()
{

}

void MainWindow::ActionAdelante()
{

}

void MainWindow::ActionAtras()
{

}

bool MainWindow::ConfirmarContinuar()
{
    //esta funcion cuando se implemente retornara true si ha habido cambios y false si no los ha habido
    //por ahora retorna siempre false
    return false;
}

void MainWindow::setupActions()
{
    QObject::connect(ui->actionNuevo,SIGNAL(triggered(bool)),this,SLOT(ActionNuevo()));
    QObject::connect(ui->action_Salir, SIGNAL(triggered(bool)),qApp, SLOT(quit()));
}
