#-------------------------------------------------
#
# Project created by QtCreator 2016-11-04T13:02:01
#
#-------------------------------------------------

QT += core gui

CONFIG += static
CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SDMed
TEMPLATE = app

SOURCES += main.cpp\
    Editor/editor.cpp \
    Modelos/PrincipalModel.cpp \
    Calc/src/Calc.cpp \
    src/Certificacion.cpp \
    src/Concepto.cpp \
    src/Datos.cpp \
    src/Fecha.cpp \
    src/LineaMedicion.cpp \
    src/MedCert.cpp \
    src/Medicion.cpp \
    src/Obra.cpp \
    src/Precio.cpp \
    src/Redondeos.cpp \
    src/Unidades.cpp \
    src/Codificacion.cpp \
    filter.cpp \
    Tablas/tablamedcert.cpp \
    Delegados/delegadocolumnasbloqueadas.cpp \
    Tablas/tablaprincipal.cpp \
    iconos.cpp \
    Delegados/delegadoiconos.cpp \
    Tablas/tablabase.cpp \
    Dialogos/dialogosuprimirmedicion.cpp \
    Dialogos/dialogoprecio.cpp \
    Delegados/delegadobase.cpp \
    mainwindow.cpp \
    Dialogos/dialogodatoscodigoresumen.cpp \
    Dialogos/dialogonuevacertificacion.cpp \
    Modelos/MedCertModel.cpp \
    Undo/undomedicion.cpp \
    Undo/undoeditarprincipal.cpp \
    Editor/micustomtextedit.cpp \
    Delegados/delegadonumerosbase.cpp \
    Delegados/delegadonumerostablaprincipal.cpp \
    Delegados/delegadonumerostablamedcert.cpp \
    Dialogos/dialogoabout.cpp \
    Dialogos/dialogocreditos.cpp \
    Dialogos/dialogoajustarprecio.cpp \
    Undo/undoajustarpresupuesto.cpp \
    Dialogos/dialogolicencia.cpp \
    instancia.cpp \
    Ficheros/abrirguardarseg.cpp \
    Ficheros/abrirguardarbc3.cpp \
    Ficheros/abrirguardar.cpp \
    Modelos/TreeModel.cpp \
    Modelos/treeitem.cpp \
    Delegados/delegadoarbol.cpp \
    Tablas/vistaarbol.cpp

HEADERS  += \
    Editor/editor.h \
    defs.h \
    Calc/include/Calc.h \
    Calc/include/nodocalc.h \
    Calc/include/pila.h \
    include/arista.h \
    include/Certificacion.h \
    include/Concepto.h \
    include/Datos.h \
    include/definiciones.h \
    include/Fecha.h \
    include/Grafo.h \
    include/Importar.h \
    include/LineaMedicion.h \
    include/MedCert.h \
    include/Medicion.h \
    include/nodo.h \
    include/Obra.h \
    include/Precio.h \
    include/Redondeos.h \
    include/Unidades.h \    
    include/Codificacion.h \
    filter.h \
    Tablas/tablamedcert.h \
    Delegados/delegadocolumnasbloqueadas.h \
    Tablas/tablaprincipal.h \
    iconos.h \
    Delegados/delegadoiconos.h \
    Tablas/tablabase.h \
    Dialogos/dialogosuprimirmedicion.h \
    Dialogos/dialogoprecio.h \
    Delegados/delegadobase.h \
    mainwindow.h \
    Dialogos/dialogodatoscodigoresumen.h \
    Modelos/PrincipalModel.h \
    Dialogos/dialogonuevacertificacion.h \
    Modelos/MedCertModel.h \
    Undo/undomedicion.h \
    Undo/undoeditarprincipal.h \
    Editor/micustomtextedit.h \
    Delegados/delegadonumerosbase.h \
    Delegados/delegadonumerostablaprincipal.h \
    Delegados/delegadonumerostablamedcert.h \
    Dialogos/dialogoabout.h \
    Dialogos/dialogocreditos.h \
    Dialogos/dialogoajustarprecio.h \
    Undo/undoajustarpresupuesto.h \
    Dialogos/dialogolicencia.h \
    instancia.h \
    Ficheros/abrirguardarseg.h \
    Ficheros/abrirguardarbc3.h \
    Ficheros/abrirguardar.h \
    Modelos/TreeModel.h \
    Modelos/treeitem.h \
    Delegados/delegadoarbol.h \
    Tablas/vistaarbol.h

FORMS    += \
    Dialogos/dialogosuprimirmedicion.ui \
    Dialogos/dialogoprecio.ui \
    Ui/mainwindow.ui \
    Ui/dialogodatosgenerales.ui \
    Ui/dialogodatoscodigoresumen.ui \
    Ui/dialogonuevacertificacion.ui \
    Editor/editor.ui \
    Dialogos/dialogoabout.ui \
    Dialogos/dialogocreditos.ui \
    Dialogos/dialogoajustarprecio.ui \
    Dialogos/dialogolicencia.ui

RESOURCES += \
    Editor/iconosEditor.qrc \
    iconos.qrc \
    recursos.qrc

CONFIG +=C++14

DISTFILES += \
    estilo.qss

