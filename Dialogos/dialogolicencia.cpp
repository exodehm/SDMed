#include "dialogolicencia.h"
#include "ui_dialogolicencia.h"

DialogoLicencia::DialogoLicencia(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogoLicencia)
{
    ui->setupUi(this);    
}

DialogoLicencia::~DialogoLicencia()
{
    delete ui;
}
