#include "uiconfigmodo.h"

UiConfigModo::UiConfigModo(QWidget *parent) : QWidget(parent)
{
    try {
        setStyleSheet("color: white;");

        btn = "QPushButton { border: 2px solid gray; border-radius: 5px; color: white; background-color: rgb(43,42,41);}";
        btnSeleccionado = "QPushButton { border: 4px solid rgb(255,112,61); border-radius: 5px; color: white; background-color: rgb(43,42,41);}";
        btnSeleccionadoWidget = "QPushButton { border: 1px solid rgb(255,112,61); border-radius: 5px; color: white; background-color: rgb(43,42,41);}"
                                "QPushButton:checked { background-color: green; border: 4px solid rgb(255,112,61);"
                                "border-radius: 5px; color: white;}";
        btnNoSeleccionadoWidget = "QPushButton { border: 2px solid rgb(255,112,61); border-radius: 5px; color: white;}"
                                  "QPushButton:checked { background-color: green; border: 1px solid green;"
                                  "border-radius: 5px; color: white;}";

        fuente = new QFont;
        fuente->setPointSize(12);
        fuente->setBold(true);
        fuente->setWeight(75);

        btnPCMV = new QPushButton(this);
        btnPCMV->setGeometry(QRect(26, 10, 130, 35));
        fuente->setPointSize(14);
        btnPCMV->setFont(*fuente);
        btnPCMV->setCheckable(true);
        btnPCMV->setText("P/CMV");
        connect(btnPCMV, SIGNAL(clicked()), this, SLOT(abrir_modo_pcmv()));

        btnVCMV = new QPushButton(this);
        btnVCMV->setGeometry(QRect(176, 10, 130, 35));
        fuente->setPointSize(14);
        btnVCMV->setFont(*fuente);
        btnVCMV->setCheckable(true);
        btnVCMV->setText("V/CMV");
        connect(btnVCMV, SIGNAL(clicked()), this, SLOT(abrir_modo_vcmv()));

        btnPSIMV = new QPushButton(this);
        btnPSIMV->setGeometry(QRect(326, 10, 130, 35));
        fuente->setPointSize(14);
        btnPSIMV->setFont(*fuente);
        btnPSIMV->setCheckable(true);
        btnPSIMV->setText("P-SIMV");
        connect(btnPSIMV, SIGNAL(clicked()), this, SLOT(abrir_modo_psimv()));

        btnVSIMV = new QPushButton(this);
        btnVSIMV->setGeometry(QRect(476, 10, 130, 35));
        fuente->setPointSize(14);
        btnVSIMV->setFont(*fuente);
        btnVSIMV->setCheckable(true);
        btnVSIMV->setText("V-SIMV");
        connect(btnPSIMV, SIGNAL(clicked()), this, SLOT(abrir_modo_vsimv()));

        btnPCPAP = new QPushButton(this);
        btnPCPAP->setGeometry(QRect(626, 10, 130, 35));
        fuente->setPointSize(14);
        btnPCPAP->setFont(*fuente);
        btnPCPAP->setCheckable(true);
        btnPCPAP->setText("PCPAP");
        connect(btnPCPAP, SIGNAL(clicked()), this, SLOT(abrir_modo_pcpap()));

        btnVCPAP = new QPushButton(this);
        btnVCPAP->setGeometry(QRect(780, 10, 130, 35));
        fuente->setPointSize(14);
        btnVCPAP->setFont(*fuente);
        btnVCPAP->setCheckable(true);
        btnVCPAP->setText("VCPAP");
        connect(btnVCPAP, SIGNAL(clicked()), this, SLOT(abrir_modo_vcpap()));

        perillaPaso = 0.1;
        modoVentilador = false;
        conte_modo = new QStackedWidget(this);
        conte_modo->setGeometry(QRect(5, 50, 1010, 440));
        conte_modo->setObjectName("conte_modo");
        conte_modo->setStyleSheet("background-color: black;");

        modoPCMV = new UiModoPCMV;
        conte_modo->addWidget(modoPCMV);

        modoVCMV = new UiModoVCMV;
        conte_modo->addWidget(modoVCMV);

        modoPSIMV = new UiModoPSIMV;
        conte_modo->addWidget(modoPSIMV);

        modoVSIMV = new UiModoVSIMV;
        conte_modo->addWidget(modoVSIMV);

        modoPCPAP = new UiModoPCPAP;
        conte_modo->addWidget(modoPCPAP);

        modoVCPAP = new UiModoVCPAP;
        conte_modo->addWidget(modoVCPAP);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }

}

