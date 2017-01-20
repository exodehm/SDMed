#include "tablaprincipal.h"

TablaPrincipal::TablaPrincipal(QWidget *parent) : QTableView(parent)
{
    setEditTriggers(QAbstractItemView::SelectedClicked | QAbstractItemView::AnyKeyPressed);

    cabecera = this->horizontalHeader();
    alturaFilas = this->verticalHeader();

    resizeColumnsToContents();
    resizeRowsToContents();

    alturaFilas->setSectionResizeMode(QHeaderView::Fixed);
    alturaFilas->setDefaultSectionSize(24);

    dlgCB = new DelegadoColumnasBloqueadas;
    setItemDelegateForColumn(tipoColumna::IMPPRES, dlgCB);
    dlgIco =  new DelegadoIconos;
    setItemDelegateForColumn(tipoColumna::NATURALEZA,dlgIco);
}

