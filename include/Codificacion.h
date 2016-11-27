#ifndef CODIFICACION_H
#define CODIFICACION_H
#include <string>
#include <list>

class Codificacion
{
private:
    int Nat;
    int Cuadro;
    std::list<std::string>ListaCodificacion;

public:
    enum CuadroDePrecios {Nulo, PREOC_EOCE,IVE_CAM, ITEC,FCBP,ARAGON,ARCOS,PRESTO_CENTRO,EK,CHILE,BPCCL,AGRO,EMEDOS,FITC,FECE};
    enum Naturaleza{Sin_clasificar, Mano_de_Obra, Maquinaria, Materiales, Comp_residuo,Clasificacion_residuo, Capitulo, Partida};
    //constructor
    Codificacion(int n=PREOC_EOCE);
    void CambiarCodificacion(int n);
    int AsignarNaturalezaSegunCuadro (std::string codigo);
    int LeeNat()const;
    const std::string LeeNombre(int n) const;
    int LeeTam() const;
};

#endif // CODIFICACION_H
