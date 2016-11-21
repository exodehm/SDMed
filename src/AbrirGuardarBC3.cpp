#include "../include/AbrirGuardar.h"

#include <typeinfo>

Obra* AbrirGuardarBC3::Leer(std::ifstream &ifs)
{

    Obra* obra;//= new Obra;
    const int MAXCHAR = 100000;
    char registro[MAXCHAR];
    std::list<std::string>listaD;
    std::list<std::string>listaM;
    std::list<std::string>listaC;
    std::list<std::string>listaT;
    /**********************************/
    /**********crear lista D***********/
    /**********************************/
    while (!ifs.eof())
    {
        ifs.getline (registro,MAXCHAR,'~');
        if (registro[0]=='D')
        {
            listaD.push_back(&registro[2]);
        }
    }
    /**********************************/
    /**********crear lista M***********/
    /**********************************/
    ifs.seekg(0,std::ios::beg);
    while (!ifs.eof())
    {
        ifs.getline (registro,MAXCHAR,'~');
        if (registro[0]=='M')
        {
            listaM.push_back(&registro[2]);
        }
    }
    /**********************************/
    /**********crear lista C***********/
    /**********************************/
    ifs.seekg(0,std::ios::beg);
    while (!ifs.eof())
    {
        ifs.getline (registro,MAXCHAR,'~');
        if (registro[0]=='C')
        {
            listaC.push_back(&registro[2]);
        }
    }
    /**********************************/
    /**********crear lista T***********/
    /**********************************/
    ifs.seekg(0,std::ios::beg);
    while (!ifs.eof())
    {
        ifs.getline (registro,MAXCHAR,'~');
        if (registro[0]=='T')
        {
            listaT.push_back(&registro[2]);
        }
    }
    /***********************************/
    /********Registro D*****************/
    /***********************************/
    std::cout<<"Procesar registro D"<<std::endl;
    for (auto elem = listaD.begin();elem!=listaD.end();++elem)
    {
        std::cout<<*elem<<std::endl;
        procesarRelaciones(obra, *elem,listaM);
    }
    /***********************************/
    /********Registro C*****************/
    /***********************************/
    std::cout<<"Procesar registro C"<<std::endl;
    ifs.seekg(0,std::ios::beg);
    while (!ifs.eof())
    {
        ifs.getline (registro,MAXCHAR,'~');
        if (registro[0]=='C')
        {
            procesarConceptos(obra, &registro[2], listaT);
        }
    }
    /***********************************/
    /********Registros N y T************/
    /***********************************/
    /*std::cout<<"Procesar registro N"<<std::endl;
    ifs.seekg(0,std::ios::beg);
    while (!ifs.eof())
    {
        ifs.getline (registro,100000,'~');
        if (registro[0]=='N')
        {
            //std::cout<<"Procesar N"<<std::endl;
            procesarMediciones(obra, &registro[2]);
        }
        if (registro[0]=='T')
        {
            procesarTexto(obra, &registro[2]);
        }
    }*/
    std::cout<<"Salgo de Leer"<<std::endl;
    return obra;
}

void AbrirGuardarBC3::procesarRelaciones (Obra* &obra, std::string linea, std::list<std::string>&listaM)
{
    //Miro si el registro tiene 2 o 3 campos
    //3 campos->verson FIEBDC-3/2012->tener en cuenta porcentajes
    //2 campos->version anterior->no considera porcentajes
    int nHijos=0;
    int nCampos=0;
    int i=0;
    std::string nombreRaiz="";
    while (linea[i]!='\0')
    {
        if (linea[i]=='|')
        {
            nCampos++;
        }
        if (linea[i]=='\\')
        {
            nHijos++;
        }
        i++;
    }
    std::string nombrepadre,nombrehijos;
    //std::cout<<"Hijos: "<<nHijos/3<<std::endl;
    //std::cout<<"Campos: "<<nCampos-1<<std::endl;
    std::stringstream iss(linea);
    std::getline (iss,nombrepadre,'|');
    //std::getline (iss,nombrehijos,'|');
    //std::cout<<"Padre: "<<nombrepadre<<"- Num Hijos: "<<nHijos/3<<std::endl;
    if (!obra)
    {
        obra= new Obra(nombrepadre);
    }
    //guardo el nombre de la raiz para ponerlo al principio
    if (esRaiz(nombrepadre))
    {
        nombreRaiz=nombrepadre;
    }

    quitarSimbolos(nombrepadre);
    std::cout<<"Relaciones::NombrePadre: "<<nombrepadre<<std::endl;
    std::string nombrehijo,factor,cantidad;

    for (int i=0; i<nHijos/3; i++)
    {
        //std::cout<<"Vuelta "<<i<<std::endl;
        std::getline (iss,nombrehijo,'\\');
        std::getline (iss,factor,'\\');
        std::getline (iss,cantidad,'\\');
        std::cout<<"Relaciones::Hijo: "<<nombrehijo<<" Factor: "<<factor<<" Cantidad: "<<cantidad<<std::endl;

        float cant = std::atof(cantidad.c_str());
        //procesarMediciones(listaM, nombrepadre, nombrehijo);
        MedCert medi = procesarMediciones(listaM, nombrepadre, nombrehijo);
        //int n;std::cin>>n;
        obra->CrearPartida(nombrepadre, medi, nombrehijo);
    }
    //si tengo la raiz la pongo al comienzo
    if (nombreRaiz.length()>0)
    {
        quitarSimbolos(nombreRaiz);
        obra->EscribeRaiz(nombreRaiz);
    }
}

