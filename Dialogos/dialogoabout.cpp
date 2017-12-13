#include "dialogoabout.h"
#include "ui_dialogoabout.h"

DialogoAbout::DialogoAbout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogoAbout)
{
    ui->setupUi(this);
    ui->label->setOpenExternalLinks(true);
    QObject::connect(ui->botonCreditos,SIGNAL(clicked(bool)),this,SLOT(VerCreditos()));
    QObject::connect(ui->botonLicencia,SIGNAL(clicked(bool)),this,SLOT(VerLicencia()));
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

void DialogoAbout::VerLicencia()
{
    DialogoLicencia* d = new DialogoLicencia(this);
    d->show();
}
