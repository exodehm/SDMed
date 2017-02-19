#include "delegadosparcialessubtotales.h"

DelegadosParcialesSubtotales::DelegadosParcialesSubtotales(QObject *parent):DelegadoEditorNumeros(parent)
{

}

void DelegadosParcialesSubtotales::paint( QPainter *painter,const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
    if (index.isValid())
    {
        //qDebug()<<"Columna del delegado: "<<index.column();
        painter->save();
        painter->setPen(Qt::yellow);
        painter->setBrush(Qt::yellow);
        //painter->fillRect(option.rect, brush);
        painter->drawRect(option.rect);
        painter->setPen(Qt::magenta);
        //painter->drawText(option.rect, Qt::AlignCenter, QString::number(index.data().toDouble(),'f',2));
        QStyledItemDelegate::paint(painter, option, index);
        painter->restore();
    }
    else
        QStyledItemDelegate::paint(painter, option, index);
}

QSize DelegadosParcialesSubtotales::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize( 45, 15);
}
