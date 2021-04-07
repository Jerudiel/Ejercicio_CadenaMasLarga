#ifndef WIDGETGRAFICALAZO_H
#define WIDGETGRAFICALAZO_H

#include <QWidget>
#include "utilidades/qcustomplot.h"
#include <QTimer>

#define MAX_PUNTOS 250

class WidgetGraficaLazo : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetGraficaLazo(QWidget *parent = nullptr, QString nombre = "", QString tituloy = "", float min_y=0, float max_y=0, QString titulox = "", float min_x=0, float max_x=0,QBrush color_linea = Qt::black, int tiempo = 50);
    QCustomPlot *grafica;
    QCPCurve *graficaCurva;
    int indiceXDato;
    QTimer *timerActualiza;

    QVector<double> eje_x;
    QVector<double> eje_y;
    QVector<QCPCurveData> eje_curva_x;
    QVector<QCPCurveData> eje_curva_y;

    void graficar(QString datox, QString datoy);
    void limpiar();
public slots:
    void replot();
signals:

};

#endif // WIDGETGRAFICALAZO_H
