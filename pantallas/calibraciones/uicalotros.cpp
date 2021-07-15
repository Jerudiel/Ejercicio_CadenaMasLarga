#include "uicalotros.h"

UiCalOtros::UiCalOtros(QWidget *parent, Monitor *monitor) : QWidget(parent)
{
    try {
        setStyleSheet("QLineEdit{ background: gray;} QPushButton{color: white;}");
        this->monitor = monitor;
        fuente = new QFont;
        fuente->setPointSize(12);
        fuente->setBold(true);
        fuente->setWeight(75);

        lblAltura = new QLabel(this);
        lblAltura->setGeometry(QRect(10, 20, 100, 30));
        lblAltura->setFont(*fuente);
        lblAltura->setStyleSheet("color: white;");
        lblAltura->setAlignment(Qt::AlignCenter);
        lblAltura->setObjectName("lblAltura");

        lEAltura = new QLineEdit(this);
        lEAltura->setGeometry(QRect(150, 20, 100, 30));
        lEAltura->setFont(*fuente);
        lEAltura->setAlignment(Qt::AlignCenter);
        lEAltura->setObjectName("lEAltura");

        lblPresionar = new QLabel(this);
        lblPresionar->setGeometry(QRect(340, 20, 100, 30));
        lblPresionar->setFont(*fuente);
        lblPresionar->setStyleSheet("color: white;");
        lblPresionar->setAlignment(Qt::AlignCenter);
        lblPresionar->setObjectName("lblPresionar");

        lEPresionar = new QLineEdit(this);
        lEPresionar->setGeometry(QRect(450, 20, 100, 30));
        lEPresionar->setFont(*fuente);
        lEPresionar->setAlignment(Qt::AlignCenter);
        lEPresionar->setObjectName("lEPresionar");

        lblSoltar = new QLabel(this);
        lblSoltar->setGeometry(QRect(340, 70, 100, 30));
        lblSoltar->setFont(*fuente);
        lblSoltar->setStyleSheet("color: white;");
        lblSoltar->setAlignment(Qt::AlignCenter);
        lblSoltar->setObjectName("lblSoltar");

        lESoltar = new QLineEdit(this);
        lESoltar->setGeometry(QRect(450, 70, 100, 30));
        lESoltar->setFont(*fuente);
        lESoltar->setAlignment(Qt::AlignCenter);
        lESoltar->setObjectName("lESoltar");

        lblPorceCambio = new QLabel(this);
        lblPorceCambio->setGeometry(QRect(650, 20, 100, 30));
        lblPorceCambio->setFont(*fuente);
        lblPorceCambio->setStyleSheet("color: white;");
        lblPorceCambio->setAlignment(Qt::AlignCenter);
        lblPorceCambio->setObjectName("lblPorceCambio");

        lEPorceCambio = new QLineEdit(this);
        lEPorceCambio->setGeometry(QRect(760, 20, 100, 30));
        lEPorceCambio->setFont(*fuente);
        lEPorceCambio->setAlignment(Qt::AlignCenter);
        lEPorceCambio->setObjectName("lEPorceCambio");

        //

        lblLsAire = new QLabel(this);
        lblLsAire->setGeometry(QRect(650, 70, 100, 30));
        lblLsAire->setFont(*fuente);
        lblLsAire->setStyleSheet("color: white;");
        lblLsAire->setAlignment(Qt::AlignCenter);
        lblLsAire->setObjectName("lblLsAire");

        lELsAire = new QLineEdit(this);
        lELsAire->setGeometry(QRect(760, 70, 100, 30));
        lELsAire->setFont(*fuente);
        lELsAire->setAlignment(Qt::AlignCenter);
        lELsAire->setObjectName("lELsAire");

        lblLiAire = new QLabel(this);
        lblLiAire->setGeometry(QRect(650, 120, 100, 30));
        lblLiAire->setFont(*fuente);
        lblLiAire->setStyleSheet("color: white;");
        lblLiAire->setAlignment(Qt::AlignCenter);
        lblLiAire->setObjectName("lblLiAire");

        lELiAire = new QLineEdit(this);
        lELiAire->setGeometry(QRect(760, 120, 100, 30));
        lELiAire->setFont(*fuente);
        lELiAire->setAlignment(Qt::AlignCenter);
        lELiAire->setObjectName("lELiAire");

        //

        lblLsO2 = new QLabel(this);
        lblLsO2->setGeometry(QRect(650, 170, 100, 30));
        lblLsO2->setFont(*fuente);
        lblLsO2->setStyleSheet("color: white;");
        lblLsO2->setAlignment(Qt::AlignCenter);
        lblLsO2->setObjectName("lblLsO2");

        lELsO2 = new QLineEdit(this);
        lELsO2->setGeometry(QRect(760, 170, 100, 30));
        lELsO2->setFont(*fuente);
        lELsO2->setAlignment(Qt::AlignCenter);
        lELsO2->setObjectName("lELsO2");

        lblLiO2 = new QLabel(this);
        lblLiO2->setGeometry(QRect(650, 220, 100, 30));
        lblLiO2->setFont(*fuente);
        lblLiO2->setStyleSheet("color: white;");
        lblLiO2->setAlignment(Qt::AlignCenter);
        lblLiO2->setObjectName("lblLiO2");

        lELiO2 = new QLineEdit(this);
        lELiO2->setGeometry(QRect(760, 220, 100, 30));
        lELiO2->setFont(*fuente);
        lELiO2->setAlignment(Qt::AlignCenter);
        lELiO2->setObjectName("lELiO2");

        //

        lblOffPip= new QLabel(this);
        lblOffPip->setGeometry(QRect(10, 150, 100, 30));
        lblOffPip->setFont(*fuente);
        lblOffPip->setStyleSheet("color: white;");
        lblOffPip->setAlignment(Qt::AlignCenter);
        lblOffPip->setObjectName("lblOffPip");

        lEOffPip = new QLineEdit(this);
        lEOffPip->setGeometry(QRect(150, 150, 100, 30));
        lEOffPip->setFont(*fuente);
        lEOffPip->setAlignment(Qt::AlignCenter);
        lEOffPip->setObjectName("lEOffPip");

        btnAplicarAltura = new QPushButton(this);
        btnAplicarAltura->setGeometry(QRect(50, 75, 225, 50));
        btnAplicarAltura->setFont(*fuente);
        btnAplicarAltura->setText("Aplicar Altura");
        btnAplicarAltura->setObjectName("btnAplicarAltura");
        connect(btnAplicarAltura, SIGNAL(clicked()), this, SLOT(aplicarCambiosAltura()));

        btnAplicarTeclado = new QPushButton(this);
        btnAplicarTeclado->setGeometry(QRect(370, 120, 225, 50));
        btnAplicarTeclado->setFont(*fuente);
        btnAplicarTeclado->setText("Aplicar Teclado");
        btnAplicarTeclado->setObjectName("btnAplicarTeclado");
        //connect(btnAplicarTeclado, SIGNAL(clicked()), this, SLOT(aplicarCambiosTeclado()));

        btnAplicarFio2 = new QPushButton(this);
        btnAplicarFio2->setGeometry(QRect(700, 275, 225, 50));
        btnAplicarFio2->setFont(*fuente);
        btnAplicarFio2->setText("Aplicar FIO2");
        btnAplicarFio2->setObjectName("btnAplicarFio2");
        connect(btnAplicarFio2, SIGNAL(clicked()), this, SLOT(aplicarCambiosFio2()));

        btnAplicarComPip = new QPushButton(this);
        btnAplicarComPip->setGeometry(QRect(50, 200, 225, 50));
        btnAplicarComPip->setFont(*fuente);
        btnAplicarComPip->setText("Aplicar Off pip");
        btnAplicarComPip->setObjectName("btnAplicarComPip");
        //connect(btnAplicarComPip, SIGNAL(clicked()), this, SLOT(aplicarCambiosOffPip()));

        labelInfo = new QLabel(this);
        labelInfo->setGeometry(QRect(40, 400, 600, 50));
        labelInfo->setFont(*fuente);
        labelInfo->setAlignment(Qt::AlignCenter);
        labelInfo->setObjectName("labelInfo");
        labelInfo->setText("Prueba de label!!!");

        timerTecladoAplicados = new QTimer;
        timerTecladoAplicados->setSingleShot(true);
        //connect(timerTecladoAplicados, SIGNAL(timeout()), this, SLOT(revisarCambiosTeclado()));

        retranslateUi();
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiCalOtros::retranslateUi(){
    try {
        lblAltura->setText("Altura(m): ");
        lblPresionar->setText("Presionar: ");
        lblSoltar->setText("Soltar: ");
        lblPorceCambio->setText("% cambio: ");
        lblLsAire->setText("ls_aire: ");
        lblLiAire->setText("li_aire: ");
        lblLsO2->setText("ls_o2: ");
        lblLiO2->setText("li_o2: ");
        lblOffPip->setText("Off pip: ");
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiCalOtros::paintEvent(QPaintEvent* /*event*/)
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

/*void UiCalOtros::cargarOffPip(){
    try {
        QString temp = monitor->consul->leer_com_pip();
        QStringList parts = temp.split(",");
        labelInfo->setText("");
        lEOffPip->setText(parts.at(1));
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}*/

void UiCalOtros::cargarAltura(){
    try {
        QString temp = monitor->consul->leer_altura();
        QStringList parts = temp.split(",");
        labelInfo->setText("");
        lEAltura->setText(parts.at(1));
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

/*void UiCalOtros::cargarTeclado(){
    try {
        QString temp = monitor->consul->leer_teclado();
        QStringList parts = temp.split(",");
        labelInfo->setText("");
        lEPresionar->setText(parts.at(1));
        lESoltar->setText(parts.at(2));
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}*/

void UiCalOtros::cargarFio2(){
    try {
        QString temp = monitor->consul->leer_fio2();
        QStringList parts = temp.split(",");
        labelInfo->setText("");
        lEPorceCambio->setText(parts.at(1));
        lELsAire->setText(parts.at(2));
        lELiAire->setText(parts.at(3));
        lELsO2->setText(parts.at(4));
        lELiO2->setText(parts.at(5));
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

/*void UiCalOtros::aplicarCambiosOffPip(){
    try {
        QString offpip = lEOffPip->text();
        bool entero = false;
        try {
            offpip.toFloat();
            entero = true;
        }  catch (...) {
            entero = false;
        }
        if(entero){
            bool temp = monitor->consul->guarda_com_pip(lEOffPip->text());
            if(temp){
                labelInfo->setText("Off pip guardado");
            }
            else{
                labelInfo->setText("Error al guardar off pip");
            }
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}*/

void UiCalOtros::aplicarCambiosAltura(){
    try {
        QString altura = lEAltura->text();
        bool entero = false;
        try {
            altura.toInt();
            entero = true;
        }  catch (...) {
            entero = false;
        }
        if(entero){
            bool temp = monitor->consul->guarda_altura(lEAltura->text());
            if(temp){
                labelInfo->setText("Altura guardada");
            }
            else{
                labelInfo->setText("Error al guardar altura");
            }
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

/*void UiCalOtros::aplicarCambiosTeclado(){
    try {
        QString presionar = lEPresionar->text();
        QString soltar = lESoltar->text();
        bool entero = false;
        try {
            presionar.toInt();
            soltar.toInt();
            entero = true;
        }  catch (...) {
            entero = false;
        }
        if(entero){
            bool temp = monitor->consul->guarda_teclado(lEPresionar->text(),lESoltar->text());
            if(temp){
                //QString trama = "Umbral:" + presionar + "," + soltar + "\n";
                monitor->cambiosCalTeclado = false;
                monitor->envia_trama_teclado(presionar, soltar);
                labelInfo->setText("Configurando teclado...");
                timerTecladoAplicados->start(6000);
            }
            else{
                labelInfo->setText("Error al guardar teclado");
            }
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}*/

void UiCalOtros::aplicarCambiosFio2(){
    try {
        QString porce_cambio = lEPorceCambio->text();
        QString ls_aire_s = lELsAire->text();
        QString li_aire_s = lELiAire->text();
        QString ls_o2_s = lELsO2->text();
        QString li_o2_s = lELiO2->text();
        bool entero = false;
        try {
            porce_cambio.toInt();
            ls_aire_s.toInt();
            li_aire_s.toInt();
            ls_o2_s.toInt();
            li_o2_s.toInt();
            entero = true;
        }  catch (...) {
            entero = false;
        }
        if(entero){
            bool temp = monitor->consul->guarda_fio2(lEPorceCambio->text(),lELsAire->text(),lELiAire->text(),lELsO2->text(),lELiO2->text());
            if(temp){
                labelInfo->setText("Cambios guardados fio2");
                //cargar cambios en las fórmulas

                //mandar a recargar las tramas del ventilador
                monitor->actualizar_fio2();
            }
            else{
                labelInfo->setText("Error al guardar fio2");
            }
        }
        else{
            labelInfo->setText("Parámetros fio2 no son enteros");
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

/*void UiCalOtros::revisarCambiosTeclado(){
    try {
        if(monitor->cambiosCalTeclado){
            bool temp = monitor->consul->guarda_teclado(lEPresionar->text(),lESoltar->text());
            if(temp){
                labelInfo->setText("Los cambios teclado fueron aplicados");
            }
            else{
                labelInfo->setText("Los cambios teclado No fueron aplicados, error.");
            }
        }
        else{
            labelInfo->setText("Los cambios teclado No fueron aplicados, error.");
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}*/
