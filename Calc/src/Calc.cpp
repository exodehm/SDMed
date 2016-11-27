#include "../include/Calc.h"


Calc::Calc()
{
    cadena=0;
    tamanno=0;
    InicializarArray();
}

Calc::Calc(const std::string &sExpresion)
{
    cadena = new char[sExpresion.length()+1];
    char *cadena1 = new char[sExpresion.length()+1];
    strcpy(cadena1, sExpresion.c_str());
    quitaEspacios(cadena1);
    tamanno=strlen(cadena1)+1;
    cadena= new char[tamanno];
    strcpy(cadena, cadena1);
    delete cadena1;
    InicializarArray();
}

Calc::Calc(const char* cExpresion)
{
	tamanno=strlen(cExpresion)+1;
    char *cadena1 = new char[tamanno];
    strcpy(cadena1, cExpresion);
    quitaEspacios(cadena1);
    tamanno=strlen(cadena1)+1;
    cadena= new char[tamanno];
    strcpy(cadena, cadena1);
    delete cadena1;
    InicializarArray();
}

Calc::Calc (const Calc& Ref)
{
    cadena= new char[strlen(Ref.cadena)+1];
    strcpy (cadena,Ref.cadena);
    tamanno=Ref.tamanno;
}

Calc::~Calc()
{
    if (cadena)
        {
            delete[] cadena;
        }
}

bool Calc::esOperando (char c)
{
    return ((c>='0' && c<='9') || c=='.' || c=='e');
}

bool Calc::esParentesis (char c)
{
    return (c=='(' || c==')');
}

bool Calc::esOperador (char c)
{
    return (c=='+' || c=='-' || c=='*' || c=='/' || c=='^' || c=='%' || c=='s' || c=='m');
}

const Calc::op_t* Calc::defineOperador (char c)
{
    const op_t* punt= cadena_ref;
    switch (c)
        {
        case '(':
            return &punt[PAREN_IZQ];
        case ')':
            return &punt[PAREN_DER];
        case '^':
            return &punt[POT];
        case '+':
            return &punt[SUMA];
        case '-':
            return &punt[RESTA];
        case '*':
            return &punt[MULT];
        case '/':
            return &punt[DIV];
        case '%':
            return &punt[PORC];
        case 's':
            return &punt[RAIZC];
        case 'm':
            return &punt[MOD];
        }
    return punt=0;
}

bool Calc::Precedencia (const op_t& op_Pila,const op_t& op_Expresion)
{
    return (op_Pila.precedencia==op_Expresion.precedencia? op_Pila.bIzqDer:op_Pila.precedencia<op_Expresion.precedencia);
}

Calc::elemento_t* Calc::pasaPostfija (elemento_t* ExpInfija, int &tamanno)
{
    int parentesis=0;
    for (int i=0; i<tamanno; i++)
        {
            if (esParentesis(ExpInfija[i].OP.operador.simbolo))
                {
                    parentesis++;
                }
        }
    //cout<<parentesis<<endl;
    //creo un array de char para ir almacenando la Expresión Postfija EP
    elemento_t* EP=new elemento_t[(tamanno-parentesis)];
    //creo una pila para ir almacenando operadores
    pila<elemento_t> PilaOperadores;
    int j=0;
    elemento_t c;
    for (int i=0; i<tamanno; i++)
        {
            if (ExpInfija[i].semantica==OPERANDO)
                {
                    EP[j++]=ExpInfija[i];
                }
            else if (ExpInfija[i].OP.operador.simbolo=='(')
                {
                    PilaOperadores.Push (ExpInfija[i]);
                }
            else if (ExpInfija[i].OP.operador.simbolo==')')
                {
                    while (PilaOperadores.MirarPila().OP.operador.simbolo!='(')
                        {
                            PilaOperadores.Pop(c);
                            EP[j++]=c;
                        }
                    PilaOperadores.Pop(c); //saco el parentesis '('
                }
            else if (esOperador(ExpInfija[i].OP.operador.simbolo))
                {
                    while (!PilaOperadores.Vacia() && PilaOperadores.MirarPila().OP.operador.simbolo!='(' && (Precedencia(PilaOperadores.MirarPila().OP.operador,ExpInfija[i].OP.operador)))
                        {
                            PilaOperadores.Pop(c);
                            EP[j++]=c;
                        }
                    PilaOperadores.Push(ExpInfija[i]);
                }
        }
    while (!PilaOperadores.Vacia())
        {
            PilaOperadores.Pop(c);
            EP[j++]=c;
        }
    tamanno=j;
    return EP;
}

double Calc::Operar (float a, float b, char c)
{
    switch (c)
        {
        case '+':
            return a+b;
        case '-':
            return a-b;
        case '*':
            return a*b;
        case '/':
            return a/b;
        case '^':
        {
            return pow (a,b);
        }
        case 'm':
            return fmod(a,b);
        }
    return '\a';
}

void Calc::OperarUnitario (OP_TIPO tipo, pila<double> &PilaResultados, double Valor)
{
    switch (tipo)
        {
        case NEG:
        {
            PilaResultados.Pop(Valor);
            Valor=-Valor;
            PilaResultados.Push(Valor);
        }
        break;

        case POS:
        {
            PilaResultados.Pop(Valor);
        }
        break;

        case PORC:
        {
            PilaResultados.Pop (Valor);
            Valor/=100;
            PilaResultados.Push(Valor);
        }
        break;

        case RAIZC:
        {
            PilaResultados.Pop (Valor);
            Valor=sqrt(Valor);
            PilaResultados.Push (Valor);
        }
        default:
            break;
        }
}

