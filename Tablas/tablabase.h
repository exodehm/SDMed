#ifndef TABLABASE_H
#define TABLABASE_H

#include <QTableView>
#include <QStyledItemDelegate>
#include <QMenu>
#include <QSignalMapper>
#include <QHeaderView>
#include <QItemSelectionModel>

#include "../Delegados/delegadobase.h"
#include "../Delegados/delegadoeditormediciones.h"
#include "../Delegados/delegadosparcialessubtotales.h"
#include "../Delegados/delegadocolumnasbloqueadas.h"
#include "../Delegados/delegadomedicionesestandar.h"
#include "../Delegados/delegadoiconos.h"
#include "../Delegados/delegadoeditornumeros.h"
#include "../Modelos/MedCertModel.h"
#include "../Modelos/PrincipalModel.h"
#include "../filter.h"

class Filter;

class TablaBase : public QTableView
{
    Q_OBJECT

public:
    TablaBase(int nColumnas, QWidget *parent=nullptr);
    ~TablaBase();
    bool columnaBloqueada(int columna);
    QHeaderView* CabeceraDeTabla();
    int limiteIzquierdo;
    int limiteDerecho;

private slots:
    void Bloquear(int columna);


public slots:    
    void Copiar();
    void Pegar();
    void Certificar();    

    virtual void MostrarMenuCabecera(QPoint pos)=0;
    virtual void MostrarMenuLateralTabla(QPoint pos)=0;

signals:
    void CambiaFila(QModelIndex ind);
    void CopiarPartidas();
    void CopiarMedicion();
    void PegarPartidas();
    void PegarMedicion();
    void CertificarLineasMedicion();    

protected:
    QHeaderView* cabeceraHorizontal;
    QHeaderView* alturaFilas;
    QHeaderView* cabeceraVertical;
    DelegadoBase* dlgBA;
    DelegadoEditorNumeros* dlgEN;
    DelegadoColumnasBloqueadas* dlgCB;
    DelegadoIconos* dlgIco;
    bool* celdaBloqueada;
    Filter* filtro;
    QSignalMapper* mapperH;
    QSignalMapper* mapperV;
};

#endif // TABLABASE_H
