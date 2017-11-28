#include "undoeditarprincipal.h"

UndoEditarPrincipal::UndoEditarPrincipal(Obra *O, PrincipalModel *M, QModelIndex I, QVariant D,
                                                 QString descripcion, QUndoCommand *parent):
    obra(O),modelo(M),indice(I),datoNuevo(D), QUndoCommand(descripcion,parent)
{
    datoAntiguo = indice.data() ;
    pilaAristas = obra->LeePilaAristas();
    setText(descripcion);
}

void UndoEditarPrincipal::undo()
{
    qDebug()<<"Undo en clase base";

}

void UndoEditarPrincipal::redo()
{
    qDebug()<<"Redo en clase base";
}

void UndoEditarPrincipal::Posicionar()
{
    obra->DefinePilaAristas(pilaAristas);
    obra->DefineAristaPadre(pilaAristas.top());
    pArista aux = pilaAristas.top();
    obra->DefineNodoPadre(aux->destino);
    //modelo->QuitarIndicadorFilaVacia();
    obra->PosicionarAristaActual(indice.row());
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
    Posicionar();
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
    Posicionar();
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
    Posicionar();
    obra->EditarNaturaleza(datoAntiguo.toInt());    
}

void UndoEditarNaturaleza::redo()
{
    qDebug()<<"RedoEditarNaturaleza";
    Posicionar();
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
    Posicionar();    
    obra->EditarUnidad(datoAntiguo.toString());   
}

void UndoEditarUnidad::redo()
{
    qDebug()<<"RedoEditarUnidad";
    Posicionar();
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
    Posicionar();    
    obra->EditarResumen(datoAntiguo.toString());
}

void UndoEditarResumen::redo()
{
    qDebug()<<"RedoEditarResumen";
    Posicionar();    
    obra->EditarResumen(datoNuevo.toString());
}


//#############################CANTIDAD#############################//

UndoEditarCantidad::UndoEditarCantidad(Obra* O, PrincipalModel* M,  QModelIndex I, QVariant D, QString descripcion, QUndoCommand* parent):
    UndoEditarPrincipal(O,M,I,D,descripcion,parent)
{    
    cantidadAntigua = obra->LeeTotalMedicion(MedCert::MEDICION);
    cantidadNueva = datoNuevo.toFloat();
}

void UndoEditarCantidad::undo()
{
    qDebug()<<"UndoEditarCantidad con datoAntiguo: "<<cantidadAntigua<<" y datonuevo: "<<cantidadNueva;
    Posicionar();    
    if (ListaMedicion.hayMedicion())
    {
        obra->EditarCantidad(0);//pongo a 0 el valor
        obra->PegarMedicion(0,ListaMedicion,obra->AristaActual());
    }
    else
    {
        obra->EditarCantidad(cantidadAntigua);
    }   
}

void UndoEditarCantidad::redo()
{
    qDebug()<<"RedoEditarCantidad con datoNuevo: "<<cantidadNueva<<" y datoAntiguo: "<<cantidadAntigua;
    //guardo la medicion
    Posicionar();
    ListaMedicion = obra->LeeListaMedicion(MedCert::MEDICION);//habra que arreglarlo para que trabaje sobre la certificacion
    obra->EditarCantidad(cantidadNueva);
}

//#############################PRECIO#############################//

UndoEditarPrecio::UndoEditarPrecio(Obra* O, PrincipalModel* M,  QModelIndex I, QVariant D, int A, QString descripcion, QUndoCommand* parent):
    UndoEditarPrincipal(O,M,I,D,descripcion,parent)
{
    accion = A;
    precioAntiguo=obra->LeePrecio();
    precioNuevo=datoNuevo.toFloat();
}

void UndoEditarPrecio::undo()
{
    qDebug()<<"UndoEditarPrecio";
    Posicionar();
    switch (accion)
    {
    case precio::MODIFICAR:
        qDebug()<<"modificar undo";
        obra->EditarPrecio(precioAntiguo);
        break;
    case precio::SUPRIMIR:
    {
        qDebug()<<"suprimir undo";
        obra->BajarNivel();
        obra->Pegar(grafoaux);
        obra->SubirNivel();
        break;
    }
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
    Posicionar();
    switch (accion) {
    case precio::MODIFICAR:
        qDebug()<<"modificar undo";
        obra->EditarPrecio(precioNuevo);
        break;
    case precio::SUPRIMIR:
    {
        qDebug()<<"suprimir undo";
        qDebug()<<obra->AristaActual()->destino->datonodo.LeeCodigo();
        grafoaux = obra->GrafoAPartirDeNodo(obra->AristaActual()->destino);
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
    Posicionar();
    obra->EditarTexto(textoantiguo);
}

void UndoEditarTexto::redo()
{
    //qDebug()<<"Redo EditarTextoPartida: "<<textonuevo<<"--"<<textoantiguo;
    Posicionar();
    obra->EditarTexto(textonuevo);
}
