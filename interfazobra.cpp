#include "interfazobra.h"
#include "ui_interfazobra.h"

InterfazObra::InterfazObra(QWidget *parent):QWidget(parent)
{
    AbrirGuardar* A = new AbrirGuardarBC3();
    QString nombrefichero = "/home/david/programacion/cmasmas/PruebasObra/bin/Debug/CENZANO.bc3";
    O = A->Leer(nombrefichero);
    //O=new Obra("001 / 14 VDAS","14 Viviendas y garaje");
    if (O)
    {
        O->IrAInicio();
        O->MostrarHijos();
        GenerarUI();
    }
}

InterfazObra::~InterfazObra()
{
    delete O;
}

void InterfazObra::GenerarUI()
{
    lienzoGlobal = new QVBoxLayout(this);
    separador = new QSplitter(Qt::Vertical);
    widgetSuperior = new QWidget(separador);
    separador->addWidget(widgetSuperior);
    lienzoSuperior = new QVBoxLayout(widgetSuperior);


    modeloTablaP = new PrincipalModel(O);
    tablaPrincipal = new TablaPrincipal(modeloTablaP->columnCount(QModelIndex()), separador);
    tablaPrincipal->setModel(modeloTablaP);


    modeloTablaMC = new MedicionesModel(O);
    tablaMediciones =  new TablaMedCert(modeloTablaMC->columnCount(QModelIndex()), separador);
    tablaMediciones->setModel(modeloTablaMC);
    separador->addWidget(tablaMediciones);
    //editor
    editor = new Editor(separador);
    separador->addWidget(editor);
    //zona de botones
    botonAvanzar = new QPushButton("->");
    botonRetroceder = new QPushButton("<-");

    //una vez creadas las tablas y los editores los coloco en el layout
    comboMedCert = new QComboBox;
    comboMedCert->addItem(tr("Medicion"));
    comboMedCert->addItem(tr("Certificación"));
    botonera = new QHBoxLayout();
    botonera->addWidget(comboMedCert);
    botonera->addWidget(botonRetroceder);
    botonera->addWidget(botonAvanzar);
    botonera->addStretch();

    lienzoSuperior->addLayout(botonera);
    lienzoSuperior->addWidget(tablaPrincipal);

    lienzoGlobal->addWidget(separador);

    RefrescarVista(QModelIndex(),QModelIndex());
    MostrarDeSegun(0);

    /**********editor*****************/
    //EscribirTexto();

    /************signals y slots*****************/
    QObject::connect(tablaPrincipal,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(BajarNivel(QModelIndex)));
    QObject::connect(tablaPrincipal->CabeceraDeTabla(),SIGNAL(sectionDoubleClicked(int)),this,SLOT(SubirNivel()));
    QObject::connect(tablaPrincipal,SIGNAL(clicked(QModelIndex)),this,SLOT(PosicionarTablaP(QModelIndex)));
    QObject::connect(tablaPrincipal,SIGNAL(CambiaFila(QModelIndex)),this,SLOT(PosicionarTablaP(QModelIndex)));
    //QObject::connect(ui->botonCopiar,SIGNAL(clicked(bool)),this,SLOT(CopiarMedicion()));
    //QObject::connect(ui->botonPegar,SIGNAL(clicked(bool)),this,SLOT(PegarMedicion()));
    //QObject::connect(ui->TablaMed,SIGNAL(clicked(QModelIndex)),this,SLOT(PosicionarTablaM(QModelIndex)));
    QObject::connect(modeloTablaP, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)), this, SLOT(RefrescarVista(QModelIndex,QModelIndex)));
    QObject::connect(modeloTablaMC, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)), this, SLOT(RefrescarVista(QModelIndex,QModelIndex)));

    QObject::connect(comboMedCert,SIGNAL(currentIndexChanged(int)),this,SLOT(MostrarDeSegun(int)));    
    //QObject::connect(tabMedCert,SIGNAL(currentChanged(int)),this,SLOT(CambiarMedCert(int)));

    QObject::connect(botonAvanzar,SIGNAL(clicked(bool)),this,SLOT(Avanzar()));
    QObject::connect(botonRetroceder,SIGNAL(clicked(bool)),this,SLOT(Retroceder()));

    //QObject::connect(ui->botonGuardar,SIGNAL(clicked(bool)),this,SLOT(GuardarBC3()));

}

void InterfazObra::MostrarDeSegun(int indice)
{
    bool verCertificacion;
    if (indice==0)
    {
        verCertificacion=true;
    }
    else
    {
        verCertificacion=false;
    }
    tablaPrincipal->setColumnHidden(tipoColumna::CANCERT,verCertificacion);
    tablaPrincipal->setColumnHidden(tipoColumna::PORCERTPRES,verCertificacion);
    tablaPrincipal->setColumnHidden(tipoColumna::PRCERT,verCertificacion);
    tablaPrincipal->setColumnHidden(tipoColumna::IMPCERT,verCertificacion);
}

