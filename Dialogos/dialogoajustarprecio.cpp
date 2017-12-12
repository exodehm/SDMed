#include "dialogoajustarprecio.h"
#include "ui_dialogoajustarprecio.h"

DialogoAjustarPrecio::DialogoAjustarPrecio(float cantidad, QWidget *parent) :
    cantidadinicial(cantidad), cantidadfinal(cantidad), QDialog(parent), ui(new Ui::DialogoAjustarPrecio)
{
    cantidades[0]=cantidad;
    ui->setupUi(this);
    rx = new QRegExp("[-]{0,1}[0-9]{0,9}[\\,\\.]{1}[0-9]{1,3}");
    ui->editorcantidad->setValidator(new QRegExpValidator(*rx));
    ui->editorporcentaje->setValidator(new QRegExpValidator(*rx));
    ui->editorcantidad->setText(QString::number(cantidadinicial));
    porcentaje=cantidadfinal/cantidadinicial*100;
    ui->editorporcentaje->setText(QString::number(porcentaje));

    QObject::connect(ui->radioButtonCantidad,SIGNAL(clicked(bool)),this,SLOT(ActivarDesactivarCuadros()));
    QObject::connect(ui->radioButtonPorcentaje,SIGNAL(clicked(bool)),this,SLOT(ActivarDesactivarCuadros()));
    QObject::connect(ui->editorcantidad,SIGNAL(textChanged(QString)),this,SLOT(AjustarPorcentaje()));
    QObject::connect(ui->editorporcentaje,SIGNAL(textChanged(QString)),this,SLOT(AjustarCantidad()));
}

DialogoAjustarPrecio::~DialogoAjustarPrecio()
{
    delete ui;
}

void DialogoAjustarPrecio::ActivarDesactivarCuadros()
{
    ui->editorcantidad->setEnabled(ui->radioButtonCantidad->isChecked());
    ui->editorporcentaje->setEnabled(ui->radioButtonPorcentaje->isChecked());
}

void DialogoAjustarPrecio::AjustarCantidad()
{
    if (!ui->editorcantidad->hasFocus())
    {
        QString dato = ui->editorporcentaje->text();
        dato.replace(",",".");
        porcentaje = dato.toFloat();
        cantidadfinal=cantidadinicial*porcentaje/100;
        ui->editorcantidad->setText(QString::number(cantidadfinal));
    }
}

void DialogoAjustarPrecio::AjustarPorcentaje()
{
    if (!ui->editorporcentaje->hasFocus())
    {
        QString dato = ui->editorcantidad->text();
        dato.replace(",",".");
        cantidadfinal=dato.toFloat();
        porcentaje = cantidadfinal/cantidadinicial*100;
        ui->editorporcentaje->setText(QString::number(porcentaje));
    }
}

float* DialogoAjustarPrecio::Cantidad()
{
    cantidades[1]= ui->editorcantidad->text().toFloat();
    return cantidades;
    //return ui->editorcantidad->text().toFloat();
}
