#ifndef OBRA_H
#define OBRA_H

#include <cstring>

#include "Grafo.h"
#include "Concepto.h"
#include "MedCert.h"
#include "Redondeos.h"
#include "Certificacion.h"
#include "Datos.h"


struct TipoDato
{
    TEXTO datoTexto;
    float datoNumero;
    int datoInt;
    int etipodato;
};

struct Dato
{
    TipoDato dato;
    int color;    
};

class Obra
{
public:

    typedef std::list<std::pair<pNodo,pArista>> ListaNodosAristas;
    typedef std::list<std::pair<pArista,pNodo>> ListaAristasNodos;

    //Constructor
    Obra();
    Obra(TEXTO Cod, TEXTO Res, int ud=0, int CuadroDePrecios=1);
    Obra(Concepto conceptoRaiz);
    /** Default destructor */
    ~Obra();
    //constructor copia
    Obra(const Obra& origen);
    //operador =
    Obra& operator=(const Obra& G);
    /*********************/
    void IniciarObra (Concepto conceptoRaiz);
    void CrearPartida(TEXTO Cod, TEXTO Res="", float cantidad=1, float precio=0,int ud=0, int nat = Codificacion::Sin_clasificar);
    void CrearPartida (TEXTO CodPadre, float cantidad, TEXTO CodHijo);
    void CrearPartida (TEXTO CodPadre, MedCert med, TEXTO CodHijo);
    void CrearPartida(TEXTO CodigoHijo, int posicion);
    pNodo DefinirConcepto(TEXTO Cod, TEXTO Res="", float precio=0, int ud=0, int nat = Codificacion::Sin_clasificar);
    void CopiarPartida(TEXTO codigo, float cantidad);
    void BorrarPartida();
    void BorrarPartida(pNodo N);
    void SuprimirDescomposicion();
    void DuplicarPartida(TEXTO codigo);    
    /*****moverse por la obra**********/
    void BajarNivel();
    //void SubirNivel();
    int SubirNivel();
    void Siguiente();
    void Anterior();
    void HijoSiguiente();
    void HijoAnterior();
    void IrAInicio();
    void PosicionarAristaActual(int pos);
    /******funciones para mostrar datos*******/    
    void VerNodos();
    void VerArbol();
    void VerRama();
    TEXTO VerTexto();
    /*********funciones de calculo**************/
    void SumarHijos(pNodo n);
    void Actualizar(pNodo n);
    void Recalcular();
    void AjustarPrecio(float nuevoprecio);
    float Redondear(float numero, int precision);
    /**********funciones de precio*************/
    void BloquearPrecio (float precio); //escribe un precio bloqueado y no considera el descompuesto
    void DesbloquearPrecio();           //anula el bloqueo y suma el descompuesto
    bool esPrecioBloqueado();           //consulta para saber si la partida activa tiene el precio bloqueado
    bool esPrecioBloqueado(pArista A);           //consulta para saber si un precio esta bloqueado
    void EditarPrecio(float precio);    //escribe un precio si no hay descompuesto
    void EditarCostesIndirectos(float coste);
    float LeePrecio();
    /*********funciones de edicion***********/
    void EditarCodigo (TEXTO codigo);
    void EditarResumen (TEXTO resumen);
    void EditarTexto (TEXTO textopartida);
    void EditarCantidad (float cantidad);
    void EditarUnidad(int ud);
    void EditarUnidad(TEXTO ud);
    void EditarNaturaleza (int nat);
    void EditarCertificacionCant(float cantidad);
    void EditarCertificacionPorc(float porcentaje);
    void CopiarPartidas(ListaAristasNodos&listaNodosSeleccionados, const QList<int> &listaIndices);    
    void Pegar(const ListaAristasNodos& listaNodosACopiar, bool ultimafila = false);
    void InsertarPartidas(const ListaAristasNodos& listaNodosACopiar, QList<int>indices);
    void EditarCodificacion(int n);
    /*****funciones relacionadas con la edicion de la medicion o certificacion de la partida********/
    void InsertarLineasVaciasMedicion(int tabla, int pos, int num);
    void inicializarActual();
    void Medir_O_Certificar();
    void AnadirMedicionCertificacion();
    void BorrarLineasMedicion(int pos, int numLineas=1);
    void borrarTodaMedicionOCertificacion();
    void borrarTodaMedicion();
    void borrarTodaCertificacion();
    void EditarLineaMedicion (int fila, int columna, float valor, TEXTO comentario);
    void PosicionarLineaActualMedicion(int fila);
    void avanzarLineaActualMedicion();
    void retrocederLineaActualMedicion();
    void seleccionarLineaMedicion();
    void selecDeselecTodo();
    void CopiarMedicion(Medicion& ListaMedicion, const QList<int> &listaIndices);
    void PegarMedicion(int fila, const Medicion& ListaMedicion);
    void PegarMedicion(int fila, const Medicion& ListaMedicion, pArista A);
    void bloquearColumna(int nColumna, float fValor);
    void Desbloquear();
    void Certificar(const Medicion& listaParaCertificar);
    bool anadirCertificacion(TEXTO tFecha);
    void borrarCertificacion(int n);
    int verNumCertificaciones();
    int CertificacionActiva();
    void EstablecerCertificacionActual(int n);
    void cambiarFechaCertificacion(std::string fecha);
    const Medicion LeeListaMedicion(int tabla=MedCert::MEDICION) const;
    const float& LeeTotalMedicion(int tabla=MedCert::MEDICION) const;
    /**********seleccionar entre medicion y certificacion********/
    void cambiarEntreMedYCert(int n);
    /***************************varias de consulta********************/
    bool HayDescomposicion(pArista A) const;
    bool HayDescomposicionPartidaActual() const;
    bool HayDescomposicionPadre() const;
    bool HayMedicion(pArista A) const;
    bool HayMedicionPartidaActual() const;
    bool HayMedicionPadre() const;
    bool HayCertificacion() const;    
    bool EsPartidaVacia() const;
    pNodo ExisteConcepto(const TEXTO& codigo);
    bool ExisteHermano(const TEXTO& codigo);
    bool NivelCero() const;
    bool NivelUno();
    bool NivelUno(pNodo nodo);
    bool EsPartida();
    /************************Codigo, Resumen y Fecha de la obra*************/
    const TEXTO LeeCodigoObra() const;
    const TEXTO LeeCodigoPartida() const;
    const TEXTO LeeCodigoActual() const;
    const TEXTO LeeResumenObra() const;    
    float LeePrecioObra() const;
    const TEXTO LeeFechaObra() const;
    void EscribeCodigoObra(TEXTO codigo);
    void EscribeResumenObra(TEXTO resumen);
    void EscribeRaiz(TEXTO nombreRaiz);

