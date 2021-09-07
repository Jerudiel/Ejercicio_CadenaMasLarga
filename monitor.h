#ifndef MONITOR_H
#define MONITOR_H

#include <QWidget>

#include <QFont>
#include <QRect>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QString>
#include <QPushButton>
#include <QSizePolicy>
#include <QPalette>
#include <QTimer>
#include <QMap>
#include <QGridLayout>
#include <QtGui/QGuiApplication>
#include <QVector>

#include "signos/widgetsigno3.h"
#include "utilidades/widgetsignobar.h"
#include "consultas.h"
#include "consultasdb.h"
#include "utilidades/alarmasx.h"
#include "utilidades/infoalarma.h"
#include "tarjetas/ventilador.h"
#include "tarjetas/senpresion.h"
#include "utilidades/alarmaaudled.h"
#include "utilidades/ventanamenu.h"
#include "utilidades/ventanaconfirmacion.h"
#include "utilidades/ventanapruebas.h"
#include "utilidades/ventanacalibrar.h"
#include "utilidades/tramas/tramas.h"
#include "utilidades/uiqwidgetmenugrafica.h"
#include "utilidades/ventanaaviso.h"
#include "utilidades/ventanaavisotest.h"
#include "utilidades/ventanainfo.h"
#include "utilidades/widgetgrafica.h"
#include "utilidades/widgetgraficalazo.h"
#include "utilidades/ventanainsfuga.h"
#include "utilidades/ventanainsoxi.h"
#include "utilidades/ventanaconfigpi.h"
#include "utilidades/ventanainoperante.h"
#include "utilidades/gpio.h"

class Monitor : public QWidget
{
    Q_OBJECT
public:
    explicit Monitor(QWidget *parent = nullptr, ConsultasDb *consul = nullptr, bool debug_c = false, bool debug_s = false, bool control_gases = false);

    QWidget * mainwindow;
    QFont * fuente;
    ConsultasDb *consul;
    QWidget * centralwidget;
    QWidget * horizontalLayoutWidget;
    QHBoxLayout * principalLayout;
    QVBoxLayout * contenidoLayout;
    QHBoxLayout * informacionLayout;
    QVBoxLayout * debugLayout;
    QLabel * label_Modo;
    QLabel * label_debug;
    QHBoxLayout * botonesLayout;
    QString estiloBotonA;
    QString estiloBotonI;
    QPushButton * btn_ventilador;
    QPushButton * btn_grafica;
    QPushButton * btn_test;
    AlarmasX *widgetAlarms;
    QLabel * label_info_alarma;
    QVBoxLayout * graficaLayout;
    QGridLayout * graphiclayout;
    bool estadoVentilador;
    bool cambiagrafi;
    int contadorGrafica;
    QHBoxLayout * gridLayoutInf;
    QPalette *paleNormal;
    QPalette *paleAlta;
    QPalette *palemedia_baja;
    WidgetSignoBar * signoPIP;
    WidgetSignoBar * signoPEEP;
    WidgetSignoBar * signoPLATEU;
    WidgetSignoBar * signoTiempoI;
    WidgetSignoBar * signoTiempoE;
    WidgetSignoBar * signoVm;
    QVBoxLayout * barLayout;
    QVBoxLayout * menuLayout;
    InfoAlarma *infoAlarmas;
    QLabel * label_fecha;
    QVBoxLayout * opcionesLayout;
    WidgetSigno3 * widgetPresPrin;
    WidgetSigno3 * widgetVoli;
    WidgetSigno3 * widgetVole;
    WidgetSigno3 * widgetFR;
    WidgetSigno3 * widgetTiTe;
    WidgetSigno3 * widgetFlujo;
    int contadorErrorConVent;
    Ventilador *serVent;
    int numero_datos_presion;
    bool banderaConexionSenPresion;
    int banderaModoSenPresion;

    QTimer *timerTPresion1S;
    int timerCont1S;
    bool timerActivo1S;

    QTimer *timerTPresion5S;
    int timerCont5S;
    bool timerActivo5S;

    int tpresionModo;

    SenPresion *serPresion;

    int elementSel;

