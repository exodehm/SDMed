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
    dlgNumTablaP = new DelegadoNumerosTablaPrincipal;
    dlgNumTablaMC = new DelegadoNumerosTablaMedCert;
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
            PonerDelegadoOriginal(columna);
        }
        clearSelection();
    }
}

void TablaBase::Copiar()
{
    qDebug()<<sender()->parent();
    TablaBase* tabla = qobject_cast<TablaBase*>(sender()->parent());
    MedCertModel* mod = qobject_cast<MedCertModel*>(tabla->model());//pruebo a castear a modelo de tabla medicion
    if (mod)
    {
        emit CopiarMedicion();
    }
    else
    {
        emit CopiarPartidas();
    }
}

void TablaBase::Pegar()
{
    qDebug()<<sender()->parent();
    TablaBase* tabla = qobject_cast<TablaBase*>(sender()->parent());
    MedCertModel* mod = qobject_cast<MedCertModel*>(tabla->model());//pruebo a castear a modelo de tabla medicion
    if (mod)
    {
        emit PegarMedicion();
    }
    else
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

void TablaBase::PonerDelegadoOriginal(int columna)
{
    if (sender()->parent()->parent()->objectName()=="TablaP")
    {
        if (columna!=tipoColumna::CODIGO && columna!=tipoColumna::UD && columna!=tipoColumna::RESUMEN)
        {
            setItemDelegateForColumn(columna,dlgNumTablaP);
        }
        else
        {
            setItemDelegateForColumn(columna,dlgBA);
        }
    }
    else
    {
        if (columna==tipoColumna::N || columna==tipoColumna::LONGITUD || columna==tipoColumna::ANCHURA || columna==tipoColumna::ALTURA)
        {
            setItemDelegateForColumn(columna,dlgNumTablaMC);
        }
        else
        {
            setItemDelegateForColumn(columna,dlgBA);
        }
    }
}

void TablaBase::BorrarFilas(QList<int>indices)
{
    //llama a la funcion BorrarFilas del modelo de la tabla activa
    MedCertModel* modelo = qobject_cast<MedCertModel*>(model());
    if (modelo)
    {
        modelo->BorrarFilas(indices);
    }
    else
    {
        PrincipalModel* modelo = qobject_cast<PrincipalModel*>(model());
        if (modelo)
        {
            modelo->BorrarFilas(indices);
        }
    }
}
