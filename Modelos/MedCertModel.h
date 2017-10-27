#ifndef MEDCERTMODELBASE_H
#define MEDCERTMODELBASE_H

#include <QAbstractTableModel>
#include <QStandardItemModel>
#include <QClipboard>
#include <QMimeData>
#include <QItemSelectionModel>
#include <QList>
#include <QStringList>
#include <QUndoStack>
#include <QVariant>
#include <QDebug>
#include <QTextStream>
#include <QFileDialog>
#include <QLocale>
#include <QModelIndex>
#include <iostream>

#include "../include/Obra.h"
#include "../Undo/undomedicion.h"
#include "../defs.h"



class MedCertModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    MedCertModel(Obra* O, int tablaorigen, QUndoStack* p, QObject* parent=nullptr);
    ~MedCertModel();

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
    void VerMedCert(QList<QStringList>&datos);
    void emitDataChanged(const QModelIndex &index);
    QModelIndex IndiceAnterior();

signals:
    void EditarCampoLineaMedicion (QModelIndex, float, QString);
    void Posicionar (QModelIndex indice);


protected:
    Obra* miobra;
    QList<QStringList>datos;
    QStringList LeyendasCabecera;
    int tabla;

    QUndoStack* pila;
};


#endif // MEDCERTMODELBASE_H
