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
    explicit InterfazObra(QWidget *parent = 0);
    ~InterfazObra();

    void GenerarUI();
    void RefrescarVista();
    void EscribirTexto();

public slots:

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
    void ActualizarTablaMedicion(QModelIndex indice1, QModelIndex indice2);
    void CopiarMedicion();
    void PegarMedicion();
    void GuardarBC3();
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
    QHBoxLayout* botonera;
    QHBoxLayout* lienzoSuperior;
    QHBoxLayout* lienzoIntermedio;
    QHBoxLayout* lienzoInferior;
    QPushButton* botonAvanzar;
    QPushButton* botonRetroceder;
    TablaBase* tablaPrincipal;
    TablaBase* tablaMediciones;
    QComboBox* comboMedCert;

    Editor* editor;

    QModelIndex *indice;    

    Obra* O;
};

#endif // INTERFAZOBRA_H
