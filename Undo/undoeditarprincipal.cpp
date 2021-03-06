#include "undoeditarprincipal.h"

UndoEditarPrincipal::UndoEditarPrincipal(Obra *O, PrincipalModel *M, QModelIndex I, QVariant D,
                                                 QString descripcion, QUndoCommand *parent):
    obra(O),modelo(M),indice(I),datoNuevo(D), QUndoCommand(descripcion,parent)
{
    datoAntiguo = indice.data() ;
    pilaAristas = obra->LeePilaAristas();
    setText(descripcion);
}

QModelIndex UndoEditarPrincipal::LeeIndice() const
{
    return indice;
}

void UndoEditarPrincipal::undo()
{
    qDebug()<<"Undo en clase base";
}

void UndoEditarPrincipal::redo()
{
    qDebug()<<"Redo en clase base";
}

//#############################CODIGO#############################//

UndoEditarCodigo::UndoEditarCodigo(Obra* O, PrincipalModel* M,  QModelIndex I, QVariant D, QString descripcion, QUndoCommand* parent):
    UndoEditarPrincipal(O,M,I,D,descripcion,parent)
{
    accion = codigo::NADA;
    filaInsertar=modelo->FilaVacia();
}

void UndoEditarCodigo::undo()
{
    qDebug()<<"UndoEditarCodigo";
    obra->Posicionar(pilaAristas, indice.row());
    switch (accion)
    {
    case codigo::NUEVO:
        qDebug()<<"Borrando el codigo y la partida";       
        modelo->removeRow(indice.row());
        break;
    case codigo::CAMBIAR:
        obra->EditarCodigo(datoAntiguo.toString());
        break;
    default:
        break;
    }
}

void UndoEditarCodigo::redo()
{
    qDebug()<<"RedoEditarCodigo";
    obra->Posicionar(pilaAristas, indice.row());
    qDebug()<<"La fila vacia esta en: "<<modelo->FilaVacia();
    if ((indice.row()==modelo->FilaVacia() && modelo->HayFilaVacia()) || accion==codigo::NUEVO)//insertar partida nueva
    {
        qDebug()<<"Insertando codigo en la fila "<<indice.row();
        accion = codigo::NUEVO;
        obra->PosicionarAristaActual(indice.row());
        obra->CrearPartida(datoNuevo.toString(),filaInsertar);
        modelo->QuitarIndicadorFilaVacia();
    }
    else
    {
        qDebug()<<"EDITAR codigo en la fila "<<indice.row();
        accion = codigo::CAMBIAR;
        obra->EditarCodigo(datoNuevo.toString());
    }
}

//#############################NATURALEZA#############################//

UndoEditarNaturaleza::UndoEditarNaturaleza(Obra* O, PrincipalModel* M,  QModelIndex I, QVariant D, QString descripcion, QUndoCommand* parent):
    UndoEditarPrincipal(O,M,I,D,descripcion,parent)
{
    qDebug()<<"DatoAntiguo: "<<datoAntiguo;
    qDebug()<<"DatoNuevo: "<<datoNuevo;
}

void UndoEditarNaturaleza::undo()
{
    qDebug()<<"UndoEditarNaturaleza";
    obra->Posicionar(pilaAristas,indice.row());
    obra->EditarNaturaleza(datoAntiguo.toInt());    
}

void UndoEditarNaturaleza::redo()
{
    qDebug()<<"RedoEditarNaturaleza";
    obra->Posicionar(pilaAristas,indice.row());
    obra->EditarNaturaleza(datoNuevo.toInt());   
}

//#############################UNIDAD#############################//

UndoEditarUnidad::UndoEditarUnidad(Obra* O, PrincipalModel* M,  QModelIndex I, QVariant D, QString descripcion, QUndoCommand* parent):
    UndoEditarPrincipal(O,M,I,D,descripcion,parent)
{

}

void UndoEditarUnidad::undo()
{
    qDebug()<<"UndoEditarUnidad";
    obra->Posicionar(pilaAristas,indice.row());
    obra->EditarUnidad(datoAntiguo.toString());
}

void UndoEditarUnidad::redo()
{
    qDebug()<<"RedoEditarUnidad";
    obra->Posicionar(pilaAristas,indice.row());
    obra->EditarUnidad(datoNuevo.toString());   
}


//#############################RESUMEN#############################//

UndoEditarResumen::UndoEditarResumen(Obra* O, PrincipalModel* M,  QModelIndex I, QVariant D, QString descripcion, QUndoCommand* parent):
    UndoEditarPrincipal(O,M,I,D,descripcion,parent)
{

}

