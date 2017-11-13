#include "../include/Obra.h"

Obra::Obra():G(),selectorMedCer(MedCert::MEDICION),Redondeos() {}

Obra::Obra(TEXTO Cod, TEXTO Res, int ud, int CuadroDePrecios):G(),codificacion(CuadroDePrecios),
    selectorMedCer(MedCert::MEDICION),Redondeos()
{
    Concepto* conceptoRaiz=new Concepto(Cod,ud,Res);
    IniciarObra(*conceptoRaiz);
    std::cout<<"Iniciada la obra con "<<LeeCodigoObra().toStdString()<<std::endl;    
}

Obra::Obra(Concepto conceptoRaiz)
{
    IniciarObra(conceptoRaiz);
}

Obra::Obra(const Obra& origen)
{
    G=origen.G;
    Redondeos=origen.Redondeos;
    Cert=origen.Cert;
    padre=G.LeeRaiz();
    aristaPadre=new arista<MedCert,Concepto>(1);//el concepto raiz en principio tiene siempre el valor 1 (una unidad de obra)
    aristaPadre->destino=padre;
    pilaAristas.push(aristaPadre);
    aristaActual=0;
}

Obra& Obra::operator=(const Obra& origen)
{
    if (this!=&origen)
    {
        G=origen.G;
        Redondeos=origen.Redondeos;
        Cert=origen.Cert;
        padre=G.LeeRaiz();
        aristaPadre=new arista<MedCert,Concepto>(1);//el concepto raiz en principio tiene siempre el valor 1 (una unidad de obra)
        aristaPadre->destino=padre;
        pilaAristas.push(aristaPadre);
        aristaActual=0;
    }
    return *this;
}

Obra::~Obra()
{
    //delete G;
}

void Obra::IniciarObra (Concepto conceptoRaiz)
{
    pNodo primero=new nodo<Concepto,MedCert> (conceptoRaiz);
    pArista aristaInicial=new arista<MedCert,Concepto>(1);
    G.Insertar(primero,primero, aristaInicial);
    //mapaNodos.insert(std::pair<const TEXTO,pNodo>(primero->datonodo.LeeCodigo(),primero));
    mapaNodos.insert(primero->datonodo.LeeCodigo(),primero);
    padre=primero;
    aristaPadre=new arista<MedCert,Concepto>(1);//el concepto raiz en principio tiene siempre el valor 1 (una unidad de obra)
    aristaPadre->destino=padre;
    pilaAristas.push(aristaPadre);
    aristaActual=nullptr;
    CI=1.00;
}

void Obra::CrearPartida (TEXTO CodPadre, float cantidad, TEXTO CodHijo)
{
    MedCert m(cantidad);
    CrearPartida(CodPadre,m,CodHijo);
}

void Obra::CrearPartida (TEXTO CodPadre, MedCert med, TEXTO CodHijo)
{
    pNodo padre = ExisteConcepto(CodPadre);
    pNodo hijo = ExisteConcepto(CodHijo);
    if (!padre)
    {
        padre = DefinirConcepto(CodPadre);
    }
    if (!hijo)
    {
        hijo = DefinirConcepto(CodHijo);
    }
    pArista relacion=new arista<MedCert,Concepto>(med);
    G.Insertar(padre, hijo, relacion);
}

void Obra::CrearPartida(TEXTO Cod, TEXTO Res, float cantidad, float precio, int ud, int nat)
{
    /******variables que usaré para crear el concepto*****************/    
    pArista nuevaArista;
    //int N=Codificacion::Partida;//en principio la inicializo como partida
    int N=nat;
    //ahora toca ver si se trata de un porcentaje
    pNodo nuevoNodo = ExisteConcepto(Cod);
    if (!nuevoNodo)
    {
        nuevoNodo = DefinirConcepto(Cod,Res,precio,ud,nat);
    }
    //según sea partida o no, crearé una cant certificacion = cant medicion o no
    nuevaArista= new arista<MedCert,Concepto>(cantidad);
    //si el nodo es una partida, borro el valor de la certificacion, si no, me vale como esta==a la medicion
    if (NivelUno())
    {
        selectorMedCer=MedCert::CERTIFICACION;
        nuevaArista->datoarista.escribeTotalMedCer(selectorMedCer,0);
        selectorMedCer=MedCert::MEDICION;
    } 
    G.Insertar(padre,nuevoNodo,nuevaArista);
    aristaActual = G.hallarArista(padre,nuevoNodo);
    //Y actualizo el grafo partiendo del nodo insertado
    Actualizar(aristaActual->destino);
}

void Obra::CrearPartida(TEXTO CodigoHijo, int posicion)
{
    qDebug()<<"Insertar por posicion en: "<<posicion;
    pNodo nuevoNodo = ExisteConcepto(CodigoHijo);
    if (!nuevoNodo)
    {
       nuevoNodo = DefinirConcepto(CodigoHijo);       
    }
    float cantidad=0;
    if (NivelCero())
    {
        cantidad=1;
    }
    pArista A = new arista<MedCert,Concepto>(cantidad);
    G.Insertar(padre, nuevoNodo, A, posicion);
}

