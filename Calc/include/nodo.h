#ifndef NODO_H_INCLUDED
#define NODO_H_INCLUDED

template<typename TIPO>
class pila;

template<typename TIPO>
class Nodo

{
	private: //los miembros de la clase
	TIPO valor;
	Nodo<TIPO>* siguiente;

	public:
	//constructor
	Nodo(TIPO v=0,Nodo<TIPO>*sig=0)
	{
		valor=v;
		siguiente=sig;
	};

	friend class pila<TIPO>;

};


#endif // NODO_H_INCLUDED
