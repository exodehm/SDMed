#ifndef NODO_H_INCLUDED
#define NODO_H_INCLUDED

#include <iostream>
#include "definiciones.h"

template <typename DATOA, typename DATON>
struct arista;//declaración previa

template <typename DATON, typename DATOA>
struct nodo
{
    DATON datonodo;
    unsigned short int nPadres;
    nodo<DATON,DATOA>* siguiente;
    arista<DATOA,DATON>* adyacente;
    //constructor
    nodo (DATON N=0, unsigned short int numPadres=0, nodo<DATON,DATOA>* s=nullptr, arista<DATOA, DATON>* a=nullptr):datonodo(N),nPadres(numPadres),siguiente(s),adyacente(a) {}
    //constructor copia
    nodo (const nodo<DATON,DATOA>& n)
    {
        std::cout<<"nodo Constructor copia"<<std::endl;
        datonodo=n.datonodo;
        nPadres=n.nPadres;
        siguiente=nullptr;
        adyacente=nullptr;
        std::list<pArista>lista_aristas;
    }
    //destructor
    ~nodo()
    {
        siguiente=nullptr;
        adyacente=nullptr;
        //borrar pila?
        //borrar datonodo?
        //std::cout<<"Destructor nodo"<<std::endl;
    }
    //operador de asignacion
    nodo& operator = (const nodo<DATON, DATOA>& n)
    {
        if (this!=&n)
        {
            datonodo=n.datonodo;
            nPadres=n.nPadres;
            siguiente=nullptr;
            adyacente=nullptr;
        }
        return *this;
    }

    void InsertarHijo(pNodo& hijo, pArista& nueva, pArista& precedente)
    {
        //std::cout<<"INSERTAR NODO"<<std::endl;
        nueva->origen=this;
        nueva->destino=hijo;

        if (!adyacente)//primera arista
        {
            //std::cout<<"primer NODO"<<std::endl;
            adyacente = nueva;
        }
        else if (!precedente)//insertar en primera posicion
        {
            //std::cout<<"primerita posicion"<<std::endl;
            nueva->siguiente=adyacente;
            adyacente->anterior=nueva;
            adyacente=nueva;
        }
        else
        {
            nueva->siguiente = precedente->siguiente;
            nueva->anterior=precedente;
            if (precedente->siguiente)
            {
                precedente->siguiente->anterior=nueva;
            }
            precedente->siguiente=nueva;
        }
        //std::cout<<"NODO INSERTADO CON EXITO"<<std::endl;
    }
};

#endif // NODO_H_INCLUDED
