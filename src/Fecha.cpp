#include "../include/Fecha.h"

/***************dia*****************************/
Dia::Dia()
{
    std::stringstream iss;
    struct tm *tiempo;
    time_t fecha_sistema;
    time(&fecha_sistema);
    tiempo=localtime(&fecha_sistema);

    int Dia = tiempo->tm_mday;
    if (Dia<10)
    {
        dia[0]='0';
        iss<<Dia;
        iss>>dia[1];
    }
    else
    {
        iss<<Dia/10;
        iss>>dia[0];
        iss<<Dia%10;
        iss>>dia[1];
    }
    dia[2]='\0';
}

Dia::Dia(char* d)
{
    EscribeDia(d);
}

Dia::Dia(std::string d)
{
    EscribeDia(d.c_str());
}

const char* Dia::LeeDia() const
{
    return dia;
}

void Dia::EscribeDia(const char* d)
{
    if (strlen(d)==0)
    {
        dia[0]='0';
        dia[1]='0';
        dia[2]='\0';
    }
    else if (strlen(d)==1)//un digito
    {
        dia[0]='0';
        dia[1]=d[0];
        dia[2]=d[1];
    }
    else
    {
        dia[0]=d[0];
        dia[1]=d[1];
        dia[2]='\0';
    }
}

void Dia::EscribeDia(const std::string d)
{
    EscribeDia(d.c_str());
}

void Dia::EscribeDia(const Dia& d)
{
    EscribeDia(d.LeeDia());
}


Dia& Dia::operator=(const Dia& d)
{
    if (this!=&d)
    {
        strncpy(dia,d.dia,3);
    }
    return *this;
}

bool Dia::operator<= (Dia& d)
{
    int dia1, dia2;
    std::stringstream sdia1(this->LeeDia());
    std::stringstream sdia2(d.LeeDia());
    sdia1 >> dia1;
    sdia2 >> dia2;
    return dia1 <= dia2;
}

bool Dia::operator > (Dia& d)
{
    int dia1, dia2;
    std::stringstream sdia1(this->LeeDia());
    std::stringstream sdia2(d.LeeDia());
    sdia1 >> dia1;
    sdia2 >> dia2;
    return dia1 > dia2;
}

bool Dia::operator < (Dia& d)
{
    int dia1, dia2;
    std::stringstream sdia1(this->LeeDia());
    std::stringstream sdia2(d.LeeDia());
    sdia1 >> dia1;
    sdia2 >> dia2;
    return dia1 < dia2;;
}

std::ostream& operator <<(std::ostream& os, const Dia& d)
{
    os<<d.dia[0]<<d.dia[1];
    return os;
}

std::istream& operator >>(std::istream& is, Dia& d)
{
    is>>d.dia[0]>>d.dia[1];
    return is;
}

/********************mes**************************/
Mes::Mes()
{
    std::stringstream iss;
    struct tm *tiempo;
    time_t fecha_sistema;
    time(&fecha_sistema);
    tiempo=localtime(&fecha_sistema);
    int Mes = tiempo->tm_mon + 1;
    if (Mes<10)
    {
        mes[0]='0';
        iss<<Mes;
        iss>>mes[1];
    }
    else
    {
        iss<<Mes/10;
        iss>>mes[0];
        iss<<Mes%10;
        iss>>mes[1];
    }
    mes[2]='\0';
}

Mes::Mes(char* m)
{
    EscribeMes(m);
}

Mes::Mes(std::string m)
{
    EscribeMes(m.c_str());
}

const char* Mes::LeeMes() const
{
    return mes;
}

void Mes::EscribeMes(const char* m)
{
    if (strlen(m)==0)
    {
        mes[0]='0';
        mes[1]='0';
        mes[2]='\0';
    }
    else if (strlen(m)==1)//un digito
    {
        mes[0]='0';
        mes[1]=m[0];
        mes[2]=m[1];
    }
    else
    {
        mes[0]=m[0];
        mes[1]=m[1];
        mes[2]=m[2];
    }
}

void Mes::EscribeMes(const std::string m)
{
    EscribeMes(m.c_str());
}

void Mes::EscribeMes(const Mes& m)
{
    EscribeMes(m.LeeMes());
}

