#include "alarmaqw.h"

AlarmaQW::AlarmaQW(QWidget *parent, QString nombre, QString etiqueta, QString unidad, Monitor * monitor) : QWidget(parent)
{
    try {
        this->nombre = nombre;
        this->etiqueta = etiqueta;
        this->unidad = unidad;
        resize(110,330);
        resolu = 0;
        this->monitor = monitor;

        limMax = 100;
        limMin = 0;
        valueMax = float(limMax/2.0);
        valueMin = float(limMin/2.0);
        tipo = 0;
        idMax = 1;
        idMin = 2;

        eleActivo = 0;
        alaActiva = false;

        estiloETB = "QLabel { color: black; font-size: 12px ; font-style:bold; font-weight: bold;}";
        estiloETW = "QLabel { color: white; font-size: 12px ; font-style:bold; font-weight: bold;}";

        letiqueta = new QLabel(this);
        letiqueta->setGeometry(QRect(2, 20, 105, 20));
        letiqueta->setStyleSheet("color: white; font-size: 14px ; font-style:bold; font-weight: bold;");
        letiqueta->setAlignment(Qt::AlignCenter);
        letiqueta->setObjectName("letiqueta");
        letiqueta->setText(etiqueta);

        lunidad = new QLabel(this);
        lunidad->setGeometry(QRect(2, 40, 105, 20));
        lunidad->setStyleSheet("color: white; font-size: 12px ; font-style:bold; font-weight: bold;");
        lunidad->setAlignment(Qt::AlignCenter);
        lunidad->setObjectName("lunidad");
        lunidad->setText(unidad);

        bmaximo = new QRoundProgressBarAlarm(this);
        bmaximo->setGeometry(QRect(2, 70, 105, 105));
        bmaximo->setObjectName("bmaximo");
        bmaximo->setRange(limMin, limMax);
        bmaximo->setOutlinePenWidth(15);
        bmaximo->setDataPenWidth(10);
        bmaximo->setUnit("MAX");
        bmaximo->setStyleSheet("font-style:bold; font-weight: bold");
        bmaximo->setValue(valueMax);

        escala = new QLabel(this);
        escala->setGeometry(QRect(2, 190, 105, 20));
        escala->setStyleSheet(estiloETB);
        escala->setAlignment(Qt::AlignCenter);
        escala->setObjectName("escala");
        escala->setText("U");

        bminimo = new QRoundProgressBarAlarm(this);
        bminimo->setGeometry(QRect(2, 220, 105, 105));
        bminimo->setObjectName("bminimo");
        bminimo->setRange(limMin, limMax);
        bminimo->setOutlinePenWidth(15);
        bminimo->setDataPenWidth(10);
        bminimo->setUnit("MIN");
        bminimo->setStyleSheet("font-style:bold; font-weight: bold");
        bminimo->setValue(valueMin);

    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void AlarmaQW::setTipo(int tipo){
    try {
        this->tipo = tipo;
        if(this->tipo == 0){
            valueMax = limMax / 2.0;
            valueMin = limMin / 2.0;
        }
        else if(this->tipo == 1){
            valueMax = static_cast<int>(limMax / 2);
            valueMin = static_cast<int>(limMin / 2);
        }
        bmaximo->setValue(valueMax);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

QString AlarmaQW::IDTOSTR(int idObjeto){
    try {
        QString strTemp = "";
        if(idObjeto == 0){
            strTemp = "RESET";
        }
        else if(idObjeto == 1){
            strTemp = "GUARDAR";
        }
        else if(idObjeto == 2){
            strTemp = "PRE-MAX";
        }
        else if(idObjeto == 3){
            strTemp = "PRE-MIN";
        }
        else if(idObjeto == 4){
            strTemp = "VOLM-MAX";
        }
        else if(idObjeto == 5){
            strTemp = "VOLM-MIN";
        }
        else if(idObjeto == 6){
            strTemp = "FTO-MAX";
        }
        else if(idObjeto == 7){
            strTemp = "FTO-MIN";
        }
        else if(idObjeto == 8){
            strTemp = "VTI-MAX";
        }
        else if(idObjeto == 9){
            strTemp = "VTI-MIN";
        }
        else if(idObjeto == 10){
            strTemp = "APNEA";
        }
        return strTemp;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

void AlarmaQW::setIDS(int idMX, int IdMin){
    try {
        this->idMax = idMX;
        this->idMin = IdMin;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

std::pair<float, float> AlarmaQW::getValores(){
    try {
        //qDebug() << "AlarmaQW::getValores : " + QString::number(valueMax,'f',1) + " - " + QString::number(valueMin, 'f', 1);
        return std::make_pair(valueMax, valueMin);
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return std::make_pair(0, 0);
    }
}

void AlarmaQW::setActivo(int eleActivo){
    try {
        alaActiva = true;
        this->eleActivo = eleActivo;
        actualizarFoco();
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void AlarmaQW::actualizarFoco(){
    try {
        if(eleActivo == idMax){
            bminimo->setInactive();
            bmaximo->setActive();
        }
        else if(eleActivo == idMin){
            bmaximo->setInactive();
            bminimo->setActive();
        }

        escala->setStyleSheet(estiloETW);
        if(tipo == 0){
            resolu = 0;
            escala->setText("+ 0.1");
        }
        else{
            resolu = 1;
            escala->setText("+ 1");
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

bool AlarmaQW::activo(){
    try {
        return alaActiva;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void AlarmaQW::setInactivo(){
    try {
        alaActiva = false;
        eleActivo = 0;
        escala->setStyleSheet(estiloETB);
        bmaximo->setInactive();
        bminimo->setInactive();
        if(tipo == 0){
            resolu = 0;
        }
        else{
            resolu = 1;
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void AlarmaQW::setLimMax(int max){
    try {
        limMax = max;
        bmaximo->setRange(limMin, limMax);
        bminimo->setRange(limMin, limMax);
        valueMax = float(limMax/2.0);
        valueMin = float(limMin/2.0);
        bmaximo->setValue(valueMax);
        bminimo->setValue(valueMin);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void AlarmaQW::setLimMin(int min){
    try {
        limMin = min;
        bmaximo->setRange(limMin, limMax);
        bminimo->setRange(limMin, limMax);
        bmaximo->setValue(static_cast<int>(limMax/2.0));
        bminimo->setValue(static_cast<int>(limMin/2.0));
        valueMax = float(limMax/2.0);
        valueMin = float(limMin/2.0);
        bmaximo->setValue(valueMax);
        bminimo->setValue(valueMin);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void AlarmaQW::setMaxValue(float value){
    try {
        valueMax = value;
        bmaximo->setValue(valueMax);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void AlarmaQW::setMinValue(float value){
    try {
        valueMin = value;
        bminimo->setValue(valueMin);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

float AlarmaQW::getMaxValue(){
    try {
        return bmaximo->value();
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return 0;
    }
}

float AlarmaQW::getMinValue(){
    try {
        return bminimo->value();
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return 0;
    }
}

void AlarmaQW::teclado(QString tecla){
    try {
        if(tecla == "mod"){
            if(eleActivo == idMax || eleActivo == idMin){
                mod();
            }
        }
        else if(tecla == "mas"){
            if(eleActivo == idMax or eleActivo == idMin){
                if(monitor->sentido_giro){
                    menos();
                }
                else{
                    mas();
                }
            }
        }
        else if(tecla == "men"){
            if(eleActivo == idMax or eleActivo == idMin){
                if(monitor->sentido_giro){
                    mas();
                }
                else{
                    menos();
                }
            }
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void AlarmaQW::mas(){
    try {
        if(eleActivo == idMax){
            float valTemp = valueMax;
            if(resolu == 0){
                if(valTemp + 0.1 <= limMax){
                    valueMax += 0.1;
                }
            }
            else if(resolu ==1){
                if(valTemp + 1 <= limMax){
                    valueMax += 1;
                }
            }
            else if(resolu ==2){
                if(valTemp + 10 <= limMax){
                    valueMax += 10;
                }
            }
            else if(resolu ==3){
                if(valTemp + 100 <= limMax){
                    valueMax += 100;
                }
            }
            bmaximo->setValue(valueMax);
        }
        else if(eleActivo == idMin){
            float valTemp = valueMin;
            float valMax = valueMax;
            if(resolu == 0){
                if(valTemp + 0.1 <= valMax){
                    valueMin += 0.1;
                }
            }
            else if(resolu ==1){
                if(valTemp + 1 <= valMax){
                    valueMin += 1;
                }
            }
            else if(resolu ==2){
                if(valTemp + 10 <= valMax){
                    valueMin += 10;
                }
            }
            else if(resolu ==3){
                if(valTemp + 100 <= valMax){
                    valueMin += 100;
                }
            }
            bminimo->setValue(valueMin);
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void AlarmaQW::menos(){
    try {
        if(eleActivo == idMax){
            float valTemp = valueMax;
            float valMin = valueMin;
            if(resolu == 0){
                if(valTemp - 0.1 >= valMin){
                    valueMax -= 0.1;
                }
            }
            else if(resolu ==1){
                if(valTemp - 1 >= valMin){
                    valueMax -= 1;
                }
            }
            else if(resolu ==2){
                if(valTemp - 10 >= valMin){
                    valueMax -= 10;
                }
            }
            else if(resolu ==3){
                if(valTemp - 100 >= valMin){
                    valueMax -= 100;
                }
            }
            bmaximo->setValue(valueMax);
        }
        else if(eleActivo == idMin){
            float valTemp = valueMin;
            if(resolu == 0){
                if(valTemp - 0.1 >= limMin){
                    valueMin -= 0.1;
                }
            }
            else if(resolu ==1){
                if(valTemp - 1 >= limMin){
                    valueMin -= 1;
                }
            }
            else if(resolu ==2){
                if(valTemp - 10 >= limMin){
                    valueMin -= 10;
                }
            }
            else if(resolu ==3){
                if(valTemp - 100 >= limMin){
                    valueMin -= 100;
                }
            }
            bminimo->setValue(valueMin);
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void AlarmaQW::mod(){
    try {
        //qDebug() << "mod-tipo: " + QString::number(tipo);
        if(tipo == 0){
            if(resolu == 0){
                resolu = 1;
                escala->setText("+ 1");
            }
            else if(resolu == 1){
                resolu = 2;
                escala->setText("+ 10");
            }
            else if(resolu == 2){
                resolu = 3;
                escala->setText("+ 100");
            }
            else if(resolu == 3){
                resolu = 0;
                escala->setText("+ 0.1");
            }
        }
        else if(tipo == 1){
            if(resolu == 1){
                resolu = 2;
                escala->setText("+ 10");
            }
            else if(resolu == 2){
                resolu = 3;
                escala->setText("+ 100");
            }
            else if(resolu == 3){
                resolu = 1;
                escala->setText("+ 1");
            }
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}
