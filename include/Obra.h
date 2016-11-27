#ifndef OBRA_H
#define OBRA_H

#include <iomanip>
#include <cstring>

#include <QList>
#include <QString>
#include <QStringList>
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
    void CrearPartida(TEXTO Cod, TEXTO Res="", float cantidad=1, float precio=0,int ud=0);
    void CrearPartida (TEXTO CodPadre, float cantidad, TEXTO CodHijo);
    void CrearPartida (TEXTO CodPadre, MedCert med, TEXTO CodHijo);
    void CopiarPartida(TEXTO codigo, float cantidad);
    void BorrarPartida();
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
    const QList<QStringList>&VerActual();
    const QList<QStringList>& VerMedCert();
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
    void escribirPrecio(float precio);  //escribe un precio si no hay descompuesto
    /*********funciones de edicion***********/
    void EditarCodigo (TEXTO codigo);
    void EditarResumen (TEXTO resumen);
    void EditarCantidad (float cantidad);
    void EditarUnidad(int ud);
    void EditarCertificacionCant(float cantidad);
    void EditarCertificacionPorc(float porcentaje);
    void Copiar(const std::pair<pArista,pNodo>& dato);
    void Pegar(std::list<std::pair<pArista,pNodo>>listaNodosACopiar);
    void EditarCodificacion(int n);
    /*****funciones relacionadas con la medicion o certificacion de la partida********/
    void inicializarActual();
    void Medir_O_Certificar();
    void AnadirMedicionCertificacion();
    void BorrarLineasMedicion();
    void borrarTodaMedicionOCertificacion();
    void borrarTodaMedicion();
    void borrarTodaCertificacion();
    void EditarLineaMedicion (int columna, float valor, TEXTO comentario);
    void PosicionarLineaActualMedicion(int fila);
    void avanzarLineaActualMedicion();
    void retrocederLineaActualMedicion();
    void seleccionarLineaMedicion();
    void selecDeselecTodo();
    std::list<TEXTO> copiarMedicion();
    void pegarMedicion(const std::list<TEXTO>&listaMedicion);
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
    /***************************varias***************************/
    bool hayDescomposicion();
    bool hayMedicion() const;
    bool hayCertificacion() const;
    pNodo existeConcepto(const TEXTO& codigo);
    bool existeHermano(TEXTO codigo);
    bool NivelCero() const;
    bool NivelUno() const;
    bool EsPartida();
    /************************Codigo y Resumen de la obra*************/
    const TEXTO LeeCodigoObra() const;
    const TEXTO LeeResumenObra() const;
    const float LeePrecioObra() const;
    const TEXTO LeeFecha() const;
    void EscribeCodigoObra(TEXTO codigo);
    void EscribeResumenObra(TEXTO resumen);
    void EscribeRaiz(TEXTO nombreRaiz);
    /*************************auxiliar crear tabla*********************/
    QStringList RellenaLinea(pNodo nodo, pArista arista);


private:
    Grafo<datonodo_t,datoarista_t> G;
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
    //Listados para tablas;
    QList<QStringList> listadoTablaP;
    QList<QStringList> listadoTablaMC;

};

#endif // OBRA_H
