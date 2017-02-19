#include "delegadocolumnasbloqueadas.h"

DelegadoColumnasBloqueadas::DelegadoColumnasBloqueadas(QObject *parent):DelegadoBase(parent)
{

}

void DelegadoColumnasBloqueadas::paint( QPainter *painter,const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
    if (index.isValid())
    {
        //qDebug()<<"Columna del delegado: "<<index.model();
        painter->save();
        painter->setPen(QColor(255,255,170));
        painter->setBrush(QColor(255,255,170));
        //painter->fillRect(option.rect, brush);
        painter->drawRect(option.rect);
        painter->setPen(Qt::gray);
        painter->drawText(option.rect, Qt::AlignCenter, index.data().toString());
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

QString DelegadoColumnasBloqueadas::displayText(const QVariant & value, const QLocale & locale) const
{
    QString str = QString::number(value.toDouble(), 'g', 2);
    return str;
}
