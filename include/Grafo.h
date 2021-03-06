#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include <stack>
#include <list>

#include <QDebug>

#include "arista.h"
#include "nodo.h"
#include "definiciones.h"

template <typename DATON, typename DATOA>
class Grafo
{
public:

    typedef DATON datonodo_t;
    typedef DATOA datoarista_t;
    typedef nodo<datonodo_t,datoarista_t>* pNodo;
    typedef arista<datoarista_t,datonodo_t>* pArista;
    typedef nodo<datonodo_t,datoarista_t> t_nodo;
    typedef arista<datoarista_t,datonodo_t> t_arista;
    //constructor
    Grafo():Raiz(nullptr)
    {
        std::cout<<"Constructor grafo"<<std::endl;
    }
    Grafo (pNodo nodo)
    {
        Raiz = new t_nodo(*nodo);
    }
    Grafo (datonodo_t nodo)
    {
        Raiz = new t_nodo(nodo);
    }
    //constructor copia
    Grafo (const Grafo& G);
    //sobrecarga del operador =
    Grafo& operator=(const Grafo& G);

    //funciones
    /************auxiliares de nodos y aristas***************/
    void escribeRaiz(pNodo& n);
    void anadirNodo (pNodo& n);
    void eliminarNodo(pNodo& n);
    void eliminarArista (pArista& A);
    pArista hallarArista (pNodo& nodopadre, pNodo& nodohijo);
    /*********insertar,eliminar,copiar elementos del grafo*******************/
    void Insertar (pNodo& padre, pNodo& hijo, pArista& NuevaArista, int posicion=-1);
    void borrarNodos(pArista& A);
    void Copiar(pNodo& padre, pNodo& hijo, pArista NuevaArista, pArista& precedente=nullptr);
    Grafo GrafoAPartirDeNodo(pNodo& nodo);
    pNodo CrearGrafoAPartirDeNodo(pNodo& nodo);
    pNodo CrearRamaAPartirDeNodo(pNodo& nodo);
    /******funciones para recorrer el grafo*************************/
    std::list<pNodo> recorrerNodos() const;
    std::list<pNodo> listaHojas();
    std::list<std::pair<pArista,pNodo>> recorrerHijos(const pNodo& padre) const;
    std::list<pNodo>& recorrerGrafo(pNodo& inicio);
    std::list<pNodo>& lista_recorrerGrafo(pNodo& inicio);
    std::list<std::pair<pNodo,int>>& recorrerGrafoConNiveles(const pNodo& inicio, int nivel=0);
    std::list<std::pair<pNodo,int>>& lista_recorrerGrafoConNiveles(const pNodo& inicio, int nivel=0);
    std::list<pNodo>& recorrerAncestrosOrdenado(pNodo& nodoAInvestigar);
    std::list<pNodo>& recorrerAncestros(pNodo& nodoAInvestigar);
    std::list<pNodo>& lista_recorrerAncestros(pNodo& nodoAInvestigar);
    /**********comprobaciones necesarias****************/
    bool esReferenciaCircular(pNodo& padre, pNodo& hijo);
    bool existeHermano (pNodo& padre, pNodo& hijo);
    bool existeNodo (const pNodo& n);
    bool existeNodoConMismoContenido (const pNodo& nodoAComparar);
    bool esPadre(const pNodo& padre, const pNodo& hijo);
    bool existeCodigo(TEXTO codigo) const;
    /***********otras*******************************/
    void guardaAristas (pNodo& n);
    void guardaAristasParaCopia (pNodo& n);
    void guardaAristasNivel (const pNodo& n, int nivel);
    pNodo posicionarseEnNodo(datonodo_t dato);
    template <typename T>
    void VaciarPila(std::stack<T>& pila);
    /***********consultoras*************************/
    int LeeNumNodos()const
    {
        int i=0;
        pNodo indice = Raiz;
        while (indice)
        {
            i++;
            indice=indice->siguiente;
        }
        return i;
    }
    int NivelNodoPadre(pNodo& padre) const;
    const pNodo& LeeRaiz() const
    {
        return Raiz;
    }
    bool esHoja(const pNodo& n)
    {
        if (n->adyacente)
        {
            return false;
        }
        return true;
    }
    ~Grafo();

private:

    pNodo Raiz;
    std::stack<pArista> pilaAristas;
    std::stack<pArista> pilaAristasParaCopia;
    std::stack<pNodo> pilaNodos;
    std::list<pNodo>nodos;
    std::stack<std::pair<pArista,int> >aristasConNiveles;
    std::list<std::pair<pNodo,int> >nodosConNiveles;
    //funciones privadas porque son de uso interno
    void InsertarHijo(pNodo& padre, pNodo& hijo, pArista& NuevaArista, pArista& precedente=nullptr);
    void InsertarHijo(pNodo& padre, pNodo& hijo, datoarista_t valorArista, pArista precedente=nullptr);
};

