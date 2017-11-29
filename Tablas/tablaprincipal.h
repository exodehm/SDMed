#ifndef TABLAPRINCIPAL_H
#define TABLAPRINCIPAL_H

#include "../defs.h"
#include "tablabase.h"

class TablaPrincipal : public TablaBase
{
     Q_OBJECT
public:
    explicit TablaPrincipal(int nColumnas, QWidget *parent=nullptr);    

public slots:
    void MostrarMenuCabecera(QPoint pos);
    void MostrarMenuLateralTabla(QPoint pos);

};

#endif // TABLAPRINCIPAL_H
