#ifndef MEDICION_H
#define MEDICION_H

#include <iostream>
#include <list>
#include <string>
#include <sstream>

#include <iomanip>

#include "LineaMedicion.h"
#include "GestorEntradaDatosLineasMedicion.h"
#include "Fecha.h"
#include "./defs.h"

class Medicion
{
private:
    std::list<LineaMedicion> lm;
    std::list<LineaMedicion>::iterator actual;

    float TotalCantidad;
    //LineaMedicion* actual;
    bool todoseleccionado;
    Fecha fecha;
    //enum {COM,UD,LONG,LAT,ALT,FOR} campo;
    GestorEntradaDatosLineasMedicion Gestor;

public:
    //constructores
    Medicion(float total=1);
    Medicion (const Medicion& origen);
    //sobrecarga de =
    Medicion& operator=(const Medicion& origen);
    //destructor
    ~Medicion();
    //funciones miembro
    void Insertar();
    void Insertar (int tipo, int fila, std::string Comentario, float unidades, float longitud, float latitud, float altura);
    void Insertar(int fila, LineaMedicion lineamed);
    void InsertarLineasVacias(int pos, int num);
    void EliminarLineas(int pos, int numLineas);
    void BorrarMedicion();
    void MostrarMedicion();
    void SumaMedicion();
    void SumaSubParcial();
    void SumaSubTotal();
    void AvanzarActual();
    void RetrocederActual();
    void SelecDeselecLinea();
    void SelecDeselecTodo();
    void Bloquear(int nColumna, float fValor);
    void Desbloquear(int nColumna);
    void DesbloquearTodo();
    void PosicionarLineaActual(int pos);
    /*******copia/pega*********************/
    void Copiar(std::list<LineaMedicion*>* l);
    void Pegar(std::list<LineaMedicion*>* l);
    //consultores
    const std::list<LineaMedicion> &LeeLista() const;
    const float& LeeTotal ()const;
    const LineaMedicion LeeActual() const;
    const bool hayMedicion() const;
    /***************modificadores************************/
    void EditarCampo (int fila, int columna, float valor, std::string comentario="");
    void EscribeTotal (float cantidad);
    void actualAlComienzo();

    void Ver();
};

#endif // MEDICION_H