Mes& Mes::operator=(const Mes& m)
{
    if (this!=&m)
    {
        strncpy(mes,m.mes,3);
    }
    return *this;
}

bool Mes:: operator <= (Mes& m)
{
    int mes1, mes2;
    std::stringstream smes1(this->LeeMes());
    std::stringstream smes2(m.LeeMes());
    smes1 >> mes1;
    smes2 >> mes2;
    return mes1 <= mes2;

}
bool Mes::operator > (Mes& m)
{
    int mes1, mes2;
    std::stringstream smes1(this->LeeMes());
    std::stringstream smes2(m.LeeMes());
    smes1 >> mes1;
    smes2 >> mes2;
    return mes1 > mes2;
}
bool Mes::operator < (Mes& m)
{
    int mes1, mes2;
    std::stringstream smes1(this->LeeMes());
    std::stringstream smes2(m.LeeMes());
    smes1 >> mes1;
    smes2 >> mes2;
    return mes1 < mes2;
}

std::ostream& operator <<(std::ostream& os, const Mes& m)
{
    os<<m.mes[0]<<m.mes[1];
    return os;
}

std::istream& operator >>(std::istream& is, Mes& m)
{
    is>>m.mes[0]>>m.mes[1];
    return is;
}

/****************anno**************************/
Anno::Anno()
{
    std::stringstream iss;
    struct tm *tiempo;
    time_t fecha_sistema;
    time(&fecha_sistema);
    tiempo=localtime(&fecha_sistema);
    int Anno = tiempo->tm_year + 1900;
    iss<<Anno/1000;
    iss>>anno[0];
    int aux=Anno%1000;
    iss<<aux/100;
    iss>>anno[1];
    aux=aux%100;
    iss<<aux/10;
    iss>>anno[2];
    aux=aux%10;
    iss<<aux;
    iss>>anno[3];
    anno[4]='\0';
}

Anno::Anno(char* a)
{
    for (int i=0; i<=4; i++)
    {
        anno[i]=a[i];
    }
}

Anno::Anno(std::string a)
{
    EscribeAnno(a.c_str());
}

const char* Anno::LeeAnno() const
{
    return anno;
}

void Anno::EscribeAnno(const char* a)
{
    if (strlen(a)==2)
    {
        if (a[0]>='8')
        {
            anno[0]='1';
            anno[1]='9';
        }
        else
        {
            anno[0]='2';
            anno[1]='0';

        }
        anno[2]=a[0];
        anno[3]=a[1];
        anno[4]='\0';
    }
    else
    {
        anno[0]=a[0];
        anno[1]=a[1];
        anno[2]=a[2];
        anno[3]=a[3];
        anno[4]='\0';
    }
}

void Anno::EscribeAnno (const std::string a)
{
    EscribeAnno(a.c_str());
}

void Anno::EscribeAnno (const Anno& a)
{
    EscribeAnno(a.LeeAnno());
}

Anno& Anno::operator=(const Anno& a)
{
    if (this!=&a)
    {
        strncpy(anno,a.anno,5);
    }
    return *this;
}

bool Anno::operator<= (Anno& a)
{
    int anno1, anno2;
    std::stringstream sanno1(this->LeeAnno());
    std::stringstream sanno2(a.LeeAnno());
    sanno1 >> anno1;
    sanno2 >> anno2;
    return anno1 <= anno2;
}

bool Anno::operator > (Anno& a)
{
    int anno1, anno2;
    std::stringstream sanno1(this->LeeAnno());
    std::stringstream sanno2(a.LeeAnno());
    sanno1 >> anno1;
    sanno2 >> anno2;
    return anno1 > anno2;
}

bool Anno::operator < (Anno& a)
{
    int anno1, anno2;
    std::stringstream sanno1(this->LeeAnno());
    std::stringstream sanno2(a.LeeAnno());
    sanno1 >> anno1;
    sanno2 >> anno2;
    return anno1 < anno2;
}

std::ostream& operator <<(std::ostream& os, const Anno& a)
{
    os<<a.anno[0]<<a.anno[1]<<a.anno[2]<<a.anno[3];
    return os;
}

