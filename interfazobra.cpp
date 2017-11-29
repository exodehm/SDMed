#include "interfazobra.h"
//#include "ui_interfazobra.h"

InterfazObra::InterfazObra(QString nombrefichero, QWidget *parent):QWidget(parent)
{
    AbrirGuardar* A = new AbrirGuardarBC3();    
    O = A->Leer(nombrefichero);
    if (O)
    {
        IniciarObra();
    }
}

InterfazObra::InterfazObra(QString codigo, QString resumen,QWidget *parent):QWidget(parent)
{
    O= new Obra(codigo,resumen);
    if (O)
    {
       IniciarObra();
    }
}

void InterfazObra::IniciarObra()
{
    O->IrAInicio();    
    pila = new QUndoStack(this);
    GenerarUI();
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
    modeloTablaP = new PrincipalModel(O, pila);
    tablaPrincipal = new TablaPrincipal(modeloTablaP->columnCount(QModelIndex()), separadorPrincipal);
    tablaPrincipal->setObjectName("TablaP");
    tablaPrincipal->setModel(modeloTablaP);
    separadorPrincipal->addWidget(tablaPrincipal);

    //tabla mediciones
    modeloTablaMed = new MedCertModel(O, MedCert::MEDICION, pila);
    tablaMediciones =  new TablaMedCert(modeloTablaMed->columnCount(QModelIndex()), this);
    tablaMediciones->setObjectName("TablaMC");
    tablaMediciones->setModel(modeloTablaMed);
    //tabla certificaciones
    modeloTablaCert = new MedCertModel(O, MedCert::CERTIFICACION, pila);
    tablaCertificaciones =  new TablaMedCert(modeloTablaCert->columnCount(QModelIndex()), this);
    tablaCertificaciones->setModel(modeloTablaCert);
    tablaCertificaciones->setEnabled(false);
    //tab para las tablas de mediciones y certificaciones
    separadorTablasMedicion = new QTabWidget;
    separadorTablasMedicion->addTab(tablaMediciones,QString(tr("Medicion")));
    separadorTablasMedicion->addTab(tablaCertificaciones,QString(tr("Certificacion")));

    separadorPrincipal->addWidget(separadorTablasMedicion);

    //editor
    editor = new Editor(separadorPrincipal);
    separadorPrincipal->addWidget(editor);

    //añado el separador al layout
    lienzoGlobal->addWidget(separadorPrincipal);

    RefrescarVista();
    MostrarDeSegun(0);
    O->cambiarEntreMedYCert(MedCert::MEDICION);    

    /************signals y slots*****************/
    QObject::connect(tablaPrincipal,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(BajarNivel()));
    QObject::connect(tablaPrincipal->CabeceraDeTabla(),SIGNAL(sectionDoubleClicked(int)),this,SLOT(SubirNivel()));
    QObject::connect(tablaPrincipal,SIGNAL(clicked(QModelIndex)),this,SLOT(PosicionarTablaP(QModelIndex)));
    QObject::connect(tablaPrincipal,SIGNAL(CambiaFila(QModelIndex)),this,SLOT(PosicionarTablaP(QModelIndex)));
    QObject::connect(tablaMediciones,SIGNAL(CambiaFila(QModelIndex)),this,SLOT(PosicionarTablaM(QModelIndex)));
    QObject::connect(modeloTablaMed,SIGNAL(Posicionar(QModelIndex)),this,SLOT(PosicionarTablaM(QModelIndex)));
    QObject::connect(tablaPrincipal,SIGNAL(CopiarPartidas()),this,SLOT(CopiarPartidasTablaP()));
    QObject::connect(tablaPrincipal,SIGNAL(PegarPartidas()),this,SLOT(PegarPartidasTablaP()));
    QObject::connect(tablaMediciones,SIGNAL(CopiarMedicion()),this,SLOT(CopiarMedicionTablaM()));
    QObject::connect(tablaMediciones,SIGNAL(PegarMedicion()),this,SLOT(PegarMedicionTablaM()));
    QObject::connect(tablaMediciones,SIGNAL(CertificarLineasMedicion()),this,SLOT(Certificar()));    
    QObject::connect(separadorTablasMedicion,SIGNAL(currentChanged(int)),this,SLOT(CambiarEntreMedicionYCertificacion(int)));
    QObject::connect(pila,SIGNAL(indexChanged(int)),this,SLOT(ActivarDesactivarUndoRedo(int)));
    QObject::connect(pila,SIGNAL(indexChanged(int)),this,SLOT(RefrescarVista()));
    QObject::connect(editor->LeeEditor(),SIGNAL(GuardaTexto()),this,SLOT(GuardarTextoPartida()));
    QObject::connect(editor,SIGNAL(GuardaTexto()),this,SLOT(GuardarTextoPartida()));

}

Obra* InterfazObra::LeeObra()
{
    return O;
}

QUndoStack* InterfazObra::Pila()
{
    return pila;
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
    GuardarTextoPartidaInicial();
    QString cadenaundo = tr("Subir nivel");
    //pila->push(new UndoMover(movimiento::ARRIBA,this,cadenaundo));
    O->SubirNivel();
    modeloTablaP->QuitarIndicadorFilaVacia();
    RefrescarVista(QModelIndex(),QModelIndex());*/
    Mover(movimiento::ARRIBA);
}

void InterfazObra::BajarNivel()
{
    /*Q_UNUSED (indice);
    GuardarTextoPartidaInicial();
    GuardarTextoPartidaModificada();
    QString cadenaundo = tr("Bajar nivel");
    //pila->push(new UndoMover(movimiento::ABAJO, this,cadenaundo));
    O->BajarNivel();
    RefrescarVista(QModelIndex(),QModelIndex());*/
    Mover(movimiento::ABAJO);
}

