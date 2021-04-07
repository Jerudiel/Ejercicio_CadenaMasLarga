#ifndef TRAMAVCMV_H
#define TRAMAVCMV_H

#include <QString>
#include <QStringList>
#include <QDebug>

#include "utilidades/formulas.h"

class TramaVCMV
{
public:
    TramaVCMV(Formulas *formulas);
    QString vtinsp;
    QString peep;
    QString fr;
    QString flujo;
    QString meseta;
    QString patron;
    QString oxigeno;
    QString mod_trigger;
    QString trigger_flujo;
    QString trigger_presion;
    QString palarmax;
    float ti;

    void llenar(QStringList parametros, QString alarpmax);
    QString obtener_trama_serpresion_config();
    QString obtener_vtinsp();
    QString obtener_peep();
    QString obtener_fr();
    QString obtener_flujo();
    QString obtener_fio2();
    QString obtener_modo_trigger();
    QString obtener_sensibilidad();
    QString obtener_tpausa();
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

#endif // TRAMAVCMV_H
