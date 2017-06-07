#include "interfazobra.h"
//#include "ui_interfazobra.h"

InterfazObra::InterfazObra(QString nombrefichero, QWidget *parent):QWidget(parent)
{
    AbrirGuardar* A = new AbrirGuardarBC3();    
    O = A->Leer(nombrefichero);
    if (O)
    {
        O->IrAInicio();
        O->MostrarHijos();
        GenerarUI();
    }
}

InterfazObra::InterfazObra(QString codigo, QString resumen,QWidget *parent):QWidget(parent)
{
    O= new Obra(codigo,resumen);
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
    separadorPrincipal = new QSplitter(Qt::Vertical);

    //tabla principal
    modeloTablaP = new PrincipalModel(O);
    tablaPrincipal = new TablaPrincipal(modeloTablaP->columnCount(QModelIndex()), separadorPrincipal);
    tablaPrincipal->setModel(modeloTablaP);
    separadorPrincipal->addWidget(tablaPrincipal);

    //tabla mediciones
    modeloTablaMC = new MedicionesModel(O);
    tablaMediciones =  new TablaMedCert(modeloTablaMC->columnCount(QModelIndex()), this);
    tablaMediciones->setModel(modeloTablaMC);
    separadorTablasMedicion = new QTabWidget;
    separadorTablasMedicion->addTab(tablaMediciones,QString(tr("Medicion")));
    separadorTablasMedicion->addTab(new QWidget(),"+");

    separadorPrincipal->addWidget(separadorTablasMedicion);

    //editor
    editor = new Editor(separadorPrincipal);
    separadorPrincipal->addWidget(editor);

    //añado el separador al layout
    lienzoGlobal->addWidget(separadorPrincipal);

    RefrescarVista(QModelIndex(),QModelIndex());
    MostrarDeSegun(0);   

    /************signals y slots*****************/
    QObject::connect(tablaPrincipal,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(BajarNivel(QModelIndex)));
    QObject::connect(tablaPrincipal->CabeceraDeTabla(),SIGNAL(sectionDoubleClicked(int)),this,SLOT(SubirNivel()));
    QObject::connect(tablaPrincipal,SIGNAL(clicked(QModelIndex)),this,SLOT(PosicionarTablaP(QModelIndex)));
    QObject::connect(tablaPrincipal,SIGNAL(CambiaFila(QModelIndex)),this,SLOT(PosicionarTablaP(QModelIndex)));
    QObject::connect(tablaMediciones,SIGNAL(CambiaFila(QModelIndex)),this,SLOT(PosicionarTablaM(QModelIndex)));
    QObject::connect(tablaPrincipal,SIGNAL(CopiarPartidas()),this,SLOT(CopiarPartidasTablaP()));
    QObject::connect(tablaPrincipal,SIGNAL(PegarPartidas()),this,SLOT(PegarPartidasTablaP()));
    QObject::connect(tablaMediciones,SIGNAL(CopiarMedicion()),this,SLOT(CopiarMedicionTablaM()));
    QObject::connect(tablaMediciones,SIGNAL(PegarMedicion()),this,SLOT(PegarMedicionTablaM()));
    //QObject::connect(ui->TablaMed,SIGNAL(clicked(QModelIndex)),this,SLOT(PosicionarTablaM(QModelIndex)));
    QObject::connect(modeloTablaP, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)), this, SLOT(RefrescarVista(QModelIndex,QModelIndex)));
    QObject::connect(modeloTablaMC, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)), this, SLOT(RefrescarVista(QModelIndex,QModelIndex)));


    //QObject::connect(tabMedCert,SIGNAL(currentChanged(int)),this,SLOT(CambiarMedCert(int)));
}

Obra* InterfazObra::LeeObra()
{
    return O;
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
    tablaPrincipal->clearSelection();
    modeloTablaP->QuitarIndicadorFilaVacia();
    GuardarTextoPartida();
    O->SubirNivel();
    RefrescarVista(QModelIndex(),QModelIndex());
    //O->MostrarHijos();
    //qDebug()<<"Subir nivel";
}

void InterfazObra::BajarNivel(QModelIndex indice)
{
    Q_UNUSED (indice);
    modeloTablaP->QuitarIndicadorFilaVacia();
    GuardarTextoPartida();
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
    modeloTablaP->QuitarIndicadorFilaVacia();
    GuardarTextoPartida();
    O->Siguiente();
    RefrescarVista(QModelIndex(),QModelIndex());
}

void InterfazObra::Retroceder()
{
    modeloTablaP->QuitarIndicadorFilaVacia();
    GuardarTextoPartida();
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

    modeloTablaP->ActualizarDatos();
    modeloTablaMC->ActualizarDatos();
    if (modeloTablaP->rowCount(QModelIndex())==0)
    {
        modeloTablaP->insertRow(0);
    }
    //O->MostrarHijos();
    EscribirTexto();
    //MostrarTexto();
    modeloTablaP->layoutChanged();
    modeloTablaMC->layoutChanged();
    tablaPrincipal->resizeColumnsToContents();
    tablaMediciones->resizeColumnsToContents();
    separadorTablasMedicion->setVisible(O->EsPartida());//solo se ve si es partida(Nat == 7)

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
    if (editor->HayCambios())
    {
        O->EditarTexto(editor->LeeContenido());
    }
}

