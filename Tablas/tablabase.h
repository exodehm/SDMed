#ifndef TABLABASE_H
#define TABLABASE_H

#include <QTableView>
#include <QStyledItemDelegate>
#include <QMenu>
#include <QSignalMapper>
#include <QHeaderView>
#include <QItemSelectionModel>

#include "../Delegados/delegadobase.h"
#include "../Delegados/delegadocolumnasbloqueadas.h"
#include "../Delegados/delegadoiconos.h"
#include "../Delegados/delegadonumerosbase.h"
#include "../Delegados/delegadonumerostablaprincipal.h"
#include "../Delegados/delegadonumerostablamedcert.h"
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
    void PonerDelegadoOriginal(int columna);
    void BorrarFilas(QList<int>indices);

private slots:
    void Bloquear(int columna);


public slots:    
    void Copiar();
    void Pegar();
    void Certificar();

    void SeleccionarTodo();

    virtual void MostrarMenuCabecera(QPoint pos)=0;
    virtual void MostrarMenuLateralTabla(QPoint pos)=0;

signals:
    void CambiaFila(QModelIndex ind);
    /*void CopiarPartidas();
    void CopiarMedicion();*/
    void CopiarContenido();
    void PegarContenido();
    void CertificarLineasMedicion();    

protected:
    QHeaderView* cabeceraHorizontal;
    QHeaderView* alturaFilas;
    QHeaderView* cabeceraVertical;
    DelegadoBase* dlgBA;    
    DelegadoNumerosTablaPrincipal* dlgNumTablaP;
    DelegadoNumerosTablaMedCert* dlgNumTablaMC;
    DelegadoColumnasBloqueadas* dlgCB;
    DelegadoIconos* dlgIco;
    bool* celdaBloqueada;
    Filter* filtro;
    QSignalMapper* mapperH;
    QSignalMapper* mapperV;
};

#endif // TABLABASE_H
