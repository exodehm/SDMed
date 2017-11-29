#include "delegadonumerostablaprincipal.h"

DelegadoNumerosTablaPrincipal::DelegadoNumerosTablaPrincipal(QObject *parent):DelegadoNumerosBase(parent)
{

}

void DelegadoNumerosTablaPrincipal::paint( QPainter *painter,const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
    QAbstractItemModel *model =const_cast<QAbstractItemModel *>(index.model());
    PrincipalModel* modelo = qobject_cast<PrincipalModel*>(model);
    if (index.isValid() && modelo->HayListaDatos())
    {
        QModelIndex indice = index;
        if (modelo->HayFilaVacia())
        {
            if (index.row()>modelo->FilaVacia())
            {
                //qDebug()<<"indice 1: "<<indice.row()<<"--"<<indice.column()<<"--Fila vacia: "<<modelo->FilaVacia();
                indice = modelo->index(index.row()-1,index.column());
            }
        }
        painter->save();
        //qDebug()<<"Indice: "<<indice.row()<<" - "<<indice.column()<<"-"<<indice.data().toString()<<"-"<<modelo->LeeColorS(indice.row(),indice.column());
        painter->setPen(modelo->LeeColor(indice.row()+1,indice.column()));
        painter->drawText(option.rect, Qt::AlignRight | Qt::AlignVCenter,index.data().toString());
        painter->restore();
    }
    else
    {
        DelegadoNumerosBase::paint(painter, option, index);
    }
}

