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
    //cargo los settings
    readSettings();
    //archivos recientes
    for (int i=0;i<MaxRecentFiles;i++)
    {
        recentFileActions[i] = new QAction(this);
        connect (recentFileActions[i], SIGNAL(triggered()), this, SLOT(ActionAbrirDesdeReciente()));
        ui->menuAbrir_reciente->addAction(recentFileActions[i]);
    }
    updateArchivosRecientesActions();
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

bool MainWindow::ActionAbrir()
{
    QString nombrefichero;
    nombrefichero = QFileDialog::getOpenFileName(this,\
                                                 tr("Abrir Obra"),\
                                                 rutaarchivo,\
                                                 tr("Archivos BC3 (*.bc3);;Archivos SDM (*.sdm)"));
    for (auto elem : ListaObras)
    {
        if (nombrefichero == elem.nombrefichero)
        {
            QMessageBox::warning(this, tr("Aviso"),
                                           tr("La obra %1 ya está abierta").arg(nombrefichero),
                                           QMessageBox::Ok);
            return false;
        }
    }

    if (!nombrefichero.isEmpty())
    {
        if (recentFiles.contains(nombrefichero))
        {
            recentFiles.removeAll(nombrefichero);
        }
        recentFiles.prepend(nombrefichero);

        updateArchivosRecientesActions();
        AbrirArchivo(nombrefichero);
        ruta.setPath(nombrefichero);
        rutaarchivo=ruta.canonicalPath();
        ui->actionGuardar->setEnabled(true);
        return true;
    }
    return false;
}

