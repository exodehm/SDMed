#ifndef REDONDEOS_H_INCLUDED
#define REDONDEOS_H_INCLUDED

#include <list>
#include <utility>

#include <string>

class Coeficientes
{
private:

    typedef unsigned short int factorRed;
    factorRed RedCapitulo;
    factorRed RedCantidadConceptos;
    factorRed RedOtrasCantidades;
    factorRed RedPreciosCap;
    factorRed RedPreciosPart;
    factorRed RedPrecElementales;
    factorRed RedSubtotal;
    factorRed RedLineasMedicion;
    factorRed RedSuministros;
    std::list<std::pair<std::string,factorRed> > Factores;
    //constructor
public:

    Coeficientes();
};

#endif // REDONDEOS_H_INCLUDED
