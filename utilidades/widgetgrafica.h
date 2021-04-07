#ifndef WIDGETGRAFICA_H
#define WIDGETGRAFICA_H

#include <QWidget>
#include "utilidades/qcustomplot.h"
#include <QTimer>
#include <QVector>

#define MAX_PUNTOS 250

class WidgetGrafica : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetGrafica(QWidget *parent = nullptr, QString nombre = "", QString tituloy = "", float min=0, float max=0, QBrush color_linea = Qt::black, int tiempo = 50, bool promediador = false, int orden = 2);
    QCustomPlot *grafica;
    int indiceXDato;
    QTimer *timerActualiza;

    int tiempo;
    bool promediador;
    int orden;

    int contador_promediador;
    QStringList *lista_promediador;
    bool promediador_listo;

    QVector<double> indicesx;
    QVector<double> indicesY;
    QVector<double> base;
    QVector<double> datos_backup;
    int contador;
    bool llenado;
    int datos_borrados;
    QStringList listaDatos;
    int contReplot;
    int datos_eliminar;
    int contador_datos;

    void limpiar_promediador();

public slots:
    void replot();
    void graficar(QString dato);
    void actualiza(QString dato);

protected:
    virtual void timerEvent(QTimerEvent *event);
signals:

};

#endif // WIDGETGRAFICA_H
