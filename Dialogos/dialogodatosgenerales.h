#ifndef DIALOGODATOSGENERALES_H
#define DIALOGODATOSGENERALES_H

#include "ui_dialogodatosgenerales.h"

#include "./Medicionux/include/Obra.h"

#include <QDebug>

class DialogoDatosGenerales : public QDialog, private Ui::DialogoDatosGenerales
{
    Q_OBJECT

public:
    explicit DialogoDatosGenerales(Obra *O, QWidget *parent = 0);
    int LeeCodificacion();


private slots:
    void crearTablaDatosGenerales (int n);
};

#endif // DIALOGODATOSGENERALES_H
