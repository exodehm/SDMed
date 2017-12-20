#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractItemModel>

#include "./treeitem.h"
#include "../include/Obra.h"
#include "../defs.h"
#include "../iconos.h"


class TreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit TreeModel(Obra* O, QObject *parent = nullptr);
      ~TreeModel();

      QVariant data(const QModelIndex &index, int role) const override;
      Qt::ItemFlags flags(const QModelIndex &index) const override;
      QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
      QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
      QModelIndex parent(const QModelIndex &index) const override;
      int rowCount(const QModelIndex &parent = QModelIndex()) const override;
      int columnCount(const QModelIndex &parent = QModelIndex()) const override;

  private:
      void setupModelData(Obra *obra, TreeItem *parent);
      void ActualizarDatos(const std::list<std::list<Dato>>& datosStd);
      TreeItem* CrearItem(pNodo nodo, TreeItem* parent = nullptr);

      TreeItem *rootItem;
      std::list<std::pair<TreeItem*,int>>listaitems;
      Obra* obra;
};

#endif // TREEMODEL_H
