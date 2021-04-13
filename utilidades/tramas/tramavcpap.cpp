#include "tramavcpap.h"

TramaVCPAP::TramaVCPAP(Formulas *formulas)
{
    try {
        cpap = "";
        ps = "";
        oxigeno = "";
        mod_trigger = "";
        trigger_flujo = "";
        trigger_presion = "";
        apnea = "";
        frecuencia = "";
        vt = "";
        flujo = "";
        palarmax = "";
        ti = 0;
        //formulas = new Formulas;
        this->formulas = formulas;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void TramaVCPAP::llenar(QStringList parametros, QString alarpmax){
    try {
        cpap = parametros.at(1);
        ps = parametros.at(2);
        oxigeno = parametros.at(3);
        apnea = parametros.at(4);
        mod_trigger = parametros.at(5);
        trigger_flujo = parametros.at(6);
        trigger_presion = parametros.at(7);
        frecuencia = parametros.at(8);
        vt = parametros.at(9);
        flujo = parametros.at(10);
        palarmax = alarpmax;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }

}

QString TramaVCPAP::obtener_trama_serpresion_config(){
    try {
        QString modo = "5";
        QString t_cpap = obtener_cpap();
        QString t_ps = obtener_ps();
        QString t_fio2 = obtener_fio2();
        QString t_mod_trigger = obtener_modo_trigger();
        QString t_sensibilidad = obtener_sensibilidad();
        QString t_apnea = obtener_apnea();
        QString t_frecuencia = obtener_fr();
        QString t_vt = obtener_vt();
        QString t_flujo = obtener_flujo();
        //unir
        QString trama = "C" + modo + t_cpap + t_ps + t_fio2 + t_mod_trigger + t_sensibilidad + t_apnea + t_frecuencia + t_vt + t_flujo + "\n";
        if(trama.size() == 24){
            //qDebug() << "trama: " + trama + "size: " + QString::number(trama.size());
            return trama;
        }
        else{
            //qDebug() << "trama- error tamaño : " + trama + "size: " + QString::number(trama.size());
            return "";
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

QString TramaVCPAP::obtener_cpap(){
    try {
        QString cpap_s = "";
        int cpap_int = cpap.toInt();
        if(cpap_int >= 0 && cpap_int < 10){
            cpap_s = "0" + cpap;
        }
        else if(cpap_int >= 10 && cpap_int < 100){
            cpap_s = cpap;
        }
        return cpap_s;

    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

QString TramaVCPAP::obtener_ps(){
    try {
        QString ps_s = "";
        int ps_int = ps.toInt();
        if(ps_int >= 0 && ps_int < 10){
            ps_s = "0" + ps;
        }
        else if(ps_int >= 10 && ps_int < 100){
            ps_s = ps;
        }
        return ps_s;

    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

QString TramaVCPAP::obtener_fio2(){
    try {
        QString fio2_s = "";
        int fio2_int = oxigeno.toInt();
        if(fio2_int >= 0 && fio2_int < 10){
            fio2_s = "00" + oxigeno;
        }
        else if(fio2_int >= 10 && fio2_int < 100){
            fio2_s = "0" + oxigeno;
        }
        else if(fio2_int >= 100 && fio2_int < 1000){
            fio2_s = oxigeno;
        }
        return fio2_s;

    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

QString TramaVCPAP::obtener_modo_trigger(){
    try {
        if(mod_trigger == "1"){
            return "1";
        }
        else{
            return "0";
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

QString TramaVCPAP::obtener_sensibilidad(){
    try {
        QString sensi_s = "";
        QString temp_s = "";
        if(mod_trigger == "1"){
            temp_s = trigger_flujo;
        }
        else{
            temp_s = trigger_presion;
        }
        //dar formato
        int temp_int = temp_s.toInt();
        if(temp_int >= 0 && temp_int < 10){
            sensi_s = "0" + temp_s;
        }
        else if(temp_int >= 10 && temp_int < 100){
            sensi_s = temp_s;
        }
        return sensi_s;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

QString TramaVCPAP::obtener_apnea(){
    try {
        QString apnea_s = "";
        int apnea_int = apnea.toInt();
        if(apnea_int >= 0 && apnea_int < 10){
            apnea_s = "0" + apnea;
        }
        else if(apnea_int >= 10 && apnea_int < 100){
            apnea_s = apnea;
        }
        return apnea_s;

    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

QString TramaVCPAP::obtener_fr(){
    try {
        QString fr_s = "";
        int fr_int = frecuencia.toInt();
        if(fr_int >= 0 && fr_int < 10){
            fr_s = "0" + apnea;
        }
        else if(fr_int >= 10 && fr_int < 100){
            fr_s = apnea;
        }
        return fr_s;

    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

QString TramaVCPAP::obtener_vt(){
    try {
        QString vt_s = "";
        int vt_int = vt.toInt();
        if(vt_int >= 0 && vt_int < 10){
            vt_s = "000" + vt;
        }
        else if(vt_int >= 10 && vt_int < 100){
            vt_s = "00" + vt;
        }
        else if(vt_int >= 100 && vt_int < 1000){
            vt_s = "0" + vt;
        }
        else if(vt_int >= 1000 && vt_int < 10000){
            vt_s = vt;
        }
        return vt_s;

    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

QString TramaVCPAP::obtener_flujo(){
    try {
        QString flujo_s = "";
        int flujo_int = flujo.toInt();
        if(flujo_int >= 0 && flujo_int < 10){
            flujo_s = "00" + QString::number(flujo_int);
        }
        else if(flujo_int >= 10 && flujo_int < 100){
            flujo_s = "0" + QString::number(flujo_int);
        }
        else if(flujo_int >= 100 && flujo_int < 1000){
            flujo_s = QString::number(flujo_int);
        }
        return flujo_s;

    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

QString TramaVCPAP::obtener_trama_ventilador(){
    try {
        QString modo = "5";
        QString t_ti = obt_ti();
        QString t_tp = obt_tp();
        QString t_te = obt_te();
        QString t_fr = obt_fr();
        QString t_pwm = obt_pwm();
        QString t_pwm_oxi = obt_pwm_oxi();
        QString t_pwm_aire = obt_pwm_aire();
        QString t_fio2 = obtener_fio2();

        QString t_pinsp = obt_pinsp();
        QString t_peep = obt_peep();
        QString t_psoporte = obt_psoporte();
        QString t_palarmax = obt_palarmax();
        QString t_estado = obt_estado();

        //calculos
        int periodo = static_cast<int>((QString::number(60.0/ frecuencia.toFloat(), 'f', 2)).toFloat() * 100);
        int temp_ti = t_ti.toInt();
        int temp_tp = t_tp.toInt();
        int temp_te = t_te.toInt();
        if((periodo - temp_ti - temp_tp - temp_te) != 0){
            int temp_te_ = periodo - temp_ti - temp_tp;
            if(0 <= temp_te && temp_te <10){
                t_te = "000" + QString::number(temp_te_);
            }
            else if(10 <= temp_te && temp_te <100){
                t_te = "00" + QString::number(temp_te_);
            }
            else if(100 <= temp_te && temp_te <1000){
                t_te = "0" + QString::number(temp_te_);
            }
            else{
                t_te = QString::number(temp_te_);
            }
        }
        //unir
        QString trama = "M" + modo + t_ti + t_tp + t_te + t_fr + t_pwm + t_pwm_oxi + t_pwm_aire + t_fio2 + t_pinsp + t_peep + t_psoporte + t_palarmax + t_estado + "\n";
        if(trama.size() == 46){
            return trama;
        }
        else{
            qDebug() << "trama incorrecta M: " + trama;
            qDebug() << "longitud: " + QString::number(trama.size());
            return "";
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

QString TramaVCPAP::obt_ti(){
    try {
        //calculos
        float vol_l = vt.toInt()/1000.0;
        int flujo_t = flujo.toInt();
        float pi = vol_l / flujo_t * 60.0;
        //int periodo = static_cast<int>((QString::number(60.0/ fr.toFloat(), 'f', 2)).toFloat());
        //float tp = 0;
        ti = pi;
        float temp_ti = (QString::number(pi, 'f', 2)).toFloat();

        //
        QString ti_s = "";
        int ti_int = static_cast<int>(temp_ti*100);
        if(ti_int >= 0 && ti_int < 10){
            ti_s = "000" + QString::number(ti_int);
        }
        else if(ti_int >= 10 && ti_int < 100){
            ti_s = "00" + QString::number(ti_int);
        }
        else if(ti_int >= 100 && ti_int < 1000){
            ti_s = "0" + QString::number(ti_int);
        }
        else if(ti_int >= 1000 && ti_int < 10000){
            ti_s = QString::number(ti_int);
        }
        return ti_s;

    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

QString TramaVCPAP::obt_tp(){
    try {
        return "0000";

    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

QString TramaVCPAP::obt_te(){
    try {
        //calculos
        float ti_t = ti;
        //float tp = 0;
        float periodo = 60.0 / frecuencia.toInt();
        float tt = periodo - ti_t;
        //

        QString tp_s = "";
        int temp = static_cast<int>((tt) * 100);
        if(temp >= 0 && temp < 10){
            tp_s = "000" + QString::number(temp);
        }
        else if(temp >= 10 && temp < 100){
            tp_s = "00" + QString::number(temp);
        }
        else if(temp >= 100 && temp < 1000){
            tp_s = "0" + QString::number(temp);
        }
        else if(temp >= 1000 && temp < 10000){
            tp_s = QString::number(temp);
        }
        return tp_s;

    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

QString TramaVCPAP::obt_fr(){
    try {
        QString fr_s = "";
        int fr_int = frecuencia.toInt();
        if(fr_int >= 0 && fr_int < 10){
            fr_s = "00" + QString::number(fr_int);
        }
        else if(fr_int >= 10 && fr_int < 100){
            fr_s = "0" + QString::number(fr_int);
        }
        else if(fr_int >= 100 && fr_int < 1000){
            fr_s = QString::number(fr_int);
        }
        return fr_s;

    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

QString TramaVCPAP::obt_pwm(){
    try {
        int flujo_t = flujo.toInt();
        int temp = formulas->obtener_valor_pwm(flujo_t);
        QString s = "";
        if(temp >= 0 && temp < 10){
            s = "000" + QString::number(temp);
        }
        else if(temp >= 10 && temp < 100){
            s = "00" + QString::number(temp);
        }
        else if(temp >= 100 && temp < 1000){
            s = "0" + QString::number(temp);
        }
        else if(temp >= 1000 && temp < 10000){
            s = QString::number(temp);
        }
        return s;

    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

QString TramaVCPAP::obt_pwm_oxi(){
    try {
        int temp = oxigeno.toInt();
        int oxi = formulas->obtener_valor_pwm_oxigeno(temp);
        QString s = "";
        if(oxi >= 0 && oxi < 10){
            s = "000" + QString::number(oxi);
        }
        else if(oxi >= 10 && oxi < 100){
            s = "00" + QString::number(oxi);
        }
        else if(oxi >= 100 && oxi < 1000){
            s = "0" + QString::number(oxi);
        }
        else if(oxi >= 1000 && oxi < 10000){
            s = QString::number(oxi);
        }
        return s;

    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

QString TramaVCPAP::obt_pwm_aire(){
    try {
        int temp = oxigeno.toInt();
        int aire = formulas->obtener_valor_pwm_aire(temp);
        QString s = "";
        if(aire >= 0 && aire < 10){
            s = "000" + QString::number(aire);
        }
        else if(aire >= 10 && aire < 100){
            s = "00" + QString::number(aire);
        }
        else if(aire >= 100 && aire < 1000){
            s = "0" + QString::number(aire);
        }
        else if(aire >= 1000 && aire < 10000){
            s = QString::number(aire);
        }
        return s;

    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

QString TramaVCPAP::obt_pinsp(){
    try {
        return "000";
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

QString TramaVCPAP::obt_peep(){
    try {
        QString peep_s = "";
        int peep_int = cpap.toInt();
        if(peep_int >= 0 && peep_int < 10){
            peep_s = "00" + cpap;
        }
        else if(peep_int >= 10 && peep_int < 100){
            peep_s = "0" + cpap;
        }
        else if(peep_int >= 100 && peep_int < 1000){
            peep_s = cpap;
        }
        return peep_s;

    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

QString TramaVCPAP::obt_psoporte(){
    try {
        QString ps_s = "";
        int ps_int = ps.toInt();
        if(ps_int >= 0 && ps_int < 10){
            ps_s = "00" + ps;
        }
        else if(ps_int >= 10 && ps_int < 100){
            ps_s = "0" + ps;
        }
        else if(ps_int >= 100 && ps_int < 1000){
            ps_s = ps;
        }
        return ps_s;

    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

QString TramaVCPAP::obt_palarmax(){
    try {          
        QString pmax_s = "";
        int flujo_prog = flujo.toInt();
        int pmax_int = palarmax.toInt();
        if(flujo_prog > 25){
            pmax_int = pmax_int + (flujo_prog * 0.29) - 7.75;
        }

        if(pmax_int >= 0 && pmax_int < 10){
            pmax_s = "00" + QString::number(pmax_int);
        }
        else if(pmax_int >= 10 && pmax_int < 100){
            pmax_s = "0" + QString::number(pmax_int);
        }
        else if(pmax_int >= 100 && pmax_int < 1000){
            pmax_s = QString::number(pmax_int);
        }
        return pmax_s;

    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

QString TramaVCPAP::obt_estado(){
    try {
        return "0";

    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

