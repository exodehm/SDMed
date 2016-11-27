#-------------------------------------------------
#
# Project created by QtCreator 2016-11-04T13:02:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PruebasInterfazObra
TEMPLATE = app


SOURCES += main.cpp\
        interfazobra.cpp \
    Editor/editor.cpp \
    Modelos/PrincipalModel.cpp \
    Calc/src/Calc.cpp \
    src/AbrirGuardar.cpp \
    src/AbrirGuardarBC3.cpp \
    src/Certificacion.cpp \
    src/Concepto.cpp \
    src/Datos.cpp \
    src/Exportar.cpp \
    src/Fecha.cpp \
    src/GestorEntradaDatosLineasMedicion.cpp \
    src/LineaMedicion.cpp \
    src/MedCert.cpp \
    src/Medicion.cpp \
    src/Obra.cpp \
    src/Precio.cpp \
    src/Redondeos.cpp \
    src/Unidades.cpp \
    Modelos/MedicionesModel.cpp \
    src/Codificacion.cpp

HEADERS  += interfazobra.h \
    Editor/editor.h \
    Editor/ui_editor.h \
    Modelos/PrincipalModel.h \
    defs.h \
    Calc/include/Calc.h \
    Calc/include/nodo.h \
    Calc/include/nodocalc.h \
    Calc/include/pila.h \
    include/AbrirGuardar.h \
    include/arista.h \
    include/Caracteres.h \
    include/Certificacion.h \
    include/Concepto.h \
    include/Datos.h \
    include/definiciones.h \
    include/Fecha.h \
    include/GestorEntradaDatosLineasMedicion.h \
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
    Modelos/MedicionesModel.h \
    include/Codificacion.h

FORMS    += interfazobra.ui

RESOURCES += \
    Editor/iconosEditor.qrc

CONFIG +=C++14