pNodo Obra::DefinirConcepto(TEXTO Cod, TEXTO Res, float precio,int ud, int nat)
{
    int N=nat;
    if (Cod.contains("%"))
    {
        ud=Unidad::porcentaje;
        N=Codificacion::Sin_clasificar;
        //std::cin.ignore(100,'\n');
        precio=padre->datonodo.LeeImportePres()/100;
    }
    else //si no lo es
    {
        /***asignamos la naturaleza***/
        if (NivelCero())
        {
            N=Codificacion::Capitulo;
        }
        else if(NivelUno())
        {
            N=Codificacion::Partida;
        }
        else
        {
            N=codificacion.AsignarNaturalezaSegunCuadro(Cod.toStdString());
        }
        /***si la naturaleza del concepto es maquinaria o mano de obra podemos asignar
        de forma automatica la unidad a la hora**/
        if (N==Codificacion::Mano_de_Obra || N==Codificacion::Maquinaria) //mano de obra o maquinaria
        {
            ud=Unidad::hora; //hora h
        }
        else if(N==Codificacion::Partida)
        {
            ud=Unidad::sinUnidad;
        }
    }
    //por ultimo creo el concepto con los datos dados y lo inserto en la obra
    Concepto* NuevoConcepto= new Concepto(Cod,ud, Res,precio,N);
    pNodo nuevoNodo = new nodo<Concepto,MedCert>(*NuevoConcepto);
    //mapaNodos.insert(std::pair<const TEXTO,pNodo>(Cod,nuevoNodo));
    mapaNodos.insert(Cod,nuevoNodo);
    return nuevoNodo;
}

void Obra::CopiarPartida(TEXTO codigo, float cantidad)
{
    /*pNodo nAux=0;
    TratarNodo* tratamiento = new EncontrarNodoPorCodigo (codigo,nAux);
    G.recorrerNodos(*tratamiento);

    pArista nuevaArista=new arista<MedCert,Concepto>(cantidad);

    G.CopiarNodo(padre,nAux,aristaActual,nuevaArista);
    aristaActual=nuevaArista;

    Actualizar(aristaActual->destino);*/
}

void Obra::DuplicarPartida(TEXTO codigo)
{
    //creo un nuevo concepto con los mismos datos que el actual
    Concepto* NuevoConcepto= new Concepto(aristaActual->destino->datonodo);
    //le pongo el nuevo código
    NuevoConcepto->EscribeCodigo(codigo);
    //creo el nuevo nodo
    pNodo Nuevo = new nodo<Concepto,MedCert>(*NuevoConcepto);
    //creo una nueva arista con valor 0
    pArista aux= new arista<MedCert,Concepto>(0);
    //la inserto bajo el mismo padre que el nodo que estoy copiando
    G.Insertar(padre,Nuevo, aux);
    //G.Insertar(padre,Nuevo, 0);
    //ahora ligo el nuevo nodo con los hijos del nodo que he copiado
    if (aristaActual->destino->adyacente)//si tiene hijos
    {
        pArista auxiliar=aristaActual->destino->adyacente;
        while (auxiliar->siguiente)//mientras haya aristas que copiar
        {
            pArista nueva=new arista<MedCert,Concepto>(auxiliar->datoarista);
            //G.Insertar(Nuevo, auxiliar->destino,nueva, aristaActual);
            auxiliar=auxiliar->siguiente;
        }
        //ultimo elemento
        pArista nueva=new arista<MedCert,Concepto>(auxiliar->datoarista);
        //G.Insertar(Nuevo, auxiliar->destino,nueva, aristaActual);
        auxiliar=auxiliar->siguiente;
    }
    Actualizar(aristaActual->destino);
}

void Obra::BajarNivel()
{
    if (padre->adyacente)
    {
        aristaPadre=aristaActual;
        pilaAristas.push (aristaPadre);
        padre=aristaPadre->destino;
        aristaActual=padre->adyacente;//==0 en caso de hoja
    }    
}

/*void Obra::SubirNivel()
{
    if (pilaAristas.size()>1)
    {
        pArista aux = pilaAristas.top();
        pilaAristas.pop();
        aristaPadre=pilaAristas.top();
        padre=pilaAristas.top()->destino;
        aristaActual=aux;
    }
    if (padre->adyacente)
    {
        //aristaActual=padre->adyacente;
        //aristaActual=kk;
    }
}*/

int Obra::SubirNivel()
{
    if (pilaAristas.size()>1)
    {
        pArista aux = pilaAristas.top();
        pilaAristas.pop();
        aristaPadre=pilaAristas.top();
        padre=pilaAristas.top()->destino;
        aristaActual=aux;
    }
    pArista aux = padre->adyacente;
    int pos=0;
    while (aux!=aristaActual)
    {
        aux=aux->siguiente;
        pos++;
    }
    return pos;
}

void Obra::Siguiente()
{
    if (aristaPadre->siguiente)
    {
        pArista auxiliar=aristaPadre->siguiente;
        SubirNivel();
        aristaActual=auxiliar;
        BajarNivel();
    }
}

void Obra::Anterior()
{
    if (aristaPadre->anterior)
    {
        pArista auxiliar=aristaPadre->anterior;
        SubirNivel();
        aristaActual=auxiliar;
        BajarNivel();
    }
}

void Obra::HijoSiguiente()
{
    if (aristaActual && aristaActual->siguiente)
    {
        aristaActual=aristaActual->siguiente;
        //std::cout<<aristaActual->destino->datonodo.LeeResumen()<<std::endl;
    }
}

void Obra::HijoAnterior()
{
    if (aristaActual && aristaActual->anterior)
    {
        aristaActual=aristaActual->anterior;
        //std::cout<<aristaActual->destino->datonodo.LeeResumen()<<std::endl;
    }
}

