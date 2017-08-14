#ifndef INTERFAZOBRA_H
#define INTERFAZOBRA_H

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

#include "./include/Obra.h"
#include "./include/AbrirGuardar.h"

#include "./Modelos/PrincipalModel.h"
#include "./Modelos/MedCertModel.h"

#include "./Tablas/tablaprincipal.h"
#include "./Tablas/tablamedcert.h"
#include "./Editor/editor.h"

class InterfazObra : public QWidget
{
    Q_OBJECT

public:
    explicit InterfazObra(QString nombrefichero, QWidget *parent = nullptr);
    explicit InterfazObra(QString codigo, QString resumen, QWidget *parent=nullptr);
    ~InterfazObra();

    void GenerarUI();
    void EscribirTexto();
    void GuardarTextoPartida();

public slots:

    Obra* LeeObra();
    void SubirNivel();
    void BajarNivel(QModelIndex indice);
    /*void lineaMas();
    void lineaMenos();
    void PosicionarTablaP();*/
    void PosicionarTablaP(QModelIndex indice);
    void PosicionarTablaM(QModelIndex indice);
    void MostrarDeSegun(int indice);
    void Avanzar();
    void Retroceder();
    void RefrescarVista(QModelIndex indice1, QModelIndex indice2);
    //void ActualizarTablaMedicion(QModelIndex indice1, QModelIndex indice2);
    void CopiarPartidasTablaP();
    void CopiarMedicionTablaM();
    void CopiarPartidas(std::list<std::pair<pArista, pNodo> > &listaNodosCopiarPegar);
    void PegarPartidasTablaP();
    void PegarMedicionTablaM();
    void PegarPartidas(const std::list<std::pair<pArista, pNodo> > &listaNodosCopiarPegar);
    void CopiarMedicionPortapapeles(const QModelIndexList &lista);
    void CopiarPartidasPortapapeles(const QModelIndexList &lista);
    void CopiarMedicion(Medicion& listaMedicionCopiarPegar);
    void PegarMedicion(const Medicion& ListaMedicion);
    void Certificar();
    void CambiarEntreMedicionYCertificacion(int n);
    void GuardarBC3(QString fileName);  

signals:
    void CopiarP();
    void PegarP();
    void CopiarM();
    void PegarM();

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

    QModelIndex *indice;    

    Obra* O;
};

#endif // INTERFAZOBRA_H
