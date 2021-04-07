#include "ventanaavisotest.h"

VentanaAvisoTest::VentanaAvisoTest(QWidget *parent, int width, int height, QString titulo) : QWidget(parent)
{
    try {
        btn = "border: 2px solid rgb(145,145,145); background-color: rgb(145,145,145); border-radius: 5px; color: black;";
        btnSeleccionado = "border: 2px solid rgb(255,112,61); background-color: rgb(145,145,145); border-radius: 5px; color: black;";

        setWindowFlags(Qt::FramelessWindowHint);
        setAttribute(Qt::WA_TranslucentBackground);

        pwidth = width;
        pheight = height;

        int sangria_x = 25;
        offset_x = 262 + sangria_x;
        int sangria_y = 65;
        offset_y = 175 + sangria_y;

        fillColor = QColor(30, 30, 30, 120);
        penColor = QColor("#333333");

        popup_fillColor = QColor("#D5D8DC");
        popup_penColor = QColor(200, 200, 200, 255);

        titulo_color = QColor(0, 0, 255);
        mensaje_color = QColor(70, 70, 70);

        proceso_color = QColor(0, 0, 255);
        ok_color = QColor(0, 255, 0);
        error_color = QColor(255, 0, 0);

        //self.signals = VentanaAvisoSignalsTest()
        this->titulo = titulo;
        mensajes = nullptr;

        fuente = new QFont;
        fuente->setPointSize(11);
        fuente->setBold(true);

        listaMensajes = new QStringList;
        listaEstados = new QStringList;
        estadoFinal = false;

        btn_ok = new QPushButton(this);
        btn_ok->setFont(*fuente);
        btn_ok->setObjectName("btn_no");
        btn_ok->setText("ACEPTAR");
        btn_ok->setStyleSheet("border: 2px solid rgb(255,112,61); background-color: rgb(145,145,145); border-radius: 5px; color: black;");
        btn_ok->hide();
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void VentanaAvisoTest::setTituloColor(QColor color){
    try {
        titulo_color = color;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void VentanaAvisoTest::setMensajeColor(QColor color){
    try {
        mensaje_color = color;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void VentanaAvisoTest::setFondoColor(QColor color){
    try {
        popup_fillColor = color;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void VentanaAvisoTest::paintEvent(QPaintEvent* /*event*/){
    try {
       QSize s = size();
       QPainter *qp = new QPainter;
       qp->begin(this);
       qp->setRenderHint(QPainter::Antialiasing, true);
       qp->setPen(penColor);
       qp->setBrush(fillColor);
       qp->drawRect(0,0, s.width(), s.height());

       qp->setPen(popup_penColor);
       qp->setBrush(popup_fillColor);
       //int popup_width = 400;
       //int popup_height = 500;
       int ow = static_cast<int>(s.width() / 2 - pwidth /2);
       int oh = static_cast<int>(s.height() / 2 - pheight /2);
       qp->drawRoundedRect(ow, oh, pwidth, pheight, 5, 5);

       QFont *font = new QFont;
       font->setPixelSize(16);
       font->setBold(true);
       QFontMetrics *fm = new QFontMetrics(*font);
       qp->setFont(*font);
       qp->setPen(titulo_color);

       //int tolw = 80;
       //int tolh = -5;
       int tw = fm->horizontalAdvance(titulo);//fm->width(titulo);
       int pwt = static_cast<int>(s.width() / 2 - tw / 2);
       qp->drawText(pwt, oh +50, titulo);

       int cont = 125;
       qp->setPen(mensaje_color);
       font->setPixelSize(14);
       qp->setFont(*font);

       if(listaMensajes->size() > 0){
           int cont2 = 0;
           for(int j=0; j<listaMensajes->size();j++){
               //int tw = fm->horizontalAdvance(listaMensajes->at(j)); //fm->width(listaMensajes->at(j));
               //int pwt = static_cast<int>(s.width()/2-tw/2);
               int pwt = static_cast<int>(s.width()/2) - 200;
               qp->setPen(mensaje_color);
               qp->drawText(pwt, oh + cont, listaMensajes->at(j));
               qp->setPen(colorEstado(listaEstados->at(cont2)));
               qp->drawText(pwt+310, oh + cont, "[" + listaEstados->at(cont2) + "]");
               cont += 25;
               cont2 += 1;
           }
       }

       qp->end();
       ow = static_cast<int>(ow + pwidth/2) - 50;
       oh = static_cast<int>(oh + pheight) - 70;
       fin();
       if(estadoFinal){
           btn_ok->setGeometry(QRect(ow, oh, 100, 50));
           btn_ok->show();
       }

    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

QColor VentanaAvisoTest::colorEstado(QString estado){
    try {
        if(estado == PROCESO){
            return proceso_color;
        }
        else if(estado == OK){
            return ok_color;
        }
        else if(estado == ERROR){
            return error_color;
        }
        else{
            return QColor(0,0,0);
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return QColor(0,0,0);
    }
}

int VentanaAvisoTest::agregarMensaje(QString mensaje, QString estado){
    try {
        listaMensajes->append(mensaje);
        listaEstados->append(estado);
        return listaMensajes->size() - 1;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return 0;
    }
}

void VentanaAvisoTest::actualizaEstadoMsg(int indice, QString estado){
    try {
        if(indice != -1){
            if(indice < listaMensajes->size()){
                listaEstados->replace(indice, estado);
                update();
            }
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void VentanaAvisoTest::textoMostrar(QString mensajes){
    try {
        this->mensajes = mensajes;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void VentanaAvisoTest::fin(){
    try {
        bool resultado = true;
        for(int k=0;k<listaEstados->size();k++){
            if(listaEstados->at(k) == ERROR || listaEstados->at(k) == PROCESO){
                resultado = false;
                break;
            }
        }
        if(resultado){
            estadoFinal = true;
        }
        else{
            estadoFinal = false;
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

bool VentanaAvisoTest::teclado(QString tecla){
    try {
        if("ok" == tecla){
            if(btn_ok->isVisible() && estadoFinal){
                close();
                return true;
            }
            else{
                return false;
            }
        }
        else{
            return false;
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return false;
    }
}
