#include "../include/Medicion.h"
#include <iomanip>

Medicion::Medicion(float total):lm(),TotalCantidad(total),actual(0),todoseleccionado(false),fecha()
{
    //std::cout<<"Nueva medición con valor "<<total<<std::endl;
}

Medicion::Medicion (const Medicion& origen)
{
    lm =origen.lm;
    TotalCantidad=origen.TotalCantidad;
    actual=0;
    todoseleccionado=false;
    fecha=origen.fecha;
}

Medicion::~Medicion()
{
    //std::cout<<"Borrada Medicion"<<std::endl;
    //m=std::list<LineaMedicion>();?
}

Medicion& Medicion::operator=(const Medicion& origen)
{
    if (this!=&origen)
    {
        lm=origen.lm;
        TotalCantidad=origen.TotalCantidad;
        actual=0;
        todoseleccionado=false;
        fecha=origen.fecha;
    }
    return *this;
}

void Medicion::Insertar ()
{
    std::string entrada;
    std::string comentario;
    int tipo=0;
    char respuesta='S';
    std::string subopcion="0";
    do
    {
        std::cout<<"(Enter) o (1) Suma parcial - (2) Suma total - (3)Formula"<<std::endl;
        std::cin.ignore(100,'\n');
        getline (std::cin,subopcion);

        if (subopcion=="1" || subopcion=="2")//suma parcial o suma total
        {
            std::cout<<"Insertar comentario "<<std::endl;
            getline (std::cin,comentario);
            std::cout<<"El comentario es: "<<comentario<<std::endl;
            if (subopcion=="1") tipo=1;
            if (subopcion=="2") tipo=2;
            Insertar(tipo,comentario,0,0,0,0);
        }
        else
        {
            std::istringstream str(subopcion);
            str>>tipo;
            Gestor.GestionarEntrada(tipo);
            Insertar(tipo,Gestor.D.comentario,Gestor.D.fUd,Gestor.D.fLong,Gestor.D.fAncho,Gestor.D.fAlto);
        }
        std::cout<<"¿Quieres introducir otra linea de medición?"<<std::endl;
        std::cout << "(S) para introducir (N) para salir" << std::endl;
        std::cin>>respuesta;
    }

    while (respuesta=='s' || respuesta=='S');
}

void Medicion::Insertar (int tipo, std::string ComentarioFormula, float unidades, float longitud, float latitud, float altura)
{
    //creo una linea de medicion para rellenarla y meterla en la lista
    LineaMedicion buffer;

    //inserto cada valor en su campo, excepto el comentario
    buffer.EscribeUds(unidades);
    buffer.EscribeLargo(longitud);
    buffer.EscribeAncho(latitud);
    buffer.EscribeAlto(altura);

    //si es un tipo de linea normal, el comentario va a su sitio
    if (tipo==LineaMedicion::tipo::NORMAL)
    {
        buffer.EscribeTipo(LineaMedicion::tipo::NORMAL);
        buffer.EscribeComentario(ComentarioFormula);
    }
    else if (tipo==LineaMedicion::tipo::SUBPARC)
    {
        buffer.EscribeTipo(LineaMedicion::tipo::SUBPARC);
        buffer.EscribeComentario(ComentarioFormula);
    }
    else if (tipo==LineaMedicion::tipo::SUBTOTAL)
    {
        buffer.EscribeTipo(LineaMedicion::tipo::SUBTOTAL);
        buffer.EscribeComentario(ComentarioFormula);
    }
    //si es tipo formula el comentario se pasa al campo de formula
    else if (tipo==LineaMedicion::tipo::FORMULA)
    {
        buffer.EscribeTipo(LineaMedicion::tipo::FORMULA);
        buffer.EscribeFormula(ComentarioFormula);
    }
    buffer.EscribeParcial();
    /*std::cout<<"Tipo: "<<buffer.LeeTipo()<<std::endl;
    std::cout<<"Total: "<<buffer.LeeParcial()<<std::endl;
    std::cout<<"SubTotal: "<<buffer.LeeSubtotal()<<std::endl;*/
    Insertar(buffer);
}

