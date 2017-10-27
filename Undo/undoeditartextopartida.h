#ifndef UNDOEDITARTEXTOPARTIDA_H
#define UNDOEDITARTEXTOPARTIDA_H

#include <QUndoCommand>
#include <QDebug>

#include "../include/Obra.h"


class UndoEditarTextoPartida : public QUndoCommand
{
public:
    UndoEditarTextoPartida(Obra* O, QString descripcion, QUndoCommand* parent = nullptr);

    void undo();
    void redo();

private:

    Obra* obra;
    TEXTO textoantiguo;
    TEXTO textonuevo;
};

#endif // UNDOEDITARTEXTOPARTIDA_H
