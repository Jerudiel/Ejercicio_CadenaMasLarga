#ifndef ALARMASX_H
#define ALARMASX_H

#include <QWidget>
#include <QPixmap>
#include <QDir>
#include <QLabel>
#include <QTimer>
#include <QtMultimedia/QSoundEffect>
#include <QProcess>

class AlarmasX : public QWidget
{
    Q_OBJECT
public:
    explicit AlarmasX(QWidget *parent = nullptr);
    int estadoP;
    int estadoB;
    bool toggleB;
    bool toggleBEdo;

    QPixmap *irespiOn;
    QPixmap *irespiOff;

    QPixmap *ibat100;
    QPixmap *ibat75;
    QPixmap *ibat50;
    QPixmap *ibat25;
    QPixmap *ibat00;
    QPixmap *ibatAC;

    QPixmap *ibat100c;
    QPixmap *ibat75c;
    QPixmap *ibat50c;
    QPixmap *ibat25c;
    QPixmap *ibat00c;

    QLabel *lrespi;
    QLabel *lbateria;

    QSoundEffect *reproductor;
    bool audio_corriendo;

    QTimer *timer_act;

    void beep();
    void iniciar_alarma();
    void hilo_audio_media();
    void detener_alarma();

    void trigger(int estado);
    void bateria(int nivel, int modo);


    float duration;
    int freq;
public slots:
    void termina_reproductor();
    void actualiza();

signals:

};

#endif // ALARMASX_H

