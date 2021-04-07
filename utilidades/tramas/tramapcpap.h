#ifndef TRAMAPCPAP_H
#define TRAMAPCPAP_H

#include <QString>
#include <QStringList>
#include <QDebug>

#include "utilidades/formulas.h"

class TramaPCPAP
{
public:
    TramaPCPAP(Formulas *formulas);
    QString cpap;
    QString ps;
    QString oxigeno;
    QString mod_trigger;
    QString trigger_flujo;
    QString trigger_presion;
    QString apnea;
    QString frecuencia;
    QString pinsp;
    QString tinsp;
    QString palarmax;
    int ti;

    void llenar(QStringList parametros, QString alarpmax);
    QString obtener_trama_serpresion_config();
    QString obtener_cpap();
    QString obtener_ps();
    QString obtener_fio2();
    QString obtener_modo_trigger();
    QString obtener_sensibilidad();
    QString obtener_apnea();
    QString obtener_fr();
    QString obtener_pinsp();
    QString obtener_tinsp();
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

#endif // TRAMAPCPAP_H
