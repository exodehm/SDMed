#include "undomedicion.h"

UndoMedicion::UndoMedicion(Obra* O, MedCertModel* M,  QModelIndex I,
                           QVariant D, QString descripcion, QUndoCommand* parent):
    obra(O),modelo(M), indice(I), datoNuevo(D),QUndoCommand(descripcion,parent)
{

    pilaAristas = obra->LeePilaAristas();
    datoAntiguo = indice.data();
    if (indice.column()==tipoColumna::COMENTARIO || indice.column()==tipoColumna::FORMULA)
    {
        fValorAntiguo=0;
        fValorNuevo=0;
        sValorNuevo=datoNuevo.toString();
        sValorAntiguo=datoAntiguo.toString();

    }
    else if (indice.column()==tipoColumna::N || indice.column()==tipoColumna::LONGITUD || indice.column()==tipoColumna::ANCHURA || indice.column()==tipoColumna::ALTURA)
    {
        fValorNuevo=datoNuevo.toFloat();
        fValorAntiguo=datoAntiguo.toFloat();
        sValorNuevo="";
        sValorAntiguo="";
    } 
    setText(text());
    qDebug()<<"valor antiguo:"<<datoAntiguo.toString()<<"- valor nuevo: "<<datoNuevo.toString();
}

void UndoMedicion::undo()
{
    qDebug()<<"Undo EditarMedicion";
    Posicionar();
    obra->EditarLineaMedicion(indice.row(), indice.column(),fValorAntiguo, sValorAntiguo);
}

void UndoMedicion::redo()
{
    qDebug()<<"Redo EditarMedicion";
    Posicionar();
    obra->EditarLineaMedicion(indice.row(), indice.column(),fValorNuevo, sValorNuevo);
}

void UndoMedicion::Posicionar()
{
    obra->DefinePilaAristas(pilaAristas);
    obra->DefineAristaPadre(pilaAristas.top());
    pArista aux = pilaAristas.top();
    obra->DefineNodoPadre(aux->destino);
    //obra->PosicionarAristaActual(indice.row());
}

//#############################BORRAR LINEAS MEDICION#############################//

UndoBorrarLineasMedicion::UndoBorrarLineasMedicion(Obra *O, MedCertModel *M, QList<int> listaindices, QString descripcion, QUndoCommand *parent):
    obra(O),modelo(M),QUndoCommand(descripcion,parent)
{
    //para implementar el undo primero guardo la actual lista de mediciones
    //cuando hago redo borro de la lista las lineas indicadas y cuando
    //hago undo sustituyo la lista con elementos borrada por la lista original
    indices=listaindices;
    listaMedicion=obra->LeeListaMedicion(MedCert::MEDICION);
    pilaAristas = obra->LeePilaAristas();
    setText(text());
}

void UndoBorrarLineasMedicion::undo()
{
    qDebug()<<"Undo Borrar Lineas Medicion";
    Posicionar();
    obra->borrarTodaMedicion();
    obra->PegarMedicion(0,listaMedicion);    
}

void UndoBorrarLineasMedicion::redo()
{
    qDebug()<<"Redo Borrar Lineas Medicion";
    Posicionar();
    foreach (int i, indices)
    {
        modelo->removeRow(i);
    }
<<<<<<< HEAD
}

void UndoBorrarLineasMedicion::Posicionar()
{
    obra->DefinePilaAristas(pilaAristas);
    obra->DefineAristaPadre(pilaAristas.top());
    pArista aux = pilaAristas.top();
    obra->DefineNodoPadre(aux->destino);
}

//#############################INSERTAR LINEAS MEDICION#############################//

UndoInsertarLineasMedicion::UndoInsertarLineasMedicion(Obra *O, MedCertModel *M, QList<int> listaindices, QString descripcion, QUndoCommand *parent):
    obra(O),modelo(M),QUndoCommand(descripcion,parent)
{
    //para implementar el undo primero guardo la actual lista de mediciones
    //cuando hago redo inserto en la lista las lineas indicadas y cuando
    //hago undo sustituyo la lista con elementos insertados por la lista original
    indices=listaindices;
    listaMedicion=obra->LeeListaMedicion(MedCert::MEDICION);
    pilaAristas = obra->LeePilaAristas();
    setText(text());
}

