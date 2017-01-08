#ifndef INTERFAZOBRA_H
#define INTERFAZOBRA_H

#include <QWidget>
#include <QHeaderView>
#include <QKeyEvent>

#include "./include/Obra.h"
#include "./include/AbrirGuardar.h"
#include "./Modelos/PrincipalModel.h"
#include "./Modelos/MedicionesModel.h"
#include "./Delegados/delegadoeditormediciones.h"
#include "filter.h"

namespace Ui {
class InterfazObra;
}

class InterfazObra : public QWidget
{
    Q_OBJECT

public:
    explicit InterfazObra(QWidget *parent = 0);
    ~InterfazObra();

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
    Ui::InterfazObra *ui;    
    QHeaderView* cabeceraTablaP;
    PrincipalModel* modeloTablaP;
    MedicionesModel* modeloTablaMC;
    //DelegadoEditorMediciones* dlgEM;

    Filter *filter;

    QModelIndex *indice;
    //bool eventFilter(QObject * watched, QEvent * e);

    Obra* O;
};

#endif // INTERFAZOBRA_H
