#include "tablamedcert.h"

TablaMedCert::TablaMedCert(QWidget *parent):QTableView(parent)
{
    celdaBloqueada[0]=true;
    celdaBloqueada[7]=true;
    celdaBloqueada[8]=true;
    celdaBloqueada[9]=true;
    for (int i=1;i<7;i++)
    {
        celdaBloqueada[i]=false;
    }  
    cabecera = this->horizontalHeader();
    alturaFilas = this->verticalHeader();

    resizeColumnsToContents();
    resizeRowsToContents();

    alturaFilas->setSectionResizeMode(QHeaderView::Fixed);
    alturaFilas->setDefaultSectionSize(24);

    dlgEM = new DelegadoEditorMediciones;
    dlgPS = new DelegadosParcialesSubtotales;
    dlgCB = new DelegadoColumnasBloqueadas;
    dlgME = new DelegadoMedicionesEstandar;

    setItemDelegateForColumn(tipoColumna::N,dlgEM);
    setItemDelegateForColumn(tipoColumna::COMENTARIO,dlgEM);
    setItemDelegateForColumn(tipoColumna::LONGITUD,dlgEM);
    setItemDelegateForColumn(tipoColumna::ANCHURA,dlgEM);
    setItemDelegateForColumn(tipoColumna::ALTURA,dlgEM);    
    setItemDelegateForColumn(tipoColumna::FORMULA,dlgEM);
    setItemDelegateForColumn(tipoColumna::PARCIAL,dlgPS);
    setItemDelegateForColumn(tipoColumna::SUBTOTAL,dlgPS);
    setItemDelegateForColumn(tipoColumna::FASE,dlgCB);
    setItemDelegateForColumn(tipoColumna::ID,dlgCB);

    installEventFilter(this);
    QObject::connect(cabecera, SIGNAL(sectionClicked(int)), this,SLOT(Bloquear(int)));
}

void TablaMedCert::Bloquear(int columna)
{
    if (columna>tipoColumna::FASE && columna<tipoColumna::PARCIAL)
    {
        celdaBloqueada[columna]=!celdaBloqueada[columna];
        if (columnaBloqueada(columna))
        {
            setItemDelegateForColumn(columna,dlgCB);
        }
        else
        {
            setItemDelegateForColumn(columna,dlgEM);
        }
        clearSelection();        
    }
}

bool TablaMedCert::columnaBloqueada(int columna)
{
    return celdaBloqueada[columna];
}

bool TablaMedCert::eventFilter(QObject *watched, QEvent *e)
{
    if (e->type() == QEvent::KeyPress)
    {
        QModelIndex indice = this->currentIndex();
        QKeyEvent *ke =static_cast<QKeyEvent*>(e);
        switch (ke->key())
        {
        case (Qt::Key_Delete):
        {
            if (this->selectionModel()->isRowSelected(indice.row(),QModelIndex()))//si hay alguna fila seleccionada
            {
                this->model()->removeRows(selectionModel()->selectedRows().first().row(),selectionModel()->selectedRows().size());
                if(this->model()->rowCount(QModelIndex())==1)
                {
                    this->model()->insertRows(0,1);
                }
            }
            else
            {
                this->model()->setData(this->currentIndex(),"",Qt::EditRole);//solo si hay una celda seleccionada
            }
            return true;
            break;
        }
        case (Qt::Key_Tab):
        {
            int col=indice.column();
            while (columnaBloqueada(col+1))
            {
                col++;
            }
            col++;
            if (col>tipoColumna::FORMULA)
            {
                if (indice.row()==this->model()->rowCount(QModelIndex())-1)
                    {
                        this->model()->insertRow(this->model()->rowCount(QModelIndex()));
                        QModelIndex ind = this->model()->index(indice.row()+1,1);
                        this->setCurrentIndex(ind);                        
                    }
                else
                {
                    QModelIndex ind = this->model()->index(indice.row()+1,1);
                    this->setCurrentIndex(ind);                    
                }
            }
            else
            {
                QModelIndex ind = this->model()->index(indice.row(),col);
                this->setCurrentIndex(ind);                
            }
            return true;
            break;
        }
        case (Qt::Key_Backtab):
        {
            int col=indice.column();
            while (columnaBloqueada(col-1))
            {
                col--;
            }
            col--;
            if (col<tipoColumna::COMENTARIO)
            {
                if (indice.row()==0)
                    {
                        QModelIndex ind = this->model()->index(0,1);
                        this->setCurrentIndex(ind);
                    }
                else
                {
                    int columna = this->model()->columnCount(QModelIndex())-4;
                    while (columnaBloqueada(columna))
                    {
                        columna--;
                    }
                    QModelIndex ind = this->model()->index(indice.row()-1,columna);
                    this->setCurrentIndex(ind);
                }
            }
            else
            {
                QModelIndex ind = this->model()->index(indice.row(),col);
                this->setCurrentIndex(ind);
            }
            return true;
            break;
        }
        case (Qt::Key_Down):
        {
            if (indice.row() == this->model()->rowCount(QModelIndex())-1)
            {
                this->model()->insertRow(this->model()->rowCount(QModelIndex()));
                QModelIndex ind = this->model()->index(indice.row()+1,indice.column(), QModelIndex());
                this->setCurrentIndex(ind);
                return true;
            }
            break;
        }
        case (Qt::Key_Right):
        {
            int col=indice.column();
            while (columnaBloqueada(col+1))
            {
                col++;
            }
            col++;
            if (col>tipoColumna::FORMULA)
            {
                col=tipoColumna::FORMULA;
            }
            QModelIndex ind = this->model()->index(indice.row(),col);
            this->setCurrentIndex(ind);
            return true;
            break;
        }
        case (Qt::Key_Left):
        {
            int col=indice.column();
            while (columnaBloqueada(col-1))
            {
                col--;
            }
            col--;
            if (col<tipoColumna::COMENTARIO)
            {
                col=tipoColumna::COMENTARIO;
            }
            QModelIndex ind = this->model()->index(indice.row(),col);
            this->setCurrentIndex(ind);
            return true;
            break;
        }
        case (Qt::Key_F5):
        {
            if (indice.row()>0)
            {
                qDebug()<<selectionModel()->selectedRows().size();
                this->model()->insertRows(indice.row(),selectionModel()->selectedRows().size());
                QModelIndex ind = this->model()->index(indice.row(),1);
                this->setCurrentIndex(ind);
                return true;
            }
            break;
        }
        default:
        {
            break;
        }
        }
        return false;
    }
    return QWidget::eventFilter(watched, e);
}
