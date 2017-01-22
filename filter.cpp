#include "filter.h"

Filter::Filter(QObject *parent) : QObject(parent) {}

bool Filter::eventFilter(QObject *obj, QEvent* event)
{
    TablaMedCert* table = dynamic_cast<TablaMedCert*>(obj);
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
                table->model()->removeRows(table->selectionModel()->selectedRows().first().row(),table->selectionModel()->selectedRows().size());
                if(table->model()->rowCount(QModelIndex())==1)
                {
                    table->model()->insertRows(0,1);
                }
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
            while (table->columnaBloqueada(col+1))
            {
                col++;
            }
            col++;
            if (col>table->limiteDerecho)
            {
                if (indice.row()==table->model()->rowCount(QModelIndex())-1)
                {
                    table->model()->insertRow(table->model()->rowCount(QModelIndex()));
                    QModelIndex ind = table->model()->index(indice.row()+1,1);
                    table->setCurrentIndex(ind);
                }
                else
                {
                    QModelIndex ind = table->model()->index(indice.row()+1,1);
                    table->setCurrentIndex(ind);
                }
            }
            else
            {
                QModelIndex ind = table->model()->index(indice.row(),col);
                table->setCurrentIndex(ind);
            }
            return true;
            break;
        }
        case (Qt::Key_Backtab):
        {
            int col=indice.column();
            while (table->columnaBloqueada(col-1))
            {
                col--;
            }
            col--;
            if (col<table->limiteIzquierdo)
            {
                if (indice.row()==0)
                {
                    QModelIndex ind = table->model()->index(0,1);
                    table->setCurrentIndex(ind);
                }
                else
                {
                    int columna = table->model()->columnCount(QModelIndex())-4;
                    while (table->columnaBloqueada(columna))
                    {
                        columna--;
                    }
                    QModelIndex ind = table->model()->index(indice.row()-1,columna);
                    table->setCurrentIndex(ind);
                }
            }
            else
            {
                QModelIndex ind = table->model()->index(indice.row(),col);
                table->setCurrentIndex(ind);
            }
            return true;
            break;
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
            break;
        }
        case (Qt::Key_Right):
        {
            int col=indice.column();
            while (table->columnaBloqueada(col+1))
            {
                col++;
            }
            col++;
            if (col>table->limiteDerecho)
            {
                col=table->limiteDerecho;
            }
            QModelIndex ind = table->model()->index(indice.row(),col);
            table->setCurrentIndex(ind);
            return true;
            break;
        }
        case (Qt::Key_Left):
        {
            int col=indice.column();
            while (table->columnaBloqueada(col-1))
            {
                col--;
            }
            col--;
            if (col<table->limiteIzquierdo)
            {
                col=table->limiteIzquierdo;
            }
            QModelIndex ind = table->model()->index(indice.row(),col);
            table->setCurrentIndex(ind);
            return true;
            break;
        }
        case (Qt::Key_F5):
        {
            if (indice.row()>0)
            {
                qDebug()<<table->selectionModel()->selectedRows().size();
                table->model()->insertRows(indice.row(),table->selectionModel()->selectedRows().size());
                QModelIndex ind = table->model()->index(indice.row(),1);
                table->setCurrentIndex(ind);
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
}

