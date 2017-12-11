#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //seccion ver medicion/certificacion
    labelVerMedCert = new QLabel("Ver:");
    comboMedCert = new QComboBox;
    comboMedCert->addItem(tr("Medición"));
    comboMedCert->addItem(tr("Certificación"));
    comboMedCert->setEnabled(false);//lo inicio desactivado mientras no haya una obra activa
    ui->CertBar->addWidget(labelVerMedCert);
    ui->CertBar->addWidget(comboMedCert);
    //seccion annadir nueva certificacion
    botonNuevaCertificacion = new QPushButton(tr("Añadir Certificación"));
    botonNuevaCertificacion->setEnabled(false);
    ui->CertBar->addWidget(botonNuevaCertificacion);
    //seccion certificacion actual
    labelCertificacionActual = new QLabel(tr("Cert. actual"));
    comboCertificacionActual = new QComboBox;
    ui->CertBar->addWidget(labelCertificacionActual);
    ui->CertBar->addWidget(comboCertificacionActual);
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
    comboMedCert->setEnabled(true);
    botonNuevaCertificacion->setEnabled(true);
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
    QObject::connect(nuevaobra.miobra,SIGNAL(ActivarBoton(int)),this,SLOT(ActivarDesactivarBotonesPila(int)));
    ui->tabPrincipal->addTab(nuevaobra.miobra,nuevaobra.miobra->LeeObra()->LeeResumenObra());
    ui->tabPrincipal->setCurrentIndex(ui->tabPrincipal->currentIndex()+1);
    ListaObras.push_back(nuevaobra);
    obraActual=ListaObras.begin();
    std::advance(obraActual,ListaObras.size()-1);
    ActivarDesactivarBotonesPila(obraActual->miobra->Pila()->index());
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
            ActivarDesactivarBotonesPila(obraActual->miobra->Pila()->index());
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
    if (recentFiles.contains(nombrefichero))
    {
        recentFiles.removeAll(nombrefichero);
    }
    recentFiles.prepend(nombrefichero);
    updateArchivosRecientesActions();
    AbrirArchivo(nombrefichero);
    return true;
}

void MainWindow::AbrirArchivo(const QString &nombrefichero)
{
    MetaObra NuevaObra;
    NuevaObra.nombrefichero = nombrefichero;
    NuevaObra.miobra = new InterfazObra(nombrefichero);
    AnadirObraAVentanaPrincipal(NuevaObra);
    comboMedCert->setEnabled(true);
    botonNuevaCertificacion->setEnabled(true);
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
    bool toReturn=false;
    qDebug()<<"Nombrefichero: "<<nombreFichero;
    QString extension = nombreFichero.right(4);
    qDebug()<<"La extension del archivo a guardar es "<<extension;
    obraActual->nombrefichero=nombreFichero;
    if (extension == ".bc3" || extension == ".BC3")
    {
        obraActual->miobra->GuardarBC3(nombreFichero);
        qDebug()<<"Guardada la obra "<<nombreFichero<<" con exito";
        toReturn = true;
    }
    if (extension == ".sdm" || extension == ".SDM")
    {
        qDebug()<<"Guardando en formato SDM";
        toReturn = true;
    }
    //qDebug()<<"Borrar Pila";
    obraActual->miobra->Pila()->clear();
    return toReturn;
}

