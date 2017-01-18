#include "interfazobra.h"
#include "ui_interfazobra.h"

InterfazObra::InterfazObra(QWidget *parent):QWidget(parent),ui(new Ui::InterfazObra)
{
    AbrirGuardar* A = new AbrirGuardarBC3();
    QString nombrefichero = "/home/david/programacion/cmasmas/PruebasObra/bin/Debug/CENZANO.bc3";
    O = A->Leer(nombrefichero);
    if (O)
    {
        O->IrAInicio();
        O->MostrarHijos();

        ui->setupUi(this);
        filter = new Filter;

        modeloTablaP = new PrincipalModel(O);
        ui->tablaPrinc->setAlternatingRowColors(true);
        ui->tablaPrinc->setModel(modeloTablaP);

        ui->tablaPrinc->setEditTriggers(QAbstractItemView::SelectedClicked | QAbstractItemView::AnyKeyPressed);
        cabeceraTablaP = ui->tablaPrinc->horizontalHeader();
        //cabeceraTablaP->setSelectionMode(QAbstractItemView::NoSelection);

        modeloTablaMC = new MedicionesModel(O);
        ui->TablaMed->setModel(modeloTablaMC);        

        RefrescarVista();
        MostrarDeSegun(0);

        /**********editor*****************/
        EscribirTexto();

        /************signals y slots*****************/
        QObject::connect(ui->tablaPrinc,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(BajarNivel(QModelIndex)));
        QObject::connect(ui->tablaPrinc,SIGNAL(clicked(QModelIndex)),this,SLOT(PosicionarTablaP(QModelIndex)));
        QObject::connect(ui->botonCopiar,SIGNAL(clicked(bool)),this,SLOT(CopiarMedicion()));
        QObject::connect(ui->botonPegar,SIGNAL(clicked(bool)),this,SLOT(PegarMedicion()));
        //QObject::connect(ui->TablaMed,SIGNAL(clicked(QModelIndex)),this,SLOT(PosicionarTablaM(QModelIndex)));
        QObject::connect(modeloTablaMC, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)), this, SLOT(ActualizarTablaMedicion(QModelIndex,QModelIndex)));
        QObject::connect(cabeceraTablaP,SIGNAL(sectionDoubleClicked(int)),this,SLOT(SubirNivel()));
        QObject::connect(ui->comboMedCert,SIGNAL(currentIndexChanged(int)),this,SLOT(MostrarDeSegun(int)));
        //QObject::connect(modeloTablaP,SIGNAL(EditarCampoTexto(int, QString)),this,SLOT(EditarCodigoResumen(int, QString)));
        //QObject::connect(modeloTablaP,SIGNAL(EditarNaturaleza(int)),this,SLOT(EditarNaturaleza(int)));
        //QObject::connect(modeloTablaP,SIGNAL(EditarCampoNumerico(int,float)),this,SLOT(EditarCantidadPrecio(int,float)));        
        //QObject::connect(tabMedCert,SIGNAL(currentChanged(int)),this,SLOT(CambiarMedCert(int)));

        QObject::connect(ui->botonAdelante,SIGNAL(clicked(bool)),this,SLOT(Avanzar()));
        QObject::connect(ui->botonAtras,SIGNAL(clicked(bool)),this,SLOT(Retroceder()));
    }
}


InterfazObra::~InterfazObra()
{
    delete ui;
    delete O;
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
    ui->tablaPrinc->setColumnHidden(tipoColumna::CANCERT,verCertificacion);
    ui->tablaPrinc->setColumnHidden(tipoColumna::PORCERTPRES,verCertificacion);
    ui->tablaPrinc->setColumnHidden(tipoColumna::PRCERT,verCertificacion);
    ui->tablaPrinc->setColumnHidden(tipoColumna::IMPCERT,verCertificacion);
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
    ui->tablaPrinc->clearSelection();
    O->SubirNivel();
    RefrescarVista();
    //O->MostrarHijos();
    //qDebug()<<"Subir nivel";
}

void InterfazObra::BajarNivel(QModelIndex indice)
{
    Q_UNUSED (indice);
    /*if (!O->EsPartidaDummy())
    {
        GuardarTextoPartida();*/
    O->BajarNivel();
    /*if (!O->HayHijos() && (O->EsPartida() || O->EsCapitulo()))
        {
            InsertarFilaVacia();
            QModelIndex posicionActual = modeloTablaP->index(0, 0, QModelIndex());
            tablaP->setCurrentIndex(posicionActual);
        }*/
    RefrescarVista();
    //}
    //qDebug()<<"Bajar nivel";
}

void InterfazObra::Avanzar()
{
    //GuardarTextoPartida();
    O->Siguiente();
    //O->MostrarHijos();
    /*if (!O->HayHijos() && (O->EsPartida() || O->EsCapitulo()))
    {
        InsertarFilaVacia();
    }*/
    RefrescarVista();
}

void InterfazObra::Retroceder()
{
    //GuardarTextoPartida();
    O->Anterior();
    //O->MostrarHijos();
    /*if (!O->HayHijos() && (O->EsPartida() || O->EsCapitulo()))
    {
        InsertarFilaVacia();
    }*/
    RefrescarVista();
}

void InterfazObra::ActualizarTablaMedicion(QModelIndex indice1, QModelIndex indice2)
{
    Q_UNUSED (indice1);
    Q_UNUSED (indice2);
    RefrescarVista();
}

void InterfazObra::RefrescarVista()
{
    modeloTablaP->ActualizarDatos();
    modeloTablaMC->ActualizarDatos();
    //O->MostrarHijos();
    EscribirTexto();
    //MostrarTexto();
    modeloTablaP->layoutChanged();
    modeloTablaMC->layoutChanged();
    ui->tablaPrinc->resizeColumnsToContents();
    ui->TablaMed->resizeColumnsToContents();
    //ui->TablaMed->resizeRowsToContents();
    ui->TablaMed->setVisible(O->EsPartida());//solo se ve si es partida(Nat == 7)    

    //AjustarAltura();
    //MostrarTablasMyC();
}

void InterfazObra::EscribirTexto()
{
    ui->editor->EscribeTexto(O->VerTexto());
}

void InterfazObra::PosicionarTablaP(QModelIndex indice)
{
    O->PosicionarAristaActual(indice.row());    
}

void InterfazObra::PosicionarTablaM(QModelIndex indice)
{
    O->PosicionarLineaActualMedicion(indice.row());
}

void InterfazObra::CopiarMedicion()
{
    QItemSelectionModel *selecmodel = ui->TablaMed->selectionModel();
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
    ui->TablaMed->clearSelection();
}

void InterfazObra::PegarMedicion()
{
    const QClipboard *clipboard = QApplication::clipboard();
    const QMimeData *mimeData = clipboard->mimeData();
    if (mimeData->hasText())
    {
        O->pegarMedicion(ui->TablaMed->currentIndex().row(),mimeData->text());
        RefrescarVista();
    }
}
