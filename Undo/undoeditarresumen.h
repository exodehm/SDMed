#ifndef UNDOEDITARRESUMEN_H
#define UNDOEDITARRESUMEN_H

#include <QUndoCommand>
#include <QDebug>

#include "../include/Obra.h"
#include "../Modelos/PrincipalModel.h"

class PrincipalModel;

class UndoEditarResumen : public QUndoCommand
{
public:
    UndoEditarResumen(Obra* O, PrincipalModel* M,  QModelIndex I, QString T, QString descripcion, QUndoCommand* parent = nullptr);

    void undo();
    void redo();

private:

    Obra* obra;
    PrincipalModel* modelo;
    QModelIndex indice;
    int fila, columna;
    QString resumenNuevo;
    QString resumenAntiguo;
};

#endif // UNDOEDITARRESUMEN_H
