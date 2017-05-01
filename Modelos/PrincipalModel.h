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

#include "../include/Obra.h"
#include "../Dialogos/dialogosuprimirmedicion.h"
#include "../Dialogos/dialogoprecio.h"


#include "../iconos.h"
#include "../defs.h"


class PrincipalModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    PrincipalModel(Obra* O, QObject* parent=nullptr);
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
    void ActualizarDatos();
    bool esColumnaNumerica(int columna) const;
    void QuitarIndicadorFilaVacia();
    /***********FUNCIONES DE EDICION**********************************/
    bool EditarCodigo(const QModelIndex & index, TEXTO codigo);
    bool EditarResumen(const QModelIndex & index, TEXTO resumen);
    bool EditarNaturaleza(const QModelIndex & index, int naturaleza);
    bool EditarCantidad(const QModelIndex & index, float cantidad);
    bool EditarPrecio(const QModelIndex & index, float precio);
    bool EditarUnidad(const QModelIndex & index, TEXTO unidad);

/*signals:
    void EditarCampoTexto (int, QString);
    void EditarCampoNumerico(int,float);
    void EditarNaturaleza (int);*/

private:
    QList <QStringList> datos;
    QStringList cabecera;
    QString LeyendasCabecera[11];
    Obra* miobra;
    bool hayFilaVacia;
    int filavacia;
};

#endif // PRINCIPALMODEL_H