void Medicion::Insertar(LineaMedicion lineamed)
{
    std::cout<<"Insertando medicion"<<std::endl;
    //si hay una cantidad introducida de forma manual la anulo y la sustituyo por el resultado de la medicion
    if (lm.empty())
    {
        TotalCantidad=0;
        actual=nullptr;
        std::cout<<"Lista vacia"<<std::endl;
    }
    //primer elemento
    if (!actual)
    {
        std::cout<<"primera linea: "<<std::endl;
        lm.push_back(lineamed);
        actual=&lm.front();
        //int c;std::cin>>c;
    }
    else
    {
        std::cout<<"NO primera linea: "<<std::endl;
        auto Iterador=lm.begin();
        while (&(*Iterador)!=actual)
        {
            Iterador++;
        }
        lm.insert(++Iterador, lineamed);
        --Iterador;
        actual=&(*Iterador);
    }
    TotalCantidad+=lineamed.LeeParcial();
    SumaSubParcial();
    SumaSubTotal();
    std::cout<<"Total Cantidad: "<<TotalCantidad<<std::endl;
}

void Medicion::EliminarLinea()
{
    auto it=lm.begin();
    while (it!=lm.end())
    {
        if (it->esSeleccionada())
        {
            TotalCantidad-=it->LeeParcial();
            lm.erase (it++);
        }
        else
        {
            ++it;
        }
    }
    if (lm.empty())
    {
        actual=0;
        TotalCantidad=0;
    }
    else
    {
        actual=&lm.front();
    }
    std::cout<<std::endl;
    SumaSubParcial();
    SumaSubTotal();
}

void Medicion::BorrarMedicion()
{
    lm.clear();
    TotalCantidad=0;
    actual=0;
    std::cout<<"Borrada la medicion"<<std::endl;
}

const bool Medicion::hayMedicion() const
{
    if (lm.empty())
    {
        return false;
    }
    return true;
}

void Medicion::MostrarMedicion()
{
    //quitada la implementación por hacer esta tarea la clase Obra mediante un functor
    //opcionalmente se puede implementar una representación alternativa mas modesta
}

void Medicion::SumaMedicion()
{
    TotalCantidad=0;
    //recorro la lista sumando cada "TotalLinea"
    std::list<LineaMedicion>::iterator Iterador=lm.begin();
    while (Iterador!=lm.end())
    {
        TotalCantidad+=Iterador->LeeParcial();
        Iterador++;
    }
}

void Medicion::SumaSubParcial()
{
    //std::cout<<"Funcion SumaSubParcial()"<<std::endl;
    std::list<LineaMedicion>::reverse_iterator rIterador=lm.rbegin();
    std::list<LineaMedicion>::reverse_iterator Apuntador;
    float subparcial=0;
    while (rIterador!=lm.rend())
    {
        if (rIterador->LeeTipo()==LineaMedicion::tipo::SUBPARC)
        {
            std::cout<<"comentario del Subparcial: "<<rIterador->LeeComentario()<<std::endl;
            Apuntador=rIterador;//posiciono el apuntador en el primer subtotal
            rIterador++;//voy a la siguiente linea
            while ((rIterador->LeeTipo()==LineaMedicion::tipo::NORMAL || rIterador ->LeeTipo()==LineaMedicion::tipo::FORMULA) && rIterador!=lm.rend())
            {
                subparcial+=rIterador->LeeParcial();
                std::cout<<"Linea: "<<rIterador->LeeComentario()<<std::endl;
                rIterador++;

            }
            std::cout<<"Subparcial es: "<<subparcial<<std::endl;
            Apuntador->EscribeSubtotal(subparcial);
            subparcial=0;
        }
        else
        {
            rIterador++;
        }
    }
}

void Medicion::SumaSubTotal()
{
    std::list<LineaMedicion>::reverse_iterator rIterador=lm.rbegin();
    std::list<LineaMedicion>::reverse_iterator Apuntador;
    float subtotal=0;

    while (rIterador!=lm.rend())
    {
        if (rIterador->LeeTipo()==LineaMedicion::tipo::SUBTOTAL)
        {
            Apuntador=rIterador;
            ++Apuntador;
            while (Apuntador!=lm.rend())
            {
                subtotal+=Apuntador->LeeParcial();
                ++Apuntador;
            }
            rIterador->EscribeSubtotal(subtotal);
        }
        subtotal=0;
        ++rIterador;
    }
}

