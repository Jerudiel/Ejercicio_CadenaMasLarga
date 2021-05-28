#include "reloj.h"



Reloj::Reloj(): QWidget()
{
    try {
        //QDateTime dateTime = QDateTime::currentDateTime();
        //QString dateTimeString = dateTime.toString("yyyy-MM-dd hh:mm:ss.zzz");
        label_fechahora = nullptr;
        timer_hora = new QTimer;
        timer_hora->setInterval(1000);
        connect(timer_hora, SIGNAL(timeout()), this, SLOT(update()));
        timer_hora->start();
        this->color = "white";
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }

}

void Reloj::asignaLabel(QLabel *label_fechahora){
    try {
        this->label_fechahora = label_fechahora;
        this->label_fechahora->setStyleSheet("color: " + color + ";");
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Reloj::set_color_label(QString color){
    try {
        this->color = color;
        if(label_fechahora != nullptr){
            this->label_fechahora->setStyleSheet("color: " + color + ";");
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

/*void Reloj::start(){
    try {
        myhilo = new MyHilo(label_fechahora);
        myhilo->run();
    }  catch (...) {

    }
}*/

void Reloj::update(){
    try {
        QDateTime dateTime = QDateTime::currentDateTime();
        //QString dateTimeString = dateTime.toString("yy-MM-dd hh:mm:ss");
        QString dateTimeString = dateTime.toString("hh:mm:ss dd/MM/yy ");
        if(label_fechahora != nullptr){
            label_fechahora->setText(dateTimeString);
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}
