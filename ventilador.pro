QT       += core gui
QT       += serialport sql multimedia printsupport
QT       += websockets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
LIBS += -lwiringPi

SOURCES += \
    consultas.cpp \
    consultasdb.cpp \
    main.cpp \
    mainwindow.cpp \
    monitor.cpp \
    pantallas/calibraciones/uicalcontrol.cpp \
    pantallas/calibraciones/uicalibraciones.cpp \
    pantallas/calibraciones/uicalotros.cpp \
    pantallas/calibraciones/uicalsensores.cpp \
    pantallas/calibraciones/uicalteclado.cpp \
    pantallas/modos/uimodopcmv.cpp \
    pantallas/modos/uimodopcpap.cpp \
    pantallas/modos/uimodopsimv.cpp \
    pantallas/modos/uimodovcmv.cpp \
    pantallas/modos/uimodovcpap.cpp \
    pantallas/modos/uimodovsimv.cpp \
    pantallas/uialarmas.cpp \
    pantallas/uicalibrar.cpp \
    pantallas/uiconfigdatetime.cpp \
    pantallas/uiconfigmodo.cpp \
    pantallas/uiconfiguracion.cpp \
    pantallas/uieventos.cpp \
    pantallas/uiinfosistema.cpp \
    signos/widgetsigno2.cpp \
    signos/widgetsigno3.cpp \
    tarjetas/senpresion.cpp \
    tarjetas/teclado.cpp \
    tarjetas/ventilador.cpp \
    utilidades/alarmaaudled.cpp \
    utilidades/alarmaqw.cpp \
    utilidades/alarmasx.cpp \
    utilidades/formulas.cpp \
    utilidades/gpio.cpp \
    utilidades/infoalarma.cpp \
    utilidades/logutils.cpp \
    utilidades/myswitch.cpp \
    utilidades/qcustomplot.cpp \
    utilidades/qroundprogressbar.cpp \
    utilidades/qroundprogressbaralarm.cpp \
    utilidades/qroundprogressbarconfig.cpp \
    utilidades/reloj.cpp \
    utilidades/serverws.cpp \
    utilidades/temperatura.cpp \
    utilidades/tramas/tramaalarmas.cpp \
    utilidades/tramas/tramapcmv.cpp \
    utilidades/tramas/tramapcpap.cpp \
    utilidades/tramas/tramapsimv.cpp \
    utilidades/tramas/tramas.cpp \
    utilidades/tramas/tramavcmv.cpp \
    utilidades/tramas/tramavcpap.cpp \
    utilidades/tramas/tramavsimv.cpp \
    utilidades/uiqwidgetconfigreloj.cpp \
    utilidades/uiqwidgetmenugrafica.cpp \
    utilidades/ventanaaviso.cpp \
    utilidades/ventanaavisotest.cpp \
    utilidades/ventanacalibrar.cpp \
    utilidades/ventanaconfigpi.cpp \
    utilidades/ventanaconfirmacion.cpp \
    utilidades/ventanainfo.cpp \
    utilidades/ventanainoperante.cpp \
    utilidades/ventanainsfuga.cpp \
    utilidades/ventanainsoxi.cpp \
    utilidades/ventanamenu.cpp \
    utilidades/ventanapruebas.cpp \
    utilidades/widgetgrafica.cpp \
    utilidades/widgetgraficalazo.cpp \
    utilidades/widgetparametro.cpp \
    utilidades/widgetsignobar.cpp \
    utilidades/widgetsignobarconfig.cpp

HEADERS += \
    consultas.h \
    consultasdb.h \
    mainwindow.h \
    monitor.h \
    pantallas/calibraciones/uicalcontrol.h \
    pantallas/calibraciones/uicalibraciones.h \
    pantallas/calibraciones/uicalotros.h \
    pantallas/calibraciones/uicalsensores.h \
    pantallas/calibraciones/uicalteclado.h \
    pantallas/modos/uimodopcmv.h \
    pantallas/modos/uimodopcpap.h \
    pantallas/modos/uimodopsimv.h \
    pantallas/modos/uimodovcmv.h \
    pantallas/modos/uimodovcpap.h \
    pantallas/modos/uimodovsimv.h \
    pantallas/uialarmas.h \
    pantallas/uicalibrar.h \
    pantallas/uiconfigdatetime.h \
    pantallas/uiconfigmodo.h \
    pantallas/uiconfiguracion.h \
    pantallas/uieventos.h \
    pantallas/uiinfosistema.h \
    signos/widgetsigno2.h \
    signos/widgetsigno3.h \
    tarjetas/senpresion.h \
    tarjetas/teclado.h \
    tarjetas/ventilador.h \
    utilidades/alarmaaudled.h \
    utilidades/alarmaqw.h \
    utilidades/alarmasx.h \
    utilidades/formulas.h \
    utilidades/gpio.h \
    utilidades/infoalarma.h \
    utilidades/logutils.h \
    utilidades/myswitch.h \
    utilidades/qcustomplot.h \
    utilidades/qroundprogressbar.h \
    utilidades/qroundprogressbaralarm.h \
    utilidades/qroundprogressbarconfig.h \
    utilidades/reloj.h \
    utilidades/serverws.h \
    utilidades/temperatura.h \
    utilidades/tramas/tramaalarmas.h \
    utilidades/tramas/tramapcmv.h \
    utilidades/tramas/tramapcpap.h \
    utilidades/tramas/tramapsimv.h \
    utilidades/tramas/tramas.h \
    utilidades/tramas/tramavcmv.h \
    utilidades/tramas/tramavcpap.h \
    utilidades/tramas/tramavsimv.h \
    utilidades/uiqwidgetconfigreloj.h \
    utilidades/uiqwidgetmenugrafica.h \
    utilidades/ventanaaviso.h \
    utilidades/ventanaavisotest.h \
    utilidades/ventanacalibrar.h \
    utilidades/ventanaconfigpi.h \
    utilidades/ventanaconfirmacion.h \
    utilidades/ventanainfo.h \
    utilidades/ventanainoperante.h \
    utilidades/ventanainsfuga.h \
    utilidades/ventanainsoxi.h \
    utilidades/ventanamenu.h \
    utilidades/ventanapruebas.h \
    utilidades/widgetgrafica.h \
    utilidades/widgetgraficalazo.h \
    utilidades/widgetparametro.h \
    utilidades/widgetsignobar.h \
    utilidades/widgetsignobarconfig.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    graficos.qrc
