#ifndef UNDOEDITARCODIGO_H
#define UNDOEDITARCODIGO_H

#include <QUndoCommand>
#include <QDebug>

#include "../include/Obra.h"
#include "../Modelos/PrincipalModel.h"

class PrincipalModel;

class UndoEditarCodigo : public QUndoCommand
{
public:    
    UndoEditarCodigo(Obra* O, PrincipalModel* M,  QModelIndex I, QString T, QString descripcion, QUndoCommand* parent = nullptr);

    void undo();
    void redo();

private:

    Obra* obra;
    PrincipalModel* modelo;
    QModelIndex indice;
    int fila, columna;
    QString codigoNuevo;
    QString codigoAntiguo;
    int accion;
    pArista A;
};

#endif // UNDOEDITARCODIGO_H
