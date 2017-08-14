#include "tablabase.h"

TablaBase::TablaBase(int nColumnas, QWidget *parent): QTableView(parent)
{
    celdaBloqueada =  new bool[nColumnas];
    for (int i=0;i<nColumnas;i++)
    {
        celdaBloqueada[i]=false;
    }
    cabeceraHorizontal = this->horizontalHeader();
    cabeceraVertical = this->verticalHeader();
    alturaFilas = this->verticalHeader();
    dlgBA = new DelegadoBase;
    dlgCB = new DelegadoColumnasBloqueadas;
    dlgEN = new DelegadoEditorNumeros;
    filtro = new Filter;
    installEventFilter(filtro);
    cabeceraHorizontal->setContextMenuPolicy(Qt::CustomContextMenu);
    cabeceraVertical->setContextMenuPolicy(Qt::CustomContextMenu);
    mapperH = new QSignalMapper(cabeceraHorizontal);
    mapperV = new QSignalMapper(cabeceraVertical);

    resizeColumnsToContents();
    resizeRowsToContents();
    setEditTriggers(QAbstractItemView::SelectedClicked | QAbstractItemView::AnyKeyPressed);

    cabeceraHorizontal->setSectionResizeMode(QHeaderView::Fixed);
    alturaFilas->setDefaultSectionSize(24);
    QObject::connect(cabeceraHorizontal, SIGNAL(customContextMenuRequested(QPoint)), SLOT(MostrarMenuCabecera(QPoint)));
    QObject::connect(cabeceraVertical, SIGNAL(customContextMenuRequested(QPoint)), SLOT(MostrarMenuLateralTabla(QPoint)));
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

void TablaBase::Copiar()
{
    qDebug()<<sender()->parent();
    TablaBase* tabla = qobject_cast<TablaBase*>(sender()->parent());
    if (MedCertModel* mod = qobject_cast<MedCertModel*>(tabla->model()))
    {
        emit CopiarMedicion();
    }
    else if (PrincipalModel* mod = qobject_cast<PrincipalModel*>(tabla->model()))
    {
        emit CopiarPartidas();
    }
}

void TablaBase::Pegar()
{
    qDebug()<<sender()->parent();
    TablaBase* tabla = qobject_cast<TablaBase*>(sender()->parent());
    if (MedCertModel* mod = qobject_cast<MedCertModel*>(tabla->model()))
    {
        emit PegarMedicion();
    }
    else if (PrincipalModel* mod = qobject_cast<PrincipalModel*>(tabla->model()))
    {
        emit PegarPartidas();
    }
}

void TablaBase::Certificar()
{    
    emit CertificarLineasMedicion();
}

QHeaderView* TablaBase::CabeceraDeTabla()
{
    return cabeceraHorizontal;
}
