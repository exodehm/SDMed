#ifndef DELEGADOARBOL_H
#define DELEGADOARBOL_H

#include <QStyledItemDelegate>
#include <QPainter>
#include <QDebug>
#include "./Modelos/treeitem.h"
#include "./defs.h"
#include "./include/Codificacion.h"


class DelegadoArbol : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit DelegadoArbol(QObject* parent=nullptr);
    void paint( QPainter *painter,const QStyleOptionViewItem &option, const QModelIndex &index ) const;

private:
    QFont* fuenteCapitulo;
    QFont* fuentePartida;
    QFont* fuenteSimples;//materiales, maquinaria, mano de obra

    QColor* colorFuenteCapitulo;
    QColor* colorFuentePartida;
    QColor* colorFuenteSimples;

    QBrush* colorFondoCapitulo;
    QBrush* colorFondoPartida;
    QBrush* colorFondoSimples;
};

#endif // DELEGADOARBOL_H
