#ifndef EDITOR_H
#define EDITOR_H
#include <QMainWindow>
#include <QStatusBar>
#include <QLabel>
#include <QColor>
#include <QColorDialog>
#include <QFont>
#include <QFontDialog>
#include <QFocusEvent>
#include <QDebug>

#include "ui_editor.h"
#include "micustomtextedit.h"

#include "filter.h"

class Filter;


class Editor : 	public QMainWindow, private Ui::Editor
{
    Q_OBJECT
public:
    Editor (QWidget *parent=nullptr);
    QTextEdit &LeeTexto() const;
    QTextEdit* LeeEditor();
    void EscribeTexto(const QString& texto);
    bool HayCambios();
    QString LeeContenido() const;
    QString LeeContenidoConFormato() const;
    void Formatear();

    void focusOutEvent(QFocusEvent* event);

protected:
    void setupActions();

protected slots:

    void negritas();
    void cursiva();
    void undo();
    void redo();
    void copy();
    void cut();
    void paste();
    void definirFuente();
    void definirColorLetra();
    void definirColorFondo();
    void Justificar();
    void AlinearDerecha();
    void AlinearIzquierda();
    void Centrar();
    void updateStats();


signals:
    void GuardaTexto();

private:

    MiCustomTextEdit* textEdit;
    QLabel *mStatLabel;
    QFont fuenteActual;
    QColor colorFondo;
    QColor colorLetra;
    bool cursivas;
    bool negrita;
    Filter* filtro;
};

#endif
