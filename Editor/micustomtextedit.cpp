#include "micustomtextedit.h"

MiCustomTextEdit::MiCustomTextEdit(QWidget *parent):QTextEdit(parent)
{
    //Formatear();
}

void MiCustomTextEdit::Formatear()
{
    font.setFamily(QStringLiteral("URW Gothic L"));
    font.setPointSize(10);
    font.setBold(false);
    font.setItalic(false);
    font.setUnderline(false);
    font.setWeight(50);
    font.setStrikeOut(false);
    setFont(font);
}

QFont &MiCustomTextEdit::Fuente()
{
    return font;
}

void MiCustomTextEdit::focusOutEvent(QFocusEvent* event)
{
    qDebug()<<"Focus out de miscustomtextedit: "<<event->type();
    Formatear();
    emit GuardaTexto();
}

void MiCustomTextEdit::focusInEvent(QFocusEvent* event)
{
    qDebug()<<"Focus in: "<<event->type();
    emit EscribeTexto(document()->toPlainText());
}