//********************//
//destructor del grafo//
//********************//
template <typename datonodo_t, typename datoarista_t>
Grafo<datonodo_t,datoarista_t>::~Grafo()
{
    //std::cout<<"Iniciamos el destructor"<<std::endl;
    qDebug()<<"Iniciamos el destructor";
    std::list<pArista> aristas;
    pNodo nodo = Raiz;
    while( nodo )
    {
        pArista arista = nodo->adyacente;
        while( arista )
        {
            aristas.push_back(arista);
            arista = arista->siguiente;
        }

        pNodo temp = nodo->siguiente;
        delete nodo;
        nodo = temp;
    }
    for( pArista arista : aristas )
        delete arista;
    //std::cout<<"Borrada la raiz"<<std::endl;
    qDebug()<<"Borrada la raiz";
}

//*****************//
//constructor copia//
//*****************//
template <typename datonodo_t, typename datoarista_t>
Grafo<datonodo_t, datoarista_t>::Grafo (const Grafo<datonodo_t, datoarista_t>& G)
{
    std::cout<<"CONSTRUCTOR COPIA"<<std::endl;
    Raiz = CrearGrafoAPartirDeNodo(G.Raiz);
    std::cout<<"Copia terminada"<<std::endl;
}

//*************************//
//sobrecarga del operador =//
//*************************//
template <typename datonodo_t, typename datoarista_t>
Grafo<datonodo_t, datoarista_t>& Grafo<datonodo_t, datoarista_t>::operator=(const Grafo<datonodo_t, datoarista_t>& G)
{
    /*if (this!=&G)
    {
        std::cout<<"Sobrecarga operador = en grafo"<<std::endl;
        delete Raiz;
        //vacio la pila
        VaciarPila(pilaAristas);
        pNodo indice1=G.Raiz;
        Raiz=new t_nodo (*indice1);
        pNodo indice=Raiz;
        pArista indiceA=indice1->adyacente;
        while (indice1->siguiente)
        {
            indiceA=indice1->adyacente;

            while (indiceA)
            {
                pNodo hijo=posicionarseEnNodo(indiceA->destino->datonodo);//creo un nodo con el contenido del nodo origen hijo
                if (hijo==nullptr)
                {
                    hijo=new t_nodo(*indiceA->destino);
                }
                pArista A= new t_arista(*indiceA);
                InsertarHijo(indice,hijo,A,A->anterior);
                indiceA=indiceA->siguiente;
            }

            indice1=indice1->siguiente;
            indice=indice->siguiente;
        }
    }*/
    return *this;
}

//***********************//
//poner un nodo como raiz//
//***********************//
template <typename datonodo_t, typename datoarista_t>
void Grafo<datonodo_t,datoarista_t>::escribeRaiz(pNodo& n)
{

    std::cout<<"Grafo::escribeRaiz"<<std::endl;
    if (Raiz)
    {
        if (Raiz==n)
        {
            //std::cout<<"Primer NODO"<<std::endl;
            //        Raiz=n;
        }
        else
        {
            pNodo indice = Raiz;
            while (indice->siguiente)
            {
                if (indice->siguiente == n)
                {
                    indice->siguiente=n->siguiente;
                    n->siguiente=Raiz->siguiente;
                    Raiz=n;
                }
                else
                {
                    indice=indice->siguiente;
                }
            }
        }
    }
}

//**************//
//añadir un nodo//
//**************//
template <typename datonodo_t, typename datoarista_t>
void Grafo<datonodo_t,datoarista_t>::anadirNodo(pNodo& n)
{
    if (Raiz==nullptr)
    {
        Raiz=n;
    }
    else
    {
        pNodo indice=Raiz;
        //me posiciono al final de la lista
        while (indice && indice->siguiente!=0)
        {
            indice=indice->siguiente;
        }
        indice->siguiente=n;
    }
}

//****************//
//eliminar un nodo//
//****************//
template <typename datonodo_t, typename datoarista_t>
void Grafo<datonodo_t,datoarista_t>::eliminarNodo(pNodo& n)
{
    pNodo anterior=Raiz;
    //avanzo anterior hasta el nodo anterior al que quiero borrar
    while (anterior->siguiente!=n)
    {
        anterior=anterior->siguiente;
    }
    if (anterior==Raiz)//primer elemento
    {
        Raiz->siguiente=n->siguiente;
    }
    else
    {
        anterior->siguiente=n->siguiente;
    }
    //std::cout<<"Borrando el nodo: "<<n->datonodo.LeeCodigo().toStdString()<<std::endl;
    qDebug()<<"Borrando el nodo: "<<n->datonodo.LeeCodigo();
    delete n;
}

