#include "mainwindow.h"

MainWindow::MainWindow(ServerWS *server, QWidget *parent, bool debug_t, bool debug_c, bool debug_s)
    : QMainWindow(parent)
{
    try {
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

        //aqui debería ir la inicialización de las consultas a sqlite
        consul = new Consultas;
        bool conectado = consul->conecta();
        if(conectado){
            consul->cerrar();
            //aquí agregar las pantallas
            //qDebug() << "Se crea pantalla monitor";
            monitor = new Monitor(this, consul, debug_c, debug_s);

            connect(monitor, SIGNAL(calTeclado(QString)), this, SLOT(calibrarTeclado(QString)));

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

            reloj = new Reloj;
            reloj->asignaLabel(monitor->label_fecha);
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
        if(!avisoVentiActivo && !avisoPresiActivo && !avisoTeclaActivo && ! monitor->ventiladorInoperante){
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
                        qDebug() << "teclado cfg";
                        tecladoComandoRecibido = true;
                    }
                    else if(trama == "MPR_timeout"){
                        qDebug() << "Error teclado";
                        monitor->muestraAviso("ERROR TECLADO\n REVISAR SENSOR");
                    }
                    else if(trama.contains("listo")){
                        tecladoConectado = true;
                        qDebug() << "Teclado dice que esta listo";
                        if(trama.mid(6) != monitor->versionTecladoEsperada){
                            monitor->muestraAviso("VERSION OBSOLETA\n ACTUALIZAR TECLADO");
                        }
                        else{
                            monitor->versionTeclado = trama.mid(6);
                            monitor->tecladoListo = true;
                        }
                    }
                    else if(trama == "error"){
                        qDebug() << "Hubo un error en el teclado";
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
                        qDebug() << "Apagar por teclado!!!";
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
        if(!avisoVentiActivo && !avisoPresiActivo && !avisoTeclaActivo && ! monitor->ventiladorInoperante){
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
                        qDebug() << "teclado cfg";
                        tecladoComandoRecibido = true;
                    }
                    else if(trama == "MPR_timeout"){
                        qDebug() << "Error teclado";
                        monitor->muestraAviso("ERROR TECLADO\n REVISAR SENSOR");
                    }
                    else if(trama.contains("listo")){
                        tecladoConectado = true;
                        qDebug() << "Teclado dice que esta listo";
                        if(trama.mid(6) != monitor->versionTecladoEsperada){
                            monitor->muestraAviso("VERSION OBSOLETA\nACTUALIZAR TECLADO");
                        }
                        else{
                            monitor->versionTeclado = trama.mid(6);
                            monitor->tecladoListo = true;
                        }
                    }
                    else if(trama == "error"){
                        qDebug() << "Hubo un error en el teclado";
                    }

                    //
                    if(monitor->inicializacion){
                        if(contenedorPrincipal->currentWidget() == monitor){
                            teclado(trama);
                            serTeclado->serPuerto->clear();
                        }
                        else if(contenedorPrincipal->currentWidget() == configuracion){
                            if(trama == "mon"){
                                abrePantallaMonitor();
                            }
                            else if(trama == "ala"){
                                abrePantallaAlarmas();
                            }
                            else if(trama.contains("Umbral:")){
                                monitor->revisar_cal_teclado(trama);
                            }
                            else{
                                configuracion->teclado(trama);
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

void MainWindow::calibrarTeclado(QString trama){
    try {
        serTeclado->escribir(trama);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}


