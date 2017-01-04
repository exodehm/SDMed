#ifndef EDITOR_H
#define EDITOR_H
#include <QMainWindow>
#include <QStatusBar>
#include <QLabel>
#include <QColor>
#include <QColorDialog>
#include <QFont>
#include <QFontDialog>

#include "ui_editor.h"


class QLabel;

class Editor : 	public QMainWindow, private Ui::Editor
{
	Q_OBJECT
	public:
    Editor (QWidget* parent=nullptr);
	//~MainWindow();
    QTextEdit &LeeTexto();
    void EscribeTexto(const QString& texto);

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
	
	private:
	
	QLabel *mStatLabel;
	QFont fuenteActual;
	QColor colorFondo;
	QColor colorLetra;
	bool cursivas;
	bool negrita;
};

#endif
