#include "undoeditarprecio.h"

UndoEditarPrecio::UndoEditarPrecio(Obra* O, PrincipalModel* M,  QModelIndex I, float D, int A, QString descripcion, QUndoCommand* parent):
    obra(O),modelo(M),indice(I),precioNuevo(D), accion(A), QUndoCommand(descripcion,parent)
{
    precioAntiguo = indice.data().toFloat() ;
    fila= indice.row();
    columna=indice.column();
    setText(descripcion);
}

void UndoEditarPrecio::undo()
{
    qDebug()<<"UndoEditarPrecio";
    switch (accion)
    {
    case precio::MODIFICAR:
        qDebug()<<"modificar undo";
        obra->EditarPrecio(precioAntiguo);
        break;
    case precio::SUPRIMIR:
    {
        qDebug()<<"suprimir undo";
        obra->BajarNivel();
        obra->Pegar(grafoaux);
        obra->SubirNivel();
        break;
    }
    case precio::BLOQUEAR:
        qDebug()<<"bloquear undo";
        obra->DesbloquearPrecio();
        break;
    case precio::AJUSTAR:
        qDebug()<<"Ajustar undo";
        break;
    default:
        break;
    }
    modelo->emitDataChanged(indice);
    modelo->ActualizarDatos();
    modelo->layoutChanged();
}

void UndoEditarPrecio::redo()
{
    qDebug()<<"RedoEditarPrecio";
    switch (accion) {
    case precio::MODIFICAR:
        qDebug()<<"modificar undo";
        obra->EditarPrecio(precioNuevo);
        break;
    case precio::SUPRIMIR:
    {
        qDebug()<<"suprimir undo";
        qDebug()<<obra->AristaActual()->destino->datonodo.LeeCodigo();
        grafoaux = obra->GrafoAPartirDeNodo(obra->AristaActual()->destino);
        obra->SuprimirDescomposicion();
        obra->EditarPrecio(precioNuevo);
        break;
    }
    case precio::BLOQUEAR:
        qDebug()<<"bloquear undo";
        obra->BloquearPrecio(precioNuevo);
        break;
    case precio::AJUSTAR:
        qDebug()<<"Ajustar undo";
        break;
    default:
        break;
    }
    modelo->emitDataChanged(indice);
    modelo->ActualizarDatos();
    modelo->layoutChanged();
}
