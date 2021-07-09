#include "uiinfosistema.h"

UiInfoSistema::UiInfoSistema(QWidget *parent, Monitor *monitor) : QWidget(parent)
{
    try {
        setStyleSheet("color: white;");
        this->monitor = monitor;
        fuente = new QFont;
        fuente->setPointSize(12);
        fuente->setBold(true);
        fuente->setWeight(75);

        labelVersionTeclado = new QLabel(this);
        labelVersionTeclado->setGeometry(QRect(40, 20, 350, 50));
        labelVersionTeclado->setFont(*fuente);
        labelVersionTeclado->setStyleSheet("color: white;");
        labelVersionTeclado->setAlignment(Qt::AlignCenter);
        labelVersionTeclado->setObjectName("labelVersionTeclado");

        labelVersionSensores = new QLabel(this);
        labelVersionSensores->setGeometry(QRect(40, 100, 350, 50));
        labelVersionSensores->setFont(*fuente);
        labelVersionSensores->setAlignment(Qt::AlignCenter);
        labelVersionSensores->setObjectName("labelVersionSensores");

        labelAlarmasSensores = new QLabel(this);
        labelAlarmasSensores->setGeometry(QRect(400, 100, 350, 50));
        labelAlarmasSensores->setFont(*fuente);
        labelAlarmasSensores->setAlignment(Qt::AlignCenter);
        labelAlarmasSensores->setObjectName("labelAlarmasSensores");

        labelVersionVentilador = new QLabel(this);
        labelVersionVentilador->setGeometry(QRect(40, 180, 350, 50));
        labelVersionVentilador->setFont(*fuente);
        labelVersionVentilador->setAlignment(Qt::AlignCenter);
        labelVersionVentilador->setObjectName("labelVersionVentilador");

        labelAlarmasVentilador = new QLabel(this);
        labelAlarmasVentilador->setGeometry(QRect(400, 180, 350, 50));
        labelAlarmasVentilador->setFont(*fuente);
        labelAlarmasVentilador->setAlignment(Qt::AlignCenter);
        labelAlarmasVentilador->setObjectName("labelAlarmasVentilador");


        labelEntradaAire = new QLabel(this);
        labelEntradaAire->setGeometry(QRect(400, 230, 350, 50));
        labelEntradaAire->setFont(*fuente);
        labelEntradaAire->setAlignment(Qt::AlignCenter);
        labelEntradaAire->setObjectName("labelEntradaAire");

        labelEntradaOxigeno = new QLabel(this);
        labelEntradaOxigeno->setGeometry(QRect(400, 280, 350, 50));
        labelEntradaOxigeno->setFont(*fuente);
        labelEntradaOxigeno->setAlignment(Qt::AlignCenter);
        labelEntradaOxigeno->setObjectName("labelEntradaOxigeno");

        labelSenPresion = new QLabel(this);
        labelSenPresion->setGeometry(QRect(400, 330, 350, 50));
        labelSenPresion->setFont(*fuente);
        labelSenPresion->setAlignment(Qt::AlignCenter);
        labelSenPresion->setObjectName("labelSenPresion");


        labelVersionCPU = new QLabel(this);
        labelVersionCPU->setGeometry(QRect(40, 260, 350, 50));
        labelVersionCPU->setFont(*fuente);
        labelVersionCPU->setAlignment(Qt::AlignCenter);
        labelVersionCPU->setObjectName("labelVersionCPU");

        labelNumeroSerie = new QLabel(this);
        labelNumeroSerie->setGeometry(QRect(40, 340, 350, 50));
        labelNumeroSerie->setFont(*fuente);
        labelNumeroSerie->setAlignment(Qt::AlignCenter);
        labelNumeroSerie->setObjectName("labelNumeroSerie");


        labelNumeroReinicios = new QLabel(this);
        labelNumeroReinicios->setGeometry(QRect(400, 20, 350, 50));
        labelNumeroReinicios->setFont(*fuente);
        labelNumeroReinicios->setAlignment(Qt::AlignCenter);
        labelNumeroReinicios->setObjectName("labelNumeroReinicios");

        tempMon = new Temperatura(this, monitor);

        //self.tempMon = Temperatura(self, self.Monitor, self.logger)
        switchGiro = new MySwitch(this, "LEFT", "RIGHT");
        switchGiro->ponerGeometry(QRect(800, 100, 150, 50));
        switchGiro->ponerChecked(true);
        //connect(switchGiro, SLOT(pressed()), this, SIGNAL(cambiarSentidoGiro()));
        connect(switchGiro, &QPushButton::clicked , this, &UiInfoSistema::cambiarSentidoGiro);

        switchSenPre = new MySwitch(this, "ABS", "REL");
        switchSenPre->ponerGeometry(QRect(800, 200, 150, 50));
        switchSenPre->ponerChecked(false);
        //connect(switchSenPre, SLOT(pressed()), this, SIGNAL(cambiarSenPre()));
        connect(switchSenPre, &QPushButton::clicked , this, &UiInfoSistema::cambiarSenPre);

        timerActualiza = new QTimer;
        timerActualiza->setInterval(5000);
        //connect(timerActualiza, SLOT(timeout()), this, SIGNAL(actualizaValores()));
        connect(timerActualiza, &QTimer::timeout , this, &UiInfoSistema::actualizaValores);
        timerActualiza->start();

        retranslateUi();
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiInfoSistema::paintEvent(QPaintEvent* /*event*/)
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

void UiInfoSistema::retranslateUi(){
    try {
        labelVersionTeclado->setText("Version teclado: ");
        labelVersionSensores->setText("Version sensores: ");
        labelVersionVentilador->setText("Version ventilador: ");
        labelVersionCPU->setText("Version CPU: ");
        labelNumeroReinicios->setText("Reinicios de aplicacion: ");
        labelAlarmasSensores->setText("Al sen act: ");
        labelAlarmasVentilador->setText("Al vent act: ");
        labelEntradaAire->setText("Entrada aire:  psi");
        labelEntradaOxigeno->setText("Entrada oxigeno:  psi");
        labelSenPresion->setText("Sensor presión: cmH2O");
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiInfoSistema::cambiarSentidoGiro(){
    try {
        if(switchGiro->estaChecked()){
            monitor->consul->cambiar_sentido_giro("1");
        }
        else{
            monitor->consul->cambiar_sentido_giro("0");
        }
        QString temp = monitor->consul->leer_sentido_giro();
        if(temp[2] == "0"){
            monitor->sentido_giro = false;
        }
        else{
            monitor->sentido_giro = true;
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiInfoSistema::cambiarSenPre(){
    try {
        if(switchSenPre->estaChecked()){
            monitor->consul->cambiar_tipo_sensor("1");
            //qDebug() << "cambiarSenPre - checked: 1";
        }
        else{
            monitor->consul->cambiar_tipo_sensor("0");
            //qDebug() << "cambiarSenPre - checked: 0";
        }
        QString temp = monitor->consul->leer_tipo_sensor();
        //qDebug() << "cambiarSenPre - temp: " + temp;
        if(temp[2] == "0"){
            monitor->tipo_sensor_presion = false;
        }
        else{
            monitor->tipo_sensor_presion = true;
        }

    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiInfoSistema::cargarVersiones(){
    try {
        labelVersionVentilador->setText("Version ventilador: " + monitor->versionVentilador);
        labelVersionSensores->setText("Version sensores: " + monitor->versionSenPresion);
        labelVersionTeclado->setText("Version teclado: " + monitor->versionTeclado);
        labelVersionCPU->setText("Version CPU: " + monitor->versionPi);
        if(monitor->estadoAlarmasVentilador == "0"){
            labelAlarmasVentilador->setText("Al vent act: Ninguna");
        }
        else if(monitor->estadoAlarmasVentilador == "1"){
            labelAlarmasVentilador->setText("Al vent act: Sensores");
        }
        else if(monitor->estadoAlarmasVentilador == "2"){
            labelAlarmasVentilador->setText("Al vent act: CPU");
        }
        else if(monitor->estadoAlarmasVentilador == "3"){
            labelAlarmasVentilador->setText("Al vent act: Todas");
        }

        if(monitor->estadoAlarmasSensores == "0"){
            labelAlarmasVentilador->setText("Al sen act: Ninguna");
        }
        else if(monitor->estadoAlarmasSensores == "1"){
            labelAlarmasVentilador->setText("Al sen act: Ventilador");
        }
        else if(monitor->estadoAlarmasSensores == "2"){
            labelAlarmasVentilador->setText("Al sen act: CPU");
        }
        else if(monitor->estadoAlarmasSensores == "3"){
            labelAlarmasVentilador->setText("Al sen act: Todas");
        }

        if(monitor->sentido_giro){
            switchGiro->ponerChecked(true);
        }
        else{
            switchGiro->ponerChecked(false);
        }
        switchGiro->actualizar();

        if(monitor->tipo_sensor_presion){
            switchSenPre->ponerChecked(true);
        }
        else{
            switchSenPre->ponerChecked(false);
        }
        switchSenPre->actualizar();
        //numero de serie
        QString numserie = monitor->consul->numero_serie();
        labelNumeroSerie->setText(numserie);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiInfoSistema::actualizaValores(){
    try {
        //qDebug() << "Entra a actualizaValores" ;
        float aire_of = 0;
        float oxigeno_of = 0;
        if(monitor->tipo_sensor_presion){
            float beta = exp(-1.18e-4 * monitor->altura_prog);
            float p_h = 14.7 * beta;
            aire_of = monitor->entrada_aire - p_h;
            oxigeno_of = monitor->entrada_oxigeno - p_h;
        }
        else{
            aire_of = monitor->entrada_aire;
            oxigeno_of = monitor->entrada_oxigeno;
        }
        labelEntradaAire->setText("Entrada aire: " + QString::number(aire_of,'f',2) + " psi");
        labelEntradaOxigeno->setText("Entrada oxigeno: " + QString::number(oxigeno_of,'f',2) + " psi");
        labelSenPresion->setText("Sensor presión: " + QString::number(monitor->sensor_presion_c) + " cmH2O");
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

