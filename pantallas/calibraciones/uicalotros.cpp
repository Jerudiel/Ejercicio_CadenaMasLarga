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
        lblAltura->setGeometry(QRect(650, 20, 100, 30));
        lblAltura->setFont(*fuente);
        lblAltura->setStyleSheet("color: white;");
        lblAltura->setAlignment(Qt::AlignCenter);
        lblAltura->setObjectName("lblAltura");

        lEAltura = new QLineEdit(this);
        lEAltura->setGeometry(QRect(760, 20, 100, 30));
        lEAltura->setFont(*fuente);
        lEAltura->setAlignment(Qt::AlignCenter);
        lEAltura->setObjectName("lEAltura");

        lblPresionar = new QLabel(this);
        lblPresionar->setGeometry(QRect(650, 150, 100, 30));
        lblPresionar->setFont(*fuente);
        lblPresionar->setStyleSheet("color: white;");
        lblPresionar->setAlignment(Qt::AlignCenter);
        lblPresionar->setObjectName("lblPresionar");

        lEPresionar = new QLineEdit(this);
        lEPresionar->setGeometry(QRect(760, 150, 100, 30));
        lEPresionar->setFont(*fuente);
        lEPresionar->setAlignment(Qt::AlignCenter);
        lEPresionar->setObjectName("lEPresionar");

        lblSoltar = new QLabel(this);
        lblSoltar->setGeometry(QRect(650, 200, 100, 30));
        lblSoltar->setFont(*fuente);
        lblSoltar->setStyleSheet("color: white;");
        lblSoltar->setAlignment(Qt::AlignCenter);
        lblSoltar->setObjectName("lblSoltar");

        lESoltar = new QLineEdit(this);
        lESoltar->setGeometry(QRect(760, 200, 100, 30));
        lESoltar->setFont(*fuente);
        lESoltar->setAlignment(Qt::AlignCenter);
        lESoltar->setObjectName("lESoltar");

        lblPorceCambio = new QLabel(this);
        lblPorceCambio->setGeometry(QRect(650, 300, 100, 30));
        lblPorceCambio->setFont(*fuente);
        lblPorceCambio->setStyleSheet("color: white;");
        lblPorceCambio->setAlignment(Qt::AlignCenter);
        lblPorceCambio->setObjectName("lblPorceCambio");

        lEPorceCambio = new QLineEdit(this);
        lEPorceCambio->setGeometry(QRect(760, 300, 100, 30));
        lEPorceCambio->setFont(*fuente);
        lEPorceCambio->setAlignment(Qt::AlignCenter);
        lEPorceCambio->setObjectName("lEPorceCambio");

        lblOffO2 = new QLabel(this);
        lblOffO2->setGeometry(QRect(650, 350, 100, 30));
        lblOffO2->setFont(*fuente);
        lblOffO2->setStyleSheet("color: white;");
        lblOffO2->setAlignment(Qt::AlignCenter);
        lblOffO2->setObjectName("lblOffO2");

        lEOffO2 = new QLineEdit(this);
        lEOffO2->setGeometry(QRect(760, 350, 100, 30));
        lEOffO2->setFont(*fuente);
        lEOffO2->setAlignment(Qt::AlignCenter);
        lEOffO2->setObjectName("lEOffO2");

        lblLMinAire = new QLabel(this);
        lblLMinAire->setGeometry(QRect(780, 400, 100, 30));
        lblLMinAire->setFont(*fuente);
        lblLMinAire->setStyleSheet("color: white;");
        lblLMinAire->setAlignment(Qt::AlignCenter);
        lblLMinAire->setObjectName("lblLMinAire");

        lELMinAire = new QLineEdit(this);
        lELMinAire->setGeometry(QRect(890, 400, 100, 30));
        lELMinAire->setFont(*fuente);
        lELMinAire->setAlignment(Qt::AlignCenter);
        lELMinAire->setObjectName("lELMinAire");

        lblLsAire = new QLabel(this);
        lblLsAire->setGeometry(QRect(570, 400, 100, 30));
        lblLsAire->setFont(*fuente);
        lblLsAire->setStyleSheet("color: white;");
        lblLsAire->setAlignment(Qt::AlignCenter);
        lblLsAire->setObjectName("lblLsAire");

        lELsAire = new QLineEdit(this);
        lELsAire->setGeometry(QRect(680, 400, 100, 30));
        lELsAire->setFont(*fuente);
        lELsAire->setAlignment(Qt::AlignCenter);
        lELsAire->setObjectName("lELsAire");

        btnAplicarAltura = new QPushButton(this);
        btnAplicarAltura->setGeometry(QRect(700, 75, 225, 50));
        btnAplicarAltura->setFont(*fuente);
        btnAplicarAltura->setText("Aplicar Altura");
        btnAplicarAltura->setObjectName("btnAplicarAltura");
        connect(btnAplicarAltura, SIGNAL(clicked()), this, SLOT(aplicarCambiosAltura()));

        btnAplicarTeclado = new QPushButton(this);
        btnAplicarTeclado->setGeometry(QRect(700, 240, 225, 50));
        btnAplicarTeclado->setFont(*fuente);
        btnAplicarTeclado->setText("Aplicar Teclado");
        btnAplicarTeclado->setObjectName("btnAplicarTeclado");
        connect(btnAplicarTeclado, SIGNAL(clicked()), this, SLOT(aplicarCambiosTeclado()));

        btnAplicarFio2 = new QPushButton(this);
        btnAplicarFio2->setGeometry(QRect(700, 445, 225, 50));
        btnAplicarFio2->setFont(*fuente);
        btnAplicarFio2->setText("Aplicar FIO2");
        btnAplicarFio2->setObjectName("btnAplicarFio2");
        connect(btnAplicarFio2, SIGNAL(clicked()), this, SLOT(aplicarCambiosFio2()));

        labelInfo = new QLabel(this);
        labelInfo->setGeometry(QRect(40, 450, 600, 50));
        labelInfo->setFont(*fuente);
        labelInfo->setAlignment(Qt::AlignCenter);
        labelInfo->setObjectName("labelInfo");
        labelInfo->setText("Prueba de label!!!");

        timerTecladoAplicados = new QTimer;
        timerTecladoAplicados->setSingleShot(true);
        connect(timerTecladoAplicados, SIGNAL(timeout()), this, SLOT(revisarCambiosTeclado()));

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
        lblOffO2->setText("OF_02: ");
        lblLMinAire->setText("ls_aire: ");
        lblLsAire->setText("lmin_aire: ");
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

