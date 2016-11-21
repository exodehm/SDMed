#ifndef CALC_H
#define CALC_H

#include <cstdlib>
#include <cstring>
#include <cmath>
#include "pila.h"
#include <string>
#include <iostream>
#include <sstream>


class Calc
{

public:

    enum OP_TIPO { PAREN_IZQ, PAREN_DER, POT, MULT, DIV, SUMA, RESTA, NEG, POS, PORC, RAIZC, MOD } TipoOperador;

    struct op_t
    {
        char simbolo;
        unsigned short int precedencia;
        OP_TIPO TipoOperador;
        bool bIzqDer;
        bool bBinario;
    };

    op_t cadena_ref[12];

    enum eSemantica {OPERANDO, OPERADOR} semantica;

    struct elemento_t
    {
        eSemantica semantica;
        union
        {
            double operando;
            op_t operador;
        } OP;
    };

    //funciones miembro
    bool esOperando (char);
    bool esParentesis (char);
    bool esOperador (char);
    elemento_t* preparaCadena (const char* cadena, int& t);
    elemento_t* pasaPostfija (elemento_t*, int& t);
    double Operar (float a, float b, char);
    void OperarUnitario (OP_TIPO, pila<double>&, double);
    double EvaluaEpostfija (elemento_t*, int t);
    const op_t* defineOperador (char c);
    bool Precedencia (const op_t&,const  op_t&);
    void InicializarArray();
    double CalcularExpresion();
    void anadirExpresion(const std::string &sExpresion);
	void anadirExpresion(const char* cExpresion);
	void quitaEspacios (char* cadena);
    /** Constructor */
    Calc();
    Calc(const std::string &sExpresion);
	Calc(const char* cExpresion);
    /**Constructor copia*/
    Calc (const Calc& Ref);
    /** Destructor */
    ~Calc();

    private:

    char* cadena;
    int tamanno;
};

#endif // CALC_H
