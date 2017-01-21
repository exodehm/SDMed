#include "../include/AbrirGuardar.h"

AbrirGuardarBC3::AbrirGuardarBC3()
{
    NuevaLinea=10;
    RetornoCarro=13;
    FinDeArchivo=0x1A;
}


/*Obra* AbrirGuardarNormal::Leer(std::ifstream &ifs )
{
    /*************variables auxiliares*********************/
    /*int numNodos;
    Concepto* C;
    pNodo nuevonodo;
    bool hoja;
    std::list<pNodo>listaNoHojas;
    /*******************************************************/
    /*ifs.read(reinterpret_cast<char*>(&numNodos),sizeof(int));
    std::cout<<"Total nodos son: "<<numNodos<<std::endl;
    C=leerConcepto(ifs);
    std::cout<<"Raiz: "<<C->LeeCodigo()<<std::endl;
    obra = new Obra(*C);
    delete C;
    //obra->G.listaHojas.clear();//otro chapú....quito la raiz de la lista de hojas porque voy a introducirla de forma manual
    ifs.read(reinterpret_cast<char*>(&hoja),sizeof(bool));
    std::cout<<"Bool= "<<hoja<<std::endl;
    //guardarNodoEnLista(hoja,listaNoHojas,obra,obra->G.LeeRaiz());

    for (int i=0; i<numNodos-1; i++)//numNodos-1`porque no cuento el raiz
    {
        C=leerConcepto(ifs);
        std::cout<<C->LeeCodigo()<<std::endl;
        nuevonodo=new nodo<Concepto,MedCert> (*C);
        //obra->G.anadirNodo(nuevonodo);
        obra->CrearPartida();
        delete C;
        ifs.read(reinterpret_cast<char*>(&hoja),sizeof(bool));
        //std::cout<<"Bool= "<<hoja<<std::endl;
        //guardarNodoEnLista(hoja,listaNoHojas,obra,nuevonodo);
    }
    //recorro cada nodo padre y le inserto las aristas
    for (auto it=listaNoHojas.begin(); it!=listaNoHojas.end(); ++it)
    {
        int numAristas=0;
        ifs.read(reinterpret_cast<char*>(&numAristas),sizeof(int));
        std::cout<<"El nodo tiene: "<<numAristas<<" aristas."<<std::endl;
        for (int i=0; i<numAristas; i++)
        {
            procesarAristas(obra,*it,ifs);
        }
    }
    obra->aristaActual=obra->G.LeeRaiz()->adyacente;
    obra->padre=obra->G.LeeRaiz();
    obra->aristaPadre->destino=obra->G.LeeRaiz();

    return obra;
}*/

Concepto* AbrirGuardarNormal::leerConcepto( std::ifstream &ifs)
{
    //tamaño de los miembros no variables
   /* int tamannoconcepto=sizeof(Unidad)+sizeof(Precio)+5*sizeof(int)+sizeof(float)+sizeof(Fecha)+sizeof(Concepto::Divisas);
    std::string sAux;
    Concepto* C=new Concepto;
    //en esta lectura capturo todos los miembros fijos
    ifs.read(reinterpret_cast<char*>(C),tamannoconcepto);
    //ahora voy a por los strings
    //codigo
    sAux=leerString(ifs);
    C->EscribeCodigo(sAux);
    //resumen
    sAux=leerString(ifs);
    C->EscribeResumen(sAux);
    //texto
    sAux=leerString(ifs);
    C->EscribeTexto(sAux);

    return C;*/
}


void AbrirGuardarNormal::procesarAristas(Obra* O, pNodo n, std::ifstream& ifs)
{
    /*std::string codigonodohijo=leerString(ifs);
    std::cout<<"Nodo hijo: "<<codigonodohijo<<std::endl;
//    pNodo hijo=buscaNodoPorCodigo(codigonodohijo,O);
    bool haymedicion=true;
    pArista A=new arista<MedCert,Concepto>(0);
    for (int i=0; i<2; i++)
    {

        ifs.read(reinterpret_cast<char*>(&haymedicion),sizeof(bool));
        std::cout<<"Hay medicion? "<<haymedicion<<std::endl;
        float cantidad=0;
        if (!haymedicion)
        {
            std::cout<<"No hay medicion"<<std::endl;
            ifs.read(reinterpret_cast<char*>(&cantidad),sizeof(float));
            A->datoarista.LeeMedCer(i).EscribeTotal(cantidad);
        }
        else
        {
            std::cout<<"Si hay medicion"<<std::endl;
            InsertarMedicion(A,i,ifs);
        }
        std::cout<<"Cantidad de la arista: "<<cantidad<<std::endl;
    }
//    O->G.InsertarHijo(n,hijo,A->anterior,A);*/
}

