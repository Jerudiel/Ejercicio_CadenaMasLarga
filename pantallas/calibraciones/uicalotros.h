#ifndef UICALOTROS_H
#define UICALOTROS_H

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

class UiCalOtros : public QWidget
{
    Q_OBJECT
public:
    explicit UiCalOtros(QWidget *parent = nullptr, Monitor *monitor = nullptr);
    Monitor *monitor;
    QFont * fuente;
    //QLabel * lblAltura;
    //QLineEdit * lEAltura;
    //QLabel * lblPresionar;
    //QLineEdit * lEPresionar;
    //QLabel * lblSoltar;
    //QLineEdit * lESoltar;
    QLabel * lblPorceCambio;
    QLineEdit * lEPorceCambio;

    QLabel * lblLsAire;
    QLineEdit * lELsAire;
    QLabel * lblLiAire;
    QLineEdit * lELiAire;
    QLabel * lblLsO2;
    QLineEdit * lELsO2;
    QLabel * lblLiO2;
    QLineEdit * lELiO2;

    //QLabel * lblOffPip;
    //QLineEdit * lEOffPip;

    //QPushButton *btnAplicarAltura;
    //QPushButton *btnAplicarTeclado;
    QPushButton *btnAplicarFio2;
    //QPushButton *btnAplicarComPip;
    QLabel *labelInfo;
    //QTimer *timerTecladoAplicados;

    void retranslateUi();
    virtual void paintEvent(QPaintEvent *event);

    //void cargarAltura();
    //void cargarTeclado();
    void cargarFio2();
    //void cargarOffPip();
public slots:
    //void aplicarCambiosAltura();
    //void aplicarCambiosTeclado();
    void aplicarCambiosFio2();
    //void aplicarCambiosOffPip();
    //void revisarCambiosTeclado();
signals:

};

#endif // UICALOTROS_H