    AlarmaAudLed *alarmaControl;

    bool estadoAlarmaPresion;
    bool estadoAlarmaVol;
    bool estadoAlarmaFr;
    bool estadoAlarmaVolMin;
    bool estadoAlarmaBateria;
    bool estadoAlarmaGases;
    bool estadoAlarmaFIO2;
    bool estadoAlarmaApnea;
    bool estadoAlarmaSensores;
    bool estadoAlarmaAlimentacion;
    bool estadoAlarmaDesconexion;

    bool estadoAlarmaMec;
    bool estadoAlarmaEner;
    bool estadoAlarmaNeu;
    bool estadoAlarma1;
    bool estadoAlarma2;

    QString tramaConfigVent;
    bool alarmaboolean;

    QString modoVentilador;

    QString tramaVentilador;

    QString tramaV;

    bool configurandoVentilador;
    bool primera_vez_ventilador;
    bool banderaPosicionVentilador;
    bool banderaOffsetVentilador;
    bool banderaModoVentilador;
    bool banderaTramaVentilador;
    int numeroBanderaVentilador;
    int contadorBanderaConxVent;

    QTimer *timerVentilador;
    bool banderaConexionVentilador;

    QTimer *timerConVentilador;

    QTimer *timerConfigVent;

    QTimer *timerOffsetsVent;

    bool senPresionListo;
    bool origenListo;
    int contadorOrigen;
    int contadorVVentilador;

    QString trama_c_senpresion;
    QString trama_w_serpresion;
    bool banderConfigCLista;
    bool dentroTimerValida5s;
    bool configurandoSenPresion;

    QString versionVentiladorEsperada;
    QString versionSenPresionEsperada;
    QString versionTecladoEsperada;
    QString versionVentilador;
    QString versionSenPresion;
    QString versionTeclado;

    bool vrecibidaVentilador;
    bool vrecibidaSenpresion;

    QString versionPi;
    QString estadoAlarmasVentilador;
    QString estadoAlarmasVentiladorControl;
    QString estadoAlarmasSensores;

    bool error_sensores_sensor_presion;
    bool error_sensores_sensor_inhalacion;
    bool error_sensores_sensor_exhalacion;

    QTimer *timerLimpiarBuffer;

    QTimer *timerEstadoSenPresion;
    int contadorTimerEstadoSenPresion;
    bool banderaTimerEstadoSenPresion;

    QTimer *timerTerminaConfigurar;

    bool tecladoListo;
    int contadorTerminaConfigurar;
    bool ventiladorListo;
    bool primera_vez_offset_ventildor;

    bool sentido_giro;

    QString tramaCambiosCalibrar;

    bool huboCambioModo;
    QString ultimoModo;
    QString nuevoModo;
    bool huboCambioTrama;
    QString ultimaTrama;
    bool primera_vez_modo;
    QString temp_peep;

    QTimer *temp_timer_ini;

    QTimer *temp_timer_det;

    int modoSel;

    bool primera_vez_modo_sen_presion;
    QString ultimaTramaSenPresion;
    QString tramaSenPresion;
    bool huboCambioTramaSenPresion;

    void retranslate_ui();

    QString trama_w;
    QString trama_w_ultima;
    bool primera_vez_modo_sen_presion_w;
    bool huboCambioTramaSenPresionW;

    int indiceMsg1;
    bool vTestActiva;

    QTimer *temp_actua;

    QString trigger_activar;
    QString trigger_ult_est;

    QTimer *timerMuestraAlarmas;

    QStringList *lista_alarmas;
    int contadorMuestraAlarmas;
    int contador_respuesta_config_senrpesion;

    QMap<QString, QString> *dict_color_muestra_alarma;

    float min_grafica_presion;
    float max_grafica_presion;
    float min_grafica_volumen;
    float max_grafica_volumen;
    float min_grafica_flujo;
    float max_grafica_flujo;
    float modo_graficas;

    float min_lazo_pres_x;
    float max_lazo_pres_x;
    float min_lazo_vol_y;
    float max_lazo_vol_y;

