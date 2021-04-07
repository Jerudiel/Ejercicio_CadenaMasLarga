#ifndef TRAMAPSIMV_H
#define TRAMAPSIMV_H

#include <QString>
#include <QStringList>
#include <QDebug>

#include "utilidades/formulas.h"

class TramaPSIMV
{
public:
    TramaPSIMV(Formulas *formulas);
    QString pinsp;
    QString psoporte;
    QString peep;
    QString fr;
    QString tinsp;
    QString tincr;
    QString oxigeno;
    QString mod_trigger;
    QString trigger_flujo;
    QString trigger_presion;
    QString palarmax;

    void llenar(QStringList parametros, QString alarpmax);
    QString obtener_trama_serpresion_config();
    QString obtener_pinsp();
    QString obtener_peep();
    QString obtener_psoporte();
    QString obtener_fr();
    QString obtener_tinsp();
    QString obtener_fio2();
    QString obtener_modo_trigger();
    QString obtener_sensibilidad();
    QString obtener_tincr();
    QString obtener_trama_ventilador();
    QString obt_ti();
    QString obt_tp();
    QString obt_te();
    QString obt_fr();
    QString obt_pwm();
    QString obt_pwm_oxi();
    QString obt_pwm_aire();
    QString obt_pinsp();
    QString obt_peep();
    QString obt_psoporte();
    QString obt_palarmax();
    QString obt_estado();

    Formulas * formulas;
};

#endif // TRAMAPSIMV_H
