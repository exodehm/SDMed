#include "delegadoeditormediciones.h"

DelegadoEditorMediciones::DelegadoEditorMediciones(QObject *parent):QStyledItemDelegate(parent)
{

}

QWidget* DelegadoEditorMediciones::createEditor(QWidget * parent, const QStyleOptionViewItem&option, const QModelIndex&index) const
{
    const QAbstractItemModel * model = index.model();
    if (!model)
    {
        return QStyledItemDelegate::createEditor(parent,option, index);
    }
    QLineEdit* mieditor = new QLineEdit(parent);
    return mieditor;
}

void DelegadoEditorMediciones::setEditorData(QWidget * editor, const QModelIndex&index)const
{
    QLineEdit *mieditor=qobject_cast<QLineEdit*>(editor);
    const QAbstractItemModel *model =index.model();
    if (!mieditor|| !model)
    {
        QStyledItemDelegate::setEditorData(editor,index);
    }
    mieditor->setText(index.data().toString());
}

void DelegadoEditorMediciones::setModelData(QWidget * editor, QAbstractItemModel * model, const QModelIndex&index) const
{
    if (!index.isValid()) return;
    QLineEdit * mieditor=qobject_cast<QLineEdit * >(editor);
    if (!mieditor)
    {
        return QStyledItemDelegate::setModelData(editor, model, index);
    }
    qDebug()<<"Actualizando al modelo: "<<model->columnCount(QModelIndex())<<" con el indice: "<<index.row()<<" - "<<index.column()<<" y el dato: "<<mieditor->text();
    model->setData(index,mieditor->text(),Qt::DisplayRole);
    model->setData(index,mieditor->text(),Qt::EditRole);
}

bool DelegadoEditorMediciones::eventFilter(QObject *obj, QEvent* event)
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