std::istream& operator >>(std::istream& is, Anno& a)
{
    is>>a.anno[0]>>a.anno[1]>>a.anno[2]>>a.anno[3];
    return is;
}


Fecha::Fecha():dia(),mes(),anno() {}

Fecha::Fecha (const Fecha& f)
{
    dia=f.dia;
    mes=f.mes;
    anno=f.anno;
}

Fecha::Fecha(const Dia& d,const Mes& m,const Anno& a):dia(d),mes(m),anno(a) {}

Fecha::Fecha(std::string f)
{
    EscribeFecha(f);
}

Fecha::Fecha(const char* c)
{
    std::stringstream ss;
    ss<<c;
    EscribeFecha(ss.str());
}

Fecha& Fecha::operator=(const Fecha& f)
{
    if (this!=&f)
    {
        dia=f.dia;
        mes=f.mes;
        anno=f.anno;
    }
    return *this;
}


void Fecha::EscribeFecha(std::string f)
{
    if (f.size()==8)
    {
        dia.EscribeDia(f.substr(0,2).c_str());
        mes.EscribeMes(f.substr(2,2).c_str());
        anno.EscribeAnno(f.substr(4,4).c_str());
    }
    else if (f.size()==7)
    {
        dia.EscribeDia(f.substr(0,1).c_str());
        mes.EscribeMes(f.substr(1,2).c_str());
        anno.EscribeAnno(f.substr(3,4).c_str());
    }
    else if (f.size()==6)
    {
        dia.EscribeDia(f.substr(0,2).c_str());
        mes.EscribeMes(f.substr(2,2).c_str());
        anno.EscribeAnno(f.substr(4,2).c_str());
    }
    else if (f.size()==5)
    {
        dia.EscribeDia(f.substr(0,1).c_str());
        mes.EscribeMes(f.substr(1,2).c_str());
        anno.EscribeAnno(f.substr(3,2).c_str());
    }
    else if (f.size()==4)
    {
        dia.EscribeDia(f.substr(0,0).c_str());
        mes.EscribeMes(f.substr(0,2).c_str());
        anno.EscribeAnno(f.substr(2,2).c_str());
    }
    else if (f.size()==3)
    {
        dia.EscribeDia(f.substr(0,0).c_str());
        mes.EscribeMes(f.substr(0,1).c_str());
        anno.EscribeAnno(f.substr(1,2).c_str());
    }
    else if (f.size()==2)
    {
        dia.EscribeDia(f.substr(0,0).c_str());
        mes.EscribeMes(f.substr(0,0).c_str());
        anno.EscribeAnno(f.substr(0,2).c_str());
    }
}

Dia Fecha::LeeDia() const
{
    return dia;
}

Mes Fecha::LeeMes() const
{
    return mes;
}

Anno Fecha::LeeAnno() const
{
    return anno;
}

std::string Fecha::LeeFecha() const
{
    std::string fecha;
    fecha.append(std::string(LeeDia().LeeDia()));
    fecha.append(std::string(LeeMes().LeeMes()));
    fecha.append(std::string(LeeAnno().LeeAnno()));
    return fecha;
}

void Fecha::EscribeDia(const Dia& d)
{
    dia.EscribeDia(d);
}
void Fecha::EscribeMes(const Mes& m)
{
    mes.EscribeMes(m);
}
void Fecha::EscribeAnno(const Anno& a)
{
    anno.EscribeAnno(a);
}

std::string Fecha::PasarAString()
{
    std::stringstream ss;
    ss<<dia<<mes<<anno;
    return ss.str();
}
bool Fecha::operator<=(Fecha &f)
{
    //return f.LeeAnno()<=this->LeeAnno();
    /*int anno1, anno2;
    stringstream sanno1(f.LeeAnno());
    stringstream sanno2(anno2);
    sanno1 >> anno1;
    sanno2 >> anno2;
    std::cout<<LeeAnno()<<"vs"<<f.LeeAnno();*/
    Anno anno1 = LeeAnno();
    Anno anno2 = f.LeeAnno();
    return anno1<=anno2;
}

