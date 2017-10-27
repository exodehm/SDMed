#ifndef UNDOMOVER_H
#define UNDOMOVER_H

#include <QUndoCommand>
#include <QDebug>

#include "./include/Obra.h"
#include "./interfazobra.h"

class InterfazObra;


class UndoMover : public QUndoCommand
{
public:

    UndoMover(int movimiento, InterfazObra* I, QString descripcion, QUndoCommand* parent = nullptr);

    void undo();
    void redo();

private:
    int direccion;
    InterfazObra* instancia;
    QModelIndex indiceActual;    
    int posicion;
};

#endif // UNDOMOVER_H
