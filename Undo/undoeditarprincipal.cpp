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
    modelo->QuitarIndicadorFilaVacia();
    obra->PosicionarAristaActual(indice.row());
}

//#############################CODIGO#############################//
UndoEditarCodigo::UndoEditarCodigo(Obra* O, PrincipalModel* M,  QModelIndex I, QVariant D, QString descripcion, QUndoCommand* parent):
    UndoEditarPrincipal(O,M,I,D,descripcion,parent)
{
    accion = codigo::NADA;

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
    modelo->emitDataChanged(indice);
    //modelo->QuitarIndicadorFilaVacia();
    modelo->ActualizarDatos(obra->LeeDescompuesto());
    modelo->layoutChanged();
}

void UndoEditarCodigo::redo()
{
    qDebug()<<"RedoEditarCodigo";
    obra->PosicionarAristaActual(indice.row());
    if ((indice.row()==modelo->FilaVacia() && modelo->HayFilaVacia()) || accion==codigo::NUEVO)//insertar partida nueva
    {
        qDebug()<<"Insertando codigo en la fila "<<indice.row();
        accion = codigo::NUEVO;
        obra->PosicionarAristaActual(indice.row());
        obra->CrearPartida(datoNuevo.toString(),modelo->FilaVacia());
    }
    else
    {
        qDebug()<<"EDITAR codigo en la fila "<<indice.row();
        accion = codigo::CAMBIAR;
        obra->EditarCodigo(datoNuevo.toString());
    }
    modelo->emitDataChanged(indice);
    modelo->QuitarIndicadorFilaVacia();
    modelo->ActualizarDatos(obra->LeeDescompuesto());
    modelo->layoutChanged();
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
    modelo->QuitarIndicadorFilaVacia();
    modelo->emitDataChanged(indice);
    //modelo->ActualizarDatos();
    modelo->layoutChanged();
}

void UndoEditarResumen::redo()
{
    qDebug()<<"RedoEditarResumen";
    obra->PosicionarAristaActual(indice.row());
    obra->EditarResumen(datoNuevo.toString());
    modelo->emitDataChanged(indice);
    //modelo->ActualizarDatos();
    modelo->layoutChanged();
}


//#############################CANTIDAD#############################//

UndoEditarCantidad::UndoEditarCantidad(Obra* O, PrincipalModel* M,  QModelIndex I, QVariant D, QString descripcion, QUndoCommand* parent):
    UndoEditarPrincipal(O,M,I,D,descripcion,parent)
{

}

void UndoEditarCantidad::undo()
{
    qDebug()<<"UndoEditarCantidad";
    Posicionar();
    if (ListaMedicion.hayMedicion())
    {
        obra->EditarCantidad(0);//pongo a 0 el valor
        obra->PegarMedicion(0,ListaMedicion,obra->AristaActual());
    }
    else
    {
        obra->EditarCantidad(datoAntiguo.toFloat());
    }
    modelo->emitDataChanged(indice);
    modelo->ActualizarDatos(obra->LeeDescompuesto());
    modelo->layoutChanged();
}

void UndoEditarCantidad::redo()
{
    qDebug()<<"RedoEditarCantidad";
    //guardo la medicion
    ListaMedicion = obra->LeeListaMedicion(MedCert::MEDICION);//habra que arreglarlo para que trabaje sobre la certificacion
    obra->PosicionarAristaActual(indice.row());
    obra->EditarCantidad(datoNuevo.toFloat());
    modelo->emitDataChanged(indice);
    modelo->ActualizarDatos(obra->LeeDescompuesto());
    modelo->layoutChanged();
}

//#############################PRECIO#############################//

UndoEditarPrecio::UndoEditarPrecio(Obra* O, PrincipalModel* M,  QModelIndex I, QVariant D, int A, QString descripcion, QUndoCommand* parent):
    UndoEditarPrincipal(O,M,I,D,descripcion,parent)
{
    accion = A;
}

void UndoEditarPrecio::undo()
{
    qDebug()<<"UndoEditarPrecio";
    Posicionar();
    switch (accion)
    {
    case precio::MODIFICAR:
        qDebug()<<"modificar undo";
        obra->EditarPrecio(datoAntiguo.toFloat());
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
    modelo->emitDataChanged(indice);
    modelo->ActualizarDatos(obra->LeeDescompuesto());
    modelo->layoutChanged();
}

void UndoEditarPrecio::redo()
{
    qDebug()<<"RedoEditarPrecio";
    obra->PosicionarAristaActual(indice.row());
    switch (accion) {
    case precio::MODIFICAR:
        qDebug()<<"modificar undo";
        obra->EditarPrecio(datoNuevo.toFloat());
        break;
    case precio::SUPRIMIR:
    {
        qDebug()<<"suprimir undo";
        qDebug()<<obra->AristaActual()->destino->datonodo.LeeCodigo();
        grafoaux = obra->GrafoAPartirDeNodo(obra->AristaActual()->destino);
        obra->SuprimirDescomposicion();
        obra->EditarPrecio(datoNuevo.toFloat());
        break;
    }
    case precio::BLOQUEAR:
        qDebug()<<"bloquear undo";
        obra->BloquearPrecio(datoNuevo.toFloat());
        break;
    case precio::AJUSTAR:
        qDebug()<<"Ajustar undo";
        break;
    default:
        break;
    }
    modelo->emitDataChanged(indice);
    modelo->ActualizarDatos(obra->LeeDescompuesto());
    modelo->layoutChanged();
}
