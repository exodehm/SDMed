#include "tablaprincipal.h"

TablaPrincipal::TablaPrincipal(QWidget *parent) : QTableView(parent)
{
    for (int i=0;i<9;i++)
    {
        celdaBloqueada[0]=false;
    }
    celdaBloqueada[9]=true;
    celdaBloqueada[10]=true;


    setEditTriggers(QAbstractItemView::SelectedClicked | QAbstractItemView::AnyKeyPressed);

    cabecera = this->horizontalHeader();
    alturaFilas = this->verticalHeader();

    resizeColumnsToContents();
    resizeRowsToContents();

    alturaFilas->setSectionResizeMode(QHeaderView::Fixed);
    alturaFilas->setDefaultSectionSize(24);

    dlgIco =  new DelegadoIconos;
    setItemDelegateForColumn(tipoColumna::NATURALEZA,dlgIco);

    dlgCB = new DelegadoColumnasBloqueadas;
    dlgEM = new DelegadoEditorMediciones;
    setItemDelegateForColumn(tipoColumna::IMPPRES, dlgCB);
    setItemDelegateForColumn(tipoColumna::IMPCERT, dlgCB);

    installEventFilter(this);
    //QObject::connect(cabecera, SIGNAL(sectionClicked(int)), this,SLOT(Bloquear(int)));
}

void TablaPrincipal::Bloquear(int columna)
{
    if (columna>tipoColumna::FASE && columna<tipoColumna::PARCIAL)
    {
        celdaBloqueada[columna]=!celdaBloqueada[columna];
        if (columnaBloqueada(columna))
        {
            setItemDelegateForColumn(columna,dlgCB);
        }
        else
        {
            setItemDelegateForColumn(columna,dlgEM);
        }
        clearSelection();
    }
}

bool TablaPrincipal::columnaBloqueada(int columna)
{
    return celdaBloqueada[columna];
}

bool TablaPrincipal::eventFilter(QObject *watched, QEvent *e)
{
    return QWidget::eventFilter(watched, e);
}

