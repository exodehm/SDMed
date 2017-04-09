#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QList>

#include "interfazobra.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void ActionNuevo();
    void ActionAbrir();
    bool ActionGuardar();
    bool ActionGuardarComo();
    void ActionCerrar();
    void ActionSalir();
    void ActionImportarBC3();
    void ActionExportarBC3();
    void ActionAdelante();
    void ActionAtras();

private:

    struct MetaObra
    {
        InterfazObra* miobra;
        QString nombrefichero;
        MetaObra():miobra(nullptr){}
    };
    std::list<MetaObra>ListaObras;
    std::list<MetaObra>::iterator obraActual;

    Ui::MainWindow *ui;

    bool ConfirmarContinuar();
    void setupActions();
};

#endif // MAINWINDOW_H
