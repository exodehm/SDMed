#ifndef DELEGADOBASE_H
#define DELEGADOBASE_H

#include <QStyledItemDelegate>
#include <QLineEdit>
#include <QKeyEvent>
#include <QDebug>

#include "./include/Obra.h"
#include "./defs.h"

class DelegadoBase : public QStyledItemDelegate
{
    Q_OBJECT
public:

    explicit DelegadoBase(QObject* parent=nullptr);
    //void paint( QPainter *painter,const QStyleOptionViewItem &option, const QModelIndex &index ) const;
    //QSize sizeHint( const QStyleOptionViewItem &option, const QModelIndex &index ) const;
    bool eventFilter(QObject *obj, QEvent* event);

    //QString displayText(const QVariant & value, const QLocale & locale ) const;

};

#endif // DELEGADOBASE_H
