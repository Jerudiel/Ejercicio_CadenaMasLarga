#ifndef UICALIBRACIONES_H
#define UICALIBRACIONES_H

#include <QWidget>

#include <monitor.h>
#include <QString>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTabWidget>
#include <QFont>
#include <QSizePolicy>
#include <QStyleOption>
#include <QPainter>

#include "pantallas/calibraciones/uicalsensores.h"
#include "pantallas/calibraciones/uicalcontrol.h"
#include "pantallas/calibraciones/uicalotros.h"

class UiCalibraciones : public QWidget
{
    Q_OBJECT
public:
    explicit UiCalibraciones(QWidget *parent = nullptr);
    Monitor * monitor;
    QString btn;
    QString btnSeleccionado;
    QString btnSeleccionadoWidget;
    QString btnNoSeleccionadoWidget;
    QWidget * centralwidget;
    QWidget * horizontalLayoutWidget;
    QSizePolicy * sizePolicy;
    QTabWidget * tabWidget;
    QWidget * tab_cal;
    QFont * fuente;

    UiCalSensores *tab_sensores;
    UiCalControl *tab_control;
    UiCalOtros *tab_otros;

    int elementSel;

    void retranslateUi();
    virtual void paintEvet(QPaintEvent *event);
    void llenarConfiguracion();
public slots:
    void cambioTab(int i);
signals:

};

#endif // UICALIBRACIONES_H
