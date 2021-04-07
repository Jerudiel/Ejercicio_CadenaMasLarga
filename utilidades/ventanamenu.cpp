#include "ventanamenu.h"

VentanaMenu::VentanaMenu(QWidget *parent, int width, int height, QString titulo, QString version) : QWidget(parent)
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
        this->version = version;
        mensajes = nullptr;

        fuente = new QFont;
        fuente->setPointSize(11);
        fuente->setBold(true);

        listaMensajes = new QStringList;
        listaEstados = new QStringList;
        estadoFinal = false;

        btn_calibrar = new QPushButton(this);
        btn_calibrar->setFont(*fuente);
        btn_calibrar->setObjectName("btn_calibrar");
        btn_calibrar->setText("IR A VENTILACIÓN");
        btn_calibrar->setStyleSheet("border: 2px solid rgb(255,112,61); background-color: rgb(145,145,145); border-radius: 5px; color: black;");
        btn_calibrar->setGeometry(QRect(offset_x + 20, offset_y + 100, 200, 50));

        btn_pruebas = new QPushButton(this);
        btn_pruebas->setFont(*fuente);
        btn_pruebas->setObjectName("btn_pruebas");
        btn_pruebas->setText("PRUEBAS INICIALES");
        btn_pruebas->setStyleSheet("border: 2px solid rgb(145,145,145); background-color: rgb(145,145,145); border-radius: 5px; color: black;");
        btn_pruebas->setGeometry(QRect(offset_x + 250, offset_y + 100, 200, 50));

        label_version = new QLabel(this);
        label_version->setFont(*fuente);
        label_version->setObjectName("label_version");
        label_version->setStyleSheet("background-color: #D5D8DC; color: black;");
        label_version->setText("V"+version);
        label_version->setGeometry(QRect(offset_x + 350, offset_y + 180, 50, 50));
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void VentanaMenu::setTituloColor(QColor color){
    try {
        titulo_color = color;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void VentanaMenu::setMensajeColor(QColor color){
    try {
        mensaje_color = color;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void VentanaMenu::setFondoColor(QColor color){
    try {
        popup_fillColor = color;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void VentanaMenu::paintEvent(QPaintEvent* /*event*/){
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

QColor VentanaMenu::colorEstado(QString estado){
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