void MainWindow::AnadirObraAVentanaPrincipal(MetaObra &nuevaobra)
{
    QObject::connect(nuevaobra.miobra,SIGNAL(CopiarP()),this,SLOT(ActionCopiar()));
    QObject::connect(nuevaobra.miobra,SIGNAL(PegarP()),this,SLOT(ActionPegar()));
    QObject::connect(nuevaobra.miobra,SIGNAL(CopiarM()),this,SLOT(ActionCopiar()));
    QObject::connect(nuevaobra.miobra,SIGNAL(PegarM()),this,SLOT(ActionPegar()));
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

bool MainWindow::ActionAbrirDesdeReciente()
{
    QAction *action = qobject_cast<QAction *>(sender());
    QString nombrefichero;
    if (action)
    {
        nombrefichero = action->data().toString();
    }
    int indice=0;
    for (auto elem : ListaObras)
    {
        if (nombrefichero == elem.nombrefichero)
        {
            qDebug()<<"Cambio la obra al indice: "<<indice;
            CambiarObraActual(indice);
            ui->tabPrincipal->setCurrentIndex(indice);
            return false;
        }
        indice++;
    }
    AbrirArchivo(nombrefichero);
    return true;
}

void MainWindow::AbrirArchivo(const QString &nombrefichero)
{
    MetaObra NuevaObra;
    NuevaObra.nombrefichero = nombrefichero;
    NuevaObra.miobra = new InterfazObra(nombrefichero);
    AnadirObraAVentanaPrincipal(NuevaObra);    
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
    QFileDialog d(this,tr("Guardar fichero"),QDir::homePath(),tr("Archivos BC3 (*.bc3);;Archivos SDM (*.sdm)"));
    if (d.exec())
    {
        QString fileName = d.selectedFiles()[0];
        if (fileName.isEmpty())
        {
            return false;
        }
        else
        {
            QString extension = d.selectedNameFilter();
            extension = extension.right(5);
            extension = extension.left(4);
            if (fileName.right(4)==".bc3" || fileName.right(4)==".sdm")
            {
                fileName=fileName.left(fileName.size()-4);
            }
            return GuardarObra(fileName + extension);
        }
    }
    return false;
}

bool MainWindow::GuardarObra(QString nombreFichero)
{
    qDebug()<<"Nombrefichero: "<<nombreFichero;
    QString extension = nombreFichero.right(4);
    qDebug()<<"La extension del archivo a guardar es "<<extension;
    obraActual->nombrefichero=nombreFichero;
    if (extension == ".bc3" || extension == ".BC3")
    {
        obraActual->miobra->GuardarBC3(nombreFichero);
        qDebug()<<"Guardada la obra "<<nombreFichero<<" con exito";
        return true;
    }
    if (extension == ".sdm" || extension == ".SDM")
    {
        qDebug()<<"Guardando en formato SDM";
        return true;
    }
    return false;
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

void MainWindow::updateArchivosRecientesActions()
{
    while (recentFiles.size()>MaxRecentFiles)
    {
        recentFiles.removeLast();
    }
    qDebug()<<"Numero de archivos recientes : "<<recentFiles.count();
    QMutableStringListIterator i(recentFiles);
    while (i.hasNext()) {
        if (!QFile::exists(i.next()))
            i.remove();
    }
    //actualizar el submenu
    for (int j = 0; j < MaxRecentFiles; ++j)
    {
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
    /*separatorAction->setVisible(!recentFiles.isEmpty());*/
}

QString MainWindow::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}

void MainWindow::ActionSalir()
{
    writeSettings();
    qDebug()<<"Salir";
    qApp->quit();
}

void MainWindow::ActionCopiar()
{
    QWidget* w = qApp->focusWidget();
    qDebug()<<"Copiar main: "<<w->metaObject()->className();
    if (strcmp(w->metaObject()->className(),"TablaPrincipal")==0)
    {
        obraActual->miobra->CopiarPartidas(ListaNodosCopiarPegar);
    }
    if (strcmp(w->metaObject()->className(),"TablaMedCert")==0)
    {
        obraActual->miobra->CopiarMedicion(ListaMedicionCopiarPegar);
    }
}

void MainWindow::ActionPegar()
{
    QWidget* w = qApp->focusWidget();
    qDebug()<<w->metaObject()->className();
    if (strcmp(w->metaObject()->className(),"TablaPrincipal")==0)
    {
       obraActual->miobra->PegarPartidas(ListaNodosCopiarPegar);
    }
    if (strcmp(w->metaObject()->className(),"TablaMedCert")==0)
    {
        obraActual->miobra->PegarMedicion(ListaMedicionCopiarPegar);
    }
}

void MainWindow::ActionCortar()
{
    qDebug()<<"Accion Cortar";
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

void MainWindow::readSettings()
{
    QSettings settings("EGSoft", "SDMed");
    settings.beginGroup("MainWindow");
    QPoint pos = settings.value("pos").toPoint();
    QSize size = settings.value("size").toSize();
    recentFiles = settings.value("recentfiles").toStringList();
    this->resize(size);
    this->move(pos);    
    settings.endGroup();
}

void MainWindow::writeSettings()
{
    QSettings settings("EGSoft", "SDMed");
    settings.beginGroup("MainWindow");
    settings.setValue("pos", this->pos());
    settings.setValue("size", this->size());
    settings.setValue("recentfiles", recentFiles);
    settings.endGroup();
}

void MainWindow::setupActions()
{
    QObject::connect(ui->actionNuevo,SIGNAL(triggered(bool)),this,SLOT(ActionNuevo()));
    QObject::connect(ui->actionAbrir,SIGNAL(triggered(bool)),this,SLOT(ActionAbrir()));
    QObject::connect(ui->actionCerrar,SIGNAL(triggered(bool)),this,SLOT(ActionCerrar()));
    QObject::connect(ui->actionGuardar,SIGNAL(triggered(bool)),this,SLOT(ActionGuardar()));
    QObject::connect(ui->actionGuardar_como,SIGNAL(triggered(bool)),this,SLOT(ActionGuardarComo()));
    QObject::connect(ui->action_Salir, SIGNAL(triggered(bool)),this, SLOT(ActionSalir()));
    QObject::connect(ui->actionCopiar,SIGNAL(triggered(bool)),this,SLOT(ActionCopiar()));
    QObject::connect(ui->actionCortar,SIGNAL(triggered(bool)),this,SLOT(ActionCortar()));
    QObject::connect(ui->actionPegar,SIGNAL(triggered(bool)),this,SLOT(ActionPegar()));
    QObject::connect(ui->tabPrincipal,SIGNAL(currentChanged(int)),this,SLOT(CambiarObraActual(int)));
    QObject::connect(ui->actionAdelante,SIGNAL(triggered(bool)),this,SLOT(ActionAdelante()));
    QObject::connect(ui->actionAtras,SIGNAL(triggered(bool)),this,SLOT(ActionAtras()));
    QObject::connect(comboMedCert,SIGNAL(currentIndexChanged(int)),this,SLOT(CambiarMedCert(int)));    
}
