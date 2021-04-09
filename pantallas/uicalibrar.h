#ifndef UICALIBRAR_H
#define UICALIBRAR_H

#include <QWidget>
#include "monitor.h"
#include <QFont>
#include <QVector>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTimer>
#include <QStyleOption>
#include <QPainter>

#include "pantallas/calibraciones/uicalibraciones.h"

class UiCalibrar : public QWidget
{
    Q_OBJECT
public:
    explicit UiCalibrar(QWidget *parent = nullptr, Monitor * monitor = nullptr);
    Monitor *monitor;
    QFont * fuente;
    UiCalibraciones *calibraciones;
    /*QVector< QVector< int > > rangos_offsets;
    QLabel * labelFactor1;
    QLineEdit * lineEditFactor1;
    QLabel * labelFactor2;
    QLineEdit * lineEditFactor2;
    QLabel * labelFactor3;
    QLineEdit * lineEditFactor3;
    QLabel * labelFactor4;
    QLineEdit * lineEditFactor4;
    QLabel * labelFactor5;
    QLineEdit * lineEditFactor5;
    QLabel * labelFactor6;
    QLineEdit * lineEditFactor6;
    QLabel * labelFactor7;
    QLineEdit * lineEditFactor7;
    QLabel * labelFactor8;
    QLineEdit * lineEditFactor8;
    QLabel * labelFactor9;
    QLineEdit * lineEditFactor9;
    QLabel * labelFactor10;
    QLineEdit * lineEditFactor10;
    QLabel * labelFactor11;
    QLineEdit * lineEditFactor11;
    QLabel * labelFactor12;
    QLineEdit * lineEditFactor12;
    QLabel * labelFactor13;
    QLineEdit * lineEditFactor13;
    QLabel * labelFactor14;
    QLineEdit * lineEditFactor14;
    QLabel * labelFactor15;
    QLineEdit * lineEditFactor15;
    QLabel * labelFactor16;
    QLineEdit * lineEditFactor16;
    QLabel * labelFactor17;
    QLineEdit * lineEditFactor17;
    QLabel * labelFactor18;
    QLineEdit * lineEditFactor18;
    QLabel * labelFactor19;
    QLineEdit * lineEditFactor19;
    QPushButton *btnAplicarCambios;
    QPushButton *btnAplicarOffsets;
    QPushButton *btnAplicarAltura;
    QPushButton *btnAplicarTeclado;
    QPushButton *btnAplicarFio2;
    QLabel *labelInfo;
    QTimer *timerCambiosAplicados;
    QTimer *timerOffsetsAplicados;
    QTimer *timerTecladoAplicados;*/



    //void retranslateUi();
    virtual void paintEvent(QPaintEvent *event);


    /*void cargarFactores();
    void cargarOffsets();
    void cargarAltura();
    void cargarTeclado();
    void cargarFio2();*/


public slots:
    /*void aplicarCambios();
    void aplicarCambiosOffsets();
    void aplicarCambiosAltura();
    void aplicarCambiosTeclado();
    void aplicarCambiosFio2();
    void revisarCambios();
    void revisarCambiosOffsets();
    void revisarCambiosTeclado();*/

signals:

};

#endif // UICALIBRAR_H

