#include "uiqwidgetmenugrafica.h"

UiQWidgetMenuGrafica::UiQWidgetMenuGrafica(QWidget *parent) : QWidget(parent)
{
    try {
        estiloBotonA = "QPushButton { border: 2px solid rgb(255,112,61); background-color: gray; border-radius: 5px; color: black; margin-left: 2px; padding-left: 4px; padding-right: 4px}";
        estiloBotonI = "QPushButton { border: 2px solid rgb(145,145,145); background-color: rgb(145,145,145); border-radius: 5px; color: black; margin-left: 2px; padding-left: 4px; padding-right: 4px}";

        horizontalLayout =  new QHBoxLayout(this);
        horizontalLayout->setContentsMargins(0,0,0,0);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");

        btncontrolgrafica =  new QPushButton(this);
        fuente = new QFont;
        fuente->setFamily("Futura Md BT");
        fuente->setPointSize(12);
        fuente->setBold(true);
        fuente->setWeight(75);
        btncontrolgrafica->setFont(*fuente);
        btncontrolgrafica->setStyleSheet(estiloBotonA);
        btncontrolgrafica->setObjectName("btncontrolgrafica");
        sizePolicy = new QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy->setHorizontalStretch(0);
        sizePolicy->setVerticalStretch(0);
        sizePolicy->setHeightForWidth(btncontrolgrafica->sizePolicy().hasHeightForWidth());
        btncontrolgrafica->setSizePolicy(*sizePolicy);
        horizontalLayout->addWidget(btncontrolgrafica);

        btntipografica =  new QPushButton(this);
        btntipografica->setFont(*fuente);
        btntipografica->setStyleSheet(estiloBotonI);
        btntipografica->setObjectName("btntipografica");
        sizePolicy = new QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy->setHorizontalStretch(0);
        sizePolicy->setVerticalStretch(0);
        sizePolicy->setHeightForWidth(btntipografica->sizePolicy().hasHeightForWidth());
        btntipografica->setSizePolicy(*sizePolicy);
        horizontalLayout->addWidget(btntipografica);

        horizontalLayout->setStretch(0,1);
        horizontalLayout->setStretch(1,1);

        estadomostrargrafica = true;
        estadotipografica = false;

        btnsel = 0;
        retranslateUi();
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void UiQWidgetMenuGrafica::retranslateUi(){
    try {
        btncontrolgrafica->setText("PAUSAR\nGRAFICA");
        btntipografica->setText("LAZOS");
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void UiQWidgetMenuGrafica::ocultar(){
    try {
        hide();
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void UiQWidgetMenuGrafica::mostrar(){
    try {
        show();
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

bool UiQWidgetMenuGrafica::cambiar_mostrar_grafica(){
    try {
        if(estadomostrargrafica){
            estadomostrargrafica = false;
            btncontrolgrafica->setText("MOSTRAR\nGRAFICA");
        }
        else{
            estadomostrargrafica = true;
            btncontrolgrafica->setText("PAUSAR\nGRAFICA");
        }
        return estadomostrargrafica;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return false;
    }
}

bool UiQWidgetMenuGrafica::cambiar_tipo_grafica(){
    try {
        if(estadotipografica){
            estadotipografica = false;
            btntipografica->setText("LAZOS");
        }
        else{
            estadotipografica = true;
            btntipografica->setText("ONDAS");
        }
        return estadotipografica;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return false;
    }
}

int UiQWidgetMenuGrafica::seleccionar_boton(){
    try {
        if(btnsel == 0){
            btnsel = 1;
            btncontrolgrafica->setStyleSheet(estiloBotonI);
            btntipografica->setStyleSheet(estiloBotonA);
        }
        else{
            btnsel = 0;
            btncontrolgrafica->setStyleSheet(estiloBotonA);
            btntipografica->setStyleSheet(estiloBotonI);
        }
        return btnsel;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return 0;
    }
}
