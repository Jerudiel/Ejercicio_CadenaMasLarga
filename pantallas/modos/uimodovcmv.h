#ifndef UIMODOVCMV_H
#define UIMODOVCMV_H

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

class UiModoVCMV : public QWidget
{
    Q_OBJECT
public:
    explicit UiModoVCMV();
    QString btn;
    QString btnSeleccionado;
    WidgetParametro * vcmv_vtinsp;
    WidgetParametro * vcmv_peep;
    WidgetParametro * vcmv_fr;
    WidgetParametro * vcmv_flujo;
    WidgetParametro * vcmv_meseta;
    WidgetParametro * vcmv_oxi;
    QGroupBox * TriggerBox;
    QFont * fuente;
    MySwitch * switchTrigger;
    QStackedWidget * conte_trigger;
    WidgetParametro * trigger_p;
    WidgetParametro * trigger_f;
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
    bool buscar_limites();
    void recalcular_vt_max();
    void obtener_info_adicional();
    void mostrar_mensaje(QString mensaje);
public slots:
    void outTimer();

signals:

};

#endif // UIMODOVCMV_H
