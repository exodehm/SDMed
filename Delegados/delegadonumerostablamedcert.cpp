#include "delegadonumerostablamedcert.h"

DelegadoNumerosTablaMedCert::DelegadoNumerosTablaMedCert(QObject* parent):DelegadoNumerosBase(parent)
{

}

void DelegadoNumerosTablaMedCert::paint( QPainter *painter,const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
    /*QAbstractItemModel *model =const_cast<QAbstractItemModel *>(index.model());
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
    }*/
    if (index.isValid())
    {
        if (index.column()==tipoColumna::PARCIAL || index.column()==tipoColumna::SUBTOTAL)
        {
            painter->save();
            painter->setPen(Qt::yellow);
            painter->setBrush(Qt::yellow);
            painter->drawRect(option.rect);
            painter->setPen(Qt::magenta);
            painter->drawText(option.rect, Qt::AlignCenter, displayText(index.data(), QLocale::system()));
            painter->restore();
        }
        else
        {
            painter->drawText(option.rect, Qt::AlignCenter, displayText(index.data(), QLocale::system()));
        }
    }
    else
    {
        DelegadoNumerosBase::paint(painter, option, index);
    }
}