void AbrirGuardarNormal::InsertarMedicion(pArista& a, int MedCer, std::ifstream& ifs)
{
    int tamLista=0;
    ifs.read(reinterpret_cast<char*>(&tamLista),sizeof(int));
    for (int i=0; i<tamLista; i++)
    {
        InsertarLineaMedicion(a,MedCer,ifs);
    }
}

void AbrirGuardarNormal::InsertarLineaMedicion(pArista& a, int MedCer, std::ifstream& ifs)
{
    /*int tamanno=2*sizeof(int)+6*sizeof(float)+2*sizeof(bool)+sizeof(LineaMedicion::tipo);
    LineaMedicion m;
    ifs.read(reinterpret_cast<char*>(&m),tamanno);
    std::string sAux=leerString(ifs);
    m.EscribeComentario(sAux);
    a->datoarista.LeeMedCer(MedCer).Insertar(m);*/
}


/*********************GUARDAR****************************************/

void AbrirGuardarNormal::Escribir(QFile &fichero, const Obra *obra)
{
//    int numeronodos=obra->G.LeeNumNodos();

//    ofs.write(reinterpret_cast<char*>(&numeronodos),sizeof(int));
//    std::cout<<"Los nodos son: "<<numeronodos<<std::endl;
    /*pNodo indice=obra->G.LeeRaiz();
    //nodos
    for (int i=0; i<numeronodos; i++)
    {
        EscribirConcepto(indice->datonodo,ofs);
        hoja=esHoja(indice);
        ofs.write(reinterpret_cast<char*>(&hoja),sizeof(bool));
        std::cout<<indice->datonodo.LeeCodigo()<<"-"<<hoja<<"-";
        indice=indice->siguiente;
    }
    std::cout<<"Ya he guardado los nodos y el valor auxiliar"<<std::endl;
    //aristas
    indice=obra->G.LeeRaiz();
    while (indice)
    {
        if (indice->adyacente)
        {
            escribirAristas(indice->adyacente,ofs);
        }
        indice=indice->siguiente;
    }*/
    std::cout<<"Fichero escrito"<<std::endl;
}

void AbrirGuardarNormal::EscribirConcepto(Concepto C, std::ofstream &ofs)
{
    /*std::cout<<"Guardando nodo: "<<C.LeeCodigo()<<std::endl;
    //el tamaño de todos los miembros fijos (todos menos los strings)
    int tamannoconcepto=sizeof(Unidad)+sizeof(Precio)+5*sizeof(int)+sizeof(float)+sizeof(Fecha)+sizeof(Concepto::Divisas);
    //guardo los miembros fijos
    ofs.write (reinterpret_cast<char*>(&C),tamannoconcepto);
    //codigo
    guardarString(C.LeeCodigo(),ofs);
    //resumen
    guardarString(C.LeeResumen(),ofs);
    //texto
    guardarString(C.LeeTexto(),ofs);
    std::cout<<"Ya he guardado el nodo"<<std::endl;*/
}