void UndoEditarResumen::undo()
{
    qDebug()<<"UndoEditarResumen";
    obra->Posicionar(pilaAristas, indice.row());
    obra->EditarResumen(datoAntiguo.toString());
}

void UndoEditarResumen::redo()
{
    qDebug()<<"RedoEditarResumen";
    obra->Posicionar(pilaAristas, indice.row());
    obra->EditarResumen(datoNuevo.toString());
}


//#############################CANTIDAD#############################//

UndoEditarCantidad::UndoEditarCantidad(Obra* O, PrincipalModel* M,  QModelIndex I, QVariant D, QString descripcion, QUndoCommand* parent):
    UndoEditarPrincipal(O,M,I,D,descripcion,parent)
{    
    ListaMedicion = obra->LeeListaMedicion(obra->AristaActual(), MedCert::MEDICION);//habra que completarlo para que trabaje sobre la certificacion
    QString cantidadstring = datoAntiguo.toString();
    cantidadstring.replace(",",".");
    cantidadAntigua=cantidadstring.toFloat();
    cantidadNueva = datoNuevo.toFloat();
}

void UndoEditarCantidad::undo()
{
    qDebug()<<"UndoEditarCantidad con datoAntiguo: "<<cantidadAntigua<<" y datonuevo: "<<cantidadNueva;
    obra->Posicionar(pilaAristas,indice.row());
    if (ListaMedicion.hayMedicion())
    {
        qDebug()<<"Caso 1";
        obra->EditarCantidad(0);//pongo a 0 el valor
        obra->PegarMedicion(0,ListaMedicion,obra->AristaActual());
    }
    else
    {
        qDebug()<<"Caso 2";
        obra->EditarCantidad(cantidadAntigua);
    }   
}

void UndoEditarCantidad::redo()
{
    qDebug()<<"RedoEditarCantidad con datoNuevo: "<<cantidadNueva<<" y datoAntiguo: "<<cantidadAntigua;
    //guardo la medicion
    obra->Posicionar(pilaAristas,indice.row());
    obra->EditarCantidad(cantidadNueva);
}

//#############################PRECIO#############################//

UndoEditarPrecio::UndoEditarPrecio(Obra* O, PrincipalModel* M,  QModelIndex I, QVariant D, int A, QString descripcion, QUndoCommand* parent):
    UndoEditarPrincipal(O,M,I,D,descripcion,parent)
{
    accion = A;
    QString preciostring = datoAntiguo.toString();
    preciostring.replace(",",".");
    precioAntiguo=preciostring.toFloat();
    precioNuevo=datoNuevo.toFloat();
}

void UndoEditarPrecio::undo()
{
    qDebug()<<"UndoEditarPrecio en fila: "<<indice.row();
    obra->Posicionar(pilaAristas,indice.row());
    switch (accion)
    {
    case precio::MODIFICAR:
        qDebug()<<"modificar undo";
        obra->EditarPrecio(precioAntiguo);
        break;
    case precio::SUPRIMIR:    
        qDebug()<<"suprimir undo";
        obra->BajarNivel();
        obra->Pegar(listanodos);
        obra->SubirNivel();
        break;    
    case precio::BLOQUEAR:
        qDebug()<<"bloquear undo";
        obra->DesbloquearPrecio();
        break;
    case precio::AJUSTAR:
        qDebug()<<"Ajustar undo";
        break;
    default:
        break;
    }  
}

void UndoEditarPrecio::redo()
{
    qDebug()<<"RedoEditarPrecio";
    obra->Posicionar(pilaAristas,indice.row());
    switch (accion) {
    case precio::MODIFICAR:
        qDebug()<<"modificar undo";
        obra->EditarPrecio(precioNuevo);
        break;
    case precio::SUPRIMIR:
    {
        qDebug()<<"suprimir undo";
        qDebug()<<obra->AristaActual()->destino->datonodo.LeeCodigo();
        rama = obra->GrafoAPartirDeNodo(obra->AristaActual()->destino);
        cantidad = new t_arista(*obra->AristaActual());
        std::pair<pArista,pNodo> pareja(cantidad,rama);
        listanodos.push_back(pareja);
        obra->SuprimirDescomposicion();
        obra->EditarPrecio(precioNuevo);
        break;
    }
    case precio::BLOQUEAR:
        qDebug()<<"bloquear undo";
        obra->BloquearPrecio(precioNuevo);
        break;
    case precio::AJUSTAR:
        qDebug()<<"Ajustar undo";
        break;
    default:
        break;
    } 
}

