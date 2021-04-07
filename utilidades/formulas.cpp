#include "formulas.h"

#include "math.h"

Formulas::Formulas()
{
    try {
        pwm_max = 483;
        pwm_min = 60;
        flujo_max = 96;
        flujo_aire_21 = 36;
        flujo_oxi_21 = 0;

        li_aire = 0;
        porce_cambio = 0;
        of_o2 = 0;
        m_aire = 0;


        /*diccionario_o2 = QMap<int, int>( { {"a", 1}, {"b", 2}, {"c", 3} } );
        diccionario_o2 = QMap<int,int>({{21,238},{},{},{},{},{},{},{},{},{},
                          {31,},{},{},{},{},{},{},{},{},{},
                          {41,},{},{},{},{},{},{},{},{},{},
                          {51,},{},{},{},{},{},{},{},{},{},
                          {61,},{},{},{},{},{},{},{},{},{},
                          {71,},{},{},{},{},{},{},{},{},{},
                          {81,},{},{},{},{},{},{},{},{},{},
                          {91,},{},{},{},{},{},{},{},{},{}});*/
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

int Formulas::get_pwm_max(){
    try {
        return pwm_max;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return 0;
    }
}

int Formulas::obtener_valor_pwm(float flujo){
    try {
        /*
        Primero convertir flujo a porcentaje
        fórmula: y = 5.45x + 3.8189 usado
        maximo 483
        */
        //qDebug() << "obtener_valor_pwm - flujo: " + QString::number(flujo);
        float porcentaje = 15.931 * exp(0.0141*flujo);
        //qDebug() << "obtener_valor_pwm - porcentaje: " + QString::number(porcentaje);
        if(porcentaje > 60){
            porcentaje = 60;
        }
        float pwm = 5.45*porcentaje + 3.8189;
        //qDebug() << "obtener_valor_pwm - pwm: " + QString::number(pwm);
        if( pwm > pwm_max){
            return pwm_max;
        }
        else{
            return static_cast<int>(pwm);
        }

    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return 0;
    }
}

int Formulas::obtener_valor_pwm_aire(int porcentaje){
    try {
        int pwm_aire = 0;
        if(porcentaje < porce_cambio){
            pwm_aire = pwm_max;
        }
        else if(porcentaje == porce_cambio){
            pwm_aire = pwm_max;
        }
        else{
            if(porcentaje == 100){
                pwm_aire = pwm_min;
            }
            else{
                //pwm_aire = 300 + (4*(100-porcentaje));
                pwm_aire = m_aire - ((porcentaje - porce_cambio)*((m_aire - li_aire)/(100-porce_cambio)));
            }
        }
        return pwm_aire;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return 0;
    }
}

int Formulas::obtener_valor_pwm_oxigeno(int porcentaje){
    try {
        int pwm_oxigeno = 0;
        if(porcentaje < porce_cambio){
            if(porcentaje == 21){
                pwm_oxigeno = pwm_min;
            }
            else{
                //float cociente = 30/21.0;
                //pwm_oxigeno = ((porcentaje - 22) * cociente) + 180;
                pwm_oxigeno = of_o2 + (porcentaje * ((pwm_max - of_o2)/(porce_cambio)));
            }
        }
        else if(porcentaje == porce_cambio){
            pwm_oxigeno = pwm_max;
        }
        else{
            //float cociente = 16/21.0;
            pwm_oxigeno = pwm_max; //((porcentaje - 22) * cociente) + 225;
        }
        return pwm_oxigeno;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return 0;
    }
}

void Formulas::actualizar_fio2(QString porce_cambio_s, QString of_o2_s, QString m_aire_s, QString pwm_min_s){
    try {
        porce_cambio = porce_cambio_s.toInt();
        of_o2 = of_o2_s.toInt();
        m_aire = m_aire_s.toInt();
        li_aire = pwm_min_s.toInt();
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}
