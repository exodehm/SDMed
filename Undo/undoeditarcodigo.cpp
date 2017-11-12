#include "undoeditarcodigo.h"

UndoEditarCodigo::UndoEditarCodigo(Obra* O, PrincipalModel* M,  QModelIndex I, QString T, QString descripcion, QUndoCommand* parent):
    obra(O),modelo(M),indice(I),codigoNuevo(T), QUndoCommand(descripcion,parent)
{
    codigoAntiguo = indice.data().toString();
    fila= indice.row();
    columna=indice.column();
    setText(descripcion);
}

void UndoEditarCodigo::undo()
{
    qDebug()<<"UndoEditarCodigo";
    switch (accion)
    {
    case codigo::NUEVO:
        qDebug()<<"Borrando el codigo y la partida";
        modelo->removeRow(fila);
        break;
    case codigo::CAMBIAR:
        obra->EditarCodigo(codigoAntiguo);
        break;
    default:
        break;
    }
    modelo->emitDataChanged(indice);
    //modelo->QuitarIndicadorFilaVacia();
    modelo->ActualizarDatos();
    modelo->layoutChanged();
}

void UndoEditarCodigo::redo()
{
    qDebug()<<"RedoEditarCodigo";
    if (indice.row()==modelo->FilaVacia() && modelo->HayFilaVacia() || accion==codigo::NUEVO)//insertar partida nueva
    {
        qDebug()<<"Insertando codigo en la fila "<<indice.row();
        accion = codigo::NUEVO;
        obra->PosicionarAristaActual(fila);
        obra->CrearPartida(codigoNuevo,modelo->FilaVacia());        
    }
    else
    {
        accion = codigo::CAMBIAR;
        obra->EditarCodigo(codigoNuevo);
    }    
    modelo->emitDataChanged(indice);
    modelo->QuitarIndicadorFilaVacia();
    modelo->ActualizarDatos();
    modelo->layoutChanged();
}
