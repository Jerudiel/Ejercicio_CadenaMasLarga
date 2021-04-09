#include "uicalibrar.h"

UiCalibrar::UiCalibrar(QWidget *parent, Monitor *monitor) : QWidget(parent)
{
    try {
        setStyleSheet("QLineEdit{ background: gray;} QPushButton{color: white;}");
        this->monitor = monitor;
        fuente = new QFont;
        fuente->setPointSize(12);
        fuente->setBold(true);
        fuente->setWeight(75);

        calibraciones = new UiCalibraciones(this->monitor, this);
        calibraciones->setObjectName("calibraciones");

        /*rangos_offsets = {{0,70},{0,70},{0,200},{0,200},{0,500},{0,999},{0,999}};

        labelFactor1 = new QLabel(this);
        labelFactor1->setGeometry(QRect(10, 20, 130, 30));
        labelFactor1->setFont(*fuente);
        labelFactor1->setStyleSheet("color: white;");
        labelFactor1->setAlignment(Qt::AlignCenter);
        labelFactor1->setObjectName("labelFactor1");

        lineEditFactor1 = new QLineEdit(this);
        lineEditFactor1->setGeometry(QRect(150, 20, 100, 30));
        lineEditFactor1->setFont(*fuente);
        lineEditFactor1->setAlignment(Qt::AlignCenter);
        lineEditFactor1->setObjectName("lineEditFactor1");

        labelFactor2 = new QLabel(this);
        labelFactor2->setGeometry(QRect(10, 70, 130, 30));
        labelFactor2->setFont(*fuente);
        labelFactor2->setStyleSheet("color: white;");
        labelFactor2->setAlignment(Qt::AlignCenter);
        labelFactor2->setObjectName("labelFactor2");

        lineEditFactor2 = new QLineEdit(this);
        lineEditFactor2->setGeometry(QRect(150, 70, 100, 30));
        lineEditFactor2->setFont(*fuente);
        lineEditFactor2->setAlignment(Qt::AlignCenter);
        lineEditFactor2->setObjectName("lineEditFactor2");

        labelFactor3 = new QLabel(this);
        labelFactor3->setGeometry(QRect(10, 120, 130, 30));
        labelFactor3->setFont(*fuente);
        labelFactor3->setStyleSheet("color: white;");
        labelFactor3->setAlignment(Qt::AlignCenter);
        labelFactor3->setObjectName("labelFactor3");

        lineEditFactor3 = new QLineEdit(this);
        lineEditFactor3->setGeometry(QRect(150, 120, 100, 30));
        lineEditFactor3->setFont(*fuente);
        lineEditFactor3->setAlignment(Qt::AlignCenter);
        lineEditFactor3->setObjectName("lineEditFactor3");

        labelFactor4 = new QLabel(this);
        labelFactor4->setGeometry(QRect(10, 170, 130, 30));
        labelFactor4->setFont(*fuente);
        labelFactor4->setStyleSheet("color: white;");
        labelFactor4->setAlignment(Qt::AlignCenter);
        labelFactor4->setObjectName("labelFactor4");

        lineEditFactor4 = new QLineEdit(this);
        lineEditFactor4->setGeometry(QRect(150, 170, 100, 30));
        lineEditFactor4->setFont(*fuente);
        lineEditFactor4->setAlignment(Qt::AlignCenter);
        lineEditFactor4->setObjectName("lineEditFactor4");

        labelFactor5 = new QLabel(this);
        labelFactor5->setGeometry(QRect(10, 220, 130, 30));
        labelFactor5->setFont(*fuente);
        labelFactor5->setStyleSheet("color: white;");
        labelFactor5->setAlignment(Qt::AlignCenter);
        labelFactor5->setObjectName("labelFactor5");

        lineEditFactor5 = new QLineEdit(this);
        lineEditFactor5->setGeometry(QRect(150, 220, 100, 30));
        lineEditFactor5->setFont(*fuente);
        lineEditFactor5->setAlignment(Qt::AlignCenter);
        lineEditFactor5->setObjectName("lineEditFactor5");

        labelFactor6 = new QLabel(this);
        labelFactor6->setGeometry(QRect(340, 20, 100, 30));
        labelFactor6->setFont(*fuente);
        labelFactor6->setStyleSheet("color: white;");
        labelFactor6->setAlignment(Qt::AlignCenter);
        labelFactor6->setObjectName("labelFactor6");

        lineEditFactor6 = new QLineEdit(this);
        lineEditFactor6->setGeometry(QRect(450, 20, 100, 30));
        lineEditFactor6->setFont(*fuente);
        lineEditFactor6->setAlignment(Qt::AlignCenter);
        lineEditFactor6->setObjectName("lineEditFactor6");

        labelFactor7 = new QLabel(this);
        labelFactor7->setGeometry(QRect(340, 70, 100, 30));
        labelFactor7->setFont(*fuente);
        labelFactor7->setStyleSheet("color: white;");
        labelFactor7->setAlignment(Qt::AlignCenter);
        labelFactor7->setObjectName("labelFactor7");

        lineEditFactor7 = new QLineEdit(this);
        lineEditFactor7->setGeometry(QRect(450, 70, 100, 30));
        lineEditFactor7->setFont(*fuente);
        lineEditFactor7->setAlignment(Qt::AlignCenter);
        lineEditFactor7->setObjectName("lineEditFactor7");

        labelFactor8 = new QLabel(this);
        labelFactor8->setGeometry(QRect(340, 120, 100, 30));
        labelFactor8->setFont(*fuente);
        labelFactor8->setStyleSheet("color: white;");
        labelFactor8->setAlignment(Qt::AlignCenter);
        labelFactor8->setObjectName("labelFactor8");

        lineEditFactor8 = new QLineEdit(this);
        lineEditFactor8->setGeometry(QRect(450, 120, 100, 30));
        lineEditFactor8->setFont(*fuente);
        lineEditFactor8->setAlignment(Qt::AlignCenter);
        lineEditFactor8->setObjectName("lineEditFactor8");

        labelFactor9 = new QLabel(this);
        labelFactor9->setGeometry(QRect(340, 170, 100, 30));
        labelFactor9->setFont(*fuente);
        labelFactor9->setStyleSheet("color: white;");
        labelFactor9->setAlignment(Qt::AlignCenter);
        labelFactor9->setObjectName("labelFactor9");

        lineEditFactor9 = new QLineEdit(this);
        lineEditFactor9->setGeometry(QRect(450, 170, 100, 30));
        lineEditFactor9->setFont(*fuente);
        lineEditFactor9->setAlignment(Qt::AlignCenter);
        lineEditFactor9->setObjectName("lineEditFactor9");

        labelFactor10 = new QLabel(this);
        labelFactor10->setGeometry(QRect(340, 220, 100, 30));
        labelFactor10->setFont(*fuente);
        labelFactor10->setStyleSheet("color: white;");
        labelFactor10->setAlignment(Qt::AlignCenter);
        labelFactor10->setObjectName("labelFactor10");

        lineEditFactor10 = new QLineEdit(this);
        lineEditFactor10->setGeometry(QRect(450, 220, 100, 30));
        lineEditFactor10->setFont(*fuente);
        lineEditFactor10->setAlignment(Qt::AlignCenter);
        lineEditFactor10->setObjectName("lineEditFactor10");

        labelFactor11 = new QLabel(this);
        labelFactor11->setGeometry(QRect(340, 270, 100, 30));
        labelFactor11->setFont(*fuente);
        labelFactor11->setStyleSheet("color: white;");
        labelFactor11->setAlignment(Qt::AlignCenter);
        labelFactor11->setObjectName("labelFactor11");

        lineEditFactor11 = new QLineEdit(this);
        lineEditFactor11->setGeometry(QRect(450, 270, 100, 30));
        lineEditFactor11->setFont(*fuente);
        lineEditFactor11->setAlignment(Qt::AlignCenter);
        lineEditFactor11->setObjectName("lineEditFactor11");

        labelFactor12 = new QLabel(this);
        labelFactor12->setGeometry(QRect(340, 320, 100, 30));
        labelFactor12->setFont(*fuente);
        labelFactor12->setStyleSheet("color: white;");
        labelFactor12->setAlignment(Qt::AlignCenter);
        labelFactor12->setObjectName("labelFactor12");

        lineEditFactor12 = new QLineEdit(this);
        lineEditFactor12->setGeometry(QRect(450, 320, 100, 30));
        lineEditFactor12->setFont(*fuente);
        lineEditFactor12->setAlignment(Qt::AlignCenter);
        lineEditFactor12->setObjectName("lineEditFactor12");

        labelFactor13 = new QLabel(this);
        labelFactor13->setGeometry(QRect(650, 20, 100, 30));
        labelFactor13->setFont(*fuente);
        labelFactor13->setStyleSheet("color: white;");
        labelFactor13->setAlignment(Qt::AlignCenter);
        labelFactor13->setObjectName("labelFactor13");

        lineEditFactor13 = new QLineEdit(this);
        lineEditFactor13->setGeometry(QRect(760, 20, 100, 30));
        lineEditFactor13->setFont(*fuente);
        lineEditFactor13->setAlignment(Qt::AlignCenter);
        lineEditFactor13->setObjectName("lineEditFactor13");

        labelFactor14 = new QLabel(this);
        labelFactor14->setGeometry(QRect(650, 150, 100, 30));
        labelFactor14->setFont(*fuente);
        labelFactor14->setStyleSheet("color: white;");
        labelFactor14->setAlignment(Qt::AlignCenter);
        labelFactor14->setObjectName("labelFactor14");

        lineEditFactor14 = new QLineEdit(this);
        lineEditFactor14->setGeometry(QRect(760, 150, 100, 30));
        lineEditFactor14->setFont(*fuente);
        lineEditFactor14->setAlignment(Qt::AlignCenter);
        lineEditFactor14->setObjectName("lineEditFactor14");

        labelFactor15 = new QLabel(this);
        labelFactor15->setGeometry(QRect(650, 200, 100, 30));
        labelFactor15->setFont(*fuente);
        labelFactor15->setStyleSheet("color: white;");
        labelFactor15->setAlignment(Qt::AlignCenter);
        labelFactor15->setObjectName("labelFactor15");

        lineEditFactor15 = new QLineEdit(this);
        lineEditFactor15->setGeometry(QRect(760, 200, 100, 30));
        lineEditFactor15->setFont(*fuente);
        lineEditFactor15->setAlignment(Qt::AlignCenter);
        lineEditFactor15->setObjectName("lineEditFactor15");

        labelFactor16 = new QLabel(this);
        labelFactor16->setGeometry(QRect(650, 300, 100, 30));
        labelFactor16->setFont(*fuente);
        labelFactor16->setStyleSheet("color: white;");
        labelFactor16->setAlignment(Qt::AlignCenter);
        labelFactor16->setObjectName("labelFactor16");

        lineEditFactor16 = new QLineEdit(this);
        lineEditFactor16->setGeometry(QRect(760, 300, 100, 30));
        lineEditFactor16->setFont(*fuente);
        lineEditFactor16->setAlignment(Qt::AlignCenter);
        lineEditFactor16->setObjectName("lineEditFactor16");

        labelFactor17 = new QLabel(this);
        labelFactor17->setGeometry(QRect(650, 350, 100, 30));
        labelFactor17->setFont(*fuente);
        labelFactor17->setStyleSheet("color: white;");
        labelFactor17->setAlignment(Qt::AlignCenter);
        labelFactor17->setObjectName("labelFactor17");

        lineEditFactor17 = new QLineEdit(this);
        lineEditFactor17->setGeometry(QRect(760, 350, 100, 30));
        lineEditFactor17->setFont(*fuente);
        lineEditFactor17->setAlignment(Qt::AlignCenter);
        lineEditFactor17->setObjectName("lineEditFactor17");

        labelFactor18 = new QLabel(this);
        labelFactor18->setGeometry(QRect(780, 400, 100, 30));
        labelFactor18->setFont(*fuente);
        labelFactor18->setStyleSheet("color: white;");
        labelFactor18->setAlignment(Qt::AlignCenter);
        labelFactor18->setObjectName("labelFactor18");

        lineEditFactor18 = new QLineEdit(this);
        lineEditFactor18->setGeometry(QRect(890, 400, 100, 30));
        lineEditFactor18->setFont(*fuente);
        lineEditFactor18->setAlignment(Qt::AlignCenter);
        lineEditFactor18->setObjectName("lineEditFactor18");

        labelFactor19 = new QLabel(this);
        labelFactor19->setGeometry(QRect(570, 400, 100, 30));
        labelFactor19->setFont(*fuente);
        labelFactor19->setStyleSheet("color: white;");
        labelFactor19->setAlignment(Qt::AlignCenter);
        labelFactor19->setObjectName("labelFactor19");

        lineEditFactor19 = new QLineEdit(this);
        lineEditFactor19->setGeometry(QRect(680, 400, 100, 30));
        lineEditFactor19->setFont(*fuente);
        lineEditFactor19->setAlignment(Qt::AlignCenter);
        lineEditFactor19->setObjectName("lineEditFactor19");

        btnAplicarCambios = new QPushButton(this);
        btnAplicarCambios->setGeometry(QRect(40, 375, 225, 50));
        btnAplicarCambios->setFont(*fuente);
        btnAplicarCambios->setText("Aplicar");
        btnAplicarCambios->setObjectName("btnAplicarCambios");
        connect(btnAplicarCambios, SIGNAL(clicked()), this, SLOT(aplicarCambios()));

        btnAplicarOffsets = new QPushButton(this);
        btnAplicarOffsets->setGeometry(QRect(340, 375, 225, 50));
        btnAplicarOffsets->setFont(*fuente);
        btnAplicarOffsets->setText("Aplicar Offsets");
        btnAplicarOffsets->setObjectName("btnAplicarOffsets");
        connect(btnAplicarOffsets, SIGNAL(clicked()), this, SLOT(aplicarCambiosOffsets()));

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

        timerCambiosAplicados = new QTimer;
        timerCambiosAplicados->setSingleShot(true);
        connect(timerCambiosAplicados, SIGNAL(timeout()), this, SLOT(revisarCambios()));

        timerOffsetsAplicados = new QTimer;
        timerOffsetsAplicados->setSingleShot(true);
        connect(timerOffsetsAplicados, SIGNAL(timeout()), this, SLOT(revisarCambiosOffsets()));

        timerTecladoAplicados = new QTimer;
        timerTecladoAplicados->setSingleShot(true);
        connect(timerTecladoAplicados, SIGNAL(timeout()), this, SLOT(revisarCambiosTeclado()));

        retranslateUi();*/
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

/*void UiCalibrar::retranslateUi(){
    try {
        labelFactor1->setText("Factor inh: ");
        labelFactor2->setText("Umbral bajo: ");
        labelFactor3->setText("Factor exh: ");
        labelFactor4->setText("umbral alto: ");
        labelFactor5->setText("off presión: ");
        labelFactor6->setText("OF_PEEP: ");
        labelFactor7->setText("OF_PIP: ");
        labelFactor8->setText("OF_CPEEP: ");
        labelFactor9->setText("OF_CPIP: ");
        labelFactor10->setText("OF_CPRE: ");
        labelFactor11->setText("OF_BAT: ");
        labelFactor12->setText("G_BAT: ");
        labelFactor13->setText("Altura(m): ");
        labelFactor14->setText("Presionar: ");
        labelFactor15->setText("Soltar: ");
        labelFactor16->setText("% cambio: ");
        labelFactor17->setText("OF_02: ");
        labelFactor18->setText("ls_aire: ");
        labelFactor19->setText("lmin_aire: ");
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}*/

void UiCalibrar::paintEvent(QPaintEvent* /*event*/)
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

/*void UiCalibrar::revisarCambios(){
    try {
        if(monitor->cambiosCalibrar){
            bool temp = monitor->consul->guarda_cali(lineEditFactor1->text(), lineEditFactor2->text(), lineEditFactor3->text(),
                                                    lineEditFactor4->text(), lineEditFactor5->text());
            if(temp){
                labelInfo->setText("Los cambios fueron aplicados");
            }
            else{
                labelInfo->setText("Los cambios No fueron aplicados, error.");
            }
        }
        else{
            labelInfo->setText("Los cambios No fueron aplicados, error.");
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiCalibrar::revisarCambiosOffsets(){
    try {
        if(monitor->cambiosOffsets){
            bool temp = monitor->consul->guarda_offsets(lineEditFactor6->text(), lineEditFactor7->text(), lineEditFactor8->text(),
                                                      lineEditFactor9->text(), lineEditFactor10->text(), lineEditFactor11->text(),
                                                      lineEditFactor12->text());
            if(temp){
                labelInfo->setText("Los cambios offsets fueron aplicados");
            }
            else{
                labelInfo->setText("Los cambios offsets No fueron aplicados, error.");
            }
        }
        else{
            labelInfo->setText("Los cambios offsets No fueron aplicados, error.");
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiCalibrar::revisarCambiosTeclado(){
    try {
        if(monitor->cambiosCalTeclado){
            bool temp = monitor->consul->guarda_teclado(lineEditFactor14->text(),lineEditFactor15->text());
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

void UiCalibrar::aplicarCambios(){
    try {
        QStringList *temp_list = new QStringList;
        QString temp1 = lineEditFactor1->text();
        temp_list->append(temp1);
        QString temp2 = lineEditFactor2->text();
        temp_list->append(temp2);
        QString temp3 = lineEditFactor3->text();
        temp_list->append(temp3);
        QString temp4 = lineEditFactor4->text();
        temp_list->append(temp4);
        QString temp5 = lineEditFactor5->text();
        temp_list->append(temp5);

        if(temp1.size() == 3 && temp2.size() == 3 && temp3.size() == 3 && temp4.size() == 4 && temp5.size() == 2){
            try {
                bool resultado = true;
                for(int j=0; j < temp_list->size(); j++){
                    try {
                        temp_list->at(j).toInt();
                    }  catch (std::exception &e) {
                        resultado = false;
                        break;
                    }
                }
                QString trama = "B";
                if(resultado){
                    for(int j=0; j < temp_list->size(); j++){
                        trama += temp_list->at(j);
                    }
                    trama += "\n";
                    monitor->serPresion->escribir(trama);
                    labelInfo->setText("Configurando...");
                    timerCambiosAplicados->start(6000);
                }
                else{
                    labelInfo->setText("Revisar formato de factores");
                }

            }  catch (std::exception &e) {
                labelInfo->setText("Revisar formato de factores");
            }
        }
        else{
            labelInfo->setText("Formato incorrecto: " + QString::number(temp1.size()) + " " + QString::number(temp2.size()) + " " + QString::number(temp3.size()) + " " + QString::number(temp4.size()) + " " + QString::number(temp5.size()) + " ");

        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiCalibrar::cargarFactores(){
    try {
        QString temp = monitor->consul->leer_calibracion();
        QStringList parts = temp.split(",");
        labelInfo->setText("");
        lineEditFactor1->setText(parts.at(1));
        lineEditFactor2->setText(parts.at(2));
        lineEditFactor3->setText(parts.at(3));
        lineEditFactor4->setText(parts.at(4));
        lineEditFactor5->setText(parts.at(5));
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiCalibrar::cargarOffsets(){
    try {
        QString temp = monitor->consul->leer_offsets();
        QStringList parts = temp.split(",");
        labelInfo->setText("");
        lineEditFactor6->setText(parts.at(1));
        lineEditFactor7->setText(parts.at(2));
        lineEditFactor8->setText(parts.at(3));
        lineEditFactor9->setText(parts.at(4));
        lineEditFactor10->setText(parts.at(5));
        lineEditFactor11->setText(parts.at(6));
        lineEditFactor12->setText(parts.at(7));
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiCalibrar::cargarAltura(){
    try {
        QString temp = monitor->consul->leer_altura();
        QStringList parts = temp.split(",");
        labelInfo->setText("");
        lineEditFactor13->setText(parts.at(1));
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiCalibrar::cargarTeclado(){
    try {
        QString temp = monitor->consul->leer_teclado();
        QStringList parts = temp.split(",");
        labelInfo->setText("");
        lineEditFactor14->setText(parts.at(1));
        lineEditFactor15->setText(parts.at(2));
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiCalibrar::cargarFio2(){
    try {
        QString temp = monitor->consul->leer_fio2();
        QStringList parts = temp.split(",");
        labelInfo->setText("");
        lineEditFactor16->setText(parts.at(1));
        lineEditFactor17->setText(parts.at(2));
        lineEditFactor18->setText(parts.at(3));
        lineEditFactor19->setText(parts.at(4));
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiCalibrar::aplicarCambiosOffsets(){
    try {
        labelInfo->setText("Cargando offsets...");
        QStringList *temp_list = new QStringList;
        QString of_peep = lineEditFactor6->text();
        temp_list->append(of_peep);
        QString of_pip = lineEditFactor7->text();
        temp_list->append(of_pip);
        QString of_cpeep = lineEditFactor8->text();
        temp_list->append(of_cpeep);
        QString of_cpip = lineEditFactor9->text();
        temp_list->append(of_cpip);
        QString of_cpre = lineEditFactor10->text();
        temp_list->append(of_cpre);
        QString of_bat = lineEditFactor11->text();
        temp_list->append(of_bat);
        QString g_bat = lineEditFactor12->text();
        temp_list->append(g_bat);

        bool todos_numeros = true;
        for(int j=0; j < temp_list->size(); j++){
            try {
                temp_list->at(j).toInt();
            }  catch (std::exception &e) {
                todos_numeros = false;
                break;
            }
        }

        if(todos_numeros){
            bool dentro_rangos = true;
            int contador_rangos = 0;
            for(int j=0; j < temp_list->size(); j++){
                if(!(rangos_offsets[contador_rangos][0] < temp_list->at(contador_rangos).toInt() && rangos_offsets[contador_rangos][1] > temp_list->at(contador_rangos).toInt())){
                    dentro_rangos = false;
                    break;
                }
                contador_rangos += 1;
            }
            if(dentro_rangos){
                QString trama = "C";
                for(int j=0; j < temp_list->size(); j++){
                    trama += temp_list->at(j);
                }
                trama += "\n";
                if(trama.size() == 23){
                    monitor->cambiosOffsets = false;
                    monitor->tramaOffsets = trama;
                    monitor->serVent->envia_trama_config(trama);
                    labelInfo->setText("Configurando offsets...");
                    timerOffsetsAplicados->start(6000);
                }
                else{
                    labelInfo->setText("offsets formato 3 bytes incorrecto");
                }
            }
            else{
                labelInfo->setText("offsets fuera de rangos");
            }
        }
        else{
            labelInfo->setText("Revisar valores offsets");
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiCalibrar::aplicarCambiosAltura(){
    try {
        QString altura = lineEditFactor13->text();
        bool entero = false;
        try {
            altura.toInt();
            entero = true;
        }  catch (...) {
            entero = false;
        }
        if(entero){
            bool temp = monitor->consul->guarda_altura(lineEditFactor13->text());
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

void UiCalibrar::aplicarCambiosTeclado(){
    try {
        QString presionar = lineEditFactor14->text();
        QString soltar = lineEditFactor15->text();
        bool entero = false;
        try {
            presionar.toInt();
            soltar.toInt();
            entero = true;
        }  catch (...) {
            entero = false;
        }
        if(entero){
            bool temp = monitor->consul->guarda_teclado(lineEditFactor14->text(),lineEditFactor15->text());
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

void UiCalibrar::aplicarCambiosFio2(){
    try {
        QString porce_cambio = lineEditFactor16->text();
        QString of_o2 = lineEditFactor17->text();
        QString m_aire = lineEditFactor18->text();
        bool entero = false;
        try {
            porce_cambio.toInt();
            of_o2.toInt();
            m_aire.toInt();
            entero = true;
        }  catch (...) {
            entero = false;
        }
        if(entero){
            bool temp = monitor->consul->guarda_fio2(lineEditFactor16->text(),lineEditFactor17->text(),lineEditFactor18->text(),lineEditFactor19->text());
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
*/
