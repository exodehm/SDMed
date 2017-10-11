#include "editarmedicionnumerocommand.h"


EditarMedicionNumeroCommand::EditarMedicionNumeroCommand(Obra *O, MedCertModel *M, QModelIndex I, QVariant V, QString descripcion, QUndoCommand *parent):
    obra(O), modelo (M), indice(I), valorNuevo(V), QUndoCommand(descripcion,parent)
{
    fila= indice.row();
    columna=indice.column();
    valorAntiguo=indice.data();
    qDebug()<<"Creando objeto undo command, datoAntiguo = "<<valorAntiguo;
}

void EditarMedicionNumeroCommand::undo()
{
    qDebug()<<"Undo EditarMedicionTextoCommand con dato: "<<valorAntiguo.toDouble()<<" en la obra: "<<obra->LeeResumenObra();
    obra->EditarLineaMedicion(fila, columna,valorAntiguo.toDouble(),"");//mando el valor numerico y el string vacío
    modelo->ActualizarDatos();
    modelo->layoutChanged();
    modelo->emitDataChanged(indice);
}

void EditarMedicionNumeroCommand::redo()
{
    qDebug()<<"Redo EditarMedicionTextoCommand con dato: "<<valorNuevo.toDouble()<<" en la obra: "<<obra->LeeResumenObra();
    obra->EditarLineaMedicion(fila, columna,valorNuevo.toDouble(),"");//mando el valor numerico y el string vacío
    modelo->ActualizarDatos();
    modelo->layoutChanged();
    modelo->emitDataChanged(indice);
}
