#ifndef WIDGETSIGNOBARCONFIG_H
#define WIDGETSIGNOBARCONFIG_H

#include <QWidget>

#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "utilidades/qroundprogressbaralarm.h"


class WidgetSignoBarConfig : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetSignoBarConfig(QWidget *parent = nullptr, QString nombre = "");
    QString nombre;
    QVBoxLayout * boxLayout;
    QLabel * label_title;
    QHBoxLayout * horizontalLayout;
    QRoundProgressBarAlarm * bar;
    QVBoxLayout * verticalLayout;
    QFont * fuente;
    void retranslateUi();
    void activo();
    void inactivo();
    //virtual void paintEvent(QPaintEvent *event);

signals:

};

#endif // WIDGETSIGNOBARCONFIG_H
