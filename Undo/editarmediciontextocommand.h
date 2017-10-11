#ifndef EDITARMEDICIONTEXTOCOMMAND_H
#define EDITARMEDICIONTEXTOCOMMAND_H

#include <QUndoCommand>
#include <QModelIndex>
#include <QDebug>

#include "./include/Obra.h"
#include "./Modelos/MedCertModel.h"

class MedCertModel;


class EditarMedicionTextoCommand : public QUndoCommand
{
public:
    EditarMedicionTextoCommand(Obra* O, MedCertModel* M,  QModelIndex I, QVariant V, QString descripcion, QUndoCommand* parent = nullptr);

    void undo();
    void redo();

private:

    Obra* obra;
    MedCertModel* modelo;
    int fila, columna;
    QVariant valorAntiguo;
    QVariant valorNuevo;
};

#endif // EDITARMEDICIONTEXTOCOMMAND_H
