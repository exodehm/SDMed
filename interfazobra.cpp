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

        modeloTablaP = new PrincipalModel(O);
        ui->tablaPrinc->setAlternatingRowColors(true);
        ui->tablaPrinc->setModel(modeloTablaP);

        ui->tablaPrinc->setEditTriggers(QAbstractItemView::SelectedClicked | QAbstractItemView::AnyKeyPressed);
        cabeceraTablaP = ui->tablaPrinc->horizontalHeader();

        modeloTablaMC =  new MedicionesModel(O);
        ui->TablaMed->setModel(modeloTablaMC);

        RefrescarVista();

        MostrarDeSegun(0);

        /**********editor*****************/
        EscribirTexto();

        /************signals y slots*****************/
        QObject::connect(ui->tablaPrinc,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(BajarNivel(QModelIndex)));
        QObject::connect(ui->tablaPrinc,SIGNAL(clicked(QModelIndex)),this,SLOT(PosicionarTablaP(QModelIndex)));
        //QObject::connect(tablaMC[0],SIGNAL(clicked(QModelIndex)),this,SLOT(PosicionarTablaM(QModelIndex)));
        QObject::connect(cabeceraTablaP,SIGNAL(sectionDoubleClicked(int)),this,SLOT(SubirNivel()));
        QObject::connect(ui->comboMedCert,SIGNAL(currentIndexChanged(int)),this,SLOT(MostrarDeSegun(int)));
        //QObject::connect(modeloTablaP,SIGNAL(EditarCampoTexto(int, QString)),this,SLOT(EditarCodigoResumen(int, QString)));
        //QObject::connect(modeloTablaP,SIGNAL(EditarNaturaleza(int)),this,SLOT(EditarNaturaleza(int)));
        //QObject::connect(modeloTablaP,SIGNAL(EditarCampoNumerico(int,float)),this,SLOT(EditarCantidadPrecio(int,float)));
        //QObject::connect(modeloTablaM,SIGNAL(EditarCampoLineaMedicion(int,float,QString)),this,SLOT(EditarCampoLineaMedicion(int,float, QString)));
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
    O->SubirNivel();
    RefrescarVista();
    //O->MostrarHijos();
    qDebug()<<"Subir nivel";
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
    qDebug()<<"Bajar nivel";
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

void InterfazObra::RefrescarVista()
{
    modeloTablaP->ActualizarDatos();
    modeloTablaMC->ActualizarDatos();
    O->MostrarHijos();
    EscribirTexto();
    //MostrarTexto();
    modeloTablaP->layoutChanged();
    modeloTablaMC->layoutChanged();
    ui->tablaPrinc->resizeColumnsToContents();
    ui->TablaMed->resizeColumnsToContents();

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
    qDebug()<<"Estoy en: "<<indice.row()<<" :: "<<indice.column();
}




