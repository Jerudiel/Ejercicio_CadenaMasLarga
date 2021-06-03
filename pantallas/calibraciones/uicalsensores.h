#ifndef UICALSENSORES_H
#define UICALSENSORES_H

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

class UiCalSensores : public QWidget
{
    Q_OBJECT
public:
    explicit UiCalSensores(QWidget *parent = nullptr, Monitor *monitor = nullptr);
    Monitor *monitor;
    QFont * fuente;
    QVector< QVector< int > > rangos_offsets;
    QLabel * lblFactInh;
    QLineEdit * lEFactInh;
    QLabel * lblUmBajo;
    QLineEdit * lEUmBajo;
    QLabel * lblFactExh;
    QLineEdit * lEFactExh;
    QLabel * lblUmBAlto;
    QLineEdit * lEUmAlto;
    QLabel * lblOffPres;
    QLineEdit * lEOffPres;
    QLabel * lblAjuExh;
    QLineEdit * lEAjuExh;
    QLabel * lblOffExh;
    QLineEdit * lEOffExh;
    QPushButton *btnAplicarCambios;
    QLabel * lblFacVPH;
    QLineEdit * lEFacVPH;
    QLabel * lblDeltaT;
    QLineEdit * lEDeltaT;
    QLabel *labelInfo;
    QTimer *timerCambiosAplicados;

    QTimer *timerMuestraMensaje;
    void muestraMensaje(QString trama);

    void retranslateUi();
    virtual void paintEvent(QPaintEvent *event);
    void cargarFactores();
    QString darFormato3Bytes(QString numero);
    QString darFormato4Bytes(QString numero);

public slots:
    void aplicarCambios();
    void revisarCambios();
    void limpiaMensaje();
signals:

};

#endif // UICALSENSORES_H
