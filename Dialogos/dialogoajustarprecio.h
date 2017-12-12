#ifndef DIALOGOAJUSTARPRECIO_H
#define DIALOGOAJUSTARPRECIO_H

#include <QRegExp>
#include <QRegExpValidator>

#include <QDialog>

namespace Ui {
class DialogoAjustarPrecio;
}

class DialogoAjustarPrecio : public QDialog
{
    Q_OBJECT

public:
    explicit DialogoAjustarPrecio(float cantidad, QWidget *parent = 0);
    ~DialogoAjustarPrecio();
    float *Cantidad();

private slots:
    void ActivarDesactivarCuadros();
    void AjustarCantidad();
    void AjustarPorcentaje();

private:
    Ui::DialogoAjustarPrecio *ui;
    QRegExp* rx;

    float cantidadinicial, cantidadfinal, porcentaje;
    float cantidades[2];
};

#endif // DIALOGOAJUSTARPRECIO_H
