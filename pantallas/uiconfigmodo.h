#ifndef UICONFIGMODO_H
#define UICONFIGMODO_H

#include <QWidget>

#include <QString>
#include <QFont>
#include <QPushButton>
#include <QStackedWidget>

#include "modos/uimodopcmv.h"
#include "modos/uimodopcpap.h"
#include "modos/uimodopsimv.h"
#include "modos/uimodovcmv.h"
#include "modos/uimodovcpap.h"
#include "modos/uimodovsimv.h"

class UiConfigModo : public QWidget
{
    Q_OBJECT
public:
    explicit UiConfigModo(QWidget *parent = nullptr);
    QString btn;
    QString btnSeleccionado;
    QString btnSeleccionadoWidget;
    QString btnNoSeleccionadoWidget;
    QFont * fuente;
    QPushButton * btnPCMV;
    QPushButton * btnVCMV;
    QPushButton * btnPSIMV;
    QPushButton * btnVSIMV;
    QPushButton * btnPCPAP;
    QPushButton * btnVCPAP;
    float perillaPaso;
    bool modoVentilador;
    QStackedWidget * conte_modo;
    UiModoPCMV * modoPCMV;
    UiModoVCMV * modoVCMV;
    UiModoPSIMV * modoPSIMV;
    UiModoVSIMV * modoVSIMV;
    UiModoPCPAP * modoPCPAP;
    UiModoVCPAP * modoVCPAP;

    void retranslateUi();
    virtual void paintEvent(QPaintEvent *event);

    void boton_activo(int numero);
    void boton_inactivo(int numero);
    void boton_checked(int numero, bool estado);
public slots:
    void abrir_modo_pcmv();
    void abrir_modo_vcmv();
    void abrir_modo_psimv();
    void abrir_modo_vsimv();
    void abrir_modo_pcpap();
    void abrir_modo_vcpap();

signals:

};

#endif // UICONFIGMODO_H