void UiConfigModo::paintEvent(QPaintEvent* /*event*/)
{
    try {
        QStyleOption * opt = new QStyleOption;
        opt->initFrom(this);
        QPainter * p = new QPainter(this);
        this->style()->drawPrimitive(QStyle::PE_Widget, opt, p, this);
        p->end();
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiConfigModo::abrir_modo_pcmv(){
    try {
        conte_modo->setCurrentWidget(modoPCMV);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiConfigModo::abrir_modo_vcmv(){
    try {
        conte_modo->setCurrentWidget(modoVCMV);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiConfigModo::abrir_modo_psimv(){
    try {
        conte_modo->setCurrentWidget(modoPSIMV);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiConfigModo::abrir_modo_vsimv(){
    try {
        conte_modo->setCurrentWidget(modoVSIMV);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiConfigModo::abrir_modo_pcpap(){
    try {
        conte_modo->setCurrentWidget(modoPCPAP);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiConfigModo::abrir_modo_vcpap(){
    try {
        conte_modo->setCurrentWidget(modoVCPAP);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiConfigModo::boton_activo(int numero){
    try {
        if(numero == 1){
            if(conte_modo->currentWidget() == modoPCMV){
                btnPCMV->setStyleSheet(btnSeleccionadoWidget);
            }
            else{
                btnPCMV->setStyleSheet(btnSeleccionado);
            }
        }
        else if(numero == 2){
            if(conte_modo->currentWidget() == modoVCMV){
                btnVCMV->setStyleSheet(btnSeleccionadoWidget);
            }
            else{
                btnVCMV->setStyleSheet(btnSeleccionado);
            }
        }
        else if(numero == 3){
            if(conte_modo->currentWidget() == modoPSIMV){
                btnPSIMV->setStyleSheet(btnSeleccionadoWidget);
            }
            else{
                btnPSIMV->setStyleSheet(btnSeleccionado);
            }
        }
        else if(numero == 4){
            if(conte_modo->currentWidget() == modoVSIMV){
                btnVSIMV->setStyleSheet(btnSeleccionadoWidget);
            }
            else{
                btnVSIMV->setStyleSheet(btnSeleccionado);
            }
        }
        else if(numero == 5){
            if(conte_modo->currentWidget() == modoPCPAP){
                btnPCPAP->setStyleSheet(btnSeleccionadoWidget);
            }
            else{
                btnPCPAP->setStyleSheet(btnSeleccionado);
            }
        }
        else if(numero == 6){
            if(conte_modo->currentWidget() == modoVCPAP){
                btnVCPAP->setStyleSheet(btnSeleccionadoWidget);
            }
            else{
                btnVCPAP->setStyleSheet(btnSeleccionado);
            }
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiConfigModo::boton_inactivo(int numero){
    try {
        if(numero == 1){
            if(conte_modo->currentWidget() == modoPCMV){
                btnPCMV->setStyleSheet(btnNoSeleccionadoWidget);
            }
            else{
                btnPCMV->setStyleSheet(btn);
            }
        }
        else if(numero == 2){
            if(conte_modo->currentWidget() == modoVCMV){
                btnVCMV->setStyleSheet(btnNoSeleccionadoWidget);
            }
            else{
                btnVCMV->setStyleSheet(btn);
            }
        }
        else if(numero == 3){
            if(conte_modo->currentWidget() == modoPSIMV){
                btnPSIMV->setStyleSheet(btnNoSeleccionadoWidget);
            }
            else{
                btnPSIMV->setStyleSheet(btn);
            }
        }
        else if(numero == 4){
            if(conte_modo->currentWidget() == modoVSIMV){
                btnVSIMV->setStyleSheet(btnNoSeleccionadoWidget);
            }
            else{
                btnVSIMV->setStyleSheet(btn);
            }
        }
        else if(numero == 5){
            if(conte_modo->currentWidget() == modoPCPAP){
                btnPCPAP->setStyleSheet(btnNoSeleccionadoWidget);
            }
            else{
                btnPCPAP->setStyleSheet(btn);
            }
        }
        else if(numero == 6){
            if(conte_modo->currentWidget() == modoVCPAP){
                btnVCPAP->setStyleSheet(btnNoSeleccionadoWidget);
            }
            else{
                btnVCPAP->setStyleSheet(btn);
            }
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiConfigModo::boton_checked(int numero, bool estado){
    try {
        if(numero == 1){
            btnPCMV->setChecked(estado);
        }
        else if(numero == 2){
            btnVCMV->setChecked(estado);
        }
        else if(numero == 3){
            btnPSIMV->setChecked(estado);
        }
        else if(numero == 4){
            btnVSIMV->setChecked(estado);
        }
        else if(numero == 5){
            btnPCPAP->setChecked(estado);
        }
        else if(numero == 6){
            btnVCPAP->setChecked(estado);
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}
