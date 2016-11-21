#include "../include/LineaMedicion.h"


LineaMedicion::LineaMedicion(int fase, tipo Tip, std::string com, int uds,float larg, float lat, float alt, std::string form,
    float parc, float subt,  bool act, int factor, bool sel):nFase(fase), tipoLinea(Tip), comentario(com), n_unidades(uds),
        largo(larg),ancho(lat),alto(alt),formula(form), parcial(parc),subtotal(subt),activa(act),FacRed(factor),seleccionada(sel)
{
    //FacRed=pow (10, FacRed);
    if (!formula.empty())
    {
        tipoLinea = tipo::FORMULA;
    }
    //std::cout<<"Creada nueva linea de medicion"<<std::endl;
}

LineaMedicion::LineaMedicion(const LineaMedicion& origen)
{
    nFase=origen.nFase;
    n_unidades=origen.n_unidades;
    largo=origen.largo;
    ancho=origen.ancho;
    alto=origen.alto;
    formula=origen.formula;
    parcial=origen.parcial;
    subtotal=origen.subtotal;
    comentario=origen.comentario;
    tipoLinea=origen.tipoLinea;
    activa=origen.activa;
    FacRed=origen.FacRed;
    seleccionada=false;//independientemente del original, la copia va a false
}

const int& LineaMedicion::LeeFase() const
{
    return nFase;
}

const std::string& LineaMedicion::LeeComentario() const
{
    return comentario;
}

const int LineaMedicion::Lee_N_Uds() const
{
    return n_unidades;
}

const float& LineaMedicion::LeeLargo() const
{
    return largo;
}

const float& LineaMedicion::LeeAncho() const
{
    return ancho;
}

const float& LineaMedicion::LeeAlto() const
{
    return alto;
}

const LineaMedicion::tipo& LineaMedicion::LeeTipo() const
{
    return tipoLinea;
}
const std::string& LineaMedicion::LeeFormula() const
{
    return formula;
}

const float& LineaMedicion::LeeParcial() const
{
    return parcial;
}

const float& LineaMedicion::LeeSubtotal() const
{
    return subtotal;
}

void LineaMedicion::EscribeFase (int F)
{
    nFase=F;
}
void LineaMedicion::EscribeComentario (std::string C)
{
    comentario=C;
}
void LineaMedicion::EscribeUds (float N)
{
    n_unidades=N;
    EscribeParcial();
}
void LineaMedicion::EscribeLargo (float L)
{
    largo=L;
    EscribeParcial();
}
void LineaMedicion::EscribeAncho (float An)
{
    ancho=An;
    EscribeParcial();
}
void LineaMedicion::EscribeAlto (float Al)
{
    alto=Al;
    EscribeParcial();
}
void LineaMedicion::EscribeFormula (std::string F)
{
    formula=F;
    if (!formula.empty())
    {
        tipoLinea=tipo::FORMULA;
    }
    else
    {
        tipoLinea=tipo::NORMAL;
    }
    EscribeParcial();
}
void LineaMedicion::EscribeTipo (tipo T)
{
    tipoLinea=T;
}

void LineaMedicion::EscribeParcial()
{
    float provisional=0;
    if (tipoLinea==FORMULA)
        {
            provisional = CalcularFormula(LeeFormula(),Lee_N_Uds(),LeeLargo(),LeeAncho(),LeeAlto());
        }
    else
        {
            provisional = n_unidades*((largo==0)?1:largo)*((ancho==0)?1:ancho)*((alto==0)?1:alto);
        }
    //std::cout<<"Provisional= "<<provisional<<std::endl;
    //std::cout<<"Factor de rendimiento es: "<<FacRed<<std::endl;
    parcial = ceil(provisional*1000)/1000;
}

void LineaMedicion::EscribeSubtotal(float Sub)
{
    subtotal=Sub;
}

float LineaMedicion::CalcularFormula (std::string expresion, float UD, float LONG, float LAT, float ALT)
{
    //std::cout<<"CalcularFormula() "<<expresion<<"-"<<UD<<"-"<<LONG<<"-"<<LAT<<"-"<<ALT<<std::endl;
    float a,b,c,d;
    UD==0   ?a=1
               :a=UD;
    LONG==0 ?b=1
               :b=LONG;
    LAT==0  ?c=1
               :c=LAT;
    ALT==0  ?d=1
               :d=ALT;
    //cambio las letras por sus valores en la expresion
    for (size_t i=0; i<expresion.length(); i++)
        {
            if (expresion[i]=='a')
                {
                    std::ostringstream stm ;
                    stm<<a;
                    expresion.replace(i,1,stm.str());
                }
            if (expresion[i]=='b')
                {
                    std::ostringstream stm ;
                    stm<<b;
                    expresion.replace(i,1,stm.str());
                }
            if (expresion[i]=='c')
                {
                    std::ostringstream stm ;
                    stm<<c;
                    expresion.replace(i,1,stm.str());
                }
            if (expresion[i]=='d')
                {
                    std::ostringstream stm ;
                    stm<<d;
                    expresion.replace(i,1,stm.str());
                }
            if (expresion[i]=='p')
                {
                    expresion.replace(i,1,"3.14159");
                }
        }
    Calc evaluacion(expresion);
    //std::cout<<"La expresion es: "<<expresion<<std::endl;
    return evaluacion.CalcularExpresion();
}

LineaMedicion& LineaMedicion::operator=(const LineaMedicion& m)
{
    if (this!=&m)
        {
            n_unidades=m.n_unidades;
            largo=m.largo;
            ancho=m.ancho;
            alto=m.alto;
            comentario=m.comentario;
            formula=m.formula;
            parcial=m.parcial;
            subtotal=m.subtotal;
            tipoLinea=m.tipoLinea;
            activa=m.activa;
            FacRed=m.FacRed;
            seleccionada=false;//independientemente del original, la copia va a false
        }
    return *this;
}

void LineaMedicion::Seleccionar()
{
    if (seleccionada==true)
    {
        seleccionada=false;
    }
    else
    {
        seleccionada=true;
    }
}

void LineaMedicion::Deseleccionar()
{
    seleccionada=false;
}

bool LineaMedicion::esSeleccionada()
{
    return seleccionada;
}


/*std::ostream& LineaMedicion::operator<< (std::ostream& out, const LineaMedicion& m)
{
    float res=m.n_unidades*m.largo*m.ancho*m.alto;
    out<<m.comentario<<"   "<<m.n_unidades<<"   "<<m.largo<<"   "<<m.ancho<<"   "<<m.alto<<"   "<<res<<std::endl;
    return out;
}

std::istream& LineaMedicion::operator>> (std::istream& in,  LineaMedicion& m)
{
    std::cin.ignore();
    getline (std::cin, m.comentario);
    in>>m.n_unidades>>m.largo>>m.ancho>>m.alto;
    return in;
}*/