void Obra::IrAInicio()
{
    padre = G.LeeRaiz();
    aristaPadre->destino = padre;
    aristaActual = padre->adyacente;
}

void Obra::PosicionarAristaActual(int pos)
{
    if (padre->adyacente)
    {
        aristaActual = padre->adyacente;
        for (int i=0;i<pos;i++)
        {
            aristaActual=aristaActual->siguiente;
        }
    }
}

void Obra::MostrarHijos()
{
    /*std::string nombreNodo="";
    pArista aristaParaMostrar= new arista<MedCert,Concepto>;
    TratarArista* tratamiento=new Imprimir (nombreNodo, aristaParaMostrar, aristaActual);*/
    /*******************************/
    /********************************/
    //linea horizontal superior
    /*dibujaLinea();
    //cabecera
    std::cout<<"\t"
             <<std::left<<std::setfill(' ')//el texto se alinea a la izquierda y el relleno es un espacio
             <<'|'<<std::setw(AnchoCodigo-1)<<"Codigo"
             <<'|'<<std::setw(AnchoNaturaleza-1)<<"Nat"
             <<'|'<<std::setw(AnchoUd-1)<<"Ud"
             <<'|'<<std::setw(AnchoResumen-1)<<"Resumen"
             <<std::right//el texto se alinea a la derecha
             <<'|'<<std::setw(AnchoCanPres-1 )<<"CanPres"
             <<'|'<<std::setw(AnchoCanPres-1 )<<"CanCert"
             <<'|'<<std::setw(AnchoPorCertPres-1 )<<"PorCertPres"
             <<'|'<<std::setw(AnchoPrPres-1)<<"PrPres"
             <<'|'<<std::setw(AnchoPrPres-1)<<"PrCert"
             <<'|'<<std::setw(AnchoImpPres-1)<<"ImpPres"
             <<'|'<<std::setw(AnchoImpPres-1)<<"ImpCert"
             <<'|'<<std::endl;

    std::cout<<"\t"
             <<std::left//el texto se alinea a la izquierda
             <<'|'<<std::setw(AnchoCodigo-1)<<padre->datonodo.LeeCodigo()
             <<'|'<<std::setw(AnchoNaturaleza-1)<<""
             <<'|'<<std::setw(AnchoUd-1)<<""
             <<'|'<<std::setw(AnchoResumen-1)<<padre->datonodo.LeeResumen()
             <<std::right//el texto se alinea a la derecha
             <<'|'<<std::setw(AnchoCanPres-1)<<aristaPadre->datoarista.LeeMedicion().LeeTotal()
             <<'|'<<std::setw(AnchoCanPres-1)<<aristaPadre->datoarista.LeeCertificacion().LeeTotal()
             <<'|'<<std::setw(AnchoPorCertPres-1)<<(aristaPadre->datoarista.LeeCertificacion().LeeTotal()/aristaPadre->datoarista.LeeMedicion().LeeTotal())*100
             <<'|'<<std::setw(AnchoPrPres-1)<<padre->datonodo.LeeImportePres()//Precio de la medicion
             <<'|'<<std::setw(AnchoPrPres-1)<<padre->datonodo.LeeImporteCert()//Precio de la certificacion

             <<'|'<<std::setw(AnchoImpPres-1)<< ((padre->datonodo.LeeImportePres()==0)
                     ?   padre->datonodo.LeeImportePres()*1
                     :   padre->datonodo.LeeImportePres()*aristaPadre->datoarista.LeeMedicion().LeeTotal())

             <<'|'<<std::setw(AnchoImpPres-1)<< ((padre->datonodo.LeeImporteCert()==0)
                     ?   padre->datonodo.LeeImporteCert()*1
                     :   padre->datonodo.LeeImporteCert()*aristaPadre->datoarista.LeeCertificacion().LeeTotal())
             <<'|'<<std::endl;
    //linea horizontal superior
    dibujaLinea();
    G.recorrerHijos(padre, *tratamiento);
    //linea horizontal inferior
    dibujaLinea();
    //Mediciones
    VerMedicion VerMediciones(selectorMedCer);
    VerMediciones(aristaPadre->datoarista);

    //texto
    std::cout<<"\n\n"<<padre->datonodo.LeeTexto()<<"\n\n";*/
    //ListaNodosAristas lista = G.recorrerHijos(padre);
    //lista.push_front(padre);
    //for (auto it= lista.begin(); it!=lista.end(); ++it)
    {
        /*std::cout<<(*it)->datonodo.LeeCodigo()<<"|"                              //codigo
                 <<(*it)->datonodo.LeeNat()<<"|"                                 //naturaleza
                 <<(*it)->datonodo.LeeUd()<<"|"                                  //ud
                 <<(*it)->datonodo.LeeResumen()<<"|"                             //resumen
                 <<aristaPadre->datoarista.LeeMedicion().LeeTotal()<<"|"         //Cantidad presupuestada(medida)
                 <<aristaPadre->datoarista.LeeCertificacion().LeeTotal()<<"|"    //Cantidad certificada
                 <<(aristaPadre->datoarista.LeeCertificacion().LeeTotal()/aristaPadre->datoarista.LeeMedicion().LeeTotal())*100<<"|" //porcentaje certificado
                 <<(*it)->datonodo.LeeImportePres()<<"|"                         //precio de la medicion
                 <<(*it)->datonodo.LeeImporteCert()<<"|"                         //precio de la certificacion
                 <<(((*it)->datonodo.LeeImportePres()==0)
                    ? (*it)->datonodo.LeeImportePres()*1
                    : (*it)->datonodo.LeeImportePres()*aristaPadre->datoarista.LeeMedicion().LeeTotal())<<"|"
                 <<(((*it)->datonodo.LeeImporteCert()==0)
                    ? (*it)->datonodo.LeeImporteCert()*1
                    : (*it)->datonodo.LeeImporteCert()*aristaPadre->datoarista.LeeCertificacion().LeeTotal())<<"|"
                 <<std::endl;*/

    }
    /***************mediciones*****************/
    std::cout<<"Mediciones:"<<std::endl;
    aristaPadre->datoarista.Ver();
    /***************texto********************/
    std::cout<<"Texto:"<<std::endl;
    //std::cout<<"\n"<<padre->datonodo.LeeTexto()<<"\n\n";
}

