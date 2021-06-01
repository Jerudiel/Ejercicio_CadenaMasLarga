#ifndef UIMODOPCMV_H
#define UIMODOPCMV_H

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


class UiModoPCMV : public QWidget
{
    Q_OBJECT
public:
    explicit UiModoPCMV();
    QString btn;
    QString btnSeleccionado;
    WidgetParametro * pcmv_pinsp;
    WidgetParametro * pcmv_oxi;
    WidgetParametro * pcmv_peep;
    WidgetParametro * pcmv_fr;
    WidgetParametro * pcmv_tinsp;
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
    float perilla_global;

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

#endif // UIMODOPCMV_H
