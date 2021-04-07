#ifndef WIDGETSIGNOBAR_H
#define WIDGETSIGNOBAR_H

#include <QWidget>

#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "utilidades/qroundprogressbar.h"

class WidgetSignoBar : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetSignoBar(QWidget *parent = nullptr, QString nombre = "", QString nombrewidget = "", QString unidad = "", float min = 0, float max = 150, float value = 0, QString formato = "");
    QString nombre;
    QString nombrewidget;
    QString unidad;
    QFont * fuente;
    float min;
    float max;
    float value;
    QVBoxLayout * boxLayout;
    QLabel * label_title;
    QHBoxLayout * horizontalLayout;
    QRoundProgressBar * bar;
    QVBoxLayout * verticalLayout;
    QHBoxLayout * horLayoutProg;
    QLabel * label_val_inf;
    QLabel * label_val_prog;
    QLabel * label_val_sup;

    void retranslateUi();
    float valorProg;
    void setValorProg(QString inf="", QString prog="", QString sup="");
    virtual void paintEvent(QPaintEvent *event);

signals:

};

#endif // WIDGETSIGNOBAR_H