TEXTO Obra::VerTexto()
{
    return padre->datonodo.LeeTexto();
}

void Obra:: SumarHijos(pNodo padre)
{
    if (padre->adyacente)
    {
        //std::cout<<"Sumando hijos de "<<n->datonodo.LeeCodigo()<<std::endl;
        float sumapres=0, sumacert=0;
        float medicion = 0, certificacion = 0;
        float precio = 0;
        ListaAristasNodos lista = G.recorrerHijos(padre);
        for (auto elem : lista)
        {
            medicion = elem.first->datoarista.LeeMedicion().LeeTotal();
            certificacion = elem.first->datoarista.LeeCertificacion().LeeTotal();
            precio = elem.second->datonodo.LeeImportePres();           
            if (NivelUno(padre))
            {
                precio*=CI;
            }
            qDebug()<<"Cantidad: "<<medicion<<"* Precio: "<<precio;
            if (elem.second->datonodo.LeeCodigo().contains("%")) //si es un porcentaje
            {
                elem.second->datonodo.EscribeImportePres(sumapres/100.0);
            }
            sumapres+=Redondear(precio * medicion,3);
            sumacert+=Redondear(precio * certificacion,3);
            qDebug()<<"sumapres: "<<sumapres;
            qDebug()<<"sumacert: "<<sumacert;
        }
        padre->datonodo.EscribeImportePres(sumapres);
        padre->datonodo.EscribeImporteCert(sumacert);
    }
}

void Obra::BorrarPartida()
{
    qDebug()<<"Borrar la partida: "<<aristaActual->destino->datonodo.LeeResumen();
    auto it = mapaNodos.find(aristaActual->destino->datonodo.LeeCodigo());
    if (it!=mapaNodos.end())
    {
        qDebug()<<"Borro el nodo: "<<aristaActual->destino->datonodo.LeeCodigo();
        G.borrarNodos(aristaActual);
    }
    //mapaNodos.erase(aristaActual->destino->datonodo.LeeCodigo());
    std::list<pNodo> lista = G.recorrerNodos();
    mapaNodos.clear();
    for (auto elem : lista)
    {
        mapaNodos.insert(elem->datonodo.LeeCodigo(),elem);
        qDebug()<<"Insertar en el mapa el nodo: "<<elem->datonodo.LeeCodigo();
    }
    if (padre->adyacente)
    {
        aristaActual=padre->adyacente;
    }
    else
    {
        aristaActual->destino=0;
    }
    Actualizar(aristaActual->destino);
}

void Obra::SuprimirDescomposicion()
{
    //nodo al que le borraré la descomposicion
    pNodo nodo=aristaActual->destino;
    pArista auxiliar=nodo->adyacente;
    while (auxiliar)
    {
        G.borrarNodos(auxiliar);
        if (nodo->adyacente)
        {
            auxiliar=nodo->adyacente;
        }
        else
        {
            auxiliar=nullptr;
        }
    }
    Actualizar(aristaActual->destino);
}

void Obra::Medir_O_Certificar()
{
    if (aristaPadre->destino->datonodo.LeeNat()==Codificacion::Partida)//solo esta permitido que tengan medicion las partidas
    {
        /*aristaPadre->datoarista.LeeMedCer(selectorMedCer).Insertar();
        Actualizar(aristaPadre->destino);*/
    }
}

void Obra::BorrarLineasMedicion(int pos, int numLineas)
{
    if (aristaPadre->datoarista.LeeMedCer().hayMedicion())
    {
        aristaPadre->datoarista.ModificaMedCer(selectorMedCer).EliminarLineas(pos, numLineas);
        Actualizar(aristaPadre->destino);
    }  
}

void Obra::borrarTodaMedicionOCertificacion()
{
    if (HayMedicion())
    {
        aristaActual->datoarista.ModificaMedCer(selectorMedCer).BorrarMedicion();
        Actualizar(aristaPadre->destino);
    }
}

void Obra::borrarTodaMedicion()
{
    if (HayMedicion())
    {
        aristaActual->datoarista.ModificaMedCer(MedCert::MEDICION).BorrarMedicion();
        Actualizar(aristaPadre->destino);
    }
}

void Obra::borrarTodaCertificacion()
{
    if (HayMedicion())
    {
        aristaActual->datoarista.ModificaMedCer(MedCert::CERTIFICACION).BorrarMedicion();
        Actualizar(aristaPadre->destino);
    }
}

void Obra::PosicionarLineaActualMedicion(int fila)
{
    aristaPadre->datoarista.ModificaMedCer(selectorMedCer).PosicionarLineaActual(fila);
}

