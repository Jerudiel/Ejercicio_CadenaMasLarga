#include "uiconfigdatetime.h"

UiConfigDatetime::UiConfigDatetime(QWidget *parent, Monitor *monitor) : QWidget(parent)
{
    try {
        setStyleSheet("color: white;");
        this->monitor = monitor;

        fuente = new QFont;
        fuente->setPointSize(12);
        fuente->setBold(true);
        fuente->setWeight(75);

        calendario = new QCalendarWidget(this);
        calendario->setGridVisible(true);
        calendario->setGeometry(QRect(100, 50, 400, 200));
        calendario->setStyleSheet("background-color: rgb(43,42,41);; color: rgb(0, 102, 204);");
        //connect(calendario, SLOT(clicked(QDate)), this, SIGNAL(mostrarFecha(QDate)));
        connect(calendario, &QCalendarWidget::clicked , this, &UiConfigDatetime::mostrarFecha);

        pickerTime = new UiQWidgetConfigReloj(this);
        pickerTime->setGeometry(QRect(600, 20, 400, 250));

        label_fecha_configurada = new QLabel(this);
        QDate date = calendario->selectedDate();
        label_fecha_configurada->setText(date.toString());
        label_fecha_configurada->setGeometry(QRect(300, 300, 200, 70));
        label_fecha_configurada->hide();

        btnAplicarCambios = new QPushButton(this);
        btnAplicarCambios->setGeometry(QRect(500, 350, 150, 50));
        btnAplicarCambios->setFont(*fuente);
        btnAplicarCambios->setText("Aplicar");
        btnAplicarCambios->setObjectName("btnAplicarCambios");
        //connect(btnAplicarCambios, SLOT(clicked()), this, SIGNAL(aplicarCambios()));
        connect(btnAplicarCambios, &QPushButton::clicked, this, &UiConfigDatetime::aplicarCambios);

        label_info = new QLabel(this);
        label_info->setGeometry(QRect(250, 410, 500, 40));
        label_info->setAlignment(Qt::AlignCenter);
        fuente->setPointSize(16);
        label_info->setFont(*fuente);

        /*connect(pickerTime->btnMasHora, SLOT(clicked()), this, SIGNAL(sumar_hora));
        connect(pickerTime->btnMenosHora, SLOT(clicked()), this, SIGNAL(restar_hora));
        connect(pickerTime->btnMasMinuto, SLOT(clicked()), this, SIGNAL(sumar_minuto));
        connect(pickerTime->btnMenosMinuto, SLOT(clicked()), this, SIGNAL(restar_minuto));
        connect(pickerTime->btnModoHorario, SLOT(clicked()), this, SIGNAL(cambiar_horario));*/

        connect(pickerTime->btnMasHora, &QPushButton::clicked , this, &UiConfigDatetime::sumar_hora);
        connect(pickerTime->btnMenosHora, &QPushButton::clicked , this, &UiConfigDatetime::restar_hora);
        connect(pickerTime->btnMasMinuto, &QPushButton::clicked , this, &UiConfigDatetime::sumar_minuto);
        connect(pickerTime->btnMenosMinuto, &QPushButton::clicked , this, &UiConfigDatetime::restar_minuto);
        connect(pickerTime->btnModoHorario, &QPushButton::clicked , this, &UiConfigDatetime::cambiar_horario);

        timerAnuncio = new QTimer;
        timerAnuncio->setSingleShot(true);
        //connect(timerAnuncio, SIGNAL(timeout()), this, SLOT(muestraAviso()));
        connect(timerAnuncio, &QTimer::timeout , this, &UiConfigDatetime::muestraAviso);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiConfigDatetime::paintEvent(QPaintEvent* /*event*/)
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

void UiConfigDatetime::mostrarFecha(QDate date){
    try {
        label_fecha_configurada->setText(date.toString());
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiConfigDatetime::cargarFecha(){
    try {
        label_info->setText("");
        //agregar aqui lo del formato "%H:%M:%S %d/%m/%y"
        QDateTime dateTime = QDateTime::currentDateTime();
        //QString dateTimeString = dateTime.toString("yy-MM-dd hh:mm:ss");
        QString dateTimeString = dateTime.toString("hh:mm:ss dd/MM/yy");
        //QString hora_format = "";
        QStringList temp = dateTimeString.split(":");
        int temp_hora = temp.at(0).toInt();
        int temp_min = temp.at(1).toInt();
        if(temp_hora > 12){
            int hora = temp_hora - 12;
            QString hora_f = darFormato2Digitos(hora);
            QString minuto_f = darFormato2Digitos(temp_min);
            pickerTime->lineEditHora->setText(hora_f);
            pickerTime->lineEditMinuto->setText(minuto_f);
            //#poner el boton en PM
            pickerTime->btnModoHorario->setChecked(true);
            pickerTime->btnModoHorario->setText("PM");
            pickerTime->btnModoHorario->setStyleSheet(pickerTime->btnBlue);
        }
        else{
            QString hora_f = darFormato2Digitos(temp_hora);
            QString minuto_f = darFormato2Digitos(temp_min);
            pickerTime->lineEditHora->setText(hora_f);
            pickerTime->lineEditMinuto->setText(minuto_f);
            //# poner el boton en AM
            pickerTime->btnModoHorario->setChecked(false);
            pickerTime->btnModoHorario->setText("AM");
            pickerTime->btnModoHorario->setStyleSheet(pickerTime->btn);
        }
        QDate date = calendario->selectedDate();
        QStringList temp_1 = dateTimeString.split(" ");
        QStringList temp_2 = temp_1.at(1).split("/");
        int temp_year = temp_2.at(2).toInt() + 2000;
        int temp_month = temp_2.at(1).toInt();
        int temp_day = temp_2.at(0).toInt();
        date.setDate(temp_year, temp_month, temp_day);
        calendario->setSelectedDate(date);


    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

QString UiConfigDatetime::darFormato2Digitos(int dato){
    try {
        QString temp = "";
        if(dato < 10){
            temp = "0" + QString::number(dato);
        }
        else{
            temp = QString::number(dato);
        }
        return temp;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

void UiConfigDatetime::sumar_hora(){
    try {
        QString temp_hora = pickerTime->lineEditHora->text();
        int temp_hora_i = temp_hora.toInt();
        if(temp_hora_i < 12){
            temp_hora_i += 1;
            QString resultado = darFormato2Digitos(temp_hora_i);
            pickerTime->lineEditHora->setText(resultado);
        }
        else{
            int temp = 1;
            QString resultado = darFormato2Digitos(temp);
            pickerTime->lineEditHora->setText(resultado);
            if(pickerTime->btnModoHorario->isChecked()){
                pickerTime->btnModoHorario->setChecked(false);
                pickerTime->btnModoHorario->setText("AM");
                pickerTime->btnModoHorario->setStyleSheet(pickerTime->btn);
            }
            else{
                pickerTime->btnModoHorario->setChecked(true);
                pickerTime->btnModoHorario->setText("PM");
                pickerTime->btnModoHorario->setStyleSheet(pickerTime->btnBlue);
            }
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiConfigDatetime::sumar_minuto(){
    try {
        QString temp_minuto = pickerTime->lineEditMinuto->text();
        int temp_minuto_i = temp_minuto.toInt();
        if(temp_minuto_i < 59){
            temp_minuto_i += 1;
            QString resultado = darFormato2Digitos(temp_minuto_i);
            pickerTime->lineEditMinuto->setText(resultado);
        }
        else{
            int temp = 0;
            QString resultado = darFormato2Digitos(temp);
            pickerTime->lineEditMinuto->setText(resultado);
            sumar_hora();
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiConfigDatetime::restar_hora(){
    try {
        QString temp_hora = pickerTime->lineEditHora->text();
        int temp_hora_i = temp_hora.toInt();
        if(temp_hora_i > 1){
            temp_hora_i -= 1;
            QString resultado = darFormato2Digitos(temp_hora_i);
            pickerTime->lineEditHora->setText(resultado);
        }
        else{
            int temp = 12;
            QString resultado = darFormato2Digitos(temp);
            pickerTime->lineEditHora->setText(resultado);
            if(pickerTime->btnModoHorario->isChecked()){
                pickerTime->btnModoHorario->setChecked(false);
                pickerTime->btnModoHorario->setText("AM");
                pickerTime->btnModoHorario->setStyleSheet(pickerTime->btn);
            }
            else{
                pickerTime->btnModoHorario->setChecked(true);
                pickerTime->btnModoHorario->setText("PM");
                pickerTime->btnModoHorario->setStyleSheet(pickerTime->btnBlue);
            }
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiConfigDatetime::restar_minuto(){
    try {
        QString temp_minuto = pickerTime->lineEditMinuto->text();
        int temp_minuto_i = temp_minuto.toInt();
        if(temp_minuto_i > 0){
            temp_minuto_i -= 1;
            QString resultado = darFormato2Digitos(temp_minuto_i);
            pickerTime->lineEditMinuto->setText(resultado);
        }
        else{
            int temp = 59;
            QString resultado = darFormato2Digitos(temp);
            pickerTime->lineEditMinuto->setText(resultado);
            restar_hora();
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiConfigDatetime::cambiar_horario(){
    try {
        if(pickerTime->btnModoHorario->isChecked()){
            pickerTime->btnModoHorario->setText("PM");
            pickerTime->btnModoHorario->setStyleSheet(pickerTime->btnBlue);
        }
        else{
            pickerTime->btnModoHorario->setText("AM");
            pickerTime->btnModoHorario->setStyleSheet(pickerTime->btn);
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiConfigDatetime::aplicarCambios(){
    try {
       QDate date = calendario->selectedDate();
       int temp_year = date.year();
       int temp_month = date.month();
       int temp_day = date.day();
       int temp_hora = pickerTime->lineEditMinuto->text().toInt();
       if(pickerTime->btnModoHorario->isChecked()){
           temp_hora += 12;
       }
       int temp_minuto = pickerTime->lineEditMinuto->text().toInt();
       QString temp_year_s = QString::number(temp_year);
       QString temp_month_s = QString::number(temp_month);
       if(temp_month < 10){
           temp_month_s = "0" + QString::number(temp_month);
       }
       QString temp_day_s = QString::number(temp_day);
       if(temp_day < 10){
           temp_day_s = "0" + QString::number(temp_day);
       }
       QString temp_hora_s = QString::number(temp_hora);
       if(temp_hora < 10){
           temp_hora_s = "0" + QString::number(temp_hora);
       }
       QString temp_minuto_s = QString::number(temp_minuto);
       if(temp_minuto < 10){
           temp_minuto_s = "0" + QString::number(temp_minuto);
       }
       /*QString trama = temp_year_s + "-" + temp_month_s + "-" + temp_day_s + " " + temp_hora_s + ":" + temp_minuto_s + ":00";
       QString trama_comando = "sudo date --set='" + trama + "'";
       QProcess::execute(trama_comando);*/


       /*QString trama = temp_year_s + "-" + temp_month_s + "-" + temp_day_s + " " + temp_hora_s + ":" + temp_minuto_s + ":00";
       QString comando = "sudo /bin/bash -c date -s '" + trama + "'";
       qDebug() << "comando: " << comando;
       int rr = QProcess::execute(comando);
       //qDebug() << "[DATE EXECUTE] " << rr;
       if(rr == -2){
           qDebug() << "[SET DATE] no inicia";
       }
       else if(rr == -1){
           qDebug() << "[SET DATE] crash";
       }

       label_info->setText("Se cambio la fecha y hora");
       timerAnuncio->start(5000);*/

       ///////////nueva forma
       //poner el comando date --set ...
       QProcess process;
       //QString command = "sudo date -s '" + trama + "'";
       QString trama = temp_year_s + "-" + temp_month_s + "-" + temp_day_s + " " + temp_hora_s + ":" + temp_minuto_s + ":00";
       QString command = "sudo /bin/bash -c date -s '" + trama + "'";
       qDebug() << "[SET DATE] command: " << command;
       process.start(command);
       process.waitForFinished(-1);
       QString stdput_process = process.readAllStandardOutput();
       QString stderror_process = process.readAllStandardError();
       if(stderror_process.size() > 0){
           qDebug() << "[SET DATE] Error al actualizar fecha y hora: " << stderror_process;
       }
       else{
           qDebug() << "[SET DATE] Se actualiza la fecha y hora con éxito: " << stdput_process;
       }
       label_info->setText("Se cambio la fecha y hora");
       timerAnuncio->start(5000);
       /////////////////

    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        label_info->setText("Problema al cambiar fecha y hora");
        timerAnuncio->start(5000);
    }
}

void UiConfigDatetime::muestraAviso(){
    try {
        label_info->setText("");
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}


