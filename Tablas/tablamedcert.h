#ifndef TABLAMEDCERT_H
#define TABLAMEDCERT_H

#include <QTableView>
#include <QKeyEvent>
#include <QHeaderView>
#include <QDebug>

#include "../defs.h"
#include "../Delegados/delegadoeditormediciones.h"
#include "../Delegados/delegadosparcialessubtotales.h"
#include "../Delegados/delegadocolumnasbloqueadas.h"
#include "../Delegados/delegadomedicionesestandar.h"

class TablaMedCert : public QTableView
{
    Q_OBJECT
public:
    TablaMedCert(QWidget *parent=nullptr);
    bool eventFilter(QObject * watched, QEvent * e);    
    bool columnaBloqueada(int columna);

private slots:
    void Bloquear(int columna);

private:
    QHeaderView* cabecera;
    QHeaderView* alturaFilas;
    DelegadoEditorMediciones* dlgEM;
    DelegadosParcialesSubtotales* dlgPS;
    DelegadoColumnasBloqueadas* dlgCB;
    DelegadoMedicionesEstandar* dlgME;
    bool celdaBloqueada[10];
};

#endif // TABLAMEDCERT_H
