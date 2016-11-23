#ifndef MEDICIONESMODEL_H
#define MEDICIONESMODEL_H

#include <QAbstractTableModel>
#include <QStandardItemModel>
#include <QList>
#include <QStringList>
#include <QVariant>
#include <QDebug>
#include <QTextStream>
#include <QFileDialog>
#include <iostream>

#include "./include/Obra.h"
#include "../defs.h"



class MedicionesModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    MedicionesModel(Obra* O, QObject* parent=nullptr);
    ~MedicionesModel();

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
    void EditarCampoLineaMedicion (int, float, QString);


private:
    Obra* miobra;
    QList<QStringList>datos;
    QStringList LeyendasCabecera;    
};

#endif