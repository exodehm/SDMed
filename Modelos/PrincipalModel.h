#ifndef PRINCIPALMODEL_H
#define PRINCIPALMODEL_H

#include <QAbstractTableModel>
#include <QStandardItemModel>
#include <QList>
#include <QStringList>
#include <QVariant>
#include <QDebug>
#include <QTextStream>

#include "./include/Obra.h"
#include "./Dialogos/dialogosuprimirmedicion.h"
#include "./Dialogos/dialogoprecio.h"


#include "../iconos.h"
#include "./defs.h"


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
    QVariant data(const QModelIndex& indice,int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex & index, const QVariant& value, int role);

    bool insertRows(int row, int count, const QModelIndex & parent);
    bool removeRows(int filaInicial, int numFilas, const QModelIndex& parent);
    bool filaVacia(const QStringList& linea);
    void ActualizarDatos();

signals:
    void EditarCampoTexto (int, QString);
    void EditarCampoNumerico(int,float);
    void EditarNaturaleza (int);

private:
    QList <QStringList> datos;
    QStringList cabecera;
    QString LeyendasCabecera[11];
    Obra* miobra;    
};

#endif // PRINCIPALMODEL_H

