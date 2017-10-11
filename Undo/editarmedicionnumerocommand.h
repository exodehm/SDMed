#ifndef EDITARMEDICIONNUMEROCOMMAND_H
#define EDITARMEDICIONNUMEROCOMMAND_H

#include <QUndoCommand>
#include <QModelIndex>
#include <QDebug>

#include "./include/Obra.h"
#include "./Modelos/MedCertModel.h"

class MedCertModel;

class EditarMedicionNumeroCommand : public QUndoCommand
{
public:
    EditarMedicionNumeroCommand(Obra* O, MedCertModel* M,  QModelIndex I, QVariant V, QString descripcion, QUndoCommand* parent = nullptr);

    void undo();
    void redo();

private:

    Obra* obra;
    MedCertModel* modelo;
    QModelIndex indice;
    int fila, columna;    
    QVariant valorAntiguo;
    QVariant valorNuevo;
};

#endif // EDITARMEDICIONNUMEROCOMMAND_H
