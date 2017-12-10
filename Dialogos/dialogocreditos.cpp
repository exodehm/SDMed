#include "dialogocreditos.h"
#include "ui_dialogocreditos.h"

DialogoCreditos::DialogoCreditos(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogoCreditos)
{
    ui->setupUi(this);
}

DialogoCreditos::~DialogoCreditos()
{
    delete ui;
}
