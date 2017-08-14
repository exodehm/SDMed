#ifndef DIALOGONUEVACERTIFICACION_H
#define DIALOGONUEVACERTIFICACION_H

#include <QDialog>
#include <QDate>

namespace Ui {
class DialogoNuevaCertificacion;
}

class DialogoNuevaCertificacion : public QDialog
{
    Q_OBJECT

public:
    explicit DialogoNuevaCertificacion(QWidget *parent = 0);
    ~DialogoNuevaCertificacion();
    QString LeeFecha();

private slots:
    void cambiaDia(int d);
    void cambiaMes(int m);
    void cambiaAnno(int a);
    void actualizarCombos(QDate date);

private:
    Ui::DialogoNuevaCertificacion *ui;
    int dia,mes,anno;
};

#endif // DIALOGONUEVACERTIFICACION_H
