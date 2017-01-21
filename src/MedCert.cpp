#include "../include/MedCert.h"

MedCert::MedCert(){}

MedCert::MedCert(float cantidad)
{
    Medicion M(cantidad);
    Medicion C(cantidad);
    MC[MEDICION]=M;
    MC[CERTIFICACION]=C;
    //std::cout<<"Constructor de medcert"<<std::endl;
}

MedCert::MedCert(const MedCert& origen)
{
    MC[MEDICION]=origen.MC[MEDICION];
    MC[CERTIFICACION]=origen.MC[CERTIFICACION];
}

MedCert::~MedCert(){}

MedCert& MedCert:: operator=(const MedCert& origen)
{
    if (this!=&origen)
        {
            MC[MEDICION]=origen.MC[MEDICION];
            MC[CERTIFICACION]=origen.MC[CERTIFICACION];
        }
    return *this;
}

const Medicion& MedCert::LeeMedicion() const
{
    return MC[MEDICION];
}

const Medicion& MedCert::LeeCertificacion() const
{
    return MC[CERTIFICACION];
}

const Medicion& MedCert::LeeMedCer(int n)
{
    if (n==MEDICION || n==CERTIFICACION)
    {
        return MC[n];
    }
    else
    {
        return MC[MEDICION];
    }
}

Medicion& MedCert::ModificaMedCer(int n)
{
    if (n==MEDICION || n==CERTIFICACION)
    {
        return MC[n];
    }
    else
    {
        return MC[MEDICION];
    }
}

int MedCert::NumCertificaciones() const
{
//    return MC.size()-1;
    return -1;
}

bool MedCert::hayMedCert(int n)
{
    return MC[n].hayMedicion();
}

void MedCert::EscribeMedicion()
{
    //MC[MEDICION].Insertar();
}

void MedCert::EscribeMedicion(const Medicion& m)
{
    MC[MEDICION]=m;
}

void MedCert::EscribeCertificacion()
{
    //MC[CERTIFICACION].Insertar();
}

void MedCert::EscribeCertificacion(const Medicion& c)
{
    MC[CERTIFICACION]=c;
}

void MedCert::EscribeMedCer(int i)
{
    //MC[i].Insertar();
}

void MedCert::escribeTotalMedCer(int i, float cantidad)
{
    MC[i].EscribeTotal(cantidad);
}

void MedCert::Ver()
{
    MC[MEDICION].Ver();
}
