#ifndef ALARMAAUDLED_H
#define ALARMAAUDLED_H

#include <QWidget>
#include "utilidades/infoalarma.h"
#include <QUrl>
#include <QTimer>
#include <QtMultimedia/QSoundEffect>
#include <QDebug>
#include <QDir>
#include <QtCore>
#include <QAudioDeviceInfo>
#include <QMediaPlayer>
#include <QMediaPlaylist>

class AlarmaAudLed: public QWidget
{
    Q_OBJECT
public:
    AlarmaAudLed(InfoAlarma *infoAlarmas);
    int PRESION     = 0;
    int FRECUENCIA  = 1;
    int VOLUMEN     = 2;
    int VOLMINIMO   = 3;
    int BATERIA 	= 4;
    int GASES		= 5;
    int FIO2		= 6;
    int PRESION_CONFIG = 7;
    int APNEA		= 8;
    int INOPERANTE = 9;
    int ALIMENTACION = 10;
    int DESCONEXION = 11;
    int COMUNICACION = 12;

    int INDEX_BAJA = 0;
    int INDEX_MEDIA = 1;
    int INDEX_ALTA = 2;
    int INDEX_INOPERANTE = 3;

    int index_wave;

    QSoundEffect *reproductor;

    QMediaPlayer *reproductorMulti;
    QMediaPlaylist *listaReproduccion;

    InfoAlarma *infoAlarmas;
    bool audio_corriendo;
    QUrl wave_alta;
    QUrl wave_media;
    QUrl wave_baja;
    QUrl wave_inoperante;
    QUrl wave_actual;

    bool state_alarm_vol;
    bool state_alarm_pre;
    bool state_alarm_fr;
    bool state_alarm_volMin;
    bool state_alarm_bateria;
    bool state_alarm_gases;
    bool state_alarm_fio2;
    bool state_alarm_pre_con;
    bool state_alarma_apnea;
    bool state_alarma_inoperante;
    bool state_alarma_alimentacion;
    bool state_alarma_desconexion;
    bool state_alarma_comunicacion;

    QLabel *icono_vol;
    QLabel *icono_fr;

    bool edoAlarPresion;
    bool edoAlarVol;
    bool edoAlarFr;
    bool edoAlarVolMin;
    bool edoAlarBateria;
    bool edoAlarGases;
    bool edoAlarFio2;
    bool edoAlarPreCon;
    bool edoAlarApnea;
    bool edoAlarInoperante;
    bool edoAlarAlimentacion;
    bool edoAlarDesconexion;
    bool edoAlarComunicacion;

    bool cambioAudio;

    QTimer *timerAlarma;

    bool prioAltaAct;
    bool prioAltaAnt;

    bool prioInoperante;

    bool enPausa;

    QTimer *timerToggle;

    bool edoToggleFr;
    bool edoToggleVol;
    bool edoToogle;
    bool edoToogleBateria;
    bool edoToogleGases;
    bool edoToogleFio2;
    bool edoTooglePreCon;
    bool edoToogleApnea;
    bool edoToogleInoperante;
    bool edoToogleAlimentacion;
    bool edoToogleDesconexion;
    bool edoToogleComunicacion;

    bool toggleFR;
    bool toggleVOL;

    QTimer *timerInfoA;

    int contador;

    qint64 duracion_sonido;


    void setIconoFre(QLabel *icono_fr);
    void setIconoVol(QLabel *icono_vol);

    void cambiaEstadoAlarma(int alarma, bool estado);
    void iniciaAlarma(int tipo);
    void detenAlarma(int tipo);
    bool alarmaActiva();
    bool pausaAlarma();

    void reiniciarAlarmas();


public slots:
    void termina_reproductor();
    void reanudaAlarma();
    void toggle();
    void actualizaTiempo();
    void positionChanged(qint64 posicion);
    void durationChanged(qint64 duracion);
    //void mediaChanged(QMediaContent contenido);
    //void mediaStatusChanged(QMediaPlayer::MediaStatus mediaStatus);
    //void stateChanged(QMediaPlayer::State state);
};

#endif // ALARMAAUDLED_H
