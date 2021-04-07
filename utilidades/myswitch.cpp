#include "myswitch.h"

MySwitch::MySwitch(QWidget * parent, QString on, QString off) : QPushButton(parent)
{
    try {
        setCheckable(true);
        setMinimumWidth(66);
        setMinimumHeight(22);
        seleccionado = false;
        this->on = on;
        this->off = off;
        bgcolor = new QColor(43,42,41);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void MySwitch::switchSel(bool estado){
    try {
        seleccionado = estado;
        update();
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void MySwitch::paintEvent(QPaintEvent* /*event*/){
    try {
        QString label = (isChecked()) ? on : off;
        QColor bg_color = (isChecked()) ? Qt::darkGreen : Qt::blue;

        int radius = 20;
        int width = 64;
        QPoint center = rect().center();

        QPainter * painter = new QPainter(this);
        painter->setRenderHint(QPainter::Antialiasing);
        painter->translate(center);
        painter->setBrush(*bgcolor);
        if(seleccionado){
            //qDebug() << "paintevent seleccionado";
            QPen * pen = new QPen(QColor(255,112,61));
            pen->setWidth(4);
            painter->setPen(*pen);
            painter->drawRoundedRect(QRect(-width, -radius, 2*width, 2*radius), radius, radius);
        }
        else{
            //qDebug() << "paintevent NO seleccioando";
            QPen * pen = new QPen(Qt::gray);
            pen->setWidth(2);
            painter->setPen(*pen);

            painter->drawRoundedRect(QRect(-width, -radius, 2*width, 2*radius), radius, radius);
        }
        QPen * pen = new QPen(Qt::gray);
        pen->setWidth(2);
        painter->setPen(*pen);
        painter->setBrush(QBrush(bg_color));
        QRect * sw_rect = new QRect(-radius, -radius, width + radius, 2*radius);
        if(! isChecked()){
            sw_rect->moveLeft(-width);
        }
        QPen * pen2 = new QPen(Qt::gray);
        pen2->setWidth(2);
        painter->setPen(*pen2);
        painter->drawRoundedRect(*sw_rect, radius, radius);
        QPen * pen3 = new QPen(Qt::white);
        pen3->setWidth(4);
        painter->setPen(*pen3);
        painter->drawText(*sw_rect, Qt::AlignCenter, label);
        painter->end();
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }

}

void MySwitch::ponerGeometry(QRect rectangulo){
    try {
     setGeometry(rectangulo);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void MySwitch::ponerChecked(bool var){
    try {
         setChecked(var);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

bool MySwitch::estaChecked(){
    try {
         return isChecked();
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return false;
    }
}

void MySwitch::actualizar(){
    try {
         update();
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}
