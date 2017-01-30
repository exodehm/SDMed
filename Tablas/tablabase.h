#ifndef TABLABASE_H
#define TABLABASE_H

#include <QTableView>
#include <QMenu>
#include <QSignalMapper>
#include <QHeaderView>

#include "../Delegados/delegadoeditormediciones.h"
#include "../Delegados/delegadosparcialessubtotales.h"
#include "../Delegados/delegadocolumnasbloqueadas.h"
#include "../Delegados/delegadomedicionesestandar.h"
#include "../Delegados/delegadoiconos.h"
#include "../filter.h"

class Filter;

class TablaBase : public QTableView
{
    Q_OBJECT

public:
    TablaBase(int nColumnas, QWidget *parent=nullptr);
    bool columnaBloqueada(int columna);
    virtual void MostrarMenu(QPoint pos)=0;
    QHeaderView* CabeceraDeTabla();
    ~TablaBase();

    int limiteIzquierdo;
    int limiteDerecho;

private slots:
    void Bloquear(int columna);

public slots:
    void customMenuRequested(QPoint pos);

protected:
    QHeaderView* cabecera;
    QHeaderView* alturaFilas;
    DelegadoEditorMediciones* dlgEM;
    DelegadoColumnasBloqueadas* dlgCB;
    DelegadoIconos* dlgIco;
    bool* celdaBloqueada;
    Filter* filtro;
    QSignalMapper* mapper;
};

#endif // TABLABASE_H