void MainWindow::ActionCerrar()
{   
    if (!ListaObras.empty())
    {
        if (ConfirmarContinuar())
        {
            std::list<MetaObra>::iterator obraBorrar = obraActual;
            {
                qDebug()<<"Borrando la obra actual-> "<<obraBorrar->miobra->LeeObra()->LeeResumenObra();
                obraActual = ListaObras.erase(obraActual);
                delete obraBorrar->miobra;
                if ( obraActual == ListaObras.end() && !ListaObras.empty())
                {
                    obraActual = std::prev(obraActual);
                }
            }
        }
    }
    if (ListaObras.empty())
    {
        ui->actionGuardar->setEnabled(false);
        comboMedCert->setEnabled(false);
        botonNuevaCertificacion->setEnabled(false);
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
    for (uint i=ListaObras.size();i>0;i--)
    {
        qDebug()<<"Numero de obras: "<<i;
        ui->tabPrincipal->setCurrentIndex(i);
        emit ui->tabPrincipal->currentChanged(i);
        ActionCerrar();
    }
    if (ListaObras.empty())
    {
        writeSettings();
        qDebug()<<"Salir";
        qApp->quit();
    }
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    ActionSalir();
    QMainWindow::closeEvent(event);
}

void MainWindow::ActionCopiar()
{
    QWidget* w = qApp->focusWidget();
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
    qDebug()<<"Accion Pegar";
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

void MainWindow::ActionUndo()
{
    if (HayObra())
    {
        obraActual->miobra->Undo();
    }
}

void MainWindow::ActionRedo()
{
    if (HayObra())
    {
        obraActual->miobra->Redo();
    }
}

void MainWindow::ActivarDesactivarBotonesPila(int indice)
{
    //qDebug()<<"ActivarDesactivarBotonesUndoRedo(): "<<indice;
    ui->actionDeshacer->setEnabled(indice!=0);
    ui->actionRehacer->setEnabled(indice<obraActual->miobra->Pila()->count());
    ui->actionGuardar->setEnabled(indice!=0);
}

void MainWindow::ActionAdelante()
{
    if (HayObra())
    {
        obraActual->miobra->Mover(movimiento::DERECHA);
    }
}

void MainWindow::ActionAtras()
{
    if (HayObra())
    {
        obraActual->miobra->Mover(movimiento::IZQUIERDA);
    }
}

void MainWindow::AcercaDe()
{
    //QMessageBox::about(this,"Acerca de SDMed","Pues eso <url>http:\\kaka</url>");
    DialogoAbout *d = new DialogoAbout(this);
    d->show();
}

void MainWindow::AcercaDeQt()
{
    QMessageBox::aboutQt(this);
}

void MainWindow::NuevaCertificacion()
{
    DialogoNuevaCertificacion d;
    if (d.exec())
    {
        if (obraActual->miobra->LeeObra()->anadirCertificacion(d.LeeFecha()))
        {
            qDebug()<<"Nueva certificacion añadida con exito";
            int nuevacert = obraActual->miobra->LeeObra()->verNumCertificaciones();
            comboCertificacionActual->addItem(QString::number(nuevacert));
            comboCertificacionActual->setCurrentIndex(nuevacert-1);
        }
        else
        {
            QMessageBox::warning(this, tr("Aviso"),
                                           tr("La fecha ha de ser posterior a la de la última certificación"),
                                 QMessageBox::Ok);
        }
    }
}

void MainWindow::CambiarCertificacionActual(int actual)
{
    obraActual->miobra->LeeObra()->EstablecerCertificacionActual(actual);
}

bool MainWindow::ConfirmarContinuar()
{
    if (obraActual->miobra->Pila()->index()>0)
    {
        QString cadena = tr("La obra  <b>%1</b> ha sido modificada.<br>¿Quieres guardar los cambios?").arg(obraActual->miobra->LeeObra()->LeeResumenObra());
        int r = QMessageBox::warning(this, tr("SDMed"),
                                     cadena,
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

bool MainWindow::HayObra()
{
    return ListaObras.empty();
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
    QObject::connect(ui->actionDeshacer,SIGNAL(triggered(bool)),this,SLOT(ActionUndo()));
    QObject::connect(ui->actionRehacer,SIGNAL(triggered(bool)),this,SLOT(ActionRedo()));
    QObject::connect(ui->tabPrincipal,SIGNAL(currentChanged(int)),this,SLOT(CambiarObraActual(int)));
    QObject::connect(ui->actionAdelante,SIGNAL(triggered(bool)),this,SLOT(ActionAdelante()));
    QObject::connect(ui->actionAtras,SIGNAL(triggered(bool)),this,SLOT(ActionAtras()));
    QObject::connect(ui->actionAcerca_de,SIGNAL(triggered(bool)),this,SLOT(AcercaDe()));
    QObject::connect(ui->actionAcerca_de_Qt,SIGNAL(triggered(bool)),this,SLOT(AcercaDeQt()));
    QObject::connect(comboMedCert,SIGNAL(currentIndexChanged(int)),this,SLOT(CambiarMedCert(int)));
    QObject::connect(botonNuevaCertificacion,SIGNAL(pressed()),this,SLOT(NuevaCertificacion()));
    QObject::connect(comboCertificacionActual,SIGNAL(currentIndexChanged(int)),this,SLOT(CambiarCertificacionActual(int)));
}
