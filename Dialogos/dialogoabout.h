#ifndef DIALOGOABOUT_H
#define DIALOGOABOUT_H

#include <QDialog>

#include "./Dialogos/dialogocreditos.h"
#include "./Dialogos/dialogolicencia.h"

namespace Ui {
class DialogoAbout;
}

class DialogoAbout : public QDialog
{
    Q_OBJECT

public:
    explicit DialogoAbout(QWidget *parent = 0);
    ~DialogoAbout();

private slots:
    void VerCreditos();
    void VerLicencia();

private:
    Ui::DialogoAbout *ui;
};

#endif // DIALOGOABOUT_H
