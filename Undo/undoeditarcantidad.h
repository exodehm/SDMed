#ifndef UNDOEDITARCANTIDAD_H
#define UNDOEDITARCANTIDAD_H


#include <QUndoCommand>
#include <QDebug>

#include "../include/Obra.h"
#include "../Modelos/PrincipalModel.h"

class PrincipalModel;


class UndoEditarCantidad : public QUndoCommand
{
public:
    UndoEditarCantidad(Obra* O, PrincipalModel* M,  QModelIndex I, float D, QString descripcion, QUndoCommand* parent = nullptr);

    void undo();
    void redo();

private:

    Obra* obra;
    PrincipalModel* modelo;
    QModelIndex indice;
    float cantidadNueva;
    float cantidadAntigua;
    Medicion ListaMedicion;
    pArista A;
};

#endif // UNDOEDITARCANTIDAD_H
