#include "editarmediciontextocommand.h"

EditarMedicionTextoCommand::EditarMedicionTextoCommand(Obra *O, MedCertModel *M, QModelIndex I, QVariant V, QString descripcion, QUndoCommand *parent):
    obra(O), modelo (M), valorNuevo(V), QUndoCommand(descripcion,parent)
{
    fila= I.row();
    columna=I.column();
    valorAntiguo=I.data();
    qDebug()<<"Creando objeto undo command, datoAntiguo = "<<valorAntiguo;
}

void EditarMedicionTextoCommand::undo()
{
    qDebug()<<"Undo EditarMedicionTextoCommand con dato: "<<valorAntiguo.toString()<<" en la obra: "<<obra->LeeResumenObra();
    obra->EditarLineaMedicion(fila, columna,0, valorAntiguo.toString());//mando el string y el valor numerico a 0
    modelo->ActualizarDatos();
    modelo->layoutChanged();
}

void EditarMedicionTextoCommand::redo()
{
    qDebug()<<"Redo EditarMedicionTextoCommand con dato: "<<valorNuevo.toString()<<" en la obra: "<<obra->LeeResumenObra();
    obra->EditarLineaMedicion(fila, columna,0, valorNuevo.toString());//mando el string y el valor numerico a 0
    modelo->ActualizarDatos();
    modelo->layoutChanged();
}

