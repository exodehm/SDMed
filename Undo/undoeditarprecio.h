#ifndef UNDOEDITARPRECIO_H
#define UNDOEDITARPRECIO_H


#include <QUndoCommand>
#include <QDebug>

#include "../include/Obra.h"
#include "../Modelos/PrincipalModel.h"

class PrincipalModel;

class UndoEditarPrecio : public QUndoCommand
{
public:
    UndoEditarPrecio(Obra* O, PrincipalModel* M,  QModelIndex I, float D, int A, QString descripcion, QUndoCommand* parent = nullptr);

    void undo();
    void redo();

private:

    Obra* obra;
    PrincipalModel* modelo;
    QModelIndex indice;
    int accion;
    int fila, columna;
    float precioNuevo;
    float precioAntiguo;    
    std::list<std::pair<pArista,pNodo>>ListaNodos;
    Grafo<datonodo_t,datoarista_t>grafoaux;    
};

#endif // UNDOEDITARPRECIO_H
