#include "../include/Unidades.h"

Unidad::Unidad()
{
   strcpy(ListaUnidades[0],"");
   strcpy(ListaUnidades[1],"m.");
   strcpy(ListaUnidades[2],"m2");
   strcpy(ListaUnidades[3],"m3");
   strcpy(ListaUnidades[4],"kg");
   strcpy(ListaUnidades[5],"km");
   strcpy(ListaUnidades[6],"t");
   strcpy(ListaUnidades[7],"l");
   strcpy(ListaUnidades[8],"h.");
   strcpy(ListaUnidades[9],"d");
   strcpy(ListaUnidades[10],"a");
   strcpy(ListaUnidades[11],"Ha");
   strcpy(ListaUnidades[12],"cm3");
   strcpy(ListaUnidades[13],"cm2");
   strcpy(ListaUnidades[14],"dm3");
   strcpy(ListaUnidades[15],"ud");
   strcpy(ListaUnidades[16],"mu");
   strcpy(ListaUnidades[17],"cu");
   strcpy(ListaUnidades[18],"mes");
   strcpy(ListaUnidades[19],"%");

   strcpy(unidad,ListaUnidades[0]);

   nUnidades = sizeof(ListaUnidades)/sizeof(unidad);
}

Unidad::~Unidad()
{
    //dtor
}

void Unidad::EscribeUd(int n)
{
    std::cout<<"escrbiendo unidad numero"<<n<<std::endl;
    strcpy(unidad,ListaUnidades[n]);
}

void Unidad::EscribeUd(std::string ud)
{
    std::cout<<"escrbiendo unidad"<<std::endl;
    strcpy(unidad,ud.c_str());
}


std::string Unidad::LeeUd() const
{
    std::string cadena(unidad);
    return cadena;
}

std::string Unidad::LeeUd(int n) const
{
    std::string u(ListaUnidades[n]);
    return u;
}

int Unidad::LeeNumUd(std::string ud) const
{
    for (int i=0;i<nUnidades;i++)
    {
        if (ud == ListaUnidades[i])
        {
            return i;
        }
    }
    return 0;
}

Unidad& Unidad::operator=(const Unidad& Ref)
{
    if (this!=&Ref)
    {
        strcpy(unidad,Ref.unidad);
    }
    return *this;
}
