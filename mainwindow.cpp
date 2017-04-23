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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ActionNuevo()
{
    DialogoDatosCodigoResumen* cuadro = new DialogoDatosCodigoResumen(this);
    if (cuadro->exec())
    {
        MetaObra NuevaObra;
        NuevaObra.miobra=new InterfazObra(cuadro->LeeCodigo(),cuadro->LeeResumen());
        AnadirObraAVentanaPrincipal(NuevaObra);
    }
    delete cuadro;
    ui->actionGuardar->setEnabled(true);
}

void MainWindow::ActionAbrir()
{
    QString nombrefichero;
    nombrefichero = QFileDialog::getOpenFileName(this,\
                                                 tr("Abrir Obra"),\
                                                 rutaarchivo,\
                                                 tr("Archivos BC3 (*.bc3);;Archivos SDM (*.sdm)"));

    if (!nombrefichero.isEmpty())
    {
        MetaObra NuevaObra;
        NuevaObra.nombrefichero = nombrefichero;
        NuevaObra.miobra = new InterfazObra(nombrefichero);
        AnadirObraAVentanaPrincipal(NuevaObra);
    }
    ruta.setPath(nombrefichero);
    rutaarchivo=ruta.canonicalPath();
    ui->actionGuardar->setEnabled(true);
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
    if (obraActual->nombrefichero.isEmpty())
    {
        return ActionGuardarComo();
    }
    else
    {
        return GuardarObra(obraActual->nombrefichero);
    }
}

bool MainWindow::ActionGuardarComo()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Guardar Obra"), ".",
                                                    tr("Archivos BC3 (*.bc3);;Archivos SDM (*.sdm)"));
    if (fileName.isEmpty())
    {
        return false;
    }
    return GuardarObra(fileName);
}

bool MainWindow::GuardarObra(QString &nombreFichero)
{
    obraActual->nombrefichero=nombreFichero;
    QString extension = nombreFichero.right(4);
    if (extension!=".bc3" && extension!=".BC3")
    {
        nombreFichero.append(".bc3");
    }
    obraActual->miobra->GuardarBC3(nombreFichero);
    return true;
}

void MainWindow::ActionCerrar()
{   
    if (!ListaObras.empty())
    {
        std::list<MetaObra>::iterator obraBorrar = obraActual;
        {
            obraActual = ListaObras.erase(obraActual);
            delete obraBorrar->miobra;
            if ( obraActual == ListaObras.end() && !ListaObras.empty())
            {
                obraActual = std::prev(obraActual);
            }
        }
    }
    if (ListaObras.empty())
    {
        ui->actionGuardar->setEnabled(false);
    }
}

void MainWindow::updateRecentFileActions()
{
    QMutableStringListIterator i(recentFiles);
    while (i.hasNext()) {
        if (!QFile::exists(i.next()))
            i.remove();
    }
    for (int j = 0; j < MaxRecentFiles; ++j) {
        if (j < recentFiles.count()) {
            QString text = tr("&%1 %2")
                    .arg(j + 1)
                    .arg(strippedName(recentFiles[j]));
            recentFileActions[j]->setText(text);
            recentFileActions[j]->setData(recentFiles[j]);
            recentFileActions[j]->setVisible(true);
        } else {
            recentFileActions[j]->setVisible(false);
        }
    }
    separatorAction->setVisible(!recentFiles.isEmpty());
}

QString MainWindow::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}


void MainWindow::ActionSalir()
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
    if (isWindowModified())
    {
        int r = QMessageBox::warning(this, tr("SDMed"),
                                     tr("La obra ha sido modificada.\n"
                                        "¿Quieres guardar los cambios?"),
                                     QMessageBox::Yes | QMessageBox::Default,
                                     QMessageBox::No,
                                     QMessageBox::Cancel | QMessageBox::Escape);
        if (r == QMessageBox::Yes)
        {
            return ActionGuardar();
        }
        else if (r == QMessageBox::Cancel)
        {
            return false;
        }
    }
    return true;
}

void MainWindow::setupActions()
{
    QObject::connect(ui->actionNuevo,SIGNAL(triggered(bool)),this,SLOT(ActionNuevo()));
    QObject::connect(ui->actionAbrir,SIGNAL(triggered(bool)),this,SLOT(ActionAbrir()));
    QObject::connect(ui->actionCerrar,SIGNAL(triggered(bool)),this,SLOT(ActionCerrar()));
    QObject::connect(ui->actionGuardar,SIGNAL(triggered(bool)),this,SLOT(ActionGuardar()));
    QObject::connect(ui->actionGuardar_como,SIGNAL(triggered(bool)),this,SLOT(ActionGuardarComo()));
    QObject::connect(ui->action_Salir, SIGNAL(triggered(bool)),qApp, SLOT(quit()));
    QObject::connect(ui->tabPrincipal,SIGNAL(currentChanged(int)),this,SLOT(CambiarObraActual(int)));
    QObject::connect(ui->actionAdelante,SIGNAL(triggered(bool)),this,SLOT(ActionAdelante()));
    QObject::connect(ui->actionAtras,SIGNAL(triggered(bool)),this,SLOT(ActionAtras()));
    QObject::connect(comboMedCert,SIGNAL(currentIndexChanged(int)),this,SLOT(CambiarMedCert(int)));
}
