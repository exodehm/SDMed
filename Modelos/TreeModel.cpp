#include "TreeModel.h"

TreeModel::TreeModel(Obra *O, QObject *parent) : obra(O), QAbstractItemModel(parent),rootItem(nullptr)
{
    ActualizarDatos();
}

TreeModel::~TreeModel()
{
    qDebug()<<"Borrando el treemodel";
    delete rootItem;
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    TreeItem *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    TreeItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
    TreeItem *parentItem = childItem->parentItem();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
    TreeItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    return parentItem->childCount();
}

int TreeModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<TreeItem*>(parent.internalPointer())->columnCount();
    else
        return rootItem->columnCount();
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if (index.column()==tipoColumna::NATURALEZA)
    {
        if (role == Qt::DecorationRole)
        {
            TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
            return RepoIconos::GetIcon(item->data(index.column()).toInt());
        }        
    }
    else if (role == Qt::DisplayRole)//resto de columnas
    {
        TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
        return item->data(index.column());
    }
    if (role != Qt::DisplayRole)
        return QVariant();
    return QVariant();
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}

void TreeModel::setupModelData(Obra* obra, TreeItem *&parent)
{
    std::list<std::pair<pNodo, int>>listado = obra->VerArbol();
    auto iterador = listaitems.begin();
    for (auto elem:listado)
    {
        qDebug()<<elem.second<<" - "<<elem.first->datonodo.LeeCodigo();
        TreeItem* unItem;
        if (elem.second == 1)//primer nivel
        {            
            unItem = CrearItem(elem.first,parent);
        }
        else if (elem.second>iterador->second)
        {
            unItem = CrearItem(elem.first,(*iterador).first);
        }
        else //cuando el nivel del siguiente elemento es menor o igual que el anterior
        {
            auto iterador2 = listaitems.end();
            while(elem.second<=iterador2->second)
            {
                iterador2--;
            }           
            unItem = CrearItem(elem.first,(*iterador2).first);
        }
        std::pair <TreeItem*, int> pareja(unItem,elem.second);
        listaitems.push_back(pareja);
        iterador++;
    }
}

void TreeModel::ActualizarDatos()
{
    if (rootItem)
    {
        listaitems.clear();
        delete rootItem;
    }    
    QList<QVariant> rootData;
    rootData << tr("Código")<<tr("Nat.")<<tr("Ud.")<<tr("Resumen");
    rootItem = new TreeItem(rootData);
    QList<QVariant> ObraData;
    ObraData<<obra->LeeCodigoObra()<<"6"<<"  "<<obra->LeeResumenObra();
    TreeItem* primerItem = new TreeItem(ObraData,rootItem);
    rootItem->appendChild(primerItem);
    std::pair <TreeItem*, int> pareja(primerItem,0);
    listaitems.push_back(pareja);
    setupModelData(obra, primerItem);
}

TreeItem* TreeModel::CrearItem(pNodo nodo, TreeItem *&parent)
{
    QList<QVariant> itemdata;
    itemdata<<nodo->datonodo.LeeCodigo()<<nodo->datonodo.LeeNat()<<nodo->datonodo.LeeUd()<<nodo->datonodo.LeeResumen();
    TreeItem* item = new TreeItem(itemdata,parent);
    parent->appendChild(item);
    return item;
}
