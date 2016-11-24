#include "MedicionesModel.h"


MedicionesModel::MedicionesModel(Obra *O, QObject* parent):QAbstractTableModel(parent)
{	
    LeyendasCabecera.append(QObject::tr("Fase\n"));
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
    ActualizarDatos();
}

MedicionesModel::~MedicionesModel()
{

}

int MedicionesModel::rowCount(const QModelIndex& parent) const
{
	Q_UNUSED(parent);
    return datos.length();
}

int MedicionesModel::columnCount(const QModelIndex& parent) const
{
	Q_UNUSED(parent);
    return 10;//datos.value(0).length();
}

QVariant MedicionesModel::headerData(int section, Qt::Orientation orientation, int role) const
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

QVariant MedicionesModel::data(const QModelIndex& indice,int role) const
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
                QLocale::setDefault(QLocale( QLocale::Spanish, QLocale::Spain ));
                return QString( "%L1" ).arg(fila.at(indice.column()).toFloat());
            }
        }
        else
        {
            return fila.value(indice.column());
        }
    }
    return QVariant();
}

Qt::ItemFlags MedicionesModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
	{
        return 0;
	}
    if (index.column()!=tipoColumna::PARCIAL && index.column()!=tipoColumna::SUBTOTAL && index.column()!=tipoColumna::FORMULA)
    {
        return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
    }
    return  QAbstractItemModel::flags(index);
}

bool MedicionesModel::setData(const QModelIndex & index, const QVariant& value, int role)
{
    if (index.isValid() && (role == Qt::EditRole || role == Qt::DisplayRole))
	{
        datos[index.row()][index.column()]=value.toString();
        emit dataChanged(index, index);
        if (index.column()==tipoColumna::COMENTARIO || index.column()==tipoColumna::FORMULA)
        {            
            emit EditarCampoLineaMedicion(index.column(),0, value.toString());//mando el string y el valor numerico a 0
        }
        else if (index.column()==tipoColumna::N || index.column()==tipoColumna::LONGITUD || index.column()==tipoColumna::ANCHURA || index.column()==tipoColumna::ALTURA)
        {
            emit EditarCampoLineaMedicion(index.column(),value.toFloat(),"");//mando el valor numerico y el string vacío           
        }
        return true;
    }
    return false;
}

bool MedicionesModel::insertRows(int row, int count, const QModelIndex & parent)
{
	Q_UNUSED(parent);
    beginInsertRows(QModelIndex(), row, row+count);
    endInsertRows();
    return true;
}

bool MedicionesModel::removeRows(int filaInicial, int numFilas, const QModelIndex& parent)
{
	Q_UNUSED(parent);
    beginRemoveRows(QModelIndex(), filaInicial, filaInicial+numFilas-1);
    endRemoveRows();
	return true;
}

bool MedicionesModel::filaVacia(const QStringList& linea)
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

void MedicionesModel::ActualizarDatos()
{
    datos.clear();
    //LeyendasCabecera[tipoColumna::PARCIAL].clear();
    datos = miobra->VerMedCert();
    QStringList liena;
    foreach (liena, datos) {
        QString linea;
        foreach (linea, liena)
        {
            qDebug()<<"linea: "<<linea;
        }
    }
    //QString suma=QString::number(miobra->LeeTotalLineasMedicion(),'f',2);
    //LeyendasCabecera[tipoColumna::PARCIAL].append("Parcial\n").append(suma);
}
