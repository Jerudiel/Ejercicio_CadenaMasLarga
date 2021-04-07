#ifndef TECLADO_H
#define TECLADO_H

#include <QWidget>
#include <QtSerialPort/QtSerialPort>
#include <QString>
#include <QTimer>
//#include "monitor.h"
//#include "mainwindow.h"

class Teclado : public QWidget
{
    Q_OBJECT
public:
    explicit Teclado(bool debug = true); //, void *funcion = nullptr
    //QWidget * padre;
    //MainWindow *mainwindow;
    QString puerto;
    bool debug;
    void *funcion;
    QSerialPort * serPuerto;
    bool avisoAbierto;
    QTimer *monitor;
    bool primera;
    QStringList listaErrores = {"NoError","DeviceNotFoundError","PermissionError","OpenError","ParityError","FramingError","BreakConditionError","WriteError","ReadError","ResourceError","UnsupportedOperationError","UnknownError","TimeoutError","NotOpenError"};
    QString strDisp;
    int contador_errores;

    bool estado();
    void escribir(QString datos);
    //QString leer();

    void _closepopup();

    void msg(QString mensaje);
    void msge(QString mensaje, std::exception error);
    //void asignaPadre(MainWindow *mainwindow);


signals:
    void enviaLinea(QString temp);
    void muestraAviso(QString mensaje);
    void cierraAviso();
    void estadoTeclaActivo(bool estado);

public slots:
    void leer();
    void errores(QSerialPort::SerialPortError error);
    void run();
};

#endif // TECLADO_H
