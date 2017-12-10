#include "dialogoabout.h"
#include "ui_dialogoabout.h"

DialogoAbout::DialogoAbout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogoAbout)
{
    ui->setupUi(this);
    QObject::connect(ui->botonCreditos,SIGNAL(clicked(bool)),this,SLOT(VerCreditos()));
}

DialogoAbout::~DialogoAbout()
{
    delete ui;
}

void DialogoAbout::VerCreditos()
{
    DialogoCreditos* d = new DialogoCreditos(this);
    d->show();
}
