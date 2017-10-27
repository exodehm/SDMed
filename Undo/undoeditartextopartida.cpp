#include "undoeditartextopartida.h"

UndoEditarTextoPartida::UndoEditarTextoPartida(Obra *O, QString descripcion, QUndoCommand *parent):
    obra(O), QUndoCommand(descripcion,parent)
{
    setText(text());
}

void UndoEditarTextoPartida::undo()
{
    qDebug()<<"Undo UndoEditarTextoPartida";
}

void UndoEditarTextoPartida::redo()
{
    qDebug()<<"Redo UndoEditarTextoPartida";
}


