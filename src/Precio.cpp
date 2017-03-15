#include "../include/Precio.h"
#include <iostream>

Precio::Precio(float P):bloqueado(false)
{
    precio[NORMAL]=P;
    precio[BLOQUEADO]=0;
    /*std::cout<<"Constructor Precio "<<std::endl;*/
}

Precio::Precio (const Precio& P)
{
    precio[NORMAL]=P.precio[NORMAL];
    precio[BLOQUEADO]=P.precio[BLOQUEADO];
    bloqueado=P.bloqueado;
    //std::cout<<"Constructor Precio Copia "<<std::endl;
}

Precio::~Precio()
{
    //dtor
}

bool Precio::EsBloqueado() const {return bloqueado;}

float Precio::LeePrecio() const
{
    if (bloqueado==true)
    {
        return precio[BLOQUEADO];
    }
    return precio[NORMAL];
}

void Precio::EscribePrecio (float p)
{
    if (bloqueado==true)
    {
        precio[BLOQUEADO]=p;
    }
    else
    {
        precio[NORMAL]=p;
    }
}

void Precio::Bloquear(){bloqueado=true;}
void Precio::Desbloquear(){bloqueado=false;}

Precio& Precio::operator=(const Precio& P)
{
    if (this!=&P)
    {
        precio[NORMAL]=P.precio[NORMAL];
        precio[BLOQUEADO]=P.precio[BLOQUEADO];
        bloqueado=P.bloqueado;
    }
    return *this;
}
