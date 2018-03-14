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
    UndoMedicion(Obra* O, MedCertModel* M,  QModelIndex I, QVariant D,
                 QString descripcion, QUndoCommand* parent = nullptr);

    void undo();
    void redo();

private:

    Obra* obra;
    MedCertModel* modelo;
    QModelIndex indice;
    QVariant datoAntiguo, datoNuevo;
    float fValorAntiguo, fValorNuevo;
    TEXTO sValorAntiguo, sValorNuevo;
    std::stack <pArista> pilaAristas;

};

//#############################BORRAR LINEAS MEDICION#############################//
class UndoBorrarLineasMedicion : public QUndoCommand
{
public:
    UndoBorrarLineasMedicion(Obra* O, MedCertModel* M,  QList<int>listaindices,
                 QString descripcion, QUndoCommand* parent = nullptr);

    void undo();
    void redo();

private:

    Obra* obra;
    MedCertModel* modelo;
    QList<int>indices;
    std::stack <pArista> pilaAristas;
    Medicion listaMedicion;
};

//#############################INSERTAR LINEAS MEDICION#############################//
class UndoInsertarLineasMedicion : public QUndoCommand
{
public:
    UndoInsertarLineasMedicion(Obra* O, MedCertModel* M,  QList<int>listaindices,
                 QString descripcion, QUndoCommand* parent = nullptr);

    void undo();
    void redo();

private:

    Obra* obra;
    MedCertModel* modelo;
    QList<int>indices;
    std::stack <pArista> pilaAristas;
    Medicion listaMedicion;
};

//#############################PEGAR LINEAS MEDICION#############################//
class UndoPegarLineasMedicion : public QUndoCommand
{
public:
    UndoPegarLineasMedicion(Obra* O, int F, const Medicion& listaM, QString descripcion, QUndoCommand* parent = nullptr);

    void undo();
    void redo();

    void Posicionar();

private:

    Obra* obra;
    int fila;
    Medicion listaMedicionOriginal, listaMedicionACopiar;
    std::stack <pArista> pilaAristas;
};

#endif // UNDOMEDICION_H
