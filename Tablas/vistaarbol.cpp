#include "vistaarbol.h"

VistaArbol::VistaArbol(QWidget *parent):QTreeView(parent)
{
    delegado = new DelegadoArbol;
    setItemDelegateForColumn(tipoColumna::CODIGO,delegado);
    setItemDelegateForColumn(tipoColumna::RESUMEN,delegado);
    setColumnWidth(tipoColumna::NATURALEZA,10);
    setColumnWidth(tipoColumna::CODIGO,10);
    //setItemDelegate(delegado);
}

