#include "../include/Certificacion.h"

Certificacion::Certificacion(){}

Certificacion::~Certificacion(){}

bool Certificacion::anadir(Fecha fecha)
{
    Fecha fecha2 = verFechaCertificacion(certificaciones.size()-1);
    if (tamanno() == 0 || fecha > fecha2)
    {
        cert nuevacertificacion;
        nuevacertificacion.first=true;
        nuevacertificacion.second=fecha;
        if (!certificaciones.empty())//si no es la primera insercion
        {
            for (auto it=certificaciones.begin(); it!=certificaciones.end(); ++it)
            {
                (*it).first=false;//poner a 0 las anteriores
            }
        }
        certificaciones.push_back(nuevacertificacion);
        return true;
    }
    return false;
}

void Certificacion::eliminar(unsigned int posicion)
{
    if (posicion<=certificaciones.size())
    {
        auto it=certificaciones.begin();
        advance(it,posicion-1);
        certificaciones.erase(it);
    }
}

int Certificacion::tamanno()
{
    return certificaciones.size();
}

unsigned int Certificacion::verCertificacionActual()
{
    int n=1;
    for (auto it=certificaciones.begin(); it!=certificaciones.end(); ++it)
    {
        if ((*it).first==true)
        {
            return n;
        }
        n++;
    }
    return 0;
}

Fecha Certificacion::verFechaCertificacionActual()
{
    for (auto it=certificaciones.begin(); it!=certificaciones.end(); ++it)
    {
        if ((*it).first==true)
        {
            return (*it).second;
        }
    }
    return 0;
}

Fecha Certificacion::verFechaCertificacion(int numCertificacion)
{
    auto it =certificaciones.begin();
    std::advance(it,numCertificacion);
    return it->second;
}

void Certificacion::cambiarCertificacionActual(unsigned int actual)
{
    auto it=certificaciones.begin();
    if (actual<=certificaciones.size())
    {
        std::cout<<"Total certificaciones: "<<certificaciones.size()<<std::endl;
        for (it=certificaciones.begin(); it!=certificaciones.end(); ++it)
        {
            (*it).first=false;//pongo a 0
        }
        it=certificaciones.begin();
        //advance(it,actual-1);
        advance(it,actual);
        (*it).first=true;
    }
}

void Certificacion::cambiarFecha(std::string nuevafecha)
{
    Fecha Nueva(nuevafecha);
    auto it=certificaciones.begin();
    advance(it,verCertificacionActual()-1);
    (*it).second=Nueva;
}

std::ostream& operator <<(std::ostream& os, const Certificacion& C)
{
    for (auto it=C.certificaciones.begin(); it!=C.certificaciones.end(); ++it)
    {
        os<<(*it).first<<" - "<<(*it).second<<std::endl;
    }
}
