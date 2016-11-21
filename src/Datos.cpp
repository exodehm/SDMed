#include "../include/Datos.h"

/*Datos::Datos()
{
    DatosDeObra[0]=InfoGeneral;

    ListaDeDatos.push_back("Datos Generales");
    ListaDeDatos.push_back("Datos Técnicos");
    ListaDeDatos.push_back("Datos Personales del Director de la Obra");
    ListaDeDatos.push_back("Datos Personales del Director de la Ejecución de la Obra");
    ListaDeDatos.push_back("Datos Personales del Promotor");
    ListaDeDatos.push_back("Datos Personales del Constructor");
    ListaDeDatos.push_back("Datos Registrales");
    ListaDeDatos.push_back("Porcentajes");
}*/

std::list<std::string>& Datos::LeeListaDeDatos()
{
    return ListaDeDatos;
}

int Datos::TamLista()
{
    return ListaDeDatos.size();
}

std::string Datos::LeeElementoListaDeDatos(int n) const
{
    auto it=ListaDeDatos.begin();
    advance(it,n);
    return *it;
}

/*Datos::~Datos()
{
    //dtor
}*/

Porcentajes::Porcentajes()
{
    PorGastosGenerales=13;
    PorBeneficioIndustrial=6;
    PorIVAEjecucion=21;
    PorIVAHonorarios=21;
    PorRetencionClientes=18;
    PorRetencionFiscal=0;
    PorHonorariosProyecto=0;
    PorHonorariosDireccionObra=0;
    PorHonorariosDireccionEjecucion=0;

    ListaPorcentajes.push_back(std::make_pair("Porcentaje de gastos generales", PorGastosGenerales));
    ListaPorcentajes.push_back(std::make_pair("Porcentaje de beneficio industrial", PorBeneficioIndustrial));
    ListaPorcentajes.push_back(std::make_pair("Porcentaje de IVA sobre ejecución material", PorIVAEjecucion));
    ListaPorcentajes.push_back(std::make_pair("Porcentaje de IVA sobre honorarios", PorIVAHonorarios));
    ListaPorcentajes.push_back(std::make_pair("Porcentaje de retención del cliente", PorRetencionClientes));
    ListaPorcentajes.push_back(std::make_pair("Porcentaje de retención fiscal(IRPF)", PorRetencionFiscal));
    ListaPorcentajes.push_back(std::make_pair("Porcentaje de honorarios de proyecto", PorHonorariosProyecto));
    ListaPorcentajes.push_back(std::make_pair("Porcentaje de honorarios dirección 1", PorHonorariosDireccionObra));
    ListaPorcentajes.push_back(std::make_pair("Porcentaje de honorarios dirección 2", PorHonorariosDireccionEjecucion));
}