//*******************//
//eliminar una arista//
//*******************//
template <typename datonodo_t, typename datoarista_t>
void Grafo<datonodo_t,datoarista_t>::eliminarArista(pArista& A)
{
    pArista aux = A;
    pNodo indice=Raiz;
    //veo si la arista a borrar es la adyacente de algún nodo (primera arista)
    while (indice && indice->adyacente!=A)
    {
        indice=indice->siguiente;
    }
    if (indice)//si finalmente la arista a borrar es adyacente de indice
    {
        //std::cout<<"Es adyacente!!!"<<std::endl;
        //si es arista única
        if (!A->anterior && !A->siguiente)
        {
            //std::cout<<"Es arista unica!!!"<<std::endl;
        }
        indice->adyacente = aux->siguiente;
    }
    if (aux->anterior)
    {
        aux->anterior->siguiente = aux->siguiente;
    }
    if (aux->siguiente)
    {
        aux->siguiente->anterior=aux->anterior;
    }
    delete aux;
}

//***********************************************//
//borrar todos los nodos que penden de una arista//
//***********************************************//

template <typename datonodo_t, typename datoarista_t>
void Grafo<datonodo_t,datoarista_t>::borrarNodos(pArista& A)
{
    pNodo hijo=A->destino;
    //std::cout<<"BORRARR: "<<A->destino->datonodo.LeeCodigo().toStdString()<<std::endl;
    //quitar un padre al nodo hijo
    //std::cout<<"El nodo: "<<A->destino->datonodo.LeeCodigo().toStdString()<<" tiene: "<<hijo->nPadres<<" padres."<<std::endl;
    if (hijo->nPadres>0) hijo->nPadres--;
    //si todavía es hijo de algún padre....
    if (hijo->nPadres)
    {
        //...me limito a borrar la arista que une al padre con el hijo
        //std::cout<<"Eliminar arista A"<<std::endl;
        eliminarArista(A);
    }
    else //si se queda huerfanito
    {
        //si el hijo es hoja no tiene aristas que salgan de él, luego adyacente apunta a 0
        if (!hijo->adyacente)
        {
            //me posiciono en la arista a borrar
            //std::cout<<"Es hoja---"<<std::endl;
            qDebug()<<"Es hoja---";
            eliminarArista(A);
            eliminarNodo(hijo);//lo saco de la lista general de nodos
        }
        else
        {
            //std::cout<<"El caso mas chungo"<<std::endl;
            guardaAristas(hijo);
            eliminarArista(A);
            eliminarNodo(hijo);
            while (!pilaAristas.empty())
            {
                A=pilaAristas.top();
                pilaAristas.pop();
                borrarNodos(A);
            }
        }
    }
}

/***********************/
/****Insertar nodo *****/
/***********************/

template <typename datonodo_t, typename datoarista_t>
void Grafo<datonodo_t,datoarista_t>::Insertar(pNodo& padre, pNodo& hijo, pArista& NuevaArista, int posicion)
{
    if (Raiz==nullptr)
    {
        qDebug()<<"Añadir raiz";
        Raiz = padre;
    }
    if (!existeNodo(padre))
    {
        anadirNodo(padre);
        qDebug()<<"Añadir PADRE";
    }
    if (!existeNodo(hijo))
    {
        anadirNodo(hijo);
        qDebug()<<"Añadir HIJO";
    }
    //inserto la arista
    if (!esReferenciaCircular(padre,hijo) && !existeHermano(padre,hijo))//comprobacion necesaria
    {
        hijo->nPadres++;//añado un padre
        NuevaArista->origen=padre;
        NuevaArista->destino=hijo;
        //caso 1. Primer nodo que cuelga del nodo padre
        if (!padre->adyacente)
        {
            padre->adyacente = NuevaArista;
        }
        else
        {
            //caso 2. Poner el nuevo nodo en primer lugar habiendo otros nodos existentes
            if (posicion==0)
            {
                NuevaArista->siguiente=padre->adyacente;
                padre->adyacente->anterior=NuevaArista;
                padre->adyacente=NuevaArista;
            }
            else//casos 3 y 4. El primer paso comun es situar la arista precedente a la que quiero insertar
            {
                pArista precedente = padre->adyacente;
                //caso 3. Si no se especifica posicion esta vale -1 y se inserta al final
                if (posicion<0)
                {
                    while(precedente && precedente->siguiente)
                    {
                        //std::cout<<"INSERTO AL FINALe"<<std::endl;
                        qDebug()<<"INSERTO AL FINAL";
                        precedente=precedente->siguiente;
                    }
                }
                //caso 4. Me situo en la posicion dada
                else
                {
                    //std::cout<<"INSERTO POR POSICION"<<std::endl;
                    qDebug()<<"INSERTO POR POSICION";
                    for (int i=0; i<posicion-1; i++)
                    {
                        precedente = precedente->siguiente;
                    }
                }
                //por ultimo ligo la nueva arista
                if (precedente && precedente->siguiente)
                {
                    precedente->siguiente->anterior=NuevaArista;
                }
                NuevaArista->siguiente=precedente->siguiente;
                NuevaArista->anterior=precedente;
                precedente->siguiente=NuevaArista;
            }
        }
    }
    qDebug()<<"FIN del METODO de INSERTAR";
}