bool Fecha::operator > (Fecha &f)
{
    //return f.LeeAnno()<=this->LeeAnno();
    /*int anno1, anno2;
    stringstream sanno1(f.LeeAnno());
    stringstream sanno2(anno2);
    sanno1 >> anno1;
    sanno2 >> anno2;
    std::cout<<LeeAnno()<<"vs"<<f.LeeAnno();*/
    Anno anno1 = LeeAnno();
    Anno anno2 = f.LeeAnno();
    if(anno1 > anno2)
    {
        return true;
    }
    else if(anno1 < anno2)
    {
        return false;
    }
    else
    {
        Mes mes1 = LeeMes();
        Mes mes2 = f.LeeMes();
        if (mes1 > mes2)
        {
            return true;
        }
        else if (mes1 < mes2)
        {
            return false;
        }
        else
        {
            Dia dia1 = LeeDia();
            Dia dia2 = f.LeeDia();
            if (dia1 > dia2)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
    return false;
}

/*
void Fecha::imprimir()
{
    std::cout<<dia<<" - "<<mes<<" - "<<anno<<std::endl;
}

bool Fecha::valid() const
{
// This function will check the given date is valid or not.
// If the date is not valid then it will return the value false.
// Need some more checks on the anno, though
//    if (anno <0) return false;
    if (mes >12 ||mes <1) return false;
    if (dia >31 || dia <1) return false; //cuidado que FIEBCD acepta dias y meses ==0
    if ((dia==31 && (mes==2 || mes==4 || mes==6 || mes ==9 || mes ==11))) return false;
    if (dia ==30 && mes ==2) return false;//febrero
    if (anno <2000)
    {
        if((dia==29 && mes==2) && !((anno-1900)%4==0))return false;
    };
    if (anno>2000)
    {
        if((dia==29 &&mes==2) && !((anno-2000)%4==0))return false;
    };
    return true;
}

Fecha& Fecha::operator=(const Fecha& f)
{
    if (this!=&f)
    {
        dia=f.dia;
        mes=f.mes;
        anno=f.anno;
    }
    return *this;
}

bool operator == (const Fecha& d1, const Fecha& d2)
{
    if(!d1.valid())
    {
        return false;
    }
    if(!d2.valid())
    {
        return false;
    }
    if((d1.LeeDia()==d2.LeeDia())&& (d1.LeeMes()==d2.LeeMes())&& (d1.LeeAnno()==d2.LeeAnno()))
    {
        return true;
    }
    return false;
}

bool operator != (const Fecha& d1, const Fecha& d2)
{
    return !(d1==d2);
}

bool operator < (const Fecha& d1, const Fecha& d2)
{
    if(!d1.valid())
    {
        return false;
    }
    if(!d2.valid())
    {
        return false;
    }
    if(d1.LeeAnno() < d2.LeeAnno())
    {
        return true;
    }
    else if(d1.LeeAnno() > d2.LeeAnno())
    {
        return false;
    }
    else  // mismo año
    {
        if (d1.LeeMes() < d2.LeeMes())
        {
            return true;
        }
        else if (d1.LeeMes() > d2.LeeMes())
        {
            return false;
        }
        else  // mismo mes
        {
            if (d1.LeeDia() < d2.LeeDia())
            {
                return true;
            }
            else
            {
                return false;
            }
        };
    };
    return false;
}

bool operator > (const Fecha& d1, const Fecha& d2)
{
    if(d1==d2)
    {
        return false;
    }
    if(d1<d2)
    {
        return false;
    }

    return true;
}
bool operator <= (const Fecha& d1, const Fecha& d2)
{
    if(d1==d2)
    {
        return true;
    }
    return (d1<d2);
}

bool operator >= (const Fecha& d1, const Fecha& d2)
{
    if (d1==d2)
    {
        return true;
    }
    return (d1 > d2);
}

Fecha::~Fecha()
{
    //dtor
}*/

std::ostream& operator <<(std::ostream& os, const Fecha& efe)
{
    os<<efe.dia<<"-"<<efe.mes<<"-"<<efe.anno;
    return os;
}

std::istream& operator >>(std::istream& is, Fecha& efe)
{
    is>>efe.dia>>efe.mes>>efe.anno;
    return is;
}
