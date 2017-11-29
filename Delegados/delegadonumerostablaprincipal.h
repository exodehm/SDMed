#ifndef DELEGADONUMEROSTABLAPRINCIPAL_H
#define DELEGADONUMEROSTABLAPRINCIPAL_H

#include "./Delegados/delegadonumerosbase.h"


class DelegadoNumerosTablaPrincipal : public DelegadoNumerosBase
{
public:    
    explicit DelegadoNumerosTablaPrincipal(QObject* parent=nullptr);
    void paint( QPainter *painter,const QStyleOptionViewItem &option, const QModelIndex &index ) const;
};

#endif // DELEGADONUMEROSTABLAPRINCIPAL_H
