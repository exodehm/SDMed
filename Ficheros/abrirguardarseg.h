#ifndef ABRIRGUARDARSEG_H
#define ABRIRGUARDARSEG_H

#include "./abrirguardar.h"

class AbrirGuardarSEG : public AbrirGuardar
{
public:

    AbrirGuardarSEG();
    /*****************LEER****************************************/
    Obra* Leer(QString nombre);
    Concepto* leerConcepto( std::ifstream &ifs);
    std::string leerString(std::ifstream& ifs);
    void procesarAristas(Obra* o, pNodo n, std::ifstream& ifs);
    void InsertarMedicion(pArista& a, int MedCer, std::ifstream& ifs);
    void InsertarLineaMedicion(pArista& a, int MedCer, std::ifstream& ifs);
    /*****************GUARDAR****************************************/
    void Escribir(QFile& fichero, const Obra* obra);
    void EscribirConcepto(Concepto C, std::ofstream& ofs);
    void escribirAristas(pArista a,std::ofstream& ofs);
    void guardarString(const std::string& s, std::ofstream& ofs);
    void guardarMedicion(pArista a, std::ofstream& ofs, int i);
    void guardarLineaMedicion(LineaMedicion& lm, std::ofstream& ofs);

    bool esHoja(pNodo n);
    void guardarNodoEnLista(bool valor, std::list<pNodo>& lista, Obra* O, pNodo n);
    pNodo buscaNodoPorCodigo (std::string codigo, const Obra* O);
};

#endif // ABRIRGUARDARSEG_H