void AbrirGuardarNormal::escribirAristas(pArista a,std::ofstream &ofs)
{
    /*std::cout<<"Guardando lista de aristas"<<std::endl;
    pArista ref=a;//guardo la posicion de a;
    std::string sAux;//usaré un string para guardar los codigos de los nodos destino
    int nAristas=0;
    while (a)
    {
        nAristas++;
        a=a->siguiente;
    }
    std::cout<<"Num aristas: "<<nAristas<<std::endl;
    ofs.write(reinterpret_cast<char*>(&nAristas),sizeof(int));//guardo el nº de aristas de cada nodo
    a=ref;//vuelvo a poner a "a" en la primera arista
    while (a)
    {
        guardarString(a->destino->datonodo.LeeCodigo(),ofs);
        bool haymedicion;
        for (int i=0; i<2; i++)
        {
            if (!a->datoarista.LeeMedCer(i).hayMedicion())
            {
                std::cout<<"Entrando en modo NO medicion"<<std::endl;
                haymedicion=false;
                ofs.write(reinterpret_cast<char*>(&haymedicion),sizeof(bool));
                float cantidad=a->datoarista.LeeMedCer(i).LeeTotal();
                std::cout<<"Cantidad guardada: "<<cantidad<<std::endl;
                ofs.write(reinterpret_cast<char*>(&cantidad),sizeof(float));
            }
            else
            {
                std::cout<<"Entrando en modo SI medicion"<<std::endl;
                haymedicion=true;
                ofs.write(reinterpret_cast<char*>(&haymedicion),sizeof(bool));
                guardarMedicion(a,ofs,i);
            }
        }
        a=a->siguiente;
    }*/
}

void AbrirGuardarNormal::guardarMedicion(pArista a, std::ofstream& ofs, int i)
{
    /*std::cout<<"Guardando medicion: "<<std::endl;
    int tamLista=a->datoarista.LeeMedCer(i).LeeLista().size();
    ofs.write(reinterpret_cast<char*>(&tamLista),sizeof(int));
    std::cout<<"Numero de lineas de medicion: "<<tamLista<<std::endl;
    std::cout<<"Total en la lista: "<<a->datoarista.LeeMedCer(i).LeeTotal()<<std::endl;
    for (auto it=a->datoarista.LeeMedCer(i).LeeLista().begin(); it!=a->datoarista.LeeMedCer(i).LeeLista().end(); ++it)
    {
        std::cout<<"Guardando la linea con comentario: "<<(*it).LeeComentario()<<std::endl;
        guardarLineaMedicion(*it,ofs);
    }
    std::cout<<"Salgo de la funcion1: "<<std::endl;*/
}

void AbrirGuardarNormal::guardarLineaMedicion(LineaMedicion& lm, std::ofstream& ofs)
{
    /*std::cout<<"Guardando linea de medicion: "<<std::endl;
    int tamanno=2*sizeof(int)+6*sizeof(float)+2*sizeof(bool)+sizeof(LineaMedicion::tipo);
    std::cout<<"Tamaño es: "<<tamanno<<std::endl;
    ofs.write(reinterpret_cast<char*>(&lm),tamanno);
    std::cout<<"Contenido es: "<<lm.LeeComentario().toStdString()<<std::endl;
    guardarString(lm.LeeComentario().toStdString(),ofs);
    std::cout<<"Salgo de la funcion2: "<<std::endl;*/
}

bool AbrirGuardarNormal::esHoja(pNodo n)
{
    if (n->adyacente)
    {
        return false;
    }
    return true;
}

void AbrirGuardarNormal::guardarNodoEnLista(bool valor, std::list<pNodo>& lista, Obra* O, pNodo n)
{
    /*if (valor==true)//si es hoja
    {
        O->G.listaHojas.push_back(n);
    }
    else
    {
        lista.push_back(n);
    }*/
}

void AbrirGuardarNormal::guardarString(const std::string& s, std::ofstream& ofs)
{
    int tam=s.size()+1;
    ofs.write(reinterpret_cast<char*>(&tam),sizeof(tam));
    ofs.write(s.c_str(),tam);
}

std::string AbrirGuardarNormal::leerString(std::ifstream& ifs)
{
    int tamAux=0;
    ifs.read(reinterpret_cast<char*>(&tamAux),sizeof(tamAux));
    char* cadAux=new char[tamAux+1];
    ifs.read(cadAux,tamAux);
    std::string s=cadAux;
    delete cadAux;
    return s;
}

/*nodo<Concepto,MedCert>* AbrirGuardarNormal::buscaNodoPorCodigo (std::string codigo, const Obra* O)
{
    pNodo indice=O->G.LeeRaiz();
    while (indice->datonodo.LeeCodigo()!=codigo)
    {
        indice=indice->siguiente;
    }
    return indice;
}*/
