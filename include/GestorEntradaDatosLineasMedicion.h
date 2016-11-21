#ifndef GESTORENTRADADATOSLINEASMEDICION_H
#define GESTORENTRADADATOSLINEASMEDICION_H

#include <sstream>
#include "LineaMedicion.h"

struct GestorEntradaDatosLineasMedicion
{
    /**************miembros************************/
    bool bComentario;
    bool bUnidades;
    bool bLargo;
    bool bAncho;
    bool bAlto;
    struct datos
    {
        std::string comentario;
        float fUd;
        float fLong;
        float fAncho;
        float fAlto;
    }D;
    /********funciones*****************/
    GestorEntradaDatosLineasMedicion();
    virtual ~GestorEntradaDatosLineasMedicion();

    void bloquear (int campo,float valor);
    void desbloquear(int campo);
    void desbloquearTodo();

    bool validar (std::string& entrada, float& valor);

    datos GestionarEntrada(int tipo);
};

#endif // GESTORENTRADADATOSLINEASMEDICION_H
