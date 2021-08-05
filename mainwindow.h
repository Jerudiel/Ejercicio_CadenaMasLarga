#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "consultas.h"
#include "consultasdb.h"

#include <QStackedWidget>
#include <QDateTime>
#include <QProcess>
#include <QSettings>
#include "monitor.h"
#include "pantallas/uiconfiguracion.h"
#include "pantallas/uialarmas.h"
#include "utilidades/reloj.h"
#include "tarjetas/teclado.h"
#include "utilidades/ventanaaviso.h"
#include <QTimer>
#include <utilidades/serverws.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(ServerWS *servidor = nullptr, QWidget *parent = nullptr, bool debug_t = false, bool debug_c = false, bool debug_s = false);
    ~MainWindow();
    ServerWS *server;
    QStackedWidget * contenedorPrincipal;
    //Consultas *consul;

    ConsultasDb *consul;

    Monitor * monitor;
    UiConfiguracion *configuracion;
    UiAlarmas *alarmas;
    Reloj *reloj;
    Teclado *serTeclado;
    int ENVIAR_SIGNOS;
    bool avisoTeclaActivo;
    bool avisoPresiActivo;
    bool avisoVentiActivo;
    int tecladoConectado;
    int tecladoComandoRecibido;
    int contadorTeclado = 0;
    QTimer *timerTeclado;
    float duration = 0.12;
    int freq = 1209;

    VentanaAviso *vAviso;


    void edoTeclaActivo(bool estado);
    void edoPresiActivo(bool estado);
    void edoVentiActivo(bool estado);
    void beep();
    //void recteclado();
    void teclado(QString trama);
    //void _closepopup();
    void obtener_modo();
    void abrePantallaMonitor();
    void abrePantallaAlarmas();
    void abrePantallaConfiguracion();
    void set_date(QString trama);

    QSettings *config;

public slots:
    void recteclado(QString trama);
    void muestraAviso(QString mensajes);
    void _closepopup();
    void revisarConexionTeclado();
    void tecladoVirtual(QString trama);
    //void calibrarTeclado(QString trama);
    //void get_mode_keyboard_command(QString trama);
    //void get_umbral_key_command(QString trama);
    //void get_umbral_keyboard_command(QString trama);
    void send_frame_keyboard(QString trama);
    void set_watch(QString date);
    void get_last_event();
    void mandaActivarBloqueoPrimeraVez();

};
#endif // MAINWINDOW_H
