#ifndef PILA_H_INCLUDED
#define PILA_H_INCLUDED

#include "nodocalc.h"

template <typename TIPO>
class pila
{
	private:
    Nodo<TIPO>* ultimo;

	public:
	//constructores y destructor
	pila():ultimo(0){}
	pila (const pila <TIPO> &p);
	~pila();
	//funciones miembro
	void Push (TIPO v);
	bool Pop(TIPO& v);
	void Mostrar();
	TIPO MirarPila();
	void Borrar();
	bool Vacia();
	//sobrecarga de operadores
	pila<TIPO>& operator = (const pila<TIPO> &p);
	//istream& operator>>(istream& is, pila<TIPO>& p);
};

template <typename TIPO>
pila<TIPO>::pila (const pila <TIPO>&p)
{
	Nodo<TIPO> *aux;
	aux=p.ultimo;
	Nodo<TIPO> *Nuevo;
	ultimo=0;
	//el bucle se mantiene hasta el ultimo valor de la lista de referencia
	while (aux)
	{
		if(!ultimo) //si no hay ningun nodo
		{
			Nuevo = new Nodo<TIPO>(aux->valor,0);
			ultimo=Nuevo;
		}
		else
		{
			Nuevo->siguiente=new Nodo<TIPO>(aux->valor,0);
			Nuevo=Nuevo->siguiente;
		}
		aux=aux->siguiente;
	}
}

template <typename TIPO>
pila<TIPO>::~pila()
{
	Nodo<TIPO>* aux;
	while (ultimo)
	{
		aux=ultimo;
		ultimo=ultimo->siguiente;
		delete[] aux;
	}
}

template <typename TIPO>
void pila<TIPO>::Push (TIPO v)
{
	Nodo<TIPO>* nuevo;
	nuevo = new Nodo<TIPO> (v,ultimo);
	ultimo=nuevo;
}

template <typename TIPO>
bool pila<TIPO>::Pop(TIPO& v)
{
	if (!ultimo)
	{
		return false;
	}
	else
	{
		Nodo<TIPO>* aux;
		aux=ultimo;
		v=aux->valor;
		ultimo=ultimo->siguiente;
		delete[] aux;
	}
	return true;
}

template <typename TIPO>
void pila<TIPO>::Mostrar()
{
	/*Nodo<TIPO>* aux=ultimo;
	if (ultimo)
	{
		while (aux && aux->siguiente)
	{
		cout<<aux->valor<<",";
		aux=aux->siguiente;
	}
	cout<<aux->valor<<endl;
	}
	else
	cout<<"No hay datos en la lista"<<endl;*/
}

template <typename TIPO>
TIPO pila<TIPO>::MirarPila()
{
	return ultimo->valor;
}

template <typename TIPO>
void pila<TIPO>::Borrar()
{
	Nodo<TIPO>* aux;
	while (ultimo)
	{
		aux=ultimo;
		ultimo=ultimo->siguiente;
		delete[] aux;
	}
}

template <typename TIPO>
pila<TIPO>& pila<TIPO> :: operator = (const pila<TIPO>& p)
{
	if (this != &p)
	{
		//borro la pila actual
		Borrar();
		//creo un puntero Nuevo para crear nuevos nodos
		Nodo<TIPO> *aux;
		aux=p.ultimo;
		Nodo<TIPO> *Nuevo;
		//el bucle se mantiene hasta el ultimo valor de la lista de referencia
		while (aux)
		{
			if(!ultimo) //si no hay ningun nodo
			{
				Nuevo = new Nodo<TIPO>(aux->valor,0);
				ultimo=Nuevo;
			}
			else
			{
				Nuevo->siguiente=new Nodo<TIPO>(aux->valor,0);
				Nuevo=Nuevo->siguiente;
			}
			aux=aux->siguiente;
		}
	}
	return *this;

}

template <typename TIPO>
bool pila<TIPO>::Vacia()
{
	return 0==ultimo;
}

#endif // PILA_H_INCLUDED
