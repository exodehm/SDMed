#ifndef EXPORTAR_H_INCLUDED
#define EXPORTAR_H_INCLUDED

#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
//#include <cstdlib>

class Exportar
{
    private:
    std::ofstream archivo;

    public:
    Exportar (const char* nombre);
};

class ExportarBC3:public Exportar
{
    public:
    ExportarBC3 (const char* nombre);
};



#endif // EXPORTAR_H_INCLUDED
