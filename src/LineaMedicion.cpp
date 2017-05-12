#include "../include/LineaMedicion.h"


LineaMedicion::LineaMedicion(int fase, TEXTO com, float uds, float larg, float lat, float alt, TEXTO form, TipoLinea tipo,
    bool F, int factor):nFase(fase), comentario(com), n_unidades(uds),
        largo(larg),ancho(lat),alto(alt),formula(form), esFormula(F), Tipo (tipo), FacRed(factor)
{
    if (!formula.isEmpty())
    {
        esFormula=true;
    }
    EscribeParcial();
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
    FacRed=origen.FacRed;
    esFormula=origen.esFormula;
    Tipo = origen.Tipo;
}

const int& LineaMedicion::LeeFase() const
{
    return nFase;
}

const TEXTO &LineaMedicion::LeeComentario() const
{
    return comentario;
}

const float &LineaMedicion::Lee_N_Uds() const
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

const TEXTO& LineaMedicion::LeeFormula() const
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

const TipoLinea& LineaMedicion::LeeTipo() const
{
    return Tipo;
}

bool LineaMedicion::EsLineaVacia() const
{
    return (nFase==1 && comentario.isEmpty() && n_unidades==0 && largo==0 && ancho==0 && alto==0 && formula.isEmpty());
}

QStringList LineaMedicion::LeeLineaMedicion()
{
    QStringList lineamedicion;
    lineamedicion.append(QString::number(nFase));
    lineamedicion.append(comentario);
    lineamedicion.append(QString::number(n_unidades));
    lineamedicion.append(QString::number(largo));
    lineamedicion.append(QString::number(ancho));
    lineamedicion.append(QString::number(alto));
    lineamedicion.append(formula);
    lineamedicion.append(QString::number(parcial));
    lineamedicion.append(QString::number(subtotal));
    lineamedicion.append("");//un espacio para la columna Id...si se acaba eliminando esa columna, borrar este append
    return lineamedicion;
}

void LineaMedicion::EscribeFase (int F)
{
    nFase=F;
}
void LineaMedicion::EscribeComentario (TEXTO C)
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
void LineaMedicion::EscribeFormula (TEXTO F)
{
    formula=F;
    if (formula.isEmpty())
    {
        esFormula=false;
    }
    else
    {
        esFormula=true;
    }
    EscribeParcial();
}

void LineaMedicion::EscribeTipo(TipoLinea tipo)
{
    Tipo = tipo;
}

void LineaMedicion::EscribeParcial()
{
    float provisional=0;
    if (esFormula)
        {
            provisional = CalcularFormula(LeeFormula().toStdString(),Lee_N_Uds(),LeeLargo(),LeeAncho(),LeeAlto());
        }
    else
        {
            provisional = n_unidades*((largo==0)?1:largo)*((ancho==0)?1:ancho)*((alto==0)?1:alto);
        }
    //std::cout<<"Provisional= "<<provisional<<std::endl;
    //std::cout<<"Factor de rendimiento es: "<<FacRed<<std::endl;    
    parcial = ceil(provisional*1000.0)/1000.0;
}

void LineaMedicion::EscribeSubtotal(float Sub)
{
    subtotal=Sub;
}

float LineaMedicion::CalcularFormula (std::string expresion, float UD, float LONG, float LAT, float ALT)
{
    //std::cout<<"CalcularFormula() "<<expresion<<"-"<<UD<<"-"<<LONG<<"-"<<LAT<<"-"<<ALT<<std::endl;
    float a,b,c,d;
    UD==0   ?a=1.f
               :a=UD;
    LONG==0 ?b=1.f
               :b=LONG;
    LAT==0  ?c=1.f
               :c=LAT;
    ALT==0  ?d=1.f
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
            FacRed=m.FacRed;
            esFormula=m.esFormula;
            Tipo = m.Tipo;
        }
    return *this;
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
