#ifndef UIMODOPSIMV_H
#define UIMODOPSIMV_H

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

class UiModoPSIMV : public QWidget
{
    Q_OBJECT
public:
    explicit UiModoPSIMV();
    QString btn;
    QString btnSeleccionado;
    WidgetParametro * psimv_pinsp;
    WidgetParametro * psimv_psoporte;
    WidgetParametro * psimv_peep;
    WidgetParametro * psimv_fr;
    WidgetParametro * psimv_tinsp;
    WidgetParametro * psimv_oxi;
    QGroupBox * TriggerBox;
    QFont * fuente;
    MySwitch * switchTrigger;
    QStackedWidget * conte_trigger;
    WidgetParametro * trigger_p;
    WidgetParametro * trigger_f;
    QLabel * labelIE;
    QLabel * labelTE;
    QLabel * labelPF;
    QPushButton * btnguardarCambios;
    QLabel * labelInfo;
    int elemento_seleccionado;
    int max_peep_mas_pip;
    float min_te_min;
    float min_ti;

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
    bool obtener_max_peep_mas_pip();
    void recalcular_ti();
    void obtener_info_adicional();
    void mostrar_mensaje(QString mensaje);
public slots:
    void outTimer();

signals:

};

#endif // UIMODOPSIMV_H
