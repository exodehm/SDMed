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
    Delegados/delegadosparcialessubtotales.cpp \
    Delegados/delegadoeditormediciones.cpp \
    Delegados/delegadocolumnasbloqueadas.cpp \
    Delegados/delegadomedicionesestandar.cpp \
    Tablas/tablaprincipal.cpp \
    iconos.cpp \
    Delegados/delegadoiconos.cpp \
    Tablas/tablabase.cpp \
    Dialogos/dialogosuprimirmedicion.cpp \
    Dialogos/dialogoprecio.cpp \
    Delegados/delegadobase.cpp \
    Delegados/delegadoeditornumeros.cpp \
    mainwindow.cpp \
    Dialogos/dialogodatoscodigoresumen.cpp \
    Dialogos/dialogonuevacertificacion.cpp \
    Modelos/MedCertModel.cpp \
    Undo/undomedicion.cpp \
    Undo/undomover.cpp \
    Undo/undoeditartextopartida.cpp \
    Undo/undoprincipal.cpp \
    Undo/undoeditarprecio.cpp \
    Undo/undoeditarcantidad.cpp \
    Undo/undoeditarresumen.cpp

HEADERS  += interfazobra.h \
    Editor/editor.h \
    Editor/ui_editor.h \    
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
    Delegados/delegadosparcialessubtotales.h \
    Delegados/delegadoeditormediciones.h \
    Delegados/delegadocolumnasbloqueadas.h \
    Delegados/delegadomedicionesestandar.h \
    Tablas/tablaprincipal.h \
    iconos.h \
    Delegados/delegadoiconos.h \
    Tablas/tablabase.h \
    Dialogos/dialogosuprimirmedicion.h \
    Dialogos/dialogoprecio.h \
    Delegados/delegadobase.h \
    Delegados/delegadoeditornumeros.h \
    mainwindow.h \
    Dialogos/dialogodatoscodigoresumen.h \
    Modelos/PrincipalModel.h \
    Dialogos/dialogonuevacertificacion.h \
    Modelos/MedCertModel.h \
    Undo/undomedicion.h \
    Undo/undomover.h \
    Undo/undoeditartextopartida.h \
    Undo/undoprincipal.h \
    Undo/undoeditarprecio.h \
    Undo/undoeditarcantidad.h \
    Undo/undoeditarresumen.h

FORMS    += \
    Dialogos/dialogosuprimirmedicion.ui \
    Dialogos/dialogoprecio.ui \
    Ui/mainwindow.ui \
    Ui/dialogodatosgenerales.ui \
    Ui/dialogodatoscodigoresumen.ui \
    Ui/dialogonuevacertificacion.ui

RESOURCES += \
    Editor/iconosEditor.qrc \
    iconos.qrc \
    recursos.qrc

CONFIG +=C++14
