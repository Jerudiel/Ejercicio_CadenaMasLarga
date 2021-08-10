#include "mainwindow.h"

#include <QApplication>

#include <QObject>

#include <QtDebug>
#include <QFile>
#include <QTextStream>
#include <signal.h>


#include <QDateTime>
#include <QFile>
#include <QDir>

#include <utilidades/serverws.h>
#include "utilidades/logutils.h"

/*void myMessageHandler(QtMsgType type, const QMessageLogContext &, const QString & msg)
{
    QString txt;
    QDateTime dateTime = QDateTime::currentDateTime();
    QString dateTimeString = dateTime.toString("yyyy-MM-dd hh:mm:ss.zzz");
    switch (type) {
    case QtDebugMsg:
        txt = QString("%1 Debug: %2").arg(dateTimeString, msg);
        break;
    case QtWarningMsg:
        txt = QString("%1 Warning: %2").arg(dateTimeString, msg);
    break;
    case QtCriticalMsg:
        txt = QString("%1 Critical: %2").arg(dateTimeString, msg);
    break;
    case QtFatalMsg:
        txt = QString("%1 Fatal: %2").arg(dateTimeString, msg);
    break;
    }
    QFile outFile("p.log");
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&outFile);
    ts << txt << endl;

    if(outFile.size() > 10000000){
        outFile.resize(0);
    }

    outFile.close();



}*/

void signal_handler(int signum) {
    signal(SIGSEGV, SIG_DFL);
    signal(SIGFPE, SIG_DFL);
    //aewm_obj.show_fault(signum);
    qDebug() << "[SIGNAL] VIOLACION DE SEGMENTO" << QString::number(signum);
    //QCoreApplication::quit();
    QCoreApplication::exit(signum);
}

void signal_off(int code){

}

int main(int argc, char *argv[])
{
    signal(SIGSEGV, signal_handler);
    signal(SIGFPE, signal_handler);
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    QApplication a(argc, argv);

    //QObject::connect(a, SIGNAL(aboutToQuit()), this, SLOT());

    bool debug_s = false;
    bool debug_t = false;
    bool debug_c = false;
    bool control_gases = true;

    QStringList args = a.arguments();
    if(args.count() >= 2){
        //recorrer los argumentos
        for(int j=0; j < args.count(); j++){
            if(args.at(j).contains("-l")){
                //qInstallMessageHandler(myMessageHandler);
                LOGUTILS::initLogging();
            }
            else if(args.at(j).contains("-s")){
                //activar debug sensores
                debug_s = true;
            }
            else if(args.at(j).contains("-c")){
                //activar debug control
                debug_c = true;
            }
            else if(args.at(j).contains("-t")){
                //activar debug teclado
                debug_t = true;
            }
            else if(args.at(j).contains("-g")){
                //activar debug teclado
                control_gases = true;
            }
        }
    }

    ServerWS *server = new ServerWS(9090, true);

    MainWindow w(server, nullptr, debug_t, debug_c, debug_s, control_gases);
    w.show();

    //res
    int res_app = a.exec();
    //qDebug() << "res_app: " << res_app;
    //QCoreApplication::exit(res_app);
    return res_app;
}

//:/iconos/btn_GraficaSI.png

/*#include "widgetsigno3.h"

#include <QApplication>

int main(int argc, char *argv[]){
    QApplication app(argc, argv);

    WidgetSigno3 wdg; //Crear una instancia de la clase book
    wdg.show(); //Mandar a llamar al método show de la clase book

    return app.exec();
}*/
