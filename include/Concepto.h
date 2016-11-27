#ifndef CONCEPTO_H
#define CONCEPTO_H

#include <QString>
#include "Fecha.h"
#include "Codificacion.h"
#include "Precio.h"
#include "Unidades.h"

typedef QString TEXTO;

class Concepto
{
public:

    enum Divisas {EUR,USA,UK};
    //constructores
    Concepto (const TEXTO C1="",
              int numUd=0,
              const TEXTO R="",
              float Prec=0,
              int N=0,
              Divisas D=EUR,
              int Dur=0,
              int E=0,
              float F=1,
              int For=0,
              int I=0);
    Concepto (const Concepto& Ref);
    //destructor
    ~Concepto();
    //funciones miembro
    void anadirConcepto();
    void bloquearPrecio();
    void desbloquearPrecio();
    //getters
    const TEXTO LeeCodigo() const;
    const TEXTO LeeResumen() const;
    const TEXTO LeeUd() const;
    int LeeNUd() const;
    const float LeeImportePres() const;
    const float LeeImporteCert() const;
    const TEXTO LeeFecha() const;
    const int& LeeNat() const;
    Divisas LeeDivisa() const;
    int LeeDuracion() const;
    int LeeExistencias() const;
    float LeeFactorRendimiento() const;
    int LeeFormula() const;
    int LeeInfo() const;
    TEXTO LeeTexto() const;
    bool esPrecioBloqueado();
    //setters
    void EscribeCodigo (TEXTO C);
    void EscribeResumen (TEXTO R);
    void EscribeUd(TEXTO U);
    void EscribeUd(int numUd);
    void EscribeFecha(Fecha efe);
    void EscribePrecio(float P);
    void EscribeImportePres(float P);
    void EscribeImporteCert(float P);
    void EscribeTexto(TEXTO nuevotexto);
    void EscribeNaturaleza(int nat);
    //operador de asignacion
    Concepto& operator=(const Concepto& Ref);
    //operadores relacionales
    friend bool operator==(const Concepto& C1, const Concepto& C2);
    friend bool operator!=(const Concepto& C1, const Concepto& C2);

    /*friend std::ostream& operator<<(std::ostream& os, const Concepto& C)
    {
        os<<C.LeeCodigo();
        return os;
    }*/

private:

    Unidad U;
    Precio Importe[2];
    int Nat;
    Divisas Divisa;
    int DurUnit;
    int Existencias;
    float FacRend;
    Fecha fecha;
    int Formula;
    int Info;
    TEXTO Codigo;
    TEXTO Resumen;
    TEXTO Texto;
    enum {MEDICION,CERTIFICACION};

    const int AnchoCodigo=20;
    const int AnchoResumen=50;
};






#endif // CONCEPTO_H
