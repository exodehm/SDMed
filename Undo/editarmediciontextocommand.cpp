#include "editarmediciontextocommand.h"

EditarMedicionTextoCommand::EditarMedicionTextoCommand(QString descripcion, QUndoCommand *parent):QUndoCommand(descripcion,parent)
{
    qDebug()<<"Creando objeto undo command";
}

void EditarMedicionTextoCommand::undo()
{
    qDebug()<<"Undo EditarMedicionTextoCommand";
}

void EditarMedicionTextoCommand::redo()
{
    qDebug()<<"Redo EditarMedicionTextoCommand";
}
