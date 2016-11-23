#include "../include/Concepto.h"

Concepto::Concepto(const TEXTO C1, int numUd, const TEXTO R, float Prec, int N, Divisas D, int Dur, int E, float F, int For, int I)
    :Nat(N), Divisa(D), DurUnit(Dur), Existencias(E), FacRend(F), Formula(For), Info(I)
{
    EscribeCodigo(C1);
    EscribeResumen(R);
    U.EscribeUd(numUd);
    Importe[MEDICION]=Prec;
    Importe[CERTIFICACION]=Prec;
    //el constructor de fecha inicializa esa variable de forma automática
}

Concepto::Concepto(const Concepto& Ref)
{
    Codigo=Ref.Codigo;
    U=Ref.U;
    Resumen=Ref.Resumen;
    Importe[MEDICION]=Ref.Importe[MEDICION];
    Importe[CERTIFICACION]=Ref.Importe[CERTIFICACION];
    Nat=Ref.Nat;
    Divisa=Ref.Divisa;
    DurUnit=Ref.DurUnit;
    Existencias=Ref.Existencias;
    FacRend=Ref.FacRend;
    fecha=Ref.fecha;
    Formula=Ref.Formula;
    Info=Ref.Info;
    Texto=Ref.Texto;
    //std::cout<<"Constructor copia"<<std::endl;
}

void Concepto::anadirConcepto()
{
    TEXTO C;
    TEXTO R;
    float P;
    /*std::cout<<"Introduce código: "<<std::endl;
    std::cin>>C;
    std::cout<<"Introduce resúmen: "<<std::endl;
    std::cin>>R;
    std::cout<<"Introduce precio: "<<std::endl;
    std::cin>>P;*/
    Codigo=C;
    Resumen=R;
    Importe[MEDICION]=P;
}

const TEXTO Concepto::LeeCodigo() const
{
    return Codigo;
}

const TEXTO Concepto::LeeResumen() const
{
    return Resumen;
}

const TEXTO Concepto::LeeUd() const
{
    return QString::fromStdString(U.LeeUd());
}

int Concepto::LeeNUd() const
{
    int posicion=0;
/*    while (strcmp(LeeUd().c_str(),UdMedida[posicion]))
    {
        posicion++;
    }*/
    return posicion;
}

const TEXTO Concepto::LeeFecha() const
{
    //return fecha.LeeFecha();
}

const float Concepto::LeeImportePres() const
{
    return Importe[MEDICION].LeePrecio();
}

const float Concepto::LeeImporteCert() const
{
    return Importe[CERTIFICACION].LeePrecio();
}

const int Concepto:: LeeNat() const
{
    return Nat;
}

Concepto::Divisas Concepto::LeeDivisa() const
{
    return Divisa;
}

int Concepto::LeeDuracion() const
{
    return DurUnit;
}

int Concepto::LeeExistencias() const
{
    return Existencias;
}

float Concepto::LeeFactorRendimiento() const
{
    return FacRend;
}

int Concepto::LeeFormula() const
{
    return Formula;
}

int Concepto::LeeInfo() const
{
    return Info;
}

TEXTO Concepto::LeeTexto() const
{
    return Texto;
}

bool Concepto::esPrecioBloqueado()
{
    return Importe[MEDICION].EsBloqueado();
}

void Concepto::EscribeCodigo (TEXTO C)
{
    C.truncate(AnchoCodigo);//limito el codigo a 10 caracteres
    Codigo = C;
}

void Concepto::EscribeResumen (TEXTO R)
{
    R.truncate(AnchoResumen);//limito el resumen a 50 caracteres
    Resumen = R;
}

void Concepto::EscribeNaturaleza(int nat)
{
    Nat = nat;
}

void Concepto::EscribePrecio(float P)
{
    Importe[MEDICION].EscribePrecio(P);
    Importe[CERTIFICACION].EscribePrecio(P);
}

void Concepto::EscribeImportePres(float P)
{
    Importe[MEDICION].EscribePrecio(P);
}

void Concepto::EscribeImporteCert(float P)
{
    Importe[CERTIFICACION].EscribePrecio(P);
}

void Concepto::bloquearPrecio()
{
    Importe[MEDICION].Bloquear();
}

void Concepto::desbloquearPrecio()
{
    Importe[MEDICION].Desbloquear();
}

void Concepto::EscribeUd(TEXTO ud)
{
    /*ud=ud.substr(0,2);
    U.EscribeUd(ud);*/
}

void Concepto::EscribeUd(int numUd)
{
    U.EscribeUd(numUd);
}

void Concepto::EscribeFecha(Fecha efe)
{
    fecha=efe;
}

void Concepto::EscribeTexto(TEXTO nuevotexto)
{
    Texto=nuevotexto;
}

Concepto::~Concepto()
{
    //dtor
}

Concepto& Concepto::operator=(const Concepto& Ref)
{
    if (this!=&Ref)
    {
        Codigo=Ref.Codigo;
        U=Ref.U;
        Resumen=Ref.Resumen;
        Importe[MEDICION]=Ref.Importe[MEDICION];
        Importe[CERTIFICACION]=Ref.Importe[CERTIFICACION];
        Nat=Ref.Nat;
        Divisa=Ref.Divisa;
        DurUnit=Ref.DurUnit;
        Existencias=Ref.Existencias;
        FacRend=Ref.FacRend;
        fecha=Ref.fecha;
        Formula=Ref.Formula;
        Info=Ref.Info;
        Texto=Ref.Texto;
    }
    return *this;
}

bool operator==(const Concepto& C1, const Concepto& C2)
{
    return C1.LeeCodigo()==C2.LeeCodigo();
}

bool operator!=(const Concepto& C1, const Concepto& C2)
{
    return C1.LeeCodigo()!=C2.LeeCodigo();
}
