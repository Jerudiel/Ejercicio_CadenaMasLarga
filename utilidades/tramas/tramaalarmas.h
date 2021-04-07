#ifndef TRAMAALARMAS_H
#define TRAMAALARMAS_H

#include <QString>

#include <QStringList>
#include <QDebug>

class TramaAlarmas
{
public:
    TramaAlarmas();
    QString fr_max;
    QString fr_min;
    QString vol_max;
    QString vol_min;
    QString volmin_max;
    QString volmin_min;
    QString pres_max;
    QString pres_min;

    void llenar(QStringList parametros);
    QString obtener_trama();
    QString obtener_fr_max();
    QString obtener_fr_min();
    QString obtener_vol_max();
    QString obtener_vol_min();
    QString obtener_volmin_max();
    QString obtener_volmin_min();
    QString obtener_pres_max();
    QString obtener_pres_min();
};

#endif // TRAMAALARMAS_H
