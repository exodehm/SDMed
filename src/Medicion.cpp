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

void Medicion::Insertar(int fila, TEXTO comentario, float unidades, float longitud, float latitud, float altura, TEXTO formula, TipoLinea tipo)
{
    //creo una linea de medicion para rellenarla y meterla en la lista
    LineaMedicion buffer(1,comentario,unidades,longitud,latitud,altura,formula, tipo);
    Insertar(fila, buffer);
}

void Medicion::Insertar(int fila, LineaMedicion lineamed)
{    
    actual=lm.begin();
    std::advance(actual, fila);
    lm.insert(actual,lineamed);
    TotalCantidad+=lineamed.LeeParcial();
    SumaSubParcial();
    SumaSubTotal();
    std::cout<<"Total Cantidad: "<<TotalCantidad<<std::endl;
    for (actual=lm.begin();actual!=lm.end();++actual)
    {
        std::cout<<actual->LeeComentario().toStdString()<<"-"<<actual->Lee_N_Uds()<<std::endl;
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
        if (rIterador->LeeTipo()==TipoLinea::SUBPARCIAL)
        {
            Apuntador = rIterador;//posiciono el apuntador en el primer subtotal
            rIterador++;//voy a la siguiente linea
            while((rIterador->LeeTipo()==TipoLinea::NORMAL || rIterador->LeeTipo()==TipoLinea::FORMULA) && rIterador!=lm.rend())
            {
                subparcial+=rIterador->LeeParcial();                
                rIterador++;
            }
            Apuntador->EscribeSubtotal(subparcial);
            subparcial=0;
        }
        else
        {
            rIterador->EscribeSubtotal(0);
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
        //if (rIterador->LeeTipo()==LineaMedicion::tipo::SUBTOTAL)
        if (rIterador->LeeTipo()==TipoLinea::SUBTOTAL)
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

void Medicion::PosicionarLineaActual(int pos)
{
    actual=lm.begin();
    std::advance(actual,pos);
}

void Medicion::EditarCampo (int fila, int columna, float valor, TEXTO comentario)
{
    actual=lm.begin();
    std::advance(actual, fila);
    if (columna==tipoColumna::COMENTARIO)
    {
        actual->EscribeComentario(comentario);
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

void Medicion::Ver()
{
    for (auto elem:lm)
    {
        std::cout<<"|"<<std::setw(20)<<elem.LeeComentario().toStdString()<<"|"<<std::setw(1)<<elem.Lee_N_Uds()<<"|"<<
        std::setw(3)<<elem.LeeLargo()<<"|"<<
        std::setw(3)<<elem.LeeAncho()<<"|"<<
        std::setw(3)<<elem.LeeAlto()<<"|"<<
        std::setw(10)<<elem.LeeFormula().toStdString()<<"|"<<
        std::setw(8)<<elem.LeeParcial()<<"|"<<
        std::setw(10)<<elem.LeeSubtotal()<<"|"<<std::endl;
    }
        std::cout<<std::endl;
}
