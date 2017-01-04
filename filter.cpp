#include "filter.h"

Filter::Filter(QObject *parent) : QObject(parent) {}

bool Filter::eventFilter(QObject *object, QEvent *event)
{
    QTableView* table = dynamic_cast<QTableView*>(object);
    if( !table ) return false;

    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if (keyEvent->key() == Qt::Key_Tab)
        {
            QModelIndex current = table->currentIndex();
            if( current.column() != table->model()->columnCount() )
            {
                QModelIndex newIndex = table->model()->index(current.row(),current.column()+1);
                table->setCurrentIndex(newIndex);
                table->selectionModel()->select(newIndex,QItemSelectionModel::ClearAndSelect);
                return true;
            }
        }
    }
    return false;
}
