#include "widgetparametro.h"

WidgetParametro::WidgetParametro(QWidget *parent, QString nombre, QString unidad, float lim_sup, float lim_inf, QString resolucion, float valor, int id, int tipo, bool salto) : QWidget(parent)
{
    try {
        this->nombre = nombre;
        this->lim_sup = lim_sup;
        this->lim_inf = lim_inf;
        this->resolucion = resolucion;
        perilla = resolucion.toFloat();
        this->valor = valor;
        this->id = id;
        this->tipo = tipo;
        this->salto = salto;
        this->unidad = unidad;
        setStyleSheet("background-color: black;");
        boxLayout = new QVBoxLayout(this);
        boxLayout->setContentsMargins(3,3,3,3);
        boxLayout->setSpacing(3);
        boxLayout->setObjectName("boxLayout");
        label_title = new QLabel(this);
        fuente = new QFont;
        fuente->setPointSize(14);
        fuente->setBold(true);
        fuente->setWeight(75);
        label_title->setFont(*fuente);
        label_title->setAlignment(Qt::AlignCenter);
        label_title->setObjectName("label_title");
        label_title->setStyleSheet("color: white;");
        boxLayout->addWidget(label_title);
        horizontalLayout = new QHBoxLayout;
        horizontalLayout->setContentsMargins(20,0,5,0);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName("horizontalLayout");
        bar = new QRoundProgressBarAlarm(this);
        bar->setObjectName("bar");
        bar->setOutlinePenWidth(15);
        bar->setDataPenWidth(10);
        bar->setFormat("%d");
        set_tipo();
        bar->setRange(lim_inf, lim_sup);
        bar->setValue(valor);
        bar->setUnit(unidad);
        bar->update();
        bar->setStyleSheet("font-style:bold; font-weight: bold;");
        verticalLayout = new QVBoxLayout(bar);
        verticalLayout->setContentsMargins(5,5,5,5);
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout->addWidget(bar);
        boxLayout->addLayout(horizontalLayout);
        boxLayout->setStretch(0,1);
        boxLayout->setStretch(1,3);
        retranslateUi();

        /*if(resolucion == "0.1"){
            qDebug() << nombre + " resolucion 0.1 ----";
        }
        else{
            qDebug() << nombre + " resolucion: " + resolucion;
            //qDebug() << "Resta: " + QString::number(0.1-resolucion,'f',5);
        }*/

    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void WidgetParametro::set_tipo(){
    try {
        if(tipo == 0){
            bar->setDecimals(0);
        }
        else{
            bar->setDecimals(1);
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void WidgetParametro::set_lim_sup(float valor){
    try {
        lim_sup = valor;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void WidgetParametro::set_lim_inf(float valor){
    try {
        lim_inf = valor;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

bool WidgetParametro::sumar(){
    try {
        //qDebug() << "suma -widgetparametro - valor: " + QString::number(valor, 'f', 2);
        //qDebug() << "suma -widgetparametro - perilla: " + QString::number(perilla, 'f', 2);
        //qDebug() << "suma -widgetparametro - lim_sup: " + QString::number(lim_sup, 'f', 2);
        if(valor + perilla <= lim_sup){
            if(salto && static_cast<int>(valor) == 0){
                valor = 5.0; //round(5,1)
                bar->setValue(valor);
            }
            else{
                valor = (QString::number(valor + perilla, 'f', 1)).toFloat();
                bar->setValue(valor);
            }
            return true;
        }
        else{
            return false;
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return false;
    }
}

bool WidgetParametro::restar(){
    try {
        if(valor - perilla >= lim_inf){
            if(salto && valor - perilla < 5){
                valor = 0.0;
                bar->setValue(valor);
            }
            else{
                valor = (QString::number(valor - perilla, 'f', 1)).toFloat();
                bar->setValue(valor);
            }
            return true;
        }
        else{
            return false;
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return false;
    }
}

float WidgetParametro::cambiar_perilla(){
    try {
        if(QString::number(perilla,'f',1) == "0.1"){
            if(lim_sup > 1){
                perilla = 1;
            }
        }
        else if(QString::number(perilla,'f',1)  == "1.0"){
            if(lim_sup > 10){
                perilla = 10;
            }
            else if(resolucion == "0.1"){
                perilla = 0.1;
            }
        }
        else if(QString::number(perilla,'f',1)  == "10.0"){
            if(lim_sup > 100){
                perilla = 100;
            }
            else if(resolucion == "0.1"){
                perilla = 0.1;
            }
            else{
                perilla = 1;
            }
        }
        else if(QString::number(perilla,'f',1)  == "100.0"){
            if(resolucion == "0.1"){
                perilla = 0.1;
            }
            else{
                perilla = 1;
            }
        }
        return perilla;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return 1;
    }
}

void WidgetParametro::activo(){
    try {
        bar->setActive();
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void WidgetParametro::inactivo(){
    try {
        bar->setInactive();
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

float WidgetParametro::get_valor(){
    try {
        if(resolucion == "0.1"){
            //qDebug() << "get_valor : " + resolucion;
            return (QString::number(valor, 'f', 1)).toFloat();
        }
        else{
            //qDebug() << "get_valor int: " + resolucion;
            return static_cast<int>(valor);
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return 1;
    }
}

void WidgetParametro::set_valor(QString valor){
    try {
        if(lim_inf <= valor.toFloat() && valor.toFloat() <= lim_sup){
            this->valor = valor.toFloat();
            bar->setValue(this->valor);
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void WidgetParametro::retranslateUi(){
    try {
        label_title->setText(nombre);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}