    float min_lazo_vol_x;
    float max_lazo_vol_x;
    float min_lazo_flujo_y;
    float max_lazo_flujo_y;

    QString ultimo_estado_nobreak;
    bool primera_vez_nobreak;

    bool recuperado;
    bool ventanaAbierta;

    int boton_seleccionado_menu;
    int boton_seleccionado_calibracion;
    int boton_seleccionado_pruebas;

    VentanaMenu *menu;

    int contador_apagar;

    VentanaConfirmacion *ventana_confirmacion;
    bool espera_parar;
    bool espera_iniciar;
    bool espera_actualizar;
    bool espera_apagar;
    QTimer *timerConfirmacion;
    int contador_confirmacion;
    int boton_seleccionado_confirmacion;

    VentanaPruebas *pruebas;

    VentanaInsFuga *fugas;

    VentanaInsOxi *oxis;

    VentanaCalibrar *calibrar;

    VentanaConfigPI *configPI;

    VentanaInoperante *ventanaInoperante;
    bool ventanaInoperanteAbierta;

    VentanaInfo *ventanaInfo;
    QTimer *timerVentanaInfo;
    void mostrarVentanaInfo(QString mensaje);

    bool inicializacion;

    int numero_prueba;
    bool pruebas_iniciales;
    bool sensores_estado;
    int presion_tope;
    int presion_pruebas;
    int presion_inicial_pruebas;
    int presion_inicial_salida;
    int contador_pruebas_iniciales;
    QMap<int, int> *dic_presion_tope;
    QMap<int, int> *dic_tiempo_presion;
    QMap<int, int> *dic_tiempo_presion_fuga;
    QMap<int, int> *dic_tiempo_presion_salida;
    QTimer *timerPresion;
    QTimer *timerPresionFinal;
    QTimer *timerPresionSalida;
    QTimer *timerFinPruebaPresion;
    int contador_valvulas;
    QString pwm_100;
    QString pwm_50;
    QString pwm_25;
    QString pwm_0;
    QString exa_0;
    QString exa_1;
    QString estado_trama_valvulas;
    QMap<int, QString> *dic_trama_valvulas;
    bool esperando_presion_tope;
    bool esperando_presion_salida;
    bool fin_prueba_presion_serpresion;
    bool fin_prueba_presion_serventilador;
    bool buscar_q_tope;

    QTimer *timerOxigeno;
    int contador_timerOxigeno;

    bool pruebas_terminadas;

    Tramas *tramas;



    QTimer *timerBorrar;

    int min_entrada_aire;
    int min_entrada_oxi;
    int max_entrada_aire;
    int max_entrada_oxi;

    QMap<QString, int> *diccionario_alarma;

    bool es_actualizacion;

    bool falla_actualizacion;

    int entrada_aire;
    int entrada_oxigeno;
    int sensor_presion_c;

    UiQWidgetMenuGrafica *submenugrafica;

    bool volverIntetarComandoM;
    bool volverIntentarModo;

    bool revisar_presion_tope;
    bool revisar_liberacion_presion;

    bool desactivar_s;

    bool ventiladorInoperante;

    VentanaAviso *vAvisoV;
    VentanaAviso *vAviso;

    int contador_paro_tarjeta_sensores;
    QTimer *timerVentiladorDetenido;
    bool fue_h;
    bool recibe_a0;
    bool reenviar_paro;
    int contador_reenvio;
    bool listo_medir_fio2;
    QTimer *timerFIO2;

    bool cambiosCalibrar;
    bool cambiosOffsets;
    QString tramaOffsets;
    void cargarTramaOffsets();
    int contadorOffsetsVentilador;

    int altura_prog;
    bool tipo_sensor_presion;

    VentanaAviso *vAvisoC;

    int tiempo_respuesta_ventilador;

    QString alarma_pres_max;
    QString alarma_pres_min;
    QString alarma_volmin_max;
    QString alarma_volmin_min;
    QString alarma_fr_max;
    QString alarma_fr_min;
    QString alarma_vol_max;
    QString alarma_vol_min;
    QString alarma_apnea;

    QString nivel_oxigeno;
    QString modo_nobreak;
    QString nivel_batt;

