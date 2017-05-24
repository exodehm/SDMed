#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QList>
#include <QDir>

#include "interfazobra.h"
#include "Dialogos/dialogodatoscodigoresumen.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void updateRecentFileActions();
    QString strippedName(const QString &fullFileName);

private slots:
    void ActionNuevo();
    void ActionAbrir();
    bool ActionGuardar();
    bool ActionGuardarComo();
    void ActionCerrar();
    void ActionSalir();
    void ActionCopiar();
    void ActionPegar();
    void ActionCortar();

    void ActionAdelante();
    void ActionAtras();
    void CambiarObraActual(int indice);
    void CambiarMedCert(int indice);

private:

    struct MetaObra
    {
        InterfazObra* miobra;
        QString nombrefichero;
        MetaObra():miobra(nullptr){}
        //~MetaObra(){delete miobra;}
    };
    std::list<MetaObra>ListaObras;
    std::list<MetaObra>::iterator obraActual;    
    QString rutaarchivo;

    QStringList recentFiles;
    enum { MaxRecentFiles = 5 };
    QAction *recentFileActions[MaxRecentFiles];
    QAction *separatorAction;

    Ui::MainWindow *ui;

    bool ConfirmarContinuar();
    void setupActions();
    void AnadirObraAVentanaPrincipal(MetaObra& nuevaobra);
    bool GuardarObra(QString nombreFichero);
    //el combo he de annadirlo a mano porque no se puede insertar un widget a una qToolBar desde QtDesigner
    QLabel* label;
    QComboBox* comboMedCert;

    QDir ruta;
    //listas para copiar y pegar
    std::list<std::pair<pArista,pNodo>>ListaNodosCopiarPegar;
    Medicion ListaMedicionCopiarPegar;
};

#endif // MAINWINDOW_H
