#ifndef TABLAPRINCIPAL_H
#define TABLAPRINCIPAL_H

#include "../defs.h"
#include "./Tablas/tablabase.h"

class TablaPrincipal : public TablaBase
{
public:
    explicit TablaPrincipal(int nColumnas, QWidget *parent=nullptr);
    void MostrarMenu(QPoint pos);
};

#endif // TABLAPRINCIPAL_H