    /***********acceso a nodos y aristas**************/
    pNodo Padre();
    pArista AristaPadre();
    pArista AristaActual();
    std::list<std::list<Dato>>LeeDescompuesto();
    std::list<Dato> RellenaDatoLinea(pNodo nodo, pArista arista);
    std::stack<pArista> LeePilaAristas();
    void DefinePilaAristas(const std::stack<pArista> &pila);
    void DefineAristaPadre(const pArista& ap);
    void DefineNodoPadre(const pNodo& np);
    void DefineAristaActual(const pArista& aa);
    /***********varias***********************************/
    pNodo GrafoAPartirDeNodo(pNodo nodo);
    std::list<pNodo> ListaConceptos();
    void InsertarMapa(TEXTO codigo, pNodo nodo);
    const Grafo<datonodo_t,datoarista_t>& LeeGrafo() const
    {
        return G;
    }    

private:
    Grafo<datonodo_t,datoarista_t> G;
    QHash<TEXTO,pNodo>mapaNodos;
    //elementos auxiliares para moverme por el grafo
    pNodo padre;
    pArista aristaPadre;
    pArista aristaActual;
    std::stack <pArista>pilaAristas;
    //objeto usado para asignar la naturaleza del concepto
    Codificacion codificacion;  
    //miembros para la certificacion
    Certificacion Cert;
    int selectorMedCer;
    //redondeos de la obra
    Coeficientes Redondeos;
    float CI;//Costes Indirectos

    //auxiliar para copiado de partidas
    QList<pNodo>ListaN;

    friend class AbrirGuardarBC3;    
};

#endif // OBRA_H
