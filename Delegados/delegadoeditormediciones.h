#ifndef DELEGADOEDITORMEDICIONES_H
#define DELEGADOEDITORMEDICIONES_H

//#include <QStyledItemDelegate>
#include <QLineEdit>
#include <QKeyEvent>
#include <QDebug>

#include "./delegadobase.h"

class DelegadoEditorMediciones : public DelegadoBase
{
public:
    DelegadoEditorMediciones(QObject* parent=nullptr);
    QWidget * createEditor(QWidget * parent, const QStyleOptionViewItem&option, const QModelIndex&index) const;
    void setEditorData(QWidget * editor, const QModelIndex&index)const;
    void setModelData(QWidget * editor, QAbstractItemModel * model, const QModelIndex&index) const;
};

#endif // DELEGADOEDITORMEDICIONES_H
