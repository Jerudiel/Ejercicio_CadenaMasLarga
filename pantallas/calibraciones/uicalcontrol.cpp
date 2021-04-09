#include "uicalcontrol.h"

UiCalControl::UiCalControl(QWidget *parent, Monitor *monitor) : QWidget(parent)
{
    try {
        setStyleSheet("QLineEdit{ background: gray;} QPushButton{color: white;}");
        this->monitor = monitor;

        fuente = new QFont;
        fuente->setPointSize(12);
        fuente->setBold(true);
        fuente->setWeight(75);

        rangos_offsets = {{0,70},{0,70},{0,200},{0,200},{0,500},{0,999},{0,999}};

        lblOffPeep = new QLabel(this);
        lblOffPeep->setGeometry(QRect(10, 20, 130, 30));
        lblOffPeep->setFont(*fuente);
        lblOffPeep->setStyleSheet("color: white;");
        lblOffPeep->setAlignment(Qt::AlignCenter);
        lblOffPeep->setObjectName("lblOffPeep");

        lEOffPeep = new QLineEdit(this);
        lEOffPeep->setGeometry(QRect(150, 20, 100, 30));
        lEOffPeep->setFont(*fuente);
        lEOffPeep->setAlignment(Qt::AlignCenter);
        lEOffPeep->setObjectName("lEOffPeep");

        lblOffPip = new QLabel(this);
        lblOffPip->setGeometry(QRect(10, 70, 130, 30));
        lblOffPip->setFont(*fuente);
        lblOffPip->setStyleSheet("color: white;");
        lblOffPip->setAlignment(Qt::AlignCenter);
        lblOffPip->setObjectName("lblOffPip");

        lEOffPip = new QLineEdit(this);
        lEOffPip->setGeometry(QRect(150, 70, 100, 30));
        lEOffPip->setFont(*fuente);
        lEOffPip->setAlignment(Qt::AlignCenter);
        lEOffPip->setObjectName("lEOffPip");

        lblOffCpeep = new QLabel(this);
        lblOffCpeep->setGeometry(QRect(10, 120, 130, 30));
        lblOffCpeep->setFont(*fuente);
        lblOffCpeep->setStyleSheet("color: white;");
        lblOffCpeep->setAlignment(Qt::AlignCenter);
        lblOffCpeep->setObjectName("lblOffCpeep");

        lEOffCpeep = new QLineEdit(this);
        lEOffCpeep->setGeometry(QRect(150, 120, 100, 30));
        lEOffCpeep->setFont(*fuente);
        lEOffCpeep->setAlignment(Qt::AlignCenter);
        lEOffCpeep->setObjectName("lEOffCpeep");

        lblOffCpip = new QLabel(this);
        lblOffCpip->setGeometry(QRect(10, 170, 130, 30));
        lblOffCpip->setFont(*fuente);
        lblOffCpip->setStyleSheet("color: white;");
        lblOffCpip->setAlignment(Qt::AlignCenter);
        lblOffCpip->setObjectName("lblOffCpip");

        lEOffCpip = new QLineEdit(this);
        lEOffCpip->setGeometry(QRect(150, 170, 100, 30));
        lEOffCpip->setFont(*fuente);
        lEOffCpip->setAlignment(Qt::AlignCenter);
        lEOffCpip->setObjectName("lEOffCpip");

        lblOffCPres = new QLabel(this);
        lblOffCPres->setGeometry(QRect(10, 220, 130, 30));
        lblOffCPres->setFont(*fuente);
        lblOffCPres->setStyleSheet("color: white;");
        lblOffCPres->setAlignment(Qt::AlignCenter);
        lblOffCPres->setObjectName("lblOffCPres");

        lEOffCPres = new QLineEdit(this);
        lEOffCPres->setGeometry(QRect(150, 220, 100, 30));
        lEOffCPres->setFont(*fuente);
        lEOffCPres->setAlignment(Qt::AlignCenter);
        lEOffCPres->setObjectName("lEOffCPres");

        lblOffBat = new QLabel(this);
        lblOffBat->setGeometry(QRect(340, 20, 130, 30));
        lblOffBat->setFont(*fuente);
        lblOffBat->setStyleSheet("color: white;");
        lblOffBat->setAlignment(Qt::AlignCenter);
        lblOffBat->setObjectName("lblOffBat");

        lEOffBat = new QLineEdit(this);
        lEOffBat->setGeometry(QRect(450, 20, 100, 30));
        lEOffBat->setFont(*fuente);
        lEOffBat->setAlignment(Qt::AlignCenter);
        lEOffBat->setObjectName("lEOffBat");

        lblGBat = new QLabel(this);
        lblGBat->setGeometry(QRect(340, 70, 130, 30));
        lblGBat->setFont(*fuente);
        lblGBat->setStyleSheet("color: white;");
        lblGBat->setAlignment(Qt::AlignCenter);
        lblGBat->setObjectName("lblGBat");

        lEGBat = new QLineEdit(this);
        lEGBat->setGeometry(QRect(450, 70, 100, 30));
        lEGBat->setFont(*fuente);
        lEGBat->setAlignment(Qt::AlignCenter);
        lEGBat->setObjectName("lEGBat");

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

        retranslateUi();

    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void UiCalControl::retranslateUi(){
    try {
        lblOffPeep->setText("OF_PEEP: ");
        lblOffPip->setText("OF_PIP: ");
        lblOffCpeep->setText("OF_CPEEP: ");
        lblOffCpip->setText("OF_CPIP: ");
        lblOffCPres->setText("OF_CPRE: ");
        lblOffBat->setText("OF_BAT: ");
        lblGBat->setText("G_BAT: ");
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiCalControl::paintEvent(QPaintEvent* /*event*/)
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

void UiCalControl::revisarCambios(){
    try {
        if(monitor->cambiosOffsets){
            bool temp = monitor->consul->guarda_offsets(lEOffPeep->text(), lEOffPip->text(), lEOffCpeep->text(),
                                                      lEOffCpip->text(), lEOffCPres->text(), lEOffBat->text(),
                                                      lEGBat->text());
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

void UiCalControl::aplicarCambios(){
    try {
        labelInfo->setText("Cargando offsets...");
        QStringList *temp_list = new QStringList;
        QString of_peep = lEOffPeep->text();
        temp_list->append(of_peep);
        QString of_pip = lEOffPip->text();
        temp_list->append(of_pip);
        QString of_cpeep = lEOffCpeep->text();
        temp_list->append(of_cpeep);
        QString of_cpip = lEOffCpip->text();
        temp_list->append(of_cpip);
        QString of_cpre = lEOffCPres->text();
        temp_list->append(of_cpre);
        QString of_bat = lEOffBat->text();
        temp_list->append(of_bat);
        QString g_bat = lEGBat->text();
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
                    timerCambiosAplicados->start(6000);
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

void UiCalControl::cargarFactores(){
    try {
        QString temp = monitor->consul->leer_offsets();
        QStringList parts = temp.split(",");
        labelInfo->setText("");
        lEOffPeep->setText(parts.at(1));
        lEOffPip->setText(parts.at(2));
        lEOffCpeep->setText(parts.at(3));
        lEOffCpip->setText(parts.at(4));
        lEOffCPres->setText(parts.at(5));
        lEOffBat->setText(parts.at(6));
        lEGBat->setText(parts.at(7));
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}
