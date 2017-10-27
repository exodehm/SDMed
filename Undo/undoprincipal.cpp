#include "undoprincipal.h"

UndoPrincipal::UndoPrincipal(Obra *O, PrincipalModel *M, QModelIndex I, QVariant D,
                             QString descripcion, QUndoCommand *parent):
    obra(O),modelo(M),indice(I),datoNuevo(D),QUndoCommand(descripcion,parent)
{
    datoAntiguo = indice.data() ;
    fila= indice.row();
    columna=indice.column();
    setText(descripcion);
}


void UndoPrincipal::undo()
{
    qDebug()<<"Undo tabla principal";
    switch (columna)
    {
    case tipoColumna::CODIGO:
        qDebug()<<"editando código";
        obra->EditarCodigo(datoAntiguo.toString());
        break;
    case tipoColumna::NATURALEZA:
        qDebug()<<"editando naturaleza";
        obra->EditarNaturaleza(datoAntiguo.toInt());
        break;
    case tipoColumna::UD:
        qDebug()<<"editando unidad";
        obra->EditarUnidad(datoAntiguo.toString());
        break;
    case tipoColumna::RESUMEN:
        qDebug()<<"editando resumen";
        obra->EditarResumen(datoAntiguo.toString());
        break;
    case tipoColumna::CANPRES:
        qDebug()<<"editando cantidad";
        obra->EditarCantidad(datoAntiguo.toFloat());
        break;
    case tipoColumna::PRPRES:
        qDebug()<<"editando precio";
        modelo->EditarPrecio(indice, datoAntiguo.toFloat());
        break;
    default:
        break;
    }
    modelo->emitDataChanged(indice);
}

void UndoPrincipal::redo()
{
    qDebug()<<"Redo tabla principal";
    switch (columna)
    {
    case tipoColumna::CODIGO:
        qDebug()<<"editando código";
        obra->EditarCodigo(datoNuevo.toString());
        break;
    case tipoColumna::NATURALEZA:
        qDebug()<<"editando naturaleza";
        obra->EditarNaturaleza(datoNuevo.toInt());
        break;
    case tipoColumna::UD:
        qDebug()<<"editando unidad";
        obra->EditarUnidad(datoNuevo.toString());
        break;
    case tipoColumna::RESUMEN:
        qDebug()<<"editando resumen";
        obra->EditarResumen(datoNuevo.toString());
        break;
    case tipoColumna::CANPRES:
        qDebug()<<"editando cantidad";
        obra->EditarCantidad(datoNuevo.toFloat());
        break;
    case tipoColumna::PRPRES:        
        if (modelo->EditarPrecio(indice, datoNuevo.toFloat()))
        {
            qDebug()<<"editando precio";
        }
        break;
    default:
        break;
    }
    modelo->emitDataChanged(indice);
}
