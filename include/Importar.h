#ifndef IMPORTAR_H
#define IMPORTAR_H

#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <cstdlib>

#include "Obra.h"

class Importar
{
public:
    /** Default constructor */
    Importar(const char* N);
    /** Default destructor */
    ~Importar();
    virtual nodo<Concepto,Medicion>* importar ()=0;

    const char* nombreArchivo;
    Grafo<Concepto,Medicion> NuevoGrafo;
};

class ImportarBC3 : public Importar
{
    public:
    ImportarBC3(const char* N);
    nodo<Concepto,Medicion>* importar ();
    void quitarSimbolos (nodo<Concepto,Medicion>* n);
    void procesarConceptos(char* linea);
    void procesarRelaciones (char* linea);
    void procesarMediciones (char* linea);
    void procesarTexto(char* linea);
    nodo<Concepto,Medicion>* buscaNodoPorCodigo (std::string codigo);
    bool esRaiz(const std::string& S);
};

#endif // IMPORTAR_H