void UndoInsertarLineasMedicion::undo()
{
    qDebug()<<"Undo Insertar Lineas Medicion";
    Posicionar();
    obra->borrarTodaMedicion();
    obra->PegarMedicion(0,listaMedicion);
}

void UndoInsertarLineasMedicion::redo()
{
    qDebug()<<"Redo Insertar Lineas Medicion";

    Posicionar();
    //Cuando borro SI es necesaria una lista que albergue indices no correlativos, pero
    //al insertar no. No obstante uso una lista de QList<int> para mantener el constructor,
    //aunque no es lo apropiado para esta funcion.
    obra->InsertarLineasVaciasMedicion(0,indices.first(),indices.count());
}

void UndoInsertarLineasMedicion::Posicionar()
{
    obra->DefinePilaAristas(pilaAristas);
    obra->DefineAristaPadre(pilaAristas.top());
    pArista aux = pilaAristas.top();
    obra->DefineNodoPadre(aux->destino);
}

//#############################PEGAR LINEAS MEDICION#############################//

UndoPegarLineasMedicion::UndoPegarLineasMedicion(Obra* O, int F, const Medicion& listaM, QString descripcion, QUndoCommand* parent):
    obra(O),fila(F),QUndoCommand(descripcion,parent)
{
    //para implementar el undo guardo la lista de mediciones original
    //cuando hago redo inserto en la lista las lineas de la nueva lista a copiar y cuando
    //hago undo sustituyo la lista con elementos insertados por la lista original
    listaMedicionOriginal=obra->LeeListaMedicion(MedCert::MEDICION);
    listaMedicionACopiar = listaM;
    pilaAristas = obra->LeePilaAristas();
    setText(text());
}

void UndoPegarLineasMedicion::undo()
{
    qDebug()<<"Undo Pegar Lineas Medicion";
    Posicionar();
    obra->borrarTodaMedicion();
    obra->PegarMedicion(0,listaMedicionOriginal);
}

void UndoPegarLineasMedicion::redo()
{
    qDebug()<<"Redo Pegar Lineas Medicion";
    Posicionar();
    obra->PegarMedicion(fila,listaMedicionACopiar);//indice.row() es la fila de la tabla a partir de la cual pego
}

void UndoPegarLineasMedicion::Posicionar()
=======
}

void UndoBorrarLineasMedicion::Posicionar()
{
    obra->DefinePilaAristas(pilaAristas);
    obra->DefineAristaPadre(pilaAristas.top());
    pArista aux = pilaAristas.top();
    obra->DefineNodoPadre(aux->destino);
}

//#############################INSERTAR LINEAS MEDICION#############################//

UndoInsertarLineasMedicion::UndoInsertarLineasMedicion(Obra *O, MedCertModel *M, QList<int> listaindices, QString descripcion, QUndoCommand *parent):
    obra(O),modelo(M),QUndoCommand(descripcion,parent)
{
    //para implementar el undo primero guardo la actual lista de mediciones
    //cuando hago redo inserto en la lista las lineas indicadas y cuando
    //hago undo sustituyo la lista con elementos insertados por la lista original
    indices=listaindices;
    listaMedicion=obra->LeeListaMedicion(MedCert::MEDICION);
    pilaAristas = obra->LeePilaAristas();
    setText(text());
}

void UndoInsertarLineasMedicion::undo()
{
    qDebug()<<"Undo Insertar Lineas Medicion";
    Posicionar();
    obra->borrarTodaMedicion();
    obra->PegarMedicion(0,listaMedicion);
}

void UndoInsertarLineasMedicion::redo()
{
    qDebug()<<"Redo Insertar Lineas Medicion";

    Posicionar();
    //Cuando borro SI es necesaria una lista que albergue indices no correlativos, pero
    //al insertar no. No obstante uso una lista de QList<int> para mantener el constructor,
    //aunque no es lo apropiado para esta funcion.
    obra->InsertarLineasVaciasMedicion(0,indices.first(),indices.count());
}

void UndoInsertarLineasMedicion::Posicionar()
>>>>>>> cc4eadfa63af172a3d2c2e2ffd0a5dfaa8a7d9c0
{
    obra->DefinePilaAristas(pilaAristas);
    obra->DefineAristaPadre(pilaAristas.top());
    pArista aux = pilaAristas.top();
    obra->DefineNodoPadre(aux->destino);
}
