#include "tablaprincipal.h"

TablaPrincipal::TablaPrincipal(int nColumnas, QWidget *parent): TablaBase(nColumnas, parent)
{
    limiteIzquierdo=tipoColumna::CODIGO;
    limiteDerecho=tipoColumna::PRCERT;

    celdaBloqueada[tipoColumna::CODIGO]=true;
    celdaBloqueada[tipoColumna::PORCERTPRES]=true;
    celdaBloqueada[tipoColumna::IMPPRES]=true;
    celdaBloqueada[tipoColumna::IMPCERT]=true;
    //setItemDelegateForColumn(tipoColumna::CODIGO,dlgCB);
    setItemDelegateForColumn(tipoColumna::CODIGO,dlgBA);
    setItemDelegateForColumn(tipoColumna::UD,dlgBA);
    setItemDelegateForColumn(tipoColumna::RESUMEN,dlgBA);
    setItemDelegateForColumn(tipoColumna::CANPRES,dlgEN);
    setItemDelegateForColumn(tipoColumna::PRPRES,dlgEN);
    setItemDelegateForColumn(tipoColumna::PORCERTPRES,dlgEN);
    setItemDelegateForColumn(tipoColumna::IMPPRES,dlgCB);
    setItemDelegateForColumn(tipoColumna::IMPCERT,dlgCB);

    dlgIco= new DelegadoIconos;
    setItemDelegateForColumn(tipoColumna::NATURALEZA,dlgIco);
    cabeceraHorizontal->setSelectionMode(QAbstractItemView::NoSelection);
}

void TablaPrincipal::MostrarMenuCabecera(QPoint pos)
{
    int column=this->horizontalHeader()->logicalIndexAt(pos);
    qDebug()<<"Columna: "<<column;

    QMenu *menu=new QMenu(this);
    QAction *AccionBloquearColumna = new QAction("Bloquear columna", this);
    menu->addAction(AccionBloquearColumna);
    mapperH->setMapping(AccionBloquearColumna,column);
    QObject::connect(AccionBloquearColumna, SIGNAL(triggered()), mapperH, SLOT(map()));
    QObject::connect(mapperH, SIGNAL(mapped(int)), this, SLOT(Bloquear(int)));

    menu->popup(this->horizontalHeader()->viewport()->mapToGlobal(pos));
}

void TablaPrincipal::MostrarMenuLateralTabla(QPoint pos)
{
    QMenu *menu=new QMenu(this);
    QAction *AccionCopiar = new QAction("Copiar lineas de medición", this);
    menu->addAction(AccionCopiar);
    /*copiar*/
    QObject::connect(AccionCopiar, SIGNAL(triggered()), this, SLOT(Copiar()));
    menu->popup(cabeceraVertical->viewport()->mapToGlobal(pos));
}
