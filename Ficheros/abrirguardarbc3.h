#ifndef ABRIRGUARDARBC3_H
#define ABRIRGUARDARBC3_H

#include <QTextDocument>

#include "./abrirguardar.h"


class AbrirGuardarBC3 : public AbrirGuardar
{
public:

    AbrirGuardarBC3();
    Obra*  Leer(std::ifstream &ifs);
    Obra*  Leer(TEXTO nombrefichero);
    void procesarConceptos(Obra* &obra, QStringList& registroC);
    void procesarRelaciones (Obra* &obra, const QString &linea, QStringList& registroM);
    MedCert procesarMediciones (QStringList& registroM, TEXTO nombrepadre, TEXTO nombrehijo);
    void procesarTexto(Obra* &obra, const QStringList& registroT);

    void Escribir(QFile& fichero,Obra* obra);
    void EscribirRegistroV(TEXTO& cadena);
    void EscribirRegistroK(TEXTO &cadena);
    void EscribirRegistroC(const pNodo concepto, TEXTO &cadena, const Obra* obra);
    void EscribirRegistroD(const pNodo concepto, TEXTO &cadena, const Obra* obra);
    void EscribirRegistroM(pNodo padre, pArista A, TEXTO &cadena, const Obra* obra);
    void EscribirRegistroT(const pNodo concepto, TEXTO &cadena);

    bool esRaiz(const QString &S);    
    void quitarSimbolos(TEXTO &codigo);
    void escribirAlmohadilla(const pNodo concepto, const Obra* obra, TEXTO &cadena);

    template <typename T>
    std::string tostr(const T& t);
};


#endif // ABRIRGUARDARBC3_H
