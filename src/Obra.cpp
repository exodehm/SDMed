#include "../include/Obra.h"

Obra::Obra():G(),selectorMedCer(MedCert::MEDICION),Redondeos() {}

Obra::Obra(TEXTO Cod, TEXTO Res, int ud, int CuadroDePrecios):codificacion(CuadroDePrecios),
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
    padre=G->LeeRaiz();
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
        padre=G->LeeRaiz();
        aristaPadre=new arista<MedCert,Concepto>(1);//el concepto raiz en principio tiene siempre el valor 1 (una unidad de obra)
        aristaPadre->destino=padre;
        pilaAristas.push(aristaPadre);
        aristaActual=0;
    }
    return *this;
}

Obra::~Obra()
{
    delete G;
}

void Obra::IniciarObra (Concepto conceptoRaiz)
{
    //pNodo primero=new nodo<Concepto,MedCert> (conceptoRaiz);
    //pArista aristaInicial=new arista<MedCert,Concepto>(1);
    //G.Insertar(primero,primero, aristaInicial);
    G = new Grafo<datonodo_t,datoarista_t>(conceptoRaiz);
    //mapaNodos.insert(primero->datonodo.LeeCodigo(),primero);
    mapaNodos.insert(G->LeeRaiz()->datonodo.LeeCodigo(),G->LeeRaiz());
    //padre=primero;
    padre = G->LeeRaiz();
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
    G->Insertar(padre, hijo, relacion);
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
    G->Insertar(padre,nuevoNodo,nuevaArista);
    aristaActual = G->hallarArista(padre,nuevoNodo);
    //Y actualizo el grafo partiendo del nodo insertado
    if (aristaActual)
    {
        Actualizar(aristaActual->destino);
    }
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
    G->Insertar(padre, nuevoNodo, A, posicion);
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
    G->Insertar(padre,Nuevo, aux);
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
    padre = G->LeeRaiz();
    aristaPadre->destino = padre;
    aristaActual = padre->adyacente;
}

void Obra::IrTope()
{
    while (padre!=G->LeeRaiz())
    {
        SubirNivel();
    }
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
        ListaAristasNodos lista = G->recorrerHijos(padre);
        for (auto elem : lista)
        {
            medicion = elem.first->datoarista.LeeMedicion().LeeTotal();
            certificacion = elem.first->datoarista.LeeCertificacion().LeeTotal();
            precio = elem.second->datonodo.LeeImportePres();           
            if (NivelUno(padre))
            {
                precio*=CI;
            }
            //qDebug()<<"Cantidad: "<<medicion<<"* Precio: "<<precio;
            if (elem.second->datonodo.LeeCodigo().contains("%")) //si es un porcentaje
            {
                elem.second->datonodo.EscribeImportePres(sumapres/100.0);
            }
            sumapres+=Redondear(precio * medicion,3);
            sumacert+=Redondear(precio * certificacion,3);
            //qDebug()<<"sumapres: "<<sumapres;
            //rqDebug()<<"sumacert: "<<sumacert;
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
        G->borrarNodos(aristaActual);
    }
    //mapaNodos.erase(aristaActual->destino->datonodo.LeeCodigo());
    std::list<pNodo> lista = G->recorrerNodos();
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
        G->borrarNodos(auxiliar);
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
    if (HayMedicionPadre())
    {
        aristaPadre->datoarista.ModificaMedCer(selectorMedCer).BorrarMedicion();
        Actualizar(aristaPadre->destino);
    }
}

void Obra::borrarTodaMedicion()
{
    if (HayMedicionPadre())
    {
        aristaPadre->datoarista.ModificaMedCer(MedCert::MEDICION).BorrarMedicion();
        Actualizar(aristaPadre->destino);
    }
}

