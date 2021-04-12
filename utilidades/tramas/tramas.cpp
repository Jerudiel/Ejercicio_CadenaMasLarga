#include "tramas.h"

Tramas::Tramas()
{
    try {
        modo = 0;

        formulas = new Formulas;

        trama_PCMV = new TramaPCMV(formulas);
        trama_alarmas = new TramaAlarmas;
        trama_VCMV = new TramaVCMV(formulas);
        trama_PSIMV = new TramaPSIMV(formulas);
        trama_VSIMV = new TramaVSIMV(formulas);
        trama_PCPAP = new TramaPCPAP(formulas);
        trama_VCPAP = new TramaVCPAP(formulas);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Tramas::set_modo(int modo)
{
    try {
        this->modo = modo;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Tramas::llenar_modo(int modo, QStringList parametros, QString alarpmax)
{
    try {
        if(modo == 0){
            trama_PCMV->llenar(parametros, alarpmax);
        }
        else if(modo == 1){
            trama_VCMV->llenar(parametros, alarpmax);
        }
        else if(modo == 2){
            trama_PSIMV->llenar(parametros, alarpmax);
        }
        else if(modo == 3){
            trama_VSIMV->llenar(parametros, alarpmax);
        }
        else if(modo == 4){
            trama_PCPAP->llenar(parametros, alarpmax);
        }
        else if(modo == 5){
            trama_VCPAP->llenar(parametros, alarpmax);
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Tramas::llenar_alarmas(QStringList parametros)
{
    try {
        this->trama_alarmas->llenar(parametros);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

QString Tramas::obtener_trama_serpresion_config(int modo)
{
    try {
        //qDebug() << "obtener_trama_serpresion_config, mod: " + QString::number(modo);
        if(modo == 0){
            return trama_PCMV->obtener_trama_serpresion_config();
        }
        else if(modo == 1){
            return trama_VCMV->obtener_trama_serpresion_config();
        }
        else if(modo == 2){
            return trama_PSIMV->obtener_trama_serpresion_config();
        }
        else if(modo == 3){
            return trama_VSIMV->obtener_trama_serpresion_config();
        }
        else if(modo == 4){
            return trama_PCPAP->obtener_trama_serpresion_config();
        }
        else if(modo == 5){
            return trama_VCPAP->obtener_trama_serpresion_config();
        }
        else{
            return "";
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

QString Tramas::obtener_trama_alarmas()
{
    try {
        return trama_alarmas->obtener_trama();
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

QString Tramas::obtener_trama_ventilador(int modo)
{
    try {
        if(modo == 0){
            return trama_PCMV->obtener_trama_ventilador();
        }
        else if(modo == 1){
            return trama_VCMV->obtener_trama_ventilador();
        }
        else if(modo == 2){
            return trama_PSIMV->obtener_trama_ventilador();
        }
        else if(modo == 3){
            return trama_VSIMV->obtener_trama_ventilador();
        }
        else if(modo == 4){
            return trama_PCPAP->obtener_trama_ventilador();
        }
        else if(modo == 5){
            return trama_VCPAP->obtener_trama_ventilador();
        }
        else{
            return "";
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

void Tramas::actualizar_formulas(QString porce_cambio, QString ls_aire, QString li_aire, QString ls_o2, QString li_o2)
{
    try {
        formulas->actualizar_fio2(porce_cambio, ls_aire, li_aire, ls_o2, li_o2);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}
