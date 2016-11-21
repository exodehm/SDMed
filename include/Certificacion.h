#ifndef CERTIFICACION_H
#define CERTIFICACION_H

#include <utility>
#include <list>
#include "Fecha.h"


class Certificacion
{
    private:
    typedef std::pair<bool,Fecha>cert;
    std::list<cert>certificaciones;

    public:
    Certificacion();
    virtual ~Certificacion();

    void anadir();
    void eliminar(unsigned int posicion);
    int tamanno();
    unsigned int verCertificacionActual();
    Fecha verFechaCertificacionActual();

    void cambiarCertificacionActual(unsigned int actual);
    void cambiarFecha(std::string nuevafecha);

    friend std::ostream& operator <<(std::ostream& os, const Certificacion& C);



};

#endif // CERTIFICACION_H
