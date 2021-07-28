#include "mainwindow.h"

MainWindow::MainWindow(ServerWS *server, QWidget *parent, bool debug_t, bool debug_c, bool debug_s)
    : QMainWindow(parent)
{
    try {
        QString ruta = QDir::currentPath();
        //qDebug() << "ruat path: " + ruta ;

        config = new QSettings(ruta + "/config.ini", QSettings::IniFormat);

        this->server = server;
        connect(server, SIGNAL(enviaComando(QString)), this, SLOT(tecladoVirtual(QString)));
        setGeometry(0,0,1024,650);
        setFixedSize(1024,650);

        //crear stackedwidget
        contenedorPrincipal = new QStackedWidget;
        contenedorPrincipal->setObjectName("contenedorPrincipal");

        //poner al stacked widget como centralwidget
        setCentralWidget(contenedorPrincipal);

        vAviso = nullptr;

        //prueba db postgres
        consul = new ConsultasDb(config);
        //aqui debería ir la inicialización de las consultas a sqlite
        ///consul = new Consultas;
        ///bool conectado = consul->conecta();
        if(consul->baseDatos.isOpen()){
            ///consul->cerrar();

            reloj = new Reloj;

            get_last_event();

            //aquí agregar las pantallas
            //qDebug() << "Se crea pantalla monitor";
            monitor = new Monitor(this, consul, debug_c, debug_s);

            //connect(monitor, SIGNAL(calTeclado(QString)), this, SLOT(calibrarTeclado(QString)));

            //connect(monitor, SIGNAL(get_mode_keyboard_frame(QString)), this, SLOT(get_mode_keyboard_command(QString)));
            //connect(monitor, SIGNAL(get_umbral_key(QString)), this, SLOT(get_umbral_key_command(QString)));
            //connect(monitor, SIGNAL(get_umbral_keyboard(QString)), this, SLOT(get_umbral_keyboard_command(QString)));
            connect(monitor, SIGNAL(send_frame(QString)), this, SLOT(send_frame_keyboard(QString)));
            connect(monitor, SIGNAL(set_watch(QString)), this, SLOT(set_watch(QString)));

            //qDebug() << "pantalla monitor a contenedor principal";
            contenedorPrincipal->addWidget(monitor);

            contenedorPrincipal->setCurrentWidget(monitor);

            //qDebug() << "Se crea pantalla configuracion";

            configuracion = new UiConfiguracion(monitor, this);
            contenedorPrincipal->addWidget(configuracion);

            //qDebug() << "Se crea pantalla alarmas";

            alarmas = new UiAlarmas(monitor, this);
            contenedorPrincipal->addWidget(alarmas);

            ENVIAR_SIGNOS = 0;
            showFullScreen();

            //reloj = new Reloj;
            reloj->asignaLabel(monitor->label_fecha);
            //monitor->get_last_event();
            //reloj->start();

            serTeclado = new Teclado(debug_t); //, *recteclado
            //serTeclado->asignaPadre(this);
            connect(serTeclado, SIGNAL(enviaLinea(QString)), this, SLOT(recteclado(QString)));
            connect(serTeclado, SIGNAL(muestraAviso(QString)), this, SLOT(muestraAviso(QString)));
            connect(serTeclado, SIGNAL(cierraAviso()), this, SLOT(_closepopup()));

            abrePantallaMonitor();

            avisoTeclaActivo = false;
            avisoPresiActivo = false;
            avisoVentiActivo = false;

            tecladoConectado = false;
            tecladoComandoRecibido = false;

            contadorTeclado = 0;
            timerTeclado = new QTimer;
            timerTeclado->setInterval(3000);
            connect(timerTeclado, SIGNAL(timeout()), this, SLOT(revisarConexionTeclado()));
            timerTeclado->start();
            serTeclado->escribir("listo\n");

            duration = 0.12;
            freq = 1209;

        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

MainWindow::~MainWindow()
{

}

void MainWindow::revisarConexionTeclado(){
    try {
        if(tecladoConectado){
            qDebug() << "Teclado conectado";
            timerTeclado->stop();
            monitor->label_debug->setText("Listo!");
        }
        else{
            if(tecladoComandoRecibido){
                if(tecladoComandoRecibido < 3){
                    contadorTeclado ++;
                    serTeclado->escribir("listo\n");
                    qDebug() << "Vuelve a mandar solicitud a teclado";
                }
                else{
                    qDebug() << "Termina tiempo de espera, no se pudo conectar el teclado";
                    monitor->muestraAviso("Error en el teclado");
                    timerTeclado->stop();
                }
            }
            else{
                serTeclado->escribir("config\n");
            }
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void MainWindow::edoTeclaActivo(bool estado){
    try {
        avisoTeclaActivo = estado;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void MainWindow::edoPresiActivo(bool estado){
    try {
        avisoPresiActivo = estado;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void MainWindow::edoVentiActivo(bool estado){
    try {
        avisoVentiActivo = estado;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void MainWindow::beep(){
    try {
        QProcess::execute("amixer --quiet set Master 90%");
        QProcess::execute(QString("play -v 0.1 -nq -t alsa synth %1 sine %2").arg(QString::number(duration), QString::number(freq)));
        QProcess::execute("amixer --quiet set Master 100%");
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void MainWindow::tecladoVirtual(QString trama){
    try {
        //QString trama = serTeclado->leer();
        if(!avisoVentiActivo && !avisoPresiActivo && !avisoTeclaActivo && ! monitor->ventiladorInoperante && monitor->cargaMonitorListo){
            //qDebug() << "teclado------1";
            if(trama != ""){
                beep();
                //qDebug() << "teclado------2";
                if(monitor->ventanaAbierta){
                    //qDebug() << "teclado------3";
                    if(monitor->menu != nullptr && ! monitor->menu->isHidden()){
                        monitor->tecla_menu(trama);
                        //qDebug() << "teclado------4";
                    }
                    else if(monitor->pruebas != nullptr && ! monitor->pruebas->isHidden() && ! monitor->infoAbierta){
                        monitor->tecla_pruebas(trama);
                        //qDebug() << "teclado------5";
                    }
                    else if(monitor->calibrar != nullptr && ! monitor->calibrar->isHidden()){
                        monitor->tecla_calibracion(trama);
                        //qDebug() << "teclado------6";
                    }
                    else if(monitor->ventana_confirmacion != nullptr && ! monitor->ventana_confirmacion->isHidden()){
                        monitor->tecla_confirmacion(trama);
                        //qDebug() << "teclado------7";
                    }
                    else if(monitor->infoAbierta){
                        monitor->tecla_info(trama);
                        //qDebug() << "teclado------8";
                    }
                    /*else{
                        qDebug() << "teclado------9";
                    }*/
                }
                else{
                    //qDebug() << "teclado------10";
                    if(trama == "cfg"){
                        qDebug() << "[MainWindow] teclado cfg";
                        tecladoComandoRecibido = true;
                    }
                    else if(trama == "MPR_timeout"){
                        qDebug() << "[MainWindow] Error teclado";
                        monitor->muestraAviso("ERROR TECLADO\n REVISAR SENSOR");
                    }
                    else if(trama.contains("listo")){
                        tecladoConectado = true;
                        qDebug() << "[MainWindow] Teclado dice que esta listo";
                        if(trama.mid(6) != monitor->versionTecladoEsperada){
                            monitor->muestraAviso("VERSION OBSOLETA\n ACTUALIZAR TECLADO");
                        }
                        else{
                            monitor->versionTeclado = trama.mid(6);
                            monitor->tecladoListo = true;
                        }
                    }
                    else if(trama == "error"){
                        qDebug() << "[MainWindow] Hubo un error en el teclado";
                    }

                    //
                    if(monitor->inicializacion){
                        if(contenedorPrincipal->currentWidget() == monitor){
                            teclado(trama);
                        }
                        else if(contenedorPrincipal->currentWidget() == configuracion){
                            if(trama == "mon"){
                                abrePantallaMonitor();
                            }
                            else if(trama == "ala"){
                                abrePantallaAlarmas();
                            }
                            else{
                                configuracion->teclado(trama);
                            }
                        }
                        else if(contenedorPrincipal->currentWidget() == alarmas){
                            if(trama == "con"){
                                abrePantallaConfiguracion();
                            }
                            else if(trama == "mon"){
                                abrePantallaMonitor();
                            }
                            else{
                                alarmas->teclado(trama);
                            }
                        }
                    }
                }
            }
        }
        else{
            //qDebug() << "teclado------5";
            if(trama != ""){
                if(monitor->ventiladorInoperante){
                    if(monitor->contador_apagar < 3){
                        monitor->contador_apagar ++;
                    }
                    else{
                        qDebug() << "[MainWindow] Apagar por teclado!!!";
                        QProcess::execute("sudo shutdown now");
                    }
                }
            }
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void MainWindow::recteclado(QString trama){
    try {
        //QString trama = serTeclado->leer();
        if(!avisoVentiActivo && !avisoPresiActivo && !avisoTeclaActivo && monitor->cargaMonitorListo){// && ! monitor->ventiladorInoperante
            //qDebug() << "teclado------1";
            if(trama != ""){
                beep();
                //qDebug() << "teclado------2";
                if(monitor->ventanaAbierta){
                    //qDebug() << "teclado------3";
                    if(monitor->menu != nullptr && ! monitor->menu->isHidden()){
                        monitor->tecla_menu(trama);
                        //qDebug() << "teclado------4";
                    }
                    else if(monitor->pruebas != nullptr && ! monitor->pruebas->isHidden() && ! monitor->infoAbierta){
                        monitor->tecla_pruebas(trama);
                        //qDebug() << "teclado------5";
                    }
                    else if(monitor->calibrar != nullptr && ! monitor->calibrar->isHidden()){
                        monitor->tecla_calibracion(trama);
                        //qDebug() << "teclado------6";
                    }
                    else if(monitor->ventana_confirmacion != nullptr && ! monitor->ventana_confirmacion->isHidden()){
                        monitor->tecla_confirmacion(trama);
                        //qDebug() << "teclado------7";
                    }
                    else if(monitor->infoAbierta){
                        monitor->tecla_info(trama);
                        //qDebug() << "teclado------8";
                    }
                    /*else{
                        qDebug() << "teclado------9";
                    }*/
                    serTeclado->serPuerto->clear();
                }
                else{
                    //qDebug() << "teclado------4";
                    if(trama == "cfg"){
                        qDebug() << "[MainWindow] teclado cfg";
                        tecladoComandoRecibido = true;
                    }
                    else if(trama == "MPR_timeout"){
                        qDebug() << "[MainWindow] Error teclado";
                        monitor->muestraAviso("ERROR TECLADO\n REVISAR SENSOR");
                    }
                    else if(trama.contains("listo")){
                        tecladoConectado = true;
                        qDebug() << "[MainWindow] Teclado dice que esta listo";
                        if(trama.mid(6) != monitor->versionTecladoEsperada){
                            monitor->muestraAviso("VERSION OBSOLETA\nACTUALIZAR TECLADO");
                        }
                        else{
                            monitor->versionTeclado = trama.mid(6);
                            monitor->tecladoListo = true;
                        }
                    }
                    else if(trama == "error"){
                        qDebug() << "[MainWindow] Hubo un error en el teclado";
                    }

                    //
                    if(monitor->inicializacion){
                        if(contenedorPrincipal->currentWidget() == monitor){
                            teclado(trama);
                            serTeclado->serPuerto->clear();
                        }
                        else if(contenedorPrincipal->currentWidget() == configuracion){
                            //qDebug() << "keyboard-1";
                            if(monitor->isConfigKeyboard){
                                //qDebug() << "keyboard-2";
                                if(trama.contains("Umbral:")){
                                    //monitor->revisar_cal_teclado(trama);
                                    monitor->check_umbral_keyboard(trama);
                                }
                                else if(trama.contains("Modo:")){
                                    monitor->check_mode_keyboard(trama);
                                }
                                else if(trama.contains("Umbral")){
                                    monitor->check_umbral_key(trama);
                                }
                                else{
                                    //qDebug() << "keyboard-3";
                                    monitor->watchDataKeyboard(trama);
                                }
                            }
                            else{
                                //qDebug() << "keyboard-4";
                                if(trama == "mon"){
                                    abrePantallaMonitor();
                                }
                                else if(trama == "ala"){
                                    abrePantallaAlarmas();
                                }
                                else if(trama.contains("Umbral:")){
                                    //monitor->revisar_cal_teclado(trama);
                                    monitor->check_umbral_keyboard(trama);
                                }
                                else if(trama.contains("Modo:")){
                                    monitor->check_mode_keyboard(trama);
                                }
                                else if(trama.contains("Umbral")){
                                    monitor->check_umbral_key(trama);
                                }
                                else{
                                    configuracion->teclado(trama);
                                }
                            }
                            serTeclado->serPuerto->clear();
                        }
                        else if(contenedorPrincipal->currentWidget() == alarmas){
                            if(trama == "con"){
                                abrePantallaConfiguracion();
                            }
                            else if(trama == "mon"){
                                abrePantallaMonitor();
                            }
                            else{
                                alarmas->teclado(trama);
                            }
                            serTeclado->serPuerto->clear();
                        }
                    }
                }
            }
        }
        else{
            //qDebug() << "teclado------5";
            if(trama != ""){
                if(monitor->ventiladorInoperante){
                    if(monitor->contador_apagar < 3){
                        monitor->contador_apagar ++;
                    }
                    else{
                        QProcess::execute("sudo shutdown now");
                    }
                }
                serTeclado->serPuerto->clear();
            }
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void MainWindow::teclado(QString trama){
    try {
        if(trama == "con"){
            abrePantallaConfiguracion();
        }
        else if(trama == "inidet"){
            if(monitor->estadoVentilador){
                monitor->espera_parar = true;
                monitor->mostrar_confirmacion("¿Está seguro de parar el ventilador?");
            }
            else{
                monitor->espera_parar = true;
                monitor->mostrar_confirmacion("¿Está seguro de iniciar el ventilador?");
            }
        }
        else if(trama == "ala"){
            abrePantallaAlarmas();
        }
        else{
            monitor->teclado(trama);
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void MainWindow::muestraAviso(QString mensajes){
    try {
        if(vAviso == nullptr){
            //ventiladorInoperante = true;
            vAviso = new VentanaAviso(this, 500, 300);
            QStringList *tt = new QStringList{"ERROR DE LA TARJETA DE TECLADO", "", "", "", mensajes};
            vAviso->textoMostrar(tt);
            vAviso->move(0,0);
            vAviso->resize(monitor->mainwindow->width(), monitor->mainwindow->height());
            vAviso->show();
            monitor->alarmaControl->iniciaAlarma(monitor->alarmaControl->INOPERANTE);
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void MainWindow::_closepopup(){
    try {
        vAviso->close();
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void MainWindow::obtener_modo(){
    try {
        QString modo = monitor->consul->leer_modo();
        //monitor->modoVent = modo[2];
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void MainWindow::abrePantallaMonitor(){
    try {
        contenedorPrincipal->setCurrentWidget(monitor);
        obtener_modo();
        monitor->actualizarParametros();
        monitor->label_Modo->setText(monitor->modoVentilador);
        reloj->asignaLabel(monitor->label_fecha);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void MainWindow::abrePantallaAlarmas(){
    try {
        monitor->actualizarParametros();
        alarmas->actualizaVentana();
        contenedorPrincipal->setCurrentWidget(alarmas);
        reloj->asignaLabel(alarmas->label_fecha);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void MainWindow::abrePantallaConfiguracion(){
    try {
        contenedorPrincipal->setCurrentWidget(configuracion);
        monitor->actualizarParametros();
        configuracion->llenarConfiguracion();
        reloj->asignaLabel(configuracion->label_Version);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

/*void MainWindow::calibrarTeclado(QString trama){
    try {
        serTeclado->escribir(trama);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void MainWindow::get_mode_keyboard_command(QString trama){
    try {
        serTeclado->escribir(trama);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void MainWindow::get_umbral_key_command(QString trama){
    try {
        serTeclado->escribir(trama);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void MainWindow::get_umbral_keyboard_command(QString trama){
    try {
        serTeclado->escribir(trama);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}*/

void MainWindow::send_frame_keyboard(QString trama){
    try {
        serTeclado->escribir(trama);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void MainWindow::set_date(QString trama){
    try {
        //poner el comando date --set ...
        ///QProcess process;
        //QString command = "sudo date -s '" + trama + "'";
        //QString command = "sudo /bin/bash -c date -s '" + trama + "'";
        QString command = "sudo date --set='" + trama + "'";
        qDebug() << "[RELOJ] set date comando: " << command;
        /*process.start(command);
        process.waitForFinished(-1);
        QString stdput_process = process.readAllStandardOutput();
        QString stderror_process = process.readAllStandardError();
        if(stderror_process.size() > 0){
            qDebug() << "[RELOJ] Error al actualizar fecha y hora: " << stderror_process;
        }
        else{
            qDebug() << "[RELOJ] Se actualiza la fecha y hora con éxito: " << stdput_process;
        }*/
        //
        //int res = QProcess::execute(command);
        int res = system(command.toStdString().c_str());
        if(res == -2){
            qDebug() << "[RELOJ] NO inicia execute";
        }
        else if(res == -1){
            qDebug() << "[RELOJ] Crash execute";
        }
        else if(res == 0){
            qDebug() << "[RELOJ] OK execute";
        }
        else{
            qDebug() << "[SET DATE] execute: " << res;
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void MainWindow::set_watch(QString trama){
    try {
        //qDebug() << "set_watch: " << trama;
        bool rtc_ok = false;
        bool date_ok = false;
        QDateTime dateCurrent;
        QDateTime dateRTC;
        //separar trama
        QStringList partes = trama.split(',');
        if(partes.size() == 2){
            QString fecha_last_event = partes.at(0); //yyyy-mm-dd
            QString hora_last_event = partes.at(1).split(".").at(0); //hh:mm:ss
            qDebug() << "[RELOJ] fecha last_event: " + fecha_last_event + " "+ hora_last_event;
            QDateTime dateLastEvent = QDateTime::fromString(fecha_last_event + " " + hora_last_event, "yyyy-MM-dd hh:mm:ss");
            dateLastEvent.setTimeSpec(Qt::UTC);
            QString tt = dateLastEvent.toString("d MMM yyyy hh:mm:ss");
            //qDebug() << "[RELOJ] fecha last_event-2: " + tt;
            //obtener fechas del sistema
            QProcess process;
            process.start("date");
            if(process.waitForFinished(3500)){
                QString stdput_process = process.readAllStandardOutput();
                QString stderror_process = process.readAllStandardError();
                qDebug() << "[RELOJ] fecha date: " + stdput_process;

                if(stderror_process.size() == 0 ){
                    QStringList pparts = stdput_process.split(' ');
                    if(pparts.size() >= 6){
                        QString fecha_date = pparts.at(1) + " " + pparts.at(2) + " " + pparts.at(5).mid(0,4); // MMMM dd yyyy
                        QString hora_date = pparts.at(3); //hh:mm:ss
                        //qDebug() << "[RELOJ] fecha date2: " + fecha_date + " " + hora_date;
                        dateCurrent = QDateTime::currentDateTime();//Utc //"MM/dd/yy hh:mm:ss" //QDateTime::fromString(fecha_date + " "+ hora_date, "MMM dd yyyy hh:mm:ss");
                        dateCurrent.setTimeSpec(Qt::UTC);
                        QString ttt = dateCurrent.toString("d MMM yyyy hh:mm:ss");
                        //qDebug() << "[RELOJ] fecha dateCurrent-2: " + ttt;
                        //qDebug() << "Convierte date";
                        date_ok = true;
                    }
                    else{
                        qDebug() << "[RELOJ] Error date 2: " + stderror_process;
                        reloj->set_color_label("red");
                    }
                }
                else{
                    qDebug() << "[RELOJ] Error date: " + stderror_process;
                    reloj->set_color_label("red");
                }
                //antes de esto, preguntar si está conectado por i2c
                QProcess find_i2c;
                find_i2c.start("i2cdetect -y 1");
                if(find_i2c.waitForFinished(3500)){
                    QString stdout_process_i2cfind = find_i2c.readAllStandardOutput();
                    QString stderror_process_i2cfind = find_i2c.readAllStandardError();
                    if(stderror_process_i2cfind.size() > 0){
                        //error en el comando
                        qDebug() << "[RELOJ] Error buscar i2c: " << stderror_process_i2cfind;
                        reloj->set_color_label("red");
                    }
                    else{
                        //acepta comando, ver salida
                        //qDebug() << "[RELOJ] Salida i2c: " << stdout_process_i2cfind;
                        if(stdout_process_i2cfind.contains("UU")){
                            qDebug() << "[RELOJ] RTC conectado";
                            //obtener fecha del RTc
                            QProcess process_rtc;
                            process_rtc.start("sudo hwclock -r");
                            if(process_rtc.waitForFinished(3500)){
                                QString stdput_process_rtc = process_rtc.readAllStandardOutput();
                                QString stderror_process_rtc = process_rtc.readAllStandardError();
                                qDebug() << "[RELOJ] fecha date rtc: " + stdput_process_rtc;
                                if(stderror_process_rtc.size() == 0){
                                    QStringList ppparts = stdput_process_rtc.split(' ');
                                    if(ppparts.size() >= 2){
                                        QString fecha_rtc = ppparts.at(0);
                                        QString hora_rtc = ppparts.at(1).split('.').at(0);
                                        dateRTC = QDateTime::fromString(fecha_rtc + " "+ hora_rtc, "yyyy-MM-dd hh:mm:ss");
                                        dateRTC.setTimeSpec(Qt::UTC);
                                        QString tttt = dateRTC.toString("d MMM yyyy hh:mm:ss");
                                        //qDebug() << "[RELOJ] fecha dateRTC-2: " + tttt;
                                        //qDebug() << "Convierte date RTC";
                                        rtc_ok = true;
                                    }
                                    else{
                                        qDebug() << "[RELOJ] Error fecha rtc 2: " + stderror_process_rtc;
                                        reloj->set_color_label("red");
                                    }
                                }
                                else{
                                    qDebug() << "[RELOJ] Error fecha rtc: " + stderror_process_rtc;
                                    reloj->set_color_label("red");
                                }
                            }
                            else{
                                qDebug() << "[RELOJ] command hwclock ERROR";
                                reloj->set_color_label("red");
                            }
                        }
                        else{
                            qDebug() << "[RELOJ] RTC desconectado";
                            reloj->set_color_label("red");
                        }
                    }
                }
                else{
                    qDebug() << "[RELOJ] command i2cdetect ERROR";
                    reloj->set_color_label("red");
                }


                //hacer las comparciones
                if(rtc_ok && date_ok){
                    // last_event > date
                    //qDebug() << "[RELOJ] valor: " + QString::number(dateCurrent.msecsTo(dateRTC));

                    //debug
                    //qDebug() << "[RELOJ] lastevent to current" << dateLastEvent.msecsTo(dateCurrent);
                    //qDebug() << "[RELOJ] dateCurrent to dateRTC" << dateCurrent.msecsTo(dateRTC);
                    //qDebug() << "[RELOJ] lastevent to dateRTC" << dateLastEvent.msecsTo(dateRTC) ;
                    //dateLastEvent.msecsTo(dateRTC)

                    if(dateLastEvent.msecsTo(dateCurrent) > 0){
                        //La hora es probable que esté correcta, ahora hay que preguntar por la del RTC respecto a current
                        if(dateCurrent.msecsTo(dateRTC) > 0){
                            //actualizar la current con la dle RTC
                            //el comando es: date --set="2 OCT 2006 18:00:00"
                            QString temp = dateRTC.toString("d MMM yyyy hh:mm:ss");
                            qDebug() << "[RELOJ] Hora 1-> " + temp;
                            set_date(temp);
                        }
                        else{
                            qDebug() << "[RELOJ] Hora correcta";
                        }
                    }
                    else{
                        //No es correcta la hora del ventilador
                        //preguntar por la del RTC respecto al ultimo evento
                        if(dateLastEvent.msecsTo(dateRTC) > 0){
                            //el RTC es probable que esté bien, entonces poner esa hora al sistema
                            QString temp = dateRTC.toString("d MMM yyyy hh:mm:ss");
                            qDebug() << "[RELOJ] Hora 2-> " + temp;
                            set_date(temp);
                        }
                        else{
                            //tambien esta mal, corregir hora, activar amarillo
                            reloj->set_color_label("yellow");
                            qDebug() << "[RELOJ] Advertencia";
                        }
                    }
                }
                else{
                    //error, poner en rojo
                    reloj->set_color_label("red");
                    qDebug() << "[RELOJ] Error";
                }
            }
            else{
                qDebug() << "[RELOJ] command date ERROR ";
                reloj->set_color_label("red");
            }
        }

    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void MainWindow::get_last_event(){
    try {
        //pruebas
        //qDebug() << "get_last_event mainwindow";
        QStringList last_event = consul->obtener_ultimo_evento();
        if(last_event.size() >= 1){
            set_watch(last_event.at(0));
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}