//**************************//
//insertar version con dato //
//**************************//

template <typename datonodo_t, typename datoarista_t>
void Grafo<datonodo_t,datoarista_t>::InsertarHijo(pNodo& padre, pNodo& hijo, datoarista_t valorArista, pArista precedente)
{
    pArista nueva = new t_arista(valorArista);
    InsertarHijo(padre, hijo, nueva, precedente);
}

//*******************************************//
//hallar la arista precedente a un nodo dado //
//*******************************************//

template <typename datonodo_t, typename datoarista_t>
arista<datoarista_t,datonodo_t>* Grafo<datonodo_t,datoarista_t>::hallarArista (pNodo& nodopadre, pNodo& nodohijo)
{
    //std::cout<<"Hallando precedente de "<<nodopadre->datonodo<<std::endl;
    pArista precedente = nullptr;
    if (nodopadre->adyacente)
    {
        precedente= nodopadre->adyacente;
        while(precedente->siguiente)
        {
            if (precedente->destino==nodohijo)
            {
                //std::cout<<"Retorno precedente"<<std::endl;
                return precedente;
            }
            else
            {
                precedente=precedente->siguiente;
            }
        }
    }
    std::cout<<"No retorno nada"<<std::endl;
    return precedente;
}

//**********************************************************************//
//copia un grafo a partir de un nodo dado en una parte del grafo actual //
//**********************************************************************//
template <typename datonodo_t, typename datoarista_t>
void Grafo<datonodo_t,datoarista_t>::Copiar(pNodo& padre, pNodo& hijo, pArista NuevaArista, pArista& precedente)
{
    //std::cout<<"FUNCION COPIAR "<<padre->datonodo.LeeCodigo().toStdString()<<"-->"<<hijo->datonodo.LeeCodigo().toStdString()<<std::endl;
    pArista copianuevaarista = nullptr;
    if (NuevaArista)
    {
        //std::cout<<"Creo la nueva arista con el valor: "<<NuevaArista->datoarista.LeeMedicion().LeeTotal()<<std::endl;
        copianuevaarista = new t_arista(*NuevaArista);
    }
    else
    {
        copianuevaarista = new t_arista();
    }
    pNodo copiahijo = posicionarseEnNodo(hijo->datonodo);
    if (!copiahijo)
    {
        //std::cout<<"creo copia del hijo: "<<hijo->datonodo.LeeCodigo().toStdString()<<std::endl;
        qDebug()<<"creo copia del hijo: "<<hijo->datonodo.LeeCodigo();
        copiahijo = new t_nodo(*hijo);
        copiahijo->nPadres--;
    }
    guardaAristasParaCopia(hijo);
    //std::cout<<"copia hijo: "<<copiahijo->datonodo.LeeCodigo().toStdString()<<" - "<<copiahijo<<std::endl;
    qDebug()<<"copia hijo: "<<copiahijo->datonodo.LeeCodigo()<<" - "<<copiahijo;
    pArista A = padre->adyacente;
    int pos=0;
    while (A && A!=precedente)
    {
        pos++;
        A=A->siguiente;
    }
    qDebug()<<"Posicion pos: "<<pos;
    Insertar(padre,copiahijo,copianuevaarista,pos);
    while (!pilaAristasParaCopia.empty())
    {
        pArista actual = pilaAristasParaCopia.top();
        pNodo nieto = actual->destino;
        //std::cout<<"Nieto es: "<<nieto->datonodo.LeeCodigo().toStdString()<<std::endl;
        qDebug()<<"Nieto es: "<<nieto->datonodo.LeeCodigo();
        pilaAristasParaCopia.pop();
        std::cout<<"Copia hijo adyacente: "<<copiahijo->adyacente<<std::endl;
        pArista prec = hallarArista(copiahijo,nieto);
        //if(prec)
        //std::cout<<"Arista precedente con valor: "<<prec->datoarista.LeeMedicion().LeeTotal()<<std::endl;
        pNodo repadre = posicionarseEnNodo(actual->origen->datonodo);
        //std::cout<<"Busco el repadre de actual: "<<actual->origen->datonodo.LeeCodigo().toStdString()<<std::endl;
        //pNodo repadre = actual->origen;
        if (repadre)
        {
            //std::cout<<"Hasta aqui 1 con repadre= "<<repadre->datonodo.LeeCodigo().toStdString()<<std::endl;
            Copiar(repadre, nieto, actual,prec);
        }
        //std::cout<<"Hasta aqui 2"<<std::endl;
        qDebug()<<"Hasta aqui 2";
    }
    qDebug()<<"FIN DE COPIARR";
}

