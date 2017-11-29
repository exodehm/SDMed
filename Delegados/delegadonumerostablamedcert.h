#ifndef DELEGADONUMEROSTABLAMEDCERT_H
#define DELEGADONUMEROSTABLAMEDCERT_H


#include "./Delegados/delegadonumerosbase.h"

class DelegadoNumerosTablaMedCert : public DelegadoNumerosBase
{
public:    
    explicit DelegadoNumerosTablaMedCert(QObject* parent=nullptr);
    void paint( QPainter *painter,const QStyleOptionViewItem &option, const QModelIndex &index ) const;
};

#endif // DELEGADONUMEROSTABLAMEDCERT_H
