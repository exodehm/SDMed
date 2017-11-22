#ifndef PRINCIPALMODEL_H
#define PRINCIPALMODEL_H

#include <QAbstractTableModel>
#include <QStandardItemModel>
#include <QList>
#include <QStringList>
#include <QVariant>
#include <QDebug>
#include <QTextStream>
#include <QMessageBox>
#include<QLocale>

#include "../include/Obra.h"
#include "../Dialogos/dialogosuprimirmedicion.h"
#include "../Dialogos/dialogoprecio.h"
#include "../Undo/undoeditarprincipal.h"

#include "../iconos.h"
#include "../defs.h"

struct DatoCelda
{
    TEXTO valor;
    QColor color;
};
Q_DECLARE_METATYPE(DatoCelda)


class PrincipalModel : public QAbstractTableModel
{
    Q_OBJECT

public:

    typedef std::list<std::pair<pNodo,pArista>> ListaNodosAristas;
    typedef std::list<std::pair<pArista,pNodo>> ListaAristasNodos;    
    QColor Colores[3];

    PrincipalModel(Obra* O, QUndoStack* p, QObject* parent=nullptr);
    ~PrincipalModel();

    static const int IconIndexRole = Qt::UserRole + 1;

    int rowCount(const QModelIndex& parent) const;
    int columnCount(const QModelIndex& parent) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QVariant data(const QModelIndex& index,int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex & index, const QVariant& value, int role);

    bool insertRows(int row, int count, const QModelIndex & parent);
    bool removeRows(int filaInicial, int numFilas, const QModelIndex& parent);
    bool HayFilaVacia();
    int FilaVacia();
    bool HayListaDatos();
    void ActualizarDatos(const std::list<std::list<Dato>>& datosStd);
    bool esColumnaNumerica(int columna) const;
    void QuitarIndicadorFilaVacia();
    Obra* LeeObra() const;
    bool ModificarPrecioExistente(QModelIndex indice, QVariant precio);
    /***********FUNCIONES DE EDICION**********************************/
    bool EditarCodigo(const QModelIndex & index, QVariant codigo);
    bool EditarResumen(const QModelIndex & index, QVariant resumen);
    bool EditarNaturaleza(const QModelIndex & index, QVariant naturaleza);
    bool EditarCantidad(const QModelIndex & index, QVariant cantidad);
    bool EditarPrecio(const QModelIndex & index, QVariant precio);
    bool EditarUnidad(const QModelIndex & index, TEXTO unidad);
    /*****************************************************************/
    void VerActual();    
    QColor LeeColor(int fila, int columna);
    QString LeeColorS(int i, int j);
    TEXTO CalculaCantidad(pNodo n, pArista A);

    void emitDataChanged(const QModelIndex &index);

private:

    QList<QList<DatoCelda>>datos;
    QStringList cabecera;
    QString LeyendasCabecera[11];
    Obra* miobra;
    bool hayFilaVacia;
    int filavacia;
    QUndoStack* pila;
    QLocale locale;
    int FactorRedondeoVisualizacion;
};

#endif // PRINCIPALMODEL_H

