#ifndef UNDOEDITARPRINCIPAL_H
#define UNDOEDITARPRINCIPAL_H


#include <QUndoCommand>
#include <QModelIndex>
#include <QDebug>

#include "./include/Obra.h"
#include "./Modelos/PrincipalModel.h"


class PrincipalModel;

class UndoEditarPrincipal : public QUndoCommand
{
public:
    UndoEditarPrincipal(Obra* O, PrincipalModel* M,  QModelIndex I, QVariant D,
                            QString descripcion, QUndoCommand* parent = nullptr);

    void undo();
    void redo();
    QModelIndex LeeIndice() const;

protected:

    Obra* obra;
    PrincipalModel* modelo;
    QModelIndex indice;
    QVariant datoAntiguo, datoNuevo;
    std::stack <pArista> pilaAristas;
};

//#############################CODIGO#############################//
class UndoEditarCodigo : public UndoEditarPrincipal
{
public:
    UndoEditarCodigo(Obra* O, PrincipalModel* M,  QModelIndex I, QVariant D, QString descripcion, QUndoCommand* parent = nullptr);

    void undo();
    void redo();

private:

    int accion;
    int filaInsertar;
};

//#############################NATURALEZA#############################//
class UndoEditarNaturaleza : public UndoEditarPrincipal
{
public:
    UndoEditarNaturaleza(Obra* O, PrincipalModel* M,  QModelIndex I, QVariant D, QString descripcion, QUndoCommand* parent = nullptr);

    void undo();
    void redo();
};

//#############################UNIDAD#############################//
class UndoEditarUnidad : public UndoEditarPrincipal
{
public:
    UndoEditarUnidad(Obra* O, PrincipalModel* M,  QModelIndex I, QVariant D, QString descripcion, QUndoCommand* parent = nullptr);

    void undo();
    void redo();
};

//#############################RESUMEN#############################//
class UndoEditarResumen : public UndoEditarPrincipal
{
public:
    UndoEditarResumen(Obra* O, PrincipalModel* M,  QModelIndex I, QVariant D, QString descripcion, QUndoCommand* parent = nullptr);

    void undo();
    void redo();
};

//#############################CANTIDAD#############################//
class UndoEditarCantidad : public UndoEditarPrincipal
{
public:
    UndoEditarCantidad(Obra* O, PrincipalModel* M,  QModelIndex I, QVariant D, QString descripcion, QUndoCommand* parent = nullptr);

    void undo();
    void redo();

private:
    Medicion ListaMedicion;
    float cantidadAntigua,cantidadNueva;
};

//#############################PRECIO#############################//

class UndoEditarPrecio : public UndoEditarPrincipal
{
public:
    UndoEditarPrecio(Obra* O, PrincipalModel* M,  QModelIndex I, QVariant D, int A, QString descripcion, QUndoCommand* parent = nullptr);

    void undo();
    void redo();

private:
    int accion;
    float precioAntiguo,precioNuevo;
    std::list<std::pair<pArista,pNodo>>listanodos;
    pNodo rama;
    pArista cantidad;
};

//#############################TEXTO#############################//

class UndoEditarTexto : public UndoEditarPrincipal
{
public:
    UndoEditarTexto(Obra* O, PrincipalModel* M,  QModelIndex I, TEXTO TAntiguo, TEXTO TNuevo,  QString descripcion, QUndoCommand* parent = nullptr);

    void undo();
    void redo();

private:
    TEXTO textoantiguo, textonuevo;
};

//########################BORRAR PARTIDAS#########################//
class UndoBorrarPartidas : public UndoEditarPrincipal
{
public:
    UndoBorrarPartidas(Obra* O, PrincipalModel* M, QList<int>listaindices, QString descripcion, QUndoCommand* parent = nullptr);

    void undo();
    void redo();

protected:

    QList<int>indices, rIndices;
    Obra::ListaAristasNodos listanodos,rListanodos;
};

//########################PEGAR PARTIDAS#########################//
class UndoPegarPartidas : public UndoEditarPrincipal
{
public:
    UndoPegarPartidas(Obra* O, PrincipalModel* M, QModelIndex I, Obra::ListaAristasNodos listanodospegar, bool U, QString descripcion, QUndoCommand* parent = nullptr);

    void undo();
    void redo();

protected:

    bool ultimafila;
    QList<int>indices, rIndices;
    Obra::ListaAristasNodos listanodos,rListanodos;
};


#endif // UNDOEDITARPRINCIPAL_H
