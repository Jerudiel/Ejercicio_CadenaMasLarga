#include "tramaalarmas.h"

TramaAlarmas::TramaAlarmas()
{
    try {
        fr_max = "";
        fr_min = "";
        vol_max = "";
        vol_min = "";
        volmin_max = "";
        volmin_min = "";
        pres_max = "";
        pres_min = "";
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void TramaAlarmas::llenar(QStringList parametros){
    try {
        pres_max = parametros.at(1);
        pres_min = parametros.at(2);
        volmin_max = parametros.at(3);
        volmin_min = parametros.at(4);
        fr_max = parametros.at(5);
        fr_min = parametros.at(6);
        vol_max = parametros.at(7);
        vol_min = parametros.at(8);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

QString TramaAlarmas::obtener_trama(){
    try {
        fr_max = obtener_fr_max();
        //qDebug() << "fr_max: " + fr_max;
        fr_min = obtener_fr_min();
        //qDebug() << "fr_min: " + fr_min;
        vol_max = obtener_vol_max();
        //qDebug() << "vol_max: " + vol_max;
        vol_min = obtener_vol_min();
        //qDebug() << "vol_min: " + vol_min;
        volmin_max = obtener_volmin_max();
        //qDebug() << "volmin_max: " + volmin_max;
        volmin_min = obtener_volmin_min();
        //qDebug() << "volmin_min: " + volmin_min;
        pres_max = obtener_pres_max();
        //qDebug() << "pres_max: " + pres_max;
        pres_min = obtener_pres_min();
        //qDebug() << "pres_min: " + pres_min;

        QString trama = "W" + fr_max + fr_min + vol_max + vol_min + volmin_max + volmin_min + pres_max + pres_min + "\n";
        if(trama.size() == 25){
            //qDebug() << "obtener_trama: " + trama;
            return trama;
        }
        else{
            //qDebug() << "obtener_trama-error: " + trama + " size: " + QString::number(trama.size());
            trama = "";
            return trama;
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

QString TramaAlarmas::obtener_fr_max(){
    try {
        QString fr_max_s = "";
        int fr_max_int = fr_max.toInt();
        qDebug() << "val int fr_max: " + QString::number(fr_max_int);
        if(fr_max_int >= 0 && fr_max_int < 10){
            fr_max_s = "0" + fr_max;
        }
        else if(fr_max_int >= 10 && fr_max_int < 100){
            fr_max_s = fr_max;
        }
        return fr_max_s;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

QString TramaAlarmas::obtener_fr_min(){
    try {
        QString fr_min_s = "";
        int fr_min_int = fr_min.toInt();
        if(fr_min_int >= 0 && fr_min_int < 10){
            fr_min_s = "0" + fr_min;
        }
        else if(fr_min_int >= 10 && fr_min_int < 100){
            fr_min_s = fr_min;
        }
        return fr_min_s;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

QString TramaAlarmas::obtener_vol_max(){
    try {
        QString vol_max_s = "";
        int vol_max_int = vol_max.toInt();
        if(vol_max_int >= 0 && vol_max_int < 10){
            vol_max_s = "000" + vol_max;
        }
        else if(vol_max_int >= 10 && vol_max_int < 100){
            vol_max_s = "00" + vol_max;
        }
        else if(vol_max_int >= 100 && vol_max_int < 1000){
            vol_max_s = "0" + vol_max;
        }
        else if(vol_max_int >= 1000 && vol_max_int < 10000){
            vol_max_s = vol_max;
        }
        return vol_max_s;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

QString TramaAlarmas::obtener_vol_min(){
    try {
        QString vol_min_s = "";
        int vol_min_int = vol_min.toInt();
        if(vol_min_int >= 0 && vol_min_int < 10){
            vol_min_s = "000" + vol_min;
        }
        else if(vol_min_int >= 10 && vol_min_int < 100){
            vol_min_s = "00" + vol_min;
        }
        else if(vol_min_int >= 100 && vol_min_int < 1000){
            vol_min_s = "0" + vol_min;
        }
        else if(vol_min_int >= 1000 && vol_min_int < 10000){
            vol_min_s = vol_min;
        }
        return vol_min_s;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

QString TramaAlarmas::obtener_volmin_max(){
    try {
        QString volmin_max_s = "";
        int volmin_max_int = static_cast<int>(volmin_max.toFloat()*10);
        if(volmin_max_int >= 0 && volmin_max_int < 10){
            volmin_max_s = "00" + QString::number(volmin_max_int);
        }
        else if(volmin_max_int >= 10 && volmin_max_int < 100){
            volmin_max_s = "0" + QString::number(volmin_max_int);;
        }
        else if(volmin_max_int >= 100 && volmin_max_int < 1000){
            volmin_max_s = QString::number(volmin_max_int);;
        }
        return volmin_max_s;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

QString TramaAlarmas::obtener_volmin_min(){
    try {
        QString volmin_min_s = "";
        int volmin_min_int = static_cast<int>(volmin_min.toFloat()*10);
        if(volmin_min_int >= 0 && volmin_min_int < 10){
            volmin_min_s = "00" + QString::number(volmin_min_int);
        }
        else if(volmin_min_int >= 10 && volmin_min_int < 100){
            volmin_min_s = "0" + QString::number(volmin_min_int);
        }
        else if(volmin_min_int >= 100 && volmin_min_int < 1000){
            volmin_min_s = QString::number(volmin_min_int);
        }
        return volmin_min_s;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

QString TramaAlarmas::obtener_pres_max(){
    try {
        QString pres_max_s = "";
        int pres_max_int = pres_max.toInt();
        if(pres_max_int >= 0 && pres_max_int < 10){
            pres_max_s = "00" + pres_max;
        }
        else if(pres_max_int >= 10 && pres_max_int < 100){
            pres_max_s = "0" + pres_max;
        }
        else if(pres_max_int >= 100 && pres_max_int < 1000){
            pres_max_s = pres_max;
        }
        return pres_max_s;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

QString TramaAlarmas::obtener_pres_min(){
    try {
        QString pres_min_s = "";
        int pres_min_int = pres_min.toInt();
        if(pres_min_int >= 0 && pres_min_int < 10){
            pres_min_s = "0" + pres_min;
        }
        else if(pres_min_int >= 10 && pres_min_int < 100){
            pres_min_s = pres_min;
        }
        return pres_min_s;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}


