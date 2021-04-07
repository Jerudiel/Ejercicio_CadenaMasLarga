#include "ventilador.h"

Ventilador::Ventilador(bool debug) : QWidget() // parent //QWidget *parent, Monitor *mon, bool debug
{
    try {
        //this->padre = parent;
        //this->mon = mon;
        this->puerto = "ventilador";
        //, void *funcion
        //this->funcion = funcion;
        this->debug = debug;
        serPuerto =  new QSerialPort;
        serPuerto->setPortName(this->puerto);
        serPuerto->setBaudRate(QSerialPort::Baud115200);
        //connect(serPuerto,SIGNAL(readyRead()), this,SLOT(this->funcion()));
        //conectar readyRead al slot
        connect(serPuerto,SIGNAL(readyRead()), this,SLOT(leer()));

        connect(serPuerto, SIGNAL(errorOccurred(QSerialPort::SerialPortError)), this, SLOT(errores(QSerialPort::SerialPortError)));
        avisoAbierto = false;
        monitor = new QTimer; //(padre)
        monitor->start(1000);
        connect(monitor, SIGNAL(timeout()), this, SLOT(run()));
        primera = true;
        corriendo = false;
        tramaConfiguracion = "";
        //listaErrores = {"NoError","DeviceNotFoundError","PermissionError","OpenError","ParityError","FramingError","BreakConditionError","WriteError","ReadError","ResourceError","UnsupportedOperationError","UnknownError","TimeoutError","NotOpenError"};
        strDisp = "Ventilador - ";
        contador_errores = 0;
        if(debug){
            msg("puerto: " + puerto);
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

/*void Ventilador::asignaPadre(Monitor* mon){
    try {
        this->mon = mon;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}*/

bool Ventilador::estaCorriendo(){
    try {
        return corriendo;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return false;
    }
}

void Ventilador::actualizaTrama(QString trama){
    try {
        tramaConfiguracion = trama;
        if(serPuerto->isOpen()){
            if(corriendo){
                if(debug){
                    msg("Ajustando parametros de ventilador");
                }
                serPuerto->write(tramaConfiguracion.toStdString().c_str());
            }
            else{
                if(debug){
                    msg("Ventilador detenido");
                }
                iniciar_ventilador(trama);
            }
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Ventilador::ajusta_ventilador(QString trama){
    try {
        tramaConfiguracion = trama;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Ventilador::cambio_giro(QString trama){
    try {
        tramaConfiguracion = trama;
        if(serPuerto->isOpen()){
            if(corriendo){
                if(debug){
                    msg("Cambio de giro ventilador");
                }
                serPuerto->write(tramaConfiguracion.toStdString().c_str());
            }
            else{
                if(debug){
                    msg("Sin cambio de giro, ventilador detenido");
                }
                iniciar_ventilador(trama);
            }
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Ventilador::envia_trama_config(QString trama){
    try {
        tramaConfiguracion = trama;
        if(serPuerto->isOpen()){
            if(debug){
                msg("Trama de configuracion ventilador: "+trama);
            }
            serPuerto->write(tramaConfiguracion.toStdString().c_str());
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Ventilador::iniciar_ventilador(QString trama){
    try {
        tramaConfiguracion = trama;
        if(serPuerto->isOpen()){
            if(debug){
                msg("Iniciando ventilador: "+trama);
            }
            corriendo = true;
            serPuerto->write(tramaConfiguracion.toStdString().c_str());
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Ventilador::detener_ventilador(QString trama){
    try {
        try {
            tramaConfiguracion = trama;
            if(serPuerto->isOpen()){
                if(debug){
                    msg("Detener ventilador: "+trama);
                }
                corriendo = false;
                serPuerto->write(tramaConfiguracion.toStdString().c_str());
            }
        }  catch (std::exception &e) {
            qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

bool Ventilador::estado(){
    try {
        return serPuerto->isOpen();
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return false;
    }
}

void Ventilador::leer(){
    try {
        if(serPuerto->isOpen()){
            while(serPuerto->canReadLine()){
                try {
                    QString trama = serPuerto->readLine().data();
                    QStringList ll = trama.split("\n");
                    if(debug){
                        int espera = serPuerto->bytesAvailable();
                        msg("recibido: " + ll.at(0) + ", datos: " + QString::number(espera));
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
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        emit enviaLinea("");
    }
}

void Ventilador::errores(QSerialPort::SerialPortError error){
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
                    emit muestraAviso("DESCONEXIÓN CONTROL");
                    /*if(mon->vAvisoV == nullptr){
                        mon->muestraAvisoVentilador("DESCONEXIÓN CONTROL");
                    }*/
                }
            }
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void Ventilador::_closepopup(){
    try {
        //mon->vAvisoV->close();
        emit cierraAviso();
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void Ventilador::run(){
    try {
        bool estado = serPuerto->isOpen();
        if(estado){
            if(avisoAbierto){
                avisoAbierto = false;
                _closepopup();
                //mon->edoVentiActivo(false);
                emit estadoVentiActivo(false);
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

void Ventilador::msg(QString mensaje){
    try {
        QDateTime dateTime = QDateTime::currentDateTime();
        QString dateTimeString = dateTime.toString("yyyy-MM-dd hh:mm:ss.zzz");
        qDebug() << dateTimeString + " " + strDisp + mensaje + " ";
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void Ventilador::msge(QString mensaje, std::exception error){
    try {
        qDebug() << strDisp + mensaje + " " + error.what();
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}