void Obra::avanzarLineaActualMedicion()
{
    if (aristaPadre->datoarista.LeeMedicion().hayMedicion())
    {
        //aristaPadre->datoarista.LeeMedCer(selectorMedCer).AvanzarActual();
    }
}

void Obra::retrocederLineaActualMedicion()
{
    if (aristaPadre->datoarista.LeeMedicion().hayMedicion())
    {
        //aristaPadre->datoarista.LeeMedCer(selectorMedCer).RetrocederActual();
    }
}

void Obra::seleccionarLineaMedicion()
{
    if (aristaPadre->datoarista.LeeMedicion().hayMedicion())
    {
        //aristaPadre->datoarista.LeeMedCer(selectorMedCer).SelecDeselecLinea();
    }
}

void Obra::selecDeselecTodo()
{
    if (aristaPadre->datoarista.LeeMedicion().hayMedicion())
    {
        //aristaPadre->datoarista.LeeMedCer(selectorMedCer).SelecDeselecTodo();
    }
}

void Obra::CopiarMedicion(Medicion& ListaMedicion, const QList<int> &listaIndices)
{
    int i=0;
    for (auto elem:listaIndices)
    {
        ListaMedicion.Insertar(i,aristaPadre->datoarista.LeeMedCer().LeeLineaEnPosicion(elem));
        i++;
    }
    //ListaMedicion.Ver();
}

/*std::list<TEXTO> Obra::copiarMedicion()
{
    std::list<std::string>listaMediciones;
    if (aristaPadre->datoarista.LeeMedCer(selectorMedCer).hayMedicion())
    {
        listaAuxiliar.clear();
        aristaPadre->datoarista.LeeMedCer(selectorMedCer).Copiar(&listaAuxiliar);
    }
    for (auto it=listaAuxiliar.begin(); it!=listaAuxiliar.end(); it++)
    {
        std::ostringstream oss;
        oss<<(*it)->LeeFase()<<"\t"<<(*it)->LeeComentario()<<"\t"<<(*it)->Lee_N_Uds()<<"\t"<<(*it)->LeeLargo()<<"\t"<<(*it)->LeeAncho()
           <<"\t"<<(*it)->LeeAlto()<<"\t"<<(*it)->LeeFormula()<<"\t"<<(*it)->LeeParcial()<<"\t"<<(*it)->LeeSubtotal()<<"\t"<<(*it)->LeeTipo()<<"\n";
        std::string aux(oss.str());
        listaMediciones.push_back(aux);
    }
    //return listaMediciones;
}*/

void Obra::InsertarLineasVaciasMedicion(int tabla, int pos, int num)
{
    qDebug()<<"Insertando linea vacia en tabla: "<<selectorMedCer;
    qDebug()<<"Certificacion actual: "<<Cert.verCertificacionActual();
    if (tabla==MedCert::CERTIFICACION)
    {
        aristaPadre->datoarista.ModificaMedCer(tabla).InsertarLineasVacias(pos,num,Cert.verCertificacionActual());
    }
    else
    {
        aristaPadre->datoarista.ModificaMedCer(tabla).InsertarLineasVacias(pos,num);
    }
}

void Obra::inicializarActual()
{
    /*if (aristaPadre->datoarista.hayMedicion())
    {
         aristaPadre->datoarista.LeeMedCer(selectorMedCer).actualAlComienzo();
    }*/
}


void Obra::PegarMedicion(int fila, const Medicion& ListaMedicion)
{
    PegarMedicion(fila, ListaMedicion, aristaPadre);
}

void Obra::PegarMedicion(int fila, const Medicion& ListaMedicion, pArista A)
{
    if (A->destino->datonodo.LeeNat()==Codificacion::Partida)//solo esta permitido que tengan medicion las partidas
        for (auto it =ListaMedicion.LeeLista().begin();it!=ListaMedicion.LeeLista().end();++it)
        {
            A->datoarista.ModificaMedCer().Insertar(fila,(*it));
            fila++;
        }
        Actualizar(A->destino);
}

void Obra::EditarCodificacion(int n)
{
    codificacion.CambiarCodificacion(n);
}

void Obra::bloquearColumna(int nColumna, float fValor)
{
    /*if (aristaPadre->destino->datonodo.LeeNat()==Codificacion::Partida)//solo esta permitido que tengan medicion las partidas
    {
        if (nColumna>0 && nColumna<6)
        {
            aristaPadre->datoarista.LeeMedCer(selectorMedCer).Bloquear(nColumna,fValor);
        }
        else
        {
            aristaPadre->datoarista.LeeMedCer(selectorMedCer).Desbloquear(nColumna);
        }
    }*/
}

void Obra::Desbloquear()
{
    //aristaPadre->datoarista.LeeMedCer(selectorMedCer).DesbloquearTodo();
}

void Obra::Certificar(const Medicion &listaParaCertificar)
{
    //if (aristaPadre->destino->datonodo.LeeNat()==Codificacion::Partida)//solo esta permitido que tengan medicion las partidas
    {
        int fila = 0;
        for (auto it =listaParaCertificar.LeeLista().begin();it!=listaParaCertificar.LeeLista().end();++it)
        {
            LineaMedicion linea = (*it);
            linea.EscribeFase(CertificacionActiva());
            aristaPadre->datoarista.ModificaMedCer(MedCert::CERTIFICACION).Insertar(fila,(linea));
            fila++;
        }
        Actualizar(aristaPadre->destino);
    }
}

