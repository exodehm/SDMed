#ifndef DELEGADOCOLUMNASBLOQUEADAS_H
#define DELEGADOCOLUMNASBLOQUEADAS_H

#include <QPainter>
#include <QDebug>
#include <QPen>
#include <QBrush>

#include  "../Delegados/delegadonumerosbase.h"

class DelegadoColumnasBloqueadas : public DelegadoNumerosBase
{
    Q_OBJECT
public:
    explicit DelegadoColumnasBloqueadas(QObject* parent=nullptr);
    void paint( QPainter *painter,const QStyleOptionViewItem &option, const QModelIndex &index ) const;
    QSize sizeHint( const QStyleOptionViewItem &option, const QModelIndex &index ) const;    
};

#endif // DELEGADOCOLUMNASBLOQUEADAS_H
