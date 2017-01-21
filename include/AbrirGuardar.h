#ifndef ABRIRGUARDAR_H
#define ABRIRGUARDAR_H


#include <fstream>
#include <sstream>
#include <string>
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
        virtual void Escribir(QFile& fichero, const Obra* obra) = 0;
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



class AbrirGuardarBC3 : public AbrirGuardar
{
public:

    AbrirGuardarBC3();
    Obra*  Leer(std::ifstream &ifs);
    Obra*  Leer(TEXTO nombrefichero);
    void procesarConceptos(Obra* &obra, QStringList& registroC);
    void procesarRelaciones (Obra* &obra, QString linea, QStringList& registroM);
    MedCert procesarMediciones (QStringList& registroM, TEXTO nombrepadre, TEXTO nombrehijo);
    void procesarTexto(Obra* &obra, const QStringList& registroT);

    void Escribir(QFile& fichero,const Obra* obra);
    void EscribirRegistroV(TEXTO& cadena);
    void EscribirRegistroK(TEXTO &cadena);
    void EscribirRegistroC(const pNodo concepto, TEXTO &cadena, const Obra* obra);
    void EscribirRegistroD(const pNodo concepto, TEXTO &cadena, const Obra* obra);
    void EscribirRegistroM(pNodo padre, pArista A, TEXTO &cadena, const Obra* obra);
    void EscribirRegistroT(const pNodo concepto, TEXTO &cadena);

    bool esRaiz(const QString &S);
    void quitarSimbolos (pNodo n);
    void quitarSimbolos(TEXTO &codigo);
    void escribirAlmohadilla(const pNodo concepto, const Obra* obra, TEXTO &cadena);

    char NuevaLinea;
    char RetornoCarro;
    char FinDeArchivo;

    template <typename T>
    std::string tostr(const T& t);
};

#endif // ABRIRGUARDAR_H
