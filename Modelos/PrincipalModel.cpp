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
        return datos.size();
    }
    else
    {        
        return datos.size()-1;
    }
}

int PrincipalModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);    
    return datos.at(0).size();
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
    QStringList fila = datos.at(indice.row()+1);//+1 porque la primera fila del array es el encabezado

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
    }
    else if (indice.column()==tipoColumna::CODIGO || indice.column()==tipoColumna::UD ||indice.column()==tipoColumna::RESUMEN)
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
    if (index.isValid() && (role == Qt::EditRole || role == Qt::DisplayRole) && value.toString()!=index.data().toString())
    {
        switch (index.column())
        {
        case tipoColumna::CODIGO:
        {
            qDebug()<<"editando código";
            return EditarCodigo(index,value.toString());
        }
        case tipoColumna::NATURALEZA:
        {
            qDebug()<<"editando naturaleza";
            return EditarNaturaleza(index, value.toInt());
        }
        case tipoColumna::UD:
        {
            qDebug()<<"editando unidad";
            return EditarUnidad(index, value.toString());
        }
        case tipoColumna::RESUMEN:
        {
            qDebug()<<"editando resumen";
            return EditarResumen(index, value.toString());
        }
        case tipoColumna::CANPRES:
        {
            qDebug()<<"editando cantidad";
            return EditarCantidad(index,value.toFloat());
        }
        case tipoColumna::PRPRES:
        {
            qDebug()<<"editando precio";
            return EditarPrecio(index,value.toFloat());
        }
        default:
        {
            return false;
        }
        }
    }
    return false;
}

bool PrincipalModel::insertRows(int row, int count, const QModelIndex & parent)
{
    Q_UNUSED(parent);
    qDebug()<<"-Row: "<<row<<" -Count: "<<count;
    if (!HayFilaVacia())
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
    if (rowCount(QModelIndex())==0)
    {
        insertRow(0);
    }
    endRemoveRows();
    layoutChanged();
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

Obra *PrincipalModel::LeeObra() const
{
    return miobra;
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

bool PrincipalModel::EditarCodigo(const QModelIndex & index, TEXTO codigo)
{
    if (index.row()==filavacia && HayFilaVacia())//insertar partida nueva
    {
        qDebug()<<"Insertando codigo en la fila "<<index.row();
        miobra->CrearPartida(codigo,filavacia);
    }
    else
    {
        miobra->EditarCodigo(codigo);
    }
    emit dataChanged(index, index);
    hayFilaVacia=false;
    emit dataChanged(index, index);//repito la orden una vez quitada la fila vacia para eliminar la fila sobrante
    return true;
}

bool PrincipalModel::EditarResumen(const QModelIndex &index, TEXTO resumen)
{
    miobra->EditarResumen(resumen);
    emit dataChanged(index, index);
    return true;
}

bool PrincipalModel::EditarNaturaleza(const QModelIndex & index, int naturaleza)
{
    miobra->EditarNaturaleza(naturaleza);
    emit dataChanged(index, index);
    return true;
}

bool PrincipalModel::EditarUnidad(const QModelIndex & index, TEXTO unidad)
{
    miobra->EditarUnidad(unidad);
    emit dataChanged(index, index);
    return true;
}

bool PrincipalModel::EditarCantidad(const QModelIndex & index, float cantidad)
{
    if (miobra->hayMedicionPartidaActual())
    {
        DialogoSuprimirMedicion* d = new DialogoSuprimirMedicion(miobra->LeeCodigoObra());
        if (d->exec()==QDialog::Accepted && d->Suprimir())
        {
            miobra->EditarCantidad(cantidad);
        }
        else
        {
            return false;
        }
    }
    else
    {
        miobra->EditarCantidad(cantidad);
    }
    emit dataChanged(index, index);
    return true;
}

bool PrincipalModel::EditarPrecio(const QModelIndex & index, float precio)
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
                miobra->EditarPrecio(precio);
                break;
            }
            case 2:
            {
                qDebug()<<"Bloquear precio";
                miobra->BloquearPrecio(precio);
                break;
            }
            case 3:
            {
                qDebug()<<"Ajustar";
                break;
            }
            default:
                return false;
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
        miobra->EditarPrecio(precio);
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

void PrincipalModel::ActualizarDatos()
{
    datos.clear();
    mapaDeBool.clear();
    QStringList lineapadre;
    QList<bool>bLineapadre;
    lineapadre = RellenaLinea(miobra->Padre(), miobra->AristaPadre());
    datos.append(lineapadre);
    mapaDeBool.append(bLineapadre);

    ListaAristasNodos listahijos = miobra->LeeDecompuesto();
    QStringList lineahijo;
    QList<bool>bLineahijo;
    for (auto elem:listahijos)
    {
        lineahijo = RellenaLinea(elem.second, elem.first);
        datos.append(lineahijo);
        mapaDeBool.append(bLineahijo);
        lineahijo.clear();
        bLineahijo.clear();
    }
    for(int i=0; i<datos.at(0).length(); i++)
    {
        datos[0][i].prepend(LeyendasCabecera[i]);
    }   
}

QStringList PrincipalModel::RellenaLinea(pNodo nodo, pArista arista)
{

    QStringList linea;
    linea.append(nodo->datonodo.LeeCodigo());                    //codigo
    linea.append(QString::number(nodo->datonodo.LeeNat()));      //naturaleza
    linea.append(nodo->datonodo.LeeUd());                        //ud
    linea.append((nodo->datonodo.LeeResumen()));                   //resumen
    linea.append(QString::number(arista->datoarista.LeeMedicion().LeeTotal(),'f',3));     //Cantidad presupuestada(medida)
    linea.append(QString::number(arista->datoarista.LeeCertificacion().LeeTotal(),'f',3));//Cantidad certificada
    linea.append(QString::number((arista->datoarista.LeeCertificacion().LeeTotal()/arista->datoarista.LeeMedicion().LeeTotal())*100,'f',2));//porcentaje certificado
    linea.append(QString::number(nodo->datonodo.LeeImportePres(),'f',3));               //precio de la medicion
    linea.append(QString::number(nodo->datonodo.LeeImporteCert(),'f',3));               //precio de la certificacion
    /*linea.append(nodo->datonodo.LeeImportePres()==0
                    ? QString::number(nodo->datonodo.LeeImportePres()*1,'f',3)
                    : QString::number(nodo->datonodo.LeeImportePres()*arista->datoarista.LeeMedicion().LeeTotal(),'f',3));*/
    linea.append(CalculaCantidad(nodo,arista));
    linea.append(nodo->datonodo.LeeImporteCert()==0
                 ? QString::number(nodo->datonodo.LeeImporteCert()*1,'f',3)
                 : QString::number(nodo->datonodo.LeeImporteCert()*arista->datoarista.LeeCertificacion().LeeTotal(),'f',3));

    return linea;
}

TEXTO PrincipalModel::CalculaCantidad(pNodo n, pArista A)
{
    if (n->datonodo.LeeImportePres()==0)
    {
        return QString::number(n->datonodo.LeeImportePres()*1,'f',3);
    }
    else
    {
        float factor=1;
        if (miobra->NivelUno(/*A->destino*/)&& A!=miobra->AristaPadre())
        {
            factor=1.1;//para reflejar el coste indirecto en la columna ImpPres
        }
        return QString::number(n->datonodo.LeeImportePres()*A->datoarista.LeeMedicion().LeeTotal()*factor,'f',3);
    }
}
