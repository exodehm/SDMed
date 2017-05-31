 #include "filter.h"

Filter::Filter(QObject *parent) : QObject(parent) {}

bool Filter::eventFilter(QObject *obj, QEvent* event)
{
    TablaBase* table = dynamic_cast<TablaBase*>(obj);
    if( !table ) return false;
    if (event->type() == QEvent::KeyPress)
    {
        QModelIndex indice = table->currentIndex();
        QKeyEvent *ke =static_cast<QKeyEvent*>(event);
        switch (ke->key())
        {        
        case (Qt::Key_Delete):
        {
            if (table->selectionModel()->isRowSelected(indice.row(),QModelIndex()))//si hay alguna fila seleccionada
            {
                //table->model()->removeRows(table->selectionModel()->selectedRows().first().row(),table->selectionModel()->selectedRows().size());
                table->setUpdatesEnabled(false);
                QModelIndexList indexes = table->selectionModel()->selectedIndexes();
                QList<int> listaIndices;
                foreach (QModelIndex i, indexes)
                {
                    if (!listaIndices.contains(i.row()))
                        listaIndices.prepend(i.row());
                }
                foreach (int i, listaIndices)
                {
                    table->model()->removeRow(i);
                    qDebug()<<i;
                }
                table->setUpdatesEnabled(true);
            }
            else
            {
                table->model()->setData(table->currentIndex(),"",Qt::EditRole);//solo si hay una celda seleccionada
            }
            return true;
            break;
        }
        case (Qt::Key_Tab):
        {
            int col=indice.column();
            col++;
            while (table->columnaBloqueada(col) || table->isColumnHidden(col))
            {
                col++;
                qDebug()<<"Columna: "<<col;
            }
            QModelIndex ind;
            if (col>table->limiteDerecho)
            {
                if (indice.row()==table->model()->rowCount(QModelIndex())-1)
                {
                    table->model()->insertRow(table->model()->rowCount(QModelIndex()));
                    ind = table->model()->index(indice.row()+1,table->limiteIzquierdo);
                }
                else
                {
                    col=table->limiteIzquierdo;
                    while (table->columnaBloqueada(col) || table->isColumnHidden(col))
                    {
                        col++;
                    }
                    ind = table->model()->index(indice.row()+1,col);
                }
            }
            else
            {
                ind = table->model()->index(indice.row(),col);
            }
            table->setCurrentIndex(ind);
            emit table->CambiaFila(ind);
            return true;
            break;
        }
        case (Qt::Key_Backtab):
        {
            int col=indice.column();
            col--;
            while (table->columnaBloqueada(col) || table->isColumnHidden(col))
            {
                col--;
            }
            QModelIndex ind;
            if (col<table->limiteIzquierdo)
            {
                if (indice.row()==0)
                {                   
                    col=0;
                    while (table->columnaBloqueada(col) || table->isColumnHidden(col))
                    {
                        col++;
                    }
                    ind = table->model()->index(0,col);
                }
                else
                {
                    col=table->limiteDerecho;
                    while (table->columnaBloqueada(col) || table->isColumnHidden(col))
                    {
                        col--;
                    }
                    ind = table->model()->index(indice.row()-1,col);
                }
            }
            else
            {
                ind = table->model()->index(indice.row(),col);
            }
            table->setCurrentIndex(ind);
            emit table->CambiaFila(ind);
            return true;
            break;
        }
        case (Qt::Key_Up):
        {
            if (indice.row()>0)//si estoy en la segunda fila o mas
            {
                //QModelIndex ind = table->model()->index(indice.row()-1,indice.column(), QModelIndex());
                QModelIndex ind = table->model()->index(indice.row()-1,indice.column(), QModelIndex());
                qDebug()<<"Fila: "<<ind.row()<<" - Columna: "<<ind.column();
                emit table->CambiaFila(ind);
                table->setCurrentIndex(ind);
                return true;
            }
        }
        case (Qt::Key_Down):
        {
            if (indice.row() == table->model()->rowCount(QModelIndex())-1)
            {
                table->model()->insertRow(table->model()->rowCount(QModelIndex()));
                QModelIndex ind = table->model()->index(indice.row()+1,indice.column(), QModelIndex());
                table->setCurrentIndex(ind);
                return true;
            }
            else
            {
                QModelIndex ind = table->model()->index(indice.row()+1,indice.column(), QModelIndex());
                qDebug()<<"Fila: "<<ind.row()<<" - Columna: "<<ind.column();
                emit table->CambiaFila(ind);
                table->setCurrentIndex(ind);
                return true;
            }
            break;
        }
        case (Qt::Key_Right):
        {
            int col=indice.column();
            col++;
            while (table->columnaBloqueada(col) || table->isColumnHidden(col))
            {
                col++;
            }            
            if (col>table->limiteDerecho)
            {
                col--;
                while (table->columnaBloqueada(col) || table->isColumnHidden(col))
                {
                    col--;
                }                
            }
            QModelIndex ind = table->model()->index(indice.row(),col);
            emit table->CambiaFila(ind);
            table->setCurrentIndex(ind);
            return true;
            break;
        }
        case (Qt::Key_Left):
        {
            int col=indice.column();
            col--;
            while (table->columnaBloqueada(col) || table->isColumnHidden(col))
            {
                col--;
            }            
            if (col<table->limiteIzquierdo)
            {
                col++;
                while (table->columnaBloqueada(col) || table->isColumnHidden(col))
                {
                    col++;
                }                
            }
            QModelIndex ind = table->model()->index(indice.row(),col);
            emit table->CambiaFila(ind);
            table->setCurrentIndex(ind);
            return true;
            break;
        }
        case (Qt::Key_F5):
        {
            {
                qDebug()<<table->selectionModel()->selectedRows().size();
                //table->model()->insertRows(indice.row(),table->selectionModel()->selectedRows().size());
                table->model()->insertRow(table->currentIndex().row());
                QModelIndex ind = table->model()->index(indice.row(),0);
                table->setCurrentIndex(ind);
                return true;
            }
            break;
        }        
        case (Qt::Key_C):
        {
            qDebug()<<"Copiandiki";
            break;
        }
        default:
        {
            return false;
            break;
        }
        }        
    }
    return false;
}