double Calc::EvaluaEpostfija (elemento_t* EPostfija, int tamanno)
{
    pila<double> PilaResultados;
    double Valor=0, Operando1=0,Operando2=0,Resultado=0;
    for (int i=0; i<tamanno; i++)
        {
            if (EPostfija[i].semantica==OPERANDO)
                {
                    PilaResultados.Push(EPostfija[i].OP.operando);
                }
            else if (!EPostfija[i].OP.operador.bBinario)
                OperarUnitario (EPostfija[i].OP.operador.TipoOperador,PilaResultados,Valor);
            else
                {
                    PilaResultados.Pop (Valor);
                    Operando2=Valor;
                    PilaResultados.Pop (Valor);
                    Operando1=Valor;
                    Resultado=Operar(Operando1, Operando2, EPostfija[i].OP.operador.simbolo);
                    PilaResultados.Push(Resultado);
                }
        }
    //vacío la pila y obtengo el resultado
    PilaResultados.Pop(Valor);
    Resultado=Valor;
    return Resultado;
}

Calc::elemento_t* Calc::preparaCadena (const char* cadena, int& t)
{
    short int Tam_Cadenna=t-1;
    elemento_t *EP = new elemento_t[Tam_Cadenna];
    char aux[100];
    int j=0;
    t=0;

    for (unsigned short int i=0; i<Tam_Cadenna; i++)
    {
        if (esOperando(cadena[i]))
        {
            aux[j++]=cadena[i++];
            while (esOperando (cadena[i]))
            {
                aux[j++]=cadena[i++];
                if (cadena[i-1]=='e')
                {
                    aux[j++]=cadena[i++];//incorporo el '+' despues del 'e'
                }
            }
            aux[j]='\0';
            EP[t].semantica=OPERANDO;
            std::stringstream ss(aux);
            ss>>EP[t].OP.operando;
            //std::cout<<"Soy el operando= "<<EP[t].OP.operando<<std::endl;
            j=0;
            t++;
            i--;
        }
            else
                {
                    EP[t].semantica=OPERADOR;
                    if (0==t &&!esParentesis(cadena[i]))
                        {
                            if (cadena[i]=='+')
                                EP[t].OP.operador=cadena_ref[POS];
                            else if (cadena[i]=='-')
                                EP[t].OP.operador=cadena_ref[NEG];
                        }
                    else

                        if (esOperador(cadena[i]) && (esOperador(cadena[i-1]) || (cadena[i-1]=='(')))
                            {
                                if (cadena[i]=='+')
                                    EP[t].OP.operador=cadena_ref[POS];
                                else if (cadena[i]=='-')
                                    EP[t].OP.operador=cadena_ref[NEG];
                                else
                                    EP[t].OP.operador=*defineOperador(cadena[i]);
                            }

                        else
                            EP[t].OP.operador=*defineOperador(cadena[i]);
                    std::cout<<"Soy el operador= "<<EP[t].OP.operador.simbolo<<std::endl;
                    t++;
                }
        }
    return EP;
}

void Calc::InicializarArray()
{
    cadena_ref[0]= {'(',0,PAREN_IZQ, true, false};
    cadena_ref[1]= {')',0,PAREN_DER, true, false};
    cadena_ref[2]= {'^',1,POT, false, true};
    cadena_ref[3]= {'*',3,MULT, true, true};
    cadena_ref[4]= {'/',3,DIV, true, true};
    cadena_ref[5]= {'+',4,SUMA, true, true};
    cadena_ref[6]= {'-',4,RESTA, true, true};
    cadena_ref[7]= {'-',1,NEG, false, false};
    cadena_ref[8]= {'+',1,POS, false, false};
    cadena_ref[9]= {'%',2,PORC, false, false};
    cadena_ref[10]= {'s',1,RAIZC, false, false};
    cadena_ref[11]= {'m',3,MOD,true, true};
}

double Calc::CalcularExpresion()
{
    if (cadena)
        {
			elemento_t *EI=preparaCadena(cadena, tamanno);
            elemento_t *EP=pasaPostfija(EI, tamanno);
            return EvaluaEpostfija(EP, tamanno);
        }
    else
        return 0;
}

void Calc::anadirExpresion(const std::string &sExpresion)
{
	if (cadena)
    {
        delete[]cadena;
        tamanno=0;
    }
    cadena = new char[sExpresion.length()+1];
    strcpy(cadena, sExpresion.c_str());
    tamanno=sExpresion.length()+1;
}

void Calc::anadirExpresion(const char* cExpresion)
{
    if (cadena)
    {
        delete[]cadena;
        tamanno=0;
    }
    tamanno=strlen(cExpresion)+1;
	cadena = new char[tamanno];
    strcpy(cadena, cExpresion);
}

void Calc::quitaEspacios(char* cadena)
{
    char* punt = cadena;
    while (*cadena!='\0')
    {
        if (*punt==' ')
        {
            punt++;
        }
        else
        {
            *cadena++=*punt++;
        }
    }
}
