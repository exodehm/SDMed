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
    cabecera= this->horizontalHeader();
    dlgEM = new DelegadoEditorMediciones;
    dlgPS = new DelegadosParcialesSubtotales;
    dlgCB =  new DelegadoColumnasBloqueadas;

    setItemDelegateForColumn(tipoColumna::N,dlgEM);
    setItemDelegateForColumn(tipoColumna::COMENTARIO,dlgEM);
    setItemDelegateForColumn(tipoColumna::LONGITUD,dlgEM);
    setItemDelegateForColumn(tipoColumna::ANCHURA,dlgEM);
    setItemDelegateForColumn(tipoColumna::ALTURA,dlgEM);
    setItemDelegateForColumn(tipoColumna::PARCIAL,dlgPS);
    setItemDelegateForColumn(tipoColumna::SUBTOTAL,dlgPS);
    setItemDelegateForColumn(tipoColumna::FASE,dlgCB);
    setItemDelegateForColumn(tipoColumna::ID,dlgCB);

    installEventFilter(this);
    QObject::connect(cabecera, SIGNAL(sectionClicked(int)), this,SLOT(Bloquear(int)));
}

void TablaMedCert::Bloquear(int columna)
{
    celdaBloqueada[columna]=!celdaBloqueada[columna];
    qDebug()<<"Bloqueda la columna: "<<columna;
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
            if (this->selectionModel()->isRowSelected(indice.row(),QModelIndex()))
            {
                this->model()->removeRows(selectionModel()->selectedRows().first().row(),selectionModel()->selectedRows().size());
            }
            else
            {
                this->model()->setData(this->currentIndex(),"",Qt::EditRole);
            }
            break;
        }
        case (Qt::Key_Tab):
        {
            if (indice.row() == this->model()->rowCount(QModelIndex())-1
                    && indice.column() == tipoColumna::FORMULA)
            {
                this->model()->insertRow(this->model()->rowCount(QModelIndex()));
                QModelIndex ind = this->model()->index(indice.row()+1,1);
                this->setCurrentIndex(ind);
                return true;
            }
            if (indice.column()>=tipoColumna::FORMULA)
            {
                QModelIndex ind = this->model()->index(indice.row()+1,1);
                this->setCurrentIndex(ind);
                return true;
            }
            break;
        }
        case (Qt::Key_Backtab):
        {
            if (indice.column()==1 && indice.row()>0)
            {
                QModelIndex ind = this->model()->index(indice.row()-1,tipoColumna::FORMULA);
                this->setCurrentIndex(ind);
                return true;
            }
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
        case (Qt::Key_F5):
        {
            if (indice.row()>0)
            {
                qDebug()<<selectionModel()->selectedRows().size();
                this->model()->insertRows(indice.row(),selectionModel()->selectedRows().size());
                QModelIndex ind = this->model()->index(indice.row(),indice.column(), QModelIndex());
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
