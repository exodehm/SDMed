#include "undoeditarcantidad.h"

UndoEditarCantidad::UndoEditarCantidad(Obra* O, PrincipalModel* M,  QModelIndex I, float D, QString descripcion, QUndoCommand* parent):
    obra(O),modelo(M),indice(I),cantidadNueva(D),QUndoCommand(descripcion,parent)
{
    cantidadAntigua = indice.data().toFloat() ;
    A=obra->AristaActual();
    setText(descripcion);
}

void UndoEditarCantidad::undo()
{
    qDebug()<<"UndoEditarCantidad";
    if (ListaMedicion.hayMedicion())
    {
        obra->EditarCantidad(0);
        obra->PegarMedicion(0,ListaMedicion,A);
    }
    else
    {
        obra->EditarCantidad(cantidadAntigua);
    }
    modelo->emitDataChanged(indice);
    modelo->ActualizarDatos();
    modelo->layoutChanged();
}

void UndoEditarCantidad::redo()
{
    qDebug()<<"RedoEditarCantidad";
    //guardo la medicion
    ListaMedicion = obra->LeeListaMedicion(0);
    obra->EditarCantidad(cantidadNueva);
    modelo->emitDataChanged(indice);
    modelo->ActualizarDatos();
    modelo->layoutChanged();

}
