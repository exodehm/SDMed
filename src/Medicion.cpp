#include "../include/Medicion.h"
#include <iomanip>

Medicion::Medicion(float total):lm(),TotalCantidad(total),actual(nullptr),todoseleccionado(false),fecha()
{
    //std::cout<<"Nueva medición con valor "<<total<<std::endl;
}

Medicion::Medicion (const Medicion& origen)
{
    lm =origen.lm;
    TotalCantidad=origen.TotalCantidad;    
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
        todoseleccionado=false;
        fecha=origen.fecha;
    }
    return *this;
}

void Medicion::Insertar()
{
    /*std::string entrada;
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

    while (respuesta=='s' || respuesta=='S');*/
}

void Medicion::Insertar (int tipo, int fila, std::string ComentarioFormula, float unidades, float longitud, float latitud, float altura)
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
    Insertar(fila, buffer);
}

void Medicion::Insertar(int fila, LineaMedicion lineamed)
{
    /*std::cout<<"Insertando medicion"<<std::endl;
    //si hay una cantidad introducida de forma manual la anulo y la sustituyo por el resultado de la medicion
    if (lm.empty())
    {
        TotalCantidad=0;        
        std::cout<<"Lista vacia"<<std::endl;
    }
    //primer elemento
    if (!actual)
    {
        std::cout<<"primera linea: "<<std::endl;
        lm.push_back(lineamed);
        actual=lm.begin();
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
    }*/
    actual=lm.begin();
    std::advance(actual, fila);
    lm.insert(actual,lineamed);
    TotalCantidad+=lineamed.LeeParcial();
    SumaSubParcial();
    SumaSubTotal();
    std::cout<<"Total Cantidad: "<<TotalCantidad<<std::endl;
    for (actual=lm.begin();actual!=lm.end();++actual)
    {
        std::cout<<actual->LeeComentario()<<"-"<<actual->Lee_N_Uds()<<std::endl;
    }
}

void Medicion::InsertarLineasVacias(int pos, int num)
{
    LineaMedicion lineavacia;
    actual=lm.begin();
    std::advance(actual,pos);
    lm.insert(actual, num,lineavacia);
}

void Medicion::EliminarLineas(int pos, int numLineas)
{
    std::list<LineaMedicion>::iterator it1,it2;
    it1 = it2 = lm.begin();
    std::advance(it1,pos);
    std::advance(it2,pos+numLineas);
    std::list<LineaMedicion>::iterator it3=it1;
    lm.erase(it1,it2);
    //actualizo el total y los subparciales
    SumaMedicion();
    SumaSubParcial();
    SumaSubTotal();
}

void Medicion::BorrarMedicion()
{
    lm.clear();
    TotalCantidad=0;    
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
    actual=lm.begin();
    while (actual!=lm.end())
    {
        TotalCantidad+=actual->LeeParcial();
        actual++;
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
    /*auto Iterador=lm.begin();
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
    }*/
}

void Medicion::RetrocederActual()
{
    /*auto Iterador=lm.begin();
    while (&(*Iterador)!=actual)
    {
        Iterador++;
    }
    if (Iterador!=lm.begin())
    {
        Iterador--;
        actual=&(*Iterador);
    }*/
}

void Medicion::PosicionarLineaActual(int pos)
{
    actual=lm.begin();
    std::advance(actual,pos);
}

void Medicion::SelecDeselecLinea()
{
    /*auto Iterador=lm.begin();
    while (&(*Iterador)!=actual)
    {
        Iterador++;
    }
    Iterador->Seleccionar();*/
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
    /*for (auto it=lm.begin(); it!=lm.end(); ++it)
    {
        if (it->esSeleccionada() || &(*it)==actual)
        {
            l->push_back(&(*it));
            it->Deseleccionar();
        }
    }*/
}

void Medicion::Pegar(std::list<LineaMedicion*>* l)
{
    /*for (auto it=l->begin(); it!=l->end(); it++)
    {
        Insertar(*(*it));
    }*/
}

void Medicion::EditarCampo (int fila, int columna, float valor, std::string comentario)
{
    qDebug()<<"Y por ultimo el valor en Medicion: "<<valor;
    actual=lm.begin();
    std::advance(actual, fila);
    if (columna==tipoColumna::COMENTARIO)
    {
        actual->EscribeComentario (comentario);
    }
    else
    {
        switch (columna)
        {
        case tipoColumna::UD:
        {
            actual->EscribeUds (valor);
            break;
        }
        case tipoColumna::LONGITUD:
        {
            actual->EscribeLargo (valor);
            break;
        }
        case tipoColumna::ANCHURA:
        {
            actual->EscribeAncho (valor);
            break;
        }
        case tipoColumna::ALTURA:
        {
            actual->EscribeAlto (valor);
            break;
        }
        case tipoColumna::FORMULA:
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

const LineaMedicion Medicion::LeeActual() const
{
    return (*actual);
}

void Medicion::EscribeTotal (float cantidad)
{
    TotalCantidad=cantidad;
}

void Medicion::actualAlComienzo()
{
    if (!lm.empty())
    {
        actual=lm.begin();
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
