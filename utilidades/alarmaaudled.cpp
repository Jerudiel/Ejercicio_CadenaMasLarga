#include "alarmaaudled.h"

AlarmaAudLed::AlarmaAudLed(InfoAlarma *infoAlarmas)
{
    try {
        this->infoAlarmas = infoAlarmas;
        audio_corriendo = false;

        QString ruta = QDir::currentPath();
        //qDebug() << "ruat alarmas: " + ruta ; //:/audios/audios/prioridad_alta_super.wav
        /*wave_alta = QUrl::fromLocalFile(":/audios/audios/prioridad_alta.wav");
        wave_media = QUrl::fromLocalFile(":/audios/audios/prioridad_media.wav");
        wave_baja =  QUrl::fromLocalFile(":/audios/audios/prioridad_baja.wav");
        wave_inoperante = QUrl::fromLocalFile(":/audios/audios/prioridad_alta_super.wav");
        wave_actual = wave_media;*/

        wave_alta = QUrl("qrc:/audios/audios/prioridad_alta.wav");
        wave_media = QUrl("qrc:/audios/audios/prioridad_media.wav");
        wave_baja =  QUrl("qrc:/audios/audios/prioridad_baja.wav");
        wave_inoperante = QUrl("qrc:/audios/audios/prioridad_alta_super.wav");
        wave_actual = wave_media;

        /*const auto deviceInfos = QAudioDeviceInfo::availableDevices(QAudio::AudioOutput);
        for(const QAudioDeviceInfo &deviceInfo : deviceInfos)
            qDebug() << "Device name: " << deviceInfo.deviceName();*/

        reproductor = new QSoundEffect;
        reproductor->setLoopCount(QSoundEffect::Infinite);
        reproductor->setVolume(1.0);
        reproductor->setSource(wave_actual);
        connect(reproductor, SIGNAL(playingChanged()) ,this, SLOT(termina_reproductor()));

        listaReproduccion = new QMediaPlaylist(this);
        listaReproduccion->addMedia(wave_baja);
        listaReproduccion->addMedia(wave_media);
        listaReproduccion->addMedia(wave_alta);
        listaReproduccion->addMedia(wave_inoperante);
        index_wave = 1;
        listaReproduccion->setCurrentIndex(index_wave);

        listaReproduccion->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        //listaReproduccion->playbackMode();
        //listaReproduccion->setCurrentIndex(1);

        duracion_sonido = 10000;

        reproductorMulti = new QMediaPlayer(this);
        connect(reproductorMulti, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
        connect(reproductorMulti, SIGNAL(durationChanged(qint64)), this, SLOT(durationChanged(qint64)));

        /*connect(reproductorMulti, SIGNAL(mediaChanged(QMediaContent)), this, SLOT(mediaChanged(QMediaContent)));
        connect(reproductorMulti, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), this, SLOT(mediaStatusChanged(QMediaPlayer::MediaStatus)));
        connect(reproductorMulti, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(stateChanged(QMediaPlayer::State)));*/
        //reproductorMulti->setPlaylist(listaReproduccion);
        reproductorMulti->setMedia(wave_inoperante);
        reproductorMulti->setVolume(100);

        //reproductorMulti->play();
        //qDebug() << "reproduciendo desde el inicio";
        //

        state_alarm_vol = false;
        state_alarm_pre = false;
        state_alarm_fr = false;
        state_alarm_volMin = false;
        state_alarm_bateria = false;
        state_alarm_gases = false;
        state_alarm_fio2 = false;
        state_alarm_pre_con = false;
        state_alarma_apnea = false;
        state_alarma_inoperante = false;
        state_alarma_alimentacion = false;
        state_alarma_desconexion = false;
        state_alarma_comunicacion = false;

        icono_vol = nullptr;
        icono_fr = nullptr;

        edoAlarPresion = false;
        edoAlarVol = false;
        edoAlarFr = false;
        edoAlarVolMin = false;
        edoAlarBateria = false;
        edoAlarGases = false;
        edoAlarFio2 = false;
        edoAlarPreCon = false;
        edoAlarApnea = false;
        edoAlarInoperante = false;
        edoAlarAlimentacion = false;
        edoAlarDesconexion = false;
        edoAlarComunicacion = false;

        cambioAudio = false;

        timerAlarma = new QTimer;
        timerAlarma->setSingleShot(true);
        connect(timerAlarma, SIGNAL(timeout()), this, SLOT(reanudaAlarma()));

        prioAltaAct = false;
        prioAltaAnt = false;

        prioInoperante = false;

        enPausa = false;

        timerToggle = new QTimer;
        connect(timerToggle, SIGNAL(timeout()), this, SLOT(toggle()));

        edoToggleFr = false;
        edoToggleVol = false;
        edoToogle = false;
        edoToogleBateria = false;
        edoToogleGases = false;
        edoToogleFio2 = false;
        edoTooglePreCon = false;
        edoToogleApnea = false;
        edoToogleInoperante = false;
        edoToogleAlimentacion = false;
        edoToogleDesconexion = false;
        edoToogleComunicacion = false;

        toggleFR = false;
        toggleVOL = false;

        timerInfoA = new QTimer;
        connect(timerInfoA, SIGNAL(timeout()), this, SLOT(actualizaTiempo()));

        contador = 59;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

/*void AlarmaAudLed::mediaChanged(QMediaContent contenido){
    try {
        //qDebug() << "mediaChanged: " + contenido.canonicalUrl().toString();

    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void AlarmaAudLed::mediaStatusChanged(QMediaPlayer::MediaStatus mediaStatus){
    try {
        //qDebug() << "mediaStatusChanged: " + QString::number(mediaStatus);

    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void AlarmaAudLed::stateChanged(QMediaPlayer::State state){
    try {
        //qDebug() << "stateChanged: " + QString::number(state);

    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}*/

void AlarmaAudLed::durationChanged(qint64 duracion){
    try {
        //qDebug() << "duracion cargada: " + QString::number(duracion);
        if(audio_corriendo){
            //qDebug() << "[AlarmaAudLed ]duracion cargada: manda a reproducir: " << duracion_sonido;
            duracion_sonido = duracion;
            //qDebug() << "[AlarmaAudLed] durationChanged: " << reproductorMulti->isAudioAvailable();
            reproductorMulti->play();
        }


    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void AlarmaAudLed::positionChanged(qint64 posicion){
    try {
        //qDebug() << "entra a  positionChanged : " + QString::number(posicion) + " de " + QString::number(duracion_sonido);
        /*if(duracion_sonido - posicion < 100){
            qDebug() << "duracion_sonido: " + QString::number(duracion_sonido);
            qDebug() << "posicion: " + QString::number(posicion);
        }*/
        if(duracion_sonido == posicion){
            //volver a reproducir
            //qDebug() << "entra a volver a reproducir";
            if(audio_corriendo && ! enPausa && ! cambioAudio){
                //qDebug() << "cargando para volver a reproducir";
                reproductorMulti->setMedia(wave_actual);
                //qDebug() << "[AlarmaAudLed] positionChanged: " << wave_actual;
            }

            //reproductorMulti->play();
        }

    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void AlarmaAudLed::termina_reproductor(){
    try {
        //qDebug() << "entra a  termina_reproductor";
        if(audio_corriendo && ! enPausa && ! cambioAudio){
            if(!reproductor->isPlaying()){
                reproductor->setSource(wave_actual);
                connect(reproductor, SIGNAL(playingChanged()) ,this, SLOT(termina_reproductor()));
                reproductor->play();
                //qDebug() << "termina_reproductor, volver a reproducir";
                //qDebug() << "wave: " + wave_actual.toString();
            }
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void AlarmaAudLed::actualizaTiempo(){
    try {
        contador--;
        QString tiempo = "";
        if(contador < 10){
            tiempo = "00:0" + QString::number(contador);
        }
        else{
            tiempo = "00:" + QString::number(contador);
        }
        infoAlarmas->actualiza(tiempo);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void AlarmaAudLed::setIconoFre(QLabel *icono_fr){
    try {
        this->icono_fr = icono_fr;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void AlarmaAudLed::setIconoVol(QLabel *icono_vol){
    try {
        this->icono_vol = icono_vol;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void AlarmaAudLed::toggle(){
    try {
        if(edoToogle){
            if(edoToggleFr){
                if(toggleFR){
                    icono_fr->hide();
                }
                else{
                    icono_fr->show();
                }
                toggleFR = ! toggleFR;
            }
            if(edoToggleVol){
                if(toggleVOL){
                    icono_vol->hide();
                }
                else{
                    icono_vol->show();
                }
                toggleVOL = !toggleVOL;
            }
        }
        else{
            timerToggle->stop();
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void AlarmaAudLed::cambiaEstadoAlarma(int alarma, bool estado){
    try {
        if(alarma == FRECUENCIA){
            state_alarm_fr = estado;
            if(state_alarm_fr){
                icono_fr->show();
                if(! edoToogle){
                    timerToggle->start(500);
                    edoToogle = true;
                }
                edoToggleFr = true;
            }
            else{
                icono_fr->hide();
                edoToggleFr = false;
            }
        }
        else if(alarma == VOLUMEN){
            state_alarm_vol = estado;
            if(state_alarm_vol){
                icono_vol->show();
                if(! edoToogle){
                    timerToggle->start(500);
                    edoToogle = true;
                }
                edoToggleVol = true;
            }
            else{
                icono_vol->hide();
                edoToggleVol = false;
            }
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void AlarmaAudLed::iniciaAlarma(int tipo){
    try {
        qDebug() << "[AlarmaAudLed] iniciaAalrma function int tipo: " + QString::number(tipo);
        if(tipo == PRESION){
            edoAlarPresion = true;
            state_alarm_pre = true;
        }
        else if(tipo == FRECUENCIA){
            edoAlarFr = true;
            cambiaEstadoAlarma(FRECUENCIA, true);
        }
        else if(tipo == VOLUMEN){
            edoAlarVol = true;
            cambiaEstadoAlarma(VOLUMEN, true);
        }
        else if(tipo == VOLMINIMO){
            edoAlarVolMin = true;
            prioAltaAct = true;
            state_alarm_volMin = true;
        }
        else if(tipo == BATERIA){
            edoAlarBateria = true;
            prioAltaAct = true;
            state_alarm_bateria = true;
        }
        else if(tipo == GASES){
            edoAlarGases = true;
            prioAltaAct = true;
            state_alarm_gases = true;
        }
        else if(tipo == FIO2){
            edoAlarFio2 = true;
            state_alarm_fio2 = true;
        }
        else if(tipo == PRESION_CONFIG){
            edoAlarPreCon = true;
            state_alarm_pre_con = true;
        }
        else if(tipo == APNEA){
            edoAlarApnea = true;
            state_alarma_apnea = true;
        }
        else if(tipo == INOPERANTE){
            edoAlarInoperante = true;
            prioInoperante = true;
            state_alarma_inoperante = true;
        }
        else if(tipo == ALIMENTACION){
            edoAlarAlimentacion = true;
            state_alarma_alimentacion = true;
        }
        else if(tipo == DESCONEXION){
            prioAltaAct = true;
            edoAlarDesconexion = true;
            state_alarma_desconexion = true;
        }
        else if(tipo == COMUNICACION){
            prioAltaAct = true;
            edoAlarComunicacion = true;
            state_alarma_comunicacion = true;
        }

        if(enPausa){
            reanudaAlarma();
        }

        if(!audio_corriendo){
            audio_corriendo = true;
            if(prioInoperante){
                //reproductor->setSource(wave_inoperante);
                //index_wave = INDEX_INOPERANTE;
                //listaReproduccion->setCurrentIndex(INDEX_INOPERANTE);
                //listaReproduccion->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
                //reproductorMulti->setPlaylist(listaReproduccion);
                wave_actual = wave_inoperante;
                reproductorMulti->setMedia(wave_inoperante);
                //reproductorMulti->play(); 
                qDebug() << "[AlarmaAudLed] reproducir alarma inoperante - audio_corriendo false";
            }
            else if(prioAltaAct){
                //reproductor->setSource(wave_alta);
                //index_wave = INDEX_ALTA;
                //listaReproduccion->setCurrentIndex(INDEX_ALTA);
                //listaReproduccion->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
                //reproductorMulti->setPlaylist(listaReproduccion);
                wave_actual = wave_alta;
                reproductorMulti->setMedia(wave_alta);
                //reproductorMulti->play();
                qDebug() << "[AlarmaAudLed] reproducir alarma alta - audio_corriendo false";
            }
            else{
                //reproductor->setSource(wave_media);
                //index_wave = INDEX_MEDIA;
                //listaReproduccion->setCurrentIndex(INDEX_MEDIA);
                //listaReproduccion->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
                //reproductorMulti->setPlaylist(listaReproduccion);
                wave_actual = wave_media;
                reproductorMulti->setMedia(wave_media);
                //reproductorMulti->play();
                qDebug() << "[AlarmaAudLed] reproducir alarma media - audio_corriendo false";
            }
            //reproductor->play();
            //reproductorMulti->play();
            /*int respuesta = listaReproduccion->playbackMode();
            qDebug() << "modo de la playlist: " + QString::number(respuesta);
            int current = listaReproduccion->currentIndex();
            qDebug() << "currenti index de la playlist: " + QString::number(current);*/
        }
        else{
            //ya se esta reproduciendo una alarma
            if(prioInoperante){
                cambioAudio = true;
                //reproductor->stop();
                //reproductor->setSource(wave_inoperante);
                reproductorMulti->stop();
                //index_wave = INDEX_INOPERANTE;
                //listaReproduccion->setCurrentIndex(INDEX_INOPERANTE);
                //listaReproduccion->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
                //reproductorMulti->setPlaylist(listaReproduccion);
                reproductorMulti->setMedia(wave_inoperante);
                wave_actual = wave_inoperante;
                //reproductor->play();
                //reproductorMulti->play();
                cambioAudio = false;
                qDebug() << "[AlarmaAudLed] reproducir alarma inoperante - audio_corriendo true";
            }
            else if(!prioAltaAnt && prioAltaAct){
                prioAltaAnt = true;
                //reproductor->stop();
                reproductorMulti->stop();
                cambioAudio = true;
                //reproductor->setSource(wave_inoperante);
                //index_wave = INDEX_ALTA;
                //listaReproduccion->setCurrentIndex(INDEX_ALTA);
                //listaReproduccion->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
                //reproductorMulti->setPlaylist(listaReproduccion);
                reproductorMulti->setMedia(wave_alta);
                wave_actual = wave_inoperante;
                //reproductor->play();
                //reproductorMulti->play();
                cambioAudio = false;
                qDebug() << "[AlarmaAudLed] reproducir alarma alta- audio_corriendo true";
            }
            else{
                if(!prioAltaAct){
                    cambioAudio = true;
                    //reproductor->stop();
                    reproductorMulti->stop();
                    //reproductor->setSource(wave_media);
                    //index_wave = INDEX_MEDIA;
                    //listaReproduccion->setCurrentIndex(INDEX_MEDIA);
                    //listaReproduccion->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
                    //reproductorMulti->setPlaylist(listaReproduccion);
                    reproductorMulti->setMedia(wave_media);
                    wave_actual = wave_media;
                    //reproductor->play();
                    //reproductorMulti->play();
                    cambioAudio = false;
                    qDebug() << "[AlarmaAudLed] reproducir alarma media- audio_corriendo true";
                }
            }
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void AlarmaAudLed::detenAlarma(int tipo){
    try {
        //qDebug() << "detenAlarma int tipo: " + QString::number(tipo);
        if(tipo == PRESION){
            edoAlarPresion = false;
            state_alarm_pre = false;
        }
        else if(tipo == FRECUENCIA){
            edoAlarFr = false;
            cambiaEstadoAlarma(FRECUENCIA, false);
        }
        else if(tipo == VOLUMEN){
            edoAlarVol = false;
            cambiaEstadoAlarma(VOLUMEN, false);
        }
        else if(tipo == VOLMINIMO){
            edoAlarVolMin = false;
            if(!alarmaAltaActiva()){
                prioAltaAct = false;
                prioAltaAnt = false;
            }
            state_alarm_volMin = false;
        }
        else if(tipo == BATERIA){
            edoAlarBateria = false;
            if(!alarmaAltaActiva()){
                prioAltaAct = false;
                prioAltaAnt = false;
            }
            state_alarm_bateria = false;
        }
        else if(tipo == GASES){
            edoAlarGases = false;
            if(!alarmaAltaActiva()){
                prioAltaAct = false;
                prioAltaAnt = false;
            }
            state_alarm_gases = false;
        }
        else if(tipo == FIO2){
            edoAlarFio2 = false;
            state_alarm_fio2 = false;
        }
        else if(tipo == PRESION_CONFIG){
            edoAlarPreCon = false;
            state_alarm_pre_con = false;
        }
        else if(tipo == APNEA){
            edoAlarApnea = false;
            state_alarma_apnea = false;
        }
        else if(tipo == INOPERANTE){
            edoAlarInoperante = false;
            if(!alarmaAltaActiva()){
                prioAltaAct = false;
                prioAltaAnt = false;
            }
            state_alarma_inoperante = false;
        }
        else if(tipo == ALIMENTACION){
            edoAlarAlimentacion = false;
            state_alarma_alimentacion = false;
        }
        else if(tipo == DESCONEXION){
            if(!alarmaAltaActiva()){
                prioAltaAct = false;
                prioAltaAnt = false;
            }
            edoAlarDesconexion = false;
            state_alarma_desconexion = false;
        }
        else if(tipo == COMUNICACION){
            if(!alarmaAltaActiva()){
                prioAltaAct = false;
                prioAltaAnt = false;
            }
            edoAlarComunicacion = false;
            state_alarma_comunicacion = false;
        }

        bool audio_corriendo = alarmaActiva();
        if(! audio_corriendo){
            /*if(reproductor->isPlaying()){
                reproductor->stop();
            }*/
            reproductorMulti->stop();
            qDebug() << "[AlarmaAudLed] manda a detener, no hay alarmas";
        }
        else{
            if(! prioAltaAct){
                qDebug() << "[AlarmaAudLed] Despues de detener, reanuda con wave_media";
                cambioAudio = true;
                //reproductor->stop();
                reproductorMulti->stop();
                //reproductor->setSource(wave_media);
                //index_wave = INDEX_MEDIA;
                //listaReproduccion->setCurrentIndex(INDEX_MEDIA);
                //listaReproduccion->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
                //reproductorMulti->setPlaylist(listaReproduccion);
                reproductorMulti->setMedia(wave_media);
                wave_actual = wave_media;
                //reproductor->play();
                //reproductorMulti->play();
                cambioAudio = false;
            }
            else{
                qDebug() << "[AlarmaAudLed] Despues de detener, se mantiene wave_alta reproduciendo";
            }
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

bool AlarmaAudLed::alarmaActiva(){
    try {
        return edoAlarPresion || edoAlarFr || edoAlarVol || edoAlarVolMin || edoAlarBateria || edoAlarGases || edoAlarFio2 || edoAlarPreCon || edoAlarApnea || edoAlarInoperante || edoAlarAlimentacion || edoAlarDesconexion || edoAlarComunicacion;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return false;
    }
}

bool AlarmaAudLed::pausaAlarma(){
    try {
        //qDebug() << "pausaAlarma";
        enPausa = true;
        /*if(reproductor->isPlaying()){
            reproductor->stop();
        }*/
        reproductorMulti->stop();
        timerAlarma->start(60000);
        contador = 60;
        timerInfoA->start(1000);
        infoAlarmas->muestra();
        return true;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return false;
    }
}

void AlarmaAudLed::reanudaAlarma(){
    try {
        qDebug() << "[AlarmaAudLed] reanuda Alarma";
        audio_corriendo = alarmaActiva();
        enPausa = false;
        timerAlarma->stop();
        timerInfoA->stop();
        infoAlarmas->oculta();
        /*if(!reproductor->isPlaying()){
            reproductor->setSource(wave_actual);
            reproductor->play();
        }*/
        //listaReproduccion->setCurrentIndex(index_wave);
        //listaReproduccion->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        //reproductorMulti->setPlaylist(listaReproduccion);
        reproductorMulti->setMedia(wave_actual);
        //reproductorMulti->play();
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void AlarmaAudLed::reiniciarAlarmas(){
    try {
        icono_fr->hide();
        icono_vol->hide();
        edoAlarFr = false;
        edoAlarPresion = false;
        edoAlarVol = false;
        edoAlarVolMin = false;
        edoAlarBateria = false;
        edoAlarGases = false;
        edoAlarFio2 = false;
        edoAlarPreCon = false;
        edoAlarApnea = false;
        edoAlarInoperante = false;
        audio_corriendo = false;
        edoAlarAlimentacion = false;
        edoAlarDesconexion = false;
        edoAlarComunicacion = false;
        //toggle
        if(timerToggle->isActive()){
            timerToggle->stop();
        }
        edoToogle = false;
        edoToggleFr = false;
        edoToggleVol = false;
        icono_fr->hide();
        icono_vol->hide();
        reproductorMulti->stop();
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

bool AlarmaAudLed::alarmaAltaActiva(){
    try {
        return edoAlarVolMin || edoAlarBateria || edoAlarGases || edoAlarDesconexion || edoAlarComunicacion;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return false;
    }
}

bool AlarmaAudLed::alarmaMediaActiva(){
    try {
        return edoAlarPresion || edoAlarFr || edoAlarVol || edoAlarFio2 || edoAlarPreCon || edoAlarApnea || edoAlarAlimentacion;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return false;
    }
}
