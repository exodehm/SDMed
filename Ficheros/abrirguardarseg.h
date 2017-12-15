#ifndef ABRIRGUARDARSEG_H
#define ABRIRGUARDARSEG_H

#include "./abrirguardar.h"

class AbrirGuardarSEG : public AbrirGuardar
{
public:

    AbrirGuardarSEG();
    /*****************LEER****************************************/
    Obra* Leer(QString nombrefichero);
    void leerConcepto(Concepto& C, QDataStream &datos);
    void leerMedicion(MedCert& MC, QDataStream &datos);
    void leerLineaMedicion(LineaMedicion& l,  QDataStream &datos);
    /*****************GUARDAR****************************************/
    void Escribir(QFile& fichero, Obra* obra);
    void EscribirConcepto(Concepto& C, QDataStream &datos);
    void escribirMedicion(pArista a, QDataStream &datos, int tabla);    
};

#endif // ABRIRGUARDARSEG_H