//******************************************//
//Crea un grafo a partir de un nodo dado    //
//******************************************//

template <typename datonodo_t, typename datoarista_t>
Grafo<datonodo_t,datoarista_t> Grafo<datonodo_t,datoarista_t>::GrafoAPartirDeNodo(pNodo& nodo)
{
    std::cout<<"FUNCION CREAR GRAFO A PARTIR DE NODO"<<std::endl;
    Grafo G;
    G.Raiz = CrearRamaAPartirDeNodo(nodo);
    std::cout<<"FIN FUNCION CREAR GRAFO A PARTIR DE NODO"<<std::endl;
    return G;
}

//********************************************//
//Crea un grafo a partir de un nodo dado      //
//********************************************//

template <typename datonodo_t, typename datoarista_t>
nodo<datonodo_t,datoarista_t>* Grafo<datonodo_t,datoarista_t>::CrearGrafoAPartirDeNodo(pNodo& nodo)
{
    pNodo raizcopia = nullptr;
    if (nodo)
    {
        raizcopia =  new t_nodo(*nodo);
    }
    pNodo temp=Raiz;//guardo la raiz
    Raiz=raizcopia;//tengo que definir ya la raiz aqui aunque no tenga mucho sentido porque la necesito definida para otras funciones
    guardaAristasParaCopia(nodo);
    while (!pilaAristasParaCopia.empty())
    {
        pArista AristaHijo = pilaAristasParaCopia.top();
        pilaAristasParaCopia.pop();
        Copiar(raizcopia,AristaHijo->destino,AristaHijo,nodo->adyacente->anterior);
    }
    Raiz=temp;//restauro la raiz
    return raizcopia;
}

//********************************************//
//Crea una rama a partir de un nodo dado      //
//********************************************//

template <typename datonodo_t, typename datoarista_t>
nodo<datonodo_t,datoarista_t>* Grafo<datonodo_t,datoarista_t>::CrearRamaAPartirDeNodo(pNodo& nodo)
{
    std::cout<<"CREAR RAMA A PARTIR DE NODO: "<<std::endl;
    pNodo base = new t_nodo(*nodo);
    std::cout<<"Nodo base: "<<base->datonodo.LeeCodigo().toStdString()<<std::endl;
    guardaAristasParaCopia(nodo);
    while (!pilaAristasParaCopia.empty())
    {
        pArista hijo = pilaAristasParaCopia.top();
        pilaAristasParaCopia.pop();
        Copiar(base,hijo->destino,hijo,nodo->adyacente->anterior);
    }
    return base;
}


//******************************************//
//recorre toda la lista de nodos del grafo  //
//******************************************//

template <typename datonodo_t, typename datoarista_t>
std::list<nodo<datonodo_t,datoarista_t>*>Grafo<datonodo_t,datoarista_t>::recorrerNodos() const
{
    //nodos.clear();
    std::list<pNodo> nodos;
    if (Raiz)
    {
        pNodo indice = Raiz;
        nodos.push_back(indice);
        while (indice->siguiente)
        {
            indice= indice->siguiente;
            nodos.push_back(indice);
        }
    }
    return nodos;
}


//**********************************************************************//
//recorre solamente los nodos hijos directos que penden de un nodo padre//
//**********************************************************************//

/*template <typename datonodo_t, typename datoarista_t>
std::list<nodo<datonodo_t,datoarista_t>*>Grafo<datonodo_t,datoarista_t>::recorrerHijos(const pNodo& padre)
{
    std::list<pNodo>hijos;
    if (padre->adyacente!=nullptr)
    {
        pArista A=padre->adyacente;
        while (A->siguiente!=nullptr)
        {
            hijos.push_back(A->destino);
            A=A->siguiente;
        }
        hijos.push_back(A->destino);
    }
    return hijos;
}*/

//**********************************************************************//
//recorre solamente los nodos hijos directos que penden de un nodo padre//
//**********************************************************************//
template <typename datonodo_t, typename datoarista_t>
std::list<std::pair<arista<datoarista_t, datonodo_t>*,nodo<datonodo_t,datoarista_t>*>> Grafo<datonodo_t,datoarista_t>::recorrerHijos(const pNodo& padre) const
{
    std::list<std::pair<pArista,pNodo>>hijos;
    std::pair<pArista,pNodo> aux;
    if (padre->adyacente!=nullptr)
    {
        pArista A=padre->adyacente;
        while (A->siguiente!=nullptr)
        {
            aux.second=A->destino;
            aux.first=A;
            hijos.push_back(aux);
            A=A->siguiente;
        }
        aux.second=A->destino;
        aux.first=A;
        hijos.push_back(aux);
    }
    return hijos;
}

