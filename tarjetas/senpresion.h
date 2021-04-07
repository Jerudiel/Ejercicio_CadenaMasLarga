#ifndef SENPRESION_H
#define SENPRESION_H

#include <QWidget>
#include <QtSerialPort/QtSerialPort>
#include <QString>
#include <QTimer>
//#include "monitor.h"
//#include "mainwindow.h"

class SenPresion : public QWidget
{
    Q_OBJECT
public:
    explicit SenPresion(bool debug = true); //QWidget *parent = nullptr,
    //, void *funcion = nullptr
    //QWidget *parent;
    //Monitor  *mon;
    QString puerto;
    bool debug;
    //void * funcion;
    QSerialPort * serPuerto;
    bool avisoAbierto;
    QTimer *monitor;
    QTimer *mconfig;
    bool primera;
    bool corriendo;
    QString tramaConf;
    QStringList listaErrores = {"NoError","DeviceNotFoundError","PermissionError","OpenError","ParityError","FramingError","BreakConditionError","WriteError","ReadError","ResourceError","UnsupportedOperationError","UnknownError","TimeoutError","NotOpenError"};
    QString strDisp;
    int contador_errores;

    bool estado();
    void escribir(QString datos);
    //QString leer();

    void _closepopup();

    void iniciar_sensor_presion();
    void detener_sensor_presion();
    void configurarSenPresion(QString trama);

    void msg(QString mensaje);
    void msge(QString mensaje, std::exception error);
    //void asignaPadre(Monitor* mon);

signals:
    void enviaLinea(QString temp);
    void muestraAviso(QString mensaje);
    void cierraAviso();
    void estadoPresActivo(bool estado);
    void iniciaMonitoreo();
public slots:
    void leer();
    void errores(QSerialPort::SerialPortError error);
    void run();
    void configura();
};

#endif // SENPRESION_H
