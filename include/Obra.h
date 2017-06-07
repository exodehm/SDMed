#ifndef OBRA_H
#define OBRA_H

#include <iomanip>
#include <cstring>

#include <QList>
#include <QString>
#include <QStringList>
#include <QHash>
#include <QDebug>

#include "Grafo.h"
#include "Concepto.h"
#include "MedCert.h"
#include "Redondeos.h"
#include "Certificacion.h"
#include "Datos.h"

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
    void BorrarPartidas();
    void BorrarPartida(pNodo N);
    void SuprimirDescomposicion();
    void DuplicarPartida(TEXTO codigo);    
    /*****moverse por la obra**********/
    void BajarNivel();
    void SubirNivel();
    void Siguiente();
    void Anterior();
    void HijoSiguiente();
    void HijoAnterior();
    void IrAInicio();
    void PosicionarAristaActual(int pos);
    /******funciones para mostrar datos*******/
    void MostrarHijos();    
    void VerNodos();
    void VerArbol();
    void VerRama();
    TEXTO VerTexto();
    /*********funciones de calculo**************/
    void SumarHijos(pNodo n);
    void Actualizar(pNodo n);
    void Recalcular();
    void AjustarPrecio(float nuevoprecio);
    /**********funciones de precio*************/
    void BloquearPrecio (float precio); //escribe un precio bloqueado y no considera el descompuesto
    void DesbloquearPrecio();           //anula el bloqueo y suma el descompuesto
    bool esPrecioBloqueado();           //consulta para saber si un precio esta bloqueado
    void EditarPrecio(float precio);  //escribe un precio si no hay descompuesto
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
    void CopiarPartidas(std::list<std::pair<pArista,pNodo>>&listaNodosSeleccionados, const QList<int> &listaIndices);
    void Pegar(const std::list<std::pair<pArista,pNodo>>&listaNodosACopiar, bool ultimafila = false);
    void EditarCodificacion(int n);
    /*****funciones relacionadas con la medicion o certificacion de la partida********/
    void InsertarLineasVaciasMedicion(int pos, int num);
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
    void bloquearColumna(int nColumna, float fValor);
    void Desbloquear();
    void Certificar();
    void anadirCertificacion();
    void borrarCertificacion(int n);
    int verNumCertificaciones();
    int CertificacionActiva();
    void SeleccionarCertificacion(int n);
    void cambiarFechaCertificacion(std::string fecha);
    const float& LeeTotalMedicion() const;
    /**********seleccionar entre medicion y certificacion********/
    void cambiarEntreMedYCert();
    /***************************varias de consulta********************/
    bool hayDescomposicion();
    bool hayMedicion() const;
    bool hayMedicionPartidaActual() const;
    bool hayCertificacion() const;
    bool EsPartidaVacia() const;
    pNodo existeConcepto(const TEXTO& codigo);
    bool existeHermano(const TEXTO& codigo);
    bool NivelCero() const;
    bool NivelUno();
    bool NivelUno(pNodo nodo);
    bool EsPartida();
    /************************Codigo y Resumen de la obra*************/
    const TEXTO LeeCodigoObra() const;
    const TEXTO LeeCodigoPartida() const;
    const TEXTO LeeCodigoActual() const;
    const TEXTO LeeResumenObra() const;
    float LeePrecioObra() const;
    const TEXTO LeeFecha() const;
    void EscribeCodigoObra(TEXTO codigo);
    void EscribeResumenObra(TEXTO resumen);
    void EscribeRaiz(TEXTO nombreRaiz);

    /***********acceso a nodos y aristas**************/
    pNodo Padre();
    pArista AristaPadre();
    pArista AristaActual();
    std::list<std::pair<pArista,pNodo>>LeeDecompuesto();


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
    //lista auxiliar para el copiado de conceptos
    std::list<std::pair<pArista,pNodo>>nodosParaCopiar;
    //elementos auxiliares para el copiapega de mediciones
    std::list<LineaMedicion*> listaAuxiliar;//lista para almacenar lineas de medicion
    //miembros para la certificacion
    Certificacion Cert;
    int selectorMedCer;
    //redondeos de la obra
    Coeficientes Redondeos;
    float CI;//Costes Indirectos

    friend class AbrirGuardarBC3;    
};

#endif // OBRA_H
