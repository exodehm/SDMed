
#include "editor.h"

Editor::Editor(QWidget *parent): QMainWindow(parent)
{
	setupUi(this);	
	setupActions();
    this->setWindowFlags(this->windowFlags() & ~Qt::Window); //opcionalmente editor->setWindowFlags(Qt::Widget) ?
	mStatLabel = new QLabel;
	BarraEstado->addPermanentWidget(mStatLabel);	
	updateStats();
    //fuenteActual= QFont("Arial", 10);
	colorFondo = QColor(Qt::yellow);
	colorLetra = QColor(Qt::black);
    //textEdit->setCurrentFont(fuenteActual);
	cursivas=false;
    negrita=false;

    QObject::connect (textEdit, SIGNAL(textChanged()), this, SLOT(updateStats()));
}

QTextEdit &Editor::LeeTexto()
{
    return *textEdit;
}

void Editor::EscribeTexto(const QString& texto)
{
    textEdit->setText(texto);
}

void Editor::setupActions()
{
	connect(action_Quit, SIGNAL(triggered(bool)),qApp, SLOT(quit()));
	
	connect(textEdit, SIGNAL(copyAvailable(bool)),action_Copiar, SLOT(setEnabled(bool)));
	connect(textEdit, SIGNAL(undoAvailable(bool)),action_Undo, SLOT(setEnabled(bool)));
	connect(textEdit, SIGNAL(redoAvailable(bool)),actionRedo, SLOT(setEnabled(bool)));


	connect(actionNegrita, SIGNAL(triggered(bool)),this, SLOT(negritas()));
	connect(actionCursiva, SIGNAL(triggered(bool)),this, SLOT(cursiva()));
	
	connect(action_Copiar, SIGNAL(triggered(bool)),this, SLOT(copy()));
	connect(actionCut, SIGNAL(triggered(bool)),this, SLOT(cut()));
	connect(actionPaste, SIGNAL(triggered(bool)),this, SLOT(paste()));
	
	connect(action_Undo, SIGNAL(triggered(bool)),this, SLOT(undo()));
	connect(actionRedo, SIGNAL(triggered(bool)),this, SLOT(redo()));	

	connect(actionFuente, SIGNAL(triggered(bool)),this, SLOT(definirFuente()));
	connect(actionColor_Letra, SIGNAL(triggered(bool)),this, SLOT(definirColorLetra()));
	connect(actionColor_Fondo, SIGNAL(triggered(bool)),this, SLOT(definirColorFondo()));

	connect(actionJustificar, SIGNAL(triggered(bool)),this, SLOT(Justificar()));
	connect(actionDerecha, SIGNAL(triggered(bool)),this, SLOT(AlinearDerecha()));
	connect(actionIzquierda, SIGNAL(triggered(bool)),this, SLOT(AlinearIzquierda()));
	connect(actionCentrar, SIGNAL(triggered(bool)),this, SLOT(Centrar()));
}

void Editor::negritas()
{
	negrita=!negrita;
	if (negrita)
	{	
		textEdit->setFontWeight(QFont::Bold);		
	}
	else
	{
		textEdit->setFontWeight(QFont::Normal);
	}	
}

void Editor::cursiva()
{
	cursivas=!cursivas;	
	textEdit->setFontItalic(cursivas);	
}

void Editor::undo()
{
	textEdit->document()->undo();
}

void Editor::redo()
{
	textEdit->document()->redo();
}

void Editor::copy()
{
	textEdit->copy();
}

void Editor::cut()
{
	textEdit->cut();
}

void Editor::paste()
{
	textEdit->paste();
}

void Editor::definirFuente()
{
	bool ok;
	fuenteActual = QFontDialog::getFont(&ok, fuenteActual,this);
	if (ok)
	{
		textEdit->setCurrentFont(fuenteActual);
	}
}

void Editor::definirColorLetra()
{
	colorLetra = QColorDialog::getColor(colorLetra, this);
	textEdit->setTextColor(colorLetra);
}

void Editor::definirColorFondo()
{
	colorFondo = QColorDialog::getColor(colorFondo, this);
	textEdit->setTextBackgroundColor(colorFondo);
}

void Editor::Justificar()
{
	textEdit->setAlignment(Qt::AlignJustify);	
}

void Editor::AlinearDerecha()
{
	textEdit->setAlignment(Qt::AlignRight);		
}

void Editor::AlinearIzquierda()
{
	textEdit->setAlignment(Qt::AlignLeft);		
}

void Editor::Centrar()
{
	textEdit->setAlignment(Qt::AlignCenter);	
}

void Editor::updateStats()
{
	QString text = textEdit->document()->toPlainText();
	int chars = text.length();
	text = text.simplified();
	int words = 0;
	words = text.count(" ");
	if (!text.isEmpty())
	{
		words++;
	}
	chars = chars-words+1;
	QString output = tr("Letras:	%1, Palabras: %2").arg(chars).arg(words);
	mStatLabel->setText(output);
}
