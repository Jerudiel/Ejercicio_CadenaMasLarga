#include "ventanaconfirmacion.h"

VentanaConfirmacion::VentanaConfirmacion(QWidget *parent, int width, int height, QString titulo) : QWidget(parent)
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

        label = new QLabel(this);
        label->setGeometry(QRect(offset_x + 5, offset_y, 450, 50));
        label->setFont(*fuente);
        label->setStyleSheet("background-color: #D5D8DC; color: black;");
        label->setAlignment(Qt::AlignCenter);
        label->setText("¿Está seguro de que quiere continuar?");
        label->setObjectName("label");


        btn_si = new QPushButton(this);
        btn_si->setFont(*fuente);
        btn_si->setObjectName("btn_si");
        btn_si->setText("SÍ");
        btn_si->setStyleSheet("border: 2px solid rgb(255,112,61); background-color: rgb(145,145,145); border-radius: 5px; color: black;");
        btn_si->setGeometry(QRect(offset_x + 20, offset_y + 100, 200, 50));

        btn_no = new QPushButton(this);
        btn_no->setFont(*fuente);
        btn_no->setObjectName("btn_no");
        btn_no->setText("NO");
        btn_no->setStyleSheet("border: 2px solid rgb(145,145,145); background-color: rgb(145,145,145); border-radius: 5px; color: black;");
        btn_no->setGeometry(QRect(offset_x + 250, offset_y + 100, 200, 50));

        label_time = new QLabel(this);
        label_time->setGeometry(QRect(offset_x + 350, offset_y + 180, 100, 50));
        label_time->setFont(*fuente);
        label_time->setStyleSheet("background-color: #D5D8DC; color: black;");
        label_time->setText("30 seg");
        label_time->setObjectName("label_time");
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void VentanaConfirmacion::setTituloColor(QColor color){
    try {
        titulo_color = color;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void VentanaConfirmacion::setMensajeColor(QColor color){
    try {
        mensaje_color = color;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void VentanaConfirmacion::setFondoColor(QColor color){
    try {
        popup_fillColor = color;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void VentanaConfirmacion::paintEvent(QPaintEvent* /*event*/){
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
       int tw = fm->horizontalAdvance(titulo); //fm->width(titulo);
       int pwt = static_cast<int>(s.width() / 2 - tw / 2);
       qp->drawText(pwt, oh +50, titulo);

       //int cont = 125;
       qp->setPen(mensaje_color);
       font->setPixelSize(14);
       qp->setFont(*font);

       qp->end();

    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

QColor VentanaConfirmacion::colorEstado(QString estado){
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
