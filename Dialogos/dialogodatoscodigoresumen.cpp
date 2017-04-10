#include "dialogodatoscodigoresumen.h"

DialogoDatosCodigoResumen::DialogoDatosCodigoResumen(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    QRegExpValidator *validador=new QRegExpValidator(QRegExp("[0-9A-Za-z]{1,20}"), lineEditCodigo);
    lineEditCodigo->setValidator(validador);
    connect(lineEditCodigo, SIGNAL(textChanged(const QString&)), this, SLOT(activarBoton(const QString&)));
    connect(lineEditResumen, SIGNAL(textChanged(const QString&)), this, SLOT(activarBoton(const QString&)));
}

QString DialogoDatosCodigoResumen::LeeCodigo()
{
    return lineEditCodigo->text();
}

QString DialogoDatosCodigoResumen::LeeResumen()
{
    return lineEditResumen->text();
}

bool DialogoDatosCodigoResumen::ActivadoCuadroDeDatosGenerales() const
{
    return checkBox->isChecked();
}


void DialogoDatosCodigoResumen::activarBoton(const QString& texto)
{
    if (!lineEditCodigo->text().isEmpty() && !lineEditResumen->text().isEmpty())
    {
        BotonAceptar->setEnabled(true);
        BotonAceptar->setDefault(true);
        BotonCancelar->setDefault(false);
    }
    else
    {
        BotonAceptar->setEnabled(false);
        BotonAceptar->setDefault(false);
        BotonCancelar->setDefault(true);
    }
}

