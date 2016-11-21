#ifndef ARISTA_H_INCLUDED
#define ARISTA_H_INCLUDED

template <typename, typename>
struct nodo;

template <typename DATOA, typename DATON>
struct arista
{
    DATOA datoarista;
    nodo<DATON,DATOA>* destino;
    nodo<DATON,DATOA>* origen;
    arista<DATOA,DATON>* siguiente;
    arista<DATOA,DATON>* anterior;
    //constructores
    arista(DATOA A=0, nodo<DATON,DATOA>* d=nullptr, nodo<DATON,DATOA>* o=nullptr,
           arista<DATOA,DATON>* s=nullptr, arista<DATOA,DATON>* an=nullptr):datoarista(A),destino(d),origen(o),
           siguiente(s), anterior(an) {}

    arista (const arista<DATOA,DATON>& a)
    {
        datoarista=a.datoarista;
        destino=nullptr;
        origen=nullptr;
        siguiente=nullptr;
        anterior=nullptr;
    }
    //operador de asignacion
    arista& operator = (const arista<DATOA, DATON>& a)
    {
        if (this!=&a)
            {
                datoarista=a.datoarista;
                destino=nullptr;
                origen=nullptr;
                siguiente=nullptr;
                anterior=nullptr;
            }
        return *this;
    }

    ~arista()
    {
        std::cout<<"Destructor arista"<<std::endl;
    }
};

#endif // ARISTA_H_INCLUDED