void Obra::borrarTodaCertificacion()
{
    if (HayMedicionPadre())
    {
        aristaPadre->datoarista.ModificaMedCer(MedCert::CERTIFICACION).BorrarMedicion();
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
    std::list<pNodo> lista = G->recorrerNodos();
    for (auto elem:lista)
    {
        std::cout<<elem->datonodo.LeeCodigo().toStdString()<<"-";
    }
    std::cout<<std::endl;
}

std::list<std::pair<pNodo, int>>& Obra::VerArbol()
{
    /*std::list<std::pair<pNodo,int>>lista = G.recorrerGrafoConNiveles(G.LeeRaiz());
    std::cout<<G.LeeRaiz()->datonodo.LeeCodigo().toStdString()<<std::endl;
    for (auto elem : lista)
    {
        std::cout<<elem.second<<std::setw(elem.second*2);
        std::cout<<elem.first->datonodo.LeeCodigo().toStdString()<<std::endl;
    }*/
    return G->recorrerGrafoConNiveles(G->LeeRaiz());
}

void Obra::VerRama()
{
    std::list<std::pair<pNodo,int>>lista = G->recorrerGrafoConNiveles(padre);
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
    qDebug()<<"Metodo actualizar!!!";
    if (!nodoactual)
    {
        padre->datonodo.EscribeImportePres(0);
        nodoactual=padre;
    }
    if (nodoactual)
    {
        qDebug()<<"Actualizando desde el nodo: "<<nodoactual->datonodo.LeeCodigo();
    }
    std::list<pNodo>lista = G->recorrerAncestrosOrdenado(nodoactual);
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
    float precioActual=G->LeeRaiz()->datonodo.LeeImportePres();
    std::cout<<"Ajustar el precio: "<<precioActual<<" a: "<<nuevoprecio<<std::endl;
    float factorDeAjuste=nuevoprecio/precioActual;
    std::cout<<"Factor de correción: "<<factorDeAjuste<<std::endl;
    std::list<pNodo> listahojas = G->listaHojas();

    std::cout<<"Las hojas son: ";
    for(auto elem:listahojas)
    {
        //std::cout<<*Iterador->datonodo->LeeCodigo()<<"-";
        qDebug()<<elem->datonodo.LeeCodigo();
    }
    //multiplicando las hojas x el factor de corrección
    for(auto Iterador = listahojas.cbegin(); Iterador != listahojas.cend(); Iterador++)
    {
        qDebug()<<"Precio anterior: "<<(*Iterador)->datonodo.LeeImportePres();
        (*Iterador)->datonodo.EscribeImportePres((*Iterador)->datonodo.LeeImportePres()*factorDeAjuste);
        qDebug()<<"Precio nuevo: "<<(*Iterador)->datonodo.LeeImportePres();
    }
    //y actualizo
    for(auto Iterador = listahojas.cbegin(); Iterador != listahojas.cend(); Iterador++)
    {
        Actualizar(*Iterador);
    }
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
    if (aristaActual)
    {
        return aristaActual->destino->datonodo.esPrecioBloqueado();
    }
    return false;
}

bool Obra::esPrecioBloqueado(pArista A)
{
    if(A)
    {
        return A->destino->datonodo.esPrecioBloqueado();
    }
    return false;
}

void Obra::EditarPrecio(float precio)
{
    qDebug()<<"Editar el precio en el nodo: "<<aristaActual->destino->datonodo.LeeCodigo();
    aristaActual->destino->datonodo.EscribePrecio(precio);
    Actualizar(aristaActual->destino);
}

float Obra::LeePrecio()
{
    if (aristaActual)
    {
        return aristaActual->destino->datonodo.LeeImportePres();
    }
    return false;
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
    //qDebug()<<"Estoy en la tabla: "<<selectorMedCer;
    aristaPadre->datoarista.ModificaMedCer(selectorMedCer).EditarCampo (fila, columna, valor, comentario);
    Actualizar(aristaPadre->destino);
}

const Medicion Obra::LeeListaMedicion(pArista A, int tabla) const
{
    return A->datoarista.LeeMedCer(tabla);
    //return aristaPadre->datoarista.LeeMedCer(tabla);
    //return aristaActual->datoarista.LeeMedCer(tabla);
}

const float& Obra::LeeTotalMedicion(int tabla) const
{
    return aristaPadre->datoarista.LeeMedCer(tabla).LeeTotal();
}

void Obra::CopiarPartidas(ListaAristasNodos &listaNodosSeleccionados, const QList<int> &listaIndices)
{
    std::list<std::pair<pArista,pNodo>>listaNodos=G->recorrerHijos(padre);
    auto iterator = listaNodos.begin();
    ListaN.clear();
    for (auto elem:listaIndices)
    {
        std::advance(iterator,elem);
        qDebug()<<"Numero de fila: "<<elem;
        listaNodosSeleccionados.push_back(*iterator);
        ListaN.push_back(GrafoAPartirDeNodo(iterator->second));
        qDebug()<<"Code: "<<iterator->second->datonodo.LeeCodigo();
        iterator = listaNodos.begin();
    }
    for (auto elem : ListaN)
    {
        qDebug()<<"Hijos de "<<elem->datonodo.LeeCodigo()<<" :";
        std::list<std::pair<pNodo,int>>listaB=G->recorrerGrafoConNiveles(elem);
        for (auto elem2:listaB)
        {
            qDebug()<<"Nodo:"<<elem2.first->datonodo.LeeCodigo();
        }
    }
}

void Obra::Pegar(const ListaAristasNodos &listaNodosACopiar, bool ultimafila)
{
    pArista A = aristaActual;
    bool NoHayHijos=false;
    if (!padre->adyacente)
    {
        NoHayHijos=true;
    }
    if (padre->adyacente && ultimafila)
    {
        //qDebug()<<"Pego al final";
        A=A->siguiente;//si estoy en el caso de la ultima fila me posiciono detrás de la aristaActual para copiar despues de ella, no antes
    }
    for (auto elem : listaNodosACopiar)
    {
        qDebug()<<"Nodos a copiar: "<<elem.second->datonodo.LeeCodigo();
        G->Copiar(padre,elem.second,elem.first,A);
    }
    std::list<pNodo> lista = G->recorrerNodos();
    for (auto elem : lista)
    {
       if (!mapaNodos.contains(elem->datonodo.LeeCodigo()))
       {
           //std::cout<<"Meto en el mapa el codigo: "<< elem->datonodo.LeeCodigo().toStdString()<<" del nodo: "<<elem<<std::endl;
           mapaNodos.insert(elem->datonodo.LeeCodigo(),elem);
       }
    }
    if (NoHayHijos)
    {
        aristaActual=padre->adyacente;
    }
    Actualizar(aristaActual->destino);
}

void Obra::InsertarPartidas(const ListaAristasNodos &listaNodosACopiar, QList<int>indices)
{
    pArista A = padre->adyacente;
    int i=0;
    for (auto elem : listaNodosACopiar)
    {
        qDebug()<<"Nodos a copiar: "<<elem.second->datonodo.LeeCodigo();
        qDebug()<<"Indice: "<<i<<" valor: "<<indices.at(i);
        for (int j=0;j<indices.at(i);j++)
        {
            A=A->siguiente;
        }
        G->Copiar(padre,elem.second,elem.first,A);
        i++;
        A = padre->adyacente;
    }
    std::list<pNodo> lista = G->recorrerNodos();
    for (auto elem : lista)
    {
       if (!mapaNodos.contains(elem->datonodo.LeeCodigo()))
       {
           std::cout<<"Meto en el mapa el codigo: "<< elem->datonodo.LeeCodigo().toStdString()<<" del nodo: "<<elem<<std::endl;
           mapaNodos.insert(elem->datonodo.LeeCodigo(),elem);
       }
    }
    aristaActual=padre->adyacente;
    if (aristaActual->destino)
    {
        qDebug()<<"AristaActual->destino";
        qDebug()<<"AristaActual->destino: "<<aristaActual->destino;
        Actualizar(aristaActual->destino);
    }
    qDebug()<<"Fin de la funcion de Insertar Partidas";
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

bool Obra::HayDescomposicion(pArista A) const
{
    if (A)
    {
        return A->destino->adyacente;
    }
    return false;
}

bool Obra::HayDescomposicionPartidaActual() const
{
    if (aristaActual)
    {
        return aristaActual->destino->adyacente;
    }
    return false;
}

bool Obra::HayDescomposicionPadre() const
{
    if (aristaPadre)
    {
        return aristaPadre->destino->adyacente;
    }
    return false;
}

bool Obra::HayMedicion(pArista A) const
{
    if (A)
    {            
        return A->datoarista.LeeMedicion().hayMedicion();
    }
    return false;
}

bool Obra::HayMedicionPartidaActual() const
{
    if (aristaActual)
    {
        return aristaActual->datoarista.LeeMedicion().hayMedicion();
    }
    return false;
}

bool Obra::HayMedicionPadre() const
{
    if (aristaPadre)
    {
        return aristaPadre->datoarista.LeeMedicion().hayMedicion();
    }
    return false;
}

bool Obra::HayCertificacion() const
{
    //return aristaActual->datoarista.LeeCertificacion().hayMedicion();
    if (aristaPadre)
    {
        return aristaPadre->datoarista.LeeCertificacion().hayMedicion();
    }
    return false;
}

bool Obra::EsPartidaVacia() const
{
    if (aristaPadre && aristaPadre->destino->adyacente==nullptr)
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
    std::list<pNodo> lista = G->recorrerNodos();
    for (auto elem:lista)
    {
        if (elem->datonodo.LeeCodigo()==codigo)
        {
            hijo=elem;
        }
    }
    return G->existeHermano(padre,hijo);
}

bool Obra::NivelCero() const
{
    return padre==G->LeeRaiz();
}

bool Obra::NivelUno()
{
    if (pilaAristas.size()>1)
    {
        pArista A = pilaAristas.top();//guardo la arista de la pila
        pilaAristas.pop();
        pArista anterior=pilaAristas.top();
        pilaAristas.push(A);//la vuelvo a meter
        if (anterior->destino==G->LeeRaiz())
        {
            return true;
        }
    }
    return false;
}

bool Obra::NivelUno(pNodo nodo)
{
    std::list<std::pair<pArista,pNodo>>lista = G->recorrerHijos(G->LeeRaiz());
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
    if (aristaPadre)
    {
        return aristaPadre->destino->datonodo.LeeNat()==Codificacion::Partida;
    }
    return false;
}

const TEXTO Obra::LeeCodigoObra() const
{
    return G->LeeRaiz()->datonodo.LeeCodigo();
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
    return G->LeeRaiz()->datonodo.LeeResumen();
}

float Obra::LeePrecioObra() const
{
    return G->LeeRaiz()->datonodo.LeeImportePres();
}

const TEXTO Obra::LeeFechaObra() const
{
    return G->LeeRaiz()->datonodo.LeeFecha();
}

void Obra::EscribeCodigoObra(TEXTO codigo)
{
    G->LeeRaiz()->datonodo.EscribeCodigo(codigo);
}

void Obra::EscribeResumenObra(TEXTO resumen)
{
    G->LeeRaiz()->datonodo.EscribeResumen(resumen);
}

void Obra::EscribeRaiz(TEXTO nombreRaiz)
{
    pNodo raiz = ExisteConcepto(nombreRaiz);
    G->escribeRaiz(raiz);
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

/*std::list<std::pair<pArista,pNodo>>Obra::LeeDecompuesto()
{
    return G.recorrerHijos(padre);
}*/

std::list<std::list<Dato>> Obra::LeeDescompuesto()
{
    std::list<std::list<Dato>>toReturn;
    //padre
    toReturn.push_back(RellenaDatoLinea(padre,AristaPadre()));
    //hijos
    std::list<std::pair<pArista,pNodo>>listaHijos = G->recorrerHijos(padre);
    for (auto it=listaHijos.begin();it!=listaHijos.end();++it)
    {
        toReturn.push_back(RellenaDatoLinea(it->second,it->first));
    }
    return toReturn;
}

std::list<Dato> Obra::RellenaDatoLinea(pNodo nodo, pArista arista)
{
    std::list<Dato>toReturn;
    //codigo
    Dato codigo;    
    codigo.dato.datoTexto=nodo->datonodo.LeeCodigo();
    codigo.dato.etipodato=datocelda::TEXTO;
    codigo.color = color::NORMAL;
    toReturn.push_back(codigo);
    //naturaleza
    Dato naturaleza;
    naturaleza.dato.datoNumero = nodo->datonodo.LeeNat();
    naturaleza.dato.etipodato = datocelda::INT;
    naturaleza.color = color::NORMAL;
    toReturn.push_back(naturaleza);
    //Unidad
    Dato unidad;
    unidad.dato.datoTexto=nodo->datonodo.LeeUd();
    unidad.dato.etipodato = datocelda::TEXTO;
    unidad.color=color::NORMAL;    
    toReturn.push_back(unidad);
    //resumen
    Dato resumen;
    resumen.dato.datoTexto=nodo->datonodo.LeeResumen();
    resumen.dato.etipodato = datocelda::TEXTO;
    resumen.color=color::NORMAL;    
    toReturn.push_back(resumen);
    //medicion
    Dato medicion;
    medicion.dato.datoNumero = arista->datoarista.LeeMedicion().LeeTotal();
    medicion.dato.etipodato = datocelda::NUMERO;
    HayMedicion(arista)
            ?medicion.color = color::DESCOMPUESTO
            :medicion.color = color::NORMAL;
    toReturn.push_back(medicion);
    //certificacion
    Dato certificacion;
    certificacion.dato.datoNumero = arista->datoarista.LeeCertificacion().LeeTotal();
    certificacion.dato.etipodato = datocelda::NUMERO;
    HayMedicion(arista)//HACER FUNCION DE HAYMEDICION!!!!!!!!!!
            ?certificacion.color = color::DESCOMPUESTO
            :certificacion.color = color::NORMAL;
    toReturn.push_back(certificacion);
    //porcentaje certificado
    Dato porcentaje;
    porcentaje.dato.datoNumero = arista->datoarista.LeeCertificacion().LeeTotal()/arista->datoarista.LeeMedicion().LeeTotal()*100;
    porcentaje.dato.etipodato = datocelda::NUMERO;
    porcentaje.color= color::DESCOMPUESTO;
    toReturn.push_back(porcentaje);
    //precio medicion
    Dato preciomed;
    preciomed.dato.datoNumero = nodo->datonodo.LeeImportePres();
    preciomed.dato.etipodato = datocelda::NUMERO;
    if (esPrecioBloqueado(arista))
    {
        preciomed.color = color::BLOQUEADO;
    }
    else
    {
        if (HayDescomposicion(arista))
        {
            preciomed.color = color::DESCOMPUESTO;
        }
        else
        {
            preciomed.color = color::NORMAL;
        }
    }
    toReturn.push_back(preciomed);
    //precio certificacion
    Dato preciocert;
    preciocert.dato.datoNumero = nodo->datonodo.LeeImporteCert();
    preciocert.dato.etipodato = datocelda::NUMERO;
    preciocert.color=color::NORMAL;    
    toReturn.push_back(preciocert);
    //importe presupuesto
    Dato importepres;
    importepres.dato.datoNumero = nodo->datonodo.LeeImportePres()==0
            ? nodo->datonodo.LeeImportePres()
            : nodo->datonodo.LeeImportePres()*arista->datoarista.LeeMedicion().LeeTotal();
    importepres.dato.etipodato = datocelda::NUMERO;
    importepres.color=color::NORMAL;
    toReturn.push_back(importepres);
    //importe certificacion
    Dato importecert;
    importecert.dato.datoNumero = nodo->datonodo.LeeImporteCert()==0
            ? nodo->datonodo.LeeImporteCert()
            : nodo->datonodo.LeeImporteCert()*arista->datoarista.LeeCertificacion().LeeTotal();
    importecert.dato.etipodato = datocelda::NUMERO;
    importecert.color=color::NORMAL;
    toReturn.push_back(importecert);
    return toReturn;
}

std::stack<pArista> Obra::LeePilaAristas()
{
    //qDebug()<<"Codigo es: "<<pilaAristas.top()->destino->datonodo.LeeCodigo();
    return pilaAristas;
}

void Obra::Posicionar(const std::stack<pArista> &pila, int fila)
{
    pilaAristas = pila;
    aristaPadre=pilaAristas.top();
    padre=aristaPadre->destino;
    aristaActual = padre->adyacente;
    for (int i=0;i<fila;i++)
    {
        aristaActual=aristaActual->siguiente;
        if (aristaActual)
        {
            qDebug()<<"Me pongo en: "<<aristaActual->destino->datonodo.LeeCodigo();
        }
    }
    if (aristaPadre)
        qDebug()<<"Arista padre: "<<aristaPadre;
    if (aristaPadre)
        qDebug()<<"Nodo padre: "<<aristaPadre->destino->datonodo.LeeCodigo();
    if (aristaActual)
    {
        qDebug()<<"Arista actual: "<<aristaActual;
        qDebug()<<"Arista actual->destino: "<<aristaActual->destino->datonodo.LeeCodigo();
    }
    qDebug()<<"Tamaño de la pila: "<<pilaAristas.size();
}

pNodo Obra::GrafoAPartirDeNodo(pNodo nodo)
{
    return G->CrearGrafoAPartirDeNodo(nodo);
}

std::list<pNodo> Obra::ListaConceptos()
{
    return G->recorrerNodos();
}

void Obra::InsertarMapa(TEXTO codigo, pNodo nodo)
{
    mapaNodos.insert(codigo,nodo);
}