    VentanaAvisoTest *vAvisoT;

    bool mostrarGrafica;
    bool serPresionListo;

    WidgetGrafica *graficaPresion;
    WidgetGrafica *graficaVolumen;
    WidgetGrafica *graficaFlujo;

    WidgetGraficaLazo *graficaPV;
    WidgetGraficaLazo *graficaVF;

    float ult_temp_nivel_bat;

    QTimer *timerListoApagar;
    bool listoApagarControl;
    bool listoApagarSensores;
    int listoApagarContador;

    void mostrar_confirmacion(QString texto);


    void tecla_confirmacion(QString tecla);
    void cambiagraficas();
    //void grafica_lazos();
    void limpiar_graficas();
    void abrir_menu_graficas();
    void abrir_menu();
    void tecla_menu(QString tecla);

    void tecla_pruebas(QString tecla);
    void iniciar_pruebas();
    void siguiente_pruebas();

    void detener_pruebas_presion();

    void tecla_calibracion(QString tecla);

    void preguntarVersiones();

    void configurar_grafica(QString nombre, QString titulo, float min, float max);
    void configurar_grafica_lazo(QString nombre, QString tituloy, QString titulox, float miny, float maxy, float minx, float maxx);


    //void iniciaMonSensores();
    void contornoColor(WidgetSigno3 *widget);
    void contornoColorAlarma(WidgetSigno3 *widget, QString color);
    void actualizarParametros();
    void obtener_trama_alarmas_senpresion();
    void obtener_configuracion_PCMV();
    void obtener_configuracion_VCMV();
    void obtener_configuracion_PSIMV();
    void obtener_configuracion_VSIMV();
    void obtener_configuracion_PCPAP();
    void obtener_configuracion_VCPAP();
    void llenarConfiguracionPCMV();
    void llenarConfiguracionVCMV();
    void llenarConfiguracionPSIMV();
    void llenarConfiguracionVSIMV();
    void llenarConfiguracionPCPAP();
    void llenarConfiguracionVCPAP();
    void actualizarAlarmas();
    void cargaValoresDBAlarmas(QStringList valores);
    //void edoPresiActivo(bool estado);
    //void edoVentiActivo(bool estado);
    void obtener_trama_config();
    void obtenerTramaPCMV();
    void obtenerTramaVCMV();
    void obtenerTramaPSIMV();
    void obtenerTramaVSIMV();
    void obtenerTramaPCPAP();
    void obtenerTramaVCPAP();
    QString formato3bytes(QString val);
    //void receVent();
    void libera();
    void no_libera();
    void no_fuga();
    void fuga();


    void muestraAvisoConfig(QString mensajes);
    void muestraAvisoApagar(QString mensajes);
    void muestraAviso(QString mensajes);
    //void muestraAvisoVentilador(QString mensajes);
    void muestraAvisoTest(QString mensajes);


    //void recePresion();




    void controlVentilador();
    void obtener_trama_c_senpresion();
    QString obtener_modo_vent();


    void teclado(QString tecla);
    void teclaOk();
    void seleccionar_grafica();
    void obtener_nuevo_rango_grafica(QString modo);
    void zoom_grafica(QString modo);
    void obtener_nuevo_espacio_grafica(QString modo);
    void desplazar_grafica(QString tecla);

    void mover(QString tecla);
    void elementoSeleccionado();

    void eliminar_alarma_de_lista(QString alarma);

    QString obtener_fecha();
    bool buscar_en_lista(QString alarma);
    void agregar_en_lista(QString alarma,int estado);
    void actualizar_en_lista(QString alarma,int estado);
    void borrar_en_lista(QString alarma);
    void borrar_alarmas();

    QString obtener_modo();

    //mod de hilos python a hilos y timers c++
    int beep_frecuencia;
    int beep_veces;
    float beep_tiempo;
    float beep_pausa;
    QTimer *timerBeep;

    QTimer *timerRAV;

    QTimer *timerREG;

    bool RA_setear;
    bool RA_limpiar;
    QTimer *timerRA;

    QString RAS_tipo;
    int RAS_estado;
    QTimer *timerRAS;

