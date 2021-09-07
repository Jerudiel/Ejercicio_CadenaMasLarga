#ifndef UIINFOSISTEMA_H
#define UIINFOSISTEMA_H

#include <QWidget>
#include <math.h>
#include <QLabel>
#include <QStyleOption>
#include <QPainter>
#include "utilidades/myswitch.h"
#include <QTimer>
#include "utilidades/temperatura.h"
#include "monitor.h"

class UiInfoSistema : public QWidget
{
    Q_OBJECT
public:
    explicit UiInfoSistema(QWidget *parent = nullptr, Monitor *monitor = nullptr);
    Monitor *monitor;
    QFont *fuente;
    QLabel *labelVersionTeclado;
    QLabel *labelVersionSensores;
    QLabel *labelAlarmasSensores;
    QLabel *labelVersionVentilador;
    QLabel *labelAlarmasVentilador;
    QLabel *labelEntradaAire;
    QLabel *labelEntradaOxigeno;
    QLabel *labelSenPresion;
    QLabel *labelVersionCPU;
    QLabel *labelNumeroSerie;
    QLabel *labelNumeroReinicios;
    QLabel *labelTiempoAcumulado;
    QLabel *labelTiempoTotal;

    Temperatura *tempMon; //= Temperatura(self, self.Monitor, self.logger)

    MySwitch *switchGiro;
    MySwitch *switchSenPre;
    QTimer *timerActualiza;

    QTimer *timerActualizaTiempos;
    void retranslateUi();
    virtual void paintEvent(QPaintEvent *event);

    void cargarVersiones();

public slots:
    void cambiarSentidoGiro();
    void cambiarSenPre();
    void actualizaValores();
    void actualizaTiempos();

signals:

};

#endif // UIINFOSISTEMA_H

