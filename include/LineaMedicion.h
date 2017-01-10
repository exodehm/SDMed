#ifndef LINEAMEDICION_H_INCLUDED
#define LINEAMEDICION_H_INCLUDED

#include "../Calc/include/Calc.h"

#include <string>
#include <iostream>
#include <QString>
#include <QStringList>

typedef QString TEXTO;


struct LineaMedicion
{
    int nFase;
    float n_unidades;
    float largo;
    float ancho;
    float alto;
    float parcial;
    float subtotal;
    enum tipo{NORMAL, SUBPARC, SUBTOTAL, FORMULA} tipoLinea;
    bool activa;
    int FacRed; //factor de redondeo
    bool seleccionada;
    TEXTO comentario;
    TEXTO formula;
    //constructores
    LineaMedicion(int fase=1, tipo Tip=NORMAL, TEXTO com="", float uds=0,float larg=0, float lat=0, float alt=0,
        TEXTO form="", float parc=0, float subt=0,  bool act=true, int factor = 4, bool sel=false);
    LineaMedicion(const LineaMedicion& origen);

    //destructor
    //~LineaMedicion();
    //metodos consultores
    const int& LeeFase() const;
    const TEXTO& LeeComentario() const;
    const float Lee_N_Uds() const;
    const float& LeeLargo() const;
    const float& LeeAncho() const;
    const float& LeeAlto() const;
    const float& LeeParcial() const;
    const float& LeeSubtotal() const;
    const tipo& LeeTipo() const;
    const TEXTO &LeeFormula() const;
    QStringList LeeLineaMedicion();
    //metodos modificadores
    void EscribeFase (int F);
    void EscribeComentario (TEXTO C);
    void EscribeUds (float N);
    void EscribeLargo (float L);
    void EscribeAncho (float An);
    void EscribeAlto (float Al);
    void EscribeFormula (TEXTO F);
    void EscribeTipo (tipo T);
    void EscribeParcial();
    void EscribeSubtotal(float Sub);
    float CalcularFormula (std::string expresion, float UD, float LONG, float LAT, float ALT);
    void Seleccionar();
    void Deseleccionar();
    bool esSeleccionada();
    //funciones miembro

    LineaMedicion& operator=(const LineaMedicion& m);

    friend std::ostream &operator<< (std::ostream& out, const LineaMedicion& m);
    friend std::istream &operator>> (std::istream& in,  LineaMedicion& m);
};

#endif // LINEAMEDICION_H_INCLUDED
