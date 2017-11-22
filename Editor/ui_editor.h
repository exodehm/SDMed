
/********************************************************************************
** Form generated from reading UI file 'editor.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITOR_H
#define UI_EDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Editor
{
public:
    QAction *action_Quit;
    QAction *action_Undo;
    QAction *action_Copiar;
    QAction *actionCut;
    QAction *actionPaste;
    QAction *actionInfo;
    QAction *actionRedo;
    QAction *actionFuente;
    QAction *actionColor_Letra;
    QAction *actionColor_Fondo;
    QAction *actionJustificar;
    QAction *actionDerecha;
    QAction *actionIzquierda;
    QAction *actionCentrar;
    QAction *actionNegrita;
    QAction *actionCursiva;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QTextEdit *textEdit;
    QStatusBar *BarraEstado;
    QToolBar *BarraHerramientas;

    void setupUi(QMainWindow *Editor)
    {
        if (Editor->objectName().isEmpty())
            Editor->setObjectName(QStringLiteral("Editor"));
        Editor->setEnabled(true);
        Editor->resize(582, 414);
        action_Quit = new QAction(Editor);
        action_Quit->setObjectName(QStringLiteral("action_Quit"));
        action_Undo = new QAction(Editor);
        action_Undo->setObjectName(QStringLiteral("action_Undo"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/dibujos/iconos/backward.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Undo->setIcon(icon);
        action_Copiar = new QAction(Editor);
        action_Copiar->setObjectName(QStringLiteral("action_Copiar"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/dibujos/iconos/copy.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Copiar->setIcon(icon1);
        actionCut = new QAction(Editor);
        actionCut->setObjectName(QStringLiteral("actionCut"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/dibujos/iconos/cut.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCut->setIcon(icon2);
        actionPaste = new QAction(Editor);
        actionPaste->setObjectName(QStringLiteral("actionPaste"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/dibujos/iconos/paste.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPaste->setIcon(icon3);
        actionInfo = new QAction(Editor);
        actionInfo->setObjectName(QStringLiteral("actionInfo"));
        actionRedo = new QAction(Editor);
        actionRedo->setObjectName(QStringLiteral("actionRedo"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/dibujos/iconos/forward.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRedo->setIcon(icon4);
        actionFuente = new QAction(Editor);
        actionFuente->setObjectName(QStringLiteral("actionFuente"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/dibujos/iconos/fuente.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionFuente->setIcon(icon5);
        actionColor_Letra = new QAction(Editor);
        actionColor_Letra->setObjectName(QStringLiteral("actionColor_Letra"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/dibujos/iconos/color_letra.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionColor_Letra->setIcon(icon6);
        actionColor_Fondo = new QAction(Editor);
        actionColor_Fondo->setObjectName(QStringLiteral("actionColor_Fondo"));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/dibujos/iconos/color_fondo.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionColor_Fondo->setIcon(icon7);
        actionJustificar = new QAction(Editor);
        actionJustificar->setObjectName(QStringLiteral("actionJustificar"));
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/dibujos/iconos/justificar.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionJustificar->setIcon(icon8);
        actionDerecha = new QAction(Editor);
        actionDerecha->setObjectName(QStringLiteral("actionDerecha"));
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/dibujos/iconos/alinear_derecha.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDerecha->setIcon(icon9);
        actionIzquierda = new QAction(Editor);
        actionIzquierda->setObjectName(QStringLiteral("actionIzquierda"));
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/dibujos/iconos/alinear_izquierda.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionIzquierda->setIcon(icon10);
        actionCentrar = new QAction(Editor);
        actionCentrar->setObjectName(QStringLiteral("actionCentrar"));
        QIcon icon11;
        icon11.addFile(QStringLiteral(":/dibujos/iconos/centrado.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCentrar->setIcon(icon11);
        actionNegrita = new QAction(Editor);
        actionNegrita->setObjectName(QStringLiteral("actionNegrita"));
        QIcon icon12;
        icon12.addFile(QStringLiteral(":/dibujos/iconos/negrita.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNegrita->setIcon(icon12);
        actionCursiva = new QAction(Editor);
        actionCursiva->setObjectName(QStringLiteral("actionCursiva"));
        QIcon icon13;
        icon13.addFile(QStringLiteral(":/dibujos/iconos/cursiva.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCursiva->setIcon(icon13);
        centralwidget = new QWidget(Editor);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));

        horizontalLayout->addWidget(textEdit);

        Editor->setCentralWidget(centralwidget);
        BarraEstado = new QStatusBar(Editor);
        BarraEstado->setObjectName(QStringLiteral("BarraEstado"));
        Editor->setStatusBar(BarraEstado);
        BarraHerramientas = new QToolBar(Editor);
        BarraHerramientas->setObjectName(QStringLiteral("BarraHerramientas"));
        Editor->addToolBar(Qt::TopToolBarArea, BarraHerramientas);

        BarraHerramientas->addAction(actionNegrita);
        BarraHerramientas->addAction(actionCursiva);
        BarraHerramientas->addSeparator();
        BarraHerramientas->addAction(action_Copiar);
        BarraHerramientas->addAction(actionCut);
        BarraHerramientas->addAction(actionPaste);
        BarraHerramientas->addSeparator();
        BarraHerramientas->addAction(action_Undo);
        BarraHerramientas->addAction(actionRedo);
        BarraHerramientas->addSeparator();
        BarraHerramientas->addAction(actionFuente);
        BarraHerramientas->addAction(actionColor_Letra);
        BarraHerramientas->addAction(actionColor_Fondo);
        BarraHerramientas->addSeparator();
        BarraHerramientas->addAction(actionJustificar);
        BarraHerramientas->addAction(actionDerecha);
        BarraHerramientas->addAction(actionIzquierda);
        BarraHerramientas->addAction(actionCentrar);

        retranslateUi(Editor);

        QMetaObject::connectSlotsByName(Editor);
    } // setupUi

    void retranslateUi(QMainWindow *Editor)
    {
        Editor->setWindowTitle(QApplication::translate("Editor", "Texto", 0));
        action_Quit->setText(QApplication::translate("Editor", "&Quit", 0));
        action_Quit->setShortcut(QApplication::translate("Editor", "Ctrl+Q", 0));
        action_Undo->setText(QApplication::translate("Editor", "&Undo", 0));
        //action_Undo->setShortcut(QApplication::translate("Editor", "Ctrl+Z", 0));
        action_Copiar->setText(QApplication::translate("Editor", "Copy", 0));
        //action_Copiar->setShortcut(QApplication::translate("Editor", "Ctrl+C", 0));
        actionCut->setText(QApplication::translate("Editor", "Cut", 0));
        //actionCut->setShortcut(QApplication::translate("Editor", "Ctrl+X", 0));
        actionPaste->setText(QApplication::translate("Editor", "Paste", 0));
        //actionPaste->setShortcut(QApplication::translate("Editor", "Ctrl+V", 0));
        actionInfo->setText(QApplication::translate("Editor", "Info", 0));
        actionRedo->setText(QApplication::translate("Editor", "Redo", 0));
        //actionRedo->setShortcut(QApplication::translate("Editor", "Ctrl+Shift+Z", 0));
        actionFuente->setText(QApplication::translate("Editor", "Fuente", 0));
        actionColor_Letra->setText(QApplication::translate("Editor", "Color Letra", 0));
        actionColor_Fondo->setText(QApplication::translate("Editor", "Color Fondo", 0));
        actionJustificar->setText(QApplication::translate("Editor", "Justificar", 0));
        actionDerecha->setText(QApplication::translate("Editor", "Derecha", 0));
        actionIzquierda->setText(QApplication::translate("Editor", "Izquierda", 0));
        actionCentrar->setText(QApplication::translate("Editor", "Centrar", 0));
        actionNegrita->setText(QApplication::translate("Editor", "Negrita", 0));
        actionCursiva->setText(QApplication::translate("Editor", "Cursiva", 0));
        textEdit->setHtml(QApplication::translate("Editor", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans';\"><br /></p></body></html>", 0));
        BarraHerramientas->setWindowTitle(QApplication::translate("Editor", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class Editor: public Ui_Editor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITOR_H
