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
    int li_aire;
    int flujo_max;
    int flujo_aire_21;
    int flujo_oxi_21;
    QMap<int, int> diccionario_o2;

    int porce_cambio;
    int of_o2;
    int m_aire;

    int get_pwm_max();
    int obtener_valor_pwm(float flujo);
    int obtener_valor_pwm_aire(int porcentaje);
    int obtener_valor_pwm_oxigeno(int porcentaje);

    void actualizar_fio2(QString porce_cambio_s, QString of_o2_s, QString m_aire_s, QString pwm_min_s);
};

#endif // FORMULAS_H
