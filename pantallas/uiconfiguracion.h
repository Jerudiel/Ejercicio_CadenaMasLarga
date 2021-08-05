#ifndef UICONFIGURACION_H
#define UICONFIGURACION_H

#include <QWidget>

#include <monitor.h>
#include <QString>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTabWidget>
#include <QFont>
#include <QSizePolicy>
#include <QStyleOption>
#include <QPainter>

#include "pantallas/uiconfigmodo.h"
#include "pantallas/uicalibrar.h"
#include "pantallas/uiconfigdatetime.h"
#include "pantallas/uiinfosistema.h"
#include "pantallas/uieventos.h"

class UiConfiguracion : public QWidget
{
    Q_OBJECT
public:
    explicit UiConfiguracion(Monitor * monitor, QWidget *parent = nullptr);
    Monitor * monitor;
    QString btn;
    QString btnSeleccionado;
    QString btnSeleccionadoWidget;
    QString btnNoSeleccionadoWidget;
    QWidget * centralwidget;
    QWidget * horizontalLayoutWidget;
    QHBoxLayout * principalLayout;
    QVBoxLayout * contenidoLayout;
    QHBoxLayout * informacionLayout;
    QVBoxLayout * UsuarioLayout;
    QLabel * label_Modo;
    QLabel * label_Version;
    QHBoxLayout * BotonesLayout;
    QPushButton * btn_reini_config;
    QSizePolicy * sizePolicy;
    QPushButton * btn_eventos;
    QLabel * label_info_alarma;

    QVBoxLayout *infoGases;
    QLabel *lbl_info_aire;
    QLabel *lbl_info_oxi;

    QHBoxLayout * graficaLayout;
    QTabWidget * tabWidget;
    QWidget * tab_config;
    QFont * fuente;
    UiConfigModo * configModo;
    UiInfoSistema *tab_info_sistema;
    UiCalibrar *tab_calibrar;
    UiEventos *tab_eventos;
    UiConfigDatetime *tab_datetime;
    //falta agregar los uitabs

    bool mostrando_eventos;
    int elementSel;

    bool primera_vez_guardado;
    bool primera_vez_bloqueado;
    QTimer *timerPrimeraVez;

    void retranslateUi();
    virtual void paintEvent(QPaintEvent *event);

    void activarModoPCMV();
    void activarModoVCMV();
    void activarModoPSIMV();
    void activarModoVSIMV();
    void activarModoPCPAP();
    void activarModoVCPAP();
    void teclado(QString tecla);
    void teclaOk();
    void teclaOkModo();

    void modo_perilla();
    void cambiarValor(QString tecla);
    void sumar2();
    void restar2();
    void mover(QString tecla);
    void mover_arriba();
    void mover_abajo();
    void mover_derecha();
    void mover_izquierda();
    void boton_activo();
    void boton_inactivo();
    void boton_e_activo();
    void boton_e_inactivo();
    void ultimoencontenedor();
    void ir_a_contenedor(int desde);
    void seleccionar_dentro_modo(QString tecla);
    void elementoSeleccionado();
    void elementoNoSeleccionado();
    void elementoNoChecked();
    void guardarModo(int modo);
    void guardarConfigPCMV();
    void guardarConfigVCMV();
    void guardarConfigPSIMV();
    void guardarConfigVSIMV();
    void guardarConfigPCPAP();
    void guardarConfigVCPAP();
    void llenarConfiguracion();
    void llenarConfiguracionPCMV();
    void llenarConfiguracionVCMV();
    void llenarConfiguracionPSIMV();
    void llenarConfiguracionVSIMV();
    void llenarConfiguracionPCPAP();
    void llenarConfiguracionVCPAP();

    void activarBloqueoPrimeraVez();

    //timer gases
    QTimer *timerInfoGases;

public slots:
    void reiniciaValoresModo();
    void abrir_pantalla_eventos();
    void cambioTab(int i);
    void timerTerminaPrimeraVez();
    void actualizaInfoGases();
signals:

};

#endif // UICONFIGURACION_H
