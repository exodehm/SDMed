#include "delegadosparcialessubtotales.h"

DelegadosParcialesSubtotales::DelegadosParcialesSubtotales(QObject *parent):DelegadoEditorNumeros(parent)
{

}

void DelegadosParcialesSubtotales::paint( QPainter *painter,const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
    if (index.isValid())
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
        DelegadoEditorNumeros::paint(painter, option, index);
}

QSize DelegadosParcialesSubtotales::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize(45, 15);
}