void UiCalOtros::cargarTeclado(){
    try {
        QString temp = monitor->consul->leer_teclado();
        QStringList parts = temp.split(",");
        labelInfo->setText("");
        lEPresionar->setText(parts.at(1));
        lESoltar->setText(parts.at(2));
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiCalOtros::cargarFio2(){
    try {
        QString temp = monitor->consul->leer_fio2();
        QStringList parts = temp.split(",");
        labelInfo->setText("");
        lEPorceCambio->setText(parts.at(1));
        lEOffO2->setText(parts.at(2));
        lELMinAire->setText(parts.at(3));
        lELsAire->setText(parts.at(4));
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

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

void UiCalOtros::aplicarCambiosTeclado(){
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
}

void UiCalOtros::aplicarCambiosFio2(){
    try {
        QString porce_cambio = lEPorceCambio->text();
        QString of_o2 = lEOffO2->text();
        QString m_aire = lELMinAire->text();
        QString ls_aire = lELsAire->text();
        bool entero = false;
        try {
            porce_cambio.toInt();
            of_o2.toInt();
            m_aire.toInt();
            ls_aire.toInt();
            entero = true;
        }  catch (...) {
            entero = false;
        }
        if(entero){
            bool temp = monitor->consul->guarda_fio2(lEPorceCambio->text(),lEOffO2->text(),lELMinAire->text(),lELsAire->text());
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

void UiCalOtros::revisarCambiosTeclado(){
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
}
