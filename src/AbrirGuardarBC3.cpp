#include "../include/AbrirGuardar.h"

#include <typeinfo>

Obra*  AbrirGuardarBC3::Leer(QString nombrefichero)
{
    Obra* obra = nullptr;//= new Obra;
    QFile fichero(nombrefichero);
    if(!fichero.open(QIODevice::ReadOnly))
    {
        qFatal("No puedo abrir el fichero");
        return obra;
    }
    QTextStream datos(&fichero);
    datos.setCodec("Windows-1252");
    QStringList registros = datos.readAll().split('~');
    QStringList registroD;
    QStringList registroM;
    QStringList registroC;
    QStringList registroT;

    foreach (QString linea, registros)
    {
        if (linea[0]=='C')
        {
            linea.chop(2);
            linea.remove(0,2);
            //qDebug()<<linea;
            registroC.append(linea);
        }
        if (linea[0]=='D' && linea[1]=='|')
        {
            linea.chop(2);
            linea.remove(0,2);
            //qDebug()<<linea;
            registroD.append(linea);
        }
        if (linea[0]=='M')
        {
            linea.chop(2);
            linea.remove(0,2);
            //qDebug()<<linea;
            registroM.append(linea);
        }
        if (linea[0]=='T')
        {
            linea.chop(2);
            linea.remove(0,2);
            //qDebug()<<linea;
            registroT.append(linea);
        }
    }
    //empiezo construyendo el grafo solo con los codigos-->registroD
    foreach (QString linea, registroD)
    {
        procesarRelaciones(obra,linea);
    }
    procesarConceptos(obra,registroC);
    procesarTexto(obra,registroT);
    fichero.close();
    return obra;
}

void AbrirGuardarBC3::procesarRelaciones (Obra* &obra, QString linea)
{
    //Miro si el registro tiene 2 o 3 campos
    //3 campos->verson FIEBDC-3/2012->tener en cuenta porcentajes
    //2 campos->version anterior->no considera porcentajes

    QStringList lista = linea.split("|");
    TEXTO padre = lista.at(0);

    int nHijos=(linea.count("\\")/3);
    int nCampos = lista.size()-1;
    TEXTO resto;
    if (nCampos == 2)
    {
        resto = lista.at(1);
    }
    else
    {
        resto = lista.at(2);
    }
    TEXTO nombreRaiz="";
    if (!obra)
    {
        obra= new Obra(padre);
    }
    //guardo el nombre de la raiz para ponerlo al principio
    if (esRaiz(padre))
    {
        nombreRaiz=padre;
    }
    quitarSimbolos(padre);

    //TEXTO nombrehijo,factor,cantidad;
    TEXTO registros[3]; //nombrehijo, factor, cantidad
    QStringList relaciones = resto.split("\\");
    for (int i=0; i<nHijos; i++)
    {
        qDebug()<<"Vuelta "<<i<<nHijos<<" - "<<relaciones.size()<<"Num hjijos: "<<nHijos;
        for (int j=0;j<3;j++)
        {
            registros[j] = relaciones.first();
            relaciones.pop_front();
        }
        for (int j=0;j<3;j++)
        {
            qDebug()<<"registros["<<j<<"]: "<<registros[j];
        }
        float cant =  registros[2].toFloat();
        qDebug()<<"Cantidad: "<<cant;
        //procesarMediciones(listaM, nombrepadre, nombrehijo);
        //MedCert medi = procesarMediciones(listaM, nombrepadre, nombrehijo);
        obra->CrearPartida(padre, cant, registros[0]);
    }
    //si tengo la raiz la pongo al comienzo
    if (nombreRaiz.length()>0)
    {
        quitarSimbolos(nombreRaiz);
        obra->EscribeRaiz(nombreRaiz);
    }
}

void AbrirGuardarBC3::procesarConceptos(Obra* &obra, QStringList &registroC)
{
    QString linea;
    foreach (linea, registroC)
    {
        QStringList datos = linea.split("|");
        for (int i=0;i<datos.size();i++)
        {
            qDebug()<<datos.at(i);
        }
        QString codigo = datos.at(0);
        codigo.remove('#');
        pNodo minodo = obra->existeConcepto(codigo);
        if (minodo)
        {
            //unidad
            Unidad U;
            int numUd= U.LeeNumUd(datos.at(1).toStdString());
            minodo->datonodo.EscribeUd(numUd);
            //resumen
            minodo->datonodo.EscribeResumen(datos.at(2));
            //cantidad
            float cantidad = datos.at(3).toFloat();
            minodo->datonodo.EscribePrecio(cantidad);
            //fecha
            std::string cadenafecha = datos.at(4).toStdString();
            Fecha F(cadenafecha);
            minodo->datonodo.EscribeFecha(F);
            //naturaleza
            /*int nat=0;
            if (datos[5][0]!='0')
            {
                nat=atoi(datos[5]);
            }
            else if (codigo.find('#')!=std::string::npos)
            {
                nat=AsignadorDeNaturaleza::Capitulo;
            }
            else
            {
                nat=AsignadorDeNaturaleza::Partida;
            }*/
        }
    }
}

