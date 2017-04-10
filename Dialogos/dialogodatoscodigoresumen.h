#ifndef DIALOGODATOSCODIGORESUMEN_H
#define DIALOGODATOSCODIGORESUMEN_H

#include <QRegExpValidator>
#include "ui_dialogodatoscodigoresumen.h"

class DialogoDatosCodigoResumen : public QDialog, private Ui::DialogoDatosCodigoResumen
{
    Q_OBJECT

public:
    explicit DialogoDatosCodigoResumen(QWidget *parent = nullptr);

    QString LeeCodigo();
    QString LeeResumen();
    bool ActivadoCuadroDeDatosGenerales() const;

private slots:
   void activarBoton(const QString& texto);  
};

#endif // DIALOGODATOSCODIGORESUMEN_H
