#include "uicalsensores.h"

UiCalSensores::UiCalSensores(QWidget *parent, Monitor *monitor) : QWidget(parent)
{
    try {
        setStyleSheet("QLineEdit{ background: gray;} QPushButton{color: white;}");
        this->monitor = monitor;

        fuente = new QFont;
        fuente->setPointSize(12);
        fuente->setBold(true);
        fuente->setWeight(75);

        lblFactInh = new QLabel(this);
        lblFactInh->setGeometry(QRect(10, 20, 130, 30));
        lblFactInh->setFont(*fuente);
        lblFactInh->setStyleSheet("color: white;");
        lblFactInh->setAlignment(Qt::AlignCenter);
        lblFactInh->setObjectName("lblFactInh");

        lEFactInh = new QLineEdit(this);
        lEFactInh->setGeometry(QRect(150, 20, 100, 30));
        lEFactInh->setFont(*fuente);
        lEFactInh->setAlignment(Qt::AlignCenter);
        lEFactInh->setObjectName("lEFactInh");

        lblUmBajo = new QLabel(this);
        lblUmBajo->setGeometry(QRect(10, 70, 130, 30));
        lblUmBajo->setFont(*fuente);
        lblUmBajo->setStyleSheet("color: white;");
        lblUmBajo->setAlignment(Qt::AlignCenter);
        lblUmBajo->setObjectName("lblUmBajo");

        lEUmBajo = new QLineEdit(this);
        lEUmBajo->setGeometry(QRect(150, 70, 100, 30));
        lEUmBajo->setFont(*fuente);
        lEUmBajo->setAlignment(Qt::AlignCenter);
        lEUmBajo->setObjectName("lEFactInh");

        lblFactExh = new QLabel(this);
        lblFactExh->setGeometry(QRect(10, 120, 130, 30));
        lblFactExh->setFont(*fuente);
        lblFactExh->setStyleSheet("color: white;");
        lblFactExh->setAlignment(Qt::AlignCenter);
        lblFactExh->setObjectName("lblFactExh");

        lEFactExh = new QLineEdit(this);
        lEFactExh->setGeometry(QRect(150, 120, 100, 30));
        lEFactExh->setFont(*fuente);
        lEFactExh->setAlignment(Qt::AlignCenter);
        lEFactExh->setObjectName("lEFactExh");

        lblUmBAlto = new QLabel(this);
        lblUmBAlto->setGeometry(QRect(10, 170, 130, 30));
        lblUmBAlto->setFont(*fuente);
        lblUmBAlto->setStyleSheet("color: white;");
        lblUmBAlto->setAlignment(Qt::AlignCenter);
        lblUmBAlto->setObjectName("lblUmBAlto");

        lEUmAlto = new QLineEdit(this);
        lEUmAlto->setGeometry(QRect(150, 170, 100, 30));
        lEUmAlto->setFont(*fuente);
        lEUmAlto->setAlignment(Qt::AlignCenter);
        lEUmAlto->setObjectName("lEUmAlto");

        lblOffPres = new QLabel(this);
        lblOffPres->setGeometry(QRect(10, 220, 130, 30));
        lblOffPres->setFont(*fuente);
        lblOffPres->setStyleSheet("color: white;");
        lblOffPres->setAlignment(Qt::AlignCenter);
        lblOffPres->setObjectName("lblOffPres");

        lEOffPres = new QLineEdit(this);
        lEOffPres->setGeometry(QRect(150, 220, 100, 30));
        lEOffPres->setFont(*fuente);
        lEOffPres->setAlignment(Qt::AlignCenter);
        lEOffPres->setObjectName("lEOffPres");

        lblAjuExh = new QLabel(this);
        lblAjuExh->setGeometry(QRect(340, 20, 130, 30));
        lblAjuExh->setFont(*fuente);
        lblAjuExh->setStyleSheet("color: white;");
        lblAjuExh->setAlignment(Qt::AlignCenter);
        lblAjuExh->setObjectName("lblAjuExh");

        lEAjuExh = new QLineEdit(this);
        lEAjuExh->setGeometry(QRect(470, 20, 100, 30));
        lEAjuExh->setFont(*fuente);
        lEAjuExh->setAlignment(Qt::AlignCenter);
        lEAjuExh->setObjectName("lEAjuExh");

        lblOffExh = new QLabel(this);
        lblOffExh->setGeometry(QRect(340, 70, 130, 30));
        lblOffExh->setFont(*fuente);
        lblOffExh->setStyleSheet("color: white;");
        lblOffExh->setAlignment(Qt::AlignCenter);
        lblOffExh->setObjectName("lblOffExh");

        lEOffExh = new QLineEdit(this);
        lEOffExh->setGeometry(QRect(470, 70, 100, 30));
        lEOffExh->setFont(*fuente);
        lEOffExh->setAlignment(Qt::AlignCenter);
        lEOffExh->setObjectName("lEOffExh");

        lblFacVPH = new QLabel(this);
        lblFacVPH->setGeometry(QRect(340, 120, 130, 30));
        lblFacVPH->setFont(*fuente);
        lblFacVPH->setStyleSheet("color: white;");
        lblFacVPH->setAlignment(Qt::AlignCenter);
        lblFacVPH->setObjectName("lblFacVPH");

        lEFacVPH = new QLineEdit(this);
        lEFacVPH->setGeometry(QRect(470, 120, 100, 30));
        lEFacVPH->setFont(*fuente);
        lEFacVPH->setAlignment(Qt::AlignCenter);
        lEFacVPH->setObjectName("lEFacVPH");

        btnAplicarCambios = new QPushButton(this);
        btnAplicarCambios->setGeometry(QRect(200, 300, 225, 50));
        btnAplicarCambios->setFont(*fuente);
        btnAplicarCambios->setText("Aplicar");
        btnAplicarCambios->setObjectName("btnAplicarCambios");
        connect(btnAplicarCambios, SIGNAL(clicked()), this, SLOT(aplicarCambios()));

        labelInfo = new QLabel(this);
        labelInfo->setGeometry(QRect(40, 400, 600, 50));
        labelInfo->setFont(*fuente);
        labelInfo->setAlignment(Qt::AlignCenter);
        labelInfo->setObjectName("labelInfo");
        labelInfo->setText("Prueba de label!!!");

        timerCambiosAplicados = new QTimer;
        timerCambiosAplicados->setSingleShot(true);
        connect(timerCambiosAplicados, SIGNAL(timeout()), this, SLOT(revisarCambios()));

        timerMuestraMensaje = new QTimer;
        timerMuestraMensaje->setSingleShot(true);
        connect(timerMuestraMensaje, SIGNAL(timeout()), this, SLOT(limpiaMensaje()));

        retranslateUi();

        //qDebug() << "Termina de crear pantalla sensores";

    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void UiCalSensores::retranslateUi(){
    try {
        lblFactInh->setText("Factor In1: ");
        lblUmBajo->setText("Factor In2: ");
        lblFactExh->setText("Factor In3: ");
        lblUmBAlto->setText("Factor In4: ");
        lblOffPres->setText("Offset Pre: ");
        lblAjuExh->setText("Factor Exh: ");
        lblOffExh->setText("Factor V-P L: ");
        lblFacVPH->setText("Factor V-P H: ");
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiCalSensores::paintEvent(QPaintEvent* /*event*/)
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

void UiCalSensores::revisarCambios(){
    try {
        if(monitor->cambiosCalibrar){
            bool temp = monitor->consul->guarda_cali(lEFactInh->text(), lEUmBajo->text(), lEFactExh->text(),
                                                    lEUmAlto->text(), lEOffPres->text(), lEAjuExh->text(), lEOffExh->text(), lEFacVPH->text());
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

QString UiCalSensores::darFormato3Bytes(QString numero){
    try {
        QString res = "";
        int temp_int = numero.toInt();
        if(0 <= temp_int && temp_int < 10){
            res = "00" + QString::number(temp_int);
        }
        else if(10 <= temp_int && temp_int < 100){
            res = "0" + QString::number(temp_int);
        }
        else if(100 <= temp_int && temp_int < 1000){
            res = QString::number(temp_int);
        }
        return res;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

void UiCalSensores::muestraMensaje(QString trama){
    try {
        labelInfo->setText(trama);
        timerMuestraMensaje->start(3000);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void UiCalSensores::limpiaMensaje(){
    try {
        labelInfo->setText("");
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void UiCalSensores::aplicarCambios(){
    try {
        QStringList *temp_list = new QStringList;
        QString temp1 = lEFactInh->text();
        temp_list->append(temp1);
        QString temp2 = lEUmBajo->text();
        temp_list->append(temp2);
        QString temp3 = lEFactExh->text();
        temp_list->append(temp3);
        QString temp4 = lEUmAlto->text();
        temp_list->append(temp4);
        QString temp5 = lEOffPres->text();
        temp_list->append(temp5);
        QString temp6 = lEAjuExh->text();
        temp_list->append(temp6);
        QString temp7 = lEOffExh->text();
        temp_list->append(temp7);
        QString temp8 = lEFacVPH->text();
        temp_list->append(temp8);

        try {
            bool resultado = true;
            for(int j=0; j < temp_list->size(); j++){
                try {
                    int tt_int = temp_list->at(j).toInt();
                    if(tt_int > 999){
                        resultado = false;
                        break;
                    }
                }  catch (std::exception &e) {
                    resultado = false;
                    break;
                }
            }
            QString trama = "B";
            if(resultado){
                for(int j=0; j < temp_list->size(); j++){
                    trama += darFormato3Bytes(temp_list->at(j));
                }
                trama += "\n";
                if(trama.size() == 26){
                    monitor->serPresion->escribir(trama);
                    labelInfo->setText("Configurando...");
                    timerCambiosAplicados->start(6000);
                }
                else{
                    muestraMensaje("Error tamaño de trama");
                }
            }
            else{
                muestraMensaje("Revisar formato de factores: valores entre 0-999 y enteros");
            }

        }  catch (std::exception &e) {
            labelInfo->setText("Revisar formato de factores");
        }

//        if(temp1.size() == 3 && temp2.size() == 3 && temp3.size() == 3 && temp4.size() == 3 && temp5.size() == 3 && temp6.size() == 3 && temp7.size() == 3 && temp8.size() == 3){
//            try {
//                bool resultado = true;
//                for(int j=0; j < temp_list->size(); j++){
//                    try {
//                        temp_list->at(j).toInt();
//                    }  catch (std::exception &e) {
//                        resultado = false;
//                        break;
//                    }
//                }
//                QString trama = "B";
//                if(resultado){
//                    for(int j=0; j < temp_list->size(); j++){
//                        trama += temp_list->at(j);
//                    }
//                    trama += "\n";
//                    monitor->serPresion->escribir(trama);
//                    labelInfo->setText("Configurando...");
//                    timerCambiosAplicados->start(6000);
//                }
//                else{
//                    labelInfo->setText("Revisar formato de factores");
//                }

//            }  catch (std::exception &e) {
//                labelInfo->setText("Revisar formato de factores");
//            }
//        }
//        else{
//            labelInfo->setText("Formato incorrecto: " + QString::number(temp1.size()) + " " + QString::number(temp2.size()) + " " + QString::number(temp3.size()) + " " + QString::number(temp4.size()) + " " + QString::number(temp5.size()) + " "+ QString::number(temp6.size()) + " "+ QString::number(temp7.size()) + " ");

//        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiCalSensores::cargarFactores(){
    try {
        QString temp = monitor->consul->leer_calibracion();
        QStringList parts = temp.split(",");
        labelInfo->setText("");
        lEFactInh->setText(parts.at(1));
        lEUmBajo->setText(parts.at(2));
        lEFactExh->setText(parts.at(3));
        lEUmAlto->setText(parts.at(4));
        lEOffPres->setText(parts.at(5));
        lEAjuExh->setText(parts.at(6));
        lEOffExh->setText(parts.at(7));
        lEFacVPH->setText(parts.at(8));
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}