//*************************************//
//recorrer el arbol a partir de un nodo//
//*************************************//

template <typename datonodo_t, typename datoarista_t>
std::list<nodo<datonodo_t,datoarista_t>*>& Grafo<datonodo_t,datoarista_t>::recorrerGrafo(pNodo& inicio)
{
    VaciarPila(pilaAristas);
    nodos.clear();
    return lista_recorrerGrafo(inicio);
}

template <typename datonodo_t, typename datoarista_t>
std::list<nodo<datonodo_t,datoarista_t>*>& Grafo<datonodo_t,datoarista_t>::lista_recorrerGrafo(pNodo& inicio)
{
    pArista A;
    if (inicio)
    {
        guardaAristas(inicio);
        while (!pilaAristas.empty())
        {
            A=pilaAristas.top();
            pilaAristas.pop();
            nodos.push_back(A->destino);
            lista_recorrerGrafo(A->destino);
        }
    }
    return nodos;
}

//****************************************************************************//
//recorrer el arbol a partir de un nodo con informacion del nivel de cada nodo//
//****************************************************************************//

template <typename datonodo_t, typename datoarista_t>
std::list<std::pair<nodo<datonodo_t,datoarista_t>*,int>>&Grafo<datonodo_t,datoarista_t>::recorrerGrafoConNiveles(const pNodo& inicio, int nivel)
{
    VaciarPila(aristasConNiveles);
    nodosConNiveles.clear();
    return lista_recorrerGrafoConNiveles(inicio, nivel);
}

template <typename datonodo_t, typename datoarista_t>
std::list<std::pair<nodo<datonodo_t,datoarista_t>*,int>>&Grafo<datonodo_t,datoarista_t>::lista_recorrerGrafoConNiveles(const pNodo& inicio, int nivel)
{
    pArista A;
    if (inicio)
    {
        guardaAristasNivel(inicio,nivel);
        while (!aristasConNiveles.empty())
        {
            A=aristasConNiveles.top().first;
            nivel=aristasConNiveles.top().second+1;
            aristasConNiveles.pop();
            std::pair<pNodo,int>prov;
            prov.first=A->destino;
            prov.second=nivel;
            nodosConNiveles.push_back(prov);
            lista_recorrerGrafoConNiveles(A->destino,nivel);
        }
    }
    return nodosConNiveles;
}

//******************************************************************//
//devuelve todos los ancestros de un nodo dado de forma ordenada    //
//******************************************************************//

template <typename datonodo_t, typename datoarista_t>
std::list<nodo<datonodo_t,datoarista_t>*>&Grafo<datonodo_t,datoarista_t>::recorrerAncestrosOrdenado(pNodo& nodoAInvestigar)
{
    std::list<pNodo> lista = recorrerAncestros(nodoAInvestigar);
    /*elimino nodos duplicados*/
    nodos.clear();
    bool existe=false;
    for (auto it1 = lista.crbegin(); it1!=lista.crend(); ++it1)
    {
        existe = false;
        for(auto it2 = nodos.begin(); it2!=nodos.end(); it2++)
        {
            if ((*it2)==(*it1))
            {
                existe=true;
            }
        }
        if (!existe)
        {
            nodos.push_front(*it1);
        }
    }
    /*ordeno los nodos en funcion de si alguno es padre de otros*/
    for (int i=0;i<2;i++)
    {nodos.sort([](const pNodo& hijo, const pNodo& padre)
        {
            if (padre->adyacente)
            {
                pArista A = padre->adyacente;
                while (A)
                {
                    if (A->destino==hijo)
                    {
                        std::cout<<padre<<" mayor que "<<"-"<<A->destino<<std::endl;
                        return true;
                    }
                    else
                    {
                        A=A->siguiente;
                    }
                }
            }
            return false;
        }
        );
    }
    for (auto elem:nodos)
    {
        //std::cout<<"Nodo: "<<elem<<std::endl;
        qDebug()<<"Nodo: "<<elem->datonodo.LeeCodigo();
    }
    return nodos;
}

//***************************************************//
//devuelve todos los ancestros de un nodo dado       //
//***************************************************//

template <typename datonodo_t, typename datoarista_t>
std::list<nodo<datonodo_t,datoarista_t>*>&Grafo<datonodo_t,datoarista_t>::recorrerAncestros(pNodo& nodoAInvestigar)
{
    nodos.clear();
    return lista_recorrerAncestros(nodoAInvestigar);
}

