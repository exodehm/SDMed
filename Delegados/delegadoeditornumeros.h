#ifndef DELEGADOEDITORNUMEROS_H
#define DELEGADOEDITORNUMEROS_H

#include <QRegExp>
#include <QRegExpValidator>
#include <QPainter>

#include "./delegadobase.h"


class DelegadoEditorNumeros : public DelegadoBase
{
public:
    explicit DelegadoEditorNumeros(QObject* parent=nullptr);
    QWidget * createEditor(QWidget * parent, const QStyleOptionViewItem&option, const QModelIndex&index) const;
    void setEditorData(QWidget * editor, const QModelIndex&index)const;
    void setModelData(QWidget * editor, QAbstractItemModel * model, const QModelIndex&index) const;
    void paint( QPainter *painter,const QStyleOptionViewItem &option, const QModelIndex &index ) const;
    QSize sizeHint( const QStyleOptionViewItem &option, const QModelIndex &index ) const;
    QString displayText(const QVariant & value, const QLocale & locale) const;

private:
    QRegExp* rx;
};

#endif // DELEGADOEDITORNUMEROS_H
