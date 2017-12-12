#include "undoajustarpresupuesto.h"

UndoAjustarPresupuesto::UndoAjustarPresupuesto(Obra *O, float cantidades[])
    :obra(O),cantidadantigua(cantidades[0]),cantidadnueva(cantidades[1])
{

}

void UndoAjustarPresupuesto::redo()
{
    qDebug()<<"Redo ajustar presupuesto de "<<obra->LeeResumenObra()<<"con la cantidad de: "<<cantidadnueva;
    obra->AjustarPrecio(cantidadnueva);
}

void UndoAjustarPresupuesto::undo()
{
    qDebug()<<"Undo ajustar presupuesto de "<<obra->LeeResumenObra()<<"con la cantidad de: "<<cantidadantigua;
    obra->AjustarPrecio(cantidadantigua);
}

