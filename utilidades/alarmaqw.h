#ifndef ALARMAQW_H
#define ALARMAQW_H

#include <QWidget>
#include <QString>
#include <QLabel>

#include <utilidades/qroundprogressbaralarm.h>

#include <monitor.h>

class AlarmaQW : public QWidget
{
    Q_OBJECT
public:
    explicit AlarmaQW(QWidget *parent = nullptr, QString nombre = "", QString etiqueta = "", QString unidad = "", Monitor * monitor = nullptr);
    QString nombre;
    QString etiqueta;
    QString unidad;
    int resolu;
    Monitor * monitor;

    int limMax;
    int limMin;
    float valueMax;
    float valueMin;
    int tipo;
    int idMax;
    int idMin;

    int eleActivo;
    bool alaActiva;

    QString estiloETB;
    QString estiloETW;

    QLabel * letiqueta;

    QLabel * lunidad;

    QRoundProgressBarAlarm * bmaximo;

    QLabel * escala;

    QRoundProgressBarAlarm * bminimo;

    void setTipo(int tipo);
    QString IDTOSTR(int idObjeto);
    void setIDS(int idMX, int IdMin);
    std::pair<float, float> getValores();
    void setActivo(int eleActivo);
    void actualizarFoco();
    bool activo();
    void setInactivo();
    void setLimMax(int max);
    void setLimMin(int min);
    void setMaxValue(float value);
    void setMinValue(float value);
    float getMaxValue();
    float getMinValue();
    void teclado(QString tecla);
    void mas();
    void menos();
    void mod();




signals:

};

#endif // ALARMAQW_H
