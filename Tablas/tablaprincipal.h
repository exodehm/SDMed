#ifndef TABLAPRINCIPAL_H
#define TABLAPRINCIPAL_H

#include <QTableView>
#include <QKeyEvent>
#include <QHeaderView>
#include <QDebug>

#include "../defs.h"
#include "../Delegados/delegadoeditormediciones.h"
#include "../Delegados/delegadosparcialessubtotales.h"
#include "../Delegados/delegadocolumnasbloqueadas.h"
#include "../Delegados/delegadomedicionesestandar.h"
#include "../Delegados/delegadoiconos.h"

class TablaPrincipal : public QTableView
{
    Q_OBJECT
public:
    explicit TablaPrincipal(QWidget *parent = nullptr);
    bool eventFilter(QObject * watched, QEvent * e);
    bool columnaBloqueada(int columna);

private slots:
    void Bloquear(int columna);

private:
    QHeaderView* cabecera;
    QHeaderView* alturaFilas;
    DelegadoColumnasBloqueadas* dlgCB;
    DelegadoEditorMediciones* dlgEM;
    DelegadoIconos* dlgIco;
    bool celdaBloqueada[11];
};

#endif // TABLAPRINCIPAL_H
