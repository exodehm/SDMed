#ifndef ABRIRGUARDAR_H
#define ABRIRGUARDAR_H


#include <fstream>
#include <sstream>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "./Obra.h"
#include "./include/definiciones.h"


class AbrirGuardar
{
    public:

        //redefinicion de tipos
        typedef nodo<Concepto,MedCert>* pNodo;
        typedef arista<MedCert,Concepto>* pArista;

        virtual Obra* Leer(QString nombre) = 0;
        virtual void Escribir(std::ofstream &ofs) = 0;
};

class AbrirGuardarNormal : public AbrirGuardar
{
    public:

        /*****************LEER****************************************/
        //Obra* Leer(std::ifstream &ifs);
        Obra* Leer(QString nombre);
        Concepto* leerConcepto( std::ifstream &ifs);
        std::string leerString(std::ifstream& ifs);
        void procesarAristas(Obra* o, pNodo n, std::ifstream& ifs);
        void InsertarMedicion(pArista& a, int MedCer, std::ifstream& ifs);
        void InsertarLineaMedicion(pArista& a, int MedCer, std::ifstream& ifs);
        /*****************GUARDAR****************************************/
        void Escribir(std::ofstream& ofs);
        void EscribirConcepto(Concepto C, std::ofstream& ofs);
        void escribirAristas(pArista a,std::ofstream& ofs);
        void guardarString(const std::string& s, std::ofstream& ofs);
        void guardarMedicion(pArista a, std::ofstream& ofs, int i);
        void guardarLineaMedicion(LineaMedicion& lm, std::ofstream& ofs);

        bool esHoja(pNodo n);
        void guardarNodoEnLista(bool valor, std::list<pNodo>& lista, Obra* O, pNodo n);
        pNodo buscaNodoPorCodigo (std::string codigo, const Obra* O);
};



class AbrirGuardarBC3 : public AbrirGuardar
{
public:

    AbrirGuardarBC3();
    Obra*  Leer(std::ifstream &ifs);
    Obra*  Leer(QString nombrefichero);
    void procesarConceptos(Obra* &obra, QStringList& registroC);
    void procesarRelaciones (Obra* &obra, QString linea);
    MedCert procesarMediciones (std::list<std::string>&listaM, std::string nombrepadre, std::string nombrehijo);
    void procesarTexto(Obra* &obra, const QStringList& registroT);

    void Escribir(std::ofstream &ofs);
    void EscribirRegistroV(std::ofstream &ofs);
    void EscribirRegistroK(std::ofstream &ofs);
    void EscribirRegistroC(const pNodo concepto, std::ofstream &ofs, const Obra* obra);
    void EscribirRegistroD(const pNodo concepto, std::ofstream &ofs, const Obra* obra);
    void EscribirRegistroM(pArista A, std::ofstream &ofs, const Obra* obra);
    void EscribirRegistroT(const pNodo concepto, std::ofstream &ofs);

    bool esRaiz(const QString &S);
    void quitarSimbolos (pNodo n);
    void quitarSimbolos(TEXTO &codigo);
    void escribirAlmohadilla(const pNodo concepto, const Obra* obra, std::string &cadena);
    pNodo buscarPadre(const pArista A, const Obra* obra);

    char NuevaLinea;
    char RetornoCarro;
    char FinDeArchivo;

    template <typename T>
    std::string tostr(const T& t);
};

#endif // ABRIRGUARDAR_H
