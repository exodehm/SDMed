#include "delegadocolumnasbloqueadas.h"

DelegadoColumnasBloqueadas::DelegadoColumnasBloqueadas(QObject *parent):DelegadoNumerosBase(parent)
{

}

void DelegadoColumnasBloqueadas::paint( QPainter *painter,const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
    if (index.isValid())
    {
        painter->save();
        painter->setPen(QColor(255,255,170));
        painter->setBrush(QColor(255,255,170));
        painter->drawRect(option.rect);
        painter->setPen(Qt::gray);
        painter->drawText(option.rect, Qt::AlignRight | Qt::AlignVCenter, index.data().toString());
        painter->restore();
    }
    else
        QStyledItemDelegate::paint(painter, option, index);
}

QSize DelegadoColumnasBloqueadas::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED (index);
    return option.rect.size();
}
