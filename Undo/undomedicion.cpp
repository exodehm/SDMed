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
    obra->Posicionar(pilaAristas);//no pongo el indice porque aqui va referenciado al indice de la tabla de mediciones
    obra->EditarLineaMedicion(indice.row(), indice.column(),fValorAntiguo, sValorAntiguo);
}

void UndoMedicion::redo()
{
    qDebug()<<"Redo EditarMedicion en linea: "<<indice.row()<<" y columna: "<<indice.column();
    obra->Posicionar(pilaAristas);//no pongo el indice porque aqui va referenciado al indice de la tabla de mediciones
    obra->EditarLineaMedicion(indice.row(), indice.column(),fValorNuevo, sValorNuevo);
}

//#############################BORRAR LINEAS MEDICION#############################//

UndoBorrarLineasMedicion::UndoBorrarLineasMedicion(Obra *O, MedCertModel *M, QList<int> listaindices, QString descripcion, QUndoCommand *parent):
    obra(O),modelo(M),QUndoCommand(descripcion,parent)
{
    //para implementar el undo primero guardo la actual lista de mediciones
    //cuando hago redo borro de la lista las lineas indicadas y cuando
    //hago undo sustituyo la lista con elementos borrada por la lista original
    indices=listaindices;
    listaMedicion=obra->LeeListaMedicion(obra->AristaPadre(), MedCert::MEDICION);
    pilaAristas = obra->LeePilaAristas();
    setText(text());
}

void UndoBorrarLineasMedicion::undo()
{
    qDebug()<<"Undo Borrar Lineas Medicion";
    obra->Posicionar(pilaAristas);
    obra->borrarTodaMedicion();
    obra->PegarMedicion(0,listaMedicion);    
}

void UndoBorrarLineasMedicion::redo()
{
    qDebug()<<"Redo Borrar Lineas Medicion";
    obra->Posicionar(pilaAristas);
    foreach (int i, indices)
    {
        modelo->removeRow(i);
    }
}

//#############################INSERTAR LINEAS MEDICION#############################//

UndoInsertarLineasMedicion::UndoInsertarLineasMedicion(Obra *O, MedCertModel *M, QList<int> listaindices, QString descripcion, QUndoCommand *parent):
    obra(O),modelo(M),QUndoCommand(descripcion,parent)
{
    //para implementar el undo primero guardo la actual lista de mediciones
    //cuando hago redo inserto en la lista las lineas indicadas y cuando
    //hago undo sustituyo la lista con elementos insertados por la lista original
    indices=listaindices;
    listaMedicion=obra->LeeListaMedicion(obra->AristaPadre(), MedCert::MEDICION);
    pilaAristas = obra->LeePilaAristas();
    setText(text());
}

void UndoInsertarLineasMedicion::undo()
{
    qDebug()<<"Undo Insertar Lineas Medicion";
    obra->Posicionar(pilaAristas);
    obra->borrarTodaMedicion();
    obra->PegarMedicion(0,listaMedicion);
}

void UndoInsertarLineasMedicion::redo()
{
    qDebug()<<"Redo Insertar Lineas Medicion";
    obra->Posicionar(pilaAristas);
    //Cuando borro SI es necesaria una lista que albergue indices no correlativos, pero
    //al insertar no. No obstante uso una lista de QList<int> para mantener el constructor,
    //aunque no es lo apropiado para esta funcion.
    obra->InsertarLineasVaciasMedicion(0,indices.first(),indices.count());    
}

//#############################PEGAR LINEAS MEDICION#############################//

UndoPegarLineasMedicion::UndoPegarLineasMedicion(Obra* O, int F, const Medicion& listaM, QString descripcion, QUndoCommand* parent):
    obra(O),fila(F),QUndoCommand(descripcion,parent)
{
    //para implementar el undo guardo la lista de mediciones original
    //cuando hago redo inserto en la lista las lineas de la nueva lista a copiar y cuando
    //hago undo sustituyo la lista con elementos insertados por la lista original
    listaMedicionOriginal=obra->LeeListaMedicion(obra->AristaPadre(), MedCert::MEDICION);
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
{
    /*obra->DefinePilaAristas(pilaAristas);
    obra->DefineAristaPadre(pilaAristas.top());
    pArista aux = pilaAristas.top();
    obra->DefineNodoPadre(aux->destino);*/
}