template <typename datonodo_t, typename datoarista_t>
std::list<nodo<datonodo_t,datoarista_t>*>&Grafo<datonodo_t,datoarista_t>::lista_recorrerAncestros(pNodo& nodoAInvestigar)
{
    pNodo indice=Raiz;
    while (indice)
    {
        if (indice->adyacente)
        {
            pArista A=indice->adyacente;
            while (A)
            {
                if (A->destino==nodoAInvestigar)
                {
                    pilaNodos.push(indice);
                    nodos.push_back(indice);
                    break;
                }
                else
                {
                    A=A->siguiente;
                }
            }
        }
        indice=indice->siguiente;
    }
    //while (!pilaNodos.empty() && pilaNodos.top()!=Raiz)
    while (!pilaNodos.empty())
    {

        pNodo N = pilaNodos.top();
        pilaNodos.pop();
        lista_recorrerAncestros(N);
    }
    return nodos;
}

//*********************************************************************//
//busca si un nodo que quiero copiar como hijo de otro es padre de éste//
//necesario para evitar referencias circulares                         //
//*********************************************************************//

template <typename datonodo_t, typename datoarista_t>
bool Grafo<datonodo_t,datoarista_t>::esReferenciaCircular(pNodo& padre, pNodo& hijo)
{
    if (padre==hijo)
    {
        std::cout<<"Referencia $$ circular"<<std::endl;
        return true;
    }
    else
    {
        pArista A;
        bool encontrado=false;
        guardaAristas(hijo);
        while (!pilaAristas.empty())
        {
            A=pilaAristas.top();
            pilaAristas.pop();
            if (A->destino==padre)
            {
                //vacio la pila
                while (!pilaAristas.empty())
                    pilaAristas.pop();
                std::cout<<"Referencia circular"<<std::endl;
                return true;
            }
            return encontrado || esReferenciaCircular(padre,A->destino);
        }
    }
    return false;
}

//*********************************************************************************//
//devuelve una lista con todos los nodos del grafo que no tienen aristas adyacentes//
//*********************************************************************************//
template <typename datonodo_t, typename datoarista_t>
std::list<nodo<datonodo_t,datoarista_t>*>Grafo<datonodo_t,datoarista_t>::listaHojas()
{
    std::list<pNodo>listadehojas;
    if (Raiz)
    {
        pNodo indice = Raiz;
        listadehojas.push_back(indice);
        while (indice->siguiente)
        {
            indice= indice->siguiente;
            if (!indice->adyacente)
            {
                listadehojas.push_back(indice);
            }
        }
    }
    return listadehojas;
}

//*************************************************************//
//comprueba la existencia de un nodo igual al que quiero copiar//
//necesario para evitar tener dos nodos iguales colgando del   //
//mismo padre                                                  //
//*************************************************************//

template <typename datonodo_t, typename datoarista_t>
bool Grafo<datonodo_t,datoarista_t>::existeHermano (pNodo& padre, pNodo& hijo)
{
    pArista A=padre->adyacente;
    while (A!=nullptr)
    {
        //std::cout<<"posicionada la arista"<<A<<std::endl;
        if (A->destino==hijo)
        {
            return true;
        }
        A=A->siguiente;
    }

    //std::cout<<"No hay gemelos"<<std::endl;
    return false;
}

//*********************************************//
//comprueba la presencia de un nodo en la lista//
//para evitar su inclusión por duplicado       //
//*********************************************//

template <typename datonodo_t, typename datoarista_t>
bool Grafo<datonodo_t,datoarista_t>::existeNodo (const pNodo& n)
{
    pNodo indice=Raiz;
    if (n==indice)
        return true;
    else
    {
        while (indice->siguiente)
        {
            indice=indice->siguiente;
            if (n==indice)
            {
                return true;
            }
        }
    }
    return false;
}

//*****************************************************************************//
//comprueba si existe algun nodo con el mismo contenido que el nodo a comparar //
//*****************************************************************************//

template <typename datonodo_t, typename datoarista_t>
bool Grafo<datonodo_t,datoarista_t>::existeNodoConMismoContenido (const pNodo& nodoAComparar)
{
    pNodo indice=Raiz;
    if (nodoAComparar->datonodo==indice->datonodo)
        return true;
    else
    {
        while (indice->siguiente)
        {
            indice=indice->siguiente;
            if (nodoAComparar->datonodo==indice->datonodo)
            {
                return true;
            }
        }
    }
    return false;

}

//**************************************************//
//comprueba si un nodo es padre directo de otro nodo//
//**************************************************//
template <typename datonodo_t, typename datoarista_t>
bool Grafo<datonodo_t,datoarista_t>::esPadre(const pNodo& padre, const pNodo& hijo)
{
    if (padre->adyacente)
    {
        pArista A = padre->adyacente;
        while (A)
        {
            if (A->destino==hijo)
            {
                return true;
            }
            else
            {
                A=A->siguiente;
            }
        }
    }
    return false;
}

