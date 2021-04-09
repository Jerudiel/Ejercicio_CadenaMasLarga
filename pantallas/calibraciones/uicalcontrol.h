#ifndef UICALCONTROL_H
#define UICALCONTROL_H

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


class UiCalControl : public QWidget
{
    Q_OBJECT
public:
    explicit UiCalControl(QWidget *parent = nullptr, Monitor *monitor = nullptr);
    Monitor *monitor;
    QFont * fuente;
    QVector< QVector< int > > rangos_offsets;
    QLabel * lblOffPeep;
    QLineEdit * lEOffPeep;
    QLabel * lblOffPip;
    QLineEdit * lEOffPip;
    QLabel * lblOffCpeep;
    QLineEdit * lEOffCpeep;
    QLabel * lblOffCpip;
    QLineEdit * lEOffCpip;
    QLabel * lblOffCPres;
    QLineEdit * lEOffCPres;
    QLabel * lblOffBat;
    QLineEdit * lEOffBat;
    QLabel * lblGBat;
    QLineEdit * lEGBat;
    QPushButton *btnAplicarCambios;
    QLabel *labelInfo;
    QTimer *timerCambiosAplicados;

    void retranslateUi();
    virtual void paintEvent(QPaintEvent *event);
    void cargarFactores();

public slots:
    void aplicarCambios();
    void revisarCambios();
signals:

};

#endif // UICALCONTROL_H