void AbrirGuardarBC3::procesarConceptos(Obra* &obra, char* linea, std::list<std::string>&listaT)
{
    //std::cout<<linea<<std::endl;
    char datos[6][200];
    std::istringstream iss(linea);
    for (int i=0; i<6; i++)
    {
        iss.getline(datos[i],200,'|');
        //std::cout<<"Dato["<<i<<"]: "<<datos[i]<<std::endl;
    }
    //hago una cadena para albergar el nombre del nodo
    std::string codigo(datos[0]);
    //otra cadena para el resumen
    std::string resumen(datos[2]);
    //hago una cadena para albergar los datos de la fecha y poder usar el constructor
    std::string F(datos[4]);
    Fecha fecha(F);
    //unidad
    Unidad UU;
    UU.EscribeUd(datos[1]);
    int numUd= UU.LeeNumUd(datos[1]);

    //naturaleza
    int nat=0;
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
    }
    quitarSimbolos(codigo);
    Concepto NuevoConcepto(codigo,numUd,resumen,atof(datos[3]),nat);
    NuevoConcepto.EscribeTexto(procesarTexto(listaT,codigo));
    std::cout<<"El nuevo concepto tiene un txto de: "<<NuevoConcepto.LeeTexto()<<std::endl;
    pNodo actual = obra->existeConcepto(codigo);
    if (actual)
    {
        actual->datonodo = NuevoConcepto;
    }
}

MedCert AbrirGuardarBC3::procesarMediciones (std::list<std::string>&listaM, std::string nombrepadre, std::string nombrehijo)
{
    for (auto it = listaM.begin(); it!=listaM.end(); ++it)
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
    }
}

std::__cxx11::string AbrirGuardarBC3::procesarTexto(std::list<std::string>&listaT, std::string nombrepadre)
{
    for (auto it = listaT.begin(); it!=listaT.end(); ++it)
    {
        std::string codpadre;
        std::string textocodigo;
        std::stringstream iss(*it);
        std::getline(iss,codpadre,'|');
        std::getline(iss,textocodigo,'|');
        quitarSimbolos(codpadre);


        if (codpadre == nombrepadre)
        {
            std::cout<<"Codpadre: "<<codpadre<<" - nombrpadre: "<<nombrepadre<<std::endl;
            std::cout<<"TextoCodigo: "<<textocodigo<<std::endl;
            //listaT.erase(it);
            return textocodigo;
        }
    }
    return "";

            /*std::stringstream iss(linea);
    std::string datos[2];
    for (int i=0; i<2; i++)
    {
        std::getline (iss,datos[i],'|');
    }
    std::size_t posicion=datos[0].find('#');
    if (posicion!=std::string::npos)
    {
        datos[0]=datos[0].substr(0,posicion);
    }
    //std::cout<<"Código: "<<datos[0]<<std::endl;
    pNodo nodoPadre=buscaNodoPorCodigo(datos[0],obra);
    //std::cout<<nodoPadre->datonodo.LeeCodigo()<<std::endl;
    nodoPadre->datonodo.EscribeTexto(datos[1]);*/
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
    std::string registroC="~C|";
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
    ofs<<"\r\n";
}

void AbrirGuardarBC3::EscribirRegistroD(const pNodo concepto, std::ofstream &ofs, const Obra* obra)
{
    std::string factor="1";//por ahora factor vale 1...en el futuro puede tener un valor
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
    ofs<<"\r\n";
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
    std::string registroT="~T|";
    registroT.append(concepto->datonodo.LeeCodigo());
    registroT.append("|");
    registroT.append(concepto->datonodo.LeeTexto());
    registroT.append("|");
    ofs<<registroT;
    ofs<<"\r\n";
}


/*********************VARIOS**************************/
bool AbrirGuardarBC3::esRaiz(const std::string& S)
{
    return (S[S.length()-1]=='#' && S[S.length()-2]=='#');
}

void AbrirGuardarBC3::quitarSimbolos (pNodo n)
{
    std::size_t posicion=n->datonodo.LeeCodigo().find('#');
    if (posicion!=std::string::npos)
    {
        n->datonodo.EscribeCodigo(n->datonodo.LeeCodigo().substr(0,posicion));
    }
}

void AbrirGuardarBC3::quitarSimbolos (std::string &codigo)
{
    std::size_t posicion=codigo.find('#');
    if (posicion!=std::string::npos)
    {
        codigo=codigo.substr(0,posicion);
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


