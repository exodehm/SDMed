#ifndef EDITARMEDICIONTEXTOCOMMAND_H
#define EDITARMEDICIONTEXTOCOMMAND_H

#include <QUndoCommand>
#include <QDebug>


class EditarMedicionTextoCommand : public QUndoCommand
{
public:
    EditarMedicionTextoCommand(QString descripcion, QUndoCommand* parent = nullptr);

    void undo();
    void redo();
};

#endif // EDITARMEDICIONTEXTOCOMMAND_H

//CambiaValorCommand(const QModelIndex &indiceAnterior, const QModelIndex &indiceActual, const QVariant &value, MiModel* m, );

