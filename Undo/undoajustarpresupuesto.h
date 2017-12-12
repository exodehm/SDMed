#ifndef UNDOAJUSTARPRESUPUESTO_H
#define UNDOAJUSTARPRESUPUESTO_H

#include <QUndoCommand>
#include <QDebug>

#include "./include/Obra.h"


class UndoAjustarPresupuesto : public QUndoCommand
{
public:
    UndoAjustarPresupuesto(Obra* O, float cantidades[2]);

    void undo();
    void redo();

private:
    Obra* obra;
    float cantidadnueva, cantidadantigua;
};

#endif // UNDOAJUSTARPRESUPUESTO_H
