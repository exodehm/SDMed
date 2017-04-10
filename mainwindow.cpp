#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    label = new QLabel("Ver:");
    comboMedCert = new QComboBox;
    comboMedCert->addItem(tr("Medicion"));
    comboMedCert->addItem(tr("Certificación"));
    ui->toolBar->addWidget(label);
    ui->toolBar->addWidget(comboMedCert);
    setupActions();

    //establezco la ruta incial para localizar archivos
    ruta = QDir::currentPath();
    rutaarchivo = ruta.canonicalPath();
    qDebug()<<"Ruta: "<<rutaarchivo;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ActionNuevo()
{
    if (!ConfirmarContinuar())
    {
        DialogoDatosCodigoResumen* cuadro = new DialogoDatosCodigoResumen(this);
        if (cuadro->exec())
        {
            MetaObra NuevaObra;
            NuevaObra.miobra=new InterfazObra(cuadro->LeeCodigo(),cuadro->LeeResumen());
            AnadirObraAVentanaPrincipal(NuevaObra);
        }
        delete cuadro;
    }
}

void MainWindow::ActionAbrir()
{
    QString nombrefichero;
    if (!ConfirmarContinuar())
    {
        nombrefichero = QFileDialog::getOpenFileName(this,\
                                                             tr("Abrir Obra"),\
                                                             rutaarchivo,\
                                                             tr("Archivos BC3 (*.bc3)"));
    }
    if (!nombrefichero.isEmpty())
    {
        MetaObra NuevaObra;
        NuevaObra.nombrefichero = nombrefichero;
        NuevaObra.miobra = new InterfazObra(nombrefichero);
        AnadirObraAVentanaPrincipal(NuevaObra);
    }
    ruta.setPath(nombrefichero);
    rutaarchivo=ruta.canonicalPath();
}

void MainWindow::AnadirObraAVentanaPrincipal(MetaObra &nuevaobra)
{
    ui->tabPrincipal->addTab(nuevaobra.miobra,nuevaobra.miobra->LeeObra()->LeeResumenObra());
    ui->tabPrincipal->setCurrentIndex(ui->tabPrincipal->currentIndex()+1);
    ListaObras.push_back(nuevaobra);
    obraActual=ListaObras.begin();
    std::advance(obraActual,ListaObras.size()-1);
    QString leyenda = QString(tr("Creada la obra %1").arg(obraActual->miobra->LeeObra()->LeeResumenObra()));
    statusBar()->showMessage(leyenda,5000);
}

void MainWindow::CambiarObraActual(int indice)
{
    if (!ListaObras.empty())
    {
        if ((unsigned int)indice<ListaObras.size())
        {
            obraActual=ListaObras.begin();
            std::advance(obraActual,indice);
        }
    }
}

void MainWindow::CambiarMedCert(int indice)
{
    obraActual->miobra->MostrarDeSegun(indice);
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
    obraActual->miobra->Avanzar();
}

void MainWindow::ActionAtras()
{
    obraActual->miobra->Retroceder();
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
    QObject::connect(ui->actionAbrir,SIGNAL(triggered(bool)),this,SLOT(ActionAbrir()));
    QObject::connect(ui->action_Salir, SIGNAL(triggered(bool)),qApp, SLOT(quit()));
    QObject::connect(ui->tabPrincipal,SIGNAL(currentChanged(int)),this,SLOT(CambiarObraActual(int)));
    QObject::connect(ui->actionAdelante,SIGNAL(triggered(bool)),this,SLOT(ActionAdelante()));
    QObject::connect(ui->actionAtras,SIGNAL(triggered(bool)),this,SLOT(ActionAtras()));
    QObject::connect(comboMedCert,SIGNAL(currentIndexChanged(int)),this,SLOT(CambiarMedCert(int)));
}
