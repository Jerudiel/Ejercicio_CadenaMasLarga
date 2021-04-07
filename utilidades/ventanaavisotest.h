#ifndef VENTANAAVISOTEST_H
#define VENTANAAVISOTEST_H

#include <QWidget>

#include <QString>
#include <QColor>
#include <QFont>
#include <QLabel>
#include <QPushButton>
#include <QPainter>
#include <QSize>

class VentanaAvisoTest : public QWidget
{
    Q_OBJECT
public:
    explicit VentanaAvisoTest(QWidget *parent = nullptr, int width=400, int height=500, QString titulo="");
    QString ERROR = "ERROR";
    QString OK = "OK";
    QString PROCESO = "PROCESO";

    QString btn;
    QString btnSeleccionado;

    int pwidth;
    int pheight;

    int offset_x;
    int offset_y;

    QColor fillColor;
    QColor penColor;

    QColor popup_fillColor;
    QColor popup_penColor;

    QColor titulo_color;
    QColor mensaje_color;
    QColor proceso_color;
    QColor ok_color;
    QColor error_color;
    //self.signals = VentanaAvisoSignalsTest()
    QString titulo;
    QString mensajes;

    QFont *fuente;

    QStringList *listaMensajes;
    QStringList *listaEstados;
    bool estadoFinal;
    QPushButton * btn_ok;

    void setTituloColor(QColor color);
    void setMensajeColor(QColor color);
    void setFondoColor(QColor color);
    virtual void paintEvent(QPaintEvent *event);
    QColor colorEstado(QString estado);
    int agregarMensaje(QString mensaje, QString estado = "PROCESO");
    void actualizaEstadoMsg(int indice, QString estado);
    void textoMostrar(QString mensajes);
    void fin();
    bool teclado(QString tecla);

signals:

};

#endif // VENTANAAVISOTEST_H
