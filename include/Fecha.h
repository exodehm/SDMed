#ifndef FECHA_H
#define FECHA_H

#include <ctime>
#include <string>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <cstring>

class Dia
{
private:
    char dia[3];

public:
    Dia();
    Dia(char* d);
    Dia(std::string d);

    const char* LeeDia() const;
    void EscribeDia(const char* d);
    void EscribeDia (const std::string s);
    void EscribeDia (const Dia& d);

    Dia& operator=(const Dia& d);

    friend std::ostream& operator <<(std::ostream& os, const Dia& d);
    friend std::istream& operator >>(std::istream& is, Dia& d);
};


class Mes
{
private:
    char mes[3];

public:
    Mes();
    Mes(char* m);
    Mes(std::string m);

    const char* LeeMes() const;
    void EscribeMes(const char* m);
    void EscribeMes (const std::string m);
    void EscribeMes (const Mes& m);

    Mes& operator=(const Mes& m);

    friend std::ostream& operator <<(std::ostream& os, const Mes& m);
    friend std::istream& operator >>(std::istream& is, Mes& m);
};

class Anno
{
private:
    char anno[5];

public:
    Anno();
    Anno(char* a);
    Anno(std::string a);

    const char* LeeAnno() const;
    void EscribeAnno(const char* a);
    void EscribeAnno (const std::string a);
    void EscribeAnno (const Anno& a);

    Anno& operator=(const Anno& a);

    friend std::ostream& operator <<(std::ostream& os, const Anno& a);
    friend std::istream& operator >>(std::istream& is, Anno& a);
};

class Fecha
{
public:
    //constructores
    Fecha();//construye una fecha con la fecha actual
    Fecha (const Fecha& f);
    Fecha(std::string& f);//construye una fecha a partir de una cadena
    Fecha (const char* c);
    Fecha(const Dia& d,const Mes& m,const Anno& a);
    Fecha& operator=(const Fecha& f);
    //destructor
    /*virtual ~Fecha();*/
    //metodos consultores y modificadores
    Dia LeeDia() const;
    Mes LeeMes() const;
    Anno LeeAnno() const;
    std::string LeeFecha() const;

    void EscribeDia(const Dia& d);
    void EscribeMes(const Mes& m);
    void EscribeAnno(const Anno& a);
    void EscribeFecha(std::string f);
    std::string PasarAString();
    //funciones miembro
    /*void imprimir();
    bool valid() const;
    //operador de asignacion

    //sobrecarga de operadores
    friend bool operator == (const Fecha& d1,const Fecha& d2);
    friend bool operator != (const Fecha& d1,const Fecha& d2);
    friend bool operator < (const Fecha& d1,const Fecha& d2);
    friend bool operator > (const Fecha& d1,const Fecha& d2);
    friend bool operator <= (const Fecha& d1,const Fecha& d2);
    friend bool operator >= (const Fecha& d1,const Fecha& d2);*/

    friend std::ostream& operator <<(std::ostream& os, const Fecha& efe);
    friend std::istream& operator >>(std::istream& os, Fecha& efe);


private:
    Dia dia;
    Mes mes;
    Anno anno;
};

#endif // FECHA_H
