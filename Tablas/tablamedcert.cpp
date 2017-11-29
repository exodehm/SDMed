#include "tablamedcert.h"

TablaMedCert::TablaMedCert(int nColumnas, QWidget *parent): TablaBase(nColumnas, parent)
{    
    limiteIzquierdo=tipoColumna::COMENTARIO;
    limiteDerecho=tipoColumna::PARCIAL;

    celdaBloqueada[tipoColumna::FASE]=true;
    celdaBloqueada[tipoColumna::PARCIAL]=true;
    celdaBloqueada[tipoColumna::SUBTOTAL]=true;
    celdaBloqueada[tipoColumna::ID]=true;

    setItemDelegateForColumn(tipoColumna::N,dlgNumTablaMC);
    setItemDelegateForColumn(tipoColumna::COMENTARIO,dlgBA);
    setItemDelegateForColumn(tipoColumna::LONGITUD,dlgNumTablaMC);
    setItemDelegateForColumn(tipoColumna::ANCHURA,dlgNumTablaMC);
    setItemDelegateForColumn(tipoColumna::ALTURA,dlgNumTablaMC);
    setItemDelegateForColumn(tipoColumna::FORMULA,dlgBA);
    setItemDelegateForColumn(tipoColumna::PARCIAL,dlgNumTablaMC);
    setItemDelegateForColumn(tipoColumna::SUBTOTAL,dlgNumTablaMC);
    setItemDelegateForColumn(tipoColumna::FASE,dlgCB);
    setItemDelegateForColumn(tipoColumna::ID,dlgCB);

    QObject::connect(cabeceraHorizontal, SIGNAL(sectionClicked(int)), this,SLOT(Bloquear(int)));
}

void TablaMedCert::MostrarMenuCabecera(QPoint pos)
{
    int column=this->horizontalHeader()->logicalIndexAt(pos);
    qDebug()<<"Columna: "<<column;

    QMenu *menu=new QMenu(this);
    menu->addAction(new QAction("Hacer algo", this));
    menu->popup(this->horizontalHeader()->viewport()->mapToGlobal(pos));
}

void TablaMedCert::MostrarMenuLateralTabla(QPoint pos)
{
    QMenu *menu=new QMenu(this);
    QAction *AccionCopiar = new QAction(tr("Copiar lineas de medición"), this);
    QAction *AccionPegar = new QAction(tr("Pegar lineas de medición"), this);
    QAction *AccionCertificar = new QAction(tr("Certificar lineas de medición"), this);
    QModelIndexList indexes = this->selectionModel()->selectedIndexes();
    if (indexes.size()==0)
    {
        AccionCopiar->setEnabled(false);
        AccionCertificar->setEnabled(false);
    }
    menu->addAction(AccionCopiar);
    menu->addAction(AccionPegar);
    menu->addAction(AccionCertificar);
    /*copiar*/
    QObject::connect(AccionCopiar, SIGNAL(triggered()), this, SLOT(Copiar()));
    /*pegar*/
    QObject::connect(AccionPegar, SIGNAL(triggered()), this, SLOT(Pegar()));
    /*certificar*/
    QObject::connect(AccionCertificar, SIGNAL(triggered()), this, SLOT(Certificar()));
    menu->popup(cabeceraVertical->viewport()->mapToGlobal(pos));
}
