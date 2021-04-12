#ifndef FORMULAS_H
#define FORMULAS_H

#include <QMap>
#include <QDebug>

class Formulas
{
public:
    Formulas();
    int pwm_max;
    int pwm_min;
    //int li_aire;
    int flujo_max;
    int flujo_aire_21;
    int flujo_oxi_21;
    QMap<int, int> diccionario_o2;

    int porce_cambio;
    int ls_aire;
    int li_aire;
    int ls_o2;
    int li_o2;

    int get_pwm_max();
    int obtener_valor_pwm(float flujo);
    int obtener_valor_pwm_aire(int porcentaje);
    int obtener_valor_pwm_oxigeno(int porcentaje);

    void actualizar_fio2(QString porce_cambio_s, QString ls_aire_s, QString li_aire_s, QString ls_o2_s, QString li_o2_s);
};

#endif // FORMULAS_H
