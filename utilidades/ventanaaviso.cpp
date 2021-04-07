#include "ventanaaviso.h"

VentanaAviso::VentanaAviso(QWidget *parent, int width, int height) : QWidget(parent)
{
    try {
        setWindowFlags(Qt::FramelessWindowHint);
        setAttribute(Qt::WA_TranslucentBackground);

        pwidth = width;
        pheight = height;


        fillColor = QColor(30, 30, 30, 120);
        penColor = QColor(51,51,51); //QColor("#333333");

        popup_fillColor = QColor(213,216,220);//QColor("#D5D8DC");
        popup_penColor = QColor(200, 200, 200, 255);

        //self.signals = VentanaAvisoSignalsTest()
        mensajes = nullptr;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void VentanaAviso::paintEvent(QPaintEvent* /*event*/){
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


       //int tolw = 80;
       //int tolh = -5;
       qp->setPen(QColor(255,0,0));
       int tw = fm->horizontalAdvance("AVISOS");//fm->width("AVISOS");
       int pwt = static_cast<int>(s.width() / 2 - tw / 2);
       qp->drawText(pwt, oh +50, "AVISOS");

       int cont = 100;
       qp->setPen(QColor(70,70,70));
       font->setPixelSize(16);
       //qp->setFont(*font);

       if(mensajes != nullptr){
           for(int j=0; j<mensajes->size();j++){
               int tw = fm->horizontalAdvance(mensajes->at(j));//fm->width(mensajes->at(j));
               int pwt = static_cast<int>(s.width()/2-tw/2);

               qp->drawText(pwt, oh + cont, mensajes->at(j));
               cont += 25;
           }
       }

       qp->end();

    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void VentanaAviso::textoMostrar(QStringList *mensajes){
    try {
        this->mensajes = mensajes;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}
