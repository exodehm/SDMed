#include "delegadobase.h"

DelegadoBase::DelegadoBase(QObject *parent):QStyledItemDelegate(parent)
{

}

bool DelegadoBase::eventFilter(QObject *obj, QEvent* event)
{
    if (event->type()==QEvent::KeyPress)
    {
        QKeyEvent* key = static_cast<QKeyEvent*>(event);
        if (key->key()==Qt::Key_Tab || key->key()==Qt::Key_Enter || key->key()==Qt::Key_Return)
        {
            QLineEdit *editor=qobject_cast<QLineEdit*>(obj);
            emit commitData(editor);
            emit closeEditor(editor, QStyledItemDelegate::NoHint);
        }
        else if (key->key()==Qt::Key_Escape)
        {
             QLineEdit *editor=qobject_cast<QLineEdit*>(obj);
             emit closeEditor(editor, QStyledItemDelegate::NoHint);
        }
        else
        {
            return QObject::eventFilter(obj, event);
        }
        return false;
    }
    else
    {
        return QObject::eventFilter(obj, event);
    }
    return false;
}
