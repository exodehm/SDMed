#include "delegadomedicionesestandar.h"

DelegadoMedicionesEstandar::DelegadoMedicionesEstandar(QObject *parent):QStyledItemDelegate(parent)
{

}

void DelegadoMedicionesEstandar::paint( QPainter *painter,const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
    QStyledItemDelegate::paint(painter, option, index);
}

QSize DelegadoMedicionesEstandar::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED (index);
    return option.rect.size();
}