MedCert AbrirGuardarBC3::procesarMediciones (std::list<std::string>&listaM, std::string nombrepadre, std::string nombrehijo)
{
    /*for (auto it = listaM.begin(); it!=listaM.end(); ++it)
    {
        std::string codpadre;
        std::string codhijo;
        std::string posicion;
        std::string total;

        std::stringstream iss(*it);
        std::getline(iss,codpadre,'\\');
        std::getline(iss,codhijo,'|');
        std::getline(iss,posicion,'|');
        std::getline(iss,total,'|');
        quitarSimbolos(codpadre);
        std::cout<<"Codpadre: "<<codpadre<<std::endl;
        std::cout<<"Codhijo: "<<codhijo<<std::endl;

        if (codpadre == nombrepadre && codhijo == nombrehijo)
        {
            std::cout<<"total: "<<total<<std::endl;
            std::cout<<"medicion: "<<iss.str()<<std::endl;
            std::cout<<codpadre<<" - "<<codhijo<<" - "<<std::endl;
            //int n;std::cin>>n;
            Medicion eme;
            while (iss.peek()!='|')
            {
                std::string conceptos[6];
                for (int i=0; i<6; i++)
                {
                    std::getline (iss,conceptos[i],'\\');
                    //std::cout<<"Concepto["<<i<<"]= "<<conceptos[i]<<std::endl;
                }
                //int n;std::cin>>n;
                float cantidades[4];
                for (int i=0; i<4; i++)
                {
                    (conceptos[i+2].length()>0 ? cantidades[i]=std::atof(conceptos[i+2].c_str()) : cantidades[i]=0);
                }
                int tipo;
                if (conceptos[0].size()==0)
                {
                    tipo=0;
                }
                else
                {
                    tipo=std::atoi(conceptos[0].c_str());
                }
                eme.Insertar(tipo,conceptos[1],cantidades[0],cantidades[1],cantidades[2],cantidades[3]);
            }
            MedCert MC;
            MC.EscribeMedicion(eme);
            listaM.erase(it);
            return MC;

        }
        else
        {
            return MedCert();
        }
    }*/
}

void AbrirGuardarBC3::procesarTexto(Obra *&obra,const QStringList &registroT)
{    
    QString linea;
    foreach (linea, registroT)
    {
        QStringList datos = linea.split("|");
        QString codigo = datos.at(0);
        codigo.remove('#');
        pNodo minodo = obra->existeConcepto(codigo);
        if (minodo)
        {
            minodo->datonodo.EscribeTexto(datos.at(1));
        }
    }
}

/*********************GUARDAR****************************************/

void AbrirGuardarBC3::Escribir(std::ofstream &ofs )
{
    EscribirRegistroV(ofs);
    EscribirRegistroK(ofs);
    /********Registros C y D**************/
    /*pNodo indice=obra->G.Raiz;
    for (int i=0; i<obra->G.LeeNumNodos(); i++)
    {
        EscribirRegistroC(indice,ofs,obra);
        if (indice->adyacente)
        {
            EscribirRegistroD(indice,ofs,obra);
        }
        indice=indice->siguiente;
    }*/
    /*******Registro M y N************/
    /*std::pair<pArista,int>P;
    P.first=obra->G.LeeRaiz()->adyacente;
    P.second=0;
    std::list<pArista>lista;
    TratarAristaConNiveles *tratamiento = new VerAlgo(P,lista);
    obra->G.recorrerGrafoConNiveles(obra->G.LeeRaiz(),*tratamiento,0);
    for (auto it=lista.begin();it!=lista.end();it++)
    {
        EscribirRegistroM ((*it),ofs,obra);
    }*/
    /**vuelvo al inicio para agrupar todos los textos**/

    /******************Registro T*************/
    /*indice=obra->G.LeeRaiz();
    for (int i=0; i<obra->G.LeeNumNodos(); i++)
    {
        if (!indice->datonodo.LeeTexto().empty())
        {
            EscribirRegistroT(indice,ofs);
        }
        indice=indice->siguiente;
    }*/
    ofs<<FinDeArchivo;
}

void AbrirGuardarBC3::EscribirRegistroV(std::ofstream &ofs)
{
    std::string registroV="~V|EGSOFT S.A.|FIEBDC-3/2012|SDMed 1.0||ANSI||||||";
    /*ofs.write(registroV.c_str(),registroV.size());*/
    ofs<<registroV;
    ofs<<NuevaLinea;
    ofs<<RetornoCarro;
}

void AbrirGuardarBC3::EscribirRegistroK(std::ofstream &ofs)
{
    std::string registroK="~K|\\2\\2\\3\\2\\2\\2\\2\\EUR\\|0|";
    ofs<<registroK;
    ofs<<NuevaLinea;
    ofs<<RetornoCarro;
}

