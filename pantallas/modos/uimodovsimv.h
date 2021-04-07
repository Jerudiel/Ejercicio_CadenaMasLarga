#ifndef UIMODOVSIMV_H
#define UIMODOVSIMV_H

#include <QWidget>

#include <QWidget>
#include <QString>
#include <utilidades/widgetparametro.h>
#include <utilidades/myswitch.h>
#include <QGroupBox>
#include <QFont>
#include <QStackedWidget>
#include <QLabel>
#include <QPushButton>
#include <QStringList>
#include <QStyleOption>
#include <QThread>
#include <QTimer>

class UiModoVSIMV : public QWidget
{
    Q_OBJECT
public:
    explicit UiModoVSIMV();
    QString btn;
    QString btnSeleccionado;
    WidgetParametro * vsimv_vtinsp;
    WidgetParametro * vsimv_psoporte;
    WidgetParametro * vsimv_peep;
    WidgetParametro * vsimv_fr;
    WidgetParametro * vsimv_flujo;
    WidgetParametro * vsimv_meseta;
    WidgetParametro * vsimv_oxi;
    QGroupBox * TriggerBox;
    QFont * fuente;
    MySwitch * switchTrigger;
    QStackedWidget * conte_trigger;
    WidgetParametro * trigger_p;
    WidgetParametro * trigger_f;
    WidgetParametro * vcpap_apnea;
    QLabel * labelIE;
    QLabel * labelTE;
    QLabel * labelTI;
    QPushButton * btnguardarCambios;
    QLabel * labelInfo;
    int elemento_seleccionado;
    float ti;
    float te_min;
    float ti_min;
    float tp_min;
    float pi_max;
    float ti_max;
    float vt_max;
    float flujo_max;
    float tp_max;
    float fr_max;

    QTimer *timerMensaje;

    void retranslateUi();
    virtual void paintEvent(QPaintEvent *event);
    int get_elemento_seleccionado();
    void set_trigger(QString estado);
    void update_trigger();
    void set_elemento_seleccionado(int elemento);
    void boton_activado();
    void boton_inactivado();
    void trigger_inactivo();
    void trigger_activo();
    void estado_switch(bool estado);
    void mover_izquierda();
    void mover_derecha();
    int mover_arriba();
    int mover_abajo();
    void sumar();
    void restar();
    void switch_trigger();
    void cambiaTipoTrigger();
    void cambiaPerilla();
    void cargar_valores(QStringList lista_valores);
    QStringList obtener_valores();
    void recalcular_tp_max();
    void recalcular_vt_max();
    bool buscar_limites();
    void obtener_info_adicional();
    void mostrar_mensaje(QString mensaje);
public slots:
    void outTimer();
signals:

};

#endif // UIMODOVSIMV_H
