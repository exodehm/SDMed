#ifndef ABRIRGUARDAR_H
#define ABRIRGUARDAR_H


#include <fstream>
#include <sstream>
#include <string>
#include <QFile>
#include <QTextStream>
#include <QDataStream>
#include <QDebug>
#include "../include/Obra.h"
#include "../include/definiciones.h"

#include <ctime>

class AbrirGuardar
{
public:

    AbrirGuardar();
    //virtual ~AbrirGuardar();
    virtual Obra* Leer(QString nombre) = 0;
    virtual void Escribir(QFile& fichero, Obra* obra) = 0;

protected:
    char NuevaLinea;
    char RetornoCarro;
    char FinDeArchivo;
};

#endif // ABRIRGUARDAR_H
