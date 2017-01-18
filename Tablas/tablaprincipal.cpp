#include "tablaprincipal.h"

TablaPrincipal::TablaPrincipal(QWidget *parent) : QTableView(parent)
{
    setAlternatingRowColors(true);
    setEditTriggers(QAbstractItemView::SelectedClicked | QAbstractItemView::AnyKeyPressed);
}

