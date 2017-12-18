#include "instancia.h"

Instancia::Instancia(QString nombrefichero, QWidget *parent):QWidget(parent)
{
    AbrirGuardar* A;
    switch (TipoFichero(nombrefichero)) {
    case tipoFichero::BC3:
        A = new AbrirGuardarBC3();
        break;
    case tipoFichero::SEG:
        A = new AbrirGuardarSEG();
        break;
    default:
        break;
    }
    O = A->Leer(nombrefichero);
    if (O)
    {
        IniciarObra();
    }    
}

Instancia::Instancia(QString codigo, QString resumen,QWidget *parent):QWidget(parent)
{
    O= new Obra(codigo,resumen);
    if (O)
    {
       IniciarObra();
    }
}

void Instancia::IniciarObra()
{
    O->IrAInicio();
    pila = new QUndoStack(this);
    GenerarUI();
}

Instancia::~Instancia()
{
    delete O;    
}

void Instancia::GenerarUI()
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

Obra* Instancia::LeeObra()
{
    return O;
}

QUndoStack* Instancia::Pila()
{
    return pila;
}

void Instancia::MostrarDeSegun(int indice)
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

void Instancia::SubirNivel()
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

void Instancia::BajarNivel()
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

/*void Instancia::Avanzar()
{
    GuardarTextoPartida();
    GuardarTextoPartidaInicial();
    QString cadenaundo = tr("Avanzar");
    //pila->push(new UndoMover(movimiento::DERECHA,this,cadenaundo));
    O->Siguiente();
    RefrescarVista(QModelIndex(),QModelIndex());
}*/

/*void Instancia::Retroceder()
{
    GuardarTextoPartida();
    GuardarTextoPartidaInicial();
    QString cadenaundo = tr("Retroceder");
    //pila->push(new UndoMover(movimiento::IZQUIERDA,this,cadenaundo));
    O->Anterior();
    RefrescarVista(QModelIndex(),QModelIndex());
}
*/

void Instancia::Mover(int tipomovimiento)
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

void Instancia::IrAInicio()
{
    O->IrTope();
    RefrescarVista();
}

void Instancia::Undo()
{
    qDebug()<<"Undo en: "<<O->LeeResumenObra();
    pila->undo();
}

void Instancia::Redo()
{
    qDebug()<<"Redo en: "<<O->LeeResumenObra();
    pila->redo();
}

void Instancia::RefrescarVista()
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

void Instancia::EscribirTexto()
{
    editor->EscribeTexto(O->VerTexto());
}

void Instancia::PosicionarTablaP(QModelIndex indice)
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

void Instancia::PosicionarTablaM(QModelIndex indice)
{
    O->PosicionarLineaActualMedicion(indice.row());
    
}

void Instancia::GuardarTextoPartidaInicial()
{
    if (!O->EsPartidaVacia())
    {
        textoPartidaInicial = editor->LeeContenidoConFormato();
        //qDebug()<<"textoPartidaActual"<<textoPartidaInicial;
    }
}

void Instancia::GuardarTextoPartida()
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

TEXTO Instancia::TextoPartidaInicial()
{
    return textoPartidaInicial;
}

void Instancia::CopiarPartidasTablaP()
{
    emit CopiarP();
}

void Instancia::CopiarMedicionTablaM()
{
    emit CopiarM();
}

void Instancia::CopiarPartidas(std::list<std::pair<pArista, pNodo>>&listaNodosCopiarPegar)
{
    //en esta funcion creo una lista de int para almacenar los indices de las lineas seleccionadas de la tabla
    //con esta lista de indices y las lista de nodos seleccionados me voy a la funcion Obra::CopiarPartidas
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

void Instancia::CopiarPartidasPortapapeles(const QModelIndexList &lista)
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

void Instancia::PegarPartidasTablaP()
{
    emit PegarP();
}

void Instancia::PegarMedicionTablaM()
{
    emit PegarM();
}

void Instancia::PegarPartidas(const Obra::ListaAristasNodos &listaNodosCopiarPegar)
{
    qDebug()<<"Pegar partidas";
    QModelIndex indice = tablaPrincipal->currentIndex();
    qDebug()<<indice.row();
    bool insertarAlFinal=false;
    if (modeloTablaP->HayFilaVacia() && indice.row()==modeloTablaP->FilaVacia())
    {
        insertarAlFinal=true;
    }
    QString cadenaundo = "Pegar partidas";
    //O->Pegar(listaNodosCopiarPegar,insertarAlFinal);
    pila->push(new UndoPegarPartidas(O,modeloTablaP,indice,listaNodosCopiarPegar, insertarAlFinal,cadenaundo));
    RefrescarVista();
}

void Instancia::CopiarMedicion(Medicion& listaMedicionCopiarPegar)
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
    /*foreach (int i, listaIndices)
        qDebug()<<"Copiando las linea de medicion: "<<i;*/
    selecmodel->clearSelection();
}

void Instancia::CopiarMedicionPortapapeles(const QModelIndexList& lista)
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

void Instancia::PegarMedicion(const Medicion& ListaMedicion)
{    
    QModelIndex indice = tablaMediciones->currentIndex();
    QString cadenaundo = tr("Pegar lineas de medicion");
    pila->push(new UndoPegarLineasMedicion(O,indice.row(),ListaMedicion,cadenaundo));
    RefrescarVista();
}

void Instancia::ActivarDesactivarUndoRedo(int indice)
{
    ActivarBoton(indice);
}

void Instancia::AjustarPresupuesto(float cantidades[2])
{
    pila->push(new UndoAjustarPresupuesto(O,cantidades));
}

void Instancia::Certificar()
{
    Medicion listaParaCertificar;
    CopiarMedicion(listaParaCertificar);
    O->Certificar(listaParaCertificar);
}

void Instancia::CambiarEntreMedicionYCertificacion(int n)
{
    O->cambiarEntreMedYCert(n);
}

void Instancia::GuardarBC3(QString filename)
{
    QFile ficheroBC3(filename);
    if (ficheroBC3.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        AbrirGuardarBC3* bc3 =  new AbrirGuardarBC3;
        bc3->Escribir(ficheroBC3,O);
        ficheroBC3.close();
        delete bc3;
    }
}

void Instancia::GuardarSEG(QString filename)
{
    QFile ficheroSEG(filename);
    if (ficheroSEG.open(QIODevice::WriteOnly))
    {
        AbrirGuardarSEG* seg = new AbrirGuardarSEG;
        seg->Escribir(ficheroSEG,O);
        ficheroSEG.close();
        delete seg;
    }
}

PrincipalModel* Instancia::ModeloTablaPrincipal()
{
    return modeloTablaP;
}

TablaBase* Instancia::LeeTablaPrincipal()
{
    return tablaPrincipal;
}

int Instancia::TipoFichero(TEXTO nombrefichero)
{
    nombrefichero=nombrefichero.toLower();
    if (nombrefichero.endsWith(".bc3"))
    {
        return tipoFichero::BC3;
    }
    else if (nombrefichero.endsWith(".seg"))
    {
        return tipoFichero::SEG;
    }
    else return tipoFichero::NOVALIDO;
}
