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

    void Posicionar();

protected:

    Obra* obra;
    PrincipalModel* modelo;
    QModelIndex indice;
    QVariant datoAntiguo;
    QVariant datoNuevo;
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
    std::list<std::pair<pArista,pNodo>>ListaNodos;
    Grafo<datonodo_t,datoarista_t>grafoaux;
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


#endif // UNDOEDITARPRINCIPAL_H
