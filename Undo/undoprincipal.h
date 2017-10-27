#ifndef UNDOPRINCIPAL_H
#define UNDOPRINCIPAL_H

#include <QUndoCommand>
#include <QModelIndex>
#include <QDebug>

#include "./include/Obra.h"
#include "./Modelos/PrincipalModel.h"

class PrincipalModel;

class UndoPrincipal : public QUndoCommand
{
public:
    UndoPrincipal(Obra* O, PrincipalModel* M,  QModelIndex I, QVariant D, QString descripcion, QUndoCommand* parent = nullptr);

    void undo();
    void redo();

private:

    Obra* obra;
    PrincipalModel* modelo;
    QModelIndex indice;
    int fila, columna;
    QVariant datoNuevo;
    QVariant datoAntiguo;

};

#endif // UNDOPRINCIPAL_H
