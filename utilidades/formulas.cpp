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

        porce_cambio = 0;
        ls_aire = 0;
        li_aire = 0;
        ls_o2 = 0;
        li_o2 = 0;


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

int Formulas::obtener_valor_pwm_aire(int fio2){
    try {
        float pwm_aire = 0;
        if(fio2 < porce_cambio){
            pwm_aire = pwm_max;
        }
        else if(fio2 == porce_cambio){
            pwm_aire = pwm_max;
        }
        else{
            if(fio2 == 100){
                pwm_aire = pwm_min;
            }
            else{
                //pwm_aire = 300 + (4*(100-porcentaje));
                //pwm_aire = m_aire - ((porcentaje - porce_cambio)*((m_aire - li_aire)/(100-porce_cambio)));

                /*float temp1 = ls_aire;
                float temp2 = fio2 - porce_cambio;
                float temp3 = li_aire - ls_aire;
                float temp4 = 100 - porce_cambio;
                float temp5 = (temp3/temp4);
                pwm_aire =  temp1 + (temp2 * temp5);*/

                pwm_aire = ls_aire + (1.0*(fio2 - porce_cambio)*((li_aire - ls_aire)/(100.0 - porce_cambio)));
            }
        }
        return static_cast<int>(pwm_aire);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return 0;
    }
}

int Formulas::obtener_valor_pwm_oxigeno(int fio2){
    try {
        float pwm_oxigeno = 0;
        if(fio2 < porce_cambio){
            if(fio2 == 21){
                pwm_oxigeno = pwm_min;
            }
            else{
                //float cociente = 30/21.0;
                //pwm_oxigeno = ((porcentaje - 22) * cociente) + 180;
                //pwm_oxigeno = of_o2 + (fio2 * ((pwm_max - of_o2)/(porce_cambio)));
                //qDebug() << "Entra a obtener_valor_pwm_oxigeno < porce_cambio";
                //qDebug() << "li_o2: " + QString::number(li_o2);
                //qDebug() << "ls_o2: " + QString::number(ls_o2);
                //qDebug() << "fio2: " + QString::number(fio2);
                //qDebug() << "porce_cambio: " + QString::number(porce_cambio);
                //float temp1 = li_o2;
                //qDebug() << "1 - li_o2: " + QString::number(temp1);
                //float temp2 = fio2 - 21;
                //qDebug() << "2 - fio2 - 21: " + QString::number(temp2);
                //float temp3 = ls_o2 - li_o2;
                //qDebug() << "3 - ls_o2 - li_o2: " + QString::number(temp3);
                //float temp4 = porce_cambio - 21;
                //qDebug() << "4 - porce_cambio - 21: " + QString::number(temp4,'f',2);
                //float temp5 = (temp3/temp4);
                //qDebug() << "5 - (ls_o2 - li_o2)/(porce_cambio - 21): " + QString::number(temp5,'f',2);
                pwm_oxigeno = li_o2 + (1.0*(fio2 - 21)*((ls_o2 - li_o2)/(porce_cambio - 21.0)));
                ////pwm_oxigeno =  temp1 + (temp2 * temp5);
                //qDebug() << "pwm_oxigeno: " + QString::number(pwm_oxigeno,'f',2);
            }
        }
        else if(fio2 == porce_cambio){
            pwm_oxigeno = pwm_max;
        }
        else{
            //float cociente = 16/21.0;
            pwm_oxigeno = pwm_max; //((porcentaje - 22) * cociente) + 225;
        }
        return static_cast<int>(pwm_oxigeno);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return 0;
    }
}

void Formulas::actualizar_fio2(QString porce_cambio_s, QString ls_aire_s, QString li_aire_s, QString ls_o2_s, QString li_o2_s){
    try {
        porce_cambio = porce_cambio_s.toInt();
        ls_aire = ls_aire_s.toInt();
        li_aire = li_aire_s.toInt();
        ls_o2 = ls_o2_s.toInt();
        li_o2 = li_o2_s.toInt();
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}
