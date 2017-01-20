#include "PrincipalModel.h"

PrincipalModel::PrincipalModel (Obra *O, QObject* parent):QAbstractTableModel(parent)
{
    LeyendasCabecera[0]=QObject::tr("Código\n");
    LeyendasCabecera[1]=QObject::tr("Nat\n");
    LeyendasCabecera[2]=QObject::tr("Ud\n");
    LeyendasCabecera[3]=QObject::tr("Resumen\n");
    LeyendasCabecera[4]=QObject::tr("CanPres\n");
    LeyendasCabecera[5]=QObject::tr("CanCert\n");
    LeyendasCabecera[6]=QObject::tr("PorCertPres\n");
    LeyendasCabecera[7]=QObject::tr("PrPres\n");
    LeyendasCabecera[8]=QObject::tr("PrCert\n");
    LeyendasCabecera[9]=QObject::tr("ImpPres\n");
    LeyendasCabecera[10]=QObject::tr("ImpCert\n");

    miobra = O;

    ActualizarDatos();
}

PrincipalModel::~PrincipalModel()
{

}

int PrincipalModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return miobra->VerActual().size()-1;
}

int PrincipalModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return miobra->VerActual().at(0).size();
}

QVariant PrincipalModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal)
    {
        if (role == Qt::DisplayRole)
        {
            return datos.at(0).at(section);
        }
    }
    return QAbstractTableModel::headerData(section, orientation, role);
}

QVariant PrincipalModel::data(const QModelIndex& indice,int role) const
{
    if (!indice.isValid()) return QVariant();

    QStringList fila = datos.at(indice.row()+1);

    if (    indice.column()==tipoColumna::CANPRES ||
            indice.column()==tipoColumna::CANCERT ||
            indice.column()==tipoColumna::PORCERTPRES ||
            indice.column()==tipoColumna::PRPRES ||
            indice.column()==tipoColumna::PRCERT ||
            indice.column()==tipoColumna::IMPPRES ||
            indice.column()==tipoColumna:: IMPCERT)
    {
        if (role==Qt::DisplayRole || role == Qt::EditRole)
        {
            //qDebug()<<"El valor String es: "<<QString::number(fila.at(indice.column()).toFloat(),'f',3);
            //qDebug()<<"El valor Float es: "<<fila.at(indice.column()).toFloat();

            QLocale::setDefault(QLocale( QLocale::Spanish, QLocale::Spain ));
            return QString( "%L1" ).arg(fila.at(indice.column()).toFloat());
        }
    }
    if (indice.column()==tipoColumna::CODIGO || indice.column()==tipoColumna::UD ||indice.column()==tipoColumna::RESUMEN)
    {
        if (role == Qt::DisplayRole || role == Qt::EditRole)
        {
            return fila.at(indice.column());
        }
    }

    if (indice.column()==tipoColumna::NATURALEZA)
    {
        if (role == Qt::DecorationRole)
        {
            return RepoIconos::GetIcon((Naturaleza)fila.at(indice.column()).toInt());
        }
        if (role == DatosIconos::ImageIndexRole)
        {
            return fila.at(indice.column());
        }
        if (role == Qt::ToolTipRole)
        {
            QString tip;
            tip = "<b>";
            tip += QString("%1</b>").arg(fila.at(indice.column()));
            return tip;
        }
    }
    return QVariant();
}

Qt::ItemFlags PrincipalModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
    {
        return 0;
    }
    if (index.column()!=tipoColumna::IMPPRES && index.column()!=tipoColumna::IMPCERT)
    {
        return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
    }
    return  QAbstractItemModel::flags(index);
}

bool PrincipalModel::setData(const QModelIndex & index, const QVariant& value, int role)
{
    /*if (index.isValid() && (role == Qt::EditRole || role == Qt::DisplayRole))
    {
        if (index.column()==tipoColumna::CODIGO || index.column()==tipoColumna::RESUMEN)
        {
            datos[index.row()+1][index.column()]=value.toString();
            emit dataChanged(index, index);
            emit EditarCampoTexto(index.column(),value.toString());
            return true;
        }
        else if (index.column()==tipoColumna::CANPRES || index.column()==tipoColumna::PRPRES)
        {
            datos[index.row()+1][index.column()]=value.toString();
            emit dataChanged(index, index);
            emit EditarCampoNumerico(index.column(),value.toFloat());
            return true;
        }
        else if (index.column()==tipoColumna::NATURALEZA)
        {
            datos[index.row()+1][index.column()]=value.toString();
            emit dataChanged(index, index);
            emit EditarNaturaleza(value.toInt());
            return true;
        }
    }*/
    return false;
}

bool PrincipalModel::insertRows(int row, int count, const QModelIndex & parent)
{
    Q_UNUSED(parent);
    qDebug()<<"Rosw: "<<row;
    // if (row==rowCount(QModelIndex())+1)
    {
        qDebug()<<"Caso 1";
        beginInsertRows(QModelIndex(), row, row);
        endInsertRows();
    }
    /*else
    {
        qDebug()<<"Caso 2";
        beginInsertRows(QModelIndex(), row, row+count);
        endInsertRows();
    }*/

    return true;
}

bool PrincipalModel::removeRows(int filaInicial, int numFilas, const QModelIndex& parent)
{
    Q_UNUSED(parent);
    beginRemoveRows(QModelIndex(), filaInicial, filaInicial+numFilas-1);
    endRemoveRows();
    return true;
}

bool PrincipalModel::filaVacia(const QStringList& linea)
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

void PrincipalModel::ActualizarDatos()
{
    //qDebug()<<"Filas iniciales: "<<datos.length();
    datos.clear();
    datos = miobra->VerActual();

    for(int i=0; i<datos.at(0).length(); i++)
    {
        datos[0][i].prepend(LeyendasCabecera[i]);
    }
    //qDebug()<<"Filas finales: "<<datos.length();
}
