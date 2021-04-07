#ifndef WIDGETPARAMETRO_H
#define WIDGETPARAMETRO_H

#include <QWidget>
#include <QString>

#include <QVBoxLayout>
#include <QLabel>
#include <QFont>
#include <QDebug>
#include "utilidades/qroundprogressbaralarm.h"

class WidgetParametro : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetParametro(QWidget *parent = nullptr, QString nombre = "", QString unidad = "", float lim_sup = 0, float lim_inf = 0, QString resolucion = 0, float valor = 0, int id = 0, int tipo = 0, bool salto = false);
    QString nombre;
    float lim_sup;
    float lim_inf;
    QString resolucion;
    float perilla;
    float valor;
    int id;
    int tipo;
    bool salto;
    QString unidad;
    QVBoxLayout * boxLayout;
    QLabel * label_title;
    QFont * fuente;
    QHBoxLayout * horizontalLayout;
    QRoundProgressBarAlarm * bar;
    QVBoxLayout * verticalLayout;

    void set_tipo();
    void set_lim_sup(float valor);
    void set_lim_inf(float valor);
    bool sumar();
    bool restar();
    float cambiar_perilla();
    void activo();
    void inactivo();
    float get_valor();
    void set_valor(QString valor);
    void retranslateUi();


signals:

};

#endif // WIDGETPARAMETRO_H
