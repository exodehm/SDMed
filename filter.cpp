#include "filter.h"

Filter::Filter(QObject *parent) : QObject(parent) {}

bool Filter::eventFilter(QObject *obj, QEvent* event)
{
    TablaBase* tabla = qobject_cast<TablaBase*>(obj);
    if( tabla )
    {
        if (event->type() == QEvent::KeyPress)
        {
            QModelIndex indice = tabla->currentIndex();
            QKeyEvent *ke =static_cast<QKeyEvent*>(event);
            switch (ke->key())
            {
            case (Qt::Key_Delete):
            {
                if (tabla->selectionModel()->isRowSelected(indice.row(),QModelIndex()))//si hay alguna fila seleccionada
                {
                    //table->model()->removeRows(table->selectionModel()->selectedRows().first().row(),table->selectionModel()->selectedRows().size());
                    tabla->setUpdatesEnabled(false);
                    QModelIndexList indexes = tabla->selectionModel()->selectedIndexes();
                    QList<int> listaIndices;                    
                    foreach (QModelIndex i, indexes)
                    {
                        if (!listaIndices.contains(i.row()))
                            listaIndices.prepend(i.row());//pongo prepend para borrar de atras a adelante de la lista de medicion
                    }
                    qSort(listaIndices);
                    tabla->BorrarFilas(listaIndices);
                    tabla->setUpdatesEnabled(true);
                }
                else
                {
                    tabla->model()->setData(tabla->currentIndex(),"",Qt::EditRole);//solo si hay una celda seleccionada
                }
                return true;
                break;
            }
            case (Qt::Key_Tab):
            {
                int col=indice.column();
                col++;
                while (tabla->columnaBloqueada(col) || tabla->isColumnHidden(col))
                {
                    col++;
                    qDebug()<<"Columna: "<<col;
                }
                QModelIndex ind;
                if (col>tabla->limiteDerecho)
                {
                    if (indice.row()==tabla->model()->rowCount(QModelIndex())-1)
                    {
                        tabla->model()->insertRow(tabla->model()->rowCount(QModelIndex()));
                        ind = tabla->model()->index(indice.row()+1,tabla->limiteIzquierdo);
                    }
                    else
                    {
                        col=tabla->limiteIzquierdo;
                        while (tabla->columnaBloqueada(col) || tabla->isColumnHidden(col))
                        {
                            col++;
                        }
                        ind = tabla->model()->index(indice.row()+1,col);
                    }
                }
                else
                {
                    ind = tabla->model()->index(indice.row(),col);
                }
                tabla->setCurrentIndex(ind);
                emit tabla->CambiaFila(ind);
                return true;
                break;
            }
            case (Qt::Key_Backtab):
            {
                int col=indice.column();
                col--;
                while (tabla->columnaBloqueada(col) || tabla->isColumnHidden(col))
                {
                    col--;
                }
                QModelIndex ind;
                if (col<tabla->limiteIzquierdo)
                {
                    if (indice.row()==0)
                    {
                        col=0;
                        while (tabla->columnaBloqueada(col) || tabla->isColumnHidden(col))
                        {
                            col++;
                        }
                        ind = tabla->model()->index(0,col);
                    }
                    else
                    {
                        col=tabla->limiteDerecho;
                        while (tabla->columnaBloqueada(col) || tabla->isColumnHidden(col))
                        {
                            col--;
                        }
                        ind = tabla->model()->index(indice.row()-1,col);
                    }
                }
                else
                {
                    ind = tabla->model()->index(indice.row(),col);
                }
                tabla->setCurrentIndex(ind);
                emit tabla->CambiaFila(ind);
                return true;
                break;
            }
            case (Qt::Key_Up):
            {
                if (indice.row()>0)//si estoy en la segunda fila o mas
                {
                    QModelIndex ind = tabla->model()->index(indice.row()-1,indice.column());
                    qDebug()<<"Fila: "<<ind.row()<<" - Columna: "<<ind.column();
                    emit tabla->CambiaFila(ind);
                    tabla->setCurrentIndex(ind);
                    return true;
                }
                break;
            }
            case (Qt::Key_Down):
            {
                if (indice.row() == tabla->model()->rowCount(QModelIndex())-1)
                {
                    tabla->model()->insertRow(tabla->model()->rowCount(QModelIndex()));
                    QModelIndex ind = tabla->model()->index(indice.row()+1,indice.column(), QModelIndex());
                    tabla->setCurrentIndex(ind);
                    return true;
                }
                else
                {
                    QModelIndex ind = tabla->model()->index(indice.row()+1,indice.column(), QModelIndex());
                    //qDebug()<<"Fila: "<<ind.row()<<" - Columna: "<<ind.column();
                    emit tabla->CambiaFila(ind);
                    tabla->setCurrentIndex(ind);
                    return true;
                }
                break;
            }
            case (Qt::Key_Right):
            {
                int col=indice.column();
                col++;
                while (tabla->columnaBloqueada(col) || tabla->isColumnHidden(col))
                {
                    col++;
                }
                if (col>tabla->limiteDerecho)
                {
                    col--;
                    while (tabla->columnaBloqueada(col) || tabla->isColumnHidden(col))
                    {
                        col--;
                    }
                }
                QModelIndex ind = tabla->model()->index(indice.row(),col);
                emit tabla->CambiaFila(ind);
                tabla->setCurrentIndex(ind);
                return true;
                break;
            }
            case (Qt::Key_Left):
            {
                int col=indice.column();
                col--;
                while (tabla->columnaBloqueada(col) || tabla->isColumnHidden(col))
                {
                    col--;
                }
                if (col<tabla->limiteIzquierdo)
                {
                    col++;
                    while (tabla->columnaBloqueada(col) || tabla->isColumnHidden(col))
                    {
                        col++;
                    }
                }
                QModelIndex ind = tabla->model()->index(indice.row(),col);
                emit tabla->CambiaFila(ind);
                tabla->setCurrentIndex(ind);
                return true;
                break;
            }
            case (Qt::Key_F5):
            {
                {
                    qDebug()<<tabla->selectionModel()->selectedRows().size();
                    //si no hay filas seleccionadas selecciono la fila actual de la tabla
                    if (tabla->selectionModel()->selectedRows().size()==0)
                    {
                        tabla->selectRow(tabla->currentIndex().row());
                    }
                    tabla->model()->insertRows(indice.row(),tabla->selectionModel()->selectedRows().size());
                    QModelIndex ind = tabla->model()->index(indice.row(),tabla->limiteIzquierdo);
                    tabla->setCurrentIndex(ind);
                    return true;
                }
                break;
            }
            case (Qt::Key_F2):
            {
                tabla->edit(indice);
                return true;
            }
            case (Qt::Key_A)://seleccionar todo
            {
                if (ke->modifiers()==Qt::ControlModifier)
                {
                    /*if (tabla->objectName()=="TablaP")
                    {
                        emit tabla->CopiarPartidas();
                    }
                    else
                    {
                        emit tabla->CopiarMedicion();
                    }*/
                    tabla->SeleccionarTodo();
                    return true;
                }
                break;
            }
            case (Qt::Key_C)://Copiar
            {
                if (ke->modifiers()==Qt::ControlModifier)
                {
                    if (tabla->objectName()=="TablaP")
                    {
                        emit tabla->CopiarPartidas();
                    }
                    else
                    {
                        emit tabla->CopiarMedicion();
                    }
                    return true;
                }
                break;
            }
            case (Qt::Key_X)://Cortar
            {
                if (ke->modifiers()==Qt::ControlModifier)
                {
                    qDebug()<<"Cortanding";
                    return true;
                }
            }
            case (Qt::Key_V)://Pegar
            {
                if (ke->modifiers()==Qt::ControlModifier)
                {
                    if (tabla->objectName()=="TablaP")
                    {
                        emit tabla->PegarPartidas();
                    }
                    else
                    {
                        emit tabla->PegarMedicion();
                    }
                    return true;
                }
                break;
            }
            default:
            {
                return false;
                break;
            }
            }
        }
    }
    else
    {
        Editor *editor = qobject_cast<Editor*>(obj);
        if (editor)
        {
            QTextEdit* editor1 =qobject_cast<QTextEdit*>(editor->LeeEditor());
            if( editor1)
            {
                if (event->type() == QEvent::FocusOut)
                {
                    qDebug()<<"Saliendo del editor";
                    return true;
                }
            }
        }
    }
    return QObject::eventFilter(obj, event);
}
