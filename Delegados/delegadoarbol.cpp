#include "delegadoarbol.h"

DelegadoArbol::DelegadoArbol(QObject *parent):QStyledItemDelegate(parent)
{
    colorFuenteCapitulo = new QColor(Qt::black);
    colorFuentePartida = new QColor(Qt::black);
    colorFuenteSimples = new QColor(Qt::darkGray);

    colorFondoCapitulo = new QBrush(QColor(173,248,238));
    colorFondoPartida = new QBrush(QColor(Qt::lightGray));
    colorFondoSimples = new QBrush(QColor(Qt::black));

    fuenteCapitulo = new QFont("Arial",11);
    fuenteCapitulo->setItalic(true);
    fuenteCapitulo->setBold(true);

    fuentePartida = new QFont("Arial",11);

    fuenteSimples = new QFont("Arial",10);


}

void DelegadoArbol::paint( QPainter *painter,const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
    if (index.isValid())
    {
        TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
        int naturaleza = item->data(tipoColumna::NATURALEZA).toInt();//columna 1 == naturaleza
        switch (naturaleza)
        {
        case Codificacion::Capitulo:
            painter->save();
            painter->setPen(colorFondoCapitulo->color());
            painter->setBrush(*colorFondoCapitulo);
            painter->drawRect(option.rect);
            painter->setPen(*colorFuenteCapitulo);
            painter->setFont(*fuenteCapitulo);
            painter->drawText(option.rect, Qt::AlignLeft | Qt::AlignVCenter,index.data().toString());
            painter->restore();
            break;
        case Codificacion::Partida:
            painter->save();
            painter->setPen(*colorFuentePartida);
            painter->setBrush(*colorFondoCapitulo);
            painter->setFont(*fuentePartida);
            painter->drawText(option.rect, Qt::AlignLeft | Qt::AlignVCenter,index.data().toString());
            painter->restore();
            break;
        default:
            painter->save();
            painter->setPen(*colorFuenteSimples);
            painter->setBrush(*colorFuenteSimples);
            painter->setFont(*fuenteSimples);
            painter->drawText(option.rect, Qt::AlignLeft | Qt::AlignVCenter,index.data().toString());
            painter->restore();
            break;
        }
    }
    else
        QStyledItemDelegate::paint(painter,option,index);
}
