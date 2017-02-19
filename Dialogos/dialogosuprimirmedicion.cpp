#include "dialogosuprimirmedicion.h"
#include "ui_dialogosuprimirmedicion.h"

DialogoSuprimirMedicion::DialogoSuprimirMedicion(QString titulo, QWidget *parent) :
    QDialog(parent), ui(new Ui::DialogoSuprimirMedicion)
{
    ui->setupUi(this);
    ui->radioButton_No->setChecked(true);
    setWindowTitle(titulo);
}

DialogoSuprimirMedicion::~DialogoSuprimirMedicion()
{
    delete ui;
}

bool DialogoSuprimirMedicion::Suprimir() const
{
    return ui->radioButton_Suprimir->isChecked();
}
