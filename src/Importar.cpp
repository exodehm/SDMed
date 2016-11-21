#include "../include/Importar.h"

Importar::Importar(const char* N):nombreArchivo(N) {}

Importar::~Importar()
{
    //dtor
}

ImportarBC3::ImportarBC3(const char* N):Importar(N) {}


nodo<Concepto,Medicion>* ImportarBC3::importar ()
{
    std::ifstream archivo (nombreArchivo);
    if (!archivo)
    {
        std::cout<<"No puedo encontrar "<<nombreArchivo<<std::endl;
        return 0;
    }
    else
    {
        char registro[40000];
        /***********************************/
        /********Registros C****************/
        /***********************************/
        std::cout<<"Procesar registro C"<<std::endl;
        while (!archivo.eof())
        {
            archivo.getline (registro,40000,'~');
            if (registro[0]=='C')
            {
                procesarConceptos(&registro[2]);
            }
        }
        //ahora ponemos el nodo raíz al comienzo
        std::cout<<"Ahora pongo el nodo raiz al comienzo"<<std::endl;
        nodo<Concepto,Medicion>* indice = NuevoGrafo.Raiz;
        while (indice->siguiente && !esRaiz(indice->datonodo.LeeCodigo()))
        {
            indice=indice->siguiente;
        }
        std::cout<<"Supuesta raiz: "<<indice->datonodo.LeeCodigo()<<std::endl;
        nodo<Concepto,Medicion>* anterior = NuevoGrafo.Raiz;//posiciono un nodo antes de indice
        while (anterior->siguiente && anterior->siguiente!=indice)
        {
            anterior=anterior->siguiente;
        }
        anterior->siguiente=indice->siguiente;
        indice->siguiente=NuevoGrafo.Raiz;
        NuevoGrafo.Raiz=indice;
        indice=NuevoGrafo.Raiz;
        while (indice->siguiente)
        {
            quitarSimbolos(indice);
            std::cout<<indice->datonodo.LeeCodigo()<<"-";
            indice=indice->siguiente;
        }
        quitarSimbolos(indice);
        std::cout<<indice->datonodo.LeeCodigo()<<std::endl;
        std::cout<<"Raiz: "<<NuevoGrafo.Raiz->datonodo.LeeCodigo()<<std::endl;

        /***********************************/
        /********Registros D****************/
        /***********************************/
        std::cout<<"Procesar registro D"<<std::endl;
        archivo.seekg(0,std::ios::beg);
        while (!archivo.eof())
        {
            archivo.getline (registro,40000,'~');
            if (registro[0]=='D')
            {
                procesarRelaciones(&registro[2]);
            }
        }
        /***********************************/
        /********Registros M****************/
        /***********************************/
        std::cout<<"Procesar registro M"<<std::endl;
        archivo.seekg(0,std::ios::beg);
        while (!archivo.eof())
        {
            archivo.getline (registro,40000,'~');
            if (registro[0]=='M')
            {
                //std::cout<<"Procesar M"<<std::endl;
                procesarMediciones(&registro[2]);
            }
        }
        /***********************************/
        /********Registros N y T************/
        /***********************************/
        std::cout<<"Procesar registro N"<<std::endl;
        archivo.seekg(0,std::ios::beg);
        while (!archivo.eof())
        {
            archivo.getline (registro,40000,'~');
            if (registro[0]=='N')
            {
                //std::cout<<"Procesar N"<<std::endl;
                procesarMediciones(&registro[2]);
            }
            if (registro[0]=='T')
            {
                procesarTexto(&registro[2]);
            }
        }
        archivo.close();
        /*indice=NuevoGrafo.Raiz;
        int contador=0;
        while (indice)
        {
            contador++;
            indice=indice->siguiente;
            if (contador==34) std::cout<<"El nodo de la discordia?"<<indice->datonodo.LeeCodigo()<<std::endl;
        }
        std::cout<<"Total conceptos: "<<contador<<std::endl;*/
    }
    /*
        while (p)
            {
                    case 'L':
                    {
                        std::cout<<"Proceso pliegos"<<std::endl;
                        break;
                    }
                    case 'W':
                    {
                        std::cout<<"Proceso ámbito geográfico"<<std::endl;
                        break;
                    }
                    case 'G':
                    {
                        std::cout<<"Proceso información gráfica"<<std::endl;
                        break;
                    }
                    default:
                    {
                        std::cout<<"Proceso otros conceptos"<<std::endl;
                        break;
                    }
                    }
                p=strtok(0,token);
            }
    */
    std::cout<<"Direccion devuelta: "<<NuevoGrafo.Raiz<<std::endl;
    return NuevoGrafo.Raiz;
}

void ImportarBC3::procesarConceptos(char* linea)
{
    std::cout<<linea<<std::endl;
    char datos[6][200];
    std::istringstream iss(linea);
    for (int i=0; i<6; i++)
    {
        iss.getline(datos[i],200,'|');
        //std::cout<<"Dato["<<i<<"]: "<<datos[i]<<std::endl;
    }
    //hago una cadena para albergar el nombre del nodo
    std::string nombre(datos[0]);
    //otra cadena para el resumen
    std::string resumen(datos[2]);
    //hago una cadena para albergar los datos de la fecha y poder usar el constructor
    std::string F(datos[4]);
    //naturaleza
    int nat=0;
    if (datos[5][0]!='0')
    {
        nat=atoi(datos[5]);
    }
    else if (nombre.find('#')!=std::string::npos)
    {
        nat=6;
    }
    else
    {
        nat=7;
    }

    Concepto NuevoConcepto(nombre,0,resumen,atof(datos[3]),nat);
    NuevoConcepto.EscribeUd(datos[1]);
    Fecha fecha(F);
    NuevoConcepto.EscribeFecha(fecha);

    nodo<Concepto,Medicion>* nuevoNodo = new nodo<Concepto,Medicion>(NuevoConcepto);
    if (!NuevoGrafo.Raiz)//primer elemento
        NuevoGrafo.Raiz=nuevoNodo;
    else
        NuevoGrafo.anadirNodo(nuevoNodo);
    std::cout<<"Añadido nodo: "<<nuevoNodo->datonodo.LeeCodigo()<<std::endl;
}

