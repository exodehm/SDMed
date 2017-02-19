#include "tablabase.h"

TablaBase::TablaBase(int nColumnas, QWidget *parent): QTableView(parent)
{
    celdaBloqueada =  new bool[nColumnas];
    for (int i=0;i<nColumnas;i++)
    {
        celdaBloqueada[i]=false;
    }
    cabecera = this->horizontalHeader();
    alturaFilas = this->verticalHeader();
    dlgBA = new DelegadoBase;
    dlgCB = new DelegadoColumnasBloqueadas;
    dlgEN = new DelegadoEditorNumeros;
    filtro = new Filter;
    installEventFilter(filtro);
    cabecera->setContextMenuPolicy(Qt::CustomContextMenu);
    mapper =  new QSignalMapper(cabecera);

    resizeColumnsToContents();
    resizeRowsToContents();
    setEditTriggers(QAbstractItemView::SelectedClicked | QAbstractItemView::AnyKeyPressed);

    cabecera->setSectionResizeMode(QHeaderView::Fixed);
    //cabecera->setDefaultSectionSize(24);
    alturaFilas->setDefaultSectionSize(24);
    QObject::connect(cabecera, SIGNAL(customContextMenuRequested(QPoint)), SLOT(customMenuRequested(QPoint)));
}

TablaBase::~TablaBase()
{

}

bool TablaBase::columnaBloqueada(int columna)
{
    return celdaBloqueada[columna];
}

void TablaBase::Bloquear(int columna)
{
    if (columna>=limiteIzquierdo && columna<=limiteDerecho)
    {
        celdaBloqueada[columna]=!celdaBloqueada[columna];
        if (columnaBloqueada(columna))
        {
            setItemDelegateForColumn(columna,dlgCB);
        }
        else
        {
            setItemDelegateForColumn(columna,dlgEN);
        }
        clearSelection();
    }
}

void TablaBase::customMenuRequested(QPoint pos)
{
    MostrarMenu(pos);
}

QHeaderView* TablaBase::CabeceraDeTabla()
{
    return cabecera;
}