    QString PD_vi;
    QString PD_ve;
    QString PD_vm;
    QString PD_fr;
    QString PD_ti;
    QString PD_te;
    QString PD_pip;
    QString PD_peep;
    QString PD_fp;
    QTimer *timerPD;

    bool esperando_limites_lazos;

    int contador_wdt = 0;
    QTimer *timerErrorWDT;

    int contador_wdt_ino;
    bool actualiza_por_wdt;

    QStringList *lista_wdt;
    //QTimer *timer1HoraWDT;
    void revisarErroresWDT();

    bool cambiosCalTeclado;
    void envia_trama_teclado(QString presionar, QString soltar);
    int calTecladoPres;
    int calTecladoSolt;
    void revisar_cal_teclado(QString trama);

    bool infoAbierta;
    void tecla_info(QString tecla);

    bool intentar_otro_pwm;
    QTimer *timerOtroPWM;

    int vida_o2_21;
    int vida_o2_100;

    void actualizar_fio2();

    bool ino_wdt_alarm;

    float offset_pip;
    void actualizar_off_pip();

    void cargarAltura();
    void aplicarCambiosAltura();
    void cambiarAltura(QString tecla);
    int altura_perilla;
    QTimer *timerCambiosPerilla;

    bool cambiosMIni;
    QTimer *timerMIniVent;
    int contadorMIniVentilador;

    void get_mode_keyboard();
    void check_mode_keyboard(QString trama);
    void check_umbral_key(QString trama);
    void check_umbral_keyboard(QString trama);
    void change_mode(int mode);
    void get_config_key(int key);
    void set_config_key(int key, QString press, QString release);
    void get_config_keyboard();
    void set_config_keyboard(QString press, QString release);
    QString set_format_frame(int value, int size);
    void watchDataKeyboard(QString trama);

    bool isReadyModeKeyboard;
    int valueModeKeyboard;
    bool isWaitingMode;

    bool isWaitingKey;
    bool isReadyConfigKey;
    QString nameConfigKey;
    int valuePressKey;
    int valueReleaseKey;

    bool isWaitingConfigKeyboard;
    bool isReadyConfigKeyboard;
    int valuePressKeyboard;
    int valueReleaseKeyboard;

    bool isConfigKeyboard;

    bool isReadyKeyFromKeyboard;
    QString valueFromKeyboard;

    void activarAlarmaComunicacionControl1();
    void activarAlarmaComunicacionControl2();
    void desactivarAlarmaComunicacionControl1();
    void desactivarAlarmaComunicacionControl2();

    bool estadoAlarmaComunicacion;
    bool primera_vez_comunicacion_control;
    QString ultimo_estado_comunicacion_control_1;
    QString ultimo_estado_comunicacion_control_2;

    bool primera_vez_comunicacion_sensores;
    QString ulimo_estadoAlarmasSensores;

    void activarAlarmaComunicacionSensores(int tipo);
    void desactivarAlarmaComunicacionSensores(int tipo);

    bool estadoAlarmaSonoraGases();

    bool pruebasPresionTerminadas;

    QTimer *timerMensajeVentanaPruebas;
    void ponerMensajeVentanaPruebas(QString mensaje);

    bool cargaMonitorListo;

    bool corroborarVersionControl(QString trama, QString esperada);
    QVector<int> separarVersion(QString trama);

    void get_last_event();

    int top_presure;
    int stable_presure;
    int second_stable_presure;
    int final_presure;

    int air_psi_final;
    int o2_psi_final;
    int fio2_final;
    int fio2;

    bool carga_primera_vez_fio2;

    QString ultimo_valor_alarma_aire;
    QString valor_alarma_aire;
    bool primera_alarma_aire;
    int contador_alarma_aire;
    bool desactivar_alarma_aire;

    int contador_p_aire;
    int contador_p_oxi;

    QString s_air_psi_final;
    QString s_o2_psi_final;

    //recuperacion modo test
    bool recuperacion_modo_test;

    bool listo_borrar_alarma;
    int indice_borrar_alarma;
    QString nombre_borrar_alarma;

