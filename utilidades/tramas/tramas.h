#ifndef TRAMAS_H
#define TRAMAS_H

#include <utilidades/tramas/tramapcmv.h>
#include <utilidades/tramas/tramaalarmas.h>
#include <utilidades/tramas/tramavcmv.h>
#include <utilidades/tramas/tramapsimv.h>
#include <utilidades/tramas/tramavsimv.h>
#include <utilidades/tramas/tramapcpap.h>
#include <utilidades/tramas/tramavcpap.h>
#include <utilidades/formulas.h>
#include <QStringList>
#include <QDebug>

class Tramas
{
public:
    Tramas();
    int modo;

    Formulas *formulas;

    TramaPCMV * trama_PCMV;
    TramaAlarmas * trama_alarmas;
    TramaVCMV * trama_VCMV;
    TramaPSIMV * trama_PSIMV;
    TramaVSIMV * trama_VSIMV;
    TramaPCPAP * trama_PCPAP;
    TramaVCPAP * trama_VCPAP;

    void set_modo(int modo);
    void llenar_modo(int modo, QStringList parametros, QString alarpmax);
    void llenar_alarmas(QStringList parametros);
    QString obtener_trama_serpresion_config(int modo);
    QString obtener_trama_alarmas();
    QString obtener_trama_ventilador(int modo);
    void actualizar_formulas(QString porce_cambio, QString ls_aire, QString li_aire, QString ls_o2, QString li_o2);

};

#endif // TRAMAS_H
