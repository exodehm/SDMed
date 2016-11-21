#ifndef DATOS_H
#define DATOS_H

#include <list>
#include <utility>

#include "Fecha.h"
#include "Concepto.h"

struct Datos_generales
{
    std::string Raiz;
    std::string Nombre;
    std::string LibDenominacion;
    Concepto::Divisas Divisa;
    std::string Direccion;
    std::string Ciudad;
    std::string Provincia;
    char CPostal[6];
    std::string Pais;
    std::string Comentario1;
    std::string Comentario2;
    std::string Comentario3;
    std::string Comentario4;
    char Telefono1[10];
    char Telefono2[10];
    char Fax[10];
    std::string correo_e;    
};

struct Datos_Tecnicos
{
    float SupTotal;
    float SupRasante;
    float SupPlanta;
    float SupSolar;
    float ValorSolar;
    int NumPisos;
    int FormulaRevision;
    enum TipoFormula {Privada, Oficial};
    enum Zonaformula {Canarias,Peninsula};
    char Tipo[4];
};

struct Datos_Personales
{
    char PryEncabezamiento[64];
    char PryNombre1[64];
    char PryNombre2[64];
    char PryDireccion[64];
    char PryCiudad[32];
    char PryProvincia[32];
    char CPostal[6];
    char Pais[32];
    char Telefono1[10];
    char Telefono2[10];
    std::string correo_e;
    char NIF[10];
};

struct Datos_registrales
{
    Fecha FecLicencia;
    Fecha FecInicioObra;
    Fecha FecFinObra;
    Fecha FecPrimeraOcupacion;
    char NIF[10];
    char LibNRC[19];
    char Tomo[19];
    char Libro[19];
    char Folio[19];
    char Finca[19];
    char LibLugarRegistro[33];
    char LibDecNotario[65];
    char LibDecProtocolo[17];
    Fecha LibDecFecha;
};

struct Porcentajes
{
    float PorGastosGenerales;
    float PorBeneficioIndustrial;
    float PorIVAEjecucion;
    float PorIVAHonorarios;
    float PorRetencionClientes;
    float PorRetencionFiscal;
    float PorHonorariosProyecto;
    float PorHonorariosDireccionObra;
    float PorHonorariosDireccionEjecucion;

    std::list<std::pair<std::string,float>> ListaPorcentajes;
    Porcentajes();

};

union tipoDato
{
    Datos_generales InfoGeneral;
    Datos_Tecnicos DatosTecnicos;
    Datos_Personales DirectorObra;
    Datos_registrales DatosRegistrales;
    Porcentajes porcentajes;
};

class Datos
{
    public:
        Datos();
        std::list<std::string>&LeeListaDeDatos();
        std::string LeeElementoListaDeDatos(int n) const;
        int TamLista();        
        virtual ~Datos();
    private:
        tipoDato DatosDeObra[8];
        std::list<std::string>ListaDeDatos;
};

#endif // DATOS_H