void AbrirGuardarBC3::EscribirRegistroC(const pNodo concepto, std::ofstream &ofs, const Obra* obra)
{
    /*std::string registroC="~C|";
    registroC.append(concepto->datonodo.LeeCodigo());
    escribirAlmohadilla(concepto,obra,registroC);
    registroC.append("|");
    registroC.append(concepto->datonodo.LeeUd());
    registroC.append("|");
    registroC.append(concepto->datonodo.LeeResumen());
    registroC.append("|");
    registroC.append(tostr(concepto->datonodo.LeeImportePres()));
    registroC.append("|");
    registroC.append(concepto->datonodo.LeeFecha());
    registroC.append("|");
    registroC.append(tostr(concepto->datonodo.LeeNat()));
    registroC.append("|");
    ofs<<registroC;
    ofs<<"\r\n";*/
}

void AbrirGuardarBC3::EscribirRegistroD(const pNodo concepto, std::ofstream &ofs, const Obra* obra)
{
    /*std::string factor="1";//por ahora factor vale 1...en el futuro puede tener un valor
    std::string registroD="~D|";
    registroD.append(concepto->datonodo.LeeCodigo());
    escribirAlmohadilla(concepto,obra,registroD);
    registroD.append("|");
    if (concepto->adyacente)
    {
        pArista A=concepto->adyacente;
        while (A)
        {
            registroD.append(A->destino->datonodo.LeeCodigo());
            registroD.append("\\");
            registroD.append(factor);
            registroD.append("\\");
            registroD.append(tostr(A->datoarista.LeeMedicion().LeeTotal()));
            registroD.append("\\");
            A=A->siguiente;
        }
    }
    registroD.append("|");
    ofs<<registroD;
    ofs<<"\r\n";*/
}

void AbrirGuardarBC3::EscribirRegistroM(pArista A, std::ofstream &ofs, const Obra* obra)
{
    /*std::string registroM="~M|";

    pNodo padre = buscarPadre (A,obra);
    registroM.append(padre->datonodo.LeeCodigo());
    escribirAlmohadilla(padre,obra,registroM);
    registroM.append("\\");
    registroM.append(A->destino->datonodo.LeeCodigo());
    registroM.append("||");//por ahora obvio el campo de POSICION
    registroM.append(tostr(A->datoarista.LeeMedicion().LeeTotal()));
    registroM.append("|");
    ofs<<registroM;

    /********empezamos con las lineas de medicion******************/
    /*for (auto it=A->datoarista.LeeMedicion().LeeLista().begin(); it!=A->datoarista.LeeMedicion().LeeLista().end(); ++it)
    {
        ofs<<(*it).LeeTipo()<<"\\"<<(*it).LeeComentario()<<"\\"<<(*it).Lee_N_Uds()<<"\\"<<(*it).LeeLargo()<<"\\"
           <<(*it).LeeAncho()<<"\\"<<(*it).LeeAlto()<<"\\";
    }
    ofs<<"|";
    ofs<<"\r\n";*/
}

void AbrirGuardarBC3::EscribirRegistroT(const pNodo concepto, std::ofstream &ofs)
{
   /* std::string registroT="~T|";
    registroT.append(concepto->datonodo.LeeCodigo());
    registroT.append("|");
    registroT.append(concepto->datonodo.LeeTexto());
    registroT.append("|");
    ofs<<registroT;
    ofs<<"\r\n";*/
}

/*********************VARIOS**************************/
bool AbrirGuardarBC3::esRaiz(const QString& S)
{
    return (S.at(S.length()-1)=='#' && S.at(S.length()-2)=='#');
}

void AbrirGuardarBC3::quitarSimbolos (pNodo n)
{
    /*std::size_t posicion=n->datonodo.LeeCodigo().find('#');
    if (posicion!=std::string::npos)
    {
        n->datonodo.EscribeCodigo(n->datonodo.LeeCodigo().substr(0,posicion));
    }*/
}

void AbrirGuardarBC3::quitarSimbolos (TEXTO &codigo)
{
    int posicion=-1;
    posicion = codigo.indexOf('#');
    if (posicion>0 || posicion==0)
    {
        codigo.truncate(posicion);
    }
}

void AbrirGuardarBC3::escribirAlmohadilla(const pNodo concepto, const Obra* obra, std::string &cadena)
{
    /*if (concepto==obra->G.LeeRaiz())
    {
        cadena.append("##");
    }
    if (obra->G.LeeRaiz()->adyacente)
    {
        pArista A=obra->G.LeeRaiz()->adyacente;
        while (A)
        {
            if (concepto==A->destino)
            {
                cadena.append("#");
            }
            A=A->siguiente;
        }
    }*/
}

AbrirGuardarBC3::pNodo AbrirGuardarBC3::buscarPadre(const pArista A, const Obra* obra)
{
    /*pNodo indice=obra->G.LeeRaiz();
    while (indice)
    {
        if (indice->adyacente)
        {
            pArista aux=indice->adyacente;
            while (aux)
            {
                if(aux==A)
                {
                    return indice;
                }
                aux=aux->siguiente;
            }
        }
        indice=indice->siguiente;
    }*/
    return 0;
}

template <typename T>
std::string AbrirGuardarBC3::tostr(const T& t)
{
    std::ostringstream os;
    os<<t;
    return os.str();
}


