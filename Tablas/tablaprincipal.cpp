#include "tablaprincipal.h"

TablaPrincipal::TablaPrincipal(int nColumnas, QWidget *parent): TablaBase(nColumnas, parent)
{
    limiteIzquierdo=tipoColumna::NATURALEZA;
    limiteDerecho=tipoColumna::PRCERT;

    celdaBloqueada[tipoColumna::CODIGO]=true;
    celdaBloqueada[tipoColumna::PORCERTPRES]=true;
    celdaBloqueada[tipoColumna::IMPPRES]=true;
    celdaBloqueada[tipoColumna::IMPCERT]=true;
    setItemDelegateForColumn(tipoColumna::CODIGO,dlgCB);
    setItemDelegateForColumn(tipoColumna::PORCERTPRES,dlgCB);
    setItemDelegateForColumn(tipoColumna::IMPPRES,dlgCB);
    setItemDelegateForColumn(tipoColumna::IMPCERT,dlgCB);

    dlgIco= new DelegadoIconos;
    setItemDelegateForColumn(tipoColumna::NATURALEZA,dlgIco);
    cabecera->setSelectionMode(QAbstractItemView::NoSelection);
}

void TablaPrincipal::MostrarMenu(QPoint pos)
{
    int column=this->horizontalHeader()->logicalIndexAt(pos);
    qDebug()<<"Columna: "<<column;

    QMenu *menu=new QMenu(this);
    QAction *AccionBloquearColumna = new QAction("Bloquear columna", this);
    menu->addAction(AccionBloquearColumna);
    mapper->setMapping(AccionBloquearColumna,column);
    QObject::connect(AccionBloquearColumna, SIGNAL(triggered()), mapper, SLOT(map()));
    QObject::connect(mapper, SIGNAL(mapped(int)), this, SLOT(Bloquear(int)));

    menu->popup(this->horizontalHeader()->viewport()->mapToGlobal(pos));

}

