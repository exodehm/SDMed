#include "MedCertModel.h"

MedCertModel::MedCertModel(Obra *O, int tablaorigen, QObject* parent):tabla(tablaorigen),QAbstractTableModel(parent)
{
    if (tabla==MedCert::MEDICION)
    {
        LeyendasCabecera.append(QObject::tr("Fase\n"));
    }
    else
    {
        LeyendasCabecera.append(QObject::tr("Nº Certificacion\n"));
    }
    LeyendasCabecera.append(QObject::tr("Comentario\n"));
    LeyendasCabecera.append(QObject::tr("Nº Uds\n"));
    LeyendasCabecera.append(QObject::tr("Longitud\n"));
    LeyendasCabecera.append(QObject::tr("Anchura\n"));
    LeyendasCabecera.append(QObject::tr("Altura\n"));
    LeyendasCabecera.append(QObject::tr("Fórmula\n"));
    LeyendasCabecera.append(QObject::tr("Parcial\n"));
    LeyendasCabecera.append(QObject::tr("SubTotal\n"));
    LeyendasCabecera.append(QObject::tr("Id\n"));

    miobra = O;   
}

MedCertModel::~MedCertModel()
{

}

int MedCertModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return datos.length();
}

int MedCertModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return LeyendasCabecera.length();
}

QVariant MedCertModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal)
    {
        if (role == Qt::DisplayRole)
        {
            return LeyendasCabecera.value(section);
        }
    }
    return QAbstractTableModel::headerData(section, orientation, role);
}

QVariant MedCertModel::data(const QModelIndex& indice,int role) const
{
    if (!indice.isValid()) return QVariant();

    QStringList fila = datos.value(indice.row());

    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        if (indice.column() != tipoColumna::FASE && indice.column() != tipoColumna::COMENTARIO && indice.column() != tipoColumna::FORMULA)
        {
            if (fila.at(indice.column()) == "0")
            {
                return "";//dejo vacia la casilla si el valor es 0
            }
            else
            {
                return fila.at(indice.column());
            }
        }
        else
        {
            return fila.value(indice.column());
        }
    }
    return QVariant();
}

Qt::ItemFlags MedCertModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
    {
        return 0;
    }
    if (index.column()!=tipoColumna::PARCIAL && index.column()!=tipoColumna::SUBTOTAL && index.column()!=tipoColumna::ID)
    {
        return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
    }
    return  QAbstractItemModel::flags(index);
}

bool MedCertModel::setData(const QModelIndex & index, const QVariant& value, int role)
{
    if (index.isValid() && (role == Qt::EditRole || role == Qt::DisplayRole))
    {
        if (index.column()==tipoColumna::COMENTARIO || index.column()==tipoColumna::FORMULA)
        {
            qDebug()<<"Actualizando comentario o formula...";
            miobra->EditarLineaMedicion(index.row(), index.column(),0, value.toString());//mando el string y el valor numerico a 0
        }
        else if (index.column()==tipoColumna::N || index.column()==tipoColumna::LONGITUD || index.column()==tipoColumna::ANCHURA || index.column()==tipoColumna::ALTURA)
        {
            QString valor = value.toString().replace(",",".");
            miobra->EditarLineaMedicion(index.row(), index.column(),value.toDouble(),"");//mando el valor numerico y el string vacío
        }
        ActualizarDatos();
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

bool MedCertModel::insertRows(int row, int count, const QModelIndex& parent)
{
    Q_UNUSED(parent);
    beginInsertRows(QModelIndex(), row, row+count-1);
    miobra->InsertarLineasVaciasMedicion(tabla,row, count);
    ActualizarDatos();
    endInsertRows();
    return true;
}

bool MedCertModel::removeRows(int filaInicial, int numFilas, const QModelIndex& parent)
{
    Q_UNUSED(parent);
    qDebug()<<"Fila donde se empieza a borrar: "<<filaInicial<<" con numero de filas: "<<numFilas;
    beginRemoveRows(QModelIndex(), filaInicial, filaInicial+numFilas-1);
    miobra->BorrarLineasMedicion(filaInicial,numFilas);
    ActualizarDatos();
    endRemoveRows();
    layoutChanged();
    return true;
}

bool MedCertModel::filaVacia(const QStringList& linea)
{
    int i=0;
    while (i<linea.length())
    {
        if (!linea.at(i).isEmpty())
        {
            return false;
        }
        i++;
    }
    return true;
}

void MedCertModel::ActualizarDatos()
{
    datos.clear();
    qDebug()<<"Total medicion: "<<miobra->LeeTotalMedicion(tabla);
    LeyendasCabecera[tipoColumna::PARCIAL].clear();
    VerMedCert(datos);
    if (rowCount(QModelIndex())==0 && miobra->EsPartida())
    {
        miobra->InsertarLineasVaciasMedicion(tabla,0,1);
    }
    VerMedCert(datos);
    qDebug()<<"Num liNEAS: "<<rowCount(QModelIndex());
    QString suma=QString::number(miobra->LeeTotalMedicion(tabla),'f',2);
    LeyendasCabecera[tipoColumna::PARCIAL].append("Parcial\n").append(suma);
}

void MedCertModel::VerMedCert(QList<QStringList> &datos)
{
    std::list<LineaMedicion> lista = miobra->AristaPadre()->datoarista.LeeMedCer(tabla).LeeLista();
    datos.clear();
    for (auto elem : lista)
    {
        datos.append(elem.LeeLineaMedicion());
        /*QString dato;
        foreach (dato, elem.LeeLineaMedicion())
        {
            qDebug()<<dato;
        }*/
    }
}
