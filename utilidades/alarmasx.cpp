#include "alarmasx.h"

AlarmasX::AlarmasX(QWidget *parent) : QWidget(parent)
{
    try {
        setObjectName("AlarmasX");
        estadoP = 0;
        estadoB = -1;
        toggleB=false;
        toggleBEdo=true;

        QString ruta = QDir::currentPath();
        irespiOn = new QPixmap(":/general/graficos/respia.png"); //:/general/graficos/respia.png
        irespiOff = new QPixmap(":/general/graficos/norespia.png");

        ibat100 = new QPixmap(":/general/graficos/100a.png");
        ibat75 = new QPixmap(":/general/graficos/75a.png");
        ibat50 = new QPixmap(":/general/graficos/50a.png");
        ibat25 = new QPixmap(":/general/graficos/25a.png");
        ibat00 = new QPixmap(":/general/graficos/00a.png");
        ibatAC = new QPixmap(":/general/graficos/aca.png");

        ibat100c = new QPixmap(":/general/graficos/100c.png");
        ibat75c = new QPixmap(":/general/graficos/75c.png");
        ibat50c = new QPixmap(":/general/graficos/50c.png");
        ibat25c = new QPixmap(":/general/graficos/25c.png");
        ibat00c = new QPixmap(":/general/graficos/00c.png");

        lrespi = new QLabel(this);
        lrespi->setGeometry(QRect(0, 0, 50, 53));
        lrespi->setPixmap(*irespiOff);
        lrespi->setObjectName("lrespi");
        lrespi->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        lrespi->setStyleSheet("border:1px solid white;");

        lbateria = new QLabel(this);
        lbateria->setGeometry(QRect(50, 0, 80, 53));
        lbateria->setPixmap(*ibatAC);
        lbateria->setObjectName("lbateria");
        lbateria->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        //lbateria->setStyleSheet("border:1px solid white;");

        /*self.sound_player = QtMultimedia.QSoundEffect()
        self.sound_player.playingChanged.connect(self.termina_sound_player)
        self.sound_player.setVolume(1.0)
        #self.sound_player.sound.setSource(QtCore.QUrl.fromLocalFile(sound_file))
        #self.sound_player.play()*/

        reproductor = new QSoundEffect;
        reproductor->setVolume(1.0);
        reproductor->setSource(QUrl::fromLocalFile("audios/prioridad_media.wav"));
        connect(reproductor, SIGNAL(playingChanged()) ,this, SLOT(termina_reproductor()));


        duration = 0.12;
        freq = 1209;

        audio_corriendo = false;

        timer_act = new QTimer;
        connect(timer_act, SIGNAL(timeout()), this, SLOT(actualiza()));
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void AlarmasX::termina_reproductor(){
    try {
        if(audio_corriendo){
            if(!reproductor->isPlaying()){
                reproductor->play();
            }
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void AlarmasX::beep(){
    try {
        QProcess::execute("amixer --quiet set PCM 90%");
        QProcess::execute(QString("play -v 0.1 -nq -t alsa synth %1 sine %2").arg(QString::number(duration), QString::number(freq)));
        QProcess::execute("amixer --quiet set PCM 100%");
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void AlarmasX::iniciar_alarma(){
    try {
        if(!audio_corriendo){
            audio_corriendo = true;
            reproductor->play();
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void AlarmasX::hilo_audio_media(){
    try {

    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void AlarmasX::detener_alarma(){
    try {
        if(audio_corriendo){
            audio_corriendo = false;
            if(reproductor->isPlaying()){
                reproductor->stop();
            }
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void AlarmasX::actualiza(){
    try {
        if(toggleB){
            beep();
            if(toggleBEdo){
                lbateria->setPixmap(*ibat25);
            }
            else{
                lbateria->setPixmap(*ibat100);
            }
            toggleBEdo = ! toggleBEdo;
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void AlarmasX::trigger(int estado){
    try {
        estadoP = estado;
        if(estadoP == 0){
            lrespi->setPixmap(*irespiOff);
        }
        else{
            lrespi->setPixmap(*irespiOn);
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void AlarmasX::bateria(int nivel, int modo){
    try {
        estadoB = nivel;
        if(modo == 1){
            if(estadoB == -1){
                lbateria->setPixmap(*ibatAC);
                toggleB = false;
                detener_alarma();
            }
            else if(estadoB <= 100 && estadoB >= 75){
                lbateria->setPixmap(*ibat100c);
                toggleB = false;
                detener_alarma();
            }
            else if(estadoB < 75 && estadoB >= 50){
                lbateria->setPixmap(*ibat75c);
                toggleB = false;
                detener_alarma();
            }
            else if(estadoB < 50 && estadoB >= 25){
                lbateria->setPixmap(*ibat50c);
                toggleB = false;
                detener_alarma();
            }
            else if(estadoB < 25 && estadoB >= 10){
                lbateria->setPixmap(*ibat25c);
                toggleB = false;
                detener_alarma();
            }
            else if(estadoB < 10){
                lbateria->setPixmap(*ibat00c);
                if(!toggleB){
                    toggleB = true;
                }
            }
        }
        else{
            if(estadoB == -1){
                lbateria->setPixmap(*ibatAC);
                toggleB = false;
                detener_alarma();
            }
            else if(estadoB <= 100 && estadoB >= 75){
                lbateria->setPixmap(*ibat100);
                toggleB = false;
                detener_alarma();
            }
            else if(estadoB < 75 && estadoB >= 50){
                lbateria->setPixmap(*ibat75);
                toggleB = false;
                detener_alarma();
            }
            else if(estadoB < 50 && estadoB >= 25){
                lbateria->setPixmap(*ibat50);
                toggleB = false;
                detener_alarma();
            }
            else if(estadoB < 25 && estadoB >= 10){
                lbateria->setPixmap(*ibat25);
                toggleB = false;
                detener_alarma();
            }
            else if(estadoB < 10){
                lbateria->setPixmap(*ibat00);
                if(!toggleB){
                    toggleB = true;
                }
            }
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

