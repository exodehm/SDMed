#ifndef DELEGADOMEDICIONESESTANDAR_H
#define DELEGADOMEDICIONESESTANDAR_H

#include <QStyledItemDelegate>
#include <QPainter>
#include <QDebug>
#include <QPen>
#include<QBrush>

class DelegadoMedicionesEstandar : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit DelegadoMedicionesEstandar(QObject* parent=nullptr);
    void paint( QPainter *painter,const QStyleOptionViewItem &option, const QModelIndex &index ) const;
    QSize sizeHint( const QStyleOptionViewItem &option, const QModelIndex &index ) const;
};

#endif // DELEGADOMEDICIONESESTANDAR_H
