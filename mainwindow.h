#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QList>
#include <QDir>
#include <QSettings>

#include "interfazobra.h"
#include "Dialogos/dialogodatoscodigoresumen.h"
#include "Dialogos/dialogonuevacertificacion.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString strippedName(const QString &fullFileName);

private slots:
    void ActionNuevo();
    bool ActionAbrir();
    bool ActionGuardar();
    bool ActionGuardarComo();
    void ActionCerrar();
    void ActionSalir();
    void ActionCopiar();
    void ActionPegar();
    void ActionCortar();

    void ActionUndo();
    void ActionRedo();

    void ActionAdelante();
    void ActionAtras();
    void CambiarObraActual(int indice);
    void CambiarMedCert(int indice);
    void NuevaCertificacion();
    void CambiarCertificacionActual(int actual);

    void AbrirArchivo(const QString& nombrefichero);
    bool ActionAbrirDesdeReciente();
    void updateArchivosRecientesActions();

    void ActivarDesactivarBotonesUndoRedo(int indice);


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
    //menu abrir reciente
    QStringList recentFiles;
    enum { MaxRecentFiles = 5 };
    QAction *recentFileActions[MaxRecentFiles];
    QAction *separatorAction;
    //fin de menu abrir reciente
    Ui::MainWindow *ui;

    bool ConfirmarContinuar();
    void setupActions();
    void AnadirObraAVentanaPrincipal(MetaObra& nuevaobra);
    bool GuardarObra(QString nombreFichero);

    bool HayObra();
    //combo ver medicion/certificacion
    //el combo he de annadirlo a mano porque no se puede insertar un widget a una qToolBar desde QtDesigner
    QLabel* labelVerMedCert;
    QComboBox* comboMedCert;
    //boton nueva certificacion
    QPushButton* botonNuevaCertificacion;
    //combo certificacion actual
    QLabel* labelCertificacionActual;
    QComboBox* comboCertificacionActual;

    QDir ruta;
    //listas para copiar y pegar
    std::list<std::pair<pArista,pNodo>>ListaNodosCopiarPegar;
    Medicion ListaMedicionCopiarPegar;

    void writeSettings();
    void readSettings();
};

#endif // MAINWINDOW_H
