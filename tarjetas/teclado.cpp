#include "teclado.h"

Teclado::Teclado(bool debug) : QWidget() //, void *funcion
{
    try {
        //this->padre = parent;
        //this->mainwindow = mainwindow;
        this->puerto = "teclado";
        //this->funcion = funcion;
        this->debug = debug;
        serPuerto =  new QSerialPort;
        serPuerto->setPortName(this->puerto);
        serPuerto->setBaudRate(QSerialPort::Baud115200);
        //connect(serPuerto,SIGNAL(readyRead()), this,SLOT(this->funcion()));
        connect(serPuerto,SIGNAL(readyRead()), this,SLOT(leer()));

        connect(serPuerto, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(errores(QSerialPort::SerialPortError)));
        avisoAbierto = false;
        monitor = new QTimer; //(padre);
        monitor->start(1000);
        connect(monitor, SIGNAL(timeout()), this, SLOT(run()));
        primera = true;
        //listaErrores = {"NoError","DeviceNotFoundError","PermissionError","OpenError","ParityError","FramingError","BreakConditionError","WriteError","ReadError","ResourceError","UnsupportedOperationError","UnknownError","TimeoutError","NotOpenError"};
        strDisp = "Teclado - ";
        contador_errores = 0;
        if(debug){
            msg("puerto" + puerto);
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

/*void Teclado::asignaPadre(MainWindow *mainwindow){
    try {
        this->mainwindow = mainwindow;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}*/

bool Teclado::estado(){
    try {
        return serPuerto->isOpen();
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return false;
    }
}

void Teclado::escribir(QString datos){
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

void Teclado::leer(){
    try {
        if(serPuerto->isOpen()){
            while(serPuerto->canReadLine()){
                try {
                    QString trama = serPuerto->readLine().data();
                    QStringList ll = trama.split("\n");
                    if(debug){
                        int espera = serPuerto->bytesAvailable();
                        msg("recibido: " + ll.at(0)+ ", datos: " + QString::number(espera));
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

void Teclado::errores(QSerialPort::SerialPortError error){
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
                if(contador_errores < 5){
                    contador_errores += 1;
                }
                else{
                    /*if(mainwindow->vAviso == nullptr){
                        mainwindow->muestraAviso("DESCONEXIÓN TECLADO");
                    }*/
                    emit muestraAviso("DESCONEXIÓN TECLADO");
                }
            }
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void Teclado::_closepopup(){
    try {
        //mainwindow->vAviso.close();
        emit cierraAviso();
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void Teclado::run(){
    try {
        bool estado = serPuerto->isOpen();
        if(estado){
            if(avisoAbierto){
                avisoAbierto = false;
                _closepopup();
                //mainwindow->edoTeclaActivo(false);
                emit estadoTeclaActivo(false);
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
void Teclado::msg(QString mensaje){
    try {
        qDebug() << strDisp + mensaje + " ";
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void Teclado::msge(QString mensaje, std::exception error){
    try {
        qDebug() << strDisp + mensaje + " " + error.what();
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}
