#ifndef DELEGADOEDITORMEDICIONES_H
#define DELEGADOEDITORMEDICIONES_H

#include <QStyledItemDelegate>
#include <QLineEdit>
#include <QKeyEvent>
#include <QDebug>

class DelegadoEditorMediciones : public QStyledItemDelegate
{
public:
    DelegadoEditorMediciones(QObject* parent=nullptr);
    QWidget * createEditor(QWidget * parent, const QStyleOptionViewItem&option, const QModelIndex&index) const;
    void setEditorData(QWidget * editor, const QModelIndex&index)const;
    void setModelData(QWidget * editor, QAbstractItemModel * model, const QModelIndex&index) const;
    bool eventFilter(QObject *obj, QEvent* event);
};

#endif // DELEGADOEDITORMEDICIONES_H