bool Obra::anadirCertificacion(TEXTO tFecha)
{
    Fecha fecha(tFecha.toStdString());
    return Cert.anadir(fecha);
}

void Obra::borrarCertificacion(int n)
{
    Cert.eliminar(n);
}

int Obra::CertificacionActiva()
{
    return Cert.verCertificacionActual();
}

void Obra::EstablecerCertificacionActual(int n)
{
    Cert.cambiarCertificacionActual(n);
}

void Obra::cambiarFechaCertificacion(std::string fecha)
{
    Cert.cambiarFecha(fecha);
}

void Obra::VerNodos()
{
    std::list<pNodo> lista = G.recorrerNodos();
    for (auto elem:lista)
    {
        std::cout<<elem->datonodo.LeeCodigo().toStdString()<<"-";
    }
    std::cout<<std::endl;
}

void Obra::VerArbol()
{
    std::list<std::pair<pNodo,int>>lista = G.recorrerGrafoConNiveles(G.LeeRaiz());
    //std::cout<<G.LeeRaiz()->datonodo.LeeCodigo()<<std::endl;
    for (auto elem : lista)
    {
        std::cout<<std::setw(elem.second*2);
       // std::cout<<elem.first->datonodo.LeeCodigo()<<std::endl;
    }
}

void Obra::VerRama()
{
    std::list<std::pair<pNodo,int>>lista = G.recorrerGrafoConNiveles(padre);
    for (auto elem : lista)
    {
        std::cout<<std::setw(elem.second*2);
        //std::cout<<elem.first->datonodo.LeeCodigo()<<std::endl;
    }
}

void Obra::Actualizar(pNodo nodoactual)
{
    //si no existe ningun nodo que pende del nodo actual
    //fijo manualmente el precio a 0 e indico que el nodo a partir del que se actualice será el
    //propio padre. Metodo cutre pero que parece funcionar
    if (!nodoactual)
    {
        padre->datonodo.EscribeImportePres(0);
        nodoactual=padre;
    }
    qDebug()<<"Actualizando desde el nodo: "<<nodoactual->datonodo.LeeCodigo();
    std::list<pNodo>lista = G.recorrerAncestrosOrdenado(nodoactual);
    for (auto elem:lista)
    {
        qDebug()<<"Lista a actualizar: "<<elem->datonodo.LeeCodigo()<<"-"<<elem;
    }
    //recorro la lista de nodos efectuando la suma de sus hijos
    for(auto it =lista.begin(); it != lista.end(); it ++)
    {
        SumarHijos((*it));
    }  
}

void Obra::AjustarPrecio(float nuevoprecio)
{
    /* float precioActual=G.Raiz->datonodo.LeeImportePres();
     std::cout<<"Ajustar el precio: "<<precioActual<<std::endl;
     float factorDeAjuste=nuevoprecio/precioActual;
     std::cout<<"Factor de correción: "<<factorDeAjuste<<std::endl;

     std::cout<<"Las hojas son: ";
     for(auto Iterador = G.listaHojas.cbegin(); Iterador != G.listaHojas.cend(); Iterador++)
     {
         std::cout<<(*Iterador)->datonodo.LeeCodigo()<<" - ";
     }
     //multiplicando las hojas x el factor de corrección
     for(auto Iterador = G.listaHojas.cbegin(); Iterador != G.listaHojas.cend(); Iterador++)
     {
         (*Iterador)->datonodo.EscribeImportePres((*Iterador)->datonodo.LeeImportePres()*factorDeAjuste);
     }
     //y actualizo
     for(auto Iterador = G.listaHojas.cbegin(); Iterador != G.listaHojas.cend(); Iterador++)
     {
         Actualizar(*Iterador);
     }*/
    std::cout<<std::endl;
}

float Obra::Redondear(float numero, int precision)
{
    return (floor((numero * pow(10, precision) + 0.5)) / pow(10, precision));
}

void Obra::DesbloquearPrecio()
{
    aristaActual->destino->datonodo.desbloquearPrecio();
    aristaActual->destino->datonodo.EscribeImportePres(aristaActual->destino->datonodo.LeeImportePres());
    Actualizar(aristaActual->destino);
}

bool Obra::esPrecioBloqueado()
{
    return aristaActual->destino->datonodo.esPrecioBloqueado();
}

void Obra::EditarPrecio(float precio)
{
    aristaActual->destino->datonodo.EscribePrecio(precio);
    Actualizar(aristaActual->destino);
}

void Obra::EditarCostesIndirectos(float coste)
{
    CI=coste;
}

void Obra::Recalcular()
{


}

void Obra::EditarCodigo (TEXTO codigo)
{
    if (aristaActual)
    {
        aristaActual->destino->datonodo.EscribeCodigo(codigo);
        int N =codificacion.AsignarNaturalezaSegunCuadro(codigo.toStdString());
        aristaActual->destino->datonodo.EscribeNaturaleza(N);
        if (N==Codificacion::Mano_de_Obra || N==Codificacion::Maquinaria)
        {
            aristaActual->destino->datonodo.EscribeUd(Unidad::hora);
        }
    }
}

void Obra::EditarResumen (TEXTO resumen)
{
    if (aristaActual)
    {
        aristaActual->destino->datonodo.EscribeResumen(resumen);
    }
}

