#include "monitor.h"

#include <QFont>
#include <QWidget>
#include <QRect>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QString>
#include <QPushButton>
#include <QSizePolicy>

#include "signos/widgetsigno3.h"
#include "utilidades/widgetsignobar.h"

Monitor::Monitor(QWidget *parent, Consultas *consul, bool debug_c, bool debug_s) : QWidget(parent)
{
    try {
        versionVentiladorEsperada = "3.6";
        versionSenPresionEsperada = "3.0";
        versionTecladoEsperada = "1.0";
        versionPi = "3.69";

        mainwindow = parent;
        this->consul = consul;
        setStyleSheet("background-color: rgb(0, 0, 0);");
        //fuente
        fuente = new QFont;
        fuente->setBold(true);
        fuente->setPointSize(18);

        //variables que no estaban al inicio en la creacion de la clase
        ino_wdt_alarm = false;

        offset_pip = 0;
        QString tt_offset = consul->leer_com_pip();
        QStringList tt_off_pip = tt_offset.split(",");
        offset_pip = tt_off_pip.at(1).toFloat();

        vida_o2_21 = 0;
        vida_o2_100 = 0;

        tiempo_respuesta_ventilador = 0;
        alarma_pres_max = "";
        alarma_pres_min = "";
        alarma_volmin_max = "";
        alarma_volmin_min = "";
        alarma_fr_max = "";
        alarma_fr_min = "";
        alarma_vol_max = "";
        alarma_vol_min = "";
        alarma_apnea = "";

        nivel_oxigeno = "";
        modo_nobreak = "";
        nivel_batt = "";

        mostrarGrafica = true;
        serPresionListo = false;

        beep_frecuencia = 0;
        beep_veces = 0;
        beep_tiempo = 0;
        beep_pausa = 0;

        ult_temp_nivel_bat = 0;

        esperando_limites_lazos = true;

        //central widget?
        centralwidget = new QWidget(this);
        centralwidget->setObjectName("centralwidget");

        //horizontalLayoutWidget
        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setGeometry(QRect(0,25,1024,600));
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");

        //principalLayout
        principalLayout = new QHBoxLayout(horizontalLayoutWidget);
        principalLayout->setContentsMargins(0,0,0,0);
        principalLayout->setSpacing(1);
        principalLayout->setObjectName("principalLayout");

        //contenidoLayout
        contenidoLayout = new QVBoxLayout;
        contenidoLayout->setContentsMargins(-1,0,-1,-1);
        contenidoLayout->setSpacing(2);
        contenidoLayout->setObjectName("contenidoLayout");

        //box para los elementos superiores
        //informacionLayout
        informacionLayout = new QHBoxLayout;
        informacionLayout->setObjectName("informacionLayout");

        //box para el modo y el debug
        debugLayout = new QVBoxLayout;
        debugLayout->setObjectName("debugLayout");

        //label_Modo
        label_Modo =  new QLabel(horizontalLayoutWidget);
        label_Modo->setFont(*fuente);
        label_Modo->setStyleSheet("color: rgb(255, 255, 255);");
        label_Modo->setObjectName("label_Modo");
        debugLayout->addWidget(label_Modo);

        label_debug = new QLabel(horizontalLayoutWidget);
        fuente->setPointSize(12);
        label_debug->setFont(*fuente);
        label_debug->setStyleSheet("color: rgb(255, 255, 255);");
        label_debug->setObjectName("label_debug");
        debugLayout->addWidget(label_debug);
        informacionLayout->addLayout(debugLayout);

        //box para los botones
        botonesLayout =  new QHBoxLayout;
        botonesLayout->setObjectName("botonesLayout");

        //estilos botones
        estiloBotonA = "QPushButton { border: 2px solid rgb(255,112,61); background-color: gray; border-radius: 5px; color: black; margin-left: 2px; padding-left: 4px; padding-right: 4px}";
        estiloBotonI = "QPushButton { border: 2px solid rgb(145,145,145); background-color: rgb(145,145,145); border-radius: 5px; color: black; margin-left: 2px; padding-left: 4px; padding-right: 4px}";
        fuente->setPointSize(13);
        botonesLayout->addStretch();
        //Boton de actualizacion de parametros para el ventilador
        btn_ventilador = new QPushButton(horizontalLayoutWidget);
        btn_ventilador->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        btn_ventilador->setObjectName("btn_ventilador");
        btn_ventilador->setStyleSheet(estiloBotonI);
        btn_ventilador->setFont(*fuente);
        botonesLayout->addWidget(btn_ventilador);

        //Boton para visualizacion de graficos
        btn_grafica = new QPushButton(horizontalLayoutWidget);
        btn_grafica->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        btn_grafica->setObjectName("btn_grafica");
        btn_grafica->setStyleSheet(estiloBotonI);
        btn_grafica->setFont(*fuente);
        botonesLayout->addWidget(btn_grafica);

        //Boton para el autoprueba del equipo
        btn_test = new QPushButton(horizontalLayoutWidget);
        btn_test->setObjectName("btn_test");
        btn_test->setStyleSheet(estiloBotonI);
        btn_test->setFont(*fuente);
        btn_test->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
        botonesLayout->addWidget(btn_test);
        informacionLayout->addLayout(botonesLayout);

        //aquí se crea un widget AlarmasX que se agrega a informacionLayout
        widgetAlarms = new AlarmasX(horizontalLayoutWidget);
        informacionLayout->addWidget(widgetAlarms);

        //Panel de alarmas
        label_info_alarma = new QLabel(horizontalLayoutWidget);
        fuente->setPointSize(16);
        label_info_alarma->setFont(*fuente);
        label_info_alarma->setStyleSheet("background-color: black; color: red;");
        label_info_alarma->setAlignment(Qt::AlignCenter);
        label_info_alarma->setText("");
        label_info_alarma->setObjectName("label_info_alarma");
        informacionLayout->addWidget(label_info_alarma);

        informacionLayout->setStretch(2,3);
        informacionLayout->setStretch(3,4);
        contenidoLayout->addLayout(informacionLayout);

        //layout donde va el layout de grafica y el inferior
        graficaLayout = new QVBoxLayout;
        graficaLayout->setObjectName("graficaLayout");

        //layout donde van las graficas!
        graphiclayout = new QGridLayout; //(horizontalLayoutWidget)
        graphiclayout->setGeometry(QRect(0,0,771,451));

        //////////////////aqui viene lo de las gráficas
        graficaPresion = new WidgetGrafica(this, "graficaPresion", "PRESION", -5, 35, Qt::green, 50);
        graphiclayout->addWidget(graficaPresion, 0,1);
        graficaVolumen = new WidgetGrafica(this, "graficaVolumen", "VOLUMEN", -0.5, 1.5, Qt::blue, 50);
        graphiclayout->addWidget(graficaVolumen, 1,1);
        graficaFlujo = new WidgetGrafica(this, "graficaFlujo", "FLUJO", -150, 150, Qt::yellow, 50);
        graphiclayout->addWidget(graficaFlujo, 2,1);



        graficaPV = nullptr;
        graficaVF = nullptr;

        /*graficaPV = new WidgetGraficaLazo(this, "graficaPV", "VOLUMEN", min_lazo_vol_y, max_lazo_vol_y, "PRESION", min_lazo_pres_x, max_lazo_pres_x, Qt::yellow, 50);
        graphiclayout->addWidget(graficaPV, 1,0);
        graficaVF = new WidgetGraficaLazo(this, "graficaVF", "FLUJO", min_lazo_flujo_y, max_lazo_flujo_y, "VOLUMEN", min_lazo_vol_x, max_lazo_vol_x, Qt::green, 50);
        graphiclayout->addWidget(graficaVF, 1,1);*/
        //////////////////

        estadoVentilador = false;
        cambiagrafi = false;
        contadorGrafica = 0;

        graficaLayout->addLayout(graphiclayout);


        gridLayoutInf = new QHBoxLayout;
        gridLayoutInf->setObjectName("gridLayoutInf");

        paleNormal = new QPalette;
        paleNormal->setColor(QPalette::Background, Qt::black);
        paleNormal->setColor(QPalette::Base, Qt::black);
        paleNormal->setColor(QPalette::Text, Qt::white);

        paleAlta = new QPalette;
        paleAlta->setColor(QPalette::Background, Qt::black);
        paleAlta->setColor(QPalette::Base, Qt::black);
        paleAlta->setColor(QPalette::Text, Qt::red);

        palemedia_baja = new QPalette;
        palemedia_baja->setColor(QPalette::Background, Qt::black);
        palemedia_baja->setColor(QPalette::Base, Qt::black);
        palemedia_baja->setColor(QPalette::Text, Qt::yellow);

        //aqui vienen los widgets inferiores
        signoPIP =  new WidgetSignoBar(this, "PIP", "signoPIP", "cmH2O", 0, 150, 0, "F");
        gridLayoutInf->addWidget(signoPIP);
        signoPEEP = new WidgetSignoBar(this,  "PEEP", "signoPEEP", "cmH2O", 0, 60.0, 0, "F");
        gridLayoutInf->addWidget(signoPEEP);
        signoPLATEU =  new WidgetSignoBar(this, "OXIGENO", "signoPLATEU", "%", 0, 100.0, 0, "F");
        gridLayoutInf->addWidget(signoPLATEU);
        signoTiempoI = new  WidgetSignoBar(this, "TI","signoTiempoI"," seg ", 0, 30.0, 0, "F");
        gridLayoutInf->addWidget(signoTiempoI);
        signoTiempoE = new WidgetSignoBar(this, "TE","signoTiempoE", " seg ", 0, 30.0, 0, "F");
        gridLayoutInf->addWidget(signoTiempoE);
        signoVm =  new WidgetSignoBar(this, "Vm", "signoVm", " L ", 0, 30.0, 0, "F");
        signoVm->bar->setValue(10);
        gridLayoutInf->addWidget(signoVm);
        graficaLayout->addLayout(gridLayoutInf);

        graficaLayout->setStretch(0,3);
        graficaLayout->setStretch(1,1);

        contenidoLayout->addLayout(graficaLayout);
        contenidoLayout->setStretch(0,1);
        contenidoLayout->setStretch(1,10);
        principalLayout->addLayout(contenidoLayout);

        barLayout = new QVBoxLayout;
        barLayout->setContentsMargins(0,-1,-1,-1);
        barLayout->setSpacing(2);
        barLayout->setObjectName("barLayout");

        menuLayout = new QVBoxLayout;
        menuLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        menuLayout->setSpacing(0);
        menuLayout->setObjectName("menuLayout");

        //aqui se agrega InfoAlarma y se agregar al menuLayout
        infoAlarmas = new InfoAlarma;
        menuLayout->addWidget(infoAlarmas);

        //agregar fecha y hora
        label_fecha = new QLabel(horizontalLayoutWidget);
        fuente->setPointSize(12);
        label_fecha->setFont(*fuente);
        label_fecha->setStyleSheet("color: rgb(255, 255, 255);");
        label_fecha->setObjectName("label_fecha");
        label_fecha->setText("Hola");
        menuLayout->addWidget(label_fecha);
        barLayout->addLayout(menuLayout);

        opcionesLayout = new QVBoxLayout;
        opcionesLayout->setObjectName("opcionesLayout");
        //aqui se agregan los los widgetSigno3 los laterales
        widgetPresPrin = new WidgetSigno3(this, "Pm", "widgetPresPrin", "cmH<sub>2</sub>O", "White", 167, 94, "graficos/alarmay.png");
        contornoColor(widgetPresPrin);
        opcionesLayout->addWidget(widgetPresPrin);
        widgetVoli = new WidgetSigno3(this, "Vol I", "widgetVoli", "ml", "White", 167, 94, "graficos/alarmay.png");
        contornoColor(widgetVoli);
        opcionesLayout->addWidget(widgetVoli);
        widgetVole = new WidgetSigno3(this, "Vol E", "widgetVole", "ml", "White", 167, 94, "graficos/alarmay.png");
        contornoColor(widgetVole);
        opcionesLayout->addWidget(widgetVole);
        widgetFR = new WidgetSigno3(this, "FR", "widgetFR", "r/min", "White", 167, 94, "graficos/alarmay.png");
        contornoColor(widgetFR);
        opcionesLayout->addWidget(widgetFR);
        widgetTiTe = new WidgetSigno3(this, "TI:TE", "widgetTiTe", "  ", "White", 167, 94, "graficos/alarmaw.png");
        contornoColor(widgetTiTe);
        opcionesLayout->addWidget(widgetTiTe);
        widgetFlujo = new WidgetSigno3(this, "Fp", "widgetFlujo", "L/min", "White", 167, 94, "graficos/alarmay.png");
        contornoColor(widgetFlujo);
        opcionesLayout->addWidget(widgetFlujo);


        barLayout->addLayout(opcionesLayout);
        barLayout->setStretch(0,1);
        barLayout->setStretch(1,10);
        principalLayout->addLayout(barLayout);
        principalLayout->setStretch(0,10);
        principalLayout->setStretch(1,2);
        contadorErrorConVent = 0;

        //qDebug() << "Se va a crear serVent!";

        serVent = new Ventilador(debug_c);
        connect(serVent, SIGNAL(enviaLinea(QString)), this, SLOT(receVent(QString)));
        connect(serVent, SIGNAL(muestraAviso(QString)), this, SLOT(muestraAvisoVentilador(QString)));
        connect(serVent, SIGNAL(cierraAviso()), this, SLOT(cierraAvisoVentilador()));

        numero_datos_presion = 1;

        banderaConexionSenPresion = false;
        banderaModoSenPresion = 0;

        timerTPresion1S = new QTimer;
        connect(timerTPresion1S, SIGNAL(timeout()), this, SLOT(validaUnSeg()));
        timerCont1S = 0;
        timerActivo1S = false;

        timerTPresion5S = new QTimer;
        connect(timerTPresion5S, SIGNAL(timeout()), this, SLOT(validaCincoSeg()));
        timerCont5S = 0;
        timerActivo5S = false;

        tpresionModo = 0;

        //qDebug() << "Se va a crear serPresion!";

        serPresion = new SenPresion(debug_s);
        connect(serPresion, SIGNAL(enviaLinea(QString)), this, SLOT(recePresion(QString)));
        connect(serPresion, SIGNAL(muestraAviso(QString)), this, SLOT(muestraAvisoPresion(QString)));
        connect(serPresion, SIGNAL(cierraAviso()), this, SLOT(cierraAvisoPresion()));
        connect(serPresion, SIGNAL(iniciaMonitoreo()), this, SLOT(iniciaMonSensores()));


        elementSel = 0;

        connect(btn_ventilador, SIGNAL(clicked()), this, SLOT(actualizarDatosVentilador()));
        connect(btn_grafica, SIGNAL(clicked()), this, SLOT(controlGrafica()));

        //qDebug() << "Se va a crear AlarmaAudLed!";

        alarmaControl = new AlarmaAudLed(infoAlarmas);
        alarmaControl->setIconoFre(widgetFR->label_icon);
        alarmaControl->setIconoVol(widgetVoli->label_icon);

        estadoAlarmaPresion = false;
        estadoAlarmaVol = false;
        estadoAlarmaFr = false;
        estadoAlarmaVolMin = false;
        estadoAlarmaBateria = false;
        estadoAlarmaGases = false;
        estadoAlarmaFIO2 = false;
        estadoAlarmaApnea = false;
        estadoAlarmaSensores = false;
        estadoAlarmaAlimentacion = false;
        estadoAlarmaDesconexion = false;

        estadoAlarmaMec = false;
        estadoAlarmaEner = false;
        estadoAlarmaNeu = false;
        estadoAlarma1 = false;
        estadoAlarma2 = false;

        tramaConfigVent = "";
        alarmaboolean = false;

        modoVentilador = "";

        tramaVentilador = "";

        tramaV = "";

        configurandoVentilador = false;
        primera_vez_ventilador = false;
        banderaPosicionVentilador = false;
        banderaOffsetVentilador = false;
        banderaModoVentilador = false;
        banderaTramaVentilador = false;
        numeroBanderaVentilador = 0;
        contadorBanderaConxVent = 0;

        timerVentilador = new QTimer;
        timerVentilador->setSingleShot(true);
        connect(timerVentilador, SIGNAL(timeout()), this, SLOT(revisarBanderasVentilador()));
        banderaConexionVentilador = false;

        timerConVentilador = new QTimer;
        timerConVentilador->setSingleShot(true);
        connect(timerConVentilador, SIGNAL(timeout()), this, SLOT(revisarConexionVentilador()));

        timerConfigVent = new QTimer;
        connect(timerConfigVent, SIGNAL(timeout()), this, SLOT(revisarConfigVentilador()));
        timerConfigVent->start(6000);

        timerOffsetsVent = new QTimer;
        connect(timerOffsetsVent, SIGNAL(timeout()), this, SLOT(revisarOffsetVentilador()));
        timerOffsetsVent->start(4000);

        cambiosMIni = false;
        timerMIniVent = new QTimer;
        connect(timerMIniVent, SIGNAL(timeout()), this, SLOT(revisarMIniVentilador()));
        contadorMIniVentilador = 0;

        //qDebug() << "Se va a enviar trama por serVent!";

        serVent->envia_trama_config("F\n");
        senPresionListo = false;
        origenListo = false;
        contadorOrigen = 0;
        contadorVVentilador = 0;

        trama_c_senpresion = "C0,000,000\n";
        trama_w_serpresion = "";
        banderConfigCLista = false;
        dentroTimerValida5s = false;
        configurandoSenPresion = false;


        versionVentilador = "";
        versionSenPresion = "";
        versionTeclado = "";

        vrecibidaVentilador = false;
        vrecibidaSenpresion = false;


        estadoAlarmasVentilador = "";
        estadoAlarmasVentiladorControl = "";
        estadoAlarmasSensores = "";

        error_sensores_sensor_presion = false;
        error_sensores_sensor_inhalacion = false;
        error_sensores_sensor_exhalacion = false;

        timerLimpiarBuffer = new QTimer;
        timerLimpiarBuffer->setSingleShot(true);
        connect(timerLimpiarBuffer, SIGNAL(timeout()), this, SLOT(limpiarBuffer()));

        timerEstadoSenPresion = new QTimer;
        timerEstadoSenPresion->setInterval(3000);
        contadorTimerEstadoSenPresion = 0;
        connect(timerEstadoSenPresion, SIGNAL(timeout()), this, SLOT(revisarEstadoSenPresion()));
        banderaTimerEstadoSenPresion = false;
        timerEstadoSenPresion->start();

        vAvisoC = new VentanaAviso(this, 500,300);
        muestraAvisoConfig("Terminando de configurar...");

        timerTerminaConfigurar = new QTimer;
        timerTerminaConfigurar->setInterval(2500);
        connect(timerTerminaConfigurar, SIGNAL(timeout()), this, SLOT(revisarTerminaConfigurar()));
        timerTerminaConfigurar->start();

        tecladoListo = false;
        contadorTerminaConfigurar = 0;
        ventiladorListo = false;
        primera_vez_offset_ventildor = true;

        //qDebug() << "Se va a leer_sentido_giro";

        QString temp = consul->leer_sentido_giro();
        if(temp[2] == "0"){
            sentido_giro = false;
        }
        else{
            sentido_giro = true;
        }

        //qDebug() << "Termina de leer_sentido_giro";

        tramaCambiosCalibrar = "";

        huboCambioModo = false;
        ultimoModo = "";
        nuevoModo = "";
        huboCambioTrama = false;
        ultimaTrama = "";
        primera_vez_modo = true;
        temp_peep = "000";

        temp_timer_ini = new QTimer;
        temp_timer_ini->setSingleShot(true);
        connect(temp_timer_ini, SIGNAL(timeout()), this, SLOT(iniciar_ventilador()));

        temp_timer_det = new QTimer;
        temp_timer_det->setSingleShot(true);
        connect(temp_timer_det, SIGNAL(timeout()), this, SLOT(detener_ventilador()));

        modoSel = 1;

        primera_vez_modo_sen_presion = true;
        ultimaTramaSenPresion = "";
        tramaSenPresion = "";
        huboCambioTramaSenPresion = false;

        retranslate_ui();

        //qDebug() << "Termina de retranslate_ui";

        trama_w_serpresion = "";
        trama_w = "";
        trama_w_ultima = "";
        primera_vez_modo_sen_presion_w = true;
        huboCambioTramaSenPresionW = false;

        indiceMsg1 = -1;
        vTestActiva = false;

        temp_actua = new QTimer;
        connect(temp_actua, SIGNAL(timeout()), this, SLOT(actuaTest()));
        temp_actua->setSingleShot(true);

        trigger_activar = "0";
        trigger_ult_est = "0";

        widgetAlarms->bateria(50,0);

        timerMuestraAlarmas = new QTimer;
        connect(timerMuestraAlarmas, SIGNAL(timeout()), this, SLOT(muestraAlarmas()));
        timerMuestraAlarmas->setInterval(2000);
        timerMuestraAlarmas->start(2000);

        lista_alarmas = new QStringList;
        contadorMuestraAlarmas = 0;
        contador_respuesta_config_senrpesion = 0;
        dict_color_muestra_alarma = new QMap<QString, QString>;
        dict_color_muestra_alarma->insert("Presión", "yellow");
        dict_color_muestra_alarma->insert("Vol tidal", "yellow");
        dict_color_muestra_alarma->insert("Vol minuto", "red");
        dict_color_muestra_alarma->insert("Frecuencia", "yellow");
        dict_color_muestra_alarma->insert("Apnea", "yellow");
        dict_color_muestra_alarma->insert("Vol min MAX", "red");
        dict_color_muestra_alarma->insert("Vol min MIN", "yellow");
        dict_color_muestra_alarma->insert("Presion MAX", "yellow");
        dict_color_muestra_alarma->insert("Vol tidal MAX", "yellow");
        dict_color_muestra_alarma->insert("Vol tidal MIN", "yellow");
        dict_color_muestra_alarma->insert("Presion MIN", "yellow");
        dict_color_muestra_alarma->insert("Frec. MIN", "yellow");
        dict_color_muestra_alarma->insert("Frec. MAX", "yellow");
        dict_color_muestra_alarma->insert("Bat. baja", "red");
        dict_color_muestra_alarma->insert("Bat. media", "yellow");
        dict_color_muestra_alarma->insert("Sum. Aire B", "red");
        dict_color_muestra_alarma->insert("Sum. O2 B", "red");
        dict_color_muestra_alarma->insert("Presion baja", "yellow");
        dict_color_muestra_alarma->insert("FIO2", "yellow");
        dict_color_muestra_alarma->insert("APNEA", "red");
        dict_color_muestra_alarma->insert("SENSORES", "red");
        dict_color_muestra_alarma->insert("Modo bat.", "yellow");
        dict_color_muestra_alarma->insert("Desc. Paciente", "red");
        dict_color_muestra_alarma->insert("P. Aire BAJO", "red");
        dict_color_muestra_alarma->insert("P. Aire ALTO", "red");
        dict_color_muestra_alarma->insert("P. O2 BAJO", "red");
        dict_color_muestra_alarma->insert("P. O2 ALTO", "red");
        dict_color_muestra_alarma->insert("FIO2 BAJO", "red");
        dict_color_muestra_alarma->insert("FIO2 ALTO", "red");

        min_grafica_presion = 0;
        max_grafica_presion = 35;
        min_grafica_volumen = 0;
        max_grafica_volumen = 1.2;
        min_grafica_flujo = -30;
        max_grafica_flujo = 30;
        modo_graficas = 0;

        min_lazo_pres_x = 0;
        max_lazo_pres_x = 40;
        min_lazo_vol_y = -100;
        max_lazo_vol_y = 600;

        min_lazo_vol_x = -100;
        max_lazo_vol_x = 600;
        min_lazo_flujo_y = -40;
        max_lazo_flujo_y = 40;

        ultimo_estado_nobreak = "";
        primera_vez_nobreak = true;

        recuperado = false;
        ventanaAbierta = false;

        boton_seleccionado_menu = 0;
        boton_seleccionado_calibracion = 0;
        boton_seleccionado_pruebas = 0;

        menu = new VentanaMenu(this, 500, 300, "MENU", versionPi);
        menu->move(0,0);
        menu->resize(mainwindow->width(), mainwindow->height());
        connect(menu->btn_calibrar, SIGNAL(clicked()), this, SLOT(abrir_calibracion()));
        connect(menu->btn_pruebas, SIGNAL(clicked()), this, SLOT(abrir_pruebas()));
        menu->hide();

        //qDebug() << "Termina de VentanaMenu";

        contador_apagar = 0;

        ventana_confirmacion = new VentanaConfirmacion(this, 500,300,"CONFIRMACIÓN");
        ventana_confirmacion->move(0,0);
        ventana_confirmacion->resize(mainwindow->width(), mainwindow->height());
        connect(ventana_confirmacion->btn_si, SIGNAL(clicked()), this, SLOT(espera_si_confirmacion()));
        connect(ventana_confirmacion->btn_no, SIGNAL(clicked()), this, SLOT(espera_no_confirmacion()));
        ventana_confirmacion->hide();

        //qDebug() << "Termina de VentanaConfirmacion";

        espera_parar = false;
        espera_iniciar = false;
        espera_actualizar = false;
        espera_apagar = false;

        timerConfirmacion = new QTimer;
        connect(timerConfirmacion, SIGNAL(timeout()), this, SLOT(timer_esperando_confirmacion()));
        timerConfirmacion->setInterval(1000);

        contador_confirmacion = 30;
        boton_seleccionado_confirmacion = 0;

        pruebas = new VentanaPruebas(this, 500, 300, "PRUEBAS INICIALES");
        pruebas->move(0,0);
        pruebas->resize(mainwindow->width(), mainwindow->height());
        pruebas->hide();

        //poner los instrucciones
        fugas = new VentanaInsFuga(this, 500, 450, "INSTRUCCIONES");
        fugas->move(0,0);
        fugas->resize(mainwindow->width(), mainwindow->height());
        fugas->hide();
        connect(fugas->btn_ok, SIGNAL(clicked()), this, SLOT(cerrarFugas()));

        oxis = new VentanaInsOxi(this, 500, 450, "INSTRUCCIONES");
        oxis->move(0,0);
        oxis->resize(mainwindow->width(), mainwindow->height());
        oxis->hide();
        connect(oxis->btn_ok, SIGNAL(clicked()), this, SLOT(cerrarOxis()));

        //config altura
        configPI = new VentanaConfigPI(this, 500, 300, "Configuración");
        configPI->move(0,0);
        configPI->resize(mainwindow->width(), mainwindow->height());
        configPI->hide();
        //connect(configPI->btn_guardar, SIGNAL(clicked()), this, SLOT(aplicarAltura()));
        altura_perilla = 1;
        timerCambiosPerilla = new QTimer;
        connect(timerCambiosPerilla, SIGNAL(timeout()), this, SLOT(limpiarInfoAltura()));
        timerCambiosPerilla->setSingleShot(true);

        infoAbierta = false;

        //qDebug() << "Termina de VentanaPruebas";

        calibrar = new VentanaCalibrar(this, 500,300,"CALIBRACION");
        calibrar->move(0,0);
        calibrar->resize(mainwindow->width(), mainwindow->height());
        connect(calibrar->btn_cerrar, SIGNAL(clicked()), this, SLOT(cerrar_calibracion()));
        calibrar->hide();

        //qDebug() << "Termina de VentanaCalibrar";

        inicializacion = false;

        numero_prueba = 0;
        pruebas_iniciales = false;
        sensores_estado = false;
        presion_tope = 25;
        presion_pruebas = 0;
        presion_inicial_pruebas = 0;
        presion_inicial_salida = 0;
        contador_pruebas_iniciales = 0;
        dic_presion_tope = new QMap<int, int>;
        dic_presion_tope->insert(0,30);
        dic_presion_tope->insert(1,30);
        dic_presion_tope->insert(2,30);
        dic_tiempo_presion = new QMap<int, int>;
        dic_tiempo_presion->insert(0,20000);
        dic_tiempo_presion->insert(1,15000);
        dic_tiempo_presion->insert(2,15000);
        dic_tiempo_presion_fuga = new QMap<int, int>;
        dic_tiempo_presion_fuga->insert(0,2000);
        dic_tiempo_presion_fuga->insert(1,2000);
        dic_tiempo_presion_fuga->insert(2,2000);
        dic_tiempo_presion_salida = new QMap<int, int>;
        dic_tiempo_presion_salida->insert(0,5000);
        dic_tiempo_presion_salida->insert(1,2000);
        dic_tiempo_presion_salida->insert(2,2000);

        timerPresion = new QTimer;
        connect(timerPresion, SIGNAL(timeout()), this, SLOT(prueba_presion()));
        timerPresion->setSingleShot(true);
        timerPresionFinal = new QTimer;
        connect(timerPresionFinal, SIGNAL(timeout()), this, SLOT(prueba_presion_final()));
        timerPresionFinal->setSingleShot(true);
        timerPresionSalida = new QTimer;
        connect(timerPresionSalida, SIGNAL(timeout()), this, SLOT(prueba_presion_salida()));
        timerPresionSalida->setSingleShot(true);
        timerFinPruebaPresion = new QTimer;
        connect(timerFinPruebaPresion, SIGNAL(timeout()), this, SLOT(revisar_fin_prueba_presion()));
        timerFinPruebaPresion->setSingleShot(true);

        contador_valvulas = 0;
        pwm_100 = "0170";
        pwm_50 = "0160";
        pwm_25 = "0025";
        pwm_0 = "0060";
        exa_0 = "0";
        exa_1 = "1";
        estado_trama_valvulas = "1";

        dic_trama_valvulas = new QMap<int, QString>;
        dic_trama_valvulas->insert(0, "T"+pwm_100+pwm_0+pwm_100+exa_1+estado_trama_valvulas + "\n");
        dic_trama_valvulas->insert(1, "T"+pwm_0+pwm_0+pwm_0+"01" + "\n");
        dic_trama_valvulas->insert(2, "T"+pwm_0+pwm_100+pwm_100+exa_1+estado_trama_valvulas + "\n");
        dic_trama_valvulas->insert(3, "T"+pwm_0+pwm_0+pwm_0+"01" + "\n");

        esperando_presion_tope = false;
        esperando_presion_salida = false;
        fin_prueba_presion_serpresion = false;
        fin_prueba_presion_serventilador = false;
        buscar_q_tope = false;

        timerOxigeno = new QTimer;
        connect(timerOxigeno, SIGNAL(timeout()), this, SLOT(respuesta_oxigeno()));
        //timerOxigeno->setSingleShot(true);
        contador_timerOxigeno = 0;

        pruebas_terminadas = false;

        tramas = new Tramas;
        //cargar valores fio2
        QString ff = consul->leer_fio2();
        QStringList lf = ff.split(",");
        tramas->actualizar_formulas(lf[1], lf[2], lf[3], lf[4], lf[5]);

        borrar_eventos();

        //qDebug() << "Termina de borrar_eventos";

        timerBorrar = new QTimer;
        connect(timerOxigeno, SIGNAL(timeout()), this, SLOT(borrar_eventos()));
        timerBorrar->setInterval(7200000);
        timerBorrar->start();

        min_entrada_aire = 40;
        min_entrada_oxi = 40;
        max_entrada_aire = 90;
        max_entrada_oxi = 90;

        diccionario_alarma = new QMap<QString, int>;

        es_actualizacion = false;

        falla_actualizacion = false;

        entrada_aire = 0;
        entrada_oxigeno = 0;
        sensor_presion_c = 0;

        submenugrafica = new UiQWidgetMenuGrafica(this);
        submenugrafica->hide();
        submenugrafica->setGeometry(QRect(260, 80, 250, 50));
        submenugrafica->setObjectName("submenugrafica");

        volverIntetarComandoM = false;
        volverIntentarModo = false;

        revisar_presion_tope = false;
        revisar_liberacion_presion = false;

        desactivar_s = false;

        ventiladorInoperante = false;

        vAvisoV = nullptr;
        vAviso = nullptr;
        vAvisoT = nullptr;

        contador_paro_tarjeta_sensores = 0;

        timerVentiladorDetenido = new QTimer;
        connect(timerVentiladorDetenido, SIGNAL(timeout()), this, SLOT(ventilador_detenido()));
        timerVentiladorDetenido->setInterval(2000);

        fue_h = false;
        recibe_a0 = false;
        reenviar_paro = false;

        contador_reenvio = 0;

        listo_medir_fio2 = false;
        timerFIO2 = new QTimer;
        connect(timerFIO2, SIGNAL(timeout()), this, SLOT(activar_fio2()));
        timerFIO2->setSingleShot(true);

        cambiosCalibrar = false;
        cambiosOffsets = false;
        tramaOffsets = "";
        cargarTramaOffsets();
        contadorOffsetsVentilador = 0;

        //qDebug() << "Termina de cargarTramaOffsets";

        altura_prog = 0;
        tipo_sensor_presion = true;

        //modificaciones de hilos python a timers e hilos c+
        timerRAV = new QTimer;
        timerRAV->setSingleShot(true);
        connect(timerRAV, SIGNAL(timeout()), this, SLOT(revisar_alarmas_ventilador()));

        timerREG = new QTimer;
        timerREG->setSingleShot(true);
        connect(timerREG, SIGNAL(timeout()), this, SLOT(revisar_entra_gases()));

        //qDebug() << "Termina de timerREG";

        RA_setear = false;
        RA_limpiar = false;
        timerRA =  new QTimer;
        timerRA->setSingleShot(true);
        connect(timerRA, SIGNAL(timeout()), this, SLOT(reiniciar_alarmas()));

        RAS_tipo = "";
        RAS_estado = 0;
        timerRAS =  new QTimer;
        timerRAS->setSingleShot(true);
        connect(timerRAS, SIGNAL(timeout()), this, SLOT(revisar_alarmas_senpresion()));

        //qDebug() << "Termina de timerRAS";

        PD_vi = "";
        PD_ve = "";
        PD_vm = "";
        PD_fr = "";
        PD_ti = "";
        PD_te = "";
        PD_pip = "";
        PD_peep = "";
        PD_fp = "";
        timerPD =  new QTimer;
        timerPD->setSingleShot(true);
        connect(timerPD, SIGNAL(timeout()), this, SLOT(poner_datos()));

        timerBeep = new QTimer;
        timerBeep->setSingleShot(true);
        connect(timerBeep, SIGNAL(timeout()), this, SLOT(beep()));

        //apagar
        timerListoApagar = new QTimer;
        timerListoApagar->setInterval(3000);
        connect(timerListoApagar, SIGNAL(timeout()), this, SLOT(revisarListoApagar()));
        listoApagarControl = false;
        listoApagarSensores = false;
        listoApagarContador = 0;

        contador_wdt = 0;
        timerErrorWDT =  new QTimer;
        connect(timerErrorWDT, SIGNAL(timeout()), this, SLOT(revisarErrorWDT()));

        //actualizar por wdt
        contador_wdt_ino = 0;
        actualiza_por_wdt = false;

        lista_wdt = new QStringList;

        cambiosCalTeclado = false;
        calTecladoPres = 0;
        calTecladoSolt = 0;

        isReadyModeKeyboard = false;
        valueModeKeyboard = 0;
        isReadyConfigKey = false;
        isWaitingMode = false;

        valuePressKey = 0;
        valueReleaseKey = 0;
        isWaitingKey = 0;
        isReadyConfigKey = 0;
        nameConfigKey = "";
        isConfigKeyboard = false;

        isReadyKeyFromKeyboard = false;
        valueFromKeyboard = "";

        intentar_otro_pwm = true;
        timerOtroPWM = new QTimer;
        timerOtroPWM->setSingleShot(true);
        connect(timerOtroPWM, SIGNAL(timeout()), this, SLOT(iniciar_pruebas_2()));


        //qDebug() << "Termina de cargar todo monitor";

    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
    catch(...){
        qWarning("ERROR AL CREAR CLASE MONITOR");
    }
}

void Monitor::get_mode_keyboard(){
    try {
        //dar formato de la trama y hacer un emit a mainwindow
        QString tt = "gmod\n";
        //emit get_mode_keyboard_frame(tt);
        emit send_frame(tt);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::check_mode_keyboard(QString trama){
    try {
        //checar si estoy esperando el modo o cambiando el modo
        if(isWaitingMode){
            isWaitingMode = false;

            //obtener el valor
            QStringList ttt = trama.split(":");
            valueModeKeyboard = ttt.at(1).toInt();

            isReadyModeKeyboard = true;

        }
        else{
            qDebug() << "No se esperaba un cambio de modo en el teclado";
        }

    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::change_mode(int mode){
    try {
        //dar formato de la trama y hacer un emit a mainwindow
         QString tt = "";
        if(mode == 0){
            tt = "smod0\n";
        }
        else{
            tt = "smod1\n";
        }
        //emit get_mode_keyboard_frame(tt);
        emit send_frame(tt);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::get_config_key(int key){
    try {
        //gchXX\n
        QString temp_num = "";
        if(key < 10){
            temp_num = "0" + QString::number(key);
        }
        else{
            temp_num = QString::number(key);
        }
        QString tt_trama = "gch" + temp_num + "\n";
        //emit get_umbral_key(tt_trama);
        emit send_frame(tt_trama);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::check_umbral_key(QString trama){
    try {
        //checar si estoy esperando el modo o cambiando el modo
        if(isWaitingKey){
            isWaitingKey = false;

            //obtener el valor
            QStringList ttt = trama.split(":");
            QStringList tt = ttt.at(0).split("'");
            nameConfigKey = tt.at(1);
            QStringList t = ttt.at(1).split(",");
            valuePressKey = t.at(0).toInt();
            valueReleaseKey = t.at(1).toInt();

            isReadyConfigKey = true;

        }
        else{
            qDebug() << "No se esperaba un cambio de umbral de tecla";
        }

    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::set_config_key(int key, QString press, QString release){
    try {
        //schXXTTTRRR\n
        QString ttFrame = "sch" + set_format_frame(key, 2) + set_format_frame(press.toInt(), 3) + set_format_frame(release.toInt(), 3) + "\n";
        if(ttFrame.size() == 12){
            emit send_frame(ttFrame);
        }
        else{
            qDebug() << "Error al crear trama config teclado global";
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::set_config_keyboard(QString press, QString release){
    try {
        //setTTTRRR\n
        QString ttFrame = "sch" + set_format_frame(press.toInt(), 3) + set_format_frame(release.toInt(), 3) + "\n";
        if(ttFrame.size() == 10){
            emit send_frame(ttFrame);
        }
        else{
            qDebug() << "Error al crear trama config teclado individual";
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

QString Monitor::set_format_frame(int value, int size){
    try {
        if(size == 2){
            if(value < 10){
                return "0" + QString::number(value);
            }
            else if(10 <= value && value < 100){
                return QString::number(value);
            }
            else{
                return "";
            }
        }
        else if(size == 3){
            if(value < 10){
                return "00" + QString::number(value);
            }
            else if(10 <= value && value < 100){
                return "0" + QString::number(value);
            }
            else if(100 <= value && value < 1000){
                return QString::number(value);
            }
            else{
                return "";
            }
        }
        else{
            return "";
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::get_config_keyboard(){
    try {
        //dar formato de la trama y hacer un emit a mainwindow
        QString tt = "get\n";
        //emit get_umbral_keyboard(tt);
        emit send_frame(tt);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::check_umbral_keyboard(QString trama){
    try {
        //checar si estoy esperando el modo o cambiando el modo
        if(isWaitingConfigKeyboard){
            isWaitingConfigKeyboard = false;

            //obtener el valor
            QStringList ttt = trama.split(":");
            QStringList t = ttt.at(1).split(",");
            valuePressKeyboard = t.at(0).toInt();
            valueReleaseKeyboard = t.at(1).toInt();

            isReadyConfigKeyboard = true;

        }
        else{
            qDebug() << "No se esperaba un cambio de umbral global";
        }

    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::watchDataKeyboard(QString trama){
    try {
        isReadyKeyFromKeyboard = true;
        valueFromKeyboard = trama;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::limpiarInfoAltura(){
    try {
        configPI->label_info->setText("");
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::cambiarAltura(QString tecla){
    try {
        if(tecla == "men"){
            int temp = configPI->le_altura->text().toInt();
            temp += altura_perilla;
            configPI->le_altura->setText(QString::number(temp));
        }
        else if(tecla == "mas"){
            int temp = configPI->le_altura->text().toInt();
            temp -= altura_perilla;
            configPI->le_altura->setText(QString::number(temp));
        }
        else if(tecla == "mod"){
            if(altura_perilla == 1){
                altura_perilla = 10;
            }
            else if(altura_perilla == 10){
                altura_perilla = 100;
            }
            else if(altura_perilla == 100){
                altura_perilla = 1;
            }
            configPI->label_info->setText("Perilla: " + QString::number(altura_perilla));
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void Monitor::cargarAltura(){
    try {
        QString temp = consul->leer_altura();
        QStringList parts = temp.split(",");
        configPI->label_info->setText("");
        configPI->le_altura->setText(parts.at(1));
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void Monitor::aplicarCambiosAltura(){
    try {
        QString altura = configPI->le_altura->text();
        bool entero = false;
        try {
            altura.toInt();
            entero = true;
        }  catch (...) {
            entero = false;
        }
        if(entero){
            /*bool temp = consul->guarda_altura(configPI->le_altura->text());
            if(temp){
                //configPI->label_info->setText("Altura guardada");
                configPI->label_info->setText("Aplicando cambios");
            }
            else{
                configPI->label_info->setText("Error al guardar altura");
            }*/
            configPI->label_info->setText("Aplicando cambios");
            //timerCambiosPerilla->start(2500);
            //formato
            QString temp_s = "";
            int altura_int = altura.toInt();
            if(0 <= altura_int && altura_int < 10){
                temp_s = "0000" + altura;
            }
            else if(10 <= altura_int && altura_int < 100){
                temp_s = "000" + altura;
            }
            else if(100 <= altura_int && altura_int < 1000){
                temp_s = "00" + altura;
            }
            else if(1000 <= altura_int && altura_int < 10000){
                temp_s = "0" + altura;
            }
            else if(10000 <= altura_int && altura_int < 100000){
                temp_s = altura;
            }
            temp_s ="J" + temp_s + "\n";
            serPresion->escribir(temp_s);

        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void Monitor::aplicarAltura(){
    try {
        configPI->hide();
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::actualizar_off_pip(){
    try {
        QString ff = consul->leer_com_pip();
        QStringList lf = ff.split(",");
        offset_pip = lf.at(1).toFloat();
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::actualizar_fio2(){
    try {
        //cargar valores fio2
        QString ff = consul->leer_fio2();
        QStringList lf = ff.split(",");
        tramas->actualizar_formulas(lf[1], lf[2], lf[3], lf[4], lf[5]);
        //mandar a cargar de nuevo las tramas
        actualizarParametros();
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::iniciar_pruebas_2(){
    try {
        iniciar_pruebas();
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::cerrarFugas(){
    try {
        if(!fugas->isHidden()){
            fugas->detener();
            infoAbierta = false;
            pruebas->show();
            ventanaAbierta = true;
            if(sensores_estado){
                pruebas->label_sensores_estado->setText("OK");
                pruebas->label_sensores_estado->setStyleSheet("color: green; background-color: #D5D8DC;");
                pruebas->label_info->setText("Conectar el circuito del paciente y \n pulmón");
            }
            else{
                pruebas->label_info->setText("Error en los sensores");
            }
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::cerrarOxis(){
    try {
        if(!oxis->isHidden()){
            oxis->detener();
            infoAbierta = false;
            numero_prueba++;
            pruebas->label_info->setText("Pruebas oxígeno, retire pulmón.");
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::envia_trama_teclado(QString presionar, QString soltar){
    try {
        QString temp_presionar = "";
        QString temp_soltar = "";
        calTecladoPres = presionar.toInt();
        calTecladoSolt = soltar.toInt();
        if(presionar.size() == 1){
            temp_presionar = "00" + presionar;
        }
        else if(presionar.size() == 2){
            temp_presionar = "0" + presionar;
        }
        else if(presionar.size() == 3){
            temp_presionar = presionar;
        }

        if(soltar.size() == 1){
            temp_soltar = "00" + soltar;
        }
        else if(soltar.size() == 2){
            temp_soltar = "0" + soltar;
        }
        else if(soltar.size() == 3){
            temp_soltar = soltar;
        }

        QString trama = "set" + temp_presionar + temp_soltar + "\n";
        qDebug() << "le mando al teclado: " + trama;
        emit calTeclado(trama);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::revisar_cal_teclado(QString trama){
    try {
        //QString trama = "Umbral:" + presionar + "," + soltar + "\n";
        QStringList parts = trama.split(":");
        QStringList partes = parts.at(1).split(",");
        if(partes.at(0).toInt() == calTecladoPres && partes.at(1).toInt() == calTecladoSolt){
            cambiosCalTeclado = true;
        }
        else{
            qDebug() << "cal-teclado, mal: " + trama;
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::revisarErroresWDT(){
    try {
        //obtener la fecha
        QDateTime hora = QDateTime::currentDateTime();
        //converitr fecha a qstring y agregar la fecha a la lista
        QString hora_s = hora.toString();
        lista_wdt->append(hora_s);
        //checar si hya más de tres horas
        if(lista_wdt->size() > 3){
            int minutos = QDateTime::fromString(lista_wdt->at(0), "hh:mm:ss").secsTo(QDateTime::fromString(lista_wdt->at(lista_wdt->size()-1), "hh:mm:ss"))/60;
            if(minutos < 60){
                qDebug() << "Agregar alarma inoperante por fallo constante en sensores WDT";
                ino_wdt_alarm = true;
                if(! buscar_en_lista("SENSORES")){
                    agregar_en_lista("SENSORES", 1);
                    qDebug() << "SENSORES";
                    if(! estadoAlarmaSensores){
                        estadoAlarmaSensores = true;
                        alarmaControl->iniciaAlarma(alarmaControl->INOPERANTE);
                    }
                    label_debug->setText("E WDT INO");
                    consul->agregar_evento("COMUNICACION", obtener_modo(), "ERROR SENSORES WDT INO");
                }
                else {
                    if(diccionario_alarma->value("SENSORES") == 0){
                        qDebug() << "SENSORES -  reactivar";
                        actualizar_en_lista("SENSORES", 1);
                        if(! estadoAlarmaSensores){
                            estadoAlarmaSensores = true;
                            alarmaControl->iniciaAlarma(alarmaControl->INOPERANTE);
                        }
                    }
                }
            }
        }
        //eliminar las fechas con antigüedad mayor a 60 minutos
        QStringList *respaldo = new QStringList;
        for(int j = 0; j < lista_wdt->size(); j++){
            int minutos = QDateTime::fromString(lista_wdt->at(j), "hh:mm:ss").secsTo(hora)/60;
            if(minutos < 60){
                respaldo->append(lista_wdt->at(j));
            }
        }
        lista_wdt->clear();
        for( int s = 0; s < respaldo->size() ;s++){
            lista_wdt->append(respaldo->at(s));
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::revisarErrorWDT(){
    try {
        if(contador_wdt < 3){
            contador_wdt ++;
            serPresion->escribir("P");
            qDebug() << "revisarErrorWDT - aumenta contador";
        }
        else{
            label_debug->setText("Error WDT");
            consul->agregar_evento("COMUNICACION", obtener_modo(), "ERROR SENSORES WDT");
            if(modoSel == 0 || modoSel == 2 || modoSel == 4){
                if(! buscar_en_lista("SENSORES")){
                    agregar_en_lista("SENSORES", 1);
                    qDebug() << "SENSORES";
                    if(! estadoAlarmaSensores){
                        estadoAlarmaSensores = true;
                        alarmaControl->iniciaAlarma(alarmaControl->INOPERANTE);
                    }
                }
            }
            else{
                if(! buscar_en_lista("SENSORES")){
                    agregar_en_lista("SENSORES", 1);
                    qDebug() << "SENSORES";
                    if(! estadoAlarmaSensores){
                        estadoAlarmaSensores = true;
                        alarmaControl->iniciaAlarma(alarmaControl->INOPERANTE);
                    }
                }
              /*if(vAviso == nullptr){
                  int conta = 0;
                  if(error_sensores_sensor_presion){
                      conta ++;
                  }
                  if(error_sensores_sensor_inhalacion){
                      conta += 2;
                  }
                  if(error_sensores_sensor_exhalacion){
                      conta += 4;
                  }
                  muestraAviso("VENTILADOR INOPERANTE E: " + QString::number(conta));
                  detener_ventilador();
              }*/
            }
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::revisarListoApagar(){
    try {
        if(listoApagarContador < 5){
            listoApagarContador++;
            if(listoApagarControl && listoApagarSensores){
                qDebug() << "Apagar sistema!!!";
                QProcess::execute("sudo shutdown now");
            }
            else{
                if(! listoApagarControl){
                    serVent->envia_trama_config("A2\n");
                }
                if(! listoApagarSensores){
                    serPresion->escribir("A2\n");
                }
            }
        }
        else{
            label_debug->setText("E Apagar");
            listoApagarContador = 0;
            vAvisoC->hide();
            timerListoApagar->stop();

            desactivar_s = false;
            if(! timerConVentilador->isActive()){
                timerConVentilador->start(7000);
            }
            configurandoVentilador = false;

            configurandoSenPresion = false;
            if(! timerTPresion5S->isActive()){
                timerTPresion5S->start(5000);
            }
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::ventilador_detenido(){
    try {
        //qDebug() << "entra a ventilador_detenido";
        if(recibe_a0 && ! estadoVentilador){
            //qDebug() << "entra a ventilador_detenido, valor a0: " + QString::number(recibe_a0) + " estadoVentilador: " + QString::number(estadoVentilador);
            label_debug->setText("Standby");
            consul->agregar_evento("VENTILADOR", obtener_modo(), "DETIENE LA VENTILACION");
            timerVentiladorDetenido->stop();
        }
        /*else{
            qDebug() << "entra a ventilador_detenido, valor a0: " + QString::number(recibe_a0) + " estadoVentilador: " + QString::number(estadoVentilador);
        }*/
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::activar_fio2(){
    try {
        listo_medir_fio2 = true;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::mostrar_confirmacion(QString texto){
    try {
        ventanaAbierta = true;
        ventana_confirmacion->show();
        ventana_confirmacion->label->setText(texto);
        contador_confirmacion = 30;
        ventana_confirmacion->label_time->setText(QString::number(contador_confirmacion)+" seg.");
        timerConfirmacion->start();
        ventana_confirmacion->btn_si->setStyleSheet(ventana_confirmacion->btn);
        ventana_confirmacion->btn_no->setStyleSheet(ventana_confirmacion->btnSeleccionado);
        boton_seleccionado_confirmacion = 1;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::espera_si_confirmacion(){
    try {
        if(timerConfirmacion->isActive()){
            timerConVentilador->stop();
        }
        contador_confirmacion = 0;
        ventana_confirmacion->hide();
        ventanaAbierta = false;
        if(espera_parar){
            controlVentilador();
            espera_parar = false;
        }
        else if(espera_iniciar){
            controlVentilador();
            espera_parar = false;
        }
        else if(espera_actualizar){
            actualizarDatosVentilador();
            espera_actualizar = false;
        }
        else if(espera_apagar){
            //QProcess::execute("sudo shutdown now");
            muestraAvisoApagar("Apagando...");

            desactivar_s = true;
            if(! banderaConexionVentilador){
                while(! banderaConexionVentilador && contadorBanderaConxVent < 25){
                    QThread::msleep(200);
                    contadorBanderaConxVent++;
                }
                contadorBanderaConxVent = 0;
            }
            if(timerConVentilador->isActive()){
                timerConVentilador->stop();
            }
            configurandoVentilador = true;

            configurandoSenPresion = true;
            if(timerTPresion5S->isActive()){
                timerTPresion5S->stop();
            }

            timerListoApagar->start();
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::espera_no_confirmacion(){
    try {
        if(espera_parar){
            espera_parar = false;
        }
        else if(espera_iniciar){
            espera_parar = false;
        }
        else if(espera_actualizar){
            espera_actualizar = false;
        }
        else if(espera_apagar){
            espera_apagar = false;
            contador_apagar = 0;
        }
        contador_confirmacion = 30;
        timerConfirmacion->stop();
        ventana_confirmacion->hide();
        ventanaAbierta = false;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::timer_esperando_confirmacion(){
    try {
        if(contador_confirmacion > 0){
            contador_confirmacion -= 1;
            ventana_confirmacion->label_time->setText(QString::number(contador_confirmacion) + " seg.");
        }
        else{
            contador_confirmacion = 30;
            timerConfirmacion->stop();
            ventana_confirmacion->hide();
            contador_apagar = 0;
            espera_parar = false;
            espera_iniciar = false;
            espera_actualizar = false;
            espera_apagar = false;
            ventanaAbierta = false;
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::tecla_confirmacion(QString tecla){
    try {
        if(tecla == "izq" || tecla == "der" || tecla == "arr" || tecla == "aba"){
            if(boton_seleccionado_confirmacion == 0){
                ventana_confirmacion->btn_si->setStyleSheet(ventana_confirmacion->btn);
                ventana_confirmacion->btn_no->setStyleSheet(ventana_confirmacion->btnSeleccionado);
                boton_seleccionado_confirmacion = 1;
            }
            else{
                ventana_confirmacion->btn_si->setStyleSheet(ventana_confirmacion->btnSeleccionado);
                ventana_confirmacion->btn_no->setStyleSheet(ventana_confirmacion->btn);
                boton_seleccionado_confirmacion = 0;
            }
        }
        else if(tecla == "ok"){
            if(boton_seleccionado_confirmacion == 0){
                espera_si_confirmacion();
            }
            else{
                espera_no_confirmacion();
            }
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::cambiagraficas(){
    try {
        if(! cambiagrafi){
            //obtener_rangos_lazos();
            esperando_limites_lazos = true;

            /*while(auto item = graphiclayout->takeAt(0)){
                delete item->widget();

            }*/
            while(graphiclayout->count()){
                QWidget *widget = graphiclayout->itemAt(0)->widget();
                if(widget){
                    graphiclayout->removeWidget(widget);
                    delete widget;
                }
            }

            graficaPV = new WidgetGraficaLazo(this, "graficaPV", "VOLUMEN", min_lazo_vol_y, max_lazo_vol_y, "PRESION", min_lazo_pres_x, max_lazo_pres_x, Qt::yellow, 50);
            graphiclayout->addWidget(graficaPV, 1,0);
            graficaVF = new WidgetGraficaLazo(this, "graficaVF", "FLUJO", min_lazo_flujo_y, max_lazo_flujo_y, "VOLUMEN", min_lazo_vol_x, max_lazo_vol_x, Qt::green, 50);
            graphiclayout->addWidget(graficaVF, 1,1);

            cambiagrafi = true;
            limpiar_graficas();
            submenugrafica->btntipografica->setText("ONDAS");
        }
        else{
            /*while(auto item = graphiclayout->takeAt(0)){
                delete item->widget();

            }*/
            while(graphiclayout->count()){
                QWidget *widget = graphiclayout->itemAt(0)->widget();
                if(widget){
                    graphiclayout->removeWidget(widget);
                    delete widget;
                }
            }

            cambiagrafi = false;

            graficaPresion = new WidgetGrafica(this, "graficaPresion", "PRESION", -5, 35, Qt::green, 50);
            graphiclayout->addWidget(graficaPresion, 0,1);
            graficaVolumen = new WidgetGrafica(this, "graficaVolumen", "VOLUMEN", -0.5, 1.5, Qt::blue, 50);
            graphiclayout->addWidget(graficaVolumen, 1,1);
            graficaFlujo = new WidgetGrafica(this, "graficaFlujo", "FLUJO", -150, 150, Qt::yellow, 50);
            graphiclayout->addWidget(graficaFlujo, 2,1);

            submenugrafica->btntipografica->setText("LAZOS");
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::limpiar_graficas(){
    try {
        if(! cambiagrafi){
            graficaPresion->grafica->graph(0)->data().data()->clear();
            graficaVolumen->grafica->graph(0)->data().data()->clear();
            graficaFlujo->grafica->graph(0)->data().data()->clear();

        }
        else{
            qDebug() << "Aqui debería borrar lazos";
            //graficaPV->grafica->graph(0)->data().data()->clear();
            graficaPV->limpiar();
            graficaPV->grafica->replot();
            //graficaVF->grafica->graph(0)->data().data()->clear();
            graficaVF->limpiar();
            graficaVF->grafica->replot();
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::abrir_menu_graficas(){
    try {
        if(submenugrafica->isHidden()){
            submenugrafica->show();
        }
        else{
            submenugrafica->hide();
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::abrir_menu(){
    try {
        menu->show();
        ventanaAbierta = true;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::tecla_menu(QString tecla){
    try {
        if(tecla == "izq" || tecla == "der" || tecla == "arr" || tecla == "aba"){
            if(boton_seleccionado_menu == 0){
                menu->btn_calibrar->setStyleSheet(menu->btn);
                menu->btn_pruebas->setStyleSheet(menu->btnSeleccionado);
                boton_seleccionado_menu = 1;
            }
            else{
                menu->btn_calibrar->setStyleSheet(menu->btnSeleccionado);
                menu->btn_pruebas->setStyleSheet(menu->btn);
                boton_seleccionado_menu = 0;
            }
        }
        else if(tecla == "ok"){
            if(boton_seleccionado_menu == 0){
                abrir_calibracion();
            }
            else{
                abrir_pruebas();
            }
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::abrir_pruebas(){
    try {
        //preguntar si el ventilador está activo, sino, entonces sí abre las preubas
        if(estadoVentilador){
            espera_parar = true;
            mostrar_confirmacion("¿Está seguro de parar el ventilador?");
        }
        else{
            menu->close();
            //aqui se debe abrir las instrucciones de fugas
            fugas->mostrar();
            infoAbierta = true;
            ventanaAbierta = true;
            intentar_otro_pwm = true;
        }
        /*pruebas->show();
        ventanaAbierta = true;
        if(sensores_estado){
            pruebas->label_sensores_estado->setText("OK");
            pruebas->label_sensores_estado->setStyleSheet("color: green; background-color: #D5D8DC;");
            pruebas->label_info->setText("Conectar el circuito del paciente y \ntapar la entrada");
        }
        else{
            pruebas->label_info->setText("Error en los sensores");
        }*/
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::tecla_pruebas(QString tecla){
    try {
        if(tecla == "izq" || tecla == "der" || tecla == "arr" || tecla == "aba"){
            if(boton_seleccionado_pruebas == 0){
                pruebas->btn_iniciar->setStyleSheet(pruebas->btn);
                pruebas->btn_siguiente->setStyleSheet(pruebas->btnSeleccionado);
                boton_seleccionado_pruebas = 1;
            }
            else{
                pruebas->btn_iniciar->setStyleSheet(pruebas->btnSeleccionado);
                pruebas->btn_siguiente->setStyleSheet(pruebas->btn);
                boton_seleccionado_pruebas = 0;
            }
        }
        else if(tecla == "ok"){
            if(!configPI->isHidden()){
                aplicarCambiosAltura();
            }
            else{
                if(!pruebas_iniciales){
                    if(boton_seleccionado_pruebas == 0){
                        iniciar_pruebas();
                    }
                    else{
                        siguiente_pruebas();
                    }
                }
            }
        }
        else if(tecla == "con"){
            //falta agregar el estado de las pruebas inciales
            if(!pruebas_iniciales){
                if(configPI->isHidden()){
                    configPI->show();
                    //aquí se carga el valor de la altura
                    cargarAltura();
                }
                else{
                    configPI->hide();
                }
            }
        }
        else if(tecla == "mas" || tecla == "men" || tecla == "mod"){
            cambiarAltura(tecla);
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::tecla_info(QString tecla){
    try {
        if(tecla == "ok"){
            if(!fugas->isHidden()){
                cerrarFugas();
            }
            else if(!oxis->isHidden()){
                cerrarOxis();
            }
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::iniciar_pruebas(){
    try {
        if(! pruebas_iniciales){
            if(numero_prueba == 0){
                if(sensores_estado){
                    pruebas->label_info->setText("Iniciando prueba de presión-válvulas");
                    consul->agregar_evento("PRUEBAS", obtener_modo(),"INICIAN PRUEBAS PRESION-VALVULAS");
                    if(! banderaConexionVentilador){
                        while(!banderaConexionVentilador && contadorBanderaConxVent < 25){
                            QThread::msleep(200);
                            contadorBanderaConxVent++;
                        }
                        contadorBanderaConxVent = 0;
                    }
                    if(timerConVentilador->isActive()){
                        timerConVentilador->stop();
                    }
                    QThread::sleep(1);
                    presion_tope = dic_presion_tope->value(contador_pruebas_iniciales);
                    pruebas_iniciales = true;

                    QString t_trama = dic_trama_valvulas->value(contador_valvulas);
                    serVent->envia_trama_config(t_trama);
                    serPresion->escribir("G1\n");
                }
            }
            else if(numero_prueba == 1){
                if(! banderaConexionVentilador){
                    while(!banderaConexionVentilador && contadorBanderaConxVent < 25){
                        QThread::msleep(200);
                        contadorBanderaConxVent++;
                    }
                    contadorBanderaConxVent = 0;
                }
                if(timerConVentilador->isActive()){
                    timerConVentilador->stop();
                }
                QThread::sleep(1);
                consul->agregar_evento("PRUEBAS", obtener_modo(),"INICIAN PRUEBAS OXIGENO");
                pruebas->label_info->setText("Leyendo sensor de oxígeno");
                serVent->envia_trama_config("O0\n");
                contador_timerOxigeno = 0;
                timerOxigeno->start(1000);
                pruebas_iniciales = true;
                serPresion->escribir("G1\n");
            }
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::siguiente_pruebas(){
    try {
        if(pruebas_terminadas){
            pruebas->close();
            ventanaAbierta = false;
        }
        else{
            if(numero_prueba == 0){
                /*numero_prueba++;
                pruebas->label_info->setText("Pruebas oxígeno, retire circuito de paciente.");*/
                //aqui se debe mostrar la sinstrucciones del oximetro
                oxis->mostrar();
                infoAbierta = true;
                pruebas->btn_siguiente->setText("Cerrar");
            }
            else{
                qDebug() << "Pruebas no terminadas";
                pruebas->btn_siguiente->setText("Siguiente");
                pruebas->close();
                ventanaAbierta = false;
                consul->agregar_evento("INICIO", obtener_modo(), "ENTRA A VENTILACION SIN PASAR PRUEBAS INICIALES");
            }

        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::prueba_presion(){
    try {
        pruebas->label_info->setText("No se llegó a la presión deseada");
        qDebug() << "presion maxima en aumento de presion: " + QString::number(presion_pruebas);
        detener_pruebas_presion();
        //aqui se pregunta por la bandera para ver si se vuelve a intentar
        if(intentar_otro_pwm){
            qDebug() << "*************Intentar otro PWM!!!";
            intentar_otro_pwm = false;
            pwm_100 = "0210";
            dic_trama_valvulas->clear();
            dic_trama_valvulas->insert(0, "T"+pwm_100+pwm_0+pwm_100+exa_1+estado_trama_valvulas + "\n");
            dic_trama_valvulas->insert(1, "T"+pwm_0+pwm_0+pwm_0+"01" + "\n");
            dic_trama_valvulas->insert(2, "T"+pwm_100+pwm_0+pwm_100+exa_1+estado_trama_valvulas + "\n");
            dic_trama_valvulas->insert(3, "T"+pwm_0+pwm_0+pwm_0+"01" + "\n");
            //mandar a iniciar de nuevo las pruebas iniciales
            timerOtroPWM->start(1200);
            pruebas->label_info->setText("Esp ctrl");
        }
        else{
            qDebug() << "*************Ya no intentar otro PWM!!!";
            pwm_100 = "0170";
            dic_trama_valvulas->clear();
            dic_trama_valvulas->insert(0, "T"+pwm_100+pwm_0+pwm_100+exa_1+estado_trama_valvulas + "\n");
            dic_trama_valvulas->insert(1, "T"+pwm_0+pwm_0+pwm_0+"01" + "\n");
            dic_trama_valvulas->insert(2, "T"+pwm_100+pwm_0+pwm_100+exa_1+estado_trama_valvulas + "\n");
            dic_trama_valvulas->insert(3, "T"+pwm_0+pwm_0+pwm_0+"01" + "\n");
            pruebas->label_valvulas_estado->setText("Error");
            pruebas->label_valvulas_estado->setStyleSheet("color: red; background-color: #D5D8DC;");
            pruebas->label_presion_estado->setText("Error");
            pruebas->label_presion_estado->setStyleSheet("color: red; background-color: #D5D8DC;");
            consul->agregar_evento("PRUEBAS", obtener_modo(),"ERROR PRESION FUGA");
        }

    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::prueba_presion_final(){
    try {
        serVent->envia_trama_config("Q\n");
        revisar_presion_tope = true;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::prueba_presion_salida(){
    try {
        serVent->envia_trama_config("Q\n");
        revisar_liberacion_presion = true;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::detener_pruebas_presion(){
    try {
        pruebas_iniciales = false;
        //threading.Thread(target=self.beep,args=(852, 3, 0.2, 0.2,)).start()
        beep_frecuencia = 852;
        beep_veces = 3;
        beep_tiempo = 0.2;
        beep_pausa = 0.2;
        timerBeep->start(100);
        serVent->envia_trama_config("T00000000000000\n");
        QString temp_tope = QString::number(dic_presion_tope->value(contador_pruebas_iniciales));
        serPresion->escribir("G0\n");
        qDebug() << "*****Deteniendo pruebas de presion";
        contador_valvulas = 0;
        contador_timerOxigeno = 0;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::revisar_fin_prueba_presion(){
    try {
        if(fin_prueba_presion_serpresion && fin_prueba_presion_serventilador){
            qDebug() << "Terminan las pruebas correctamente";
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::respuesta_oxigeno(){
    try {
        if(contador_timerOxigeno < 65){
            contador_timerOxigeno++;
            pruebas->label_info->setText("Prueba oxígeno " +QString::number((contador_timerOxigeno*100)/65) + " %");

        }
        else{
            pruebas->label_info->setText("No se recibió respuesta");
            pruebas->label_oxigeno_estado->setText("Error");
            pruebas->label_oxigeno_estado->setStyleSheet("color: red; background-color: #D5D8DC;");
            consul->agregar_evento("PRUEBAS", obtener_modo(), "NO RESPUESTA OXIGENO");
            serPresion->escribir("G0\n");
        }

    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::abrir_calibracion(){
    try {
        menu->close();
        ventanaAbierta = false;
        consul->agregar_evento("INICIO", obtener_modo(),"ENTRA A VENTILACION SIN PRUEBAS INICIALES");
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::tecla_calibracion(QString tecla){
    try {
        if(tecla == "ok"){
            cerrar_calibracion();
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::cerrar_calibracion(){
    try {
        calibrar->close();
        ventanaAbierta = false;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::actuaTest(){
    try {
        qDebug() << "Actualiza mensaje de pantalla de estado";
        widgetAlarms->bateria(55, 1);
        widgetAlarms->trigger(1);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::retranslate_ui(){
    try {
        label_Modo->setText("Modo: Volumen");
        btn_ventilador->setText("ACTUALIZAR\nPARAM VENT");
        btn_grafica->setText("GRAFICA");
        btn_test->setText("PRUEBA");
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::preguntarVersiones(){
    try {
        qDebug() << "Solicitud de versiones a las tarjetas";
        serVent->envia_trama_config("F\n");
        serPresion->escribir("F");
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::revisarTerminaConfigurar(){
    try {
        if(contadorTerminaConfigurar < 20){
            contadorTerminaConfigurar ++;
            if(tecladoListo){
                if(ventiladorListo && senPresionListo){
                    if(vAvisoC->isVisible()){
                        label_debug->setText("Config Lista");
                        vAvisoC->close();
                        timerTerminaConfigurar->stop();
                        inicializacion = true;
                        if(! recuperado){
                            abrir_menu();
                        }
                        else{
                            label_debug->setText("Vent ON");
                        }
                    }
                }
            }
        }
        else{
            qDebug() << "Termina tiempo de espera, no se pudo terminar la configuracion";
            if(tecladoListo){
                qDebug() << "Teclado listo" ;
            }
            else{
                qDebug() << "Teclado NO listo" ;
            }
            if(ventiladorListo){
                qDebug() << "Ventilador listo" ;
            }
            else{
                qDebug() << "Ventilador NO listo" ;
            }
            if(senPresionListo){
                qDebug() << "Senpresion listo" ;
            }
            else{
                qDebug() << "Senpresion NO listo" ;
            }

            QStringList *tt = new QStringList{"Configuracion", "", "", "", "ERROR"};
            vAvisoC->textoMostrar(tt);
            timerTerminaConfigurar->stop();
            label_debug->setText("Error config");
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

/*void Monitor::configurar_grafica(QString nombre, QString titulo, float min, float max){
    try {

    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::configurar_grafica_lazo(QString nombre, QString tituloy, QString titulox, float miny, float maxy, float minx, float maxx){
    try {

    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}*/

void Monitor::limpiarBuffer(){
    try {
        qDebug() << "Limpiar Buffer!!!!";
        QString  basura = serPresion->serPuerto->readAll();
        serPresion->serPuerto->clear(QSerialPort::Input);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::revisarEstadoSenPresion(){
    try {
        if(! banderaTimerEstadoSenPresion){
            if(contadorTimerEstadoSenPresion < 3){
                contadorTimerEstadoSenPresion++;
            }
            else{
                qDebug() << "Esta detenido senpresion";
                timerEstadoSenPresion->stop();
            }
        }
        else{
            timerEstadoSenPresion->stop();
            qDebug() << "Esta activo senpresion";
            senPresionListo = true;
            estadoVentilador = true;
            serPresion->corriendo = true;
            serVent->corriendo = true;
            serPresion->serPuerto->clear();
            recuperado = true;
            tpresionModo = 1;
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::iniciaMonSensores(){
    try {
        if(serPresion->estado()){
            qDebug() << "Iniciand monitor de tarjeta de sensores";
            serPresion->escribir("P");
            timerTPresion5S->start(5000);
            timerActivo5S = true;
            tpresionModo = 0;
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::contornoColor(WidgetSigno3 *widget){
    try {
        QString color = widget->color;
        QString nombre = widget->objectName();
        widget->setStyleSheet("QWidget#"+nombre+" {border: 3Px solid "+color+"; border-radius: 3Px;}");
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::contornoColorAlarma(WidgetSigno3 *widget, QString color){
    try {
        QString nombre = widget->objectName();
        widget->setStyleSheet("QWidget#"+nombre+" {border: 3Px solid "+color+"; border-radius: 3Px;}");
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::actualizarParametros(){
    try {
        label_debug->setText("");
        actualizarAlarmas();
        llenarConfiguracionPCMV();
        llenarConfiguracionVCMV();
        llenarConfiguracionPSIMV();
        llenarConfiguracionVSIMV();
        llenarConfiguracionPCPAP();
        llenarConfiguracionVCPAP();
        obtener_trama_config();
        obtener_trama_c_senpresion();
        obtener_trama_alarmas_senpresion();

        qDebug() << "tram trama: " + tramaVentilador;
        QString  fr = tramaVentilador.mid(14,3);
        int fr_int = fr.toInt();
        tiempo_respuesta_ventilador = static_cast<int>((120/fr_int)*1000);
        elementoSeleccionado();
        if(huboCambioTramaSenPresion || huboCambioTrama){
            if(estadoVentilador){
                label_debug->setText("Presione ACTUALIZAR");
            }
            else{
                label_debug->setText("Presione INICIAR");
            }
        }
        QString temp = consul->leer_altura();
        QStringList tt = temp.split(",");
        altura_prog = tt[1].toInt();
        QString tip = consul->leer_tipo_sensor();
        if(tip[2] == "1"){
            tipo_sensor_presion = true;
        }
        else{
            tipo_sensor_presion = false;
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::obtener_trama_alarmas_senpresion(){
    try {
        trama_w_serpresion = tramas->obtener_trama_alarmas();
        qDebug() << "TRAMA W!!: " + trama_w_serpresion;
        trama_w = trama_w_serpresion;
        if(primera_vez_modo_sen_presion_w){
            primera_vez_modo_sen_presion_w = false;
            trama_w_ultima = trama_w;
        }
        else{
            if(trama_w != trama_w_ultima){
                if(estadoVentilador){
                    label_debug->setText("Presione ACTUALIZAR");
                }
                else{
                    label_debug->setText("Presione INICIAR");
                }
                huboCambioTramaSenPresionW = true;
                trama_w_ultima = trama_w;

            }
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::obtener_configuracion_PCMV(){
    try {
        tramas->obtener_trama_serpresion_config(0);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::obtener_configuracion_VCMV(){
    try {
        tramas->obtener_trama_serpresion_config(1);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::obtener_configuracion_PSIMV(){
    try {
        tramas->obtener_trama_serpresion_config(2);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::obtener_configuracion_VSIMV(){
    try {
        tramas->obtener_trama_serpresion_config(3);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::obtener_configuracion_PCPAP(){
    try {
        tramas->obtener_trama_serpresion_config(4);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::obtener_configuracion_VCPAP(){
    try {
        tramas->obtener_trama_serpresion_config(5);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::llenarConfiguracionPCMV(){
    try {
        QStringList parts_default;
        QString ult_config = consul->buscar_ult_config("PCMV");
        if(ult_config != ""){
            parts_default = ult_config.split(",");
        }
        else{
            QString default_config = consul->cargar_config_default("PCMV");
            parts_default = default_config.split(",");
        }
        tramas->llenar_modo(0, parts_default, alarma_pres_max);
        QString modo = consul->leer_modo();
        if(modo[2] == "0"){
            float temp = parts_default.at(1).toFloat() + parts_default.at(3).toFloat();
            signoPEEP->label_title->setText("PEEP");
            signoPIP->setValorProg("", QString::number(temp), alarma_pres_max);
            signoPEEP->setValorProg(alarma_pres_min, parts_default.at(3), "");
            widgetFR->setValorProg(alarma_fr_min, parts_default.at(4), alarma_fr_max);
            signoTiempoI->setValorProg("", QString::number(parts_default.at(5).toFloat(),'f',1), "");
            signoPLATEU->setValorProg("", parts_default.at(7), "");
            signoVm->setValorProg(QString::number(alarma_volmin_min.toFloat(),'f',1),"-",QString::number(alarma_volmin_max.toFloat(),'f',1));
            widgetVoli->setValorProg(alarma_vol_min, "-", alarma_vol_max);
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::llenarConfiguracionVCMV(){
    try {
        QStringList parts_default;
        QString ult_config = consul->buscar_ult_config("VCMV");
        if(ult_config != ""){
            parts_default = ult_config.split(",");
        }
        else{
            QString default_config = consul->cargar_config_default("VCMV");
            parts_default = default_config.split(",");
        }
        tramas->llenar_modo(1, parts_default, alarma_pres_max);
        QString modo = consul->leer_modo();
        if(modo[2] == "1"){
            signoPEEP->label_title->setText("PEEP");
            widgetVoli->setValorProg(alarma_vol_min, parts_default.at(1), alarma_vol_max);
            signoPEEP->setValorProg(alarma_pres_min, parts_default.at(2), "");
            widgetFR->setValorProg(alarma_fr_min, parts_default.at(3), alarma_fr_max);
            widgetFlujo->setValorProg("", parts_default.at(4), "");
            signoPLATEU->setValorProg("", parts_default.at(7), "");
            signoVm->setValorProg(QString::number(alarma_volmin_min.toFloat(),'f',1),"-",QString::number(alarma_volmin_max.toFloat(),'f',1));
            signoPIP->setValorProg("", "-", alarma_pres_max);
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::llenarConfiguracionPSIMV(){
    try {
        QStringList parts_default;
        QString ult_config = consul->buscar_ult_config("PSIMV");
        if(ult_config != ""){
            parts_default = ult_config.split(",");
        }
        else{
            QString default_config = consul->cargar_config_default("PSIMV");
            parts_default = default_config.split(",");
        }
        tramas->llenar_modo(2, parts_default, alarma_pres_max);
        QString modo = consul->leer_modo();
        if(modo[2] == "2"){
            float temp = parts_default.at(1).toFloat() + parts_default.at(3).toFloat();
            signoPEEP->label_title->setText("PEEP");
            signoPIP->setValorProg("", QString::number(temp), alarma_pres_max);
            signoPEEP->setValorProg(alarma_pres_min, parts_default.at(3), "");
            widgetFR->setValorProg(alarma_fr_min, parts_default.at(4), alarma_fr_max);
            signoTiempoI->setValorProg("", QString::number(parts_default.at(5).toFloat(),'f',1), "");
            signoPLATEU->setValorProg("", parts_default.at(7), "");
            signoVm->setValorProg(QString::number(alarma_volmin_min.toFloat(),'f',1),"-",QString::number(alarma_volmin_max.toFloat(),'f',1));
            widgetVoli->setValorProg(alarma_vol_min, "-", alarma_vol_max);
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::llenarConfiguracionVSIMV(){
    try {
        QStringList parts_default;
        QString ult_config = consul->buscar_ult_config("VSIMV");
        if(ult_config != ""){
            parts_default = ult_config.split(",");
        }
        else{
            QString default_config = consul->cargar_config_default("VSIMV");
            parts_default = default_config.split(",");
        }
        tramas->llenar_modo(3, parts_default, alarma_pres_max);
        QString modo = consul->leer_modo();
        if(modo[2] == "3"){
            signoPEEP->label_title->setText("PEEP");
            widgetVoli->setValorProg(alarma_vol_min, parts_default.at(1), alarma_vol_max);
            signoPEEP->setValorProg(alarma_pres_min, parts_default.at(3), "");
            widgetFR->setValorProg(alarma_fr_min, parts_default.at(4), alarma_fr_max);
            widgetFlujo->setValorProg("", parts_default.at(5), "");
            signoPLATEU->setValorProg("", parts_default.at(10), "");
            signoVm->setValorProg(QString::number(alarma_volmin_min.toFloat(),'f',1),"-",QString::number(alarma_volmin_max.toFloat(),'f',1));
            signoPIP->setValorProg("", "-", alarma_pres_max);
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::llenarConfiguracionPCPAP(){
    try {
        QStringList parts_default;
        QString ult_config = consul->buscar_ult_config("PCPAP");
        if(ult_config != ""){
            parts_default = ult_config.split(",");
        }
        else{
            QString default_config = consul->cargar_config_default("PCPAP");
            parts_default = default_config.split(",");
        }
        tramas->llenar_modo(4, parts_default, alarma_pres_max);
        QString modo = consul->leer_modo();
        if(modo[2] == "4"){
            signoPEEP->label_title->setText("CPAP");
            widgetVoli->setValorProg(alarma_vol_min, "-", alarma_vol_max);
            signoPEEP->setValorProg(alarma_pres_min, parts_default.at(1), "");
            widgetFR->setValorProg(alarma_fr_min, parts_default.at(8), alarma_fr_max);
            widgetFlujo->setValorProg("", "", "");
            signoPLATEU->setValorProg("", parts_default.at(3), "");
            signoVm->setValorProg(QString::number(alarma_volmin_min.toFloat(),'f',1),"-",QString::number(alarma_volmin_max.toFloat(),'f',1));
            float temp = parts_default.at(1).toFloat() + parts_default.at(9).toFloat();
            signoPIP->setValorProg("", QString::number(temp), alarma_pres_max);
            signoTiempoI->setValorProg("", QString::number(parts_default.at(10).toFloat(),'f',1), "");
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::llenarConfiguracionVCPAP(){
    try {
        QStringList parts_default;
        QString ult_config = consul->buscar_ult_config("VCPAP");
        if(ult_config != ""){
            parts_default = ult_config.split(",");
        }
        else{
            QString default_config = consul->cargar_config_default("VCPAP");
            parts_default = default_config.split(",");
        }
        tramas->llenar_modo(5, parts_default, alarma_pres_max);
        QString modo = consul->leer_modo();
        if(modo[2] == "5"){
            signoPEEP->label_title->setText("CPAP");
            widgetVoli->setValorProg(alarma_vol_min, parts_default.at(9), alarma_vol_max);
            signoPEEP->setValorProg(alarma_pres_min, parts_default.at(1), "");
            widgetFR->setValorProg(alarma_fr_min, parts_default.at(8), alarma_fr_max);
            widgetFlujo->setValorProg("", parts_default.at(10), "");
            signoPLATEU->setValorProg("", parts_default.at(3), "");
            signoVm->setValorProg(QString::number(alarma_volmin_min.toFloat(),'f',1),"-",QString::number(alarma_volmin_max.toFloat(),'f',1));
            signoPIP->setValorProg("", parts_default.at(2), alarma_pres_max);
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::actualizarAlarmas(){
    try {
        QStringList parts_default;
        QString ult_config = consul->buscar_ult_config_alarm();
        if(ult_config != ""){
            parts_default = ult_config.split(",");
            if(parts_default.size() == 14){
                cargaValoresDBAlarmas(parts_default);
            }
        }
        else{
            QString default_config = consul->cargar_config_default_alarm();
            parts_default = default_config.split(",");
            if(parts_default.size() == 14){
                cargaValoresDBAlarmas(parts_default);
            }
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::cargaValoresDBAlarmas(QStringList valores){
    try {
        if(valores.size() == 14){
            tramas->llenar_alarmas(valores);
            alarma_pres_max = valores.at(1);
            alarma_pres_min = valores.at(2);
            alarma_volmin_max = valores.at(3);
            alarma_volmin_min = valores.at(4);
            alarma_fr_max = valores.at(5);
            alarma_fr_min = valores.at(6);
            alarma_vol_max = valores.at(7);
            alarma_vol_min = valores.at(8);
            alarma_apnea = valores.at(13);
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::obtener_trama_config(){
    try {
        QString modo = consul->leer_modo();
        if(modo[2] == "0"){
            modoSel = 0;
            obtenerTramaPCMV();
            modoVentilador = "MODO: PCMV";
        }
        else if(modo[2] == "1"){
            modoSel = 1;
            obtenerTramaVCMV();
            modoVentilador = "MODO: VCMV";
        }
        else if(modo[2] == "2"){
            modoSel = 2;
            obtenerTramaPSIMV();
            modoVentilador = "MODO: PSIMV";
        }
        else if(modo[2] == "3"){
            modoSel = 3;
            obtenerTramaVSIMV();
            modoVentilador = "MODO: VSIMV";
        }
        else if(modo[2] == "4"){
            modoSel = 4;
            obtenerTramaPCPAP();
            modoVentilador = "MODO: PCPAP";
        }
        else if(modo[2] == "5"){
            modoSel = 5;
            obtenerTramaVCPAP();
            modoVentilador = "MODO: VCPAP";
        }
        label_Modo->setText(modoVentilador);
        if(primera_vez_modo){
            primera_vez_modo = false;
            nuevoModo = modoVentilador;
            ultimoModo = modoVentilador;
        }
        else{
            nuevoModo = modoVentilador;
            if(nuevoModo != ultimoModo){
                huboCambioModo = true;
                if(estadoVentilador){
                    label_debug->setText("Presione ACTUALIZAR");
                }
                else{
                    label_debug->setText("Presione INICIAR");
                }
                consul->agregar_evento("VENTILADOR", obtener_modo(), "CAMBIO DE " + ultimoModo.mid(6) + " A: " + nuevoModo.mid(6));
                ultimoModo = nuevoModo;
            }
            else{
                huboCambioModo = false;
            }
        }
        obtener_configuracion_PCMV();
        obtener_configuracion_VCMV();
        obtener_configuracion_PSIMV();
        obtener_configuracion_VSIMV();
        obtener_configuracion_PCPAP();
        obtener_configuracion_VCPAP();
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::obtenerTramaPCMV(){
    try {
        tramaVentilador = tramas->obtener_trama_ventilador(0);
        if(primera_vez_modo){
            primera_vez_modo = false;
            ultimaTrama = tramaVentilador;
        }
        else{
            if(tramaVentilador != ultimaTrama){
                huboCambioTrama = true;
                ultimaTrama = tramaVentilador;
                if(estadoVentilador){
                    label_debug->setText("Pulse ACTUALIZAR");
                }
                else{
                    label_debug->setText("Pulse INICIAR");
                }

            }
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::obtenerTramaVCMV(){
    try {
        tramaVentilador = tramas->obtener_trama_ventilador(1);
        if(primera_vez_modo){
            primera_vez_modo = false;
            ultimaTrama = tramaVentilador;
        }
        else{
            if(tramaVentilador != ultimaTrama){
                huboCambioTrama = true;
                ultimaTrama = tramaVentilador;
                if(estadoVentilador){
                    label_debug->setText("Pulse ACTUALIZAR");
                }
                else{
                    label_debug->setText("Pulse INICIAR");
                }

            }
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::obtenerTramaPSIMV(){
    try {
        tramaVentilador = tramas->obtener_trama_ventilador(2);
        if(primera_vez_modo){
            primera_vez_modo = false;
            ultimaTrama = tramaVentilador;
        }
        else{
            if(tramaVentilador != ultimaTrama){
                huboCambioTrama = true;
                ultimaTrama = tramaVentilador;
                if(estadoVentilador){
                    label_debug->setText("Pulse ACTUALIZAR");
                }
                else{
                    label_debug->setText("Pulse INICIAR");
                }

            }
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::obtenerTramaVSIMV(){
    try {
        tramaVentilador = tramas->obtener_trama_ventilador(3);
        if(primera_vez_modo){
            primera_vez_modo = false;
            ultimaTrama = tramaVentilador;
        }
        else{
            if(tramaVentilador != ultimaTrama){
                huboCambioTrama = true;
                ultimaTrama = tramaVentilador;
                if(estadoVentilador){
                    label_debug->setText("Pulse ACTUALIZAR");
                }
                else{
                    label_debug->setText("Pulse INICIAR");
                }

            }
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::obtenerTramaPCPAP(){
    try {
        tramaVentilador = tramas->obtener_trama_ventilador(4);
        if(primera_vez_modo){
            primera_vez_modo = false;
            ultimaTrama = tramaVentilador;
        }
        else{
            if(tramaVentilador != ultimaTrama){
                huboCambioTrama = true;
                ultimaTrama = tramaVentilador;
                if(estadoVentilador){
                    label_debug->setText("Pulse ACTUALIZAR");
                }
                else{
                    label_debug->setText("Pulse INICIAR");
                }

            }
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::obtenerTramaVCPAP(){
    try {
        tramaVentilador = tramas->obtener_trama_ventilador(5);
        if(primera_vez_modo){
            primera_vez_modo = false;
            ultimaTrama = tramaVentilador;
        }
        else{
            if(tramaVentilador != ultimaTrama){
                huboCambioTrama = true;
                ultimaTrama = tramaVentilador;
                if(estadoVentilador){
                    label_debug->setText("Pulse ACTUALIZAR");
                }
                else{
                    label_debug->setText("Pulse INICIAR");
                }

            }
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::cargarTramaOffsets(){
    try {
        QString con = consul->leer_offsets();
        //qDebug() << "cargarTramaOffsets: " + con;
        QStringList parts = con.split(",");
        QStringList temp_list;
        temp_list.append(parts.at(1));
        temp_list.append(parts.at(2));
        temp_list.append(parts.at(3));
        temp_list.append(parts.at(4));
        temp_list.append(parts.at(5));
        temp_list.append(parts.at(6));
        temp_list.append(parts.at(7));

        tramaOffsets = "C";
        for(int j=0; j < temp_list.size(); j++){
            tramaOffsets = tramaOffsets + formato3bytes(temp_list.at(j));
        }
        tramaOffsets = tramaOffsets + "\n";
        if( tramaOffsets.size() == 23){
            qDebug() << "tramaOffsets cargada correctamente";
        }
        else{
            qDebug() << "tramaOffsets error al cargar";
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

QString Monitor::formato3bytes(QString val){
    try {
        QString final = "";
        int entero = val.toInt();
        if(0 < entero && entero < 10){
            final = "00" + val;
        }
        else if(10 <= entero && entero < 100){
            final = "0" + val;
        }
        else{
            final = val;
        }
        return final;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

void Monitor::receVent(QString trama){
    try {
        //QString trama = serVent->leer();
        //qDebug() << "receVent: " + trama;
        if(trama != ""){
            if(trama.size() > 0){
                if(trama[0] == "P" && trama.size() == 19){
                    if(! banderaConexionVentilador){
                        banderaConexionVentilador = true;
                    }
                    estadoAlarmasVentilador = trama[2];
                    estadoAlarmasVentiladorControl = trama[3];

                    nivel_oxigeno = trama.mid(4,3);
                    modo_nobreak = trama[7];
                    nivel_batt = trama[8];
                    entrada_aire = trama.mid(9,3).toInt()/10;
                    entrada_oxigeno = trama.mid(12,3).toInt()/10;
                    sensor_presion_c = trama.mid(15,3).toInt();
                    int estado_sensor_presion_i2c = trama.mid(18,1).toInt();
                    if(estado_sensor_presion_i2c == 1){
                        consul->agregar_evento("SENSORES", obtener_modo(), "SENSOR PRESION CONTROL");
                        muestraAvisoVentilador("SENSOR PRESIÓN");
                    }
                    signoPLATEU->bar->setValue(nivel_oxigeno.toFloat());
                    if(primera_vez_nobreak){
                        primera_vez_nobreak = false;
                        ultimo_estado_nobreak = modo_nobreak;
                        if(modo_nobreak == "0"){
                            float temp_nivel = nivel_batt.toFloat()*20;
                            widgetAlarms->bateria(temp_nivel,0);
                            consul->agregar_evento("ALIMENTACION", obtener_modo(), "MODO BATERIA");
                        }
                        else{
                            float temp_nivel = nivel_batt.toFloat()*20;
                            widgetAlarms->bateria(temp_nivel,1);
                            consul->agregar_evento("ALIMENTACION", obtener_modo(), "MODO AC");
                        }
                    }
                    else{
                        if(modo_nobreak != ultimo_estado_nobreak){
                            if(modo_nobreak == "0"){
                                if(!buscar_en_lista("Modo bat.")){
                                    agregar_en_lista("Modo bat.", 1);
                                    consul->agregar_evento("ALIMENTACION", obtener_modo(), "MODO BATERIA");
                                    qDebug() << "___Agrega Modo bat.";
                                    if(! estadoAlarmaAlimentacion){
                                        estadoAlarmaAlimentacion = true;
                                        alarmaControl->iniciaAlarma(alarmaControl->ALIMENTACION);
                                    }
                                }
                                else{
                                    //ya esta en la lista
                                    actualizar_en_lista("Modo bat.", 1);
                                    consul->agregar_evento("ALIMENTACION", obtener_modo(), "MODO BATERIA");
                                    qDebug() << "___Activa Modo bat.";
                                    if(! estadoAlarmaAlimentacion){
                                        estadoAlarmaAlimentacion = true;
                                        alarmaControl->iniciaAlarma(alarmaControl->ALIMENTACION);
                                    }
                                }
                                float temp_nivel = nivel_batt.toFloat() * 20;
                                //threading.Thread(target=self.beep,args=(1209, 2, 0.25, 0.25,)).start()
                                beep_frecuencia = 1209;
                                beep_veces = 2;
                                beep_tiempo = 0.25;
                                beep_pausa = 0.25;
                                timerBeep->start(100);
                                widgetAlarms->bateria(temp_nivel, 0);
                                if(temp_nivel <= 20){
                                    //consul->agregar_evento("ALIMENTACION", obtener_modo(), "BATERIA BAJA");
                                    if(! buscar_en_lista("Bat. baja")){
                                        agregar_en_lista("Bat. baja", 1);
                                        consul->agregar_evento("ALARMA", obtener_modo(), "BATERIA BAJA");
                                        qDebug() << "___Agrega Bat. baja";
                                        if(! estadoAlarmaBateria){
                                            estadoAlarmaBateria = true;
                                            alarmaControl->iniciaAlarma(alarmaControl->BATERIA);
                                        }
                                    }
                                    else{
                                        actualizar_en_lista("Bat. baja", 1);
                                        consul->agregar_evento("ALARMA", obtener_modo(), "BATERIA BAJA");
                                        qDebug() << "___Activa Bat. baja";
                                        if(! estadoAlarmaBateria){
                                            estadoAlarmaBateria = true;
                                            alarmaControl->iniciaAlarma(alarmaControl->BATERIA);
                                        }
                                    }
                                }
                                else if(20 < temp_nivel && temp_nivel <= 40){
                                    if(! buscar_en_lista("Bat. media")){
                                        agregar_en_lista("Bat. media", 1);
                                        consul->agregar_evento("ALARMA", obtener_modo(), "BATERIA MEDIA");
                                        qDebug() << "___Agrega Bat. media";
                                        if(! estadoAlarmaBateria){
                                            estadoAlarmaBateria = true;
                                            alarmaControl->iniciaAlarma(alarmaControl->BATERIA);
                                        }
                                    }
                                    else{
                                        actualizar_en_lista("Bat. media", 1);
                                        consul->agregar_evento("ALARMA", obtener_modo(), "BATERIA MEDIA");
                                        qDebug() << "___Activa Bat. media";
                                        if(! estadoAlarmaBateria){
                                            estadoAlarmaBateria = true;
                                            alarmaControl->iniciaAlarma(alarmaControl->BATERIA);
                                        }
                                    }
                                }
                            }
                            else{
                                //threading.Thread(target=self.beep, args=(1477, 1, 0.5, 0,)).start()
                                beep_frecuencia = 1477;
                                beep_veces = 1;
                                beep_tiempo = 0.5;
                                beep_pausa = 0;
                                timerBeep->start(100);
                                if(buscar_en_lista("Modo bat.")){
                                   actualizar_en_lista("Modo bat.", 0);
                                   qDebug() << "___Elimina Modo bat.";
                                   if(estadoAlarmaAlimentacion){
                                       estadoAlarmaAlimentacion = false;
                                       alarmaControl->iniciaAlarma(alarmaControl->ALIMENTACION);
                                   }
                                   ult_temp_nivel_bat = nivel_batt.toFloat()*20;
                                }
                                float temp_nivel = nivel_batt.toFloat() * 20;
                                widgetAlarms->bateria(temp_nivel, 1);
                                consul->agregar_evento("ALIMENTACION", obtener_modo(), "MODO AC");
                                /*if(buscar_en_lista("Bateria")){
                                    actualizar_en_lista("Bateria", 0);
                                    qDebug() << "___Elimina Bateria";
                                    if(estadoAlarmaBateria){
                                        estadoAlarmaBateria = false;
                                        alarmaControl->detenAlarma(alarmaControl->BATERIA);
                                    }
                                }*/
                                if(temp_nivel <= 20){
                                    //consul->agregar_evento("ALIMENTACION", obtener_modo(), "BATERIA BAJA");
                                    if(! buscar_en_lista("Bat. baja")){
                                        agregar_en_lista("Bat. baja", 1);
                                        consul->agregar_evento("ALARMA", obtener_modo(), "BATERIA BAJA");
                                        qDebug() << "___Agrega Bat. baja";
                                        if(! estadoAlarmaBateria){
                                            estadoAlarmaBateria = true;
                                            alarmaControl->iniciaAlarma(alarmaControl->BATERIA);
                                        }
                                    }
                                    else{
                                        actualizar_en_lista("Bat. baja", 1);
                                        consul->agregar_evento("ALARMA", obtener_modo(), "BATERIA BAJA");
                                        qDebug() << "___Activa Bat. baja";
                                        if(! estadoAlarmaBateria){
                                            estadoAlarmaBateria = true;
                                            alarmaControl->iniciaAlarma(alarmaControl->BATERIA);
                                        }
                                    }
                                }
                                else if(20 < temp_nivel && temp_nivel <= 40){
                                    if(! buscar_en_lista("Bat. media")){
                                        agregar_en_lista("Bat. media", 1);
                                        consul->agregar_evento("ALARMA", obtener_modo(), "BATERIA MEDIA");
                                        qDebug() << "___Agrega Bat. media";
                                        if(! estadoAlarmaBateria){
                                            estadoAlarmaBateria = true;
                                            alarmaControl->iniciaAlarma(alarmaControl->BATERIA);
                                        }
                                    }
                                    else{
                                        actualizar_en_lista("Bat. media", 1);
                                        consul->agregar_evento("ALARMA", obtener_modo(), "BATERIA MEDIA");
                                        qDebug() << "___Activa Bat. media";
                                        if(! estadoAlarmaBateria){
                                            estadoAlarmaBateria = true;
                                            alarmaControl->iniciaAlarma(alarmaControl->BATERIA);
                                        }
                                    }
                                }
                            }
                        }
                        else{
                            int temp_modo = modo_nobreak.toInt();
                            float temp_nivel = nivel_batt.toFloat()*20;
                            widgetAlarms->bateria(temp_nivel, temp_modo);
                            /*if(temp_nivel <= 20){
                                if(! buscar_en_lista("Bateria")){
                                    agregar_en_lista("Bateria", 1);
                                    consul->agregar_evento("ALIMENTACION", obtener_modo(), "BATERIA BAJA");
                                    qDebug() << "___Agrega Bateria";
                                    if(! estadoAlarmaBateria){
                                        estadoAlarmaBateria = true;
                                        alarmaControl->iniciaAlarma(alarmaControl->BATERIA);
                                    }
                                }
                            }*/
                            if(temp_nivel > ult_temp_nivel_bat){
                                if(temp_nivel > 20){
                                    if(buscar_en_lista("Bat. baja") && diccionario_alarma->value("Bat. baja") == 1){
                                        actualizar_en_lista("Bat. baja", 0);
                                        qDebug() << "___Elimina Bat. baja";
                                        if(estadoAlarmaBateria && ! buscar_en_lista("Bat. media")){
                                            estadoAlarmaBateria = false;
                                            alarmaControl->detenAlarma(alarmaControl->BATERIA);
                                        }
                                    }
                                }
                                if(temp_nivel > 40){
                                    if(buscar_en_lista("Bat. media") && diccionario_alarma->value("Bat. media") == 1){
                                        actualizar_en_lista("Bat. media", 0);
                                        qDebug() << "___Elimina Bat. media";
                                        if(estadoAlarmaBateria){
                                            estadoAlarmaBateria = false;
                                            alarmaControl->detenAlarma(alarmaControl->BATERIA);
                                        }
                                    }
                                }
                            }
                            else{
                                if(temp_nivel <= 20){
                                    //consul->agregar_evento("ALIMENTACION", obtener_modo(), "BATERIA BAJA");
                                    if(! buscar_en_lista("Bat. baja")){
                                        agregar_en_lista("Bat. baja", 1);
                                        consul->agregar_evento("ALARMA", obtener_modo(), "BATERIA BAJA");
                                        qDebug() << "___Agrega Bat. baja";
                                        if(! estadoAlarmaBateria){
                                            estadoAlarmaBateria = true;
                                            alarmaControl->iniciaAlarma(alarmaControl->BATERIA);
                                        }
                                    }
                                    else if (diccionario_alarma->value("Bat. baja") == 0){
                                        actualizar_en_lista("Bat. baja", 1);
                                        consul->agregar_evento("ALARMA", obtener_modo(), "BATERIA BAJA");
                                        qDebug() << "___Activa Bat. baja";
                                        if(! estadoAlarmaBateria){
                                            estadoAlarmaBateria = true;
                                            alarmaControl->iniciaAlarma(alarmaControl->BATERIA);
                                        }
                                    }
                                }
                                else if(20 < temp_nivel && temp_nivel <= 40){
                                    if(! buscar_en_lista("Bat. media")){
                                        agregar_en_lista("Bat. media", 1);
                                        consul->agregar_evento("ALARMA", obtener_modo(), "BATERIA MEDIA");
                                        qDebug() << "___Agrega Bat. media";
                                        if(! estadoAlarmaBateria){
                                            estadoAlarmaBateria = true;
                                            alarmaControl->iniciaAlarma(alarmaControl->BATERIA);
                                        }
                                    }
                                    else if (diccionario_alarma->value("Bat. media") == 0){
                                        actualizar_en_lista("Bat. media", 1);
                                        consul->agregar_evento("ALARMA", obtener_modo(), "BATERIA MEDIA");
                                        qDebug() << "___Activa Bat. media";
                                        if(! estadoAlarmaBateria){
                                            estadoAlarmaBateria = true;
                                            alarmaControl->iniciaAlarma(alarmaControl->BATERIA);
                                        }
                                    }
                                }
                            }
                            ult_temp_nivel_bat = temp_nivel;
                        }
                        ultimo_estado_nobreak = modo_nobreak;
                    }
                    //threading.Thread(target=self.revisar_alarmas_ventilador).start()
                    timerRAV->start(300);
                    //threading.Thread(target=self.revisar_entra_gases,args=(self.entrada_aire, self.entrada_oxigeno, self.nivel_oxigeno,)).start()
                    timerREG->start(400);
                }
                else if(trama == "S"){
                    if(! desactivar_s){
                        serVent->envia_trama_config("S\n");
                        banderaConexionVentilador = true;
                        if(! timerConVentilador->isActive()){
                            timerConVentilador->start(7000);
                        }
                    }
                    if(volverIntetarComandoM){
                        volverIntetarComandoM = false;
                        if(volverIntentarModo){
                            temp_timer_ini->start(1000);
                        }
                        else{
                            temp_timer_det->start(800);
                        }
                        qDebug() << "segundo intento comando M - llega desde S";
                    }
                }
                else if(trama[0] == "C" && trama.size() == 22){
                    if(trama == tramaOffsets.mid(0,22)){
                        cambiosOffsets = true;
                        if(timerOffsetsVent->isActive()){
                            timerOffsetsVent->stop();
                            /*serVent->envia_trama_config("P\n");
                            timerConVentilador->start(7000);
                            ventiladorListo = true;*/
                            //
                            timerMIniVent->start(4000);
                            serVent->envia_trama_config(tramaVentilador);
                        }
                    }
                }
                else if(trama[0] == "O" && trama.size() == 3){
                    if(trama[1] == "0"){
                        if(timerOxigeno->isActive()){
                            timerOxigeno->stop();
                        }
                        if(trama[2] == "0"){
                            pruebas->label_oxigeno_estado->setText("Error");
                            pruebas->label_oxigeno_estado->setStyleSheet("color: red; background-color: #D5D8DC;");
                            pruebas->label_info->setText("Error en el sensor");
                            consul->agregar_evento("PRUEBAS",obtener_modo(), "OXIGENO ERROR SENSOR");
                            pruebas_iniciales = false;
                        }
                        else if(trama[2] == "1"){
                            pruebas->label_oxigeno_estado->setText("Error");
                            pruebas->label_oxigeno_estado->setStyleSheet("color: red; background-color: #D5D8DC;");
                            pruebas->label_info->setText("Sensor no usable.");
                            consul->agregar_evento("PRUEBAS",obtener_modo(), "OXIGENO SENSOR NO USABLE");
                            pruebas_iniciales = false;
                        }
                        else{
                            int entero = trama.mid(2,1).toInt();
                            if(entero == 2){
                                pruebas->label_oxigeno_estado->setText("Precaución");
                                pruebas->label_oxigeno_estado->setStyleSheet("color: yellow; background-color: #D5D8DC;");
                                pruebas->label_info->setText("Sensor viejo.");
                                consul->agregar_evento("PRUEBAS",obtener_modo(), "OXIGENO SENSOR VIEJO");
                                pruebas_iniciales = false;
                            }
                            else{
                                vida_o2_21 = entero;

                                pruebas->label_oxigeno_estado->setText("OK");
                                pruebas->label_oxigeno_estado->setStyleSheet("color: green; background-color: #D5D8DC;");
                                pruebas->label_info->setText("Prueba 21% Oxígeno superada");
                                contador_timerOxigeno = 0;
                                serVent->envia_trama_config("O1\n");
                                timerOxigeno->start(1000);
                                consul->agregar_evento("PRUEBAS",obtener_modo(), "OXIGENO SENSOR OK");
                            }
                        }
                    }
                    else{
                        serPresion->escribir("G0\n");
                        pruebas_iniciales = false;
                        if(timerOxigeno->isActive()){
                            timerOxigeno->stop();
                        }
                        if(trama[2] == "0"){
                            pruebas->label_oxigeno_estado->setText("Error");
                            pruebas->label_oxigeno_estado->setStyleSheet("color: red; background-color: #D5D8DC;");
                            pruebas->label_info->setText("Error en el sensor");
                            consul->agregar_evento("PRUEBAS",obtener_modo(), "OXIGENO ERROR SENSOR");
                        }
                        else if(trama[2] == "1"){
                            pruebas->label_oxigeno_estado->setText("Error");
                            pruebas->label_oxigeno_estado->setStyleSheet("color: red; background-color: #D5D8DC;");
                            pruebas->label_info->setText("Sensor no usable.");
                            consul->agregar_evento("PRUEBAS",obtener_modo(), "OXIGENO SENSOR NO USABLE");
                        }
                        else{
                            int entero = trama.mid(2,1).toInt();
                            if(entero == 2){
                                pruebas->label_oxigeno_estado->setText("Precaución");
                                pruebas->label_oxigeno_estado->setStyleSheet("color: yellow; background-color: #D5D8DC;");
                                pruebas->label_info->setText("Sensor viejo.");
                                consul->agregar_evento("PRUEBAS",obtener_modo(), "OXIGENO SENSOR VIEJO");
                            }
                            else{
                                pruebas->label_oxigeno_estado->setText("OK");
                                pruebas->label_oxigeno_estado->setStyleSheet("color: green; background-color: #D5D8DC;");
                                pruebas->label_info->setText("Prueba 100% Oxígeno superada");
                                qDebug() << "Terminan todas las pruebas";
                                pruebas_terminadas = true;
                                consul->agregar_evento("PRUEBAS",obtener_modo(), "OXIGENO SENSOR OK");
                                consul->agregar_evento("PRUEBAS",obtener_modo(), "OXIGENO TERMINA OK");
                                vida_o2_100 = entero;
                                int promedio = (vida_o2_21 + vida_o2_100)/2;
                                if(promedio <= 2){
                                    pruebas->label_info->setText("Sensor de oxígeno viejo");
                                }
                                else if(promedio >= 8){
                                    pruebas->label_info->setText("Sensor de oxígeno nuevo 100%");
                                }
                                else{
                                    int vida = promedio * 13 ;
                                    pruebas->label_info->setText("Sensor de oxígeno " + QString::number(vida) + " % de vida");
                                }

                            }
                        }
                    }
                }
                else if(trama == tramaVentilador.mid(0,45)){
                    if(numeroBanderaVentilador == 3 || numeroBanderaVentilador == 0){
                        timerVentilador->stop();
                        qDebug() << "Llego la trama de configuracion principal ventilador";
                        configurandoVentilador = false;
                        volverIntetarComandoM = false;
                        volverIntentarModo = false;
                        if(trama.mid(44,1) == "0"){
                            if(!cambiosMIni){
                                cambiosMIni = true;
                                if(timerMIniVent->isActive()){
                                    timerMIniVent->stop();
                                }
                                serVent->envia_trama_config("P\n");
                                timerConVentilador->start(7000);
                                ventiladorListo = true;
                            }
                            else{
                                reenviar_paro = false;
                                if(! configurandoSenPresion){
                                    estadoVentilador = false;
                                    label_debug->setText("Standby...");
                                    consul->agregar_evento("VENTILADOR", obtener_modo(), "DETIENE LA VENTILACION F");
                                    tpresionModo = 0;
                                }
                                else{
                                   label_debug->setText("Deteniendo...");
                                   tpresionModo = 0;
                                   estadoVentilador = false;
                                }
                            }
                        }
                        else if(trama.mid(44,1) == "1"){
                            estadoVentilador = true;
                            if(banderConfigCLista){
                                banderaTimerEstadoSenPresion = false;
                                serPresion->iniciar_sensor_presion();
                                if(banderaTimerEstadoSenPresion){
                                    label_debug->setText("Vent ON");
                                    qDebug() << "---ini senpres";
                                    consul->agregar_evento("VENTILADOR", obtener_modo(), "INICIA LA VENTILACION");
                                }
                                banderaModoSenPresion = 2;
                                timerTPresion1S->start(2000);
                                banderConfigCLista = false;
                                tpresionModo = 1;
                                configurandoSenPresion = false;
                                if(es_actualizacion){
                                    es_actualizacion = false;
                                    //threading.Thread(target=self.reiniciar_alarmas, args=(True, False,))
                                    RA_setear = true;
                                    RA_limpiar = true;
                                    timerRA->start(500);
                                }
                                else{
                                    //threading.Thread(target=self.reiniciar_alarmas, args=(True, True,))
                                    RA_setear = true;
                                    RA_limpiar = true;
                                    timerRA->start(500);
                                }
                                listo_medir_fio2 = false;
                                timerFIO2->start(60000);
                                //limpiar promediadores
                                graficaPresion->limpiar_promediador();
                                graficaVolumen->limpiar_promediador();
                                graficaFlujo->limpiar_promediador();
                            }
                        }
                    }
                }
                else if(trama[0] == "E" && trama.size() == 2){
                    if(trama[1] == "R"){
                        qDebug() << "Error en rango";
                        label_debug->setText("Error rangos");
                        consul->agregar_evento("COMUNICACION", obtener_modo(), "ERROR RANGOS DE CONFIGURACION");
                    }
                    else if(trama[1] == "T"){
                        qDebug() << "Error en trama";
                        label_debug->setText("Error trama");
                        consul->agregar_evento("COMUNICACION", obtener_modo(), "ERROR TRAMA");
                    }
                    else if(trama[1] == "A"){
                        qDebug() << "Error en caracter";
                        label_debug->setText("Error ascii");
                        consul->agregar_evento("COMUNICACION", obtener_modo(), "ERROR ASCII");
                        if(volverIntetarComandoM){
                            volverIntetarComandoM = false;
                            if(volverIntentarModo){
                                temp_timer_ini->start(1000);
                            }
                            else{
                                temp_timer_det->start(800);
                            }
                            qDebug() << "segundo intento comando M";
                        }
                        else if(reenviar_paro){
                            if(contador_reenvio == 0){
                                contador_reenvio++;
                                temp_timer_det->start(800);
                            }
                            else{
                                reenviar_paro = false;
                                contador_reenvio = 0;
                                label_debug->setText("Vent ON - EP");
                            }
                        }
                    }
                }
                else if(trama[0] == "Q"){
                    int presion = trama.mid(1,3).toInt();
                    qDebug() << "PRESION Q: " + QString::number(presion);
                    QString estado_sensor = trama.mid(4,1);
                    if(estado_sensor == "1"){
                        qDebug() << "Error en el sensor de presion - Control";
                    }

                    if(buscar_q_tope){
                        if(esperando_presion_tope){
                            if(timerPresion->isActive()){
                                timerPresion->stop();
                            }
                            esperando_presion_tope = false;
                            presion_inicial_pruebas = presion;
                            qDebug() << "***** Llegó a la presión tope Q";
                            timerPresionFinal->start(1000);
                        }
                        else{
                           qDebug() << "U sin bandera";
                        }
                        buscar_q_tope = false;
                    }
                    else{
                        if(revisar_presion_tope){
                            presion_pruebas = presion;
                            if((presion_inicial_pruebas - presion_pruebas) > presion_tope*0.1){
                                fuga();
                                revisar_presion_tope = false;
                            }
                            else{
                                presion_inicial_salida = presion;
                                no_fuga();
                                revisar_presion_tope = false;
                            }
                        }
                        else if(revisar_liberacion_presion){
                            presion_pruebas = presion;
                            if((presion_inicial_salida - presion_pruebas) > presion_tope * 0.5){
                                libera();
                                revisar_liberacion_presion = false;
                            }
                            else{
                                no_libera();
                                revisar_liberacion_presion = false;
                            }
                        }
                    }
                }
                else if(trama[0] == "U"){
                    QThread::msleep(50);
                    int presion = trama.mid(1,3).toInt();
                    qDebug() << "PRESION U: " + QString::number(presion);
                    QString estado_sensor = trama.mid(4,1);
                    serVent->envia_trama_config("U\n");
                    //checar si la presión es mayor a 35, mandar a detener y mostrar error
                    if(presion > 35){
                        //mandar a detener pruebas
                        consul->agregar_evento("PRUEBAS", obtener_modo(), "ERROR PRESION TOPE Uc");
                        pruebas->label_info->setText("Error presión tope");
                        detener_pruebas_presion();
                        pruebas->label_valvulas_estado->setText("Error");
                        pruebas->label_valvulas_estado->setStyleSheet("color: red; background-color: #D5D8DC;");
                        pruebas->label_presion_estado->setText("Error");
                        pruebas->label_presion_estado->setStyleSheet("color: red; background-color: #D5D8DC;");
                    }
                    else{
                        buscar_q_tope = true;
                        timerPresionFinal->start(1000);
                    }
                }
                else if(trama[0] == "F"){
                    vrecibidaVentilador = true;
                    qDebug() << "Version ventilador: "+ trama.mid(2,3);
                    if(trama.mid(2,3) != versionVentiladorEsperada){
                        if(vAvisoV == nullptr){
                            muestraAvisoVentilador("VERSION OBSOLETA\n ACTUALIZAR VERSION DE VENTILADOR");
                            timerConfigVent->stop();
                            consul->agregar_evento("INICIO", obtener_modo(), "INCORRECTO CONTROL");
                        }
                    }
                    else{
                        versionVentilador = trama.mid(2,3);
                        if(trama[1] == "0"){
                            estadoVentilador = false;
                            numeroBanderaVentilador = 0;
                            qDebug() << "Origen";
                            origenListo = true;
                            serVent->envia_trama_config(tramaOffsets);
                            timerOffsetsVent->start();
                            consul->agregar_evento("INICIO", obtener_modo(), "CORRECTO CONTROL");
                        }
                        else{
                            estadoVentilador = true;
                            ventiladorListo = true;
                            origenListo = true;
                            consul->agregar_evento("INICIO", obtener_modo(), "RECUPERACION");
                        }
                    }
                }
                else if(trama[0] == "T"){
                    if(trama.mid(14,1) == "1"){
                        if(contador_valvulas == 0 || contador_valvulas == 2 || contador_valvulas == 4 || contador_valvulas == 6 || contador_valvulas == 8 || contador_valvulas == 10){
                            timerPresion->start(dic_tiempo_presion->value(contador_pruebas_iniciales));
                            esperando_presion_tope = true;
                            qDebug() << "***** Esperando presion tope, timer: "+ QString::number(dic_tiempo_presion->value(contador_pruebas_iniciales));
                            qDebug() << "Ini timer!!!!: " +  QDate::currentDate().toString();
                        }
                        else{
                            //threading.Thread(target=self.beep,args=(1336, 4, 0.2, 0.2,)).start()
                            beep_frecuencia = 1336;
                            beep_veces = 4;
                            beep_tiempo = 0.2;
                            beep_pausa = 0.2;
                            timerBeep->start(100);
                            qDebug() << "beep ventilador";
                            qDebug() << "liberando presion: " + QString::number(dic_tiempo_presion_salida->value(contador_pruebas_iniciales));
                            timerPresionSalida->start(dic_tiempo_presion_salida->value(contador_pruebas_iniciales));
                            esperando_presion_salida = true;
                            qDebug() << "***** Liberando presion";
                        }
                    }
                    else{
                        if(pruebas_iniciales){
                            pruebas->label_info->setText("Error en prueba");
                            consul->agregar_evento("PRUEBAS", obtener_modo(), "ERROR CONTROL");
                            detener_pruebas_presion();
                            pruebas->label_valvulas_estado->setText("Error");
                            pruebas->label_valvulas_estado->setStyleSheet("color: red; background-color: #D5D8DC;");
                            pruebas->label_presion_estado->setText("Error");
                            pruebas->label_presion_estado->setStyleSheet("color: red; background-color: #D5D8DC;");
                        }
                        else{
                            qDebug() << "Fin de pruebas de presion serventilador";
                            fin_prueba_presion_serventilador = true;
                        }
                    }
                }
                else if(trama == "A2"){
                    listoApagarControl = true;
                }
            }
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::libera(){
    try {
        if(contador_valvulas < 2){
            contador_valvulas ++;
            serVent->envia_trama_config(dic_trama_valvulas->value(contador_valvulas));
            pruebas->label_presion_estado->setText(QString::number(contador_valvulas*25)+" %");
        }
        else{
            qDebug() << "monitor::libera-else!!!";
            pruebas->label_valvulas_estado->setText("OK");
            pruebas->label_valvulas_estado->setStyleSheet("color: green; background-color: #D5D8DC;");
            pruebas->label_presion_estado->setText("OK");
            pruebas->label_presion_estado->setStyleSheet("color: green; background-color: #D5D8DC;");
            //numero_prueba ++;
            pruebas->label_info->setText("Presione INICIAR\npara iniciar prueba de sensor de oxígeno.");
            consul->agregar_evento("PRUEBAS", obtener_modo(), "FIN PRESION CORRECTA");
            timerFinPruebaPresion->start(5000);
            detener_pruebas_presion();
            oxis->mostrar();
            infoAbierta = true;
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::no_libera(){
    try {
        consul->agregar_evento("PRUEBAS", obtener_modo(),"ERROR PRESION LIBERAR");
        pruebas->label_info->setText("Error en liberación de aire");
        detener_pruebas_presion();
        pruebas->label_valvulas_estado->setText("Error");
        pruebas->label_valvulas_estado->setStyleSheet("color: red; background-color: #D5D8DC;");
        pruebas->label_presion_estado->setText("Error");
        pruebas->label_presion_estado->setStyleSheet("color: red; background-color: #D5D8DC;");
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::no_fuga(){
    try {
        contador_valvulas++;
        QString trama = dic_trama_valvulas->value(contador_valvulas);
        qDebug() << "***** Liberar presion";
        serVent->envia_trama_config(trama);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::fuga(){
    try {
        consul->agregar_evento("PRUEBAS", obtener_modo(), "ERROR PRESION FUGA MANTENER");
        pruebas->label_info->setText("Fuga al mantener la presión");
        detener_pruebas_presion();
        pruebas->label_valvulas_estado->setText("Error");
        pruebas->label_valvulas_estado->setStyleSheet("color: red; background-color: #D5D8DC;");
        pruebas->label_presion_estado->setText("Error");
        pruebas->label_presion_estado->setStyleSheet("color: red; background-color: #D5D8DC;");
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::revisar_alarmas_ventilador(){
    try {
        QString alarma = estadoAlarmasVentiladorControl;
        if(alarma != "0"){
            qDebug() << "Alarma ventilador: " + alarma;
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::muestraAvisoApagar(QString mensajes){
    try {
        QStringList *tt = new QStringList{"Apagando sistema", "", "", "", mensajes};
        vAvisoC->textoMostrar(tt);
        vAvisoC->move(0,0);
        vAvisoC->resize(mainwindow->width(), mainwindow->height());
        vAvisoC->show();
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::muestraAvisoConfig(QString mensajes){
    try {
        QStringList *tt = new QStringList{"Iniciando sistema", "", "", "", mensajes};
        vAvisoC->textoMostrar(tt);
        vAvisoC->move(0,0);
        vAvisoC->resize(mainwindow->width(), mainwindow->height());
        vAvisoC->show();
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::muestraAviso(QString mensajes){
    try {
        ventiladorInoperante = true;
        vAviso = new VentanaAviso(this, 500, 300);
        QStringList *tt = new QStringList{"ERROR DE LA TARJETA DE SENSORES", "", "", "", mensajes};
        vAviso->textoMostrar(tt);
        vAviso->move(0,0);
        vAviso->resize(mainwindow->width(), mainwindow->height());
        vAviso->show();
        alarmaControl->iniciaAlarma(alarmaControl->INOPERANTE);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::muestraAvisoPresion(QString mensajes){
    try {
        if(vAvisoV == nullptr){
            ventiladorInoperante = true;
            vAviso = new VentanaAviso(this, 500, 300);
            QStringList *tt = new QStringList{"ERROR DE LA TARJETA DE SENSORES", "", "", "", mensajes};
            vAviso->textoMostrar(tt);
            vAviso->move(0,0);
            vAviso->resize(mainwindow->width(), mainwindow->height());
            vAviso->show();
            alarmaControl->iniciaAlarma(alarmaControl->INOPERANTE);
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::muestraAvisoVentilador(QString mensajes){
    try {
        if(vAvisoV == nullptr){
            ventiladorInoperante = true;
            vAvisoV = new VentanaAviso(this, 500, 300);
            QStringList *tt = new QStringList{"ERROR DE LA TARJETA DE CONTROL", "", "", "", mensajes};
            vAvisoV->textoMostrar(tt);
            vAvisoV->move(0,0);
            vAvisoV->resize(mainwindow->width(), mainwindow->height());
            vAvisoV->show();
            alarmaControl->iniciaAlarma(alarmaControl->INOPERANTE);
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::cierraAvisoVentilador(){
    try {
        if(vAvisoV != nullptr){
           vAvisoV->close();
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::cierraAvisoPresion(){
    try {
        if(vAviso != nullptr){
           vAviso->close();
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::muestraAvisoTest(QString mensajes){
    try {
        qDebug() << mensajes;
        vAvisoT = new VentanaAvisoTest(this, 500, 450,"PRUEBA DEL EQUIPO");
        vAvisoT->move(0,0);
        vAvisoT->resize(mainwindow->width(), mainwindow->height());
        indiceMsg1 = vAvisoT->agregarMensaje("PRUEBA DE SENSORES");
        vAvisoT->show();
        vTestActiva = true;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::validaUnSeg(){
    try {
        if(banderaModoSenPresion == 0){
            qDebug() << "No llegó trama respuesta de configuracion";
            if(contador_respuesta_config_senrpesion < 3){
                contador_respuesta_config_senrpesion ++;
                serPresion->serPuerto->clear(QSerialPort::Input);
                QThread::msleep(250);
                serPresion->escribir(trama_c_senpresion);
                qDebug() << "Detiene sepresion y envia trama c, de nuevo";
            }
            else{
                qDebug() << "Falla actualización!!!!!";
                falla_actualizacion = true;
                configurandoVentilador = false;
                contador_respuesta_config_senrpesion = 0;
                label_debug->setText("Pulse Actualizar");
                timerTPresion1S->stop();
                consul->agregar_evento("COMUNICACION",obtener_modo(),"ERROR, NO RESPUESTA SENSORES I");
                //serPresion->iniciar_sensor_presion();
                //---Aquí poner algo para volver a poner a funcionar lose sensores pero sin aplicar cambios
                serPresion->escribir("A4\n");
            }
        }
        else if(banderaModoSenPresion == 1){
            qDebug() << "No llego trama respuesta de detener sensor";
            if(recibe_a0){
                timerTPresion1S->stop();
                contador_paro_tarjeta_sensores = 0;
                qDebug() << " recibe a0 --timer";
            }
            else{
                if(contador_paro_tarjeta_sensores <= 4){
                    contador_paro_tarjeta_sensores++;
                    serPresion->serPuerto->clear(QSerialPort::Input);
                    serPresion->detener_sensor_presion();
                }
                else{
                    if(vAviso == nullptr){
                        muestraAviso("NO RESPONDE A LA SOLICITUD DE DATOS");
                        consul->agregar_evento("COMUNICACION",obtener_modo(), "ERROR NO RESPONDE A0");
                    }
                }
            }
        }
        else if(banderaModoSenPresion == 2){
            if(banderaTimerEstadoSenPresion){
                qDebug() << "--El sensor está enviando datos";
                timerTPresion1S->stop();
                label_debug->setText("Vent ON");
                qDebug() << "---ini senpres";
                //limpiar promediadores
                graficaPresion->limpiar_promediador();
                graficaVolumen->limpiar_promediador();
                graficaFlujo->limpiar_promediador();
                consul->agregar_evento("VENTILADOR", obtener_modo(), "INICIA LA VENTILACION");
            }
            else{
                serPresion->iniciar_sensor_presion();
            }
        }
        else if(banderaModoSenPresion == 3){
            qDebug() << "No llegó trama respuesta de configuracion W";
            if(contador_respuesta_config_senrpesion < 3){
                contador_respuesta_config_senrpesion++;
                serPresion->serPuerto->clear(QSerialPort::Input);
                QThread::msleep(250);
                serPresion->escribir(trama_w_serpresion);
                qDebug() <<"Detiene sepresion y envia trama w, de nuevo";
            }
            else{
                qDebug() << "Falla actualización!!!!!";
                falla_actualizacion = true;
                configurandoVentilador = false;
                contador_respuesta_config_senrpesion = 0;
                label_debug->setText("Pulse Actualizar");
                timerTPresion1S->stop();
                consul->agregar_evento("COMUNICACION", obtener_modo(), "ERROR NO RESPUESTA SENSORES II");
                //serPresion->iniciar_sensor_presion();
                //---Aquí poner algo para volver a poner a funcionar lose sensores pero sin aplicar cambios
                serPresion->escribir("A4\n");
            }
        }
        else if(banderaModoSenPresion == 4){
            //no se recibe A3 - dejar de enviar datos
            qDebug() << "No llegó trama respuesta A3 dejar de enviar datos";
            if(contador_respuesta_config_senrpesion < 3){
                contador_respuesta_config_senrpesion++;
                serPresion->serPuerto->clear(QSerialPort::Input);
                QThread::msleep(250);
                serPresion->escribir("A3\n");
                qDebug() <<"Vulve a intentar comando A3";
            }
            else{
                qDebug() << "Falla comando A3";
                configurandoVentilador = false;
                contador_respuesta_config_senrpesion = 0;
                //label_debug->setText("Pulse Actualizar");
                timerTPresion1S->stop();
                consul->agregar_evento("COMUNICACION", obtener_modo(), "ERROR NO RESPUESTA COMANDO PARA 3");
                //serPresion->iniciar_sensor_presion();
                //---Aquí poner algo para volver a poner a funcionar lose sensores pero sin aplicar cambios
                banderaModoSenPresion = 5;
                timerTPresion1S->start(1500);
                serPresion->escribir("A4\n");
            }
        }
        else if(banderaModoSenPresion == 5){
            //no se recibe A4 - iniciar sin cambios
            qDebug() << "No llegó trama respuesta A4 inciar sin cambios";
            if(contador_respuesta_config_senrpesion < 5){
                contador_respuesta_config_senrpesion++;
                serPresion->serPuerto->clear(QSerialPort::Input);
                QThread::msleep(250);
                serPresion->escribir("A4\n");
                qDebug() <<"Vulve a intentar comando A4";
            }
            else{
                qDebug() << "Falla comando A4";
                configurandoVentilador = false;
                contador_respuesta_config_senrpesion = 0;
                timerTPresion1S->stop();
                consul->agregar_evento("COMUNICACION", obtener_modo(), "ERROR NO RESPUESTA COMANDO PARA 4");
                //serPresion->iniciar_sensor_presion();
                //---Aquí poner algo para volver a poner a funcionar lose sensores pero sin aplicar cambios
                label_debug->setText("Error Actualizar");
            }
        }
        else{
            timerTPresion1S->stop();
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::validaCincoSeg(){
    try {
        if(! configurandoSenPresion){
            if(tpresionModo == 0){
                if(timerCont5S == 3){
                    timerActivo5S = false;
                    timerCont5S = 0;
                    if(vAviso == nullptr){
                        muestraAviso("NO RESPONDE A LA SOLICITUD DE DATOS");
                        consul->agregar_evento("COMUNICACION",obtener_modo(), "ERROR NO RESPONDE SENSORES");
                        qDebug() << "solicitud de datos -- muestra aviso valida5s";
                    }
                }
                else{
                    if(vrecibidaSenpresion){
                        serPresion->escribir("P");
                    }
                    else{
                        serPresion->escribir("F");
                    }
                    timerCont5S++;
                }
            }
            else if(tpresionModo == 1){
                int temp_f = static_cast<int>(temp_peep.toFloat()*10);
                QString temp_s = QString::number(temp_f);
                if(0 <= temp_f && temp_f < 10){
                    temp_s = "00" + temp_s;
                }
                else if(10 <= temp_f && temp_f < 100){
                   temp_s = "0" + temp_s;
                }
                else{
                    temp_s = "000";
                }
                serPresion->escribir("P"+temp_s);
            }
            banderaConexionSenPresion = false;
        }
        else{
            qDebug() << "Esta configurando sen presion timer";
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::recePresion(QString trama){
    try {
        //QString trama = serPresion->leer();
        if(trama != ""){
            if(trama.size() > 0){
                if(trama[0] == "C"){
                    if(trama == "C1"){
                        qDebug() << "---configuracion C lista";
                        if(timerTPresion1S->isActive()){
                            timerTPresion1S->stop();
                        }
                        //configurandoVentilador = true;
                        contador_respuesta_config_senrpesion = 0;
                        banderaModoSenPresion = 3;
                        serPresion->escribir(trama_w_serpresion);
                        timerTPresion1S->start(5000);
                    }
                    else{
                        consul->agregar_evento("COMUNICACION", obtener_modo(), "ERROR SENSORES C");
                    }
                }
                else if(trama[0] == "W"){
                    if(trama == "W1"){
                        //preguntar si es por wdt
                        if(actualiza_por_wdt){
                            actualiza_por_wdt = false;
                            qDebug() << "---configuracion W por wdt";
                            if(timerTPresion1S->isActive()){
                                timerTPresion1S->stop();
                            }
                            contador_respuesta_config_senrpesion = 0;
                            serPresion->iniciar_sensor_presion();
                            //limpiar promediadores
                            graficaPresion->limpiar_promediador();
                            graficaVolumen->limpiar_promediador();
                            graficaFlujo->limpiar_promediador();
                            //
                            banderaModoSenPresion = 2;
                            timerTPresion1S->start(2000);
                            banderConfigCLista = false;
                            tpresionModo = 1;
                            configurandoSenPresion = false;
                        }
                        else{
                            qDebug() << "---configuracion W lista";
                            contador_respuesta_config_senrpesion = 0;
                            banderConfigCLista = true;
                            if(timerTPresion1S->isActive()){
                                timerTPresion1S->stop();
                            }
                            configurandoVentilador = true;
                            volverIntetarComandoM = true;
                            volverIntentarModo = true;
                            temp_timer_ini->start(1000);
                            qDebug() << "ini timer temp_timer_ini";
                        }
                    }
                    else{
                        consul->agregar_evento("COMUNICACION",obtener_modo(), "ERROR SENSORES W");
                    }
                }
                else if(trama[0] == "D"){
                    QStringList valores = trama.split(",");
                    if(valores.size() == 13){//> 9
                        banderaTimerEstadoSenPresion = true;
                        QString flujo = valores.at(0).mid(1);
                        //float flujo_f = flujo.toFloat();
                        QString vol = valores.at(1);
                        //float vol_f = vol.toFloat();
                        QString presion = valores.at(2);
                        //float presion_f = presion.toFloat();
                        if(mostrarGrafica){
                            //aqui va lo de la grafica
                            if(! cambiagrafi){
                                //ondas
                                graficaPresion->graficar(presion);
                                graficaVolumen->graficar(vol);
                                graficaFlujo->graficar(flujo);
                            }
                            else{
                                //lazos
                                graficaPV->graficar(presion, vol);
                                graficaVF->graficar(vol, flujo);
                            }
                        }
                        /*QString ti = valores.at(4);
                        QString te = valores.at(5);
                        QString vi = valores.at(6);
                        QString ve = valores.at(7);
                        QString vm = valores.at(8);
                        QString fr = valores.at(9);
                        QString pip = valores.at(10);
                        QString peep = valores.at(11);
                        QString fp = valores.at(12);*/
                        QString ti = valores.at(4);
                        QString te = valores.at(5);
                        QString vi = valores.at(6);
                        QString ve = valores.at(7);
                        QString vm = valores.at(8);
                        QString fr = valores.at(9);
                        QString pip = valores.at(10);
                        QString peep = valores.at(11);
                        QString fp = valores.at(12);
                        if(ti != "0" && te != "0" && vi != "0" && ve != "0" && vm != "0" && fr != "0" && pip != "0" && peep != "0" && fp != "0"){
                            PD_ti = ti;
                            PD_te = te;
                            PD_vi = vi;
                            PD_ve = ve;
                            PD_vm = vm;
                            PD_fr = fr;
                            PD_pip = pip;
                            PD_peep = peep;
                            PD_fp = fp;
                            timerPD->start(20);

                            //threading.Thread(target=self.poner_datos, args=(vi, ve, vm, fr, ti, te, pip, peep, fp,)).start()
                        }
                        /*if(ti != "0" && te != "0" && vi != "0" && ve != "0" && vm != "0" && fr != "0" && pip != "0" && peep != "0" && fp != "0"){
                            //threading.Thread(target=self.poner_datos, args=(vi, ve, vm, fr, ti, te, pip, peep, fp,)).start()
                        }*/
                        QString trigger = valores.at(3);
                        if(trigger == "1" && trigger_ult_est == "0"){
                            widgetAlarms->trigger(1);
                            //threading.Thread(target=self.beep, args=(852, 1, 0.3, 0,)).start()
                            beep_frecuencia = 852;
                            beep_veces = 1;
                            beep_tiempo = 0.3;
                            beep_pausa = 0;
                            timerBeep->start(100);
                        }
                        else if(trigger_ult_est == "1" && trigger == "0"){
                            widgetAlarms->trigger(0);
                        }
                        trigger_ult_est = trigger;
                    }
                }
                else if(trama[0] == "T"){
                    presion_pruebas = trama.mid(1).toInt();
                    qDebug() << "Valor presion prueba: " + QString::number(presion_pruebas);
                    if(presion_pruebas >= presion_tope && esperando_presion_tope){
                        if(timerPresion->isActive()){
                            timerPresion->stop();
                            esperando_presion_tope = false;
                            presion_inicial_pruebas = presion_pruebas;
                            qDebug() << "***** Llegó a la presión tope";
                            timerPresionFinal->start(2000);
                        }
                    }
                    if(esperando_presion_salida){
                        esperando_presion_salida = false;
                        presion_inicial_salida = presion_pruebas;
                    }
                }
                else if(trama[0] == "G"){
                    if(trama[1] == "1"){
                        qDebug() << "Recibe de senpresion G1, esta en modo pruebas";
                        /*QString trama = dic_trama_valvulas->value(contador_valvulas);
                        qDebug() << "*****trama valvulas: " + trama;
                        serVent->envia_trama_config(trama);*/
                    }
                    else if(trama[1] == "0"){
                        qDebug() << "Recibe de senpresion G0, termina modo pruebas";
                        /*if(pruebas_iniciales){
                            qDebug() << "Error al configurar presion tope";
                            detener_pruebas_presion();
                            pruebas->label_valvulas_estado->setText("Error");
                            pruebas->label_valvulas_estado->setStyleSheet("color: red; background-color: #D5D8DC;");
                            pruebas->label_presion_estado->setText("Error");
                            pruebas->label_presion_estado->setStyleSheet("color: red; background-color: #D5D8DC;");
                            consul->agregar_evento("COMUNICACION", obtener_modo(), "ERROR SENSORES G");
                        }
                        else{
                            qDebug() << "Termina pruebas de presion serpresion";
                            fin_prueba_presion_serpresion = true;
                        }*/
                    }
                }
                else if(trama[0] == "F"){
                    if(! vrecibidaSenpresion){
                        vrecibidaSenpresion = true;
                        versionSenPresion = trama.mid(1,3);
                        qDebug() << "Version senpresion: " + versionSenPresion;

                        QString b1 = trama.mid(4, 3);
                        QString b2 = trama.mid(7, 3);
                        QString b3 = trama.mid(10, 3);
                        QString b4 = trama.mid(13, 3);
                        QString b5 = trama.mid(16, 3);
                        QString b6 = trama.mid(19, 3);
                        QString b7 = trama.mid(22, 3);
                        consul->guarda_cali(b1, b2, b3, b4, b5, b6, b7);
                        if(trama.mid(1,3) != versionSenPresionEsperada){
                            if(vAviso == nullptr){
                                muestraAviso("VERSION OBSOLETA\n ACTUALIZAR VERSION SENSORES");
                                consul->agregar_evento("INICIO", obtener_modo(),"INCORRECTO SENSORES");
                            }
                        }
                        else{
                            versionSenPresion = trama.mid(1,3);
                            senPresionListo = true;
                            consul->agregar_evento("INICIO", obtener_modo(),"CORRECTO SENSORES");
                        }
                    }
                }
                else if(trama[0] == "E"){
                    if(trama.size() == 2){
                        if(trama[1] == "1"){
                            error_sensores_sensor_presion = true;
                            qDebug() << "Error-SV sensor de presion";
                        }
                        else if(trama[1] == "2"){
                            error_sensores_sensor_inhalacion = true;
                            qDebug() << "Error-SV sensor de inhalación";
                        }
                        else if(trama[1] == "3"){
                            error_sensores_sensor_exhalacion = true;
                            qDebug() << "Error-SV sensor de exhalación";
                        }
                    }
                    else{
                        if(! banderaConexionSenPresion){
                            banderaConexionSenPresion = true;
                        }
                        if(timerActivo5S && tpresionModo == 0){
                            timerTPresion5S->stop();
                            timerActivo5S = false;
                            timerCont5S = 0;
                            timerTPresion5S->start(5000);
                            timerActivo5S = true;
                        }
                        if(trama[1] != "0"){
                            timerTPresion5S->stop();
                            timerActivo5S = false;
                            timerCont5S = 0;
                            if(trama[1] == "1"){
                                if(vAviso == nullptr){
                                    qDebug() << "recePresion - error en el sensor de presion";
                                    muestraAviso("EN EL SENSOR DE PRESION");
                                    consul->agregar_evento("SENSORES", obtener_modo(), "ERROR SENSOR PRESION");
                                }
                            }
                            else if(trama[1] == "2"){
                                if(vAviso == nullptr){
                                    qDebug() << "recePresion - error en el sensor de flujo";
                                    muestraAviso("EN EL SENSOR DE FLUJO");
                                    consul->agregar_evento("SENSORES", obtener_modo(), "ERROR SENSOR FLUJO");
                                }
                            }
                            else if(trama[1] == "3"){
                                if(vAviso == nullptr){
                                    qDebug() << "recePresion - error en ambos sensores";
                                    muestraAviso("EN AMBOS SENSORES");
                                    consul->agregar_evento("SENSORES", obtener_modo(), "ERROR SENSORES");
                                }
                            }
                        }
                        else{
                            sensores_estado = true;
                            //jeru 01-03
                            contador_wdt = 0;

                            if( timerErrorWDT->isActive()){
                                timerErrorWDT->stop();

                                if(!ino_wdt_alarm){
                                    if(estadoAlarmaSensores){
                                        estadoAlarmaSensores = false;
                                        alarmaControl->detenAlarma(alarmaControl->INOPERANTE);
                                    }

                                    qDebug() << "Inicia actualizar ventilador por Error WDT";
                                    consul->agregar_evento("VENTILADOR", obtener_modo(), "act. vent. E WDT");
                                    huboCambioTrama = true;
                                    actualiza_por_wdt = true;
                                    actualizarDatosVentilador();
                                }

                            }
                            if(vAviso != nullptr){
                                if(vAviso->isVisible()){
                                    vAviso->hide();
                                    alarmaControl->detenAlarma(alarmaControl->INOPERANTE);
                                }
                            }
                        }
                        //checar que es Error WDT
                        if(trama == "Error WDT"){
                            if(! timerErrorWDT->isActive()){
                                revisarErroresWDT();
                                serPresion->escribir("P");
                                consul->agregar_evento("COMUNICACION", obtener_modo(), "- E WDT -");
                                timerErrorWDT->start(7000);
                            }
//                            label_debug->setText("Error WDT");
//                            consul->agregar_evento("COMUNICACION", obtener_modo(), "ERROR SENSORES WDT");
//                            if(modoSel == 0 || modoSel == 2 || modoSel == 4){
//                                if(! buscar_en_lista("SENSORES")){
//                                    agregar_en_lista("SENSORES", 1);
//                                    qDebug() << "SENSORES";
//                                    if(! estadoAlarmaSensores){
//                                        estadoAlarmaSensores = true;
//                                        alarmaControl->iniciaAlarma(alarmaControl->INOPERANTE);
//                                    }
//                                }
//                            }
//                            else{
//                              if(vAviso == nullptr){
//                                  int conta = 0;
//                                  if(error_sensores_sensor_presion){
//                                      conta ++;
//                                  }
//                                  if(error_sensores_sensor_inhalacion){
//                                      conta += 2;
//                                  }
//                                  if(error_sensores_sensor_exhalacion){
//                                      conta += 4;
//                                  }
//                                  muestraAviso("VENTILADOR INOPERANTE E: " + QString::number(conta));
//                                  detener_ventilador();
//                              }
//                            }
                        }
                        estadoAlarmasSensores = trama[2];
                    }
                }
                else if(trama[0] == "H"){
                    serPresion->escribir("H");
                    //qDebug() << "----Entra H: "+ trama[1] + " estado: " + trama[2];
                    configurandoSenPresion = false;
                    fue_h = true;
                    if(! timerTPresion5S->isActive()){
                        qDebug() << "*****Activa timer";
                        configurandoSenPresion = false;
                        timerTPresion5S->start(5000);
                    }
                    if(trama.size() == 3){
                        qDebug() << "Trama H: " + trama;
                        QString tipo_alarma = trama.mid(1,1);
                        int estado_alarma = trama.mid(2,1).toInt();
                        RAS_tipo = tipo_alarma;
                        RAS_estado = estado_alarma;
                        timerRAS->start(150);
                        //threading.Thread(target=self.revisar_alarmas_senpresion, args=(tipo_alarma, estado_alarma,)).start()

                    }

                }
                else if(trama[0] == "A"){
                    contador_respuesta_config_senrpesion = 0;
                    if(trama == "A0"){
                        configurandoSenPresion = false;
                        recibe_a0 = true;
                    }
                    else if(trama == "A2"){
                        listoApagarSensores = true;
                    }
                    else if(trama == "A3"){
                        if(timerTPresion1S->isActive()){
                            timerTPresion1S->stop();
                        }
                        timerTPresion1S->start(2500);
                        banderaModoSenPresion = 0;
                        qDebug() << "Regresa dejar de mandar datos";
                        serPresion->escribir(trama_c_senpresion);
                        qDebug() << "Detiene sepresion y envia trama c";
                    }
                    else if(trama == "A4"){
                        qDebug() << "Iniciar sin cambios";
                        if(timerTPresion1S->isActive()){
                            timerTPresion1S->stop();
                        }
                        label_debug->setText("Pulse Actualizar");
                    }
                }
                else if(trama[0] == "B"){
                    if(trama[1] == "0"){
                        cambiosCalibrar = true;
                    }
                    else if(trama[1] == "1"){
                        tramaCambiosCalibrar = "Falló calibración de flujo.";
                    }
                    else if(trama[1] == "2"){
                        tramaCambiosCalibrar = "Falló calibración de presión.";
                    }
                    else if(trama[1] == "3"){
                        tramaCambiosCalibrar = "Falló calibración.";
                    }
                }
                else if(trama[0] == "J"){
                    if(trama[1] == "0"){
                        configPI->label_info->setText("Guardando altura");
                        bool temp = consul->guarda_altura(configPI->le_altura->text());
                        if(temp){
                            configPI->label_info->setText("Altura guardada");
                        }
                        else{
                            configPI->label_info->setText("Error al guardar altura");
                        }
                    }
                    else if(trama[1] == "1"){
                        configPI->label_info->setText("Error al aplicar altura");
                    }
                    timerCambiosPerilla->start(2500);
                }

            }
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::revisar_alarmas_senpresion(){
    try {
        QString tipo = RAS_tipo;
        int estado = RAS_estado;
        qDebug() << "----Entra H: "+ tipo + " estado: " + QString::number(estado);
        if(tipo == "1"){
            qDebug() << "No hay comunicación con control";
        }
        else if(tipo == "2"){
            qDebug() << "No hay comunicacin con CPU";
        }
        else if(tipo == "3"){
            qDebug() << "No hay comunicación con nadie";
        }
        else if(tipo == "4"){
            if(estado == 1){
                qDebug() << "Alarma volumen minuto alto ACTIVADO";
                if(! buscar_en_lista("Vol min MAX")){
                    agregar_en_lista("Vol min MAX", 1);
                    qDebug() << "___Agrega Vol min MAX";
                    signoVm->bar->setPalette(*paleAlta);
                    signoVm->label_title->setStyleSheet("color: red;");
                    consul->agregar_evento("ALARMA", obtener_modo(), "VOLUMEN MIN ALTO ACTIVADO - 4");
                    if(! estadoAlarmaVolMin){
                        estadoAlarmaVolMin = true;
                        alarmaControl->iniciaAlarma(alarmaControl->VOLMINIMO);
                    }
                }
                else{
                    if(diccionario_alarma->value("Vol min MAX") == 0){
                        actualizar_en_lista("Vol min MAX", 1);
                        qDebug() << "___Agrega Vol min MAX";
                        signoVm->bar->setPalette(*paleAlta);
                        signoVm->label_title->setStyleSheet("color: red;");
                        consul->agregar_evento("ALARMA", obtener_modo(), "VOLUMEN MIN ALTO ACTIVADO - 4");
                        if(! estadoAlarmaVolMin){
                            estadoAlarmaVolMin = true;
                            alarmaControl->iniciaAlarma(alarmaControl->VOLMINIMO);
                        }
                    }
                }
            }
            else{
                qDebug() << "Alarma volumen minuto alto DESACTIVADO";
                if(buscar_en_lista("Vol min MAX")){
                    actualizar_en_lista("Vol min MAX", 0);
                    consul->agregar_evento("ALARMA", obtener_modo(), "VOLUMEN MIN ALTO DESACTIVADO - 4");
                    if(diccionario_alarma->value("Vol min MAX") == 0){
                        if(estadoAlarmaVolMin){
                            estadoAlarmaVolMin = false;
                            alarmaControl->detenAlarma(alarmaControl->VOLMINIMO);
                            signoVm->bar->setPalette(*paleNormal);
                            signoVm->label_title->setStyleSheet("color: white;");
                        }
                    }
                }
            }
        }
        else if(tipo == "5"){
            if(estado == 1){
                qDebug() << "Alarma presion alta ACTIVADO";
                if(! buscar_en_lista("Presion MAX")){
                    agregar_en_lista("Presion MAX", 1);
                    qDebug() << "___Agrega Presion MAX";
                    signoPIP->bar->setPalette(*palemedia_baja);
                    signoPIP->label_title->setStyleSheet("color: yellow;");
                    consul->agregar_evento("ALARMA", obtener_modo(), "PRESION ALTA ACTIVADA - 5");
                    if(! estadoAlarmaPresion){
                        estadoAlarmaPresion = true;
                        alarmaControl->iniciaAlarma(alarmaControl->PRESION);
                    }
                }
                else{
                    if(diccionario_alarma->value("Presion MAX") == 0){
                        actualizar_en_lista("Presion MAX", 1);
                        qDebug() << "___Agrega Presion MAX";
                        signoPIP->bar->setPalette(*palemedia_baja);
                        signoPIP->label_title->setStyleSheet("color: yellow;");
                        consul->agregar_evento("ALARMA", obtener_modo(), "PRESION ALTA ACTIVADA - 5");
                        if(! estadoAlarmaPresion){
                            estadoAlarmaPresion = true;
                            alarmaControl->iniciaAlarma(alarmaControl->PRESION);
                        }
                    }
                }
            }
            else{
                qDebug() << "Alarma presion alta DESACTIVADO";
                if(buscar_en_lista("Presion MAX")){
                    actualizar_en_lista("Presion MAX", 0);
                    consul->agregar_evento("ALARMA", obtener_modo(), "PRESION ALTA DESACTIVADA - 5");
                    signoPIP->bar->setPalette(*paleNormal);
                    signoPIP->label_title->setStyleSheet("color: white;");
                    if(diccionario_alarma->value("Presion MAX") == 0){
                        if(estadoAlarmaPresion){
                            estadoAlarmaPresion = false;
                            alarmaControl->detenAlarma(alarmaControl->PRESION);
                        }
                    }
                }
            }
        }
        else if(tipo == "6"){
            if(estado == 1){
                qDebug() << "Alarma apnea";
                if(! buscar_en_lista("APNEA")){
                    agregar_en_lista("APNEA", 1);
                    qDebug() << "___Agrega APNEA";
                    consul->agregar_evento("ALARMA", obtener_modo(), "APNEA R ACTIVADA - 6");
                    if(! estadoAlarmaApnea){
                        estadoAlarmaApnea = true;
                        alarmaControl->iniciaAlarma(alarmaControl->APNEA);
                    }
                }
                else{
                    if(diccionario_alarma->value("APNEA") == 0){
                        actualizar_en_lista("APNEA", 1);
                        qDebug() << "___Agrega APNEA";
                        consul->agregar_evento("ALARMA", obtener_modo(), "APNEA R ACTIVADA - 6");
                        if(! estadoAlarmaApnea){
                            estadoAlarmaApnea = true;
                            alarmaControl->iniciaAlarma(alarmaControl->APNEA);
                        }
                    }
                }
            }
            else if(estado == 2){
                if(! buscar_en_lista("Apnea")){
                    agregar_en_lista("Apnea", 2);
                    qDebug() << "___Agrega  Apnea A";
                    consul->agregar_evento("ALARMA", obtener_modo(), "APNEA R ACTIVADA - 6");
                    if(buscar_en_lista("APNEA")){
                        borrar_en_lista("APNEA");
                    }
                    if(! estadoAlarmaApnea){
                        estadoAlarmaApnea = true;
                        alarmaControl->iniciaAlarma(alarmaControl->APNEA);
                    }
                }
                else{
                    if(diccionario_alarma->value("Apnea") == 0){
                        actualizar_en_lista("Apnea", 1);
                        if(! estadoAlarmaApnea){
                            estadoAlarmaApnea = true;
                            alarmaControl->iniciaAlarma(alarmaControl->APNEA);
                        }
                    }
                }
            }
            else{
                if(buscar_en_lista("Apnea")){
                    actualizar_en_lista("Apnea", 0);
                    if(diccionario_alarma->value("Presion MAX") == 0){
                        if(estadoAlarmaPresion){
                            estadoAlarmaPresion = false;
                            alarmaControl->detenAlarma(alarmaControl->APNEA);
                        }
                    }
                }
            }
        }
        else if(tipo == "7"){
            if(estado == 1){
                qDebug() << "Alarma volumen tidal max ACTIVADO";
                if(! buscar_en_lista("Vol tidal MAX")){
                    agregar_en_lista("Vol tidal MAX", 1);
                    qDebug() << "___Agrega Vol tidal MAX";
                    widgetVoli->label_uni->setStyleSheet("color: yellow;");
                    widgetVoli->label_valor->setStyleSheet("color: yellow;");
                    widgetVoli->label_nombre->setStyleSheet("background-color: yellow;\n"
                                                           "color: black;\n"
                                                           "border: 2px solid yellow;\n"
                                                           "border-top-right-radius: 3Px; "
                                                           "border-bottom-right-radius: 3Px; "
                                                           "border-bottom-left-radius: 3Px;");
                    consul->agregar_evento("ALARMA", obtener_modo(), "VOLUMEN TIDAL ALTO ACTIVADO - 7");
                    contornoColorAlarma(widgetVoli, "yellow");
                    if(! estadoAlarmaVol){
                        estadoAlarmaVol = true;
                        alarmaControl->iniciaAlarma(alarmaControl->VOLUMEN);
                    }
                }
                else{
                    if(diccionario_alarma->value("Vol tidal MAX") == 0){
                        actualizar_en_lista("Vol tidal MAX", 1);
                        qDebug() << "___Agrega Vol tidal MAX";
                        widgetVoli->label_uni->setStyleSheet("color: yellow;");
                        widgetVoli->label_valor->setStyleSheet("color: yellow;");
                        widgetVoli->label_nombre->setStyleSheet("background-color: yellow;\n"
                                                               "color: black;\n"
                                                               "border: 2px solid yellow;\n"
                                                               "border-top-right-radius: 3Px; "
                                                               "border-bottom-right-radius: 3Px; "
                                                               "border-bottom-left-radius: 3Px;");
                        consul->agregar_evento("ALARMA", obtener_modo(), "VOLUMEN TIDAL ALTO ACTIVADO - 7");
                        contornoColorAlarma(widgetVoli, "yellow");
                        if(! estadoAlarmaVol){
                            estadoAlarmaVol = true;
                            alarmaControl->iniciaAlarma(alarmaControl->VOLUMEN);
                        }
                    }
                }
            }
            else{
                qDebug() << "Alarma volumen tidal max DESACTIVADO";
                if(buscar_en_lista("Vol tidal MAX")){
                    actualizar_en_lista("Vol tidal MAX", 0);
                    consul->agregar_evento("ALARMA", obtener_modo(), "VOLUMEN TIDAL ALTO DESACTIVADO - 7");
                    if(diccionario_alarma->value("Vol tidal MAX") == 0){
                        if(estadoAlarmaVol){
                            estadoAlarmaVol = false;
                            alarmaControl->detenAlarma(alarmaControl->VOLUMEN);
                            widgetVoli->label_uni->setStyleSheet("color: white;");
                            widgetVoli->label_valor->setStyleSheet("color: white;");
                            widgetVoli->label_nombre->setStyleSheet("background-color: white;\n"
                                                                   "color: black;\n"
                                                                   "border: 2px solid white;\n"
                                                                   "border-top-right-radius: 3Px; "
                                                                   "border-bottom-right-radius: 3Px; "
                                                                   "border-bottom-left-radius: 3Px;");
                            contornoColorAlarma(widgetVoli, "white");
                        }
                    }
                }
            }
        }
        else if(tipo == "8"){
            if(estado == 1){
                qDebug() << "Alarma frecuencia alta ACTIVADO";
                if(! buscar_en_lista("Frec. MAX")){
                    agregar_en_lista("Frec. MAX", 1);
                    qDebug() << "___Agrega Frec. MAX";
                    widgetFR->label_uni->setStyleSheet("color: yellow;");
                    widgetFR->label_valor->setStyleSheet("color: yellow;");
                    widgetFR->label_nombre->setStyleSheet("background-color: yellow;\n"
                                                           "color: black;\n"
                                                           "border: 2px solid yellow;\n"
                                                           "border-top-right-radius: 3Px; "
                                                           "border-bottom-right-radius: 3Px; "
                                                           "border-bottom-left-radius: 3Px;");
                    consul->agregar_evento("ALARMA", obtener_modo(), "FRECUENCIA ALTA ACTIVADA - 8");
                    contornoColorAlarma(widgetFR, "yellow");
                    if(! estadoAlarmaFr){
                        estadoAlarmaFr = true;
                        alarmaControl->iniciaAlarma(alarmaControl->FRECUENCIA);
                    }
                }
                else{
                    if(diccionario_alarma->value("Frec. MAX") == 0){
                        actualizar_en_lista("Frec. MAX", 1);
                        qDebug() << "___Agrega Frec. MAX";
                        widgetFR->label_uni->setStyleSheet("color: yellow;");
                        widgetFR->label_valor->setStyleSheet("color: yellow;");
                        widgetFR->label_nombre->setStyleSheet("background-color: yellow;\n"
                                                               "color: black;\n"
                                                               "border: 2px solid yellow;\n"
                                                               "border-top-right-radius: 3Px; "
                                                               "border-bottom-right-radius: 3Px; "
                                                               "border-bottom-left-radius: 3Px;");
                        consul->agregar_evento("ALARMA", obtener_modo(), "FRECUENCIA ALTA ACTIVADA - 8");
                        contornoColorAlarma(widgetFR, "yellow");
                        if(! estadoAlarmaFr){
                            estadoAlarmaFr = true;
                            alarmaControl->iniciaAlarma(alarmaControl->FRECUENCIA);
                        }
                    }
                }
            }
            else{
                qDebug() << "Alarma frecuencia alta DESACTIVADO";
                if(buscar_en_lista("Frec. MAX")){
                    actualizar_en_lista("Frec. MAX", 0);
                    consul->agregar_evento("ALARMA", obtener_modo(), "FRECUENCIA ALTA DESACTIVADA - 8");
                    if(diccionario_alarma->value("Frec. MAX") == 0){
                        if(estadoAlarmaFr){
                            estadoAlarmaFr = false;
                            alarmaControl->detenAlarma(alarmaControl->FRECUENCIA);
                            widgetFR->label_uni->setStyleSheet("color: white;");
                            widgetFR->label_valor->setStyleSheet("color: white;");
                            widgetFR->label_nombre->setStyleSheet("background-color: white;\n"
                                                                   "color: black;\n"
                                                                   "border: 2px solid white;\n"
                                                                   "border-top-right-radius: 3Px; "
                                                                   "border-bottom-right-radius: 3Px; "
                                                                   "border-bottom-left-radius: 3Px;");
                            contornoColorAlarma(widgetFR, "white");
                        }
                    }
                }
            }
        }
        else if(tipo == "9"){
            if(estado == 1){
                qDebug() << "Alarma frecuencia baja ACTIVADO";
                if(! buscar_en_lista("Frec. MIN")){
                    agregar_en_lista("Frec. MIN", 1);
                    qDebug() << "___Agrega Frec. MIN";
                    widgetFR->label_uni->setStyleSheet("color: yellow;");
                    widgetFR->label_valor->setStyleSheet("color: yellow;");
                    widgetFR->label_nombre->setStyleSheet("background-color: yellow;\n"
                                                           "color: black;\n"
                                                           "border: 2px solid yellow;\n"
                                                           "border-top-right-radius: 3Px; "
                                                           "border-bottom-right-radius: 3Px; "
                                                           "border-bottom-left-radius: 3Px;");
                    consul->agregar_evento("ALARMA", obtener_modo(), "FRECUENCIA BAJA ACTIVADA - 9");
                    contornoColorAlarma(widgetFR, "yellow");
                    if(! estadoAlarmaFr){
                        estadoAlarmaFr = true;
                        alarmaControl->iniciaAlarma(alarmaControl->FRECUENCIA);
                    }
                }
                else{
                    if(diccionario_alarma->value("Frec. MIN") == 0){
                        actualizar_en_lista("Frec. MIN", 1);
                        qDebug() << "___Agrega Frec. MIN";
                        widgetFR->label_uni->setStyleSheet("color: yellow;");
                        widgetFR->label_valor->setStyleSheet("color: yellow;");
                        widgetFR->label_nombre->setStyleSheet("background-color: yellow;\n"
                                                               "color: black;\n"
                                                               "border: 2px solid yellow;\n"
                                                               "border-top-right-radius: 3Px; "
                                                               "border-bottom-right-radius: 3Px; "
                                                               "border-bottom-left-radius: 3Px;");
                        consul->agregar_evento("ALARMA", obtener_modo(), "FRECUENCIA BAJA ACTIVADA - 9");
                        contornoColorAlarma(widgetFR, "yellow");
                        if(! estadoAlarmaFr){
                            estadoAlarmaFr = true;
                            alarmaControl->iniciaAlarma(alarmaControl->FRECUENCIA);
                        }
                    }
                }
            }
            else{
                qDebug() << "Alarma frecuencia baja DESACTIVADO";
                if(buscar_en_lista("Frec. MIN")){
                    actualizar_en_lista("Frec. MIN", 0);
                    consul->agregar_evento("ALARMA", obtener_modo(),  "FRECUENCIA BAJA DESACTIVADA - 9");
                    if(diccionario_alarma->value("Frec. MIN") == 0){
                        if(estadoAlarmaFr){
                            estadoAlarmaFr = false;
                            alarmaControl->detenAlarma(alarmaControl->FRECUENCIA);
                            widgetFR->label_uni->setStyleSheet("color: white;");
                            widgetFR->label_valor->setStyleSheet("color: white;");
                            widgetFR->label_nombre->setStyleSheet("background-color: white;\n"
                                                                   "color: black;\n"
                                                                   "border: 2px solid white;\n"
                                                                   "border-top-right-radius: 3Px; "
                                                                   "border-bottom-right-radius: 3Px; "
                                                                   "border-bottom-left-radius: 3Px;");
                            contornoColorAlarma(widgetFR, "white");
                        }
                    }
                }
            }
        }
        else if(tipo == "A"){
            if(estado == 1){
                qDebug() << "Alarma volumen minuto bajo ACTIVADO";
                if(! buscar_en_lista("Vol min MIN")){
                    agregar_en_lista("Vol min MIN", 1);
                    qDebug() << "___Agrega Vol min MIN";
                    signoVm->bar->setPalette(*paleAlta);
                    signoVm->label_title->setStyleSheet("color: red;");
                    consul->agregar_evento("ALARMA", obtener_modo(), "VOLUMEN MIN BAJO ACTIVADO - A");
                    if(! estadoAlarmaVolMin){
                        estadoAlarmaVolMin = true;
                        alarmaControl->iniciaAlarma(alarmaControl->VOLMINIMO);
                    }
                }
                else{
                    if(diccionario_alarma->value("Vol min MIN") == 0){
                        actualizar_en_lista("Vol min MIN", 1);
                        qDebug() << "___Agrega Vol min MIN";
                        signoVm->bar->setPalette(*paleAlta);
                        signoVm->label_title->setStyleSheet("color: red;");
                        consul->agregar_evento("ALARMA", obtener_modo(),  "VOLUMEN MIN BAJO ACTIVADO - A");
                        if(! estadoAlarmaVolMin){
                            estadoAlarmaVolMin = true;
                            alarmaControl->iniciaAlarma(alarmaControl->VOLMINIMO);
                        }
                    }
                }
            }
            else{
                qDebug() << "Alarma volumen minuto bajo DESACTIVADO";
                if(buscar_en_lista("Vol min MIN")){
                    actualizar_en_lista("Vol min MIN", 0);
                    consul->agregar_evento("ALARMA", obtener_modo(), "VOLUMEN MIN BAJO DESACTIVADO - A");
                    if(diccionario_alarma->value("Vol min MIN") == 0){
                        if(estadoAlarmaVolMin){
                            estadoAlarmaVolMin = false;
                            alarmaControl->detenAlarma(alarmaControl->VOLMINIMO);
                            signoVm->bar->setPalette(*paleNormal);
                            signoVm->label_title->setStyleSheet("color: white;");
                        }
                    }
                }
            }
        }
        else if(tipo == "B"){
            if(estado == 1){
                qDebug() << "Alarma volumen tidal bajo ACTIVADO";
                if(! buscar_en_lista("Vol tidal MIN")){
                    agregar_en_lista("Vol tidal MIN", 1);
                    qDebug() << "___Agrega Vol tidal MIN";
                    widgetVoli->label_uni->setStyleSheet("color: yellow;");
                    widgetVoli->label_valor->setStyleSheet("color: yellow;");
                    widgetVoli->label_nombre->setStyleSheet("background-color: yellow;\n"
                                                           "color: black;\n"
                                                           "border: 2px solid yellow;\n"
                                                           "border-top-right-radius: 3Px; "
                                                           "border-bottom-right-radius: 3Px; "
                                                           "border-bottom-left-radius: 3Px;");
                    consul->agregar_evento("ALARMA", obtener_modo(), "VOLUMEN TIDAL BAJO ACTIVADO - B");
                    contornoColorAlarma(widgetVoli, "yellow");
                    if(! estadoAlarmaVol){
                        estadoAlarmaVol = true;
                        alarmaControl->iniciaAlarma(alarmaControl->VOLUMEN);
                    }
                }
                else{
                    if(diccionario_alarma->value("Vol tidal MIN") == 0){
                        actualizar_en_lista("Vol tidal MIN", 1);
                        qDebug() << "___Agrega Vol tidal MIN";
                        widgetVoli->label_uni->setStyleSheet("color: yellow;");
                        widgetVoli->label_valor->setStyleSheet("color: yellow;");
                        widgetVoli->label_nombre->setStyleSheet("background-color: yellow;\n"
                                                               "color: black;\n"
                                                               "border: 2px solid yellow;\n"
                                                               "border-top-right-radius: 3Px; "
                                                               "border-bottom-right-radius: 3Px; "
                                                               "border-bottom-left-radius: 3Px;");
                        consul->agregar_evento("ALARMA", obtener_modo(), "VOLUMEN TIDAL BAJO ACTIVADO - B");
                        contornoColorAlarma(widgetVoli, "yellow");
                        if(! estadoAlarmaVol){
                            estadoAlarmaVol = true;
                            alarmaControl->iniciaAlarma(alarmaControl->VOLUMEN);
                        }
                    }
                }
            }
            else{
                qDebug() << "Alarma volumen tidal bajo DESACTIVADO";
                if(buscar_en_lista("Vol tidal MIN")){
                    actualizar_en_lista("Vol tidal MIN", 0);
                    consul->agregar_evento("ALARMA", obtener_modo(), "VOLUMEN TIDAL BAJO DESACTIVADO - B");
                    if(diccionario_alarma->value("Vol tidal MIN") == 0){
                        if(estadoAlarmaVol){
                            estadoAlarmaVol = false;
                            alarmaControl->detenAlarma(alarmaControl->VOLUMEN);
                            widgetVoli->label_uni->setStyleSheet("color: white;");
                            widgetVoli->label_valor->setStyleSheet("color: white;");
                            widgetVoli->label_nombre->setStyleSheet("background-color: white;\n"
                                                                   "color: black;\n"
                                                                   "border: 2px solid white;\n"
                                                                   "border-top-right-radius: 3Px; "
                                                                   "border-bottom-right-radius: 3Px; "
                                                                   "border-bottom-left-radius: 3Px;");
                            contornoColorAlarma(widgetVoli, "white");
                        }
                    }
                }
            }
        }
        else if(tipo == "C"){
            if(estado == 1){
                qDebug() << "Alarma presion baja ACTIVADO";
                if(! buscar_en_lista("Presion MIN")){
                    agregar_en_lista("Presion MIN", 1);
                    qDebug() << "___Agrega Presion MIN";
                    signoPEEP->bar->setPalette(*palemedia_baja);
                    signoPEEP->label_title->setStyleSheet("color: yellow;");
                    consul->agregar_evento("ALARMA", obtener_modo(), "PRESION BAJA ACTIVADA - C");
                    if(! estadoAlarmaPresion){
                        estadoAlarmaPresion = true;
                        alarmaControl->iniciaAlarma(alarmaControl->PRESION);
                    }
                }
                else{
                    if(diccionario_alarma->value("Presion MIN") == 0){
                        actualizar_en_lista("Presion MIN", 1);
                        qDebug() << "___Agrega Presion MIN";
                        signoPEEP->bar->setPalette(*palemedia_baja);
                        signoPEEP->label_title->setStyleSheet("color: yellow;");
                        consul->agregar_evento("ALARMA", obtener_modo(), "PRESION BAJA ACTIVADA - C");
                        if(! estadoAlarmaPresion){
                            estadoAlarmaPresion = true;
                            alarmaControl->iniciaAlarma(alarmaControl->PRESION);
                        }
                    }
                }
            }
            else{
                qDebug() << "Alarma presion baja DESACTIVADO";
                if(buscar_en_lista("Presion MIN")){
                    actualizar_en_lista("Presion MIN", 0);
                    consul->agregar_evento("ALARMA", obtener_modo(), "PRESION BAJA DESACTIVADA - C");
                    signoPEEP->bar->setPalette(*paleNormal);
                    signoPEEP->label_title->setStyleSheet("color: white;");
                    if(diccionario_alarma->value("Presion MIN") == 0){
                        if(estadoAlarmaPresion){
                            estadoAlarmaPresion = false;
                            alarmaControl->detenAlarma(alarmaControl->PRESION);
                        }
                    }
                }
            }
        }
        else if(tipo == "D"){
            if(estado == 1){
                qDebug() << "Alarma presion baja config ACTIVADO";
                if(! buscar_en_lista("Presion baja")){
                    agregar_en_lista("Presion baja", 1);
                    consul->agregar_evento("ALARMA", obtener_modo(), "PRESION BAJA CONFIG ACTIVADA - D");
                    qDebug() << "___Agrega Presion baja";
                    if(! estadoAlarmaPresion){
                        estadoAlarmaPresion = true;
                        alarmaControl->iniciaAlarma(alarmaControl->PRESION);
                    }
                }
                else{
                    if(diccionario_alarma->value("Presion baja") == 0){
                        actualizar_en_lista("Presion baja", 1);
                        consul->agregar_evento("ALARMA", obtener_modo(), "PRESION BAJA CONFIG ACTIVADA - D");
                        qDebug() << "___Agrega Presion baja";
                        if(! estadoAlarmaPresion){
                            estadoAlarmaPresion = true;
                            alarmaControl->iniciaAlarma(alarmaControl->PRESION);
                        }
                    }
                }
            }
            else{
                qDebug() << "Alarma presion baja config DESACTIVADO";
                if(buscar_en_lista("Presion baja")){
                    actualizar_en_lista("Presion baja", 0);
                    consul->agregar_evento("ALARMA", obtener_modo(), "PRESION BAJA CONFIG DESACTIVADA - D");
                    if(diccionario_alarma->value("Presion baja") == 0){
                        if(estadoAlarmaPresion){
                            estadoAlarmaPresion = false;
                            alarmaControl->detenAlarma(alarmaControl->PRESION);
                        }
                    }
                }
            }

        }
        else if(tipo == "E"){
            if(estado == 1){
                qDebug() << "Alarma desconexion paciente ACTIVADO";
                if(! buscar_en_lista("Desc. Paciente")){
                    agregar_en_lista("Desc. Paciente", 1);
                    consul->agregar_evento("ALARMA", obtener_modo(), "Desconexion del paciente ACTIVADA - E");
                    qDebug() << "___Agrega Desc. Paciente";
                    if(! estadoAlarmaDesconexion){
                        estadoAlarmaDesconexion = true;
                        alarmaControl->iniciaAlarma(alarmaControl->DESCONEXION);
                    }
                }
                else{
                    if(diccionario_alarma->value("Desc. Paciente") == 0){
                        actualizar_en_lista("Desc. Paciente", 1);
                        consul->agregar_evento("ALARMA", obtener_modo(), "Desconexion del paciente ACTIVADA - E");
                        qDebug() << "___Agrega Desc. Paciente";
                        if(! estadoAlarmaDesconexion){
                            estadoAlarmaDesconexion = true;
                            alarmaControl->iniciaAlarma(alarmaControl->DESCONEXION);
                        }
                    }
                }
            }
            else{
                qDebug() << "Alarma desconexion paciente DESACTIVADO";
                if(buscar_en_lista("Desc. Paciente")){
                    actualizar_en_lista("Desc. Paciente", 0);
                    consul->agregar_evento("ALARMA", obtener_modo(), "Desconexion del paciente DESACTIVADA - E");
                    if(diccionario_alarma->value("Desc. Paciente") == 0){
                        if(estadoAlarmaDesconexion){
                            estadoAlarmaDesconexion = false;
                            alarmaControl->detenAlarma(alarmaControl->DESCONEXION);
                        }
                    }
                }
            }
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::poner_datos(){
    try {
        if(cambiagrafi){
            limpiar_graficas();
        }
        //qDebug() << "poner_datos funcion";
        QString ti = PD_ti;
        QString te = PD_te;
        QString vi = PD_vi;
        QString ve = PD_ve;
        QString vm = PD_vm;
        QString fr = PD_fr;
        QString pip = PD_pip;
        QString peep = PD_peep;
        QString fp = PD_fp;
        /*qDebug() << "ti: " + ti;
        qDebug() << "te: " + te;
        qDebug() << "vi: " + vi;
        qDebug() << "ve: " + ve;
        qDebug() << "vm: " + vm;
        qDebug() << "fr: " + fr;
        qDebug() << "pip: " + pip;
        qDebug() << "peep: " + peep;
        qDebug() << "fp: " + fp;*/

        QString t_vi = QString::number(static_cast<int>(vi.toFloat()*1000));
        QString t_ve = QString::number(static_cast<int>(ve.toFloat()*1000));
        widgetVoli->label_valor->setText(t_vi);
        widgetVole->label_valor->setText(t_ve);
        signoVm->bar->setValue(vm.toFloat());
        widgetFR->label_valor->setText(fr);
        signoTiempoI->bar->setValue(ti.toFloat());
        signoTiempoE->bar->setValue(te.toFloat());
        float relacion_te = 0;
        if(ti.toFloat() != 0){
            relacion_te = te.toFloat() / ti.toFloat();
        }
        else{
            relacion_te = 0;
        }
        //qDebug() << "poner_datos funcion despues relacion";
        widgetTiTe->label_valor->setText("1:" + QString::number(relacion_te,'f',1));
        //Jeru. nuevo offset pip
        if(modoSel == 1 || modoSel == 3 || modoSel == 5){
            float temp = pip.toFloat() + offset_pip;
            signoPIP->bar->setValue(temp);
        }
        else{
            signoPIP->bar->setValue(pip.toFloat());
        }
        signoPEEP->bar->setValue(peep.toFloat());
        widgetFlujo->label_valor->setText(fp);
        //presion media
        float prom = 0;
        if(ti.toFloat() != 0 && te.toFloat() != 0){
            prom = ((pip.toFloat() * ti.toFloat())+(peep.toFloat() * te.toFloat()))/(ti.toFloat() + te.toFloat());
        }

        //float prom = (pip.toFloat()+peep.toFloat())/2;
        widgetPresPrin->label_valor->setText(QString::number(prom,'f',1));

        QGuiApplication::processEvents();
        //qDebug() << "poner_datos funcion fin ";
        // Jeru lazos 17/02
        if(esperando_limites_lazos && cambiagrafi){
            //obtener los nuevos rangos de los lazos
            min_lazo_pres_x = peep.toFloat() - (peep.toFloat()*0.35);
            max_lazo_pres_x = pip.toFloat() + (pip.toFloat()*0.2);

            min_lazo_vol_y = -0.10;
            max_lazo_vol_y = (vi.toFloat() + (vi.toFloat()*0.2));
            //qDebug() << "max_lazo_vol_y: " + QString::number(max_lazo_vol_y,'f',3);
            //qDebug() << "vi: " + vi;


            min_lazo_vol_x = -0.10;
            max_lazo_vol_x = (vi.toFloat() + (vi.toFloat()*0.2));

            min_lazo_flujo_y = -(fp.toFloat() * 1.3);
            max_lazo_flujo_y = fp.toFloat() * 1.2;

            esperando_limites_lazos = false;

            graficaPV->grafica->xAxis->setRange(min_lazo_pres_x, max_lazo_pres_x);
            graficaPV->grafica->yAxis->setRange(min_lazo_vol_y, max_lazo_vol_y);
            graficaPV->grafica->replot();

            graficaVF->grafica->xAxis->setRange(min_lazo_vol_x, max_lazo_vol_x);
            graficaVF->grafica->yAxis->setRange(min_lazo_flujo_y, max_lazo_flujo_y);
            graficaVF->grafica->replot();
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::revisarBanderasVentilador(){
    try {
        qDebug() << "Se activa timerVentilador!";
        if(numeroBanderaVentilador == 0){
            qDebug() << "-No se recibio respuesta a P";
            configurandoVentilador = false;
        }
        else if(numeroBanderaVentilador == 1){
            qDebug() << "-NO se recibio respuesta a C offset";
            configurandoVentilador = false;
        }
        else if(numeroBanderaVentilador == 2){
            qDebug() << "-No se recibio respuesta a  V modo";
            configurandoVentilador = false;
        }
        else if(numeroBanderaVentilador == 3){
            qDebug() << "-No se recibio respuesta a  comando principal";
            if(reenviar_paro){
                serVent->detener_ventilador(tramaVentilador);
            }
            else{
                configurandoVentilador = false;
                if(timerVentiladorDetenido->isActive()){
                    timerVentiladorDetenido->stop();
                }
                qDebug() << "Vent ON - 2";
            }

            /*if(es_actualizacion){
                //checar si falló la actualizacion
                qDebug() << "Falla actualización control!!";

                volverIntetarComandoM = false;

                falla_actualizacion = true;
                configurandoVentilador = false;
                label_debug->setText("Pulse Actualizar");
                timerTPresion1S->stop();
                consul->agregar_evento("COMUNICACION", obtener_modo(), "ERROR NO RESPUESTA T CONTROL");
                serPresion->iniciar_sensor_presion();
            }*/

            if(volverIntetarComandoM){
                volverIntetarComandoM = false;
                if(volverIntentarModo){
                    temp_timer_ini->start(1000);
                }
                else{
                    temp_timer_det->start(800);
                }
                qDebug() << "segundo intento comando M - llega desde bandera 3 ventilador";
            }

        }
        else if(numeroBanderaVentilador == 4){
            qDebug() << "-No se recibio respuesta a origen";
            configurandoVentilador = false;
        }
        label_debug->setText("CE:" + QString::number(numeroBanderaVentilador));
        consul->agregar_evento("Trama control", obtener_modo(),"CE: " + QString::number(numeroBanderaVentilador));
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::revisarConfigVentilador(){
    try {
        if(vrecibidaVentilador){
            if(origenListo){
                timerConfigVent->stop();
            }
            else{
                if(contadorOrigen < 6){
                    contadorOrigen++;
                }
                else{
                    if(vAvisoV == nullptr){
                        qDebug() << "origenListo Error";
                        muestraAvisoVentilador("ERROR VENTILADOR");
                        timerConfigVent->stop();
                        consul->agregar_evento("COMUNICACION", obtener_modo(), "ERROR NO RESPONDE CONTROL I");
                    }
                }
            }
        }
        else{
            if(contadorVVentilador < 3){
                serVent->envia_trama_config("F\n");
                contadorVVentilador++;
            }
            else{
                if(vAvisoV == nullptr){
                    qDebug() << "vrecibidaVentilador Error";
                    muestraAvisoVentilador("NO HAY CONEXION CON EL VENTILADOR");
                    consul->agregar_evento("COMUNICACION", obtener_modo(), "ERROR NO RESPONDE CONTROL II");
                    timerConfigVent->stop();
                }
            }
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::revisarOffsetVentilador(){
    try {
        if(cambiosOffsets){
            if(timerOffsetsVent->isActive()){
                timerOffsetsVent->stop();
                contadorOffsetsVentilador = 0;
            }
        }
        else{
            if(contadorOffsetsVentilador < 4){
                contadorOffsetsVentilador++;
                serVent->envia_trama_config(tramaOffsets);
            }
            else{
                if(vAvisoV == nullptr){
                    qDebug() << "OffsetsVentilador Error";
                    muestraAvisoVentilador("NO HAY CONEXION CON EL VENTILADOR - Offsets");
                    consul->agregar_evento("COMUNICACION", obtener_modo(), "ERROR NO RESPONDE CONTROL III");
                    timerOffsetsVent->stop();
                }
            }
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::revisarMIniVentilador(){
    try {
        if(cambiosMIni){
            if(timerMIniVent->isActive()){
                timerMIniVent->stop();
                contadorMIniVentilador = 0;
            }
        }
        else{
            if(contadorMIniVentilador < 4){
                contadorMIniVentilador++;
                serVent->envia_trama_config(tramaVentilador);
            }
            else{
                if(vAvisoV == nullptr){
                    qDebug() << "MIniVentilador Error";
                    muestraAvisoVentilador("NO HAY CONEXION CON EL VENTILADOR - MIni");
                    consul->agregar_evento("COMUNICACION", obtener_modo(), "ERROR NO RESPONDE CONTROL IV");
                    timerMIniVent->stop();
                }
            }
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::revisarConexionVentilador(){
    try {
        if(banderaConexionVentilador){
            banderaConexionVentilador = false;
        }
        else{
            if(contadorErrorConVent == 3){
                if(vAvisoV == nullptr){
                    muestraAvisoVentilador("NO RESPONDE");
                }
            }
            else{
                if(! configurandoVentilador){
                    contadorErrorConVent++;
                }
            }
        }
        if(! configurandoVentilador){
            serVent->envia_trama_config("P\n");
        }
        timerConVentilador->start(7000);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::actualizarDatosVentilador(){
    try {
        qDebug() << "Entra a actualizarDatosVentilador";
        if(! configurandoVentilador){
            if(estadoVentilador){
                if(huboCambioTrama || huboCambioTramaSenPresion || huboCambioTramaSenPresionW){
                    es_actualizacion = true;
                    qDebug() << "Cambio trama principal";
                    huboCambioTrama = false;
                    huboCambioTramaSenPresion = false;
                    huboCambioTramaSenPresionW = false;
                    label_debug->setText("Actualizando...");
                    configurandoSenPresion = true;
                    if(timerTPresion5S->isActive()){
                        timerTPresion5S->stop();
                    }
                    /*serPresion->detener_sensor_presion();
                    serPresion->serPuerto->clear(QSerialPort::Input);
                    QThread::msleep(500);
                    serPresion->escribir("A3\n");
                    banderaModoSenPresion = 4;
                    timerTPresion1S->start(1500);*/
                    //----------
                    serPresion->serPuerto->clear(QSerialPort::Input);
                    QThread::msleep(500);
                    timerTPresion1S->start(2500);
                    banderaModoSenPresion = 0;
                    serPresion->escribir(trama_c_senpresion);
                    qDebug() << "Envia trama c -";
                }
                else{
                    if(falla_actualizacion){
                        falla_actualizacion = false;
                        es_actualizacion = true;
                        qDebug() << "Reintento trama principal";
                        label_debug->setText("Actualizando...");
                        configurandoSenPresion = true;
                        if(timerTPresion5S->isActive()){
                            timerTPresion5S->stop();
                        }
                        /*serPresion->detener_sensor_presion();
                        serPresion->serPuerto->clear(QSerialPort::Input);
                        serPresion->escribir("A3\n");
                        banderaModoSenPresion = 4;
                        timerTPresion1S->start(1500);*/
                        serPresion->serPuerto->clear(QSerialPort::Input);
                        QThread::msleep(500);
                        timerTPresion1S->start(2500);
                        banderaModoSenPresion = 0;
                        serPresion->escribir(trama_c_senpresion);
                        qDebug() << "Envia trama c -";
                    }
                }
            }
            else{
                qDebug() << "Actualizar datos - no esta activo el ventilador";
                //controlVentilador();
            }
        }
        else{
            qDebug() << "Actualizar datos - esta configurando";
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::controlVentilador(){
    try {
        if(! configurandoVentilador){
            if(estadoVentilador){
                qDebug() << "Detener ventilador";
                label_debug->setText("Deteniendo.");
                if(timerTPresion5S->isActive()){
                    timerTPresion5S->stop();
                }
                QThread::sleep(1);
                configurandoSenPresion = true;
                timerTPresion1S->start(5000);
                banderaModoSenPresion = 1;
                recibe_a0 = false;
                serPresion->serPuerto->clear(QSerialPort::Input);
                serPresion->detener_sensor_presion();
                timerLimpiarBuffer->start(1000);
                configurandoVentilador = false;
                volverIntetarComandoM = true;
                volverIntentarModo = false;
                detener_ventilador();
                timerVentiladorDetenido->start();
            }
            else{
                lista_alarmas->clear();
                qDebug() << "Configurando";
                label_debug->setText("Configurando...");
                configurandoSenPresion = true;
                if(timerTPresion5S->isActive()){
                    timerTPresion5S->stop();
                }
                QThread::sleep(1);
                banderaModoSenPresion = 0;
                timerTPresion1S->start(5000);
                serPresion->escribir(trama_c_senpresion);
                configurandoVentilador = true;
            }
        }
        else{
            qDebug() << "Ya se esta configurando, espere";
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::obtener_trama_c_senpresion(){
    try {
        QString modo_vent = obtener_modo_vent();
        //qDebug() << "obtener_trama_c_senpresion, modo_vet: " + modo_vent;
        int modo_vent_int = modo_vent.toInt();
        if(modo_vent_int == 0){
            trama_c_senpresion = tramas->obtener_trama_serpresion_config(0);
        }
        else if(modo_vent_int == 1){
            trama_c_senpresion = tramas->obtener_trama_serpresion_config(1);
        }
        else if(modo_vent_int == 2){
            trama_c_senpresion = tramas->obtener_trama_serpresion_config(2);
        }
        else if(modo_vent_int == 3){
            trama_c_senpresion = tramas->obtener_trama_serpresion_config(3);
        }
        else if(modo_vent_int == 4){
            trama_c_senpresion = tramas->obtener_trama_serpresion_config(4);
        }
        else if(modo_vent_int == 5){
            trama_c_senpresion = tramas->obtener_trama_serpresion_config(5);
        }
        qDebug() << "trama C!!!: " + trama_c_senpresion;
        tramaSenPresion = trama_c_senpresion;
        if(primera_vez_modo_sen_presion){
            primera_vez_modo_sen_presion = false;
            ultimaTramaSenPresion = tramaSenPresion;
        }
        else{
            if(tramaSenPresion != ultimaTramaSenPresion){
                huboCambioTramaSenPresion = true;
                ultimaTramaSenPresion = tramaSenPresion;

                if(estadoVentilador){
                    label_debug->setText("Presione ACTUALIZAR");
                }
                else{
                    label_debug->setText("Presione INICIAR");
                }
            }
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

QString Monitor::obtener_modo_vent(){
    try {
        QString modo = "0";
        if(modoVentilador == "MODO: PCVM"){
            modo = "0";
        }
        else if(modoVentilador == "MODO: VCMV"){
            modo = "1";
        }
        else if(modoVentilador == "MODO: PSIMV"){
            modo = "2";
        }
        else if(modoVentilador == "MODO: VSIMV"){
            modo = "3";
        }
        else if(modoVentilador == "MODO: PCPAP"){
            modo = "4";
        }
        else if(modoVentilador == "MODO: VCPAP"){
            modo = "5";
        }
        return modo;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

void Monitor::iniciar_ventilador(){
    try {
        qDebug() << "Envia trama principal ventilador";
        desactivar_s = true;
        if(! banderaConexionVentilador){
            while(! banderaConexionVentilador && contadorBanderaConxVent < 25){
                QThread::msleep(200);
                contadorBanderaConxVent++;
            }
            contadorBanderaConxVent = 0;
        }
        if(timerConVentilador->isActive()){
            timerConVentilador->stop();
        }
        QThread::msleep(1000);
        numeroBanderaVentilador = 3;
        timerVentilador->start(tiempo_respuesta_ventilador);
        qDebug() << "Inicia timer de espera: " + QString::number(tiempo_respuesta_ventilador);
        QString tram = tramaVentilador.mid(0,44);
        tram = tram + "1\n";
        tramaVentilador = tram;
        qDebug() << "trama a ventilador encender: " + tramaVentilador;
        serVent->iniciar_ventilador(tramaVentilador);
        desactivar_s = false;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::detener_ventilador(){
    try {
        qDebug() << "Envia trama principal ventilador detener";
        QString tram = tramaVentilador.mid(0,44);
        tram = tram + "0\n";
        tramaVentilador = tram;
        desactivar_s = true;
        if(! banderaConexionVentilador){
            while(! banderaConexionVentilador && contadorBanderaConxVent < 25){
                QThread::msleep(200);
                contadorBanderaConxVent++;
            }
            contadorBanderaConxVent = 0;
        }
        if(timerConVentilador->isActive()){
            timerConVentilador->stop();
        }
        QThread::msleep(1000);
        numeroBanderaVentilador = 3;
        timerVentilador->start(tiempo_respuesta_ventilador);
        reenviar_paro = true;
        serVent->detener_ventilador(tramaVentilador);
        //threading.Thread(target=self.reiniciar_alarmas, args=(True, False,))
        RA_setear = true;
        RA_limpiar = false;
        timerRA->start(500);
        desactivar_s = false;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::reiniciar_alarmas(){
    try {
        bool setear = RA_setear;
        bool limpiar = RA_limpiar;
        //QThread::msleep(500);
        if(setear){
            QMap<QString, int>::iterator iter;
            for(iter = diccionario_alarma->begin(); iter != diccionario_alarma->end(); ++iter){
                iter.value() = 0;
            }
            signoVm->bar->setPalette(*paleNormal);
            signoVm->label_title->setStyleSheet("color: white;");

            signoPEEP->bar->setPalette(*paleNormal);
            signoPEEP->label_title->setStyleSheet("color: white;");

            signoPIP->bar->setPalette(*paleNormal);
            signoPIP->label_title->setStyleSheet("color: white;");

            widgetVoli->label_uni->setStyleSheet("color: white;");
            widgetVoli->label_valor->setStyleSheet("color: white;");
            widgetVoli->label_nombre->setStyleSheet("background-color: white;\n"
                                                    "color: black;\n"
                                                    "border: 2px solid white;\n"
                                                    "border-top-right-radius: 3Px; "
                                                    "border-bottom-right-radius: 3Px; "
                                                    "border-bottom-left-radius: 3Px;");
            contornoColorAlarma(widgetVoli, "white");

            widgetFR->label_uni->setStyleSheet("color: white;");
            widgetFR->label_valor->setStyleSheet("color: white;");
            widgetFR->label_nombre->setStyleSheet("background-color: white;\n"
                                                    "color: black;\n"
                                                    "border: 2px solid white;\n"
                                                    "border-top-right-radius: 3Px; "
                                                    "border-bottom-right-radius: 3Px; "
                                                    "border-bottom-left-radius: 3Px;");
            contornoColorAlarma(widgetFR, "white");

            alarmaControl->reiniciarAlarmas();

            estadoAlarmaPresion = false;
            estadoAlarmaVol = false;
            estadoAlarmaFr = false;
            estadoAlarmaVolMin = false;
            estadoAlarmaFIO2 = false;
            estadoAlarmaGases = false;
            estadoAlarmaApnea = false;
            estadoAlarmaBateria = false;
            estadoAlarmaSensores = false;
        }
        if(limpiar){
            borrar_alarmas();
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::teclado(QString tecla){
    try {
        bool temp_apa = false;
        if(tecla == "aba" || tecla == "der" || tecla == "izq" || tecla == "arr"){
            mover(tecla);
        }
        else if(tecla == "ok"){
            teclaOk();
        }
        else if(tecla == "est"){
            qDebug() << "Desactivar audio";
            if(alarmaControl->pausaAlarma()){
                consul->agregar_evento("ALARMA", obtener_modo(), "SILENCIAR AUDIO");
            }
            if(! alarmaboolean){
                alarmaboolean = true;
            }
        }
        else if(tecla == "mas" || tecla == "men"){
            //qDebug() << "Tecla mas-menos";
            if(modo_graficas == 1){
                zoom_grafica(tecla);
            }
            else{
                desplazar_grafica(tecla);
            }
        }
        else if(tecla == "mod"){
            if(modo_graficas == 1){
                modo_graficas = 0;
            }
            else{
                modo_graficas = 1;
            }
        }
        else if(tecla == "adi"){
            borrar_alarmas();
        }
        else if(tecla == "can"){
            temp_apa = true;
            if(contador_apagar < 3){
                contador_apagar++;
            }
            else{
                if(estadoVentilador){
                    contador_apagar = 0;
                    espera_parar = true;
                    mostrar_confirmacion("¿Está seguro de parar el ventilador?");
                }
                else{
                    espera_apagar = true;
                    mostrar_confirmacion("¿Desea apagar el equipo?");
                }
            }
        }
        if(! temp_apa){
            contador_apagar = 0;
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::teclaOk(){
    try {
        if(elementSel == 0){
            espera_actualizar = true;
            mostrar_confirmacion("¿Está seguro de actualizar el ventilador?");
        }
        else if(elementSel == 1){
            abrir_menu_graficas();
            elementSel = 7;
            elementoSeleccionado();
        }
        else if(elementSel == 2){
            qDebug() << "test";
            numero_prueba = 0;
            pruebas_iniciales = false;
            presion_tope = 25;
            presion_pruebas = 0;
            presion_inicial_pruebas = 0;
            presion_inicial_salida = 0;
            contador_pruebas_iniciales = 0;
            contador_valvulas = 0;
            estado_trama_valvulas = "1";
            esperando_presion_tope = false;
            esperando_presion_salida = false;
            fin_prueba_presion_serpresion = false;
            fin_prueba_presion_serventilador = false;
            buscar_q_tope = false;
            pruebas_terminadas = false;
            abrir_pruebas();

        }
        else if(elementSel == 7){
           mostrarGrafica = submenugrafica->cambiar_mostrar_grafica();
        }
        else if(elementSel == 8){
            cambiagraficas();
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::seleccionar_grafica(){
    try {
        //qDebug() << "Entra a seleccionar grafica";
        if(cambiagrafi){
            //qDebug() << "Entra a seleccionar grafica - cambiagrafi";
            if(elementSel == 3){
                graficaPV->grafica->yAxis->setLabelColor(QColor(255,112,61));
                graficaPV->grafica->xAxis->setLabelColor(Qt::white);
                graficaPV->grafica->replot();

                graficaVF->grafica->yAxis->setLabelColor(Qt::white);
                graficaVF->grafica->xAxis->setLabelColor(Qt::white);
                graficaVF->grafica->replot();

            }
            else if(elementSel == 4){
                graficaPV->grafica->yAxis->setLabelColor(Qt::white);
                graficaPV->grafica->xAxis->setLabelColor(QColor(255,112,61));
                graficaPV->grafica->replot();

                graficaVF->grafica->yAxis->setLabelColor(Qt::white);
                graficaVF->grafica->xAxis->setLabelColor(Qt::white);
                graficaVF->grafica->replot();
            }
            else if(elementSel == 5){
                graficaPV->grafica->yAxis->setLabelColor(Qt::white);
                graficaPV->grafica->xAxis->setLabelColor(Qt::white);
                graficaPV->grafica->replot();

                graficaVF->grafica->yAxis->setLabelColor(QColor(255,112,61));
                graficaVF->grafica->xAxis->setLabelColor(Qt::white);
                graficaVF->grafica->replot();
            }
            else if(elementSel == 6){
                graficaPV->grafica->yAxis->setLabelColor(Qt::white);
                graficaPV->grafica->xAxis->setLabelColor(Qt::white);
                graficaPV->grafica->replot();

                graficaVF->grafica->yAxis->setLabelColor(Qt::white);
                graficaVF->grafica->xAxis->setLabelColor(QColor(255,112,61));
                graficaVF->grafica->replot();
            }
            else{
                graficaPV->grafica->yAxis->setLabelColor(Qt::white);
                graficaPV->grafica->xAxis->setLabelColor(Qt::white);
                graficaPV->grafica->replot();

                graficaVF->grafica->yAxis->setLabelColor(Qt::white);
                graficaVF->grafica->xAxis->setLabelColor(Qt::white);
                graficaVF->grafica->replot();
            }
        }
        else{
            //qDebug() << "Entra a seleccionar grafica - no cambiagrafi";
            if(elementSel == 3){
                //qDebug() << "Entra a seleccionar grafica - no cambiagrafi 3";
                graficaPresion->grafica->yAxis->setLabelColor(QColor(255,112,61));
                graficaPresion->grafica->replot();
                graficaVolumen->grafica->yAxis->setLabelColor(QColor(Qt::white));
                graficaVolumen->grafica->replot();
                graficaFlujo->grafica->yAxis->setLabelColor(QColor(Qt::white));
                graficaFlujo->grafica->replot();

            }
            else if(elementSel == 4){
                //qDebug() << "Entra a seleccionar grafica - no cambiagrafi 4";
                graficaPresion->grafica->yAxis->setLabelColor(Qt::white);
                graficaPresion->grafica->replot();
                graficaVolumen->grafica->yAxis->setLabelColor(QColor(255,112,61));
                graficaVolumen->grafica->replot();
                graficaFlujo->grafica->yAxis->setLabelColor(Qt::white);
                graficaFlujo->grafica->replot();
            }
            else if(elementSel == 5){
                //qDebug() << "Entra a seleccionar grafica - no cambiagrafi 5";
                graficaPresion->grafica->yAxis->setLabelColor(Qt::white);
                graficaPresion->grafica->replot();
                graficaVolumen->grafica->yAxis->setLabelColor(Qt::white);
                graficaVolumen->grafica->replot();
                graficaFlujo->grafica->yAxis->setLabelColor(QColor(255,112,61));
                graficaFlujo->grafica->replot();
            }
            else{
                //qDebug() << "Entra a seleccionar grafica - no cambiagrafi else";
                graficaPresion->grafica->yAxis->setLabelColor(Qt::white);
                graficaPresion->grafica->replot();
                graficaVolumen->grafica->yAxis->setLabelColor(Qt::white);
                graficaVolumen->grafica->replot();
                graficaFlujo->grafica->yAxis->setLabelColor(Qt::white);
                graficaFlujo->grafica->replot();
            }
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::obtener_nuevo_rango_grafica(QString modo){
    try {
        if(cambiagrafi){
            //mostrando lazos
            if(elementSel == 3){
                float rango = max_lazo_vol_y - min_lazo_vol_y;
                float media = rango/2;
                float origen = min_lazo_vol_y + media;
                if(modo == "mas"){
                    float nuevo_rango = (rango * 0.75) / 2;
                    max_lazo_vol_y = origen + nuevo_rango;
                    min_lazo_vol_y = origen - nuevo_rango;
                    //graficaPV->grafica->yAxis->setRange(min_lazo_vol_y, max_lazo_vol_y);
                }
                else{
                    float nuevo_rango = (rango * 1.25) / 2;
                    max_lazo_vol_y = origen + nuevo_rango;
                    min_lazo_vol_y = origen - nuevo_rango;
                    //graficaPV->grafica->yAxis->setRange(min_lazo_vol_y, max_lazo_vol_y);
                }
                graficaPV->grafica->yAxis->setRange(min_lazo_vol_y, max_lazo_vol_y);
                graficaPV->grafica->replot();

            }
            else if(elementSel == 4){
                float rango = max_lazo_pres_x - min_lazo_pres_x;
                float media = rango/2;
                float origen = min_lazo_pres_x + media;
                if(modo == "mas"){
                    float nuevo_rango = (rango * 0.75) / 2;
                    max_lazo_pres_x = origen + nuevo_rango;
                    min_lazo_pres_x = origen - nuevo_rango;
                    //graficaPV->grafica->xAxis->setRange(min_lazo_pres_x, max_lazo_pres_x);
                }
                else{
                    float nuevo_rango = (rango * 1.25) / 2;
                    max_lazo_pres_x = origen + nuevo_rango;
                    min_lazo_pres_x = origen - nuevo_rango;
                    //graficaPV->grafica->xAxis->setRange(min_lazo_pres_x, max_lazo_pres_x);
                }
                graficaPV->grafica->xAxis->setRange(min_lazo_pres_x, max_lazo_pres_x);
                graficaPV->grafica->replot();
            }
            else if(elementSel == 5){
                float rango = max_lazo_flujo_y - min_lazo_flujo_y;
                float media = rango/2;
                float origen = min_lazo_flujo_y + media;
                if(modo == "mas"){
                    float nuevo_rango = (rango * 0.75) / 2;
                    max_lazo_flujo_y = origen + nuevo_rango;
                    min_lazo_flujo_y = origen - nuevo_rango;
                    //graficaVF->grafica->yAxis->setRange(min_lazo_flujo_y, max_lazo_flujo_y);
                }
                else{
                    float nuevo_rango = (rango * 1.25) / 2;
                    max_lazo_flujo_y = origen + nuevo_rango;
                    min_lazo_flujo_y = origen - nuevo_rango;
                    //graficaVF->grafica->yAxis->setRange(min_lazo_flujo_y, max_lazo_flujo_y);
                }
                graficaVF->grafica->yAxis->setRange(min_lazo_flujo_y, max_lazo_flujo_y);
                graficaVF->grafica->replot();
            }
            else if(elementSel == 6){
                float rango = max_lazo_vol_x - min_lazo_vol_x;
                float media = rango/2;
                float origen = min_lazo_vol_x + media;
                if(modo == "mas"){
                    float nuevo_rango = (rango * 0.75) / 2;
                    max_lazo_vol_x = origen + nuevo_rango;
                    min_lazo_vol_x = origen - nuevo_rango;
                    //graficaPV->grafica->xAxis->setRange(min_lazo_vol_x, max_lazo_vol_x);
                }
                else{
                    float nuevo_rango = (rango * 1.25) / 2;
                    max_lazo_vol_x = origen + nuevo_rango;
                    min_lazo_vol_x = origen - nuevo_rango;
                    //graficaPV->grafica->xAxis->setRange(min_lazo_vol_x, max_lazo_vol_x);
                }
                graficaVF->grafica->xAxis->setRange(min_lazo_vol_x, max_lazo_vol_x);
                graficaVF->grafica->replot();
            }
        }
        else{
            //mostrando ondas
            if(elementSel == 3){
                //qDebug() << "obtener_nuevo_rango_grafica - gra presion";
                float rango = max_grafica_presion - min_grafica_presion;
                float media = rango / 2;
                float origen = min_grafica_presion + media;
                if(modo == "mas"){
                    float nuevo_rango = (rango*0.75)/2;
                    max_grafica_presion = origen + nuevo_rango;
                    min_grafica_presion = origen - nuevo_rango;
                    //graficaPresion->grafica->yAxis->setRange(min_grafica_presion, max_grafica_presion);
                    //graficaPresion->grafica->replot();
                }
                else{
                    float nuevo_rango = (rango*1.25)/2;
                    max_grafica_presion = origen + nuevo_rango;
                    min_grafica_presion = origen - nuevo_rango;
                    //graficaPresion->grafica->yAxis->setRange(min_grafica_presion, max_grafica_presion);
                    //graficaPresion->grafica->replot();
                }
                graficaPresion->grafica->yAxis->setRange(min_grafica_presion, max_grafica_presion);
                graficaPresion->grafica->replot();

            }
            else if(elementSel == 4){
                float rango = max_grafica_volumen - min_grafica_volumen;
                float media = rango / 2;
                float origen = min_grafica_volumen + media;
                if(modo == "mas"){
                    float nuevo_rango = (rango*0.75)/2;
                    max_grafica_volumen = origen + nuevo_rango;
                    min_grafica_volumen = origen - nuevo_rango;
                    //graficaVolumen->grafica->yAxis->setRange(min_grafica_volumen, max_grafica_volumen);
                }
                else{
                    float nuevo_rango = (rango*1.25)/2;
                    max_grafica_volumen = origen + nuevo_rango;
                    min_grafica_volumen = origen - nuevo_rango;
                    //graficaVolumen->grafica->yAxis->setRange(min_grafica_volumen, max_grafica_volumen);
                }
                graficaVolumen->grafica->yAxis->setRange(min_grafica_volumen, max_grafica_volumen);
                graficaVolumen->grafica->replot();
            }
            else if(elementSel == 5){
                float rango = max_grafica_flujo - min_grafica_flujo;
                float media = rango / 2;
                float origen = min_grafica_flujo + media;
                if(modo == "mas"){
                    float nuevo_rango = (rango*0.75)/2;
                    max_grafica_flujo = origen + nuevo_rango;
                    min_grafica_flujo = origen - nuevo_rango;
                    //graficaFlujo->grafica->yAxis->setRange(min_grafica_flujo, max_grafica_flujo);
                }
                else{
                    float nuevo_rango = (rango*1.25)/2;
                    max_grafica_flujo = origen + nuevo_rango;
                    min_grafica_flujo = origen - nuevo_rango;
                    //graficaFlujo->grafica->yAxis->setRange(min_grafica_flujo, max_grafica_flujo);
                }
                graficaFlujo->grafica->yAxis->setRange(min_grafica_flujo, max_grafica_flujo);
                graficaFlujo->grafica->replot();
            }
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::zoom_grafica(QString tecla){
    try {
        //qDebug() << "zoom_grafica, tecla: "+ tecla + " elemenSel: " + QString::number(elementSel) + "cambiagrafi: " + QString::number(cambiagrafi);
        if(cambiagrafi){
            //mostrando lazos
            if(tecla == "mas"){
                if(elementSel == 3){
                    obtener_nuevo_rango_grafica("mas");
                }
                else if(elementSel == 4){
                    obtener_nuevo_rango_grafica("mas");
                }
                else if(elementSel == 5){
                    obtener_nuevo_rango_grafica("mas");
                }
                else if(elementSel == 6){
                    obtener_nuevo_rango_grafica("mas");
                }
            }
            else if(tecla =="men"){
                if(elementSel == 3){
                    obtener_nuevo_rango_grafica("menos");
                }
                else if(elementSel == 4){
                    obtener_nuevo_rango_grafica("menos");
                }
                else if(elementSel == 5){
                    obtener_nuevo_rango_grafica("menos");
                }
                else if(elementSel == 6){
                    obtener_nuevo_rango_grafica("menos");
                }
            }
        }
        else{
            //mostrando ondas
            if(tecla == "mas"){
                if(elementSel == 3){
                    obtener_nuevo_rango_grafica("mas");
                }
                else if(elementSel == 4){
                    obtener_nuevo_rango_grafica("mas");
                }
                else if(elementSel == 5){
                    obtener_nuevo_rango_grafica("mas");
                }
            }
            else if(tecla =="men"){
                if(elementSel == 3){
                    obtener_nuevo_rango_grafica("menos");
                }
                else if(elementSel == 4){
                    obtener_nuevo_rango_grafica("menos");
                }
                else if(elementSel == 5){
                    obtener_nuevo_rango_grafica("menos");
                }
            }
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::obtener_nuevo_espacio_grafica(QString modo){
    try {
        if(cambiagrafi){
            //mostrando lazos
            if(elementSel == 3){
                if(modo == "mas"){
                    max_lazo_vol_y += 0.1;
                    min_lazo_vol_y += 0.1;
                    //graficaPV->grafica->yAxis->setRange(min_lazo_vol_y, max_lazo_vol_y);
                }
                else{
                    max_lazo_vol_y -= 0.1;
                    min_lazo_vol_y -= 0.1;
                    //graficaPV->grafica->yAxis->setRange(min_lazo_vol_y, max_lazo_vol_y);
                }
                graficaPV->grafica->yAxis->setRange(min_lazo_vol_y, max_lazo_vol_y);
                graficaPV->grafica->replot();

            }
            else if(elementSel == 4){
                if(modo == "mas"){
                    max_lazo_pres_x += 5;
                    min_lazo_pres_x += 5;
                    //graficaPV->grafica->xAxis->setRange(min_lazo_pres_x, max_lazo_pres_x);
                }
                else{
                    max_lazo_pres_x -= 5;
                    min_lazo_pres_x -= 5;
                    //graficaPV->grafica->xAxis->setRange(min_lazo_pres_x, max_lazo_pres_x);
                }
                graficaPV->grafica->xAxis->setRange(min_lazo_pres_x, max_lazo_pres_x);
                graficaPV->grafica->replot();
            }
            else if(elementSel == 5){
                if(modo == "mas"){
                    max_lazo_flujo_y += 10;
                    min_lazo_flujo_y += 10;
                    //graficaVF->grafica->yAxis->setRange(min_lazo_flujo_y, max_lazo_flujo_y);
                }
                else{
                    max_lazo_flujo_y -= 10;
                    min_lazo_flujo_y -= 10;
                    //graficaVF->grafica->yAxis->setRange(min_lazo_flujo_y, max_lazo_flujo_y);
                }
                graficaVF->grafica->yAxis->setRange(min_lazo_flujo_y, max_lazo_flujo_y);
                graficaVF->grafica->replot();
            }
            else if(elementSel == 6){
                if(modo == "mas"){
                    max_lazo_vol_x += 0.1;
                    min_lazo_vol_x += 0.1;
                    //graficaPV->grafica->xAxis->setRange(min_lazo_vol_x, max_lazo_vol_x);
                }
                else{
                    max_lazo_vol_x -= 0.1;;
                    min_lazo_vol_x -= 0.1;;
                    //graficaPV->grafica->xAxis->setRange(min_lazo_vol_x, max_lazo_vol_x);
                }
                graficaVF->grafica->xAxis->setRange(min_lazo_vol_x, max_lazo_vol_x);
                graficaVF->grafica->replot();
            }
        }
        else{
            //mostrando ondas
            if(elementSel == 3){
                //qDebug() << "obtener_nuevo_espacio_grafica - gra presion";
                if(modo == "mas"){
                    max_grafica_presion += 5;
                    min_grafica_presion += 5;
                }
                else{
                    max_grafica_presion -= 5;
                    min_grafica_presion -= 5;

                }
                graficaPresion->grafica->yAxis->setRange(min_grafica_presion, max_grafica_presion);
                graficaPresion->grafica->replot();
            }
            else if(elementSel == 4){
                if(modo == "mas"){
                    max_grafica_volumen += 0.1;
                    min_grafica_volumen += 0.1;
                }
                else{
                    max_grafica_volumen -= 0.1;
                    min_grafica_volumen -= 0.1;

                }
                graficaVolumen->grafica->yAxis->setRange(min_grafica_volumen, max_grafica_volumen);
                graficaVolumen->grafica->replot();
            }
            else if(elementSel == 5){
                if(modo == "mas"){
                    max_grafica_flujo += 5;
                    min_grafica_flujo += 5;
                }
                else{
                    max_grafica_flujo -= 5;
                    min_grafica_flujo -= 5;

                }
                graficaFlujo->grafica->yAxis->setRange(min_grafica_flujo, max_grafica_flujo);
                graficaFlujo->grafica->replot();
            }
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::desplazar_grafica(QString tecla){
    try {
        //qDebug() << "desplazar_grafica, tecla: "+ tecla + " elemenSel: " + QString::number(elementSel) + "cambiagrafi: " + QString::number(cambiagrafi);
        if(cambiagrafi){
            //mostrando lazos
            if(tecla == "mas"){
                if(elementSel == 3){
                    obtener_nuevo_espacio_grafica("mas");
                }
                else if(elementSel == 4){
                    obtener_nuevo_espacio_grafica("mas");
                }
                else if(elementSel == 5){
                    obtener_nuevo_espacio_grafica("mas");
                }
                else if(elementSel == 6){
                    obtener_nuevo_espacio_grafica("mas");
                }
            }
            else if(tecla =="men"){
                if(elementSel == 3){
                    obtener_nuevo_espacio_grafica("menos");
                }
                else if(elementSel == 4){
                    obtener_nuevo_espacio_grafica("menos");
                }
                else if(elementSel == 5){
                    obtener_nuevo_espacio_grafica("menos");
                }
                else if(elementSel == 6){
                    obtener_nuevo_espacio_grafica("menos");
                }
            }
        }
        else{
            //mostrando ondas
            if(tecla == "mas"){
                if(elementSel == 3){
                    obtener_nuevo_espacio_grafica("mas");
                }
                else if(elementSel == 4){
                    obtener_nuevo_espacio_grafica("mas");
                }
                else if(elementSel == 5){
                    obtener_nuevo_espacio_grafica("mas");
                }
            }
            else if(tecla =="men"){
                if(elementSel == 3){
                    obtener_nuevo_espacio_grafica("menos");
                }
                else if(elementSel == 4){
                    obtener_nuevo_espacio_grafica("menos");
                }
                else if(elementSel == 5){
                    obtener_nuevo_espacio_grafica("menos");
                }
            }
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::controlGrafica(){
    try {
        if(mostrarGrafica){
            mostrarGrafica = false;
            btn_grafica->setText("MOSTRAR\nGRAFICA");
        }
        else{
            mostrarGrafica = true;
            btn_grafica->setText("PAUSAR\nGRAFICA");
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::mover(QString tecla){
    try {
        if(submenugrafica->isHidden()){
            if(cambiagrafi){
                if(elementSel == 0){
                    if(tecla == "arr"){
                        elementSel = 4;
                    }
                    else if(tecla == "der"){
                        elementSel = 1;
                    }
                    else if(tecla == "aba"){
                        elementSel = 3;
                    }
                    else if(tecla == "izq"){
                        elementSel = 3;
                    }
                }
                else if(elementSel == 1){
                    if(tecla == "arr"){
                        elementSel = 4;
                    }
                    else if(tecla == "der"){
                        elementSel = 2;
                    }
                    else if(tecla == "aba"){
                        elementSel = 3;
                    }
                    else if(tecla == "izq"){
                        elementSel = 0;
                    }
                }
                else if(elementSel == 2){
                    if(tecla == "arr"){
                        elementSel = 6;
                    }
                    else if(tecla == "der"){
                        elementSel = 3;
                    }
                    else if(tecla == "aba"){
                        elementSel = 5;
                    }
                    else if(tecla == "izq"){
                        elementSel = 1;
                    }
                }
                else if(elementSel == 3){
                    if(tecla == "arr"){
                        elementSel = 0;
                    }
                    else if(tecla == "der"){
                        elementSel = 4;
                    }
                    else if(tecla == "aba"){
                        elementSel = 4;
                    }
                    else if(tecla == "izq"){
                        elementSel = 6;
                    }
                }
                else if(elementSel == 4){
                    if(tecla == "arr"){
                        elementSel = 3;
                    }
                    else if(tecla == "der"){
                        elementSel = 5;
                    }
                    else if(tecla == "aba"){
                        elementSel = 0;
                    }
                    else if(tecla == "izq"){
                        elementSel = 3;
                    }
                }
                else if(elementSel == 5){
                    if(tecla == "arr"){
                        elementSel = 2;
                    }
                    else if(tecla == "der"){
                        elementSel = 6;
                    }
                    else if(tecla == "aba"){
                        elementSel = 6;
                    }
                    else if(tecla == "izq"){
                        elementSel = 4;
                    }
                }
                else if(elementSel == 6){
                    if(tecla == "arr"){
                        elementSel = 5;
                    }
                    else if(tecla == "der"){
                        elementSel = 3;
                    }
                    else if(tecla == "aba"){
                        elementSel = 2;
                    }
                    else if(tecla == "izq"){
                        elementSel = 5;
                    }
                }
            }
            else{
                if(elementSel == 0){
                    if(tecla == "arr"){
                        elementSel = 5;
                    }
                    else if(tecla == "der"){
                        elementSel = 1;
                    }
                    else if(tecla == "aba"){
                        elementSel = 3;
                    }
                    else if(tecla == "izq"){
                        elementSel = 3;
                    }
                }
                else if(elementSel == 1){
                    if(tecla == "arr"){
                        elementSel = 5;
                    }
                    else if(tecla == "der"){
                        elementSel = 2;
                    }
                    else if(tecla == "aba"){
                        elementSel = 3;
                    }
                    else if(tecla == "izq"){
                        elementSel = 0;
                    }
                }
                else if(elementSel == 2){
                    if(tecla == "arr"){
                        elementSel = 5;
                    }
                    else if(tecla == "der"){
                        elementSel = 3;
                    }
                    else if(tecla == "aba"){
                        elementSel = 3;
                    }
                    else if(tecla == "izq"){
                        elementSel = 1;
                    }
                }
                else if(elementSel == 3){
                    if(tecla == "arr"){
                        elementSel = 0;
                    }
                    else if(tecla == "der"){
                        elementSel = 0;
                    }
                    else if(tecla == "aba"){
                        elementSel = 4;
                    }
                    else if(tecla == "izq"){
                        elementSel = 2;
                    }
                }
                else if(elementSel == 4){
                    if(tecla == "arr"){
                        elementSel = 3;
                    }
                    else if(tecla == "der"){
                        elementSel = 0;
                    }
                    else if(tecla == "aba"){
                        elementSel = 5;
                    }
                    else if(tecla == "izq"){
                        elementSel = 2;
                    }
                }
                else if(elementSel == 5){
                    if(tecla == "arr"){
                        elementSel = 4;
                    }
                    else if(tecla == "der"){
                        elementSel = 0;
                    }
                    else if(tecla == "aba"){
                        elementSel = 3;
                    }
                    else if(tecla == "izq"){
                        elementSel = 2;
                    }
                }
            }
        }
        else{
            if(tecla == "izq" || tecla == "der"){
                int temp = submenugrafica->seleccionar_boton();
                if( temp == 0){
                    elementSel = 7;
                }
                else{
                    elementSel = 8;
                }
            }
            else{
                elementSel = 1;
                submenugrafica->btnsel = 1;
                submenugrafica->seleccionar_boton();
                submenugrafica->hide();
            }
        }
        elementoSeleccionado();
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::elementoSeleccionado(){
    try {
        if(cambiagrafi){
            if(elementSel == 0){
                btn_ventilador->setStyleSheet(estiloBotonA);
                btn_grafica->setStyleSheet(estiloBotonI);
                btn_test->setStyleSheet(estiloBotonI);
                seleccionar_grafica();
            }
            else if(elementSel == 1){
                btn_ventilador->setStyleSheet(estiloBotonI);
                btn_grafica->setStyleSheet(estiloBotonA);
                btn_test->setStyleSheet(estiloBotonI);
                seleccionar_grafica();
            }
            else if(elementSel == 2){
                btn_ventilador->setStyleSheet(estiloBotonI);
                btn_grafica->setStyleSheet(estiloBotonI);
                btn_test->setStyleSheet(estiloBotonA);
                seleccionar_grafica();
            }
            else if(3 <= elementSel && elementSel <= 6){
                btn_ventilador->setStyleSheet(estiloBotonI);
                btn_grafica->setStyleSheet(estiloBotonI);
                btn_test->setStyleSheet(estiloBotonI);
                seleccionar_grafica();
            }
            else{
                btn_ventilador->setStyleSheet(estiloBotonI);
                btn_grafica->setStyleSheet(estiloBotonI);
                btn_test->setStyleSheet(estiloBotonI);
                seleccionar_grafica();
            }
        }
        else{
            if(elementSel == 0){
                btn_ventilador->setStyleSheet(estiloBotonA);
                btn_grafica->setStyleSheet(estiloBotonI);
                btn_test->setStyleSheet(estiloBotonI);
                seleccionar_grafica();
            }
            else if(elementSel == 1){
                btn_ventilador->setStyleSheet(estiloBotonI);
                btn_grafica->setStyleSheet(estiloBotonA);
                btn_test->setStyleSheet(estiloBotonI);
                seleccionar_grafica();
            }
            else if(elementSel == 2){
                btn_ventilador->setStyleSheet(estiloBotonI);
                btn_grafica->setStyleSheet(estiloBotonI);
                btn_test->setStyleSheet(estiloBotonA);
                seleccionar_grafica();
            }
            else if(3 <= elementSel && elementSel <= 5){
                btn_ventilador->setStyleSheet(estiloBotonI);
                btn_grafica->setStyleSheet(estiloBotonI);
                btn_test->setStyleSheet(estiloBotonI);
                seleccionar_grafica();
            }
            else{
                btn_ventilador->setStyleSheet(estiloBotonI);
                btn_grafica->setStyleSheet(estiloBotonI);
                btn_test->setStyleSheet(estiloBotonI);
                seleccionar_grafica();
            }
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::muestraAlarmas(){
    try {
        if(lista_alarmas->size() > 0){
            if(contadorMuestraAlarmas < lista_alarmas->size()){
                QString temp = lista_alarmas->at(contadorMuestraAlarmas);
                int tam = temp.size();
                int estado = diccionario_alarma->value(temp.mid(0,tam-10));
                //qDebug() << "muestraAlarmas-estado: " + QString::number(estado);
                //qDebug() << "muestraAlarmas-alarma: " + temp.mid(0,tam-10);
                QString color;
                if(estado == 0){
                    color = "gray";
                }
                else{
                    color = dict_color_muestra_alarma->value(temp.mid(0,tam-10));
                }
                label_info_alarma->setStyleSheet("background-color: " + color + "; color: black;");
                label_info_alarma->setText(lista_alarmas->at(contadorMuestraAlarmas));
                contadorMuestraAlarmas ++;
            }
            else{
                contadorMuestraAlarmas = 0;
                QString temp = lista_alarmas->at(contadorMuestraAlarmas);
                int tam = temp.size();
                int estado = diccionario_alarma->value(temp.mid(0,tam-10));
                //qDebug() << "muestraAlarmas-estado: " + QString::number(estado);
                //qDebug() << "muestraAlarmas-alarma: " + temp.mid(0,tam-10);
                QString color;
                if(estado == 0){
                    color = "gray";
                }
                else{
                    color = dict_color_muestra_alarma->value(temp.mid(0,tam-10));
                }
                label_info_alarma->setStyleSheet("background-color: " + color + "; color: black;");
                label_info_alarma->setText(lista_alarmas->at(contadorMuestraAlarmas));

            }
        }
        else{
            label_info_alarma->setStyleSheet("background-color: black; color: black;");
            label_info_alarma->setText("");
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::eliminar_alarma_de_lista(QString alarma){
    try {
        //ver si esta en la lista
        bool encontrado = false;
        for(int j=0; j < lista_alarmas->size(); j++){
            if(alarma == lista_alarmas->at(j)){
                encontrado = true;
                break;
            }
        }
        if(encontrado){
            int cont = 0;
            int indice_borrar = 0;
            bool borrar = false;
            for(int j=0; j < lista_alarmas->size(); j++){
                if(alarma == lista_alarmas->at(j)){
                    indice_borrar = cont;
                    borrar = true;
                }
                cont++;
            }
            if(borrar){
                qDebug() << "elemento borrado" +  lista_alarmas->at(indice_borrar);
                lista_alarmas->removeAt(indice_borrar);
            }
        }
        //
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::beep(){
    try {
        //int frecuencia, int veces, float tiempo, float pausa
        for(int k = 0; k < beep_veces; k++){
            QProcess::execute(QString("play -v 0.1 -nq -t alsa synth %1 sine %2").arg(QString::number(beep_tiempo,'f',1),QString::number(beep_frecuencia) ));
            QThread::msleep(beep_pausa*1000);
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

QString Monitor::obtener_fecha(){
    try {
        QDateTime dateTime = QDateTime::currentDateTime();
        QString dateTimeString = dateTime.toString("\n hh:mm:ss");
        return dateTimeString;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

bool Monitor::buscar_en_lista(QString alarma){
    try {
        bool encontrado = false;
        for(int j=0; j < lista_alarmas->size(); j++){
            if(lista_alarmas->at(j).contains(alarma)){
                encontrado = true;
                break;
            }
        }
        return encontrado;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return false;
    }
}

void Monitor::agregar_en_lista(QString alarma,int estado){
    try {
        if(! buscar_en_lista(alarma)){
            QString temp = alarma + obtener_fecha();
            lista_alarmas->append(temp);
            diccionario_alarma->insert(alarma, estado);
            contadorMuestraAlarmas = lista_alarmas->indexOf(temp);
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::actualizar_en_lista(QString alarma,int estado){
    try {
        if(buscar_en_lista(alarma)){
            QMap<QString, int>::iterator iter;
            for(iter = diccionario_alarma->begin(); iter != diccionario_alarma->end(); ++iter){
                if(iter.key() == alarma){
                    iter.value() = estado;
                }
            }
            //actualizar la hora de alarma
            int contador = 0;
            int indice = 0;
            for(int j=0; j < lista_alarmas->size(); j++){
                if(lista_alarmas->at(j).contains(alarma)){
                    indice = contador;
                    break;
                }
                contador++;
            }
            QString temp = alarma + obtener_fecha();
            lista_alarmas->replace(indice,temp);
        }
        else{
            qDebug() << "Actualizar en ilsta, no encontrado: " + alarma + "al estado: " + QString::number(estado);
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::borrar_en_lista(QString alarma){
    try {
        //qDebug() << "borrar_en_lista";
        if(buscar_en_lista(alarma)){
            //qDebug() << "borrar_en_lista-esta en la lista";
            int cont = 0;
            int indice_borrar = 0;
            bool borrar = false;
            for(int j=0; j < lista_alarmas->size(); j++){
                //qDebug() << "borrar_en_lista-for: " + lista_alarmas->at(j);
                if(lista_alarmas->at(j).contains(alarma)){
                    indice_borrar = cont;
                    borrar = true;
                    //qDebug() << "borrar_en_lista-borrar indice: " + QString::number(indice_borrar);
                }
                cont++;
            }
            if(borrar){
                //qDebug() << "elemento borrado" +  lista_alarmas->at(indice_borrar);
                lista_alarmas->removeAt(indice_borrar);
            }
            diccionario_alarma->remove(alarma);
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::borrar_alarmas(){
    try {
        consul->agregar_evento("ALARMA", obtener_modo(), "Limpia alarmas");
        //qDebug() << "borrar_alarmas";
        QStringList temp;
        QMap<QString, int>::iterator iter;
        for(iter = diccionario_alarma->begin(); iter != diccionario_alarma->end(); ++iter){
            if(iter.value() == 0){
                temp.append(iter.key());
                //qDebug() << "dicionario_alarma: " + iter.key();
            }
        }
        for(int j=0; j < temp.size(); j++){
            //qDebug() << "borrar_en_lista: " + temp.at(j);
            borrar_en_lista(temp.at(j));
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::borrar_eventos(){
    try {
        //qDebug() << " borrar eventos " ;
        QStringList eventos = consul->obtener_eventos_para_borrar();
        //qDebug() << " borrar eventos, numero: " + QString::number(eventos.size());
        QDate ahora = QDate::currentDate();
        for(int i=0; i < eventos.size(); i++){
            //separar id y fecha de cada evento (elemento de la lista eventos
            QStringList partes = eventos.at(i).split(",");
            //dar formato a la fecha del evento
            QStringList datos_fecha = partes.at(1).split("-");
            QDate fecha_date(datos_fecha.at(0).toInt(),datos_fecha.at(1).toInt(),datos_fecha.at(2).toInt());
            if(fecha_date.daysTo(ahora) > 7){
                //qDebug() << "Borrar evento, id: " + partes.at(0);
                consul->borrar_evento(partes.at(0));
            }
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Monitor::revisar_entra_gases(){
    try {
        //self.entrada_aire, self.entrada_oxigeno, self.nivel_oxigeno,
        int aire = entrada_aire;
        int oxigeno = entrada_oxigeno;
        int nivel_oxi = nivel_oxigeno.toInt();
        float aire_of;
        float oxigeno_of;
        if(tipo_sensor_presion){
            float beta = exp(-1.18e-4 * altura_prog);
            float p_h = 14.7 * beta;
            aire_of = aire - p_h;
            oxigeno_of = oxigeno - p_h;
        }
        else{
            aire_of = aire;
            oxigeno_of = oxigeno;
        }
        if(aire_of < min_entrada_aire){
            if(! buscar_en_lista("P. Aire BAJO")){
                agregar_en_lista("P. Aire BAJO", 1);
                consul->agregar_evento("ALARMA", obtener_modo(), "Presión baja aire ACTIVADO - " + QString::number(aire_of,'f',1));
                if(! estadoAlarmaGases){
                    estadoAlarmaGases = true;
                    alarmaControl->iniciaAlarma(alarmaControl->GASES);
                }
            }
            else{
                if(diccionario_alarma->value("P. Aire BAJO") == 0){
                    actualizar_en_lista("P. Aire BAJO", 1);
                    if(! estadoAlarmaGases){
                        estadoAlarmaGases = true;
                        alarmaControl->iniciaAlarma(alarmaControl->GASES);
                    }
                }
            }
            //revisar el otro extremo
            if(buscar_en_lista("P. Aire ALTO")){
                if(diccionario_alarma->value("P. Aire ALTO") == 1){
                    actualizar_en_lista("P. Aire ALTO", 0);
                    consul->agregar_evento("ALARMA", obtener_modo(), "Presión alta aire DESACTIVADO");
                    if(estadoAlarmaGases){
                        estadoAlarmaGases = false;
                        alarmaControl->detenAlarma(alarmaControl->GASES);
                    }
                }
            }
        }
        else if(aire_of > max_entrada_aire){
            if(! buscar_en_lista("P. Aire ALTO")){
                agregar_en_lista("P. Aire ALTO", 1);
                consul->agregar_evento("ALARMA", obtener_modo(), "Presión alta aire ACTIVADO - " + QString::number(aire_of,'f',1));
                if(! estadoAlarmaGases){
                    estadoAlarmaGases = true;
                    alarmaControl->iniciaAlarma(alarmaControl->GASES);
                }
            }
            else{
                if(diccionario_alarma->value("P. Aire ALTO") == 0){
                    actualizar_en_lista("P. Aire ALTO", 1);
                    if(! estadoAlarmaGases){
                        estadoAlarmaGases = true;
                        alarmaControl->iniciaAlarma(alarmaControl->GASES);
                    }
                }
            }
            //revisar el otro extremo
            if(buscar_en_lista("P. Aire BAJO")){
                if(diccionario_alarma->value("P. Aire BAJO") == 1){
                    actualizar_en_lista("P. Aire BAJO", 0);
                    consul->agregar_evento("ALARMA", obtener_modo(), "Presión baja aire DESACTIVADO");
                    if(estadoAlarmaGases){
                        estadoAlarmaGases = false;
                        alarmaControl->detenAlarma(alarmaControl->GASES);
                    }
                }
            }
        }
        else{
            if(buscar_en_lista("P. Aire BAJO")){
                if(diccionario_alarma->value("P. Aire BAJO") == 1){
                    actualizar_en_lista("P. Aire BAJO", 0);
                    consul->agregar_evento("ALARMA", obtener_modo(), "Presión baja aire DESACTIVADO");
                    if(estadoAlarmaGases){
                        estadoAlarmaGases = false;
                        alarmaControl->detenAlarma(alarmaControl->GASES);
                    }
                }
            }
            if(buscar_en_lista("P. Aire ALTO")){
                if(diccionario_alarma->value("P. Aire ALTO") == 1){
                    actualizar_en_lista("P. Aire ALTO", 0);
                    consul->agregar_evento("ALARMA", obtener_modo(), "Presión alta aire DESACTIVADO");
                    if(estadoAlarmaGases){
                        estadoAlarmaGases = false;
                        alarmaControl->detenAlarma(alarmaControl->GASES);
                    }
                }
            }
        }
        ///////
        if(oxigeno_of < min_entrada_oxi){
            if(! buscar_en_lista("P. O2 BAJO")){
                agregar_en_lista("P. O2 BAJO", 1);
                consul->agregar_evento("ALARMA", obtener_modo(), "Presión baja oxigeno ACTIVADO - " + QString::number(oxigeno_of,'f',1));
                if(! estadoAlarmaGases){
                    estadoAlarmaGases = true;
                    alarmaControl->iniciaAlarma(alarmaControl->GASES);
                }
            }
            else{
                if(diccionario_alarma->value("P. O2 BAJO") == 0){
                    actualizar_en_lista("P. O2 BAJO", 1);
                    if(! estadoAlarmaGases){
                        estadoAlarmaGases = true;
                        alarmaControl->iniciaAlarma(alarmaControl->GASES);
                    }
                }
            }
            //revisar otro extremo
            if(buscar_en_lista("P. O2 ALTO")){
                if(diccionario_alarma->value("P. O2 ALTO") == 1){
                    actualizar_en_lista("P. O2 ALTO", 0);
                    consul->agregar_evento("ALARMA", obtener_modo(), "Presión alta oxigeno DESACTIVADO");
                    if(estadoAlarmaGases){
                        estadoAlarmaGases = false;
                        alarmaControl->detenAlarma(alarmaControl->GASES);
                    }
                }
            }
        }
        else if(oxigeno_of > max_entrada_oxi){
            if(! buscar_en_lista("P. O2 ALTO")){
                agregar_en_lista("P. O2 ALTO", 1);
                consul->agregar_evento("ALARMA", obtener_modo(), "Presión alta oxigeno ACTIVADO - " + QString::number(oxigeno_of,'f',1));
                if(! estadoAlarmaGases){
                    estadoAlarmaGases = true;
                    alarmaControl->iniciaAlarma(alarmaControl->GASES);
                }
            }
            else{
                if(diccionario_alarma->value("P. O2 ALTO") == 0){
                    actualizar_en_lista("P. O2 ALTO", 1);
                    if(! estadoAlarmaGases){
                        estadoAlarmaGases = true;
                        alarmaControl->iniciaAlarma(alarmaControl->GASES);
                    }
                }
            }
            //revisar otro extremo
            if(buscar_en_lista("P. O2 BAJO")){
                if(diccionario_alarma->value("P. O2 BAJO") == 1){
                    actualizar_en_lista("P. O2 BAJO", 0);
                    consul->agregar_evento("ALARMA", obtener_modo(), "Presión baja oxigeno DESACTIVADO");
                    if(estadoAlarmaGases){
                        estadoAlarmaGases = false;
                        alarmaControl->detenAlarma(alarmaControl->GASES);
                    }
                }
            }
        }
        else{
            if(buscar_en_lista("P. O2 BAJO")){
                if(diccionario_alarma->value("P. O2 BAJO") == 1){
                    actualizar_en_lista("P. O2 BAJO", 0);
                    consul->agregar_evento("ALARMA", obtener_modo(), "Presión baja oxigeno DESACTIVADO");
                    if(estadoAlarmaGases){
                        estadoAlarmaGases = false;
                        alarmaControl->detenAlarma(alarmaControl->GASES);
                    }
                }
            }
            if(buscar_en_lista("P. O2 ALTO")){
                if(diccionario_alarma->value("P. O2 ALTO") == 1){
                    actualizar_en_lista("P. O2 ALTO", 0);
                    consul->agregar_evento("ALARMA", obtener_modo(), "Presión alta oxigeno DESACTIVADO");
                    if(estadoAlarmaGases){
                        estadoAlarmaGases = false;
                        alarmaControl->detenAlarma(alarmaControl->GASES);
                    }
                }
            }
        }
        ///////
        if(listo_medir_fio2 && estadoVentilador){
            float fio2 = tramaVentilador.mid(29,3).toFloat();
            if(nivel_oxi < (fio2 -5)){
                if(! buscar_en_lista("FIO2 BAJO")){
                    agregar_en_lista("FIO2 BAJO", 1);
                    consul->agregar_evento("ALARMA", obtener_modo(), "FIO2 ACTIVADO - " + QString::number(nivel_oxi,'f',1) + ":" + QString::number(fio2 - 5));
                    if(! estadoAlarmaGases){
                        estadoAlarmaGases = true;
                        alarmaControl->iniciaAlarma(alarmaControl->GASES);
                    }
                }
                else{
                    if(diccionario_alarma->value("FIO2 BAJO") == 0){
                        actualizar_en_lista("FIO2 BAJO", 1);
                        if(! estadoAlarmaGases){
                            estadoAlarmaGases = true;
                            alarmaControl->iniciaAlarma(alarmaControl->GASES);
                        }
                    }
                }
                //revisar otro extremo
                if(buscar_en_lista("FIO2 ALTO")){
                    if(diccionario_alarma->value("FIO2 ALTO") == 1){
                        actualizar_en_lista("FIO2 ALTO", 0);
                        consul->agregar_evento("ALARMA", obtener_modo(), "FIO2 ALTO DESACTIVADO");
                        if(estadoAlarmaGases){
                            estadoAlarmaGases = false;
                            alarmaControl->detenAlarma(alarmaControl->GASES);
                        }
                    }
                }
            }
            else if(nivel_oxi > (fio2 + 5)){
                if(! buscar_en_lista("FIO2 ALTO")){
                    agregar_en_lista("FIO2 ALTO", 1);
                    consul->agregar_evento("ALARMA", obtener_modo(), "FIO2 ACTIVADO - " + QString::number(nivel_oxi,'f',1) + ":" + QString::number(fio2 - 5));
                    if(! estadoAlarmaGases){
                        estadoAlarmaGases = true;
                        alarmaControl->iniciaAlarma(alarmaControl->GASES);
                    }
                }
                else{
                    if(diccionario_alarma->value("FIO2 ALTO") == 0){
                        actualizar_en_lista("FIO2 ALTO", 1);
                        if(! estadoAlarmaGases){
                            estadoAlarmaGases = true;
                            alarmaControl->iniciaAlarma(alarmaControl->GASES);
                        }
                    }
                }
                //revisar otro extremo
                if(buscar_en_lista("FIO2 BAJO")){
                    if(diccionario_alarma->value("FIO2 BAJO") == 1){
                        actualizar_en_lista("FIO2 BAJO", 0);
                        consul->agregar_evento("ALARMA", obtener_modo(), "FIO2 BAJO DESACTIVADO");
                        if(estadoAlarmaGases){
                            estadoAlarmaGases = false;
                            alarmaControl->detenAlarma(alarmaControl->GASES);
                        }
                    }
                }
            }
            else{
                if(buscar_en_lista("FIO2 ALTO")){
                    if(diccionario_alarma->value("FIO2 ALTO") == 1){
                        actualizar_en_lista("FIO2 ALTO", 0);
                        consul->agregar_evento("ALARMA", obtener_modo(), "FIO2 ALTO DESACTIVADO");
                        if(estadoAlarmaGases){
                            estadoAlarmaGases = false;
                            alarmaControl->detenAlarma(alarmaControl->GASES);
                        }
                    }
                }
                if(buscar_en_lista("FIO2 BAJO")){
                    if(diccionario_alarma->value("FIO2 BAJO") == 1){
                        actualizar_en_lista("FIO2 BAJO", 0);
                        consul->agregar_evento("ALARMA", obtener_modo(), "FIO2 BAJO DESACTIVADO");
                        if(estadoAlarmaGases){
                            estadoAlarmaGases = false;
                            alarmaControl->detenAlarma(alarmaControl->GASES);
                        }
                    }
                }
            }
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

QString Monitor::obtener_modo(){
    try {
        if(modoSel == 0){
            return "PCMV";
        }
        else if(modoSel == 1){
            return "VCMV";
        }
        else if(modoSel == 2){
            return "PSIMV";
        }
        else if(modoSel == 3){
            return "VSIMV";
        }
        else if(modoSel == 4){
            return "PCPAP";
        }
        else if(modoSel == 5){
            return "VCPAP";
        }
        else{
            return "";
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}
