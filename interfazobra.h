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

#include "./include/Obra.h"
#include "./include/AbrirGuardar.h"
#include "./Modelos/PrincipalModel.h"
#include "./Modelos/MedicionesModel.h"
//#include "./Tablas/tablabase.h"
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
    void CopiarPartidas(std::list<std::pair<pArista, pNodo> > &listaNodosCopiarPegar);
    void PegarPartidasTablaP();
    void PegarPartidas(std::list<std::pair<pArista, pNodo> > &listaNodosCopiarPegar);
    void CopiarMedicion();
    void PegarMedicion();
    void GuardarBC3(QString fileName);  

signals:
    void CopiarP();
    void PegarP();

private:
    QHeaderView* cabeceraTablaP;
    PrincipalModel* modeloTablaP;
    MedicionesModel* modeloTablaMC;

    QVBoxLayout* lienzoGlobal;
    QVBoxLayout* lienzoSuperior;
    QWidget* widgetSuperior;

    QSplitter* separador;

    TablaBase* tablaPrincipal;
    TablaBase* tablaMediciones;    

    Editor* editor;

    QModelIndex *indice;    

    Obra* O;
};

#endif // INTERFAZOBRA_H
