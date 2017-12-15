#ifndef INSTANCIA_H
#define INSTANCIA_H

#include <QWidget>
#include <QHeaderView>
#include <QKeyEvent>
#include <QClipboard>
#include <QMimeData>
#include <QTextStream>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSplitter>
#include <QPushButton>
#include <QTabWidget>
#include <QUndoStack>

#include "./include/Obra.h"
#include "./Ficheros/abrirguardar.h"
#include "./Ficheros/abrirguardarbc3.h"
#include "./Ficheros/abrirguardarseg.h"

#include "./Modelos/PrincipalModel.h"
#include "./Modelos/MedCertModel.h"

#include "./Tablas/tablaprincipal.h"
#include "./Tablas/tablamedcert.h"
#include "./Editor/editor.h"

#include "./Undo/undoajustarpresupuesto.h"

#include "filter.h"

class Instancia : public QWidget
{
    Q_OBJECT

public:
    explicit Instancia(QString nombrefichero, QWidget *parent = nullptr);
    explicit Instancia(QString codigo, QString resumen, QWidget *parent=nullptr);
    ~Instancia();

    void IniciarObra();
    void GenerarUI();
    void EscribirTexto();    
    TEXTO TextoPartidaInicial();

    PrincipalModel* ModeloTablaPrincipal();
    TablaBase* LeeTablaPrincipal();

    QUndoStack* Pila();
    void Mover(int tipomovimiento);
    void AjustarPresupuesto(float cantidades[2]);

    int TipoFichero(TEXTO nombrefichero);

public slots:

    Obra* LeeObra();
    void SubirNivel();
    void BajarNivel();
    /*void Avanzar();
    void Retroceder();*/
    /*void lineaMas();
    void lineaMenos();
    void PosicionarTablaP();*/
    void PosicionarTablaP(QModelIndex indice);
    void PosicionarTablaM(QModelIndex indice);
    void MostrarDeSegun(int indice);    
    void Undo();
    void Redo();
    void RefrescarVista();
    //void ActualizarTablaMedicion(QModelIndex indice1, QModelIndex indice2);
    void CopiarPartidasTablaP();
    void CopiarMedicionTablaM();
    void CopiarPartidas(std::list<std::pair<pArista, pNodo> > &listaNodosCopiarPegar);
    void PegarPartidasTablaP();
    void PegarMedicionTablaM();
    void PegarPartidas(const Obra::ListaAristasNodos &listaNodosCopiarPegar);
    void CopiarMedicionPortapapeles(const QModelIndexList &lista);
    void CopiarPartidasPortapapeles(const QModelIndexList &lista);
    void CopiarMedicion(Medicion& listaMedicionCopiarPegar);
    void PegarMedicion(const Medicion& ListaMedicion);
    void Certificar();
    void CambiarEntreMedicionYCertificacion(int n);
    void GuardarBC3(QString filename);
    void GuardarSEG(QString filename);
    void ActivarDesactivarUndoRedo(int indice);    
    void GuardarTextoPartidaInicial();
    void GuardarTextoPartida();

signals:
    void CopiarP();
    void PegarP();
    void CopiarM();
    void PegarM();
    void ActivarBoton(int);

private:
    QHeaderView* cabeceraTablaP;
    PrincipalModel* modeloTablaP;
    MedCertModel* modeloTablaMed;
    MedCertModel* modeloTablaCert;

    QVBoxLayout* lienzoGlobal;
    QVBoxLayout* lienzoSuperior;
    QWidget* widgetSuperior;

    QSplitter* separadorPrincipal;

    QTabWidget* separadorTablasMedicion;

    TablaBase* tablaPrincipal;
    TablaBase* tablaMediciones;
    TablaBase* tablaCertificaciones;
    Editor* editor;

    QModelIndex indiceActual;

    QUndoStack* pila;

    Obra* O;
    TEXTO textoPartidaInicial;
};

#endif // INSTANCIA_H
