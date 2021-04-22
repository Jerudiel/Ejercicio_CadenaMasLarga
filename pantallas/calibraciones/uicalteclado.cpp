#include "uicalteclado.h"

UiCalTeclado::UiCalTeclado(QWidget *parent, Monitor *monitor) : QWidget(parent)
{
    try {
        QString ruta = QDir::currentPath();

        setStyleSheet("QLineEdit{ background: gray;} QPushButton{color: white;}");
        this->monitor = monitor;
        font = new QFont;
        font->setPointSize(12);
        font->setBold(true);
        font->setWeight(75);

        styleButton = "QPushButton:pressed { border: 4px solid rgb(255,112,61); background-color: gray; border-radius: 5px; color: black;}"
                         "QPushButton { border: 2px solid grey; background-color: grey; border-radius: 5px; color: black;}";

        btnOk = new QPushButton(this);
        btnOk->setGeometry(QRect(30,50, 60, 60));
        btnOk->setObjectName("btnOk");
        btnOk->setStyleSheet(styleButton);
        QPixmap pixmap(ruta+"/graficos/teclado/ok.png");
        QIcon btnOkIcon(pixmap);
        btnOk->setIcon(btnOkIcon);
        btnOk->setIconSize(QSize(50,50));
        connect(btnOk, &QPushButton::clicked, [=](){
            emit get_config_key(0);
        });

        btnCan = new QPushButton(this);
        btnCan->setGeometry(QRect(100,50, 60, 60));
        btnCan->setObjectName("btnCan");
        //btnCan->setText("X");
        btnCan->setStyleSheet(styleButton);
        QPixmap pixmap2(ruta+"/graficos/teclado/can.png");
        QIcon btnCanIcon(pixmap2);
        btnCan->setIcon(btnCanIcon);
        btnCan->setIconSize(QSize(50,50));
        connect(btnCan, &QPushButton::clicked, [=](){
            emit get_config_key(2);
        });

        btnPlay = new QPushButton(this);
        btnPlay->setGeometry(QRect(170,50, 60, 60));
        btnPlay->setObjectName("btnPlay");
        //btnIniDet->setText("Play");
        btnPlay->setStyleSheet(styleButton);
        QPixmap pixmap3(ruta+"/graficos/teclado/playpause.png");
        QIcon btnIniDetIcon(pixmap3);
        btnPlay->setIcon(btnIniDetIcon);
        btnPlay->setIconSize(QSize(50,50));
        connect(btnPlay, &QPushButton::clicked, [=](){
            emit get_config_key(4);
        });

        btnSetAlarm = new QPushButton(this);
        btnSetAlarm->setGeometry(QRect(240,50, 60, 60));
        btnSetAlarm->setObjectName("btnSetAlarm");
        //btnLimpAla->setText("L A");
        btnSetAlarm->setStyleSheet(styleButton);
        QPixmap pixmap4(ruta+"/graficos/teclado/alarmlimp.png");
        QIcon btnLimpAlaIcon(pixmap4);
        btnSetAlarm->setIcon(btnLimpAlaIcon);
        btnSetAlarm->setIconSize(QSize(50,50));
        connect(btnSetAlarm, &QPushButton::clicked, [=](){
            emit get_config_key(5);
        });

        //
        btnMon = new QPushButton(this);
        btnMon->setGeometry(QRect(30,120, 60, 60));
        btnMon->setObjectName("btnMon");
        //btnPrin->setText("M");
        btnMon->setStyleSheet(styleButton);
        QPixmap pixmap5(ruta+"/graficos/teclado/home.png");
        QIcon btnPrinIcon(pixmap5);
        btnMon->setIcon(btnPrinIcon);
        btnMon->setIconSize(QSize(50,50));
        connect(btnMon, &QPushButton::clicked, [=](){
            emit get_config_key(1);
        });

        btnCon = new QPushButton(this);
        btnCon->setGeometry(QRect(100,120, 60, 60));
        btnCon->setObjectName("btnCon");
        //btnConfig->setText("C");
        btnCon->setStyleSheet(styleButton);
        QPixmap pixmap6(ruta+"/graficos/teclado/config.png");
        QIcon btnConfigIcon(pixmap6);
        btnCon->setIcon(btnConfigIcon);
        btnCon->setIconSize(QSize(50,50));
        connect(btnCon, &QPushButton::clicked, [=](){
            emit get_config_key(3);
        });

        btnAlarm = new QPushButton(this);
        btnAlarm->setGeometry(QRect(170,120, 60, 60));
        btnAlarm->setObjectName("btnAlarm");
        //btnAla->setText("A");
        btnAlarm->setStyleSheet(styleButton);
        QPixmap pixmap7(ruta+"/graficos/teclado/ala.png");
        QIcon btnAlaIcon(pixmap7);
        btnAlarm->setIcon(btnAlaIcon);
        btnAlarm->setIconSize(QSize(50,50));
        connect(btnAlarm, &QPushButton::clicked, [=](){
            emit get_config_key(6);
        });

        //
        btnLeft = new QPushButton(this);
        btnLeft->setGeometry(QRect(50,260, 60, 60));
        btnLeft->setObjectName("btnLeft");
        //btnIzq->setText("<-");
        btnLeft->setStyleSheet(styleButton);
        QPixmap pixmap8(ruta+"/graficos/teclado/izq.png");
        QIcon btnIzqIcon(pixmap8);
        btnLeft->setIcon(btnIzqIcon);
        btnLeft->setIconSize(QSize(50,50));
        connect(btnLeft, &QPushButton::clicked, [=](){
            emit get_config_key(9);
        });

        btnUp = new QPushButton(this);
        btnUp->setGeometry(QRect(120,190, 60, 60));
        btnUp->setObjectName("btnUp");
        //btnArr->setText("^");
        btnUp->setStyleSheet(styleButton);
        QPixmap pixmap9(ruta+"/graficos/teclado/arr.png");
        QIcon btnArrIcon(pixmap9);
        btnUp->setIcon(btnArrIcon);
        btnUp->setIconSize(QSize(50,50));
        connect(btnUp, &QPushButton::clicked, [=](){
            emit get_config_key(8);
        });

        btnRight = new QPushButton(this);
        btnRight->setGeometry(QRect(190,260, 60, 60));
        btnRight->setObjectName("btnRight");
        //btnDer->setText("->");
        btnRight->setStyleSheet(styleButton);
        QPixmap pixmap10(ruta+"/graficos/teclado/der.png");
        QIcon btnDerIcon(pixmap10);
        btnRight->setIcon(btnDerIcon);
        btnRight->setIconSize(QSize(50,50));
        connect(btnRight, &QPushButton::clicked, [=](){
            emit get_config_key(10);
        });

        btnDown = new QPushButton(this);
        btnDown->setGeometry(QRect(120,330, 60, 60));
        btnDown->setObjectName("btnDown");
        //btnAba->setText("v");
        btnDown->setStyleSheet(styleButton);
        QPixmap pixmap11(ruta+"/graficos/teclado/aba.png");
        QIcon btnAbaIcon(pixmap11);
        btnDown->setIcon(btnAbaIcon);
        btnDown->setIconSize(QSize(50,50));
        connect(btnDown, &QPushButton::clicked, [=](){
            emit get_config_key(11);
        });

        //
        btnDesAlarm = new QPushButton(this);
        btnDesAlarm->setGeometry(QRect(240,190, 60, 60));
        btnDesAlarm->setObjectName("btnDesAlarm");
        //btnDesAla->setText("D A");
        btnDesAlarm->setStyleSheet(styleButton);
        QPixmap pixmap12(ruta+"/graficos/teclado/alarmdes.png");
        QIcon btnDesAlaIcon(pixmap12);
        btnDesAlarm->setIcon(btnDesAlaIcon);
        btnDesAlarm->setIconSize(QSize(50,50));
        connect(btnDesAlarm, &QPushButton::clicked, [=](){
            emit get_config_key(7);
        });

        ////
        btnOut = new QPushButton(this);
        btnOut->setGeometry(QRect(900,50, 60, 60));
        btnOut->setObjectName("btnOut");
        btnOut->setStyleSheet("QPushButton:pressed { border: 4px solid gray; background-color: gray; border-radius: 5px; color: black;}"
                                "QPushButton { border: 4px solid rgb(255,112,61); background-color: rgb(255,112,61); border-radius: 5px; color: black;}");
        QPixmap pixmap13(ruta+"/graficos/teclado/can.png");
        QIcon btnOutIcon(pixmap13);
        btnOut->setIcon(btnOutIcon);
        btnOut->setIconSize(QSize(50,50));
        connect(btnOut, &QPushButton::clicked, this, &UiCalTeclado::out);

        switchMode = new MySwitch(this, "Global", "Indiv");
        switchMode->ponerGeometry(QRect(750, 50, 150, 50));
        switchMode->ponerChecked(false);
        connect(switchMode, &QPushButton::clicked , this, &UiCalTeclado::set_mode);

        lblPush = new QLabel(this);
        lblPush->setGeometry(QRect(350, 100, 100, 30));
        lblPush->setFont(*font);
        lblPush->setStyleSheet("color: white;");
        lblPush->setAlignment(Qt::AlignCenter);
        lblPush->setObjectName("lblPush");
        lblPush->setText("Presionar: ");

        lEPush = new QLineEdit(this);
        lEPush->setGeometry(QRect(460, 100, 100, 30));
        lEPush->setFont(*font);
        lEPush->setAlignment(Qt::AlignCenter);
        lEPush->setObjectName("lEPush");

        lblRelease = new QLabel(this);
        lblRelease->setGeometry(QRect(350, 150, 100, 30));
        lblRelease->setFont(*font);
        lblRelease->setStyleSheet("color: white;");
        lblRelease->setAlignment(Qt::AlignCenter);
        lblRelease->setObjectName("lblRelease");
        lblRelease->setText("Soltar: ");

        lERelease = new QLineEdit(this);
        lERelease->setGeometry(QRect(460, 150, 100, 30));
        lERelease->setFont(*font);
        lERelease->setAlignment(Qt::AlignCenter);
        lERelease->setObjectName("lERelease");

        btnApply= new QPushButton(this);
        btnApply->setGeometry(QRect(375, 200, 150, 60));
        btnApply->setFont(*font);
        btnApply->setObjectName("btnOut");
        btnApply->setStyleSheet(styleButton);
        btnApply->setText("APLICAR");
        connect(btnApply, &QPushButton::clicked, this, &UiCalTeclado::apply);

        lblDebug = new QLabel(this);
        lblDebug->setGeometry(QRect(350, 300, 250, 60));
        lblDebug->setFont(*font);
        lblDebug->setStyleSheet("color: white;");
        lblDebug->setAlignment(Qt::AlignCenter);
        lblDebug->setObjectName("lblDebug");
        lblDebug->setText("Debug");

        timerConfigKey = new QTimer;
        timerConfigKey->setInterval(500);
        connect(timerConfigKey, SIGNAL(timeout()), this, SLOT(check_config_key()));
        contConfigKey = 0;

        timerGetMode = new QTimer;
        timerGetMode->setInterval(500);
        connect(timerGetMode, SIGNAL(timeout()), this, SLOT(check_mode()));
        contGetMode = 0;

        advert = "";
        tempAdvert = "";

        timerMessage = new QTimer;
        timerMessage->setSingleShot(true);
        connect(timerMessage, SIGNAL(timeout()), this, SLOT(eraseMessage()));

    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void UiCalTeclado::paintEvent(QPaintEvent* /*event*/)
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

/*void UiCalTeclado::set_config_key(){
    try {

    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}*/

void UiCalTeclado::get_mode(){
    try {
        //pedir modo trama: gmod\n
        monitor->isReadyModeKeyboard = false;
        monitor->isWaitingMode = true;
        monitor->get_mode_keyboard();
        //aqui debe iniciar el timer mode
        advert = "Obteniendo modo";
        tempAdvert = advert;
        lblDebug->setText(advert);
        timerGetMode->start();
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiCalTeclado::set_mode(){
    try {

    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiCalTeclado::get_config_key(int element){
    try {

    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiCalTeclado::check_config_key(){
    try {

    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiCalTeclado::check_mode(){
    try {
        if(!monitor->isReadyModeKeyboard){
            if(contGetMode < 15){
                if(contGetMode % 3 == 0){
                    tempAdvert = advert;
                    lblDebug->setText(advert);
                }
                else{
                    tempAdvert.append(".");
                    lblDebug->setText(tempAdvert);
                }
                contGetMode++;
            }
            else{
                //no llego el comando
                contGetMode = 0;
                if(timerGetMode->isActive()){
                    timerGetMode->stop();
                }
                show_message("Problema al cargar el modo");
            }
        }
        else{
            //se recibio respuesta, cehcarla y detener el timer
            if(timerGetMode->isActive()){
                timerGetMode->stop();
            }
            contGetMode = 0;
            //activar funcion que muestra el mensaje y lo borra 3 segundos después
            if(monitor->valueModeKeyboard == 0){
                switchMode->ponerChecked(false);
            }
            else{
                switchMode->ponerChecked(true);
            }
            show_message("Modo cargado");
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiCalTeclado::out(){
    try {

    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiCalTeclado::apply(){
    try {

    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiCalTeclado::show_message(QString message){
    try {
        lblDebug->setText(message);
        timerMessage->start(3000);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiCalTeclado::eraseMessage(){
    try {
        lblDebug->setText("");
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}