void ImportarBC3::procesarRelaciones (char* linea)
{
    //Miro si el registro tiene 2 o 3 campos
    //3 campos->verson FIEBDC-3/2012->tener en cuenta porcentajes
    //2 campos->version anterior->no considera porcentajes
    int nHijos=0;
    int nCampos=0;
    int i=0;
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
    std::cout<<"Hijos: "<<nHijos/3<<std::endl;
    std::cout<<"Campos: "<<nCampos-1<<std::endl;
    std::stringstream iss(linea);
    std::getline (iss,nombrepadre,'|');
    //std::getline (iss,nombrehijos,'|');
    std::cout<<"Padre: "<<nombrepadre<<"- Hijos: "<<nombrehijos<<std::endl;

    std::size_t posicion=nombrepadre.find('#');
    if (posicion!=std::string::npos)
    {
        nombrepadre=nombrepadre.substr(0,posicion);
    }
    std::cout<<"NombrePadre: "<<nombrepadre<<std::endl;
    nodo <Concepto,Medicion>* nodoPadre=buscaNodoPorCodigo(nombrepadre);
    std::cout<<"Padre en nodo: "<<nodoPadre->datonodo.LeeCodigo()<<std::endl;

    std::string hijo,factor,cantidad;

    for (int i=0; i<nHijos/3; i++)
    {
        std::cout<<"Vuelta "<<i<<std::endl;
        std::getline (iss,hijo,'\\');
        std::getline (iss,factor,'\\');
        std::getline (iss,cantidad,'\\');
        std::cout<<"Hijo: "<<hijo<<" Factor: "<<factor<<" Cantidad: "<<cantidad<<std::endl;
        nodo<Concepto,Medicion>*nodoHijo=buscaNodoPorCodigo(hijo);
        std::cout<<"Hijo en nodo: "<<nodoHijo->datonodo.LeeCodigo()<<std::endl;
        arista<Medicion,Concepto>*A=new arista<Medicion,Concepto>(std::atof(cantidad.c_str()));
        NuevoGrafo.InsertarHijo(nodoPadre,nodoHijo,A->anterior,A);
    }
}

void ImportarBC3::procesarMediciones (char* linea)
{
    std::stringstream iss(linea);
    std::string datos[3];
    for (int i=0; i<3; i++)
    {
        std::getline (iss,datos[i],'|');
    }
    std::string nombrePadre;
    std::string nombreHijo;
    std::size_t posicion=datos[0].find('\\');
    if (posicion!=std::string::npos)
    {
        nombrePadre=datos[0].substr(0,posicion);
        nombreHijo=datos[0].substr(posicion+1,datos[0].length());
    }
    posicion=nombrePadre.find('#');
    if (posicion!=std::string::npos)
    {
        nombrePadre=nombrePadre.substr(0,posicion);
    }

    nodo <Concepto,Medicion>* nodoPadre=buscaNodoPorCodigo(nombrePadre);
    arista<Medicion,Concepto>*A=nodoPadre->adyacente;
    while (A->destino->datonodo.LeeCodigo()!=nombreHijo)
    {
        A=A->siguiente;
    }
    A->datoarista.EscribeTotal(std::atof(datos[2].c_str()));
    std::cout<<"Padre: "<<nodoPadre->datonodo.LeeCodigo()<<std::endl;
    std::cout<<"Hijo: "<<A->destino->datonodo.LeeCodigo()<<std::endl;
    std::string conceptos[6];
    float cantidades[4];
    while (iss.peek()!='|')
    {
        for (int i=0; i<6; i++)
        {
            std::getline (iss,conceptos[i],'\\');
            std::cout<<"Concepto["<<i<<"]= "<<conceptos[i]<<std::endl;
        }

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
        A->datoarista.Insertar(tipo,conceptos[1],cantidades[0],cantidades[1],cantidades[2],cantidades[3]);
    }
}

void ImportarBC3::procesarTexto(char* linea)
{
    std::stringstream iss(linea);
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
    nodo <Concepto,Medicion>* nodoPadre=buscaNodoPorCodigo(datos[0]);
    //std::cout<<nodoPadre->datonodo.LeeCodigo()<<std::endl;
    nodoPadre->datonodo.EscribeTexto(datos[1]);
}

void ImportarBC3::quitarSimbolos (nodo<Concepto,Medicion>* n)
{
    std::size_t posicion=n->datonodo.LeeCodigo().find('#');
    if (posicion!=std::string::npos)
    {
        n->datonodo.EscribeCodigo(n->datonodo.LeeCodigo().substr(0,posicion));
    }
}

nodo<Concepto,Medicion>* ImportarBC3::buscaNodoPorCodigo (std::string codigo)
{
    //std::cout<<"Buscando nodo por el codigo: "<<codigo<<std::endl;
    nodo <Concepto,Medicion>* indice=NuevoGrafo.Raiz;
    //std::cout<<"Leyendo: "<<indice->datonodo.LeeCodigo();
    while (indice->datonodo.LeeCodigo()!=codigo)
    {
        indice=indice->siguiente;
    }
    //std::cout<<"Retornando: "<<indice->datonodo.LeeCodigo();
    return indice;
}

bool ImportarBC3::esRaiz(const std::string& S)
{
    return (S[S.length()-1]=='#' && S[S.length()-2]=='#');
}
