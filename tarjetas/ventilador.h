#ifndef VENTILADOR_H
#define VENTILADOR_H

#include <QWidget>
#include <QtSerialPort/QtSerialPort>
#include <QString>
#include <QTimer>
//#include "monitor.h"
//#include "mainwindow.h"

class Ventilador : public QWidget
{
    Q_OBJECT
public:
    explicit Ventilador(bool debug = true); //QWidget *parent = nullptr,  Monitor *mon = nullptr, bool debug = true
    //QWidget * padre;
    //Monitor * mon;
    QString puerto;
    bool debug;
    //, void *funcion = nullptr
    //void *funcion;
    QSerialPort * serPuerto;
    bool avisoAbierto;
    QTimer *monitor;
    bool primera;
    bool corriendo;
    QString tramaConfiguracion;
    QStringList listaErrores = {"NoError","DeviceNotFoundError","PermissionError","OpenError","ParityError","FramingError","BreakConditionError","WriteError","ReadError","ResourceError","UnsupportedOperationError","UnknownError","TimeoutError","NotOpenError"};
    QString strDisp;
    int contador_errores;

    bool estaCorriendo();
    void actualizaTrama(QString trama);
    void ajusta_ventilador(QString trama);
    void cambio_giro(QString trama);
    void envia_trama_config(QString trama);
    void iniciar_ventilador(QString trama);
    void detener_ventilador(QString trama);
    bool estado();
    //QString leer();

    void _closepopup();

    void msg(QString mensaje);
    void msge(QString mensaje, std::exception error);
    //void asignaPadre(Monitor* mon);

signals:
    void enviaLinea(QString temp);
    void muestraAviso(QString mensaje);
    void cierraAviso();
    void estadoVentiActivo(bool estado);
public slots:
    void leer();
    void errores(QSerialPort::SerialPortError error);
    void run();
};

#endif // VENTILADOR_H
