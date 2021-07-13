#include "temperatura.h"

Temperatura::Temperatura(QWidget *parent, Monitor *monitor) : QWidget(parent)
{
    try {
        this->monitor = monitor;
        estiloBT = "QPushButton { background-color: black; border-radius: 5px; text-align:left; \n"
                   "border: 2px solid black; color: black; font-size:10px}\n"
                   "QPushButton:pressed { background-color: black;\n"
                   "border: 2px solid black;}";
        temperatura = new QPushButton(this);
        temperatura->setGeometry(QRect(800, 0, 90, 50));
        temperatura->setText("");

        QString ruta = QDir::currentPath();
        iconTemp1 = new QIcon;
        iconTemp1->addPixmap(QPixmap(":/general/graficos/ter0.png"), QIcon::Normal, QIcon::Off);
        iconTemp2 = new QIcon;
        iconTemp2->addPixmap(QPixmap(":/general/graficos/ter2.png"), QIcon::Normal, QIcon::Off);
        iconTemp3 = new QIcon;
        iconTemp3->addPixmap(QPixmap(":/general/graficos/ter3.png"), QIcon::Normal, QIcon::Off);

        temperatura->setIcon(*iconTemp1);
        temperatura->setIconSize(QSize(60,50));
        temperatura->setObjectName("temperatura");
        temperatura->setStyleSheet(estiloBT);

        label = new QLabel(this);
        label->setGeometry(QRect(835, 20, 61, 21));
        fuente = new QFont;
        fuente->setPointSize(10);
        fuente->setBold(true);
        fuente->setWeight(75);

        tt = "\u00b0";

        label->setFont(*fuente);
        label->setObjectName("label");
        label->setStyleSheet("color: white;");

        monTimer = new QTimer(this);
        connect(monTimer, &QTimer::timeout, this, &Temperatura::run);
        monTimer->start(1000);
        tempAnt = 0;
        toogle = false;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void Temperatura::run(){
    try {
        QString temp = obtenTemp();
        //qDebug() << "Temperatura::run: " + temp;
        label->setText(temp + " " + tt + "C");
        int temp_int = temp.toInt();
        if(tempAnt != temp_int){
            if(temp_int >0 && temp_int <= 70){
                temperatura->setIcon(*iconTemp2);
                temperatura->setIconSize(QSize(60,50));
                toogle = false;
            }
            else if(temp_int > 71 && temp_int <= 75){
                if(toogle){
                    temperatura->setIcon(*iconTemp1);
                    temperatura->setIconSize(QSize(60,50));
                    toogle = false;
                }
                else{
                    temperatura->setIcon(*iconTemp3);
                    temperatura->setIconSize(QSize(60,50));
                    toogle = true;
                }
            }
            else if(temp_int > 75){
                monitor->detener_ventilador();
                QThread::sleep(4);
                QProcess::execute("shutdown -h now");
            }
            tempAnt = temp_int;
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

QString Temperatura::obtenTemp(){
    try {
        QProcess process;
        process.start("vcgencmd measure_temp");
        process.waitForFinished(-1);
        QString salida = process.readAllStandardOutput();
        //qDebug() << "obtenTemp: " + salida;
        QStringList ll = salida.split("\n");
        QString final = ll.at(0);
        final.replace("temp=", "");
        return final.mid(0,2);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}