//#############################TEXTO#############################//
UndoEditarTexto::UndoEditarTexto(Obra* O, PrincipalModel* M,  QModelIndex I, TEXTO TAntiguo, TEXTO TNuevo,  QString descripcion, QUndoCommand* parent):
    textoantiguo(TAntiguo),UndoEditarPrincipal(O,M,I,QVariant(),descripcion,parent)
{
    textoantiguo=TAntiguo;
    textonuevo=TNuevo;
    setText(text());
}

void UndoEditarTexto::undo()
{
    //qDebug()<<"Undo EditarTextoPartida: "<<textoantiguo<<"--"<<textonuevo;
    obra->Posicionar(pilaAristas,indice.row());
    obra->EditarTexto(textoantiguo);
}

void UndoEditarTexto::redo()
{
    //qDebug()<<"Redo EditarTextoPartida: "<<textonuevo<<"--"<<textoantiguo;
    obra->Posicionar(pilaAristas,indice.row());
    obra->EditarTexto(textonuevo);
}

//########################BORRAR PARTIDAS#########################//
UndoBorrarPartidas::UndoBorrarPartidas(Obra* O, PrincipalModel* M, QList<int>listaindices, QString descripcion, QUndoCommand* parent):
    UndoEditarPrincipal(O,M,QModelIndex(),QVariant(),descripcion,parent)
{
    indices=listaindices;//indices de menor a mayor
    for (auto elem:indices)
    {
        qDebug()<<"Indicelemento: "<<elem;
        rIndices.push_front(elem);//indices de mayor a menor
    }
    Obra::ListaAristasNodos listaAux;
    listaAux = obra->LeeGrafo()->recorrerHijos(obra->Padre());
    auto iterator = listaAux.begin();
    for (auto elem:rIndices)
    {
        std::advance(iterator,elem);
        qDebug()<<"Numero de fila: "<<elem;        
        pNodo N = obra->GrafoAPartirDeNodo(iterator->second);
        pArista A = new t_arista(*iterator->first);
        std::pair<pArista,pNodo> pareja(A,N);
        listanodos.push_back(pareja);
        iterator = listaAux.begin();
    }
    rListanodos=listanodos;
    rListanodos.reverse();
    pilaAristas = obra->LeePilaAristas();
    setText(descripcion);
}

void UndoBorrarPartidas::undo()
{
    qDebug()<<"Undo borrar partidas en fila: "<<indice.row();
    obra->Posicionar(pilaAristas,indice.row());
    obra->InsertarPartidas(rListanodos,indices);
    qDebug()<<"Fin de undooo";
}

void UndoBorrarPartidas::redo()
{
    qDebug()<<"Redo borrar partidas en fila: "<<indice.row();
    obra->Posicionar(pilaAristas,indice.row());
    foreach (int i, rIndices)
    {        
        obra->PosicionarAristaActual(i);
        obra->BorrarPartida();
    }
}

//########################PEGAR PARTIDAS#########################//
UndoPegarPartidas::UndoPegarPartidas(Obra* O, PrincipalModel* M, QModelIndex I, Obra::ListaAristasNodos listanodospegar, bool U , QString descripcion, QUndoCommand* parent):
    ultimafila(U),UndoEditarPrincipal(O,M,I,QVariant(),descripcion,parent)
{
    for (auto elem:listanodospegar)
    {
        pNodo N = obra->GrafoAPartirDeNodo(elem.second);
        pArista A = new t_arista(*elem.first);
        std::pair<pArista,pNodo> pareja(A,N);
        listanodos.push_back(pareja);
    }
    pilaAristas = obra->LeePilaAristas();
    setText(descripcion);
}

void UndoPegarPartidas::undo()
{
    qDebug()<<"Undo pegar partidas";
    obra->Posicionar(pilaAristas,indice.row());
    for (uint i=0;i<listanodos.size();i++)
    {
        obra->PosicionarAristaActual(indice.row());
        obra->BorrarPartida();
    }
}

void UndoPegarPartidas::redo()
{
    qDebug()<<"Redo pegar partidas";
    obra->Posicionar(pilaAristas,indice.row());
    if (ultimafila)
    {
        obra->PosicionarAristaActual(indice.row()-1);
    }
    obra->Pegar(listanodos, ultimafila);
}
