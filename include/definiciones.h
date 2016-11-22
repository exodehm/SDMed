#ifndef DEFINICIONES_H_INCLUDED
#define DEFINICIONES_H_INCLUDED

#include <QString>

#include "Concepto.h"
#include "MedCert.h"

typedef Concepto datonodo_t;
typedef MedCert datoarista_t;

typedef nodo<datonodo_t,datoarista_t>* pNodo;
typedef arista<datoarista_t,datonodo_t>* pArista;
typedef nodo<datonodo_t,datoarista_t> t_nodo;
typedef arista<datoarista_t,datonodo_t> t_arista;

typedef QString TEXTO;



#endif // DEFINICIONES_H_INCLUDED
