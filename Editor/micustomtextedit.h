#ifndef MICUSTOMTEXTEDIT_H
#define MICUSTOMTEXTEDIT_H

#include <QTextEdit>
#include <QFocusEvent>
#include <QDebug>

//#include "Editor/editor.h"

//se crea esta clase con el unico objetivo de redefinir las funciones virtuales focusOutEvent y focusInEvent
//tambien se añaden las señales que emitiran cuando se activen estos eventos
//se añade mediante codigo al editor creado con QDesigner
class editor;

class MiCustomTextEdit : public QTextEdit
{
    Q_OBJECT
public:
    MiCustomTextEdit(QWidget *parent=nullptr);
    QFont& Fuente();

    void Formatear();

    void focusOutEvent(QFocusEvent* event);
    void focusInEvent(QFocusEvent* event);
    void focusChanged(QWidget* old, QWidget* now);

signals:
    void GuardaTexto();
    void EscribeTexto(QString texto);

private:
    QFont font;
};

#endif // MICUSTOMTEXTEDIT_H
