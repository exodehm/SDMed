#include "undomedicion.h"

UndoMedicion::UndoMedicion(Obra* O, MedCertModel* M,  QModelIndex indiceAnterior, QModelIndex indiceActual,
                           QVariant dato, QString descripcion, QUndoCommand* parent):
    QUndoCommand(descripcion,parent),obra(O),modelo(M), datoNuevo(dato),indiceAnterior(indiceAnterior)
{

    indiceActual = indiceActual;
    fila = indiceActual.row();
    columna = indiceActual.column();
    datoAntiguo = indiceActual.data();
    if (indiceActual.column()==tipoColumna::COMENTARIO || indiceActual.column()==tipoColumna::FORMULA)
    {
        fValorAntiguo=0;
        fValorNuevo=0;
        sValorNuevo=datoNuevo.toString();
        sValorAntiguo=datoAntiguo.toString();

    }
    else if (indiceActual.column()==tipoColumna::N || indiceActual.column()==tipoColumna::LONGITUD || indiceActual.column()==tipoColumna::ANCHURA || indiceActual.column()==tipoColumna::ALTURA)
    {
        fValorNuevo=datoNuevo.toFloat();
        fValorAntiguo=datoAntiguo.toFloat();
        sValorNuevo="";
        sValorAntiguo="";
    }

    /*if (columna == 0 && fila == modelo->lineavacia && modelo->haylineavacia)
    {
        esNuevoDato = true;
        qDebug()<<"ES NUEVO DATO";
    }
    else
    {
        esNuevoDato = false;
    }*/
    setText(text());
    qDebug()<<"valor antiguo:"<<datoAntiguo.toString()<<"- valor nuevo: "<<datoNuevo.toString();

}

void UndoMedicion::undo()
{
    qDebug()<<"Undo EditarMedicion con dato: "<<datoAntiguo.toString()<<" en la obra: "<<obra->LeeResumenObra();
    obra->EditarLineaMedicion(fila, columna,fValorAntiguo, sValorAntiguo);
    modelo->emitDataChanged(indiceActual);
    modelo->ActualizarDatos();
    modelo->layoutChanged();
    //emit modelo->Posicionar(indiceAnterior);

}

void UndoMedicion::redo()
{
    qDebug()<<"Redo EditarMedicion con dato: "<<datoNuevo.toString()<<" en la obra: "<<obra->LeeResumenObra();
    obra->EditarLineaMedicion(fila, columna,fValorNuevo, sValorNuevo);
    modelo->emitDataChanged(indiceActual);
    modelo->ActualizarDatos();
    modelo->layoutChanged();
    //emit modelo->Posicionar(indiceActual);
}

int UndoMedicion::LeeFila() const
{
    return fila;

}
int UndoMedicion::LeeColumna() const
{
    return columna;
}
