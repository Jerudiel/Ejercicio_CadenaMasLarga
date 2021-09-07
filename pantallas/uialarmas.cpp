#include "uialarmas.h"

UiAlarmas::UiAlarmas(Monitor *monitor, QWidget *parent) : QWidget(parent)
{
    try {
        //MainWindow *mainwindow,
        //this->mainwindow = mainwindow;
        this->monitor = monitor;

        estiloBTInactivo = "QPushButton { background-color: rgb(43,42,41); border-radius: 5px;\n"
                           "border: 2px solid grey; color: white; font-size: 18px ; font-style:bold; font-weight: bold;}";
        estiloBTActivo = "QPushButton { background-color: rgb(43,42,41); border-radius: 5px;\n"
                         "border: 4px solid rgb(255,112,61); color: white; font-size: 18px ; font-style:bold; font-weight: bold;}";
        estiloMSGA = "color: white; font-size: 12px ; font-style:bold; font-weight: bold; background-color: black; border: 1px solid black;}";
        estiloMSGI = "color: white; font-size: 12px ; font-style:bold; font-weight: bold; background-color: black; border: 1px solid black;}";

        centralwidget = new QWidget(this);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setStyleSheet("background-color: rgb(0, 0, 0);");

        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setGeometry(QRect(0, 25, 1031, 601));
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");

        principalLayout = new QHBoxLayout(horizontalLayoutWidget);
        principalLayout->setContentsMargins(0,0,0,0);
        principalLayout->setSpacing(1);
        principalLayout->setObjectName("principalLayout");

        contenidoLayout = new QVBoxLayout;
        contenidoLayout->setContentsMargins(-1,0,-1,-1);
        contenidoLayout->setSpacing(2);
        contenidoLayout->setObjectName("contenidoLayout");

        informacionLayout = new QHBoxLayout;
        informacionLayout->setSpacing(3);
        informacionLayout->setObjectName("informacionLayout");

        UsuarioLayout = new QVBoxLayout;
        UsuarioLayout->setObjectName("UsuarioLayout");

        label_Modo = new QLabel(horizontalLayoutWidget);

        fuente = new QFont;
        fuente->setPointSize(16);
        fuente->setBold(true);

        label_Modo->setFont(*fuente);
        label_Modo->setStyleSheet("color: rgb(255, 255, 255);");
        label_Modo->setObjectName("label_Modo");
        UsuarioLayout->addWidget(label_Modo);
        informacionLayout->addLayout(UsuarioLayout);

        BotonesLayout = new QHBoxLayout;
        BotonesLayout->setObjectName("BotonesLayout");
        informacionLayout->addLayout(BotonesLayout);

        label_fecha = new QLabel(horizontalLayoutWidget);
        fuente->setPointSize(12);
        label_fecha->setFont(*fuente);
        label_fecha->setStyleSheet("color: rgb(255, 255, 255);");
        label_fecha->setAlignment(Qt::AlignCenter);
        label_fecha->setObjectName("label_fecha");
        informacionLayout->addWidget(label_fecha);

        tempMon = new Temperatura(horizontalLayoutWidget, this->monitor);

        informacionLayout->addWidget(tempMon);
        informacionLayout->setStretch(0,3);
        informacionLayout->setStretch(1,3);
        informacionLayout->setStretch(2,3);
        informacionLayout->setStretch(3,1);
        informacionLayout->setStretch(4,1);
        contenidoLayout->addLayout(informacionLayout);

        graficaLayout = new QHBoxLayout;
        graficaLayout->setObjectName("graficaLayout");

        widget = new QWidget(horizontalLayoutWidget);
        widget->setObjectName("widget");

        limiteMaxApn = 25;
        limiteMinApn = 1;
        limiteMaxVol = 2000;
        limiteMinVol = 100;
        limiteMaxPre = 150;
        limiteMinPre = 1;
        limiteMaxFre = 60;
        limiteMinFre = 5;
        limiteMinVolE = 1;
        limiteMaxVolE = 30;

        alarmaPRE = new AlarmaQW(widget, "Alarma PSU", "Presión","cmH2O",this->monitor);
        alarmaPRE->setGeometry(QRect(50,80,110,330));
        alarmaPRE->setLimMax(limiteMaxPre);
        alarmaPRE->setLimMin(limiteMinPre);
        alarmaPRE->setIDS(2,3);
        alarmaPRE->setTipo(1);

        alarmaVOLM = new AlarmaQW(widget, "Alarma VOLM", "VolMinEsp","l/min",this->monitor);
        alarmaVOLM->setGeometry(QRect(210,80,110,330));
        alarmaVOLM->setLimMax(limiteMaxVolE);
        alarmaVOLM->setLimMin(limiteMinVolE);
        alarmaVOLM->setIDS(4,5);

        alarmaFTO = new AlarmaQW(widget, "Alarma FTO", "Frecuencia","r/min",this->monitor);
        alarmaFTO->setGeometry(QRect(370,80,110,330));
        alarmaFTO->setLimMax(limiteMaxFre);
        alarmaFTO->setLimMin(limiteMinFre);
        alarmaFTO->setIDS(6,7);
        alarmaFTO->setTipo(1);

        alarmaVTI = new AlarmaQW(widget, "Alarma VTI", "vt","ml",this->monitor);
        alarmaVTI->setGeometry(QRect(530,80,110,330));
        alarmaVTI->setLimMax(limiteMaxVol);
        alarmaVTI->setLimMin(limiteMinVol);
        alarmaVTI->setIDS(8,9);
        alarmaVTI->setTipo(1);

        resetValores = new QPushButton(widget);
        resetValores->setGeometry(QRect(90, 10, 200, 60));
        resetValores->setObjectName("resetValores");
        resetValores->setStyleSheet(estiloBTInactivo);
        connect(resetValores, SIGNAL(clicked()), this, SLOT(resetValoresDefault()));

        guardarCambios = new QPushButton(widget);
        guardarCambios->setGeometry(QRect(410, 10, 200, 60));
        guardarCambios->setObjectName("guardarCambios");
        guardarCambios->setStyleSheet(estiloBTInactivo);
        connect(guardarCambios, SIGNAL(clicked()), this, SLOT(guardaCambios()));

        graficaLayout->addWidget(widget);
        contenidoLayout->addLayout(graficaLayout);
        contenidoLayout->setStretch(0, 1);
        contenidoLayout->setStretch(1, 10);
        principalLayout->addLayout(contenidoLayout);
        principalLayout->setStretch(0,10);

        estadoMensajes = new QLabel(widget);
        estadoMensajes->setGeometry(QRect(150, 450, 600, 41));
        estadoMensajes->setStyleSheet(estiloMSGI);
        estadoMensajes->setAlignment(Qt::AlignCenter);
        estadoMensajes->setObjectName("estadoMensajes");

        valPMAX   = 0;
        valPMIN   = 0;
        valVMMAX  = 0;
        valVMMIN  = 0;
        valFTMAX  = 0;
        valFTMIN  = 0;
        valVTMAX  = 0;
        valVTMIN  = 0;
        valTAPNE  = 0;

        edoAPRE = "0";
        edoAVOM = "0";
        edoAFTO = "0";
        edoAVTI = "0";

        idObjeto = 0;
        activaReset(true);

        eleActivo = 1;

        retranslateUi();

        actualizaVentana();

        timerLimpiarInfo = new QTimer;
        timerLimpiarInfo->setSingleShot(true);
        connect(timerLimpiarInfo, SIGNAL(timeout()), this, SLOT(limpiar()));
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

/*void UiAlarmas::asignaPadre(MainWindow *mainwindow){
    try {
        this->mainwindow = mainwindow;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}*/

void UiAlarmas::mostrarMensaje(QString mensaje){
    try {
        estadoMensajes->setText(mensaje);
        if(timerLimpiarInfo->isActive()){
            timerLimpiarInfo->stop();
        }
        timerLimpiarInfo->start(5000);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiAlarmas::limpiar(){
    try {
    estadoMensajes->setText("");
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

QString UiAlarmas::IDTOSTR(int idObjeto){
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
        return strTemp;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

void UiAlarmas::actualizaVentana(){
    try {
        idObjeto = 0;
        resetTodo();
        cargaConfiguracion();
        actualizaFocoObjeto();
        estadoMensajes->setText("");
        label_Modo->setText(monitor->modoVentilador);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiAlarmas::resetTodo(){
    try {
        alarmaPRE->setInactivo();
        alarmaVOLM->setInactivo();
        alarmaFTO->setInactivo();
        alarmaVTI->setInactivo();

        resetValores->setStyleSheet(estiloBTInactivo);
        guardarCambios->setStyleSheet(estiloBTInactivo);

    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiAlarmas::cargaValoresDB(QStringList valores){
    try {
        if(valores.size() == 14){
            valPMAX = valores.at(1).toInt();
            valPMIN = valores.at(2).toInt();
            alarmaPRE->setMaxValue(valPMAX);
            alarmaPRE->setMinValue(valPMIN);

            valVMMAX = valores.at(3).toFloat();
            valVMMIN = valores.at(4).toFloat();
            alarmaVOLM->setMaxValue(valVMMAX);
            alarmaVOLM->setMinValue(valVMMIN);

            valFTMAX = valores.at(5).toInt();
            valFTMIN = valores.at(6).toInt();
            alarmaFTO->setMaxValue(valFTMAX);
            alarmaFTO->setMinValue(valFTMIN);

            valVTMAX = valores.at(7).toInt();
            valVTMIN = valores.at(8).toInt();
            alarmaVTI->setMaxValue(valVTMAX);
            alarmaVTI->setMinValue(valVTMIN);
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiAlarmas::resetValoresDefault(){
    try {
        QString conf_default = monitor->consul->cargar_config_default_alarm();
        if(conf_default == ""){
            qDebug() << "[UI ALARMAS] No hay parametros por default en la bd";
        }
        else{
            QStringList conf_default_list = conf_default.split(",");
            if(conf_default_list.size() == 14){
                cargaValoresDB(conf_default_list);
            }
            else{
                qDebug() << "[UI ALARMAS] Numero de elementos incorrecto , base de datos no actualizada";
            }
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiAlarmas::cargaConfiguracion(){
    try {
        QString ultima_conf = monitor->consul->buscar_ult_config_alarm();
        if(ultima_conf != ""){
            QStringList ultima_conf_list = ultima_conf.split(",");
            if(ultima_conf_list.size() == 14){
                cargaValoresDB(ultima_conf_list);
            }
        }
        else{
            QString conf_default = monitor->consul->cargar_config_default_alarm();
            if(conf_default == ""){
                qDebug() << "[UI ALARMAS] No hay datos por default en la bd";
            }
            else{
                QStringList conf_default_list = conf_default.split(",");
                if(conf_default_list.size() == 14){
                    cargaValoresDB(conf_default_list);
                }
            }
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiAlarmas::guardaCambios(){
    try {
         /*std::make_pair(valPMAX, valPMIN) = alarmaPRE->getValores();
         std::make_pair(valVMMAX, valVMMIN) = alarmaVOLM->getValores();
         std::make_pair(valFTMAX, valFTMIN) = alarmaFTO->getValores();
         std::make_pair(valVTMAX, valVTMIN) = alarmaVTI->getValores();*/
         valPMAX = alarmaPRE->getMaxValue();
         valPMIN = alarmaPRE->getMinValue();
         valVMMAX = alarmaVOLM->getMaxValue();
         valVMMIN = alarmaVOLM->getMinValue();
         valFTMAX = alarmaFTO->getMaxValue();
         valFTMIN = alarmaFTO->getMinValue();
         valVTMAX = alarmaVTI->getMaxValue();
         valVTMIN = alarmaVTI->getMinValue();
         valTAPNE = 10;
         /*qDebug() << "guardaCambios-valPMAX: " + QString::number(valPMAX,'f',1);
         qDebug() << "guardaCambios-valPMIN: " + QString::number(valPMIN,'f',1);
         qDebug() << "guardaCambios-valVMMAX: " + QString::number(valVMMAX,'f',1);
         qDebug() << "guardaCambios-valVMMIN: " + QString::number(valVMMIN,'f',1);
         qDebug() << "guardaCambios-valFTMAX: " + QString::number(valFTMAX,'f',1);
         qDebug() << "guardaCambios-valFTMIN: " + QString::number(valFTMIN,'f',1);
         qDebug() << "guardaCambios-valVTMAX: " + QString::number(valVTMAX,'f',1);
         qDebug() << "guardaCambios-valVTMIN: " + QString::number(valVTMIN,'f',1);
         qDebug() << "guardaCambios-valTAPNE: " + QString::number(valTAPNE,'f',1);*/

         bool resultado = monitor->consul->guardar_config_ultima_alarm(QString::number(valPMAX),QString::number(valPMIN),QString::number(valVMMAX,'f',1),QString::number(valVMMIN,'f',1),QString::number(valFTMAX),QString::number(valFTMIN),QString::number(valVTMAX),QString::number(valVTMIN),edoAPRE,edoAVOM,edoAFTO,edoAVTI,QString::number(valTAPNE));
         if(resultado){
             //estadoMensajes->setText("CAMBIOS GUARDADOS");
             mostrarMensaje("CAMBIOS GUARDADOS");
             monitor->consul->agregar_evento("Alarmas", monitor->obtener_modo(), "Se guardaron cambios en alarmas", monitor->obtener_parametros());
         }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

/*void UiAlarmas::verificarConfiguracion(){
    try {

    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}*/

void UiAlarmas::teclado(QString tecla){
    try {
        if(tecla == "arr"){
            arriba();
        }
        else if(tecla == "aba"){
            abajo();
        }
        else if(tecla == "izq"){
            moverIzq();
        }
        else if(tecla == "der"){
            moverDer();
        }
        else if(tecla == "ok"){
            if(idObjeto == 0){
                resetValoresDefault();
                guardaCambios();
            }
            else if(idObjeto == 1){
                guardaCambios();
            }
        }
        else if(tecla == "mod"){
            enviaTecladoAlarma(tecla);
        }
        else if(tecla == "mas"){
            enviaTecladoAlarma(tecla);
        }
        else if(tecla == "men"){
            enviaTecladoAlarma(tecla);
        }
        /*else if(tecla == "mon"){
            mainwindow->startMonitor();
        }*/

    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiAlarmas::arriba(){
    try {
        if(idObjeto == 0){
            idObjeto = 3;
        }
        else if(idObjeto ==1){
            idObjeto = 7;
        }
        else if(idObjeto ==2){
            idObjeto = 0;
        }
        else if(idObjeto ==3){
            idObjeto = 2;
        }
        else if(idObjeto ==4){
            idObjeto = 0;
        }
        else if(idObjeto ==5){
            idObjeto = 4;
        }
        else if(idObjeto ==6){
            idObjeto = 1;
        }
        else if(idObjeto ==7){
            idObjeto = 6;
        }
        else if(idObjeto ==8){
            idObjeto = 1;
        }
        else if(idObjeto ==9){
            idObjeto = 8;
        }
        actualizaFocoObjeto();
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiAlarmas::abajo(){
    try {
        if(idObjeto == 0){
            idObjeto = 2;
        }
        else if(idObjeto ==1){
            idObjeto = 6;
        }
        else if(idObjeto ==2){
            idObjeto = 3;
        }
        else if(idObjeto ==3){
            idObjeto = 0;
        }
        else if(idObjeto ==4){
            idObjeto = 5;
        }
        else if(idObjeto ==5){
            idObjeto = 0;
        }
        else if(idObjeto ==6){
            idObjeto = 7;
        }
        else if(idObjeto ==7){
            idObjeto = 1;
        }
        else if(idObjeto ==8){
            idObjeto = 9;
        }
        else if(idObjeto ==9){
            idObjeto = 1;
        }
        actualizaFocoObjeto();
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiAlarmas::moverIzq(){
    try {
        if(idObjeto == 0){
            idObjeto = 1;
        }
        else if(idObjeto ==1){
            idObjeto = 0;
        }
        else if(idObjeto ==2){
            idObjeto = 8;
        }
        else if(idObjeto ==3){
            idObjeto = 9;
        }
        else if(idObjeto ==4){
            idObjeto = 2;
        }
        else if(idObjeto ==5){
            idObjeto = 3;
        }
        else if(idObjeto ==6){
            idObjeto = 4;
        }
        else if(idObjeto ==7){
            idObjeto = 5;
        }
        else if(idObjeto ==8){
            idObjeto = 6;
        }
        else if(idObjeto ==9){
            idObjeto = 7;
        }
        actualizaFocoObjeto();
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiAlarmas::moverDer(){
    try {
        if(idObjeto == 0){
            idObjeto = 1;
        }
        else if(idObjeto ==1){
            idObjeto = 0;
        }
        else if(idObjeto ==2){
            idObjeto = 4;
        }
        else if(idObjeto ==3){
            idObjeto = 5;
        }
        else if(idObjeto ==4){
            idObjeto = 6;
        }
        else if(idObjeto ==5){
            idObjeto = 7;
        }
        else if(idObjeto ==6){
            idObjeto = 8;
        }
        else if(idObjeto ==7){
            idObjeto = 9;
        }
        else if(idObjeto ==8){
            idObjeto = 2;
        }
        else if(idObjeto ==9){
            idObjeto = 3;
        }
        actualizaFocoObjeto();
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiAlarmas::actualizaFocoObjeto(){
    try {
        if(idObjeto == 0){
            alarmaVOLM->setInactivo();
            alarmaPRE->setInactivo();
            activaGuardar(false);
            activaReset(true);
        }
        else if(idObjeto == 1){
            alarmaVTI->setInactivo();
            alarmaFTO->setInactivo();
            activaReset(false);
            activaGuardar(true);
        }
        else if(idObjeto == 2 || idObjeto == 3){
            alarmaVOLM->setInactivo();
            alarmaVTI->setInactivo();
            activaReset(false);
            alarmaPRE->setActivo(idObjeto);
        }
        else if(idObjeto == 4 || idObjeto == 5){
            alarmaFTO->setInactivo();
            alarmaPRE->setInactivo();
            activaReset(false);
            alarmaVOLM->setActivo(idObjeto);
        }
        else if(idObjeto == 6 || idObjeto == 7){
            alarmaVOLM->setInactivo();
            alarmaVTI->setInactivo();
            activaGuardar(false);
            alarmaFTO->setActivo(idObjeto);
        }
        else if(idObjeto == 8 || idObjeto == 9){
            alarmaFTO->setInactivo();
            alarmaPRE->setInactivo();
            activaGuardar(false);
            alarmaVTI->setActivo(idObjeto);
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiAlarmas::enviaTecladoAlarma(QString tecla){
    try {
        if((idObjeto == 2 || idObjeto == 3) && alarmaPRE->activo()){
            alarmaPRE->teclado(tecla);
        }
        if((idObjeto == 4 || idObjeto == 5) && alarmaVOLM->activo()){
            alarmaVOLM->teclado(tecla);
        }
        if((idObjeto == 6 || idObjeto == 7) && alarmaFTO->activo()){
            alarmaFTO->teclado(tecla);
        }
        if((idObjeto == 8 || idObjeto == 9) && alarmaVTI->activo()){
            alarmaVTI->teclado(tecla);
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiAlarmas::activaGuardar(bool estado){
    try {
        if(estado){
            guardarCambios->setStyleSheet(estiloBTActivo);
        }
        else{
            guardarCambios->setStyleSheet(estiloBTInactivo);
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiAlarmas::activaReset(bool estado){
    try {
        if(estado){
            resetValores->setStyleSheet(estiloBTActivo);
        }
        else{
            resetValores->setStyleSheet(estiloBTInactivo);
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiAlarmas::retranslateUi(){
    try {
        label_Modo->setText("Modo: Volumen");
        guardarCambios->setText("GUARDAR");
        resetValores->setText("RESETEAR");
        cargaConfiguracion();
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}
