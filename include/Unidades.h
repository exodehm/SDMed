#ifndef UNIDADES_H
#define UNIDADES_H

#include <string>
#include <cstring>
#include <iostream>


class Unidad
{
    public:
        Unidad();
        void EscribeUd(int n);
        void EscribeUd(std::string ud);
        std::string LeeUd() const;
        std::string LeeUd(int n) const;
        int LeeNumUd(std::string ud) const;
        virtual ~Unidad();
        Unidad& operator=(const Unidad& Ref);

        enum ListaUnidades{sinUnidad,m,m2,m3,kg,km,t,l,hora,d,a,Ha,cm3,cm2,dm3,u,mu,cu,mes,porcentaje};

    private:
        char ListaUnidades[20][4];
        char unidad[4];
        int nUnidades;
};

#endif // UNIDADES_H