//***************************************************//
//guarda las aristas que penden de un nodo en la pila//
//***************************************************//

template <typename datonodo_t, typename datoarista_t>
void Grafo<datonodo_t,datoarista_t>::guardaAristas (pNodo& n)
{
    pArista A;

    if (n && n->adyacente) //si hay aristas
    {
        A=n->adyacente;
        //me posiciono en la última arista
        while (A->siguiente!=nullptr)
        {
            A=A->siguiente;
        }
        //empiezo el recorrido hacia atrás
        while (A->anterior!=nullptr)
        {
            pilaAristas.push (A); //meto la arista en la pila
            A=A->anterior;
        }
        pilaAristas.push (A); //meto la primera arista en la pila*/
    }
}


template <typename datonodo_t, typename datoarista_t>
void Grafo<datonodo_t,datoarista_t>::guardaAristasParaCopia(pNodo& n)
{
    //VaciarPila(pilaAristasParaCopia);
    pArista A;
    //std::cout<<"Guardando las aristas del nodo: "<<n->datonodo.LeeCodigo().toStdString()<<std::endl;

    if (n && n->adyacente) //si hay aristas
    {
        A=n->adyacente;
        //me posiciono en la última arista
        while (A->siguiente!=nullptr)
        {
            A=A->siguiente;
        }
        while (A->anterior!=nullptr)
        {
            if (A->destino)
                //std::cout<<"MEto la arista de :"<<A->destino->datonodo.LeeCodigo().toStdString()<<std::endl;
                pilaAristasParaCopia.push (A); //meto la arista en la pila
            A=A->anterior;
        }
        if (A->destino)
            //std::cout<<"MEto la arista de :"<<A->destino->datonodo.LeeCodigo().toStdString()<<std::endl;
            pilaAristasParaCopia.push (A); //meto la arista en la pila
    }
}

//**************************************************************//
//guarda las aristas y el nivel que penden de un nodo en la pila//
//**************************************************************//

template <typename datonodo_t, typename datoarista_t>
void Grafo<datonodo_t,datoarista_t>::guardaAristasNivel (const pNodo& n, int nivel)
{
    pArista A;
    std::pair<pArista,int> pareja;
    pareja.second=nivel;

    if (n && n->adyacente) //si hay aristas
    {
        A=n->adyacente;
        //me posiciono en la última arista
        while (A->siguiente!=nullptr)
        {
            A=A->siguiente;
        }
        //empiezo el recorrido hacia atrás
        while (A->anterior!=nullptr)
        {
            pareja.first=A;
            aristasConNiveles.push (pareja); //meto la arista en la pila
            A=A->anterior;
        }
        pareja.first=A;
        aristasConNiveles.push (pareja); //meto la arista en la pila
    }
}

//*******************************************************************************************************//
//si existe un nodo con el valor a comparar, devolvemos ese nodo. En caso concreto devolvemos valor nulo //
//*******************************************************************************************************//

template <typename DATON, typename DATOA>
nodo<DATON,DATOA>* Grafo<DATON,DATOA>::posicionarseEnNodo(datonodo_t dato)
{
    //std::cout<<"Buscando el nodo con codigo: "<<dato.LeeCodigo().toStdString()<<std::endl;
    //std::cout<<"Buscando el nodo con codigo: "<<dato<<std::endl;
    qDebug()<<"Buscando el nodo con codigo: "<<dato.LeeCodigo();
    pNodo indice=Raiz;
    while (indice)// && indice->siguiente)
    {
        //std::cout<<"Nodo a comparar: "<<indice->datonodo<<std::endl;
        if (indice->datonodo == dato)
        {
            return indice;
        }
        indice=indice->siguiente;
    }
    //std::cout<<"Me voy de la funcion sin nada"<<std::endl;
    return nullptr;
}

//*******************************//
//obtiene el nivel del nodo padre//
//** ****************************//

template <typename DATON, typename DATOA>
int Grafo<DATON,DATOA>::NivelNodoPadre(pNodo& padre) const
{
    pNodo indice=Raiz;
    pArista A;
    while (indice)
    {
        if (indice->adyacente)
        {
            A=indice->adyacente;
            while (A)
            {
                if (A->destino==padre)
                {
                    return A->nivel;
                }
                A=A->siguiente;
            }
        }
        indice=indice->siguiente;
    }
    return -1; //en caso de error o de que no haya encontrado el nodo padre.....
}

//*********************//
// vaciar la pila dada //
//*********************//

template <typename DATON, typename DATOA>
template <typename T>
void Grafo<DATON,DATOA>::VaciarPila(std::stack<T>& pila)
{
    while (!pila.empty())
    {
        pila.pop();
    }
}

#endif // GRAFO_H
