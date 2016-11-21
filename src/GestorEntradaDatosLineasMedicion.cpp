#include "../include/GestorEntradaDatosLineasMedicion.h"

GestorEntradaDatosLineasMedicion::GestorEntradaDatosLineasMedicion():bUnidades(false),bLargo(false),bAncho(false),bAlto(false) {}

GestorEntradaDatosLineasMedicion::~GestorEntradaDatosLineasMedicion()
{
    //dtor
}


void GestorEntradaDatosLineasMedicion::bloquear (int campo,float valor)
{
    switch(campo)
    {
    case 1:
    {
        bComentario=true;
        D.comentario="";
        break;
    }
    case 2:
    {
        bUnidades=true;
        D.fUd=valor;
        break;
    }
    case 3:
    {
        bLargo=true;
        D.fLong=valor;
        break;
    }
    case 4:
    {
        bAncho=true;
        D.fAncho=valor;
        break;
    }
    case 5:
    {
        bAlto=true;
        D.fAlto=valor;
        break;
    }
    default:
    {
        break;
    }
    }
}

void GestorEntradaDatosLineasMedicion::desbloquear(int campo)
{
    switch(campo)
    {
    case 6:
    {
        bComentario=false;
        break;
    }
    case 7:
    {
        bUnidades=false;
        break;
    }
    case 8:
    {
        bLargo=false;
        break;
    }
    case 9:
    {
        bAncho=false;
        break;
    }
    case 10:
    {
        bAlto=false;
        break;
    }
    default:
    {
        break;
    }
    }
}


void GestorEntradaDatosLineasMedicion::desbloquearTodo()
{
    bComentario=false;
    bUnidades=false;
    bLargo=false;
    bAncho=false;
    bAlto=false;
}

GestorEntradaDatosLineasMedicion::datos GestorEntradaDatosLineasMedicion::GestionarEntrada(int tipo)
{
    std::string entrada;
    if (tipo==0)
    {
        std::cout<<"Insertar comentario "<<std::endl;
    }
    else
    {
        std::cout<<"Insertar fórmula "<<std::endl;
    }
    getline (std::cin,D.comentario);

    if (!bUnidades)
    {
        tipo==0 ?std::cout<<"Nº Uds"<<std::endl : std::cout<<"a"<<std::endl;
        getline (std::cin,entrada);
        while (!validar(entrada,D.fUd))
        {
            getline (std::cin,entrada);

        }
    }
    if (!bLargo)
    {
        //entrar longitud
        tipo==0 ?std::cout<<"Longitud"<<std::endl : std::cout<<"b"<<std::endl;
        getline (std::cin,entrada);
        while (!validar(entrada,D.fLong))
        {
            getline (std::cin,entrada);

        }
    }
    if (!bAncho)
    {
        //entrar ancho
        tipo==0 ?std::cout<<"Anchura"<<std::endl : std::cout<<"c"<<std::endl;
        getline (std::cin,entrada);
        while (!validar(entrada,D.fAncho))
        {
            getline (std::cin,entrada);
        }
    }
    if (!bAlto)
    {
        //entrar alto
        tipo==0 ?std::cout<<"Altura"<<std::endl : std::cout<<"d"<<std::endl;
        getline (std::cin,entrada);
        while (!validar(entrada,D.fAlto))
        {
            getline (std::cin,entrada);
        }
    }
    return D;
}

bool GestorEntradaDatosLineasMedicion::validar (std::string& entrada, float& valor)
{
    if (entrada=="")
    {
        valor=0;
        return true;
    }
    for (size_t i=0; i<entrada.length(); i++)
        if (entrada[i]==',')
        {
            entrada[i]='.';
        }
    std::stringstream mystream(entrada);
    if(mystream >> valor)
    {
        return true;
    }
    return false;
}
