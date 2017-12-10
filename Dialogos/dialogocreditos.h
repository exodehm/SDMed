#ifndef DIALOGOCREDITOS_H
#define DIALOGOCREDITOS_H

#include <QDialog>

namespace Ui {
class DialogoCreditos;
}

class DialogoCreditos : public QDialog
{
    Q_OBJECT

public:
    explicit DialogoCreditos(QWidget *parent = 0);
    ~DialogoCreditos();

private:
    Ui::DialogoCreditos *ui;
};

#endif // DIALOGOCREDITOS_H
