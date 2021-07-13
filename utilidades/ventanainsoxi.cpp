#include "ventanainsoxi.h"

VentanaInsOxi::VentanaInsOxi(QWidget *parent, int width, int height, QString titulo) : QWidget(parent)
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

        imagen = new QLabel(this);
        imagen->setGeometry(QRect(offset_x + 10, offset_y - 65, 400, 300));
        imagen->setObjectName("imagen");

        label_info = new QLabel(this);
        fuente->setPointSize(12);
        label_info->setGeometry(QRect(offset_x + 10, offset_y + 240, 300, 60));
        label_info->setFont(*fuente);
        label_info->setStyleSheet("color: black; background-color: #D5D8DC;");
        label_info->setAlignment(Qt::AlignLeft);
        label_info->setText("Desconectar el pulmón.");
        label_info->setObjectName("label_info");

        btn_ok = new QPushButton(this);
        btn_ok->setFont(*fuente);
        btn_ok->setObjectName("btn_ok");
        btn_ok->setText("OK");
        btn_ok->setStyleSheet("border: 2px solid rgb(255,112,61); background-color: rgb(145,145,145); border-radius: 5px; color: black;");
        btn_ok->setGeometry(QRect(offset_x + 320, offset_y + 240, 150, 50));

        timerMuestra = new QTimer;
        timerMuestra->setInterval(1500);
        connect(timerMuestra, SIGNAL(timeout()), this, SLOT(cambiaImagen()));

        contador = 0;

        //listar imagenes y cargarlas en qpixmap
        QString ruta = QDir::currentPath();
        //qDebug() << "ruta: " + ruta + "/graficos/oxi";
        //QStringList lista = QDir(ruta + "/graficos/oxi", QString(), QDir::SortFlags(QDir::Name | QDir::IgnoreCase ), QDir::Filters ( QDir::NoDotAndDotDot) ).entryList();
        QDir directory(":/oxi/graficos/oxi"); //ruta + "/graficos/oxi"
        QStringList lista = directory.entryList(QStringList() << "*.jpg" << "*.JPG" << "*.png", QDir::Files);
        num_imagenes = lista.size();
        //qDebug() << "ruta tam: " + QString::number(num_imagenes);
        for(int i = 0 ; i < lista.size(); i++){
            //qDebug() << "lista-ruta: " + lista.at(i);
            imagenes[i] = new QPixmap(ruta + "/graficos/oxi/" + lista.at(i));
            imagenes[i]->scaled(400,300);
        }

        if(num_imagenes > 0){
            imagen->setPixmap(*imagenes[0]);
        }


    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void VentanaInsOxi::mostrar(){
    try {
        imagen->setPixmap(*imagenes[0]);
        this->show();
        if(!timerMuestra->isActive()){
            timerMuestra->start(1500);
        }
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void VentanaInsOxi::detener(){
    try {
        if(timerMuestra->isActive()){
            timerMuestra->stop();
        }
        //reiniciar contador
        contador = 0;
        this->hide();
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void VentanaInsOxi::cambiaImagen(){
    try {
        if(contador < num_imagenes-1){
            contador ++;
        }
        else{
            contador = 0;
        }
        imagen->setPixmap(*imagenes[contador]);
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void VentanaInsOxi::setTituloColor(QColor color){
    try {
        titulo_color = color;
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void VentanaInsOxi::setMensajeColor(QColor color){
    try {
        mensaje_color = color;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void VentanaInsOxi::setFondoColor(QColor color){
    try {
        popup_fillColor = color;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void VentanaInsOxi::paintEvent(QPaintEvent* /*event*/){
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

QColor VentanaInsOxi::colorEstado(QString estado){
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