void InterfazObra::SubirNivel()
{
    /*GuardarTextoPartida();
    EliminarFilasVacias();

    if (guardar.recuperar)
    {
        guardar.Arista->nodo_destino->datonodo.EscribePrecio(guardar.precio);
        qDebug()<<"Poniendo precio: "<<guardar.precio;
        guardar.recuperar=false;
        O->Actualizar(guardar.Arista->nodo_destino);
    }*/
    tablaPrincipal->clearSelection();
    modeloTablaP->QuitarIndicadorFilaVacia();
    O->SubirNivel();
    RefrescarVista(QModelIndex(),QModelIndex());
    //O->MostrarHijos();
    //qDebug()<<"Subir nivel";
}

void InterfazObra::BajarNivel(QModelIndex indice)
{
    Q_UNUSED (indice);
    GuardarTextoPartida();
    modeloTablaP->QuitarIndicadorFilaVacia();
    O->BajarNivel();
    /*if (!O->HayHijos() && (O->EsPartida() || O->EsCapitulo()))
        {
            InsertarFilaVacia();
            QModelIndex posicionActual = modeloTablaP->index(0, 0, QModelIndex());
            tablaP->setCurrentIndex(posicionActual);
        }*/
    RefrescarVista(QModelIndex(),QModelIndex());
    //}
    //qDebug()<<"Bajar nivel";
}

void InterfazObra::Avanzar()
{
    //GuardarTextoPartida();
    modeloTablaP->QuitarIndicadorFilaVacia();
    O->Siguiente();

    //O->MostrarHijos();
    /*if (!O->HayHijos() && (O->EsPartida() || O->EsCapitulo()))
    {
        InsertarFilaVacia();
    }*/
    RefrescarVista(QModelIndex(),QModelIndex());
}

void InterfazObra::Retroceder()
{
    //GuardarTextoPartida();
    modeloTablaP->QuitarIndicadorFilaVacia();
    O->Anterior();
    //O->MostrarHijos();
    /*if (!O->HayHijos() && (O->EsPartida() || O->EsCapitulo()))
    {
        InsertarFilaVacia();
    }*/
    RefrescarVista(QModelIndex(),QModelIndex());
}

void InterfazObra::RefrescarVista(QModelIndex indice1, QModelIndex indice2)
{
    Q_UNUSED (indice1);
    Q_UNUSED (indice2);
    if (modeloTablaP->rowCount(QModelIndex())==0)
    {
        modeloTablaP->insertRow(0);
    }
    modeloTablaP->ActualizarDatos();
    modeloTablaMC->ActualizarDatos();    
    //O->MostrarHijos();
    EscribirTexto();
    //MostrarTexto();
    modeloTablaP->layoutChanged();
    modeloTablaMC->layoutChanged();
    tablaPrincipal->resizeColumnsToContents();
    tablaMediciones->resizeColumnsToContents();
    tablaMediciones->setVisible(O->EsPartida());//solo se ve si es partida(Nat == 7)

    //AjustarAltura();
    //MostrarTablasMyC();
}

void InterfazObra::EscribirTexto()
{
    editor->EscribeTexto(O->VerTexto());
}

void InterfazObra::PosicionarTablaP(QModelIndex indice)
{
    int linea = indice.row();
    if (modeloTablaP->HayFilaVacia())
    {
        if (linea > modeloTablaP->FilaVacia())
        {
            linea = indice.row()-1;
        }
    }
    O->PosicionarAristaActual(linea);
}

void InterfazObra::PosicionarTablaM(QModelIndex indice)
{
    O->PosicionarLineaActualMedicion(indice.row());
}

void InterfazObra::GuardarTextoPartida()
{

}

void InterfazObra::CopiarMedicion()
{
    QItemSelectionModel *selecmodel = tablaMediciones->selectionModel();
    QModelIndexList list = selecmodel->selectedIndexes();
    QString textoACopiar;
    for(int i = 0; i < list.size(); i++)
    {
        if (i!=0 && (i-10)%10!=0 && (i-9)%9!=0) //excluyo de los datos a copiar la primera y ultima columna (Fase e Id)
        {
            QModelIndex index = list.at(i);
            textoACopiar.append(modeloTablaMC->data(index).toString());
            textoACopiar.append(";");
        }
    }
    textoACopiar.replace(",",".");
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(textoACopiar);
    tablaMediciones->clearSelection();
}

void InterfazObra::PegarMedicion()
{
    const QClipboard *clipboard = QApplication::clipboard();
    const QMimeData *mimeData = clipboard->mimeData();
    if (mimeData->hasText())
    {
        O->pegarMedicion(tablaMediciones->currentIndex().row(),mimeData->text());
        RefrescarVista(QModelIndex(),QModelIndex());
    }
}

void InterfazObra::GuardarBC3()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Guardar fichero"),
                                                    "/home/david/noname.bc3",
                                                    tr("FIEBDC-12 (*.bc3)"));

    QFile ficheroBC3(fileName);
    if (ficheroBC3.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        AbrirGuardarBC3* bc3 =  new AbrirGuardarBC3;
        bc3->Escribir(ficheroBC3,O);
        ficheroBC3.close();
        delete bc3;
    }
}
