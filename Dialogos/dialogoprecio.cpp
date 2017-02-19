#include "dialogoprecio.h"
#include "ui_dialogoprecio.h"

DialogoPrecio::DialogoPrecio(QString titulo, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogoPrecio)
{
    ui->setupUi(this);
    setWindowTitle(titulo);
}

DialogoPrecio::~DialogoPrecio()
{
    delete ui;
}

int DialogoPrecio::Respuesta()
{
    if (ui->radioButton_Suprimir->isChecked())
    {
        return 1;
    }
    else if (ui->radioButton_Bloquear->isChecked())
    {
        return 2;
    }
    else if(ui->radioButton_Ajustar->isChecked())
    {
        return 3;
    }
    return 0;
}
