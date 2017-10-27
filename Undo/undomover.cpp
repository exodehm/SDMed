#include "undomover.h"

UndoMover::UndoMover(int movimiento, InterfazObra *I, QString descripcion, QUndoCommand *parent):
    direccion(movimiento), instancia(I), QUndoCommand(descripcion,parent)
{
    setText(text());
}

void UndoMover::undo()
{
    qDebug()<<"Undo mover";
    instancia->ModeloTablaPrincipal()->QuitarIndicadorFilaVacia();
    instancia->PosicionarTablaP(indiceActual);
    switch(direccion)
    {
    case movimiento::ABAJO:
        instancia->LeeObra()->SubirNivel();
        break;
    case movimiento::ARRIBA:
        instancia->LeeTablaPrincipal()->clearSelection();
        instancia->LeeObra()->BajarNivel();
        break;
    case movimiento::DERECHA:
        instancia->LeeObra()->Anterior();
        break;
    case movimiento::IZQUIERDA:
        instancia->LeeObra()->Siguiente();
        break;
    default:
        break;
    }
    instancia->RefrescarVista(QModelIndex(),QModelIndex());
    indiceActual= instancia->ModeloTablaPrincipal()->index(posicion,0);
    instancia->LeeTablaPrincipal()->setCurrentIndex(indiceActual);
}

void UndoMover::redo()
{
    qDebug()<<"Redo mover";   
    //instancia->PosicionarTablaP(indiceActual);
    switch(direccion)
    {
    case movimiento::ABAJO:
        instancia->LeeObra()->BajarNivel();
        break;
    case movimiento::ARRIBA:
        instancia->LeeTablaPrincipal()->clearSelection();
        posicion = instancia->LeeObra()->SubirNivel();
        break;
    case movimiento::DERECHA:
        instancia->LeeObra()->Siguiente();
        break;
    case movimiento::IZQUIERDA:
        instancia->LeeObra()->Anterior();
        break;
    default:
        break;
    }
    instancia->ModeloTablaPrincipal()->QuitarIndicadorFilaVacia();    
    instancia->RefrescarVista(QModelIndex(),QModelIndex());
    indiceActual= instancia->ModeloTablaPrincipal()->index(posicion,0);
    instancia->LeeTablaPrincipal()->setCurrentIndex(indiceActual);
}

