#include "../include/AsignadorDeNaturaleza.h"


AsignadorDeNaturaleza::AsignadorDeNaturaleza(int n):Cuadro(n)
{
    Codificacion.push_back("Sin Codificacion");
    Codificacion.push_back("PREOC_EOCE");
    Codificacion.push_back("IVE_CAM");
    Codificacion.push_back("ITEC");
    Codificacion.push_back("FCBP");
    Codificacion.push_back("ARAGON");
    Codificacion.push_back("ARCOS");
    Codificacion.push_back("PRESTO_CENTRO");
    Codificacion.push_back("EK");
    Codificacion.push_back("CHILE");
    Codificacion.push_back("BPCCL");
    Codificacion.push_back("AGRO");
    Codificacion.push_back("FITC");
    Codificacion.push_back("FECE");
    Codificacion.push_back("EMEDOS");
}

const std::string AsignadorDeNaturaleza::LeeNombre(int n) const
{
    auto it=Codificacion.begin();
    advance(it,n);
    return *it;
}

int AsignadorDeNaturaleza::LeeTam() const
{
    return Codificacion.size();
}

void AsignadorDeNaturaleza::CambiarCodificacion(int n)
{
    Cuadro=n;
}

int AsignadorDeNaturaleza::AsignarNaturalezaSegunCuadro (std::string codigo)
    {
        switch (Cuadro)
            {
                case PREOC_EOCE:
                {
                    if (codigo.substr(0,3)=="U01")
                        {
                            Nat=Mano_de_Obra;
                        }
                    else if (codigo.substr(0,3)=="U02")
                        {
                            Nat=Maquinaria;
                        }
                    else if (codigo.substr(0,1)=="U")
                        {
                            Nat=Materiales;
                        }
                    else
                        {
                            Nat=Partida;
                        }
                    break;
                }
                case IVE_CAM:
                {
                    if (codigo.substr(0,2)=="MO")
                        {
                            Nat=Mano_de_Obra;
                        }
                    else if (codigo.substr(0,3)=="MMM")
                        {
                            Nat=Maquinaria;
                        }
                    else if (codigo.substr(0,1)=="P" || codigo.substr(0,1)=="M")
                        {
                            Nat=Materiales;
                        }
                    else
                    {
                        Nat=Partida;
                    }
                    break;
                }
                case ITEC:
                {
                    if (codigo.substr(0,1)=="A")
                        {
                            Nat=Mano_de_Obra;
                        }
                    else if (codigo.substr(0,1)=="C")
                        {
                            Nat=Maquinaria;
                        }
                    else if (codigo.substr(0,1)=="B")
                        {
                            Nat=Materiales;
                        }
                    else
                    {
                        Nat=Partida;
                    }
                    break;
                }
                case FCBP:
                {
                    if (codigo.substr(0,1)=="T")
                        {
                            Nat=Mano_de_Obra;
                        }
                    else if (codigo.substr(0,1)=="M")
                        {
                            Nat=Maquinaria;
                        }
                    else
                    {
                        Nat=Partida;
                    }
                    break;
                }
                case ARAGON:
                {
                    if (codigo.substr(0,3)=="u01")
                        {
                            Nat=Mano_de_Obra;
                        }
                    else if (codigo.substr(0,3)=="u02")
                        {
                            Nat=Maquinaria;
                        }
                    else if (codigo.substr(0,1)=="u")
                        {
                            Nat=Materiales;
                        }
                    else
                    {
                        Nat=Partida;
                    }
                    break;
                }
                case ARCOS:
                {
                    if (codigo.substr(0,1)=="M")
                        {
                            Nat=Mano_de_Obra;
                        }
                    else if (codigo.substr(0,3)=="E35")
                        {
                            Nat=Maquinaria;
                        }
                    else if (codigo.substr(0,1)=="E")
                        {
                            Nat=Materiales;
                        }
                    else
                    {
                        Nat=Partida;
                    }
                    break;
                }
                case PRESTO_CENTRO:
                {
                    if (codigo.substr(0,1)=="O")
                        {
                            Nat=Mano_de_Obra;
                        }
                    else if (codigo.substr(0,1)=="M")
                        {
                            Nat=Maquinaria;
                        }
                    else if (codigo.substr(0,1)=="P")
                        {
                            Nat=Materiales;
                        }
                    else
                    {
                        Nat=Partida;
                    }
                    break;
                }
                case EK:
                {
                    if (codigo.substr(0,2)=="_M")
                        {
                            Nat=Mano_de_Obra;
                        }
                    else if (codigo.substr(0,2)=="_Q")
                        {
                            Nat=Maquinaria;
                        }
                    else if (codigo.substr(0,1)=="_")
                        {
                            Nat=Materiales;
                        }
                    else
                    {
                        Nat=Partida;
                    }
                    break;
                }
                case CHILE:
                {
                    if (codigo.substr(0,1)=="O")
                        {
                            Nat=Mano_de_Obra;
                        }
                    else if (codigo.substr(0,1)=="E")
                        {
                            Nat=Maquinaria;
                        }
                    else if (codigo.substr(0,1)=="M")
                        {
                            Nat=Materiales;
                        }
                    else
                    {
                        Nat=Partida;
                    }
                    break;
                }
                case BPCCL:
                {
                    if (codigo.substr(0,2)=="MO")
                        {
                            Nat=Mano_de_Obra;
                        }
                    else if (codigo.substr(0,3)=="MAM")
                        {
                            Nat=Maquinaria;
                        }
                    else if (codigo.substr(0,1)=="S" || codigo.substr(0,1)=="M")
                        {
                            Nat=Materiales;
                        }
                    else
                    {
                        Nat=Partida;
                    }
                    break;
                }
                case AGRO:
                {
                    if (codigo.substr(0,1)=="M")
                        {
                            Nat=Mano_de_Obra;
                        }
                    else if (codigo.substr(0,1)=="C")
                        {
                            Nat=Maquinaria;
                        }
                    else if (codigo.substr(0,1)=="B")
                        {
                            Nat=Materiales;
                        }
                    else
                    {
                        Nat=Partida;
                    }
                    break;
                }
                case FITC:
                {
                    if (codigo.substr(0,1)=="O")
                        {
                            Nat=Mano_de_Obra;
                        }
                    else if (codigo.substr(0,1)=="Q")
                        {
                            Nat=Maquinaria;
                        }
                    else if (codigo.substr(0,1)=="T")
                        {
                            Nat=Materiales;
                        }
                    else
                    {
                        Nat=Partida;
                    }
                    break;
                }
                case FECE:
                {
                    if (codigo.substr(0,2)=="MO")
                        {
                            Nat=Mano_de_Obra;
                        }
                    else if (codigo.substr(0,2)=="MM")
                        {
                            Nat=Maquinaria;
                        }
                    else if (codigo.substr(0,1)=="P" || codigo.substr(0,1)=="Y")
                        {
                            Nat=Materiales;
                        }
                    else
                    {
                        Nat=Partida;
                    }
                    break;
                }
                case EMEDOS:
                {
                    if (codigo.substr(0,2)=="01")
                        {
                            Nat=Mano_de_Obra;
                        }
                    else if (codigo.substr(0,2)=="02")
                        {
                            Nat=Maquinaria;
                        }
                    /*else if (codigo.substr(0,1)=="P" || codigo.substr(0,1)=="Y")
                        {
                            Nat=Materiales;
                        }*/
                    else
                    {
                        Nat=Partida;
                    }
                    break;
                }
            }
        return Nat;
    }

int AsignadorDeNaturaleza::LeeNat()const
{
    return Nat;
}
