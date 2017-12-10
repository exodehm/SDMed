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
    src/Fecha.cpp \
    src/GestorEntradaDatosLineasMedicion.cpp \
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
    Dialogos/dialogocreditos.cpp

HEADERS  += interfazobra.h \
    Editor/editor.h \
    defs.h \
    Calc/include/Calc.h \
    Calc/include/nodocalc.h \
    Calc/include/pila.h \
    include/AbrirGuardar.h \
    include/arista.h \
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
    Dialogos/dialogocreditos.h

FORMS    += \
    Dialogos/dialogosuprimirmedicion.ui \
    Dialogos/dialogoprecio.ui \
    Ui/mainwindow.ui \
    Ui/dialogodatosgenerales.ui \
    Ui/dialogodatoscodigoresumen.ui \
    Ui/dialogonuevacertificacion.ui \
    Editor/editor.ui \
    Dialogos/dialogoabout.ui \
    Dialogos/dialogocreditos.ui

RESOURCES += \
    Editor/iconosEditor.qrc \
    iconos.qrc \
    recursos.qrc

CONFIG +=C++14
