#include "infoalarma.h"

InfoAlarma::InfoAlarma(QWidget *parent) : QWidget(parent)
{
    try {
        this->padre = parent;
        setObjectName("InfoAlarma");
        resize(200,35);
        setStyleSheet("color: white");
        tiempo = new QLabel(this);
        tiempo->setGeometry(QRect(75, 5, 80, 20));

        fuente = new QFont;
        fuente->setPointSize(12);
        fuente->setBold(true);
        fuente->setWeight(75);
        tiempo->setFont(*fuente);
        tiempo->setAlignment(Qt::AlignCenter);
        tiempo->setScaledContents(true);
        tiempo->setObjectName("tiempo");
        tiempo->setText("01:00");
        tiempo->hide();
        icono = new QLabel(this);
        icono->setGeometry(QRect(25, 0, 30, 30));
        icono->setText("");
        icono->setPixmap(QPixmap("graficos/alarmd40b.png"));
        icono->setScaledContents(true);
        icono->setObjectName("icono");
        icono->hide();

        //retranslateUi();
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void InfoAlarma::muestra(){
    try {
        icono->show();
        tiempo->setText("01:00");
        tiempo->show();
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void InfoAlarma::oculta(){
    try {
        icono->hide();
        tiempo->hide();
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void InfoAlarma::actualiza(QString valor){
    try {
        tiempo->setText(valor);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

/*void InfoAlarma::retranslateUi(){
    try {

    }  catch (...) {

    }
}*/
