#include "ventanapruebas.h"

VentanaPruebas::VentanaPruebas(QWidget *parent, int width, int height, QString titulo) : QWidget(parent)
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

        label_sensores = new QLabel(this);
        fuente->setPointSize(12);
        label_sensores->setGeometry(QRect(offset_x + 0, offset_y + 0, 250, 30));
        label_sensores->setFont(*fuente);
        label_sensores->setStyleSheet("color: black; background-color: #D5D8DC;");
        label_sensores->setAlignment(Qt::AlignLeft);
        label_sensores->setText("Sensores");
        label_sensores->setObjectName("label_sensores");

        label_sensores_estado = new QLabel(this);
        fuente->setPointSize(12);
        label_sensores_estado->setGeometry(QRect(offset_x + 300, offset_y + 0, 50, 30));
        label_sensores_estado->setFont(*fuente);
        label_sensores_estado->setStyleSheet("color: black; background-color: #D5D8DC;");
        label_sensores_estado->setAlignment(Qt::AlignLeft);
        label_sensores_estado->setText("-");
        label_sensores_estado->setObjectName("label_sensores_estado");

        label_valvulas = new QLabel(this);
        fuente->setPointSize(12);
        label_valvulas->setGeometry(QRect(offset_x + 0, offset_y + 30, 250, 30));
        label_valvulas->setFont(*fuente);
        label_valvulas->setStyleSheet("color: black; background-color: #D5D8DC;");
        label_valvulas->setAlignment(Qt::AlignLeft);
        label_valvulas->setText("Válvulas");
        label_valvulas->setObjectName("label_valvulas");

        label_valvulas_estado = new QLabel(this);
        fuente->setPointSize(12);
        label_valvulas_estado->setGeometry(QRect(offset_x + 300, offset_y + 30, 50, 30));
        label_valvulas_estado->setFont(*fuente);
        label_valvulas_estado->setStyleSheet("color: black; background-color: #D5D8DC;"); //#D5D8DC
        label_valvulas_estado->setAlignment(Qt::AlignLeft);
        label_valvulas_estado->setText("-");
        label_valvulas_estado->setObjectName("label_valvulas_estado");

        label_presion = new QLabel(this);
        fuente->setPointSize(12);
        label_presion->setGeometry(QRect(offset_x + 0, offset_y + 60, 250, 30));
        label_presion->setFont(*fuente);
        label_presion->setStyleSheet("color: black; background-color: #D5D8DC;");
        label_presion->setAlignment(Qt::AlignLeft);
        label_presion->setText("Presión");
        label_presion->setObjectName("label_presion");

        label_presion_estado = new QLabel(this);
        fuente->setPointSize(12);
        label_presion_estado->setGeometry(QRect(offset_x + 300, offset_y + 60, 50, 30));
        label_presion_estado->setFont(*fuente);
        label_presion_estado->setStyleSheet("color: black; background-color: #D5D8DC;");
        label_presion_estado->setAlignment(Qt::AlignLeft);
        label_presion_estado->setText("-");
        label_presion_estado->setObjectName("label_presion_estado");

        label_oxigeno = new QLabel(this);
        fuente->setPointSize(12);
        label_oxigeno->setGeometry(QRect(offset_x + 0, offset_y + 90, 250, 30));
        label_oxigeno->setFont(*fuente);
        label_oxigeno->setStyleSheet("color: black; background-color: #D5D8DC;");
        label_oxigeno->setAlignment(Qt::AlignLeft);
        label_oxigeno->setText("Oxígeno");
        label_oxigeno->setObjectName("label_oxigeno");

        label_oxigeno_estado = new QLabel(this);
        fuente->setPointSize(12);
        label_oxigeno_estado->setGeometry(QRect(offset_x + 300, offset_y + 90, 50, 30));
        label_oxigeno_estado->setFont(*fuente);
        label_oxigeno_estado->setStyleSheet("color: black; background-color: #D5D8DC;");
        label_oxigeno_estado->setAlignment(Qt::AlignLeft);
        label_oxigeno_estado->setText("-");
        label_oxigeno_estado->setObjectName("label_oxigeno_estado");

        label_info = new QLabel(this);
        fuente->setPointSize(12);
        label_info->setGeometry(QRect(offset_x + 0, offset_y + 120, 400, 60));
        label_info->setFont(*fuente);
        label_info->setStyleSheet("color: black; background-color: #D5D8DC;");
        label_info->setAlignment(Qt::AlignLeft);
        label_info->setText("info");
        label_info->setObjectName("label_info");

        btn_iniciar = new QPushButton(this);
        btn_iniciar->setFont(*fuente);
        btn_iniciar->setObjectName("btn_iniciar");
        btn_iniciar->setText("INICIAR");
        btn_iniciar->setStyleSheet("border: 2px solid rgb(255,112,61); background-color: rgb(145,145,145); border-radius: 5px; color: black;");
        btn_iniciar->setGeometry(QRect(offset_x + 20, offset_y + 175, 200, 50));

        btn_siguiente = new QPushButton(this);
        btn_siguiente->setFont(*fuente);
        btn_siguiente->setObjectName("btn_siguiente");
        btn_siguiente->setText("Siguiente");
        btn_siguiente->setStyleSheet("border: 2px solid rgb(145,145,145); background-color: rgb(145,145,145); border-radius: 5px; color: black;");
        btn_siguiente->setGeometry(QRect(offset_x + 300, offset_y + 175, 150, 50));
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void VentanaPruebas::setTituloColor(QColor color){
    try {
        titulo_color = color;
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void VentanaPruebas::setMensajeColor(QColor color){
    try {
        mensaje_color = color;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void VentanaPruebas::setFondoColor(QColor color){
    try {
        popup_fillColor = color;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void VentanaPruebas::paintEvent(QPaintEvent* /*event*/){
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
       int tw = fm->horizontalAdvance(titulo); //int tw = fm->width(titulo);
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

QColor VentanaPruebas::colorEstado(QString estado){
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
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return QColor(0,0,0);
    }
}
