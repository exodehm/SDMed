#ifndef TABLAMEDCERT_H
#define TABLAMEDCERT_H

#include "../defs.h"
#include "tablabase.h"

class TablaMedCert : public TablaBase
{
     Q_OBJECT
public:
    explicit TablaMedCert(int nColumnas, QWidget *parent=nullptr);    


public slots:
    void MostrarMenuCabecera(QPoint pos);
    void MostrarMenuLateralTabla(QPoint pos);

};


#endif // TABLAMEDCERT_H