    //buffer parametros
    bool Actualiza_buffer_fio2;
    QMap<int, QString> *dict_buffer_signos;
    void Agregar_buffer_signo(int signo, QString valores);
    void mostrar_buffer_signos();
    void colorear_buffer_signos(QString color);
    bool hay_datos_buffer_standby;
    void colorear_default_buffer_signos();
    bool primera_vez_buffer;

    //ventana inoperante
    void tecla_inoperante(QString tecla);

    //timer por si no responde
    QTimer *timerPingMuerto;
    bool pingSensoresVivo;
    bool pingControlVivo;

    //bandera control_gases
    bool control_gases;
    bool bloqueo_gases;

    int contador_act_dif_gases;
    int contador_desact_dif_gases;

    //timer reiniciar ping
    QTimer *timerReiniciarPing;

    //obtener parametros
    QString obtener_parametros();
    QString obtener_params_modo(QString modo);

    //tiempo trabajando
    QTimer *timerTrabajando;
    QString obtenerTiempoTrabajado();
    QString obtenerTiempoAcumulado();
    void guardarTiempoTrabajadoAcumulado();
    void revisarTiempoAcumulado();
    void detenerTiempoAcumulado();
    void iniciarTiempoAcumulado();

    //mantenimiento
    QTimer *timerMantenimiento;
    float horaParaMantenimiento;
    int intervaloRecordatorioMantenimiento;
    int intervaloPreguntarPorMantenimiento;
    bool necesitaMantenimiento;
    VentanaInoperante *ventanaRecordatorioMantenimiento;
    bool ventanaRecordatorioMantenimientoAbierta;
    void tecla_mantenimiento(QString tecla);

    Gpio *gpio;

public slots:
    void revisarErrorWDT();

    void validaUnSeg();
    void validaCincoSeg();

    void receVent(QString trama);
    void muestraAvisoVentilador(QString mensajes);
    void cierraAvisoVentilador();
    //void edoVentiActivo(bool estado);

    void recePresion(QString trama);
    void muestraAvisoPresion(QString mensajes);
    void cierraAvisoPresion();
    //void edoPresiActivo(bool estado);
    void iniciaMonSensores();


    void actualizarDatosVentilador();
    void controlGrafica();
    void revisarBanderasVentilador();
    void revisarConfigVentilador();
    void revisarOffsetVentilador();
    void revisarMIniVentilador();
    void revisarConexionVentilador();

    void limpiarBuffer();
    void revisarEstadoSenPresion();
    void revisarTerminaConfigurar();

    void iniciar_ventilador();
    void detener_ventilador();
    void actuaTest();
    void muestraAlarmas();

    void abrir_calibracion();
    void abrir_pruebas();
    void espera_si_confirmacion();
    void espera_no_confirmacion();
    void timer_esperando_confirmacion();
    void cerrar_calibracion();

    void prueba_presion();
    void prueba_presion_final();
    void prueba_presion_salida();
    void revisar_fin_prueba_presion();

    void respuesta_oxigeno();
    void borrar_eventos();

    void ventilador_detenido();
    void activar_fio2();

    //mod de hilos python a hilos y timers c++
    void beep(); //int frecuencia, int veces, float tiempo, float pausa

    void revisar_alarmas_ventilador();
    void revisar_entra_gases();
    void reiniciar_alarmas();
    void revisar_alarmas_senpresion();
    void poner_datos();
    void revisarListoApagar();

    void cerrarFugas();
    void cerrarOxis();

    void iniciar_pruebas_2();

    void aplicarAltura();

    void limpiarInfoAltura();

    void limpiarMensajeVentanaPruebas();

    void ocultarVentanaInfo();

    void revisarPingMuerto();

    void revivirPing();

    void aumentaTiempoTrabajando();

    void revisarMantenimiento();

signals:
    void calTeclado(QString trama);
    void get_mode_keyboard_frame(QString frame);
    void get_umbral_key(QString frame);
    void get_umbral_keyboard(QString frame);
    void send_frame(QString frame);
    void set_watch(QString date);
    void activarBloqueoPrimeraVez();
};

#endif // MONITOR_H
