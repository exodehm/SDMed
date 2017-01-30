#ifndef TABLAMEDCERT_H
#define TABLAMEDCERT_H

#include "../defs.h"
#include "./Tablas/tablabase.h"


class TablaMedCert : public TablaBase
{
public:
    explicit TablaMedCert(int nColumnas, QWidget *parent=nullptr);
    void MostrarMenu(QPoint pos);

private:
    DelegadosParcialesSubtotales* dlgPS;
    DelegadoMedicionesEstandar* dlgME;
};


#endif // TABLAMEDCERT_H
