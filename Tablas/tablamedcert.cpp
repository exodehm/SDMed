#include "tablamedcert.h"

TablaMedCert::TablaMedCert(int nColumnas, QWidget *parent): TablaBase(nColumnas, parent)
{
    dlgME = new DelegadoMedicionesEstandar;
    dlgPS = new DelegadosParcialesSubtotales;

    limiteIzquierdo=tipoColumna::COMENTARIO;
    limiteDerecho=tipoColumna::FORMULA;

    celdaBloqueada[tipoColumna::FASE]=true;
    celdaBloqueada[tipoColumna::PARCIAL]=true;
    celdaBloqueada[tipoColumna::SUBTOTAL]=true;
    celdaBloqueada[tipoColumna::ID]=true;

    setItemDelegateForColumn(tipoColumna::N,dlgEN);
    setItemDelegateForColumn(tipoColumna::COMENTARIO,dlgBA);
    setItemDelegateForColumn(tipoColumna::LONGITUD,dlgEN);
    setItemDelegateForColumn(tipoColumna::ANCHURA,dlgEN);
    setItemDelegateForColumn(tipoColumna::ALTURA,dlgEN);
    setItemDelegateForColumn(tipoColumna::FORMULA,dlgBA);
    setItemDelegateForColumn(tipoColumna::PARCIAL,dlgPS);
    setItemDelegateForColumn(tipoColumna::SUBTOTAL,dlgPS);
    setItemDelegateForColumn(tipoColumna::FASE,dlgCB);
    setItemDelegateForColumn(tipoColumna::ID,dlgCB);

    QObject::connect(cabecera, SIGNAL(sectionClicked(int)), this,SLOT(Bloquear(int)));
}

void TablaMedCert::MostrarMenu(QPoint pos)
{
    int column=this->horizontalHeader()->logicalIndexAt(pos);
    qDebug()<<"Columna: "<<column;

    QMenu *menu=new QMenu(this);
    menu->addAction(new QAction("Hacer algo", this));
    menu->popup(this->horizontalHeader()->viewport()->mapToGlobal(pos));
}