void Obra::EditarTexto (TEXTO textopartida)
{
    if (aristaPadre)
    {
        aristaPadre->destino->datonodo.EscribeTexto(textopartida);
    }
}

void Obra::BloquearPrecio (float precio)
{
    aristaActual->destino->datonodo.bloquearPrecio();
    aristaActual->destino->datonodo.EscribeImportePres(precio);
    Actualizar(aristaActual->destino);
}

void Obra::EditarCantidad (float cantidad)
{
    //qDebug()<<"aRISTA ACTUAL: "<<aristaActual->datoarista.LeeMedicion().LeeTotal();
    if (aristaActual)
    {
        if (NivelUno())
        {
            aristaActual->datoarista.ModificaMedCer().EscribeTotal(cantidad);
        }
        else
        {
            aristaActual->datoarista.ModificaMedCer(MedCert::MEDICION).EscribeTotal(cantidad);
            aristaActual->datoarista.ModificaMedCer(MedCert::CERTIFICACION).EscribeTotal(cantidad);
        }        
        Actualizar(aristaActual->destino);
    }
}

void Obra::EditarUnidad(int ud)
{
    if (!NivelCero())
    {
        aristaActual->destino->datonodo.EscribeUd(ud);
    }
}

void Obra::EditarUnidad(TEXTO ud)
{
    if (!NivelCero())
    {
        aristaActual->destino->datonodo.EscribeUd(ud);
    }
}

void Obra::EditarNaturaleza (int nat)
{
    if (!NivelCero())
    {
        aristaActual->destino->datonodo.EscribeNaturaleza(nat);
        if (nat==Codificacion::Mano_de_Obra || nat==Codificacion::Maquinaria)
        {
            aristaActual->destino->datonodo.EscribeUd(Unidad::hora);
        }
    }
}

void Obra::EditarCertificacionCant(float cantidad)
{
    /*aristaActual->datoarista.LeeCertificacion().EscribeTotal(cantidad);
    Actualizar(aristaActual->destino);*/
}

void Obra::EditarCertificacionPorc(float porcentaje)
{
    /*float total=(aristaActual->datoarista.LeeMedicion().LeeTotal()*porcentaje)/100;
    aristaActual->datoarista.LeeCertificacion().EscribeTotal(total);
    Actualizar(aristaActual->destino);*/
}

void Obra::EditarLineaMedicion (int fila, int columna, float valor, TEXTO comentario)
{
    qDebug()<<"Estoy en la tabla: "<<selectorMedCer;
    aristaPadre->datoarista.ModificaMedCer(selectorMedCer).EditarCampo (fila, columna, valor, comentario);
    Actualizar(aristaPadre->destino);
}

const Medicion Obra::LeeListaMedicion(int tabla) const
{
    //return aristaPadre->datoarista.LeeMedCer(tabla);
    return aristaActual->datoarista.LeeMedCer(tabla);
}

const float& Obra::LeeTotalMedicion(int tabla) const
{
    return aristaPadre->datoarista.LeeMedCer(tabla).LeeTotal();
}

void Obra::CopiarPartidas(std::list<std::pair<pArista, pNodo> > &listaNodosSeleccionados, const QList<int> &listaIndices)
{
    std::list<std::pair<pArista,pNodo>>listaNodos=G.recorrerHijos(padre);
    auto iterator = listaNodos.begin();
    for (auto elem:listaIndices)
    {
        qDebug()<<"Numero de fila: "<<elem;
        std::advance(iterator,elem);
        listaNodosSeleccionados.push_back(*iterator);
        iterator = listaNodos.begin();
    }
    for (auto elem : listaNodosSeleccionados)
    {
        qDebug()<<elem.second->datonodo.LeeCodigo();
    }
}
void Obra::CopiarPartidas(std::list<std::pair<pArista,pNodo>>&listaNodosSeleccionados, Grafo<datonodo_t,datoarista_t>&grafo)
{
    pNodo nodo = grafo.LeeRaiz();
    std::list<std::pair<pArista,pNodo>>listaNodos=grafo.recorrerHijos(nodo);
    auto iterator = listaNodos.begin();
    while(iterator!=listaNodos.end())
    {
        listaNodosSeleccionados.push_back(*iterator);
        iterator++;
    }
    /*for (auto elem:listaIndices)
    {
        qDebug()<<"Numero de fila: "<<elem;
        std::advance(iterator,elem);
        listaNodosSeleccionados.push_back(*iterator);
        iterator = listaNodos.begin();
    }*/
    for (auto elem : listaNodosSeleccionados)
    {
        qDebug()<<elem.second->datonodo.LeeCodigo();
    }
}

void Obra::Pegar(Grafo<datonodo_t, datoarista_t> grafo)
{
    std::list<std::pair<pArista,pNodo>> lista = grafo.recorrerHijos(grafo.LeeRaiz());
    Pegar(lista);
}

void Obra::Pegar(const std::list<std::pair<pArista, pNodo> > &listaNodosACopiar, bool ultimafila)
{
    pArista A = aristaActual;
    bool NoHayHijos=false;
    if (!padre->adyacente)
    {
        NoHayHijos=true;
    }
    if (padre->adyacente && ultimafila)
    {
        qDebug()<<"Pego al final del todo wey";
        A=A->siguiente;//si estoy en el caso de la ultima fila me posiciono detrás de la aristaActual para copiar despues de ella, no antes
    }
    for (auto elem : listaNodosACopiar)
    {
        G.Copiar(padre,elem.second,elem.first,A);
    }
    std::list<pNodo> lista = G.recorrerNodos();
    for (auto elem : lista)
    {
       if (!mapaNodos.contains(elem->datonodo.LeeCodigo()))
       {
           std::cout<<"Meto en el mapa el codigo: "<< elem->datonodo.LeeCodigo().toStdString()<<" del nodo: "<<elem<<std::endl;
           mapaNodos.insert(elem->datonodo.LeeCodigo(),elem);
       }
    }
    if (NoHayHijos)
    {
        aristaActual=padre->adyacente;
    }
    Actualizar(aristaActual->destino);
    //std::cout<<"Implementando el pegado"<<std::endl;
}

