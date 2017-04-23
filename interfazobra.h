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
    void CopiarMedicion();
    void CopiarPartida();
    void PegarMedicion();
    void GuardarBC3(QString fileName);
    /*void InsertarFilaVacia();
    void InsertarDelante();
    void Eliminar(const QList<int> &Lista);
    void EliminarFilasVacias();
    void EditarNaturaleza(int nat);
    void EditarCodigoResumen(int, QString texto);
    void EditarCantidadPrecio(int columna, float cantidad);
    void EditarCampoLineaMedicion(int columna, float valor, QString texto);
    void GuardarTextoPartida();
    void CambiarMedCert(int indice);*/

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
