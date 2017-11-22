#include "PrincipalModel.h"

PrincipalModel::PrincipalModel (Obra *O, QUndoStack *p, QObject* parent):pila(p), QAbstractTableModel(parent)
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

    Colores[color::NORMAL] = Qt::black;
    Colores[color::BLOQUEADO] = Qt::red;
    Colores[color::DESCOMPUESTO] = Qt::magenta;

    miobra = O;
    FactorRedondeoVisualizacion = 3;
    ActualizarDatos(O->LeeDescompuesto());
    hayFilaVacia=false;
    locale=QLocale(QLocale::Spanish,QLocale::Spain);

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
            return datos.at(0).at(section).valor;
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
    QStringList fila;
    for (auto elem:datos.at(indice.row()+1))//+1 porque la primera fila del array es el encabezado
    {
        fila.append(elem.valor);
    }
    if (hayFilaVacia && index.row()==filavacia)
    {
        return QVariant();
    }
    else if (esColumnaNumerica(indice.column()))
    {
        if (role==Qt::DisplayRole || role == Qt::EditRole)
        {
            return fila.at(indice.column());
            //qDebug()<<"En fila: "<<indice.column()<<" hay un valor: "<<fila.at(indice.column())<<" con el tipo: ";
            //QString test = QString("%1").arg(numero, 7, 'f',4, QLatin1Char('0'));
            //return QString("%1").arg(fila.at(indice.column()).toFloat(),7,'f',4,QLatin1Char('0'));
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
    if (index.isValid() && (role == Qt::EditRole /*|| role == Qt::DisplayRole*/) && value.toString()!=index.data().toString())
    {
        switch (index.column())
        {
        case tipoColumna::CODIGO:
            qDebug()<<"editando código";
            EditarCodigo(index,value);
            break;
        case tipoColumna::NATURALEZA:
            qDebug()<<"editando naturaleza";
            EditarNaturaleza(index,value.toInt());
            break;
        case tipoColumna::UD:
            qDebug()<<"editando unidad";
            EditarUnidad(index,value.toString());
            break;
        case tipoColumna::RESUMEN:
            qDebug()<<"editando resumen";
            EditarResumen(index,value.toString());
            break;
        case tipoColumna::CANPRES:
            qDebug()<<"editando cantidad";
            EditarCantidad(index,value);
            break;
        case tipoColumna::PRPRES:
            qDebug()<<"editando precio";
            EditarPrecio(index, value);
            break;
        default:
            break;
        }
        return true;
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
    ActualizarDatos(miobra->LeeDescompuesto());
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

bool PrincipalModel::EditarCodigo(const QModelIndex & index, QVariant codigo)
{   
    QString descripcion = "Editar codigo " + codigo.toString();
    pila->push(new UndoEditarCodigo(miobra,this,index,codigo,descripcion));
    return true;
}

bool PrincipalModel::EditarResumen(const QModelIndex &index, QVariant resumen)
{
    QString descripcion = "Editar resumen";
    pila->push(new UndoEditarResumen(miobra,this,index,resumen,descripcion));
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

bool PrincipalModel::EditarCantidad(const QModelIndex & index, QVariant cantidad)
{
    if (miobra->HayMedicionPartidaActual())
    {
        DialogoSuprimirMedicion* d = new DialogoSuprimirMedicion(miobra->LeeCodigoObra());
        if (d->exec()==QDialog::Rejected || d->Suprimir()==false)
        {
            return false;
        }
    }
    QString descripcion = "Editar cantidad " + cantidad.toString();
    pila->push(new UndoEditarCantidad(miobra,this,index,cantidad,descripcion));
    return true;
}

bool PrincipalModel::EditarPrecio(const QModelIndex & index, QVariant precio)
{
    if (miobra->HayDescomposicionPartidaActual())
    {
        return ModificarPrecioExistente(index, precio);
    }
    else
    {
        QString descripcion = "Editar precio";
        pila->push(new UndoEditarPrecio(miobra,this,index,precio,precio::MODIFICAR, descripcion));
        //emit dataChanged(index, index);
        return true;
    }
    return false;
}

bool PrincipalModel::ModificarPrecioExistente(QModelIndex indice, QVariant precio)
{
    DialogoPrecio* d = new DialogoPrecio(miobra->LeeCodigoActual());
    if (d->exec()==QDialog::Accepted)
    {
        QString descripcion = "Editar precio";
        switch (d->Respuesta())
        {
        case precio::SUPRIMIR:
        {
            pila->push(new UndoEditarPrecio(miobra,this,indice, precio, precio::SUPRIMIR, descripcion));
            break;
        }
        case precio::BLOQUEAR:
        {
            pila->push(new UndoEditarPrecio(miobra,this,indice, precio, precio::BLOQUEAR, descripcion));
            break;
        }
        case precio::AJUSTAR:
        {
            pila->push(new UndoEditarPrecio(miobra,this,indice, precio, precio::AJUSTAR, descripcion));
            break;
        }
        default:
            return false;
            break;
        }       
        return true;
    }
    else
    {
        return false;
    }
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
            factor=1;//1.1;//para reflejar el coste indirecto en la columna ImpPres
        }
        return QString::number(n->datonodo.LeeImportePres()*A->datoarista.LeeMedicion().LeeTotal()*factor,'f',3);
    }
}

void PrincipalModel::ActualizarDatos(const std::list<std::list<Dato> > &datosStd)
{
    //esta funcion lee la lista de datos generada por Obra::LeeDescompuesto()la cual almacena datos
    //QString, float o int y las pasa a QString. formateando los float para su correcta visualizacion
    //en la tabla. El formateo de los float se hace desde aqui porque hay que annadir la primera linea a la
    //cabecera, aunque hubiera sido mas correcto hacerlo desde el delegado
    datos.clear();
    QList<DatoCelda>lineaDatos;
    DatoCelda datoC;
    for (auto it1 = datosStd.begin(); it1 != datosStd.end();++it1)
    {
        for (auto it2 = it1->begin();it2!=it1->end();++it2)
        {
            if (it2->dato.etipodato==datocelda::INT)
            {
                datoC.valor=QString::number(it2->dato.datoNumero);
            }
            else if (it2->dato.etipodato==datocelda::NUMERO)//aqui formateo el numero a QString
            {
                datoC.valor= locale.toString(it2->dato.datoNumero,'f',FactorRedondeoVisualizacion);
            }
            else //TEXTO
            {
                 datoC.valor=it2->dato.datoTexto;
            }
            datoC.color=Colores[it2->color];
            lineaDatos.append(datoC);
            qDebug()<<"dato: "<<datoC.valor<<"--"<<datoC.color;
        }
        datos.append(lineaDatos);
        lineaDatos.clear();
    }
    for(int i=0; i<datos.at(0).length(); i++)
    {
        datos[0][i].valor.prepend(LeyendasCabecera[i]);
    }
}

QColor PrincipalModel::LeeColor(int fila, int columna)
{
    if (fila>datos.size()-1)
    {
        return Qt::black;
    }
    else
    {
        return datos.at(fila).at(columna).color;
    }
}

QString PrincipalModel::LeeColorS(int i, int j)
{
    if (LeeColor(i,j)==Qt::magenta)
    {
        return "MAGENTA";
    }
    else if (LeeColor(i,j)==Qt::black)
    {
        return "NEGRO";
    }
    else
        return "NUSE";
}

bool PrincipalModel::HayListaDatos()
{
    return datos.size()>1;//mayor que 1 porque 1 es para la cabecera
}

void PrincipalModel::emitDataChanged(const QModelIndex &index)
{
     emit dataChanged(index, index);
}
