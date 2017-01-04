#ifndef DELEGADOSPARCIALESSUBTOTALES_H
#define DELEGADOSPARCIALESSUBTOTALES_H

#include <QStyledItemDelegate>
#include <QPainter>
#include <QDebug>
#include <QPen>
#include<QBrush>

class DelegadosParcialesSubtotales : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit DelegadosParcialesSubtotales(QObject* parent=nullptr);
    void paint( QPainter *painter,const QStyleOptionViewItem &option, const QModelIndex &index ) const;
    QSize sizeHint( const QStyleOptionViewItem &option, const QModelIndex &index ) const;

private:

};

#endif // DELEGADOSPARCIALESSUBTOTALES_H
