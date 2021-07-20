#ifndef UIALARMAS_H
#define UIALARMAS_H

#include <QWidget>

#include <QFont>
#include <QRect>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QString>
#include <QPushButton>
#include <QSizePolicy>
#include <QTimer>

#include "utilidades/alarmaqw.h"
#include "utilidades/temperatura.h"
//#include "mainwindow.h"

class UiAlarmas : public QWidget
{
    Q_OBJECT
public:
    explicit UiAlarmas(Monitor *monitor = nullptr, QWidget *parent = nullptr);
    // MainWindow *mainwindow = nullptr,
    //MainWindow * mainwindow;
    Monitor * monitor;
    QString estiloBTInactivo;
    QString estiloBTActivo;
    QString estiloMSGA;
    QString estiloMSGI;
    QWidget * centralwidget;
    QWidget * horizontalLayoutWidget;
    QHBoxLayout * principalLayout;
    QVBoxLayout * contenidoLayout;
    QHBoxLayout * informacionLayout;
    QVBoxLayout * UsuarioLayout;
    QLabel * label_Modo;
    QFont * fuente;
    QHBoxLayout * BotonesLayout;
    QLabel * label_fecha;
    Temperatura *tempMon;
    QHBoxLayout * graficaLayout;
    QWidget * widget;
    int limiteMaxApn;
    int limiteMinApn;
    int limiteMaxVol;
    int limiteMinVol;
    int limiteMaxPre;
    int limiteMinPre;
    int limiteMaxFre;
    int limiteMinFre;
    int limiteMinVolE;
    int limiteMaxVolE;

    AlarmaQW * alarmaPRE;
    AlarmaQW * alarmaVOLM;
    AlarmaQW * alarmaFTO;
    AlarmaQW * alarmaVTI;

    QPushButton * resetValores;
    QPushButton * guardarCambios;

    QLabel * estadoMensajes;

    int valPMAX;
    int valPMIN;
    float valVMMAX;
    float valVMMIN;
    int valFTMAX;
    int valFTMIN;
    int valVTMAX;
    int valVTMIN;
    int valTAPNE;

    QString edoAPRE;
    QString edoAVOM;
    QString edoAFTO;
    QString edoAVTI;

    int idObjeto;

    int eleActivo;

    QString IDTOSTR(int idObjeto);
    void actualizaVentana();
    void resetTodo();
    void cargaValoresDB(QStringList valores);

    void cargaConfiguracion();

    void verificarConfiguracion();
    void teclado(QString tecla);
    void arriba();
    void abajo();
    void moverIzq();
    void moverDer();
    void actualizaFocoObjeto();
    void enviaTecladoAlarma(QString tecla);
    void activaGuardar(bool estado);
    void activaReset(bool estado);
    void retranslateUi();

    QTimer *timerLimpiarInfo;
    void mostrarMensaje(QString mensaje);
    //void asignaPadre(MainWindow *mainwindow);
public slots:
    void resetValoresDefault();
    void guardaCambios();
    void limpiar();

signals:

};

#endif // UIALARMAS_H