void InterfazObra::CopiarPartidasTablaP()
{
    emit CopiarP();
}

void InterfazObra::CopiarMedicionTablaM()
{
    emit CopiarM();
}

void InterfazObra::CopiarPartidas(std::list<std::pair<pArista, pNodo>>&listaNodosCopiarPegar)
{
    listaNodosCopiarPegar.clear();
    QItemSelectionModel *selecmodel = tablaPrincipal->selectionModel();
    QModelIndexList selectedRowsIndexesList = selecmodel->selectedIndexes();
    CopiarPartidasPortapapeles(selectedRowsIndexesList);
    QList<int> listaIndices;
    foreach (const QModelIndex &i, selectedRowsIndexesList)
    {
        if (!listaIndices.contains(i.row()))
            listaIndices.append(i.row());
    }
    qSort(listaIndices);
    O->CopiarPartidas(listaNodosCopiarPegar, listaIndices);
    selecmodel->clearSelection();
}

void InterfazObra::CopiarPartidasPortapapeles(const QModelIndexList &lista)
{
    QString textoACopiar;
    for(int i = 0; i < lista.size(); i++)
    {
        //if (i!=0 && (i-10)%10!=0 && (i-9)%9!=0) //excluyo de los datos a copiar la primera y ultima columna (Fase e Id)
        {
            QModelIndex index = lista.at(i);
            textoACopiar.append(modeloTablaP->data(index).toString());
            textoACopiar.append('\t');
        }
    }
    //textoACopiar.replace(",",".");
    int i=0, n=0;
    while (i<textoACopiar.size())
    {
        if (textoACopiar.at(i)=='\t')
        {
            n++;
        }
        if (n==11)
        {
            textoACopiar.replace(i,1,'\n');
            n=0;
        }
        i++;
    }
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(textoACopiar);

}

void InterfazObra::PegarPartidasTablaP()
{
    emit PegarP();
}

void InterfazObra::PegarMedicionTablaM()
{
    emit PegarM();
}

void InterfazObra::PegarPartidas(const std::list<std::pair<pArista, pNodo>>&listaNodosCopiarPegar)
{
    QModelIndex indice = tablaPrincipal->currentIndex();
    qDebug()<<indice.row();
    bool insertarAlFinal=false;
    if (modeloTablaP->HayFilaVacia() && indice.row()==modeloTablaP->FilaVacia())
    {
        insertarAlFinal=true;
    }
    O->Pegar(listaNodosCopiarPegar, insertarAlFinal);
    modeloTablaP->QuitarIndicadorFilaVacia();
    RefrescarVista(QModelIndex(),QModelIndex());
}

void InterfazObra::CopiarMedicion(Medicion& listaMedicionCopiarPegar)
{
    listaMedicionCopiarPegar.BorrarMedicion();
    QItemSelectionModel *selecmodel = tablaMediciones->selectionModel();
    QModelIndexList selectedRowsIndexesList = selecmodel->selectedIndexes();
    CopiarMedicionPortapapeles(selectedRowsIndexesList);
    QList<int> listaIndices;
    foreach (const QModelIndex &i, selectedRowsIndexesList)
    {
        if (!listaIndices.contains(i.row()))
            listaIndices.append(i.row());
    }
    qSort(listaIndices);
    O->CopiarMedicion(listaMedicionCopiarPegar, listaIndices);
    foreach (int i, listaIndices)
        qDebug()<<"Copiando las linea de medicion: "<<i;
    selecmodel->clearSelection();
}

void InterfazObra::CopiarMedicionPortapapeles(const QModelIndexList& lista)
{
    QString textoACopiar;
    for(int i = 0; i < lista.size(); i++)
    {
        if (i!=0 && (i-10)%10!=0 && (i-9)%9!=0) //excluyo de los datos a copiar la primera y ultima columna (Fase e Id)
        {
            QModelIndex index = lista.at(i);
            textoACopiar.append(modeloTablaMC->data(index).toString());
            textoACopiar.append('\t');
        }
    }    
    textoACopiar.replace(",",".");
    int i=0, n=0;
    while (i<textoACopiar.size())
    {
        if (textoACopiar.at(i)=='\t')
        {
            n++;
        }
        if (n==8)
        {
            textoACopiar.replace(i,1,'\n');
            n=0;
        }
        i++;
    }
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(textoACopiar);    
}

void InterfazObra::PegarMedicion(const Medicion& ListaMedicion)
{    
    QModelIndex indice = tablaMediciones->currentIndex();
    O->PegarMedicion(indice.row(),ListaMedicion);//indice.row() es la fila de la tabla a partir de la cual pego
    RefrescarVista(QModelIndex(),QModelIndex());
}

void InterfazObra::GuardarBC3(QString fileName)
{
    QFile ficheroBC3(fileName);
    if (ficheroBC3.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        AbrirGuardarBC3* bc3 =  new AbrirGuardarBC3;
        bc3->Escribir(ficheroBC3,O);
        ficheroBC3.close();
        delete bc3;
    }
}
