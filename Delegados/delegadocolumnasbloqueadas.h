#ifndef DELEGADOCOLUMNASBLOQUEADAS_H
#define DELEGADOCOLUMNASBLOQUEADAS_H

#include <QPainter>
#include <QDebug>
#include <QPen>
#include<QBrush>

#include "./Delegados/delegadobase.h"

class DelegadoColumnasBloqueadas : public DelegadoBase
{
    Q_OBJECT
public:
    explicit DelegadoColumnasBloqueadas(QObject* parent=nullptr);
    void paint( QPainter *painter,const QStyleOptionViewItem &option, const QModelIndex &index ) const;
    QSize sizeHint( const QStyleOptionViewItem &option, const QModelIndex &index ) const;

    QString displayText(const QVariant & value, const QLocale & locale ) const;
};

#endif // DELEGADOCOLUMNASBLOQUEADAS_H
