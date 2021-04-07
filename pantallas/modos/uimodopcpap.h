#ifndef UIMODOPCPAP_H
#define UIMODOPCPAP_H

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

class UiModoPCPAP : public QWidget
{
    Q_OBJECT
public:
    explicit UiModoPCPAP();
    QString btn;
    QString btnSeleccionado;
    WidgetParametro * pcpap_cpap;
    WidgetParametro * pcpap_ps;
    WidgetParametro * pcpap_oxi;
    QGroupBox * TriggerBox;
    QFont * fuente;
    MySwitch * switchTrigger;
    QStackedWidget * conte_trigger;
    WidgetParametro * trigger_p;
    WidgetParametro * trigger_f;
    WidgetParametro * pcpap_apnea;
    QGroupBox * RespaldoApnea;
    WidgetParametro * respaldo_fr;
    WidgetParametro * respaldo_pinsp;
    WidgetParametro * respaldo_tinsp;
    QLabel * labelIE;
    QLabel * labelTE;
    QLabel * labelTI;
    QPushButton * btnguardarCambios;
    QLabel * labelInfo;
    int elemento_seleccionado;
    float min_te_min;
    float min_ti;

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
    void recalcular_ti();
    void obtener_info_adicional();
    void mostrar_mensaje(QString mensaje);
public slots:
    void outTimer();
signals:

};

#endif // UIMODOPCPAP_H
