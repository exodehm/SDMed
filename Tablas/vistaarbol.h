#ifndef VISTAARBOL_H
#define VISTAARBOL_H

#include <QTreeView>

#include "./Modelos/TreeModel.h"
#include "./Delegados/delegadoarbol.h"
#include "./defs.h"


class VistaArbol : public QTreeView
{
    Q_OBJECT
public:
    VistaArbol(QWidget *parent=nullptr);

private:
    //TreeModel* modelo;// = new TreeModel(O);
    DelegadoArbol* delegado;
};

#endif // VISTAARBOL_H
