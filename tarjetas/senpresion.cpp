#include "senpresion.h"

SenPresion::SenPresion(bool debug)
{
    try {
        // : QWidget()
        //parent
        //QWidget *parent,
        //this->parent = parent;
        //this->mon = (Monitor*) mon;

        this->puerto = "senpresion";
        //, void *funcion
        //this->funcion = funcion;
        this->debug = debug;
        serPuerto =  new QSerialPort;
        serPuerto->setPortName(this->puerto);
        serPuerto->setBaudRate(QSerialPort::Baud115200);
        //connect(serPuerto,SIGNAL(readyRead()), this,SLOT(this->funcion()));
        connect(serPuerto,SIGNAL(readyRead()), this,SLOT(leer()));

        connect(serPuerto, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(errores(QSerialPort::SerialPortError)));
        avisoAbierto = false;
        monitor = new QTimer; //mon
        monitor->start(1000);
        mconfig = new QTimer; //(mon)
        connect(mconfig, SIGNAL(timeout()), this, SLOT(configura()));
        connect(monitor, SIGNAL(timeout()), this, SLOT(run()));
        primera = true;
        corriendo = false;
        tramaConf = "";
        //listaErrores = {"NoError","DeviceNotFoundError","PermissionError","OpenError","ParityError","FramingError","BreakConditionError","WriteError","ReadError","ResourceError","UnsupportedOperationError","UnknownError","TimeoutError","NotOpenError"};
        strDisp = "[SenPresion] - ";
        contador_errores = 0;
        ready = false;
        if(debug){
            msg("puerto: " + puerto);
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

/*void SenPresion::asignaPadre(Monitor* mon){
    try {
        this->mon = mon;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}*/

void SenPresion::set_ready(bool state){
    try {
        ready = state;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

bool SenPresion::estado(){
    try {
        return serPuerto->isOpen();
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return false;
    }
}

void SenPresion::escribir(QString datos){
    try {
        if(serPuerto->isOpen()){
            if(debug){
                msg("Envia: "+datos);
            }
            serPuerto->write(datos.toStdString().c_str());
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void SenPresion::leer(){
    try {
        if(ready){
            if(serPuerto->isOpen()){
                while(serPuerto->canReadLine()){
                    try {
                        QString trama = serPuerto->readLine().data();
                        QStringList ll = trama.split("\n");
                        int num = serPuerto->bytesAvailable();
                        if(debug){
                            msg("recibido: " + ll.at(0));
                        }
                        if(num > 1000){
                            QString basura = serPuerto->readAll();
                            if(debug){
                                msg("limpiar buffer de :" + QString::number(num));
                            }
                        }
                        //return ll.at(0);
                        emit enviaLinea(ll.at(0));
                    }  catch (std::exception &e) {
                        msge("Error: ", e);
                        emit enviaLinea("");
                    }
                }
                emit enviaLinea("");
            }
            else{
                emit enviaLinea("");
            }
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        emit enviaLinea("");
    }
}

void SenPresion::errores(QSerialPort::SerialPortError error){
    try {
        if(error != 0 && error !=8){
            if(debug){
                msg("Ocurrio un error: "+ listaErrores.at(error));
            }
            if(!avisoAbierto){
                if(debug){
                    msg("Mostrando la pantalla de aviso");
                }
                if(serPuerto->isOpen()){
                    serPuerto->close();
                    if(debug){
                        msg("Cerrando puerto");
                    }
                }
                //
                if(contador_errores < 3){
                    contador_errores += 1;
                }
                else{
                    emit muestraAviso("DESCONEXIÓN SENSORES");
                    /*if(mon->vAviso == nullptr){
                        mon->muestraAviso("DESCONEXIÓN SENSORES");
                    }*/
                }
            }
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void SenPresion::_closepopup(){
    try {
        //mon->vAviso->close();
        emit cierraAviso();
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void SenPresion::configura(){
    try {
        mconfig->stop();
        if(serPuerto->isOpen()){
            serPuerto->write(tramaConf.toStdString().c_str());
            QThread::sleep(2);
            serPuerto->write(tramaConf.toStdString().c_str());
            if(debug){
                msg("Configurar presion!");
            }
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void SenPresion::run(){
    try {
        bool estado = serPuerto->isOpen();
        if(estado){
            if(avisoAbierto){
                avisoAbierto = false;
                _closepopup();
                //mon->edoPresiActivo(false);
                //mon->iniciaMonSensores();
                emit iniciaMonitoreo();
                contador_errores = 0;
                if(debug){
                    msg("Cerrando pantalla de aviso");
                    msg("conectado");
                }
            }
        }
        else{
            if(primera){
                serPuerto->open(QIODevice::ReadWrite);
                if(serPuerto->isOpen()){
                    //mon->iniciaMonSensores();
                    emit iniciaMonitoreo();
                    if(debug){
                        msg("conectado");
                    }
                    primera = false;
                }
            }
            else{
                serPuerto->open(QIODevice::ReadWrite);
                if(debug){
                    msg("No se ha conectado aun");
                    msg("Reintentando conexion");
                }
            }
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void SenPresion::iniciar_sensor_presion(){
    try {
        if(serPuerto->isOpen()){
            if(!corriendo){
                if(debug){
                    msg("iniciar sensor de presion A1");
                }
                corriendo = true;
                serPuerto->write("A1\n");
            }
            else{
                if(debug){
                    msg("el sensor de presion ya esta corriendo");
                }
                serPuerto->write("A1\n");
            }
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void SenPresion::detener_sensor_presion(){
    try {
        if(serPuerto->isOpen()){
            if(corriendo){
                if(debug){
                    msg("detener sensor de presion: A0");
                }
                corriendo = false;
                serPuerto->write("A0\n");
            }
            else{
                if(debug){
                    msg("el sensor de presion ya esta detenido");
                }
                serPuerto->write("A0\n");
            }
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void SenPresion::configurarSenPresion(QString trama){
    try {
        tramaConf = trama;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void SenPresion::msg(QString mensaje){
    try {
        qDebug() << strDisp + mensaje + " ";
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void SenPresion::msge(QString mensaje, std::exception error){
    try {
        qDebug() << strDisp + mensaje + " " + error.what();
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}
