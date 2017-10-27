#ifndef UNDOMEDICION_H
#define UNDOMEDICION_H

#include <QUndoCommand>
#include <QModelIndex>
#include <QDebug>

#include "./include/Obra.h"
#include "./Modelos/MedCertModel.h"

class MedCertModel;

class UndoMedicion : public QUndoCommand
{
public:
    UndoMedicion(Obra* O, MedCertModel* M,  QModelIndex indiceAnterior, QModelIndex indiceActual,
                 QVariant dato, QString descripcion, QUndoCommand* parent = nullptr);

    void undo();
    void redo();

    int LeeFila() const;
    int LeeColumna() const;

private:

    Obra* obra;
    MedCertModel* modelo;
    QModelIndex indiceAnterior;
    QModelIndex indiceActual;
    int fila, columna;
    QVariant datoAntiguo, datoNuevo;
    float fValorAntiguo, fValorNuevo;
    TEXTO sValorAntiguo, sValorNuevo;
    bool esNuevoDato;
    int accion;
    Medicion listaMedicion;
};


#endif // UNDOMEDICION_H