void Medicion::AvanzarActual()
{
    auto Iterador=lm.begin();
    auto final=lm.end();
    final--;
    while (&(*Iterador)!=actual)
    {
        Iterador++;
    }
    if (Iterador!=final)
    {
        Iterador++;
        actual=&(*Iterador);
    }
}

void Medicion::RetrocederActual()
{
    auto Iterador=lm.begin();
    while (&(*Iterador)!=actual)
    {
        Iterador++;
    }
    if (Iterador!=lm.begin())
    {
        Iterador--;
        actual=&(*Iterador);
    }
}

void Medicion::SelecDeselecLinea()
{
    auto Iterador=lm.begin();
    while (&(*Iterador)!=actual)
    {
        Iterador++;
    }
    Iterador->Seleccionar();
}

void Medicion::SelecDeselecTodo()
{
    auto Iterador=lm.begin();
    while (Iterador!=lm.end())
    {
        Iterador->seleccionada=!todoseleccionado;
        Iterador++;
    }
    todoseleccionado=!todoseleccionado;
}

void Medicion::Copiar(std::list<LineaMedicion*>* l)
{
    for (auto it=lm.begin(); it!=lm.end(); ++it)
    {
        if (it->esSeleccionada() || &(*it)==actual)
        {
            l->push_back(&(*it));
            it->Deseleccionar();
        }
    }
}

void Medicion::Pegar(std::list<LineaMedicion*>* l)
{
    for (auto it=l->begin(); it!=l->end(); it++)
    {
        Insertar(*(*it));
    }
}

void Medicion::EditarCampo (int campo, float valor, std::string comentario)
{
    if (campo==Medicion::COM)
    {
        actual->EscribeComentario (comentario);
    }
    else
    {
        switch (campo)
        {
        case Medicion::UD:
        {
            actual->EscribeUds (valor);
            break;
        }
        case Medicion::LONG:
        {
            actual->EscribeLargo (valor);
            break;
        }
        case Medicion::LAT:
        {
            actual->EscribeAncho (valor);
            break;
        }
        case Medicion::ALT:
        {
            actual->EscribeAlto (valor);
            break;
        }
        case Medicion::FOR:
        {
            actual->EscribeFormula(comentario);
            //actual->EscribeComentario("");
            //actual->EscribeTipo(LineaMedicion::tipo::FORMULA);
        }
        default:
        {
            break;
        }
        }

        actual->EscribeParcial();
        SumaSubParcial();
        SumaSubTotal();
        SumaMedicion();
    }
}

const std::list<LineaMedicion> &  Medicion::LeeLista() const
{
    return lm;
}

const float& Medicion::LeeTotal ()const
{
    return TotalCantidad;
}

const LineaMedicion* Medicion::LeeActual() const
{
    return this->actual;
}

void Medicion::EscribeTotal (float cantidad)
{
    TotalCantidad=cantidad;
}

void Medicion::actualAlComienzo()
{
    if (lm.empty())
    {
        actual=0;
    }
    else
    {
        actual=&lm.front();
    }
}

void Medicion::Bloquear(int nColumna, float fValor)
{
    Gestor.bloquear(nColumna,fValor);
}

void Medicion::Desbloquear(int nColumna)
{
    Gestor.desbloquear(nColumna);
}

void Medicion::DesbloquearTodo()
{
    Gestor.desbloquearTodo();
}

void Medicion::Ver()
{
    for (auto elem:lm)
    {
        std::cout<<"|"<<std::setw(20)<<elem.LeeComentario()<<"|"<<std::setw(1)<<elem.Lee_N_Uds()<<"|"<<
        std::setw(3)<<elem.LeeLargo()<<"|"<<
        std::setw(3)<<elem.LeeAncho()<<"|"<<
        std::setw(3)<<elem.LeeAlto()<<"|"<<
        std::setw(10)<<elem.LeeFormula()<<"|"<<
        std::setw(8)<<elem.LeeParcial()<<"|"<<
        std::setw(10)<<elem.LeeSubtotal()<<"|"<<std::endl;
    }
        std::cout<<std::endl;

}
