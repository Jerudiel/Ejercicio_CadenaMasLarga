#include "tramapcmv.h"

#include "utilidades/formulas.h"

TramaPCMV::TramaPCMV(Formulas *formulas)
{
    try {
        pinsp = "";
        ipap = "";
        peep = "";
        fr = "";
        tinsp = "";
        tincr = "";
        oxigeno = "";
        mod_trigger = "";
        trigger_flujo = "";
        trigger_presion = "";
        palarmax = "";
        //formulas = new Formulas;
        this->formulas = formulas;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void TramaPCMV::llenar(QStringList parametros, QString alarpmax){
    try {
        pinsp = parametros.at(1);
        ipap = parametros.at(2);
        peep = parametros.at(3);
        fr = parametros.at(4);
        tinsp = parametros.at(5);
        tincr = parametros.at(6);
        oxigeno = parametros.at(7);
        mod_trigger = parametros.at(8);
        trigger_flujo = parametros.at(9);
        trigger_presion = parametros.at(10);
        palarmax = alarpmax;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }

}

QString TramaPCMV::obtener_trama_serpresion_config(){
    try {
        QString modo = "0";
        QString t_pinsp = obtener_pinsp();
        QString t_peep = obtener_peep();
        QString t_fr = obtener_fr();
        QString t_tinsp = obtener_tinsp();
        QString t_oxigeno = obtener_fio2();
        QString t_mod_trigger = obtener_modo_trigger();
        QString t_sensibilidad = obtener_sensibilidad();
        QString t_tincr = obtener_tincr();
        //unir
        QString trama = "C" + modo + t_pinsp + t_peep + t_fr + t_tinsp + t_oxigeno + t_mod_trigger + t_sensibilidad + t_tincr + "\n";
        if(trama.size() == 22){
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

QString TramaPCMV::obtener_pinsp(){
    try {
        QString pinsp_s = "";
        int pinsp_int = pinsp.toInt();
        if(pinsp_int >= 0 && pinsp_int < 10){
            pinsp_s = "00" + pinsp;
        }
        else if(pinsp_int >= 10 && pinsp_int < 100){
            pinsp_s = "0" + pinsp;
        }
        else if(pinsp_int >= 100 && pinsp_int < 1000){
            pinsp_s = pinsp;
        }
        return pinsp_s;

    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

QString TramaPCMV::obtener_peep(){
    try {
        QString peep_s = "";
        int peep_int = peep.toInt();
        if(peep_int >= 0 && peep_int < 10){
            peep_s = "0" + peep;
        }
        else if(peep_int >= 10 && peep_int < 100){
            peep_s = peep;
        }
        return peep_s;

    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

QString TramaPCMV::obtener_fr(){
    try {
        QString fr_s = "";
        int fr_int = fr.toInt();
        if(fr_int >= 0 && fr_int < 10){
            fr_s = "0" + fr;
        }
        else if(fr_int >= 10 && fr_int < 100){
            fr_s = fr;
        }
        return fr_s;

    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

QString TramaPCMV::obtener_tinsp(){
    try {
        QString tinsp_s = "";
        int tinsp_int = static_cast<int>(tinsp.toFloat()*10);
        if(tinsp_int >= 0 && tinsp_int < 10){
            tinsp_s = "00" + QString::number(tinsp_int);
        }
        else if(tinsp_int >= 10 && tinsp_int < 100){
            tinsp_s = "0" + QString::number(tinsp_int);
        }
        else if(tinsp_int >= 100 && tinsp_int < 1000){
            tinsp_s = QString::number(tinsp_int);
        }
        return tinsp_s;

    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

QString TramaPCMV::obtener_fio2(){
    try {
        QString oxi_s = "";
        int oxi_int = oxigeno.toInt();
        if(oxi_int >= 0 && oxi_int < 10){
            oxi_s = "00" + QString::number(oxi_int);
        }
        else if(oxi_int >= 10 && oxi_int < 100){
            oxi_s = "0" + QString::number(oxi_int);
        }
        else if(oxi_int >= 100 && oxi_int < 1000){
            oxi_s = QString::number(oxi_int);
        }
        return oxi_s;

    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

QString TramaPCMV::obtener_modo_trigger(){
    try {
        if(mod_trigger == "1"){
            return "1";
        }
        else{
            return "0";
        }
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

QString TramaPCMV::obtener_sensibilidad(){
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

QString TramaPCMV::obtener_tincr(){
    try {
        QString tincr_s = "";
        int tincr_int = static_cast<int>(tincr.toFloat()*10);
        if(tincr_int >= 0 && tincr_int < 10){
            tincr_s = "00" + QString::number(tincr_int);
        }
        else if(tincr_int >= 10 && tincr_int < 100){
            tincr_s = "0" + QString::number(tincr_int);
        }
        else if(tincr_int >= 100 && tincr_int < 1000){
            tincr_s = QString::number(tincr_int);
        }
        return tincr_s;

    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

QString TramaPCMV::obtener_trama_ventilador(){
    try {
        QString modo = "0";
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
        //unir
        QString trama = "M" + modo + t_ti + t_tp + t_te + t_fr + t_pwm + t_pwm_oxi + t_pwm_aire + t_fio2 + t_pinsp + t_peep + t_psoporte + t_palarmax + t_estado + "\n";
        if(trama.size() == 46){
            return trama;
        }
        else{
            qDebug() << "[TRAMA PCMV] trama incorrecta M: " + trama;
            qDebug() << "[TRAMA PCMV] longitud: " + QString::number(trama.size());
            return "";
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

QString TramaPCMV::obt_ti(){
    try {
        QString ti_s = "";
        int ti_int = static_cast<int>(tinsp.toFloat()*100);
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

QString TramaPCMV::obt_tp(){
    try {
        return "0000";

    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

QString TramaPCMV::obt_te(){
    try {
        QString te_s = "";
        float ti = tinsp.toFloat();
        float periodo = 60 / fr.toFloat();
        int temp = static_cast<int>((periodo - ti) * 100);
        if(temp >= 0 && temp < 10){
            te_s = "000" + QString::number(temp);
        }
        else if(temp >= 10 && temp < 100){
            te_s = "00" + QString::number(temp);
        }
        else if(temp >= 100 && temp < 1000){
            te_s = "0" + QString::number(temp);
        }
        else if(temp >= 1000 && temp < 10000){
            te_s = QString::number(temp);
        }
        return te_s;

    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

QString TramaPCMV::obt_fr(){
    try {
        QString fr_s = "";
        int fr_int = fr.toInt();
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

QString TramaPCMV::obt_pwm(){
    try {
        int temp = formulas->get_pwm_max();
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

QString TramaPCMV::obt_pwm_oxi(){
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

QString TramaPCMV::obt_pwm_aire(){
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

QString TramaPCMV::obt_pinsp(){
    try {
        QString pinsp_s = "";
        int pinsp_int = pinsp.toInt();
        if(pinsp_int >= 0 && pinsp_int < 10){
            pinsp_s = "00" + pinsp;
        }
        else if(pinsp_int >= 10 && pinsp_int < 100){
            pinsp_s = "0" + pinsp;
        }
        else if(pinsp_int >= 100 && pinsp_int < 1000){
            pinsp_s = pinsp;
        }
        return pinsp_s;

    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

QString TramaPCMV::obt_peep(){
    try {
        QString peep_s = "";
        int peep_int = peep.toInt();
        if(peep_int >= 0 && peep_int < 10){
            peep_s = "00" + peep;
        }
        else if(peep_int >= 10 && peep_int < 100){
            peep_s = "0" + peep;
        }
        else if(peep_int >= 100 && peep_int < 1000){
            peep_s = peep;
        }
        return peep_s;

    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

QString TramaPCMV::obt_psoporte(){
    try {
        return "000";

    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

QString TramaPCMV::obt_palarmax(){
    try {
        QString pmax_s = "";
        int pmax_int = palarmax.toInt();
        if(pmax_int >= 0 && pmax_int < 10){
            pmax_s = "00" + palarmax;
        }
        else if(pmax_int >= 10 && pmax_int < 100){
            pmax_s = "0" + palarmax;
        }
        else if(pmax_int >= 100 && pmax_int < 1000){
            pmax_s = palarmax;
        }
        return pmax_s;

    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

QString TramaPCMV::obt_estado(){
    try {
        return "0";

    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}
