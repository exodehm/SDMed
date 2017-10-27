#include "undoeditarresumen.h"

UndoEditarResumen::UndoEditarResumen(Obra* O, PrincipalModel* M,  QModelIndex I, QString T, QString descripcion, QUndoCommand* parent):
    obra(O),modelo(M),indice(I),resumenNuevo(T), QUndoCommand(descripcion,parent)
{
    resumenAntiguo = indice.data().toString();
    fila= indice.row();
    columna=indice.column();
    setText(descripcion);
}

void UndoEditarResumen::undo()
{
    qDebug()<<"UndoEditarResumen";
    obra->EditarResumen(resumenAntiguo);
    modelo->emitDataChanged(indice);
    //modelo->ActualizarDatos();
    modelo->layoutChanged();
}

void UndoEditarResumen::redo()
{
    qDebug()<<"RedoEditarResumen";
    obra->EditarResumen(resumenNuevo);
    modelo->emitDataChanged(indice);
    //modelo->ActualizarDatos();
    modelo->layoutChanged();
}
