#ifndef MEDICION_H
#define MEDICION_H

#include <iostream>
#include <list>
#include <string>
#include <sstream>
#include <QDebug>

#include <iomanip>

#include "LineaMedicion.h"
#include "GestorEntradaDatosLineasMedicion.h"
#include "Fecha.h"
#include "./defs.h"

class Medicion
{
private:
    float TotalCantidad;
    std::list<LineaMedicion> lm;
    std::list<LineaMedicion>::iterator actual;


    //LineaMedicion* actual;
    bool todoseleccionado;
    Fecha fecha;
    //enum {COM,UD,LONG,LAT,ALT,FOR} campo;
    GestorEntradaDatosLineasMedicion Gestor;

public:
    //constructores
    Medicion(float total=0);
    Medicion (const Medicion& origen);
    //sobrecarga de =
    Medicion& operator=(const Medicion& origen);
    //destructor
    ~Medicion();
    //funciones miembro
    void Insertar (int fila, TEXTO comentario="", float unidades=0, float longitud=0, float latitud=0, float altura=0, TEXTO formula="", TipoLinea tipo = TipoLinea::NORMAL);
    void Insertar(int fila, LineaMedicion lineamed);
    void InsertarLineasVacias(int pos, int num);
    void EliminarLineas(int pos, int numLineas);
    void BorrarMedicion();
    void MostrarMedicion();
    void SumaMedicion();
    void SumaSubParcial();
    void SumaSubTotal();
    void PosicionarLineaActual(int pos);
    //consultores
    const std::list<LineaMedicion> &LeeLista() const;
    const float& LeeTotal ()const;
    const LineaMedicion LeeActual() const;
    bool hayMedicion() const;
    /***************modificadores************************/
    void EditarCampo (int fila, int columna, float valor, TEXTO comentario="");
    void EscribeTotal (float cantidad);
    void actualAlComienzo();

    void Ver();
};

#endif // MEDICION_H
