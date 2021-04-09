#include "uiconfiguracion.h"

UiConfiguracion::UiConfiguracion(Monitor * monitor, QWidget *parent) : QWidget(parent)
{
    try {
        this->monitor = monitor;
        setStyleSheet("QWidget{background-color: black; color:white;}"
                      "QPushButton{background-color: rgb(43,42,41);}"
                      "QTabBar::tab {color: white; background: black;} "
                      "QTabBar::tab:selected {color: black; background: grey;}"
                      "QLabel{color: white;}");
        btn = "QPushButton { border: 2px solid gray; border-radius: 5px; color: white;}";
        btnSeleccionado = "QPushButton { border: 4px solid rgb(255,112,61); border-radius: 5px; color: white;}";
        btnSeleccionadoWidget = "QPushButton { border: 1px solid rgb(255,112,61); border-radius: 5px; color: white;}"
                                "QPushButton:checked { background-color: green; border: 4px solid rgb(255,112,61);"
                                "border-radius: 5px; color: white;}";
        btnNoSeleccionadoWidget = "QPushButton { border: 2px solid rgb(255,112,61); border-radius: 5px; color: white;}"
                                  "QPushButton:checked { background-color: green; border: 1px solid green;"
                                  "border-radius: 5px; color: white;}";
        centralwidget = new QWidget(this);
        centralwidget->setObjectName("centralwidget");

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
        fuente->setBold(true);
        fuente->setPointSize(18);
        label_Modo->setFont(*fuente);
        label_Modo->setStyleSheet("color: rgb(255, 255, 255);");
        label_Modo->setObjectName("label_Modo");
        UsuarioLayout->addWidget(label_Modo);

        label_Version = new QLabel(horizontalLayoutWidget);
        fuente->setPointSize(10);
        label_Version->setFont(*fuente);
        label_Version->setObjectName("label_Version");
        UsuarioLayout->addWidget(label_Version);
        informacionLayout->addLayout(UsuarioLayout);

        BotonesLayout = new QHBoxLayout;
        BotonesLayout->setObjectName("BotonesLayout");

        btn_reini_config = new QPushButton(horizontalLayoutWidget);
        sizePolicy = new QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy->setHorizontalStretch(0);
        sizePolicy->setVerticalStretch(0);
        sizePolicy->setHeightForWidth(btn_reini_config->sizePolicy().hasHeightForWidth());
        btn_reini_config->setSizePolicy(*sizePolicy);
        btn_reini_config->setObjectName("btn_reini_config");
        fuente->setPointSize(16);
        fuente->setBold(true);
        btn_reini_config->setFont(*fuente);
        btn_reini_config->setStyleSheet(btn);
        connect(btn_reini_config, SIGNAL(released()), this, SLOT(reiniciaValoresModo()));
        BotonesLayout->addWidget(btn_reini_config);

        btn_eventos = new QPushButton(horizontalLayoutWidget);
        sizePolicy->setHorizontalStretch(0);
        sizePolicy->setVerticalStretch(0);
        sizePolicy->setHeightForWidth(btn_eventos->sizePolicy().hasHeightForWidth());
        btn_eventos->setSizePolicy(*sizePolicy);
        btn_eventos->setObjectName("btn_eventos");
        btn_eventos->setFont(*fuente);
        btn_eventos->setStyleSheet(btn);
        connect(btn_eventos, SIGNAL(released()), this, SLOT(abrir_pantalla_eventos())); //no se usa
        BotonesLayout->addWidget(btn_eventos);

        informacionLayout->addLayout(BotonesLayout);

        label_info_alarma =  new QLabel(horizontalLayoutWidget);
        fuente->setPointSize(12);
        label_info_alarma->setFont(*fuente);
        label_info_alarma->setStyleSheet("color: rgb(255, 255, 255);");
        label_info_alarma->setAlignment(Qt::AlignCenter);
        label_info_alarma->setObjectName("label_info_alarma");
        informacionLayout->addWidget(label_info_alarma);

        informacionLayout->setStretch(0, 3);
        informacionLayout->setStretch(1, 3);
        informacionLayout->setStretch(2, 3);
        informacionLayout->setStretch(3, 1);
        informacionLayout->setStretch(4, 1);
        contenidoLayout->addLayout(informacionLayout);

        graficaLayout = new QHBoxLayout;
        graficaLayout->setObjectName("graficaLayout");

        tabWidget = new QTabWidget(horizontalLayoutWidget);
        tabWidget->setObjectName("tabWidget");

        tab_config =  new QWidget;
        tab_config->setObjectName("tab_config");
        tabWidget->addTab(tab_config, "");

        //aqui se van a agregar los 4 tabs
        tab_info_sistema = new UiInfoSistema(this, monitor);
        tab_info_sistema->setObjectName("tab_info_sistema");
        tabWidget->addTab(tab_info_sistema, "");

        tab_calibrar = new UiCalibrar(this, monitor);
        tab_calibrar->setObjectName("tab_calibrar");
        tabWidget->addTab(tab_calibrar, "");

        tab_eventos = new UiEventos(this, monitor);
        tab_eventos->setObjectName("tab_eventos");
        tabWidget->addTab(tab_eventos, "");

        tab_datetime = new UiConfigDatetime(this, monitor);
        tab_datetime->setObjectName("tab_datetime");
        tabWidget->addTab(tab_datetime, "");



        mostrando_eventos = false;

        graficaLayout->addWidget(tabWidget);
        contenidoLayout->addLayout(graficaLayout);
        contenidoLayout->setStretch(0,1);
        contenidoLayout->setStretch(1,10);
        principalLayout->addLayout(contenidoLayout);
        principalLayout->setStretch(0,10);
        //crear la pantalla config
        configModo = new UiConfigModo(tab_config);

        retranslateUi();
        tabWidget->setCurrentIndex(0);
        connect(tabWidget, SIGNAL(currentChanged(int)), this, SLOT(cambioTab(int)));
        //QtCore.QMetaObject.connectSlotsByName(self)

        elementSel = 0;
        llenarConfiguracion();
        elementoSeleccionado();
        monitor->modoVentilador = "MODO: PCMV";
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiConfiguracion::retranslateUi(){
    try {
        label_Modo->setText("MODO: PCV");
        btn_reini_config->setText("REINICIAR VALORES");
        btn_eventos->setText(" EVENTOS ");

        tabWidget->setTabText(tabWidget->indexOf(tab_config), "CONFIGURACIÓN");
        tabWidget->setTabText(tabWidget->indexOf(tab_info_sistema), "SISTEMA");
        tabWidget->setTabText(tabWidget->indexOf(tab_calibrar), "CALIBRAR");
        tabWidget->setTabText(tabWidget->indexOf(tab_datetime), "FECHA");
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiConfiguracion::paintEvent(QPaintEvent* /*event*/)
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

void UiConfiguracion::cambioTab(int i){
    try {
        //tabWidget->indexOf(tab_datetime);
        if(i == tabWidget->indexOf(tab_info_sistema)){
            tab_info_sistema->cargarVersiones();
        }
        else if(i == tabWidget->indexOf(tab_calibrar)){
            tab_calibrar->calibraciones->tab_sensores->cargarFactores();
            tab_calibrar->calibraciones->tab_control->cargarFactores();
            tab_calibrar->calibraciones->tab_otros->cargarAltura();
            tab_calibrar->calibraciones->tab_otros->cargarTeclado();
            tab_calibrar->calibraciones->tab_otros->cargarFio2();
            tab_calibrar->calibraciones->tab_otros->cargarOffPip();
        }
        else if(i == tabWidget->indexOf(tab_datetime)){
            tab_datetime->cargarFecha();
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiConfiguracion::activarModoPCMV(){
    try {
        configModo->conte_modo->setCurrentWidget(configModo->modoPCMV);
        llenarConfiguracionPCMV();
        elementoSeleccionado();
        monitor->modoVentilador = "MODO: PCMV";
        label_Modo->setText(monitor->modoVentilador);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiConfiguracion::activarModoVCMV(){
    try {
        configModo->conte_modo->setCurrentWidget(configModo->modoVCMV);
        llenarConfiguracionVCMV();
        elementoSeleccionado();
        monitor->modoVentilador = "MODO: VCMV";
        label_Modo->setText(monitor->modoVentilador);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiConfiguracion::activarModoPSIMV(){
    try {
        configModo->conte_modo->setCurrentWidget(configModo->modoPSIMV);
        llenarConfiguracionPSIMV();
        elementoSeleccionado();
        monitor->modoVentilador = "MODO: PSIMV";
        label_Modo->setText(monitor->modoVentilador);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiConfiguracion::activarModoVSIMV(){
    try {
        configModo->conte_modo->setCurrentWidget(configModo->modoVSIMV);
        llenarConfiguracionVSIMV();
        elementoSeleccionado();
        monitor->modoVentilador = "MODO: VSIMV";
        label_Modo->setText(monitor->modoVentilador);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiConfiguracion::activarModoPCPAP(){
    try {
        configModo->conte_modo->setCurrentWidget(configModo->modoPCPAP);
        llenarConfiguracionPCPAP();
        elementoSeleccionado();
        monitor->modoVentilador = "MODO: PCPAP";
        label_Modo->setText(monitor->modoVentilador);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiConfiguracion::activarModoVCPAP(){
    try {
        configModo->conte_modo->setCurrentWidget(configModo->modoVCPAP);
        llenarConfiguracionVCPAP();
        elementoSeleccionado();
        monitor->modoVentilador = "MODO: VCPAP";
        label_Modo->setText(monitor->modoVentilador);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiConfiguracion::teclado(QString tecla){
    try {
        if(tecla == "aba" || tecla == "der" || tecla == "izq" || tecla == "arr"){
            if(mostrando_eventos){
                if(tecla == "aba"){
                    tab_eventos->bajar();
                }
                else if(tecla == "arr"){
                    tab_eventos->subir();
                }
            }
            else{
                mover(tecla);
            }
        }
        else if(tecla == "mod"){
            modo_perilla();
        }
        else if(tecla == "mas" || tecla == "men"){
            cambiarValor(tecla);
        }
        else if(tecla == "ok"){
            teclaOk();
        }
        else if(tecla == "can"){
            if(mostrando_eventos){
                tabWidget->setCurrentIndex(0);
                mostrando_eventos = false;
            }
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiConfiguracion::teclaOk(){
    try {
        if(elementSel == 0){
            reiniciaValoresModo();
        }
        else if(elementSel == 1){
            activarModoPCMV();
        }
        else if(elementSel == 2){
            activarModoVCMV();
        }
        else if(elementSel == 3){
            activarModoPSIMV();
        }
        else if(elementSel == 4){
            activarModoVSIMV();
        }
        else if(elementSel == 5){
            activarModoPCPAP();
        }
        else if(elementSel == 6){
            activarModoVCPAP();
        }
        else if(elementSel == 9){
            abrir_pantalla_eventos();
        }
        else{
            teclaOkModo();
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiConfiguracion::teclaOkModo(){
    try {
        if(configModo->conte_modo->currentWidget() == configModo->modoPCMV){
            if(configModo->modoPCMV->get_elemento_seleccionado() == 5){
                configModo->modoPCMV->switch_trigger();
                configModo->modoPCMV->cambiaTipoTrigger();
            }
            else if(configModo->modoPCMV->get_elemento_seleccionado() == 7){
                guardarConfigPCMV();
            }
        }
        else if(configModo->conte_modo->currentWidget() == configModo->modoVCMV){
            if(configModo->modoVCMV->get_elemento_seleccionado() == 6){
                configModo->modoVCMV->switch_trigger();
                configModo->modoVCMV->cambiaTipoTrigger();
            }
            else if(configModo->modoVCMV->get_elemento_seleccionado() == 8){
                guardarConfigVCMV();
            }
        }
        else if(configModo->conte_modo->currentWidget() == configModo->modoPSIMV){
            if(configModo->modoPSIMV->get_elemento_seleccionado() == 6){
                configModo->modoPSIMV->switch_trigger();
                configModo->modoPSIMV->cambiaTipoTrigger();
            }
            else if(configModo->modoPSIMV->get_elemento_seleccionado() == 8){
                guardarConfigPSIMV();
            }
        }
        else if(configModo->conte_modo->currentWidget() == configModo->modoVSIMV){
            if(configModo->modoVSIMV->get_elemento_seleccionado() == 7){
                configModo->modoVSIMV->switch_trigger();
                configModo->modoVSIMV->cambiaTipoTrigger();
            }
            else if(configModo->modoVSIMV->get_elemento_seleccionado() == 9){
                guardarConfigVSIMV();
            }
        }
        else if(configModo->conte_modo->currentWidget() == configModo->modoPCPAP){
            if(configModo->modoPCPAP->get_elemento_seleccionado() == 4){
                configModo->modoPCPAP->switch_trigger();
                configModo->modoPCPAP->cambiaTipoTrigger();
            }
            else if(configModo->modoPCPAP->get_elemento_seleccionado() == 9){
                guardarConfigPCPAP();
            }
        }
        else {
            if(configModo->modoVCPAP->get_elemento_seleccionado() == 4){
                configModo->modoVCPAP->switch_trigger();
                configModo->modoVCPAP->cambiaTipoTrigger();
            }
            else if(configModo->modoVCPAP->get_elemento_seleccionado() == 9){
                guardarConfigVCPAP();
            }
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiConfiguracion::reiniciaValoresModo(){
    try {
        if(configModo->conte_modo->currentWidget() == configModo->modoPCMV){
            monitor->consul->reiniciar_valores("PCMV");
        }
        else if(configModo->conte_modo->currentWidget() == configModo->modoVCMV){
            monitor->consul->reiniciar_valores("VCMV");
        }
        else if(configModo->conte_modo->currentWidget() == configModo->modoPSIMV){
            monitor->consul->reiniciar_valores("PSIMV");
        }
        else if(configModo->conte_modo->currentWidget() == configModo->modoVSIMV){
            monitor->consul->reiniciar_valores("VSIMV");
        }
        else if(configModo->conte_modo->currentWidget() == configModo->modoPCPAP){
            monitor->consul->reiniciar_valores("PCPAP");
        }
        else {
            monitor->consul->reiniciar_valores("VCPAP");
        }
        llenarConfiguracion();
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiConfiguracion::modo_perilla(){
    try {
        if(configModo->conte_modo->currentWidget() == configModo->modoPCMV){
            configModo->modoPCMV->cambiaPerilla();
        }
        else if(configModo->conte_modo->currentWidget() == configModo->modoVCMV){
             configModo->modoVCMV->cambiaPerilla();
        }
        else if(configModo->conte_modo->currentWidget() == configModo->modoPSIMV){
             configModo->modoPSIMV->cambiaPerilla();
        }
        else if(configModo->conte_modo->currentWidget() == configModo->modoVSIMV){
             configModo->modoVSIMV->cambiaPerilla();
        }
        else if(configModo->conte_modo->currentWidget() == configModo->modoPCPAP){
             configModo->modoPCPAP->cambiaPerilla();
        }
        else {
             configModo->modoVCPAP->cambiaPerilla();
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiConfiguracion::cambiarValor(QString tecla){
    try {
        if(tecla == "mas"){
            if(monitor->sentido_giro){
                restar2();
            }
            else{
                sumar2();
            }
        }
        else{
            if(monitor->sentido_giro){
                sumar2();
            }
            else{
                restar2();
            }
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiConfiguracion::sumar2(){
    try {
        if(elementSel == 8){
            if(configModo->conte_modo->currentWidget() == configModo->modoPCMV){
                configModo->modoPCMV->sumar();
            }
            else if(configModo->conte_modo->currentWidget() == configModo->modoVCMV){
                 configModo->modoVCMV->sumar();
            }
            else if(configModo->conte_modo->currentWidget() == configModo->modoPSIMV){
                 configModo->modoPSIMV->sumar();
            }
            else if(configModo->conte_modo->currentWidget() == configModo->modoVSIMV){
                 configModo->modoVSIMV->sumar();
            }
            else if(configModo->conte_modo->currentWidget() == configModo->modoPCPAP){
                 configModo->modoPCPAP->sumar();
            }
            else {
                 configModo->modoVCPAP->sumar();
            }
        }

    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiConfiguracion::restar2(){
    try {
        if(elementSel == 8){
            if(configModo->conte_modo->currentWidget() == configModo->modoPCMV){
                configModo->modoPCMV->restar();
            }
            else if(configModo->conte_modo->currentWidget() == configModo->modoVCMV){
                 configModo->modoVCMV->restar();
            }
            else if(configModo->conte_modo->currentWidget() == configModo->modoPSIMV){
                 configModo->modoPSIMV->restar();
            }
            else if(configModo->conte_modo->currentWidget() == configModo->modoVSIMV){
                 configModo->modoVSIMV->restar();
            }
            else if(configModo->conte_modo->currentWidget() == configModo->modoPCPAP){
                 configModo->modoPCPAP->restar();
            }
            else {
                 configModo->modoVCPAP->restar();
            }
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiConfiguracion::mover(QString tecla){
    try {
        if(tecla == "arr"){
            mover_arriba();
        }
        else if(tecla == "aba"){
            mover_abajo();
        }
        else if(tecla == "izq"){
            mover_izquierda();
        }
        else if(tecla == "der"){
            mover_derecha();
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiConfiguracion::mover_arriba(){
    try {
        if(elementSel == 0){
            elementSel = 8;
            boton_inactivo();
            ultimoencontenedor();
        }
        else if(elementSel == 1){
            elementSel = 0;
            configModo->boton_inactivo(1);
            boton_activo();
        }
        else if(elementSel == 2){
            elementSel = 0;
            configModo->boton_inactivo(2);
            boton_activo();
        }
        else if(elementSel == 3){
            elementSel = 0;
            configModo->boton_inactivo(3);
            boton_activo();
        }
        else if(elementSel == 4){
            elementSel = 0;
            configModo->boton_inactivo(4);
            boton_activo();
        }
        else if(elementSel == 5){
            elementSel = 0;
            configModo->boton_inactivo(5);
            boton_activo();
        }
        else if(elementSel == 6){
            elementSel = 0;
            configModo->boton_inactivo(6);
            boton_activo();
        }
        else if(elementSel == 9){

        }
        else{
            seleccionar_dentro_modo("arr");
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiConfiguracion::mover_abajo(){
    try {
        if(elementSel == 0){
            elementSel = 4;
            boton_inactivo();
            configModo->boton_activo(4);
        }
        else if(elementSel == 1){
            elementSel = 8;
            configModo->boton_inactivo(1);
            ir_a_contenedor(1);
        }
        else if(elementSel == 2){
            elementSel = 8;
            configModo->boton_inactivo(2);
            ir_a_contenedor(2);
        }
        else if(elementSel == 3){
            elementSel = 8;
            configModo->boton_inactivo(3);
            ir_a_contenedor(3);
        }
        else if(elementSel == 4){
            elementSel = 8;
            configModo->boton_inactivo(4);
            ir_a_contenedor(4);
        }
        else if(elementSel == 5){
            elementSel = 8;
            configModo->boton_inactivo(5);
            ir_a_contenedor(5);
        }
        else if(elementSel == 6){
            elementSel = 8;
            configModo->boton_inactivo(6);
            ir_a_contenedor(6);
        }
        else if(elementSel == 9){

        }
        else{
            seleccionar_dentro_modo("aba");
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiConfiguracion::mover_derecha(){
    try {
        if(elementSel == 0){
            elementSel = 9;
            boton_inactivo();
            boton_e_activo();
        }
        else if(elementSel == 1){
            elementSel = 2;
            configModo->boton_inactivo(1);
            configModo->boton_activo(2);
        }
        else if(elementSel == 2){
            elementSel = 3;
            configModo->boton_inactivo(2);
            configModo->boton_activo(3);
        }
        else if(elementSel == 3){
            elementSel = 4;
            configModo->boton_inactivo(3);
            configModo->boton_activo(4);
        }
        else if(elementSel == 4){
            elementSel = 5;
            configModo->boton_inactivo(4);
            configModo->boton_activo(5);
        }
        else if(elementSel == 5){
            elementSel = 6;
            configModo->boton_inactivo(5);
            configModo->boton_activo(6);
        }
        else if(elementSel == 6){
            elementSel = 1;
            configModo->boton_inactivo(6);
            configModo->boton_activo(1);
        }
        else if(elementSel == 9){
            elementSel = 0;
            boton_activo();
            boton_e_inactivo();
        }
        else{
            seleccionar_dentro_modo("der");
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiConfiguracion::mover_izquierda(){
    try {
        if(elementSel == 0){
            elementSel = 9;
            boton_inactivo();
            boton_e_activo();
        }
        else if(elementSel == 1){
            elementSel = 6;
            configModo->boton_inactivo(1);
            configModo->boton_activo(6);
        }
        else if(elementSel == 2){
            elementSel = 1;
            configModo->boton_inactivo(2);
            configModo->boton_activo(1);
        }
        else if(elementSel == 3){
            elementSel = 2;
            configModo->boton_inactivo(3);
            configModo->boton_activo(2);
        }
        else if(elementSel == 4){
            elementSel = 3;
            configModo->boton_inactivo(4);
            configModo->boton_activo(3);
        }
        else if(elementSel == 5){
            elementSel = 4;
            configModo->boton_inactivo(5);
            configModo->boton_activo(4);
        }
        else if(elementSel == 6){
            elementSel = 5;
            configModo->boton_inactivo(6);
            configModo->boton_activo(5);
        }
        else if(elementSel == 9){
            elementSel = 0;
            boton_activo();
            boton_e_inactivo();
        }
        else{
            seleccionar_dentro_modo("izq");
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiConfiguracion::boton_activo(){
    try {
        btn_reini_config->setStyleSheet(btnSeleccionado);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiConfiguracion::boton_inactivo(){
    try {
        btn_reini_config->setStyleSheet(btn);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiConfiguracion::boton_e_activo(){
    try {
        btn_eventos->setStyleSheet(btnSeleccionado);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiConfiguracion::boton_e_inactivo(){
    try {
        btn_eventos->setStyleSheet(btn);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiConfiguracion::ultimoencontenedor(){
    try {
        if(configModo->conte_modo->currentWidget() == configModo->modoPCMV){
            elementSel = 8;
            configModo->modoPCMV->set_elemento_seleccionado(6);
        }
        else if(configModo->conte_modo->currentWidget() == configModo->modoVCMV){
             configModo->modoVCMV->set_elemento_seleccionado(7);
        }
        else if(configModo->conte_modo->currentWidget() == configModo->modoPSIMV){
             configModo->modoPSIMV->set_elemento_seleccionado(7);
        }
        else if(configModo->conte_modo->currentWidget() == configModo->modoVSIMV){
             configModo->modoVSIMV->set_elemento_seleccionado(8);
        }
        else if(configModo->conte_modo->currentWidget() == configModo->modoPCPAP){
             configModo->modoPCPAP->set_elemento_seleccionado(6);
        }
        else if(configModo->conte_modo->currentWidget() == configModo->modoVCPAP){
             configModo->modoVCPAP->set_elemento_seleccionado(6);
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiConfiguracion::ir_a_contenedor(int desde){
    try {
        if(configModo->conte_modo->currentWidget() == configModo->modoPCMV){
            if(desde ==1){
                configModo->modoPCMV->set_elemento_seleccionado(0);
            }
            else if(desde == 2 || desde == 3){
                configModo->modoPCMV->set_elemento_seleccionado(3);
            }
            else if(desde == 4 || desde == 5){
                configModo->modoPCMV->set_elemento_seleccionado(5);
            }
            else{
                configModo->modoPCMV->set_elemento_seleccionado(7);
            }
        }
        else if(configModo->conte_modo->currentWidget() == configModo->modoVCMV){
            if(desde ==1){
                configModo->modoVCMV->set_elemento_seleccionado(0);
            }
            else if(desde == 2 || desde == 3){
                configModo->modoVCMV->set_elemento_seleccionado(3);
            }
            else if(desde == 4 || desde == 5){
                configModo->modoVCMV->set_elemento_seleccionado(6);
            }
            else{
                configModo->modoVCMV->set_elemento_seleccionado(8);
            }
        }
        else if(configModo->conte_modo->currentWidget() == configModo->modoPSIMV){
            if(desde ==1){
                configModo->modoPSIMV->set_elemento_seleccionado(0);
            }
            else if(desde == 2 || desde == 3){
                configModo->modoPSIMV->set_elemento_seleccionado(3);
            }
            else if(desde == 4 || desde == 5){
                configModo->modoPSIMV->set_elemento_seleccionado(5);
            }
            else{
                configModo->modoPSIMV->set_elemento_seleccionado(8);
            }
        }
        else if(configModo->conte_modo->currentWidget() == configModo->modoVSIMV){
            if(desde ==1){
                configModo->modoVSIMV->set_elemento_seleccionado(0);
            }
            else if(desde == 2 || desde == 3){
                configModo->modoVSIMV->set_elemento_seleccionado(3);
            }
            else if(desde == 4){
                configModo->modoVSIMV->set_elemento_seleccionado(5);
            }
            else if(desde == 5){
                configModo->modoVSIMV->set_elemento_seleccionado(6);
            }
            else{
                configModo->modoVSIMV->set_elemento_seleccionado(9);
            }
        }
        else if(configModo->conte_modo->currentWidget() == configModo->modoPCPAP){
            if(desde ==1){
                configModo->modoPCPAP->set_elemento_seleccionado(0);
            }
            else if(desde == 2){
                configModo->modoPCPAP->set_elemento_seleccionado(1);
            }
            else if(desde == 3){
                configModo->modoPCPAP->set_elemento_seleccionado(2);
            }
            else if(desde == 4 || desde == 5){
                configModo->modoPCPAP->set_elemento_seleccionado(3);
            }
            else{
                configModo->modoPCPAP->set_elemento_seleccionado(9);
            }
        }
        else if(configModo->conte_modo->currentWidget() == configModo->modoVCPAP){
            if(desde ==1){
                configModo->modoVCPAP->set_elemento_seleccionado(0);
            }
            else if(desde == 2){
                configModo->modoVCPAP->set_elemento_seleccionado(1);
            }
            else if(desde == 3){
                configModo->modoVCPAP->set_elemento_seleccionado(2);
            }
            else if(desde == 4 || desde == 5){
                configModo->modoVCPAP->set_elemento_seleccionado(3);
            }
            else{
                configModo->modoVCPAP->set_elemento_seleccionado(9);
            }
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiConfiguracion::seleccionar_dentro_modo(QString tecla){
    try {
        if(configModo->conte_modo->currentWidget() == configModo->modoPCMV){
            int res = 0;
            if(tecla == "arr"){
                res = configModo->modoPCMV->mover_arriba();
            }
            else if(tecla == "aba"){
                res = configModo->modoPCMV->mover_abajo();
            }
            else if(tecla == "izq"){
                configModo->modoPCMV->mover_izquierda();
            }
            else if(tecla == "der"){
               configModo->modoPCMV->mover_derecha();
            }
            if(res < 0){
                elementSel = abs(res);
                configModo->boton_activo(elementSel);
            }
        }
        else if(configModo->conte_modo->currentWidget() == configModo->modoVCMV){
            int res = 0;
            if(tecla == "arr"){
                res = configModo->modoVCMV->mover_arriba();
            }
            else if(tecla == "aba"){
                res = configModo->modoVCMV->mover_abajo();
            }
            else if(tecla == "izq"){
                configModo->modoVCMV->mover_izquierda();
            }
            else if(tecla == "der"){
               configModo->modoVCMV->mover_derecha();
            }
            if(res < 0){
                elementSel = abs(res);
                configModo->boton_activo(elementSel);
            }
        }
        else if(configModo->conte_modo->currentWidget() == configModo->modoPSIMV){
            int res = 0;
            if(tecla == "arr"){
                res = configModo->modoPSIMV->mover_arriba();
            }
            else if(tecla == "aba"){
                res = configModo->modoPSIMV->mover_abajo();
            }
            else if(tecla == "izq"){
                configModo->modoPSIMV->mover_izquierda();
            }
            else if(tecla == "der"){
               configModo->modoPSIMV->mover_derecha();
            }
            if(res < 0){
                elementSel = abs(res);
                configModo->boton_activo(elementSel);
            }
        }
        else if(configModo->conte_modo->currentWidget() == configModo->modoVSIMV){
            int res = 0;
            if(tecla == "arr"){
                res = configModo->modoVSIMV->mover_arriba();
            }
            else if(tecla == "aba"){
                res = configModo->modoVSIMV->mover_abajo();
            }
            else if(tecla == "izq"){
                configModo->modoVSIMV->mover_izquierda();
            }
            else if(tecla == "der"){
               configModo->modoVSIMV->mover_derecha();
            }
            if(res < 0){
                elementSel = abs(res);
                configModo->boton_activo(elementSel);
            }
        }
        else if(configModo->conte_modo->currentWidget() == configModo->modoPCPAP){
            int res = 0;
            if(tecla == "arr"){
                res = configModo->modoPCPAP->mover_arriba();
            }
            else if(tecla == "aba"){
                res = configModo->modoPCPAP->mover_abajo();
            }
            else if(tecla == "izq"){
                configModo->modoPCPAP->mover_izquierda();
            }
            else if(tecla == "der"){
               configModo->modoPCPAP->mover_derecha();
            }
            if(res < 0){
                elementSel = abs(res);
                configModo->boton_activo(elementSel);
            }
        }
        else if(configModo->conte_modo->currentWidget() == configModo->modoVCPAP){
            int res = 0;
            if(tecla == "arr"){
                res = configModo->modoVCPAP->mover_arriba();
            }
            else if(tecla == "aba"){
                res = configModo->modoVCPAP->mover_abajo();
            }
            else if(tecla == "izq"){
                configModo->modoVCPAP->mover_izquierda();
            }
            else if(tecla == "der"){
               configModo->modoVCPAP->mover_derecha();
            }
            if(res < 0){
                elementSel = abs(res);
                configModo->boton_activo(elementSel);
            }
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiConfiguracion::elementoSeleccionado(){
    try {
        if(elementSel == 0){
            boton_activo();
        }
        else if(elementSel == 1){
            configModo->boton_checked(1, true);
            configModo->boton_activo(1);
        }
        else if(elementSel == 2){
            configModo->boton_checked(2, true);
            configModo->boton_activo(2);
        }
        else if(elementSel == 3){
            configModo->boton_checked(3, true);
            configModo->boton_activo(3);
        }
        else if(elementSel == 4){
            configModo->boton_checked(4, true);
            configModo->boton_activo(4);
        }
        else if(elementSel == 5){
            configModo->boton_checked(5, true);
            configModo->boton_activo(5);
        }
        else if(elementSel == 6){
            configModo->boton_checked(6, true);
            configModo->boton_activo(6);
        }
        elementoNoSeleccionado();
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiConfiguracion::elementoNoSeleccionado(){
    try {
        for(int i=1; i < 7; i++){
            if(i != elementSel){
                configModo->boton_inactivo(i);
            }
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiConfiguracion::elementoNoChecked(){
    try {
        for(int i=1; i < 8; i++){
            if(i != elementSel){
                configModo->boton_checked(i, false);
            }
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiConfiguracion::guardarModo(int modo){
    try {
        if(monitor->consul->actualizar_modo(modo)){
            qDebug() << "***Modo guardado: " + QString::number(modo);
        }
        else{
            qDebug() << "***Modo no guardado: " + QString::number(modo);
        }
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiConfiguracion::guardarConfigPCMV(){
    try {
        QStringList valores = configModo->modoPCMV->obtener_valores();
        if(valores.size() > 0){
            if(monitor->consul->guardar_config_ultima_PCMV(valores.at(0),valores.at(1), valores.at(2),valores.at(3),valores.at(4),valores.at(5),valores.at(6),valores.at(7),valores.at(8),valores.at(9))){
                guardarModo(0);
                monitor->consul->agregar_evento("Guardar", monitor->obtener_modo(), "Se guardaron cambios en modo PCMV");
                configModo->modoPCMV->mostrar_mensaje("Datos guardados");
            }
            else{
                qDebug() << "Error al guardar datos";
            }
        }
        else{
            qDebug() << "Error al obtener los datos";
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiConfiguracion::guardarConfigVCMV(){
    try {
        QStringList valores = configModo->modoVCMV->obtener_valores();
        if(valores.size() > 0){
            if(monitor->consul->guardar_config_ultima_VCMV(valores.at(0),valores.at(1), valores.at(2),valores.at(3),valores.at(4),valores.at(5),valores.at(6),valores.at(7),valores.at(8),valores.at(9))){
                guardarModo(1);
                monitor->consul->agregar_evento("Guardar", monitor->obtener_modo(), "Se guardaron cambios en modo VCMV");
                configModo->modoVCMV->mostrar_mensaje("Datos guardados");
            }
            else{
                qDebug() << "Error al guardar datos";
            }
        }
        else{
            qDebug() << "Error al obtener los datos";
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiConfiguracion::guardarConfigPSIMV(){
    try {
        QStringList valores = configModo->modoPSIMV->obtener_valores();
        if(valores.size() > 0){
            if(monitor->consul->guardar_config_ultima_PSIMV(valores.at(0),valores.at(1), valores.at(2),valores.at(3),valores.at(4),valores.at(5),valores.at(6),valores.at(7),valores.at(8),valores.at(9),valores.at(10))){
                guardarModo(2);
                monitor->consul->agregar_evento("Guardar", monitor->obtener_modo(), "Se guardaron cambios en modo PSIMV");
                configModo->modoPSIMV->mostrar_mensaje("Datos guardados");
            }
            else{
                qDebug() << "Error al guardar datos";
            }
        }
        else{
            qDebug() << "Error al obtener los datos";
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiConfiguracion::guardarConfigVSIMV(){
    try {
        QStringList valores = configModo->modoVSIMV->obtener_valores();
        if(valores.size() > 0){
            if(monitor->consul->guardar_config_ultima_VSIMV(valores.at(0),valores.at(1), valores.at(2),valores.at(3),valores.at(4),valores.at(5),valores.at(6),valores.at(7),valores.at(8),valores.at(9),valores.at(10),valores.at(11),valores.at(12))){
                guardarModo(3);
                monitor->consul->agregar_evento("Guardar", monitor->obtener_modo(), "Se guardaron cambios en modo VSIMV");
                configModo->modoVSIMV->mostrar_mensaje("Datos guardados");
            }
            else{
                qDebug() << "Error al guardar datos";
            }
        }
        else{
            qDebug() << "Error al obtener los datos";
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiConfiguracion::guardarConfigPCPAP(){
    try {
        QStringList valores = configModo->modoPCPAP->obtener_valores();
        if(valores.size() > 0){
            if(monitor->consul->guardar_config_ultima_PCPAP(valores.at(0),valores.at(1), valores.at(2),valores.at(3),valores.at(4),valores.at(5),valores.at(6),valores.at(7),valores.at(8),valores.at(9))){
                guardarModo(4);
                monitor->consul->agregar_evento("Guardar", monitor->obtener_modo(), "Se guardaron cambios en modo PCPAP");
                configModo->modoPCPAP->mostrar_mensaje("Datos guardados");
            }
            else{
                qDebug() << "Error al guardar datos";
            }
        }
        else{
            qDebug() << "Error al obtener los datos";
        }
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiConfiguracion::guardarConfigVCPAP(){
    try {
        QStringList valores = configModo->modoVCPAP->obtener_valores();
        if(valores.size() > 0){
            if(monitor->consul->guardar_config_ultima_VCPAP(valores.at(0),valores.at(1), valores.at(2),valores.at(3),valores.at(4),valores.at(5),valores.at(6),valores.at(7),valores.at(8),valores.at(9))){
                guardarModo(5);
                monitor->consul->agregar_evento("Guardar", monitor->obtener_modo(), "Se guardaron cambios en modo VCPAP");
                configModo->modoVCPAP->mostrar_mensaje("Datos guardados");
            }
            else{
                qDebug() << "Error al guardar datos";
            }
        }
        else{
            qDebug() << "Error al obtener los datos";
        }
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiConfiguracion::llenarConfiguracion(){
    try {
        QString modo = monitor->consul->leer_modo();
        if(modo[2] == "0"){
            configModo->boton_checked(1, true);
            activarModoPCMV();
            monitor->modoVentilador = "MODO: PCMV";
        }
        else if(modo[2] == "1"){
            configModo->boton_checked(2, true);
            activarModoVCMV();
            monitor->modoVentilador = "MODO: VCMV";
        }
        else if(modo[2] == "2"){
            configModo->boton_checked(3, true);
            activarModoPSIMV();
            monitor->modoVentilador = "MODO: PSIMV";
        }
        else if(modo[2] == "3"){
            configModo->boton_checked(4, true);
            activarModoVSIMV();
            monitor->modoVentilador = "MODO: VSIMV";
        }
        else if(modo[2] == "4"){
            configModo->boton_checked(5, true);
            activarModoPCPAP();
            monitor->modoVentilador = "MODO: PCPAP";
        }
        else if(modo[2] == "5"){
            configModo->boton_checked(6, true);
            activarModoVCPAP();
            monitor->modoVentilador = "MODO: VCPAP";
        }
        monitor->label_Modo->setText(monitor->modoVentilador);
        elementoSeleccionado();
        llenarConfiguracionPCMV();
        llenarConfiguracionVCMV();
        llenarConfiguracionPSIMV();
        llenarConfiguracionVSIMV();
        llenarConfiguracionPCPAP();
        llenarConfiguracionVCPAP();
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiConfiguracion::llenarConfiguracionPCMV(){
    try {
        QString ult_config = monitor->consul->buscar_ult_config("PCMV");
        QStringList parts_default;
        if(ult_config != ""){
            parts_default = ult_config.split(",");
        }
        else{
            QString default_config = monitor->consul->cargar_config_default("PCMV");
            parts_default = default_config.split(",");
        }
        configModo->modoPCMV->cargar_valores(parts_default);
        configModo->modoPCMV->labelInfo->setText("");
        configModo->modoPCMV->obtener_info_adicional();
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiConfiguracion::llenarConfiguracionVCMV(){
    try {
        QString ult_config = monitor->consul->buscar_ult_config("VCMV");
        QStringList parts_default;
        if(ult_config != ""){
            parts_default = ult_config.split(",");
        }
        else{
            QString default_config = monitor->consul->cargar_config_default("VCMV");
            parts_default = default_config.split(",");
        }
        configModo->modoVCMV->cargar_valores(parts_default);
        configModo->modoVCMV->labelInfo->setText("");
        configModo->modoVCMV->obtener_info_adicional();
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiConfiguracion::llenarConfiguracionPSIMV(){
    try {
        QString ult_config = monitor->consul->buscar_ult_config("PSIMV");
        QStringList parts_default;
        if(ult_config != ""){
            parts_default = ult_config.split(",");
        }
        else{
            QString default_config = monitor->consul->cargar_config_default("PSIMV");
            parts_default = default_config.split(",");
        }
        configModo->modoPSIMV->cargar_valores(parts_default);
        configModo->modoPSIMV->labelInfo->setText("");
        configModo->modoPSIMV->obtener_info_adicional();
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiConfiguracion::llenarConfiguracionVSIMV(){
    try {
        QString ult_config = monitor->consul->buscar_ult_config("VSIMV");
        QStringList parts_default;
        if(ult_config != ""){
            parts_default = ult_config.split(",");
        }
        else{
            QString default_config = monitor->consul->cargar_config_default("VSIMV");
            parts_default = default_config.split(",");
        }
        configModo->modoVSIMV->cargar_valores(parts_default);
        configModo->modoVSIMV->labelInfo->setText("");
        configModo->modoVSIMV->obtener_info_adicional();
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiConfiguracion::llenarConfiguracionPCPAP(){
    try {
        QString ult_config = monitor->consul->buscar_ult_config("PCPAP");
        QStringList parts_default;
        if(ult_config != ""){
            parts_default = ult_config.split(",");
        }
        else{
            QString default_config = monitor->consul->cargar_config_default("PCPAP");
            parts_default = default_config.split(",");
        }
        configModo->modoPCPAP->cargar_valores(parts_default);
        configModo->modoPCPAP->labelInfo->setText("");
        configModo->modoPCPAP->obtener_info_adicional();
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiConfiguracion::llenarConfiguracionVCPAP(){
    try {
        QString ult_config = monitor->consul->buscar_ult_config("VCPAP");
        QStringList parts_default;
        if(ult_config != ""){
            parts_default = ult_config.split(",");
        }
        else{
            QString default_config = monitor->consul->cargar_config_default("VCPAP");
            parts_default = default_config.split(",");
        }
        configModo->modoVCPAP->cargar_valores(parts_default);
        configModo->modoVCPAP->labelInfo->setText("");
        configModo->modoVCPAP->obtener_info_adicional();
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiConfiguracion::abrir_pantalla_eventos(){
    try {
        tab_eventos->cargar_datos();
        tabWidget->setCurrentIndex(3);
        mostrando_eventos = true;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}
