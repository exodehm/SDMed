#ifndef LINEAMEDICION_H_INCLUDED
#define LINEAMEDICION_H_INCLUDED

#include "../Calc/include/Calc.h"

#include <string>
#include <iostream>
#include <QString>
#include <QStringList>

typedef QString TEXTO;

enum TipoLinea{NORMAL, SUBPARCIAL, SUBTOTAL, FORMULA};//en este caso FORMULA solo vale para interpretar correctamente los ficheros bc3


struct LineaMedicion
{

    int nFase;
    TEXTO comentario;
    float n_unidades;
    float largo;
    float ancho;
    float alto;
    float parcial;
    float subtotal;
    TEXTO formula;
    TipoLinea Tipo;
    bool esFormula;   
    int FacRed; //factor de redondeo

    //constructores
    LineaMedicion(int fase=1, TEXTO com="", float uds=0, float larg=0, float lat=0, float alt=0,
        TEXTO form="", TipoLinea tipo = NORMAL, bool esFormula = false, int factor = 4);
    LineaMedicion(const LineaMedicion& origen);

    //destructor
    //~LineaMedicion();
    //metodos consultores
    const int& LeeFase() const;
    const TEXTO& LeeComentario() const;
    const float& Lee_N_Uds() const;
    const float& LeeLargo() const;
    const float& LeeAncho() const;
    const float& LeeAlto() const;
    const float& LeeParcial() const;
    const float& LeeSubtotal() const;    
    const TEXTO &LeeFormula() const;
    const TipoLinea& LeeTipo() const;
    const bool& EsSubTotal() const;
    bool EsFormula();
    bool EsLineaVacia() const;
    QStringList LeeLineaMedicion();    

    //metodos modificadores
    void EscribeFase (int F);
    void EscribeComentario (TEXTO C);
    void EscribeUds (float N);
    void EscribeLargo (float L);
    void EscribeAncho (float An);
    void EscribeAlto (float Al);
    void EscribeFormula (TEXTO F);
    void EscribeTipo(TipoLinea tipo);
    void EscribeTipo(int tipo);
    void EscribeParcial();
    void EscribeSubtotal(float Sub);
    float CalcularFormula (std::string expresion, float UD, float LONG, float LAT, float ALT);   
    //funciones miembro

    LineaMedicion& operator=(const LineaMedicion& m);

    friend std::ostream &operator<< (std::ostream& out, const LineaMedicion& m);
    friend std::istream &operator>> (std::istream& in,  LineaMedicion& m);
};

#endif // LINEAMEDICION_H_INCLUDED