/*void InterfazObra::Avanzar()
{
    GuardarTextoPartida();
    GuardarTextoPartidaInicial();
    QString cadenaundo = tr("Avanzar");
    //pila->push(new UndoMover(movimiento::DERECHA,this,cadenaundo));
    O->Siguiente();
    RefrescarVista(QModelIndex(),QModelIndex());
}*/

/*void InterfazObra::Retroceder()
{
    GuardarTextoPartida();
    GuardarTextoPartidaInicial();
    QString cadenaundo = tr("Retroceder");
    //pila->push(new UndoMover(movimiento::IZQUIERDA,this,cadenaundo));
    O->Anterior();
    RefrescarVista(QModelIndex(),QModelIndex());
}
*/

void InterfazObra::Mover(int tipomovimiento)
{
    GuardarTextoPartidaInicial();
    switch (tipomovimiento)
    {
    case movimiento::ARRIBA:
    {
        O->SubirNivel();
        break;
    }
    case movimiento::ABAJO:
    {
        O->BajarNivel();
        break;
    }
    case movimiento::DERECHA:
    {
        O->Siguiente();
        break;
    }
    case movimiento::IZQUIERDA:
    {
        O->Anterior();
        break;
    }
    default:
        break;
    }
    //modeloTablaP->QuitarIndicadorFilaVacia();
    tablaPrincipal->clearSelection();
    RefrescarVista();
}

void InterfazObra::Undo()
{
    qDebug()<<"Undo en: "<<O->LeeResumenObra();
    pila->undo();
}

void InterfazObra::Redo()
{
    qDebug()<<"Redo en: "<<O->LeeResumenObra();
    pila->redo();
}

void InterfazObra::RefrescarVista()
{
    modeloTablaP->ActualizarDatos(O->LeeDescompuesto());
    modeloTablaMed->ActualizarDatos();
    modeloTablaCert->ActualizarDatos();
    modeloTablaP->QuitarIndicadorFilaVacia();
    if (modeloTablaP->rowCount(QModelIndex())==0)
    {
        modeloTablaP->insertRow(0);
    }
    EscribirTexto();
    editor->Formatear();
    GuardarTextoPartidaInicial();
    modeloTablaP->layoutChanged();
    modeloTablaMed->layoutChanged();
    modeloTablaCert->layoutChanged();
    tablaPrincipal->resizeColumnsToContents();
    tablaPrincipal->setCurrentIndex(indiceActual);
    tablaMediciones->resizeColumnsToContents();
    tablaCertificaciones->resizeColumnsToContents();
    separadorTablasMedicion->setVisible(O->EsPartida());//solo se ve si es partida(Nat == 7)    
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
    indiceActual=indice;
    O->PosicionarAristaActual(linea);
}

void InterfazObra::PosicionarTablaM(QModelIndex indice)
{
    O->PosicionarLineaActualMedicion(indice.row());
    
}

void InterfazObra::GuardarTextoPartidaInicial()
{
    if (!O->EsPartidaVacia())
    {
        textoPartidaInicial = editor->LeeContenidoConFormato();
        //qDebug()<<"textoPartidaActual"<<textoPartidaInicial;
    }
}

void InterfazObra::GuardarTextoPartida()
{
    qDebug()<<QApplication::focusWidget();
    if (editor->HayCambios())
    {
        TablaBase* tabla = qobject_cast<TablaBase*>(QApplication::focusWidget());
        if (tabla)
        {
            QString cadenaundo = ("Cambiar texto de partida a " + editor->LeeContenido());
            pila->push(new UndoEditarTexto(O,modeloTablaP, QModelIndex(), textoPartidaInicial, editor->LeeContenidoConFormato(), cadenaundo));            
        }
    }
}

TEXTO InterfazObra::TextoPartidaInicial()
{
    return textoPartidaInicial;
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

void InterfazObra::PegarPartidas(const Obra::ListaAristasNodos &listaNodosCopiarPegar)
{
    qDebug()<<"Pegar partidas";
    QModelIndex indice = tablaPrincipal->currentIndex();
    qDebug()<<indice.row();
    bool insertarAlFinal=false;
    if (modeloTablaP->HayFilaVacia() && indice.row()==modeloTablaP->FilaVacia())
    {
        insertarAlFinal=true;
    }
    O->Pegar(listaNodosCopiarPegar, insertarAlFinal);
    modeloTablaP->QuitarIndicadorFilaVacia();
    RefrescarVista();
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
            textoACopiar.append(modeloTablaMed->data(index).toString());
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
    QString cadenaundo = tr("Pegar lineas de medicion");
    pila->push(new UndoPegarLineasMedicion(O,indice.row(),ListaMedicion,cadenaundo));
    RefrescarVista();
}

void InterfazObra::ActivarDesactivarUndoRedo(int indice)
{
    ActivarBoton(indice);
}

void InterfazObra::Certificar()
{
    Medicion listaParaCertificar;
    CopiarMedicion(listaParaCertificar);
    O->Certificar(listaParaCertificar);
}

void InterfazObra::CambiarEntreMedicionYCertificacion(int n)
{
    O->cambiarEntreMedYCert(n);
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

PrincipalModel* InterfazObra::ModeloTablaPrincipal()
{
    return modeloTablaP;
}

TablaBase* InterfazObra::LeeTablaPrincipal()
{
    return tablaPrincipal;
}
