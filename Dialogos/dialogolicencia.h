#ifndef DIALOGOLICENCIA_H
#define DIALOGOLICENCIA_H

#include <QDialog>

namespace Ui {
class DialogoLicencia;
}

class DialogoLicencia : public QDialog
{
    Q_OBJECT

public:
    explicit DialogoLicencia(QWidget *parent = 0);
    ~DialogoLicencia();

private:
    Ui::DialogoLicencia *ui;
};

#endif // DIALOGOLICENCIA_H