void Obra::cambiarEntreMedYCert(int n)
{
   selectorMedCer = n;
   qDebug()<<"Estoy en la tabla: "<<n;
}

int Obra::verNumCertificaciones()
{
    return Cert.tamanno();
}

bool Obra::HayDescomposicion()
{
    if (aristaActual)
    {
        return aristaActual->destino->adyacente;
    }
    return false;
}

bool Obra::PartidaConDescomposicion(const pArista &A)
{
    if (A)
    {
        return A->destino->adyacente;
    }
    return false;
}

bool Obra::PartidaConMedicion(const pArista& A)
{
    {
        if (A->datoarista.LeeMedicion().hayMedicion())
        {
            return true;
        }
        else
        {
            return false;
        }
        return A->datoarista.LeeMedicion().hayMedicion();
    }
    return false;
}

bool Obra::HayMedicion() const
{
    //if (aristaActual)
    {            
        return aristaPadre->datoarista.LeeMedicion().hayMedicion();
    }   
}

bool Obra::HayMedicionPartidaActual() const
{
    if (aristaActual)
    {
        return aristaActual->datoarista.LeeMedicion().hayMedicion();
    }
    return false;
}

bool Obra::HayCertificacion() const
{
    //return aristaActual->datoarista.LeeCertificacion().hayMedicion();
    return aristaPadre->datoarista.LeeCertificacion().hayMedicion();
}

bool Obra::EsPartidaVacia() const
{
    if (aristaPadre->destino->adyacente==nullptr)
    {
        return true;
    }
    return false;
}

pNodo Obra::ExisteConcepto(const TEXTO &codigo)
{   
    auto it = mapaNodos.find(codigo);
    if (it!=mapaNodos.end())
    {
        return it.value();
    }
    return nullptr;
}

bool Obra::ExisteHermano(const TEXTO &codigo)
{
    pNodo hijo=nullptr;
    std::list<pNodo> lista = G.recorrerNodos();
    for (auto elem:lista)
    {
        if (elem->datonodo.LeeCodigo()==codigo)
        {
            hijo=elem;
        }
    }
    return G.existeHermano(padre,hijo);
}

bool Obra::NivelCero() const
{
    return padre==G.LeeRaiz();
}

bool Obra::NivelUno()
{
    if (pilaAristas.size()>1)
    {
        pArista A = pilaAristas.top();//guardo la arista de la pila
        pilaAristas.pop();
        pArista anterior=pilaAristas.top();
        pilaAristas.push(A);//la vuelvo a meter
        if (anterior->destino==G.LeeRaiz())
        {
            return true;
        }
    }
    return false;
}

bool Obra::NivelUno(pNodo nodo)
{
    std::list<std::pair<pArista,pNodo>>lista = G.recorrerHijos(G.LeeRaiz());
    for (auto elem : lista)
    {
        if (elem.second==nodo)
        {
            return true;
        }
    }
    return false;
}

bool Obra::EsPartida()
{
    return aristaPadre->destino->datonodo.LeeNat()==Codificacion::Partida;
}

const TEXTO Obra::LeeCodigoObra() const
{
    return G.LeeRaiz()->datonodo.LeeCodigo();
}

const TEXTO Obra::LeeCodigoPartida() const
{
    return aristaPadre->destino->datonodo.LeeCodigo();
}

const TEXTO Obra::LeeCodigoActual() const
{
    return aristaActual->destino->datonodo.LeeCodigo();
}

const TEXTO Obra::LeeResumenObra() const
{
    return G.LeeRaiz()->datonodo.LeeResumen();
}

float Obra::LeePrecioObra() const
{
    return G.LeeRaiz()->datonodo.LeeImportePres();
}

const TEXTO Obra::LeeFechaObra() const
{
    return G.LeeRaiz()->datonodo.LeeFecha();
}

void Obra::EscribeCodigoObra(TEXTO codigo)
{
    G.LeeRaiz()->datonodo.EscribeCodigo(codigo);
}

void Obra::EscribeResumenObra(TEXTO resumen)
{
    G.LeeRaiz()->datonodo.EscribeResumen(resumen);
}

void Obra::EscribeRaiz(TEXTO nombreRaiz)
{
    pNodo raiz = ExisteConcepto(nombreRaiz);
    G.escribeRaiz(raiz);
}

pNodo Obra::Padre()
{
    return padre;
}

pArista Obra::AristaPadre()
{
    return aristaPadre;
}

pArista Obra::AristaActual()
{
    return aristaActual;
}

std::list<std::pair<pArista,pNodo>>Obra::LeeDecompuesto()
{
    return G.recorrerHijos(padre);
}

Grafo<datonodo_t,datoarista_t> Obra::GrafoAPartirDeNodo(pNodo nodo)
{
    return G.CrearGrafoAPartirDeNodo(nodo);
}
