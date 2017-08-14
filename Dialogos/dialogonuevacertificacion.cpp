#include "dialogonuevacertificacion.h"
#include "ui_dialogonuevacertificacion.h"
#include <QDate>

DialogoNuevaCertificacion::DialogoNuevaCertificacion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogoNuevaCertificacion)
{
    ui->setupUi(this);
    QDate date = ui->calendarWidget->selectedDate();
    dia=date.day();
    mes=date.month();
    anno=date.year();
    ui->comboDia->setCurrentIndex(dia-1);
    ui->comboMes->setCurrentIndex(mes-1);
    ui->comboAnno->setCurrentIndex(anno-2010);

    QObject::connect(ui->comboDia,SIGNAL(currentIndexChanged(int)),this,SLOT(cambiaDia(int)));
    QObject::connect(ui->comboMes,SIGNAL(currentIndexChanged(int)),this,SLOT(cambiaMes(int)));
    QObject::connect(ui->comboAnno,SIGNAL(currentIndexChanged(int)),this,SLOT(cambiaAnno(int)));
    QObject::connect(ui->calendarWidget,SIGNAL(clicked(QDate)),this,SLOT(actualizarCombos(QDate)));
}

DialogoNuevaCertificacion::~DialogoNuevaCertificacion()
{
    delete ui;
}

QString DialogoNuevaCertificacion::LeeFecha()
{
    return ui->calendarWidget->selectedDate().toString("ddMMyyyy");
}

void DialogoNuevaCertificacion::cambiaDia(int d)
{
    int m = ui->calendarWidget->selectedDate().month();
    int y = ui->calendarWidget->selectedDate().year();
    QDate date(y,m,d+1);
    ui->calendarWidget->setSelectedDate(date);
}

void DialogoNuevaCertificacion::cambiaMes(int m)
{
    int d = ui->calendarWidget->selectedDate().day();
    int y = ui->calendarWidget->selectedDate().year();
    QDate date(y,m+1,d);
    ui->calendarWidget->setSelectedDate(date);
}

void DialogoNuevaCertificacion::cambiaAnno(int a)
{
    int d = ui->calendarWidget->selectedDate().day();
    int m = ui->calendarWidget->selectedDate().month();
    QDate date(a+2010,m,d);
    ui->calendarWidget->setSelectedDate(date);
}

void DialogoNuevaCertificacion::actualizarCombos(QDate date)
{
    QString cadena = date.toString("ddMMyyyy");

    int d = cadena.left(2).toInt();
    ui->comboDia->setCurrentIndex(d-1);
    cadena.remove(0,2);
    int m = cadena.left(2).toInt();
    ui->comboMes->setCurrentIndex(m-1);
    cadena.remove(0,2);
    ui->comboAnno->setCurrentIndex(cadena.toInt()-2010);
}
