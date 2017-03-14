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
    hayFilaVacia=false;
}

PrincipalModel::~PrincipalModel()
{

}

int PrincipalModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    if (hayFilaVacia)
    {
        return miobra->VerActual().size();
    }
    else
    {
        return miobra->VerActual().size()-1;
    }
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

QVariant PrincipalModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid()) return QVariant();
    QModelIndex indice = index;
    if (hayFilaVacia)
    {
        if (index.row()>=filavacia)
        {
            indice = this->index(index.row()-1,index.column());
        }
    }
    QStringList fila = datos.at(indice.row()+1);

    if (hayFilaVacia && index.row()==filavacia)
    {
        return QVariant();
    }
    else if (esColumnaNumerica(indice.column()))
    {
        if (role==Qt::DisplayRole || role == Qt::EditRole)
        {
            return fila.at(indice.column()).toFloat();
        }
    }else if (indice.column()==tipoColumna::CODIGO || indice.column()==tipoColumna::UD ||indice.column()==tipoColumna::RESUMEN)
    {
        if (role == Qt::DisplayRole || role == Qt::EditRole)
        {
            return fila.at(indice.column());
        }
    }
    else if (indice.column()==tipoColumna::NATURALEZA)
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
            //tip += QString("%1</b>").arg(fila.at(indice.column()));
            tip += QString("%1</b>").arg(naturaleza::leyenda_nat[fila.at(indice.column()).toInt()]);
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
    if (/*index.row()!= filavacia && */index.column()!=tipoColumna::IMPPRES && index.column()!=tipoColumna::IMPCERT)
    {
        return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
    }
    return  QAbstractItemModel::flags(index);
}

bool PrincipalModel::setData(const QModelIndex & index, const QVariant& value, int role)
{
    QModelIndex indice = index;
    /*if (hayFilaVacia)
    {
        if (index.row()>=filavacia)
        {
            indice = this->index(index.row()-1,index.column());
        }
    }*/
    if (index.isValid() && (role == Qt::EditRole || role == Qt::DisplayRole))
    {
        //insertar partida nueva
        if (index.column()==tipoColumna::CODIGO && index.row()==filavacia)
        {
            qDebug()<<"Insertando codigo";
            miobra->CrearPartida(value.toString(),filavacia);
            hayFilaVacia=false;
            emit dataChanged(index, index);
            return true;
        }
        if (indice.column()==tipoColumna::RESUMEN)
        {
            miobra->EditarResumen(value.toString());
            emit dataChanged(index, index);
            return true;
        }
        else if (indice.column()==tipoColumna::CANPRES)
        {
            if (miobra->hayMedicionPartidaActual())
            {
                DialogoSuprimirMedicion* d = new DialogoSuprimirMedicion(miobra->LeeCodigoObra());
                if (d->exec()==QDialog::Accepted && d->Suprimir())
                {
                    miobra->EditarCantidad(value.toFloat());
                }
                else
                {
                    return false;
                }
            }
            else
            {
                miobra->EditarCantidad(value.toFloat());
            }
            emit dataChanged(index, index);
            return true;
        }
        else if (indice.column()==tipoColumna::PRPRES)
        {
            if (miobra->hayDescomposicion())
            {
                DialogoPrecio* d = new DialogoPrecio(miobra->LeeCodigoActual());
                if (d->exec()==QDialog::Accepted)
                {
                    switch (d->Respuesta())
                    {
                    case 1:
                    {
                        qDebug()<<"Suprimir descomposicion";
                        miobra->SuprimirDescomposicion();
                        miobra->EditarPrecio(value.toFloat());
                        break;
                    }
                    case 2:
                    {
                        qDebug()<<"Bloquear precio";
                        miobra->BloquearPrecio(value.toFloat());
                        break;
                    }
                    case 3:
                    {
                        qDebug()<<"Ajustar";
                        break;
                    }
                    default:
                        miobra->EditarPrecio(value.toFloat());
                        break;
                    }
                    emit dataChanged(index, index);
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                miobra->EditarPrecio(value.toFloat());
                emit dataChanged(index, index);
                return true;
            }            
        }       
        else if (index.column()==tipoColumna::NATURALEZA)
        {
            miobra->EditarNaturaleza(value.toInt());
            emit dataChanged(index, index);
            return true;
        }
    }
    return false;
}

bool PrincipalModel::insertRows(int row, int count, const QModelIndex & parent)
{
    Q_UNUSED(parent);
    qDebug()<<"-Row: "<<row<<" -Count: "<<count;
    {
        beginInsertRows(QModelIndex(), row, row+count-1);
        hayFilaVacia = true;
        filavacia = row;
        endInsertRows();
    }  
    return true;
}

bool PrincipalModel::removeRows(int filaInicial, int numFilas, const QModelIndex& parent)
{
    Q_UNUSED(parent);
    beginRemoveRows(QModelIndex(), filaInicial, filaInicial+numFilas-1);
    miobra->PosicionarAristaActual(filaInicial);
    miobra->BorrarPartida();    
    ActualizarDatos();
    endRemoveRows();
    if (miobra->EsPartidaVacia())
    {
        insertRows(0,1,QModelIndex());
    }
    return true;
}

bool PrincipalModel::HayFilaVacia()
{
    return hayFilaVacia;
}

int PrincipalModel::FilaVacia()
{
    if (hayFilaVacia)
    {
        qDebug()<<"Fila vacia en: "<<filavacia;
        return filavacia;
    }
    else
    {
        return this->rowCount(QModelIndex());
    }
}

void PrincipalModel::QuitarIndicadorFilaVacia()
{
    hayFilaVacia=false;
}

void PrincipalModel::ActualizarDatos()
{
    qDebug()<<"Filas iniciales: "<<datos.length();
    datos.clear();
    datos = miobra->VerActual();

    for(int i=0; i<datos.at(0).length(); i++)
    {
        datos[0][i].prepend(LeyendasCabecera[i]);
    }
    qDebug()<<"Filas finales: "<<datos.length();
}

bool PrincipalModel::esColumnaNumerica(int columna) const
{
    return  columna==tipoColumna::CANPRES ||
            columna==tipoColumna::CANCERT ||
            columna==tipoColumna::PORCERTPRES ||
            columna==tipoColumna::PRPRES ||
            columna==tipoColumna::PRCERT ||
            columna==tipoColumna::IMPPRES ||
            columna==tipoColumna:: IMPCERT;
}
