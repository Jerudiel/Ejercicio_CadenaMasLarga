#ifndef UICONFIGDATETIME_H
#define UICONFIGDATETIME_H

#include <QWidget>
#include <QFont>
#include <QCalendarWidget>
#include "utilidades/uiqwidgetconfigreloj.h"
#include <QLabel>
#include <QPushButton>
#include "monitor.h"
#include <QStyleOption>
#include <QPainter>
#include <QProcess>
#include <QTimer>

class UiConfigDatetime : public QWidget
{
    Q_OBJECT
public:
    explicit UiConfigDatetime(QWidget *parent = nullptr, Monitor *monitor = nullptr);
    Monitor *monitor;
    QFont *fuente;
    QCalendarWidget *calendario;
    UiQWidgetConfigReloj *pickerTime;
    QLabel *label_fecha_configurada;
    QPushButton *btnAplicarCambios;
    QLabel *label_info;
    QString anuncio;
    QTimer *timerAnuncio;

    virtual void paintEvent(QPaintEvent *event);

    void cargarFecha();
    QString darFormato2Digitos(int dato);


public slots:
    void mostrarFecha(QDate date);
    void aplicarCambios();
    void sumar_hora();
    void sumar_minuto();
    void restar_hora();
    void restar_minuto();
    void cambiar_horario();
    void muestraAviso();

signals:

};

#endif // UICONFIGDATETIME_H

