#ifndef VENTANAINFO_H
#define VENTANAINFO_H

#include <QWidget>
#include <QWidget>
#include <QString>
#include <QColor>
#include <QFont>
#include <QLabel>
#include <QPushButton>
#include <QPainter>
#include <QSize>

class VentanaInfo : public QWidget
{
    Q_OBJECT
public:
    explicit VentanaInfo(QWidget *parent = nullptr, int width=400, int height=500);

    int pwidth;
    int pheight;

    int offset_x;
    int offset_y;

    QColor fillColor;
    QColor penColor;

    QColor popup_fillColor;
    QColor popup_penColor;

    QFont *fuente;

    QStringList *mensajes;

    virtual void paintEvent(QPaintEvent *event);
    void textoMostrar(QStringList *mensajes);
signals:

};

#endif // VENTANAINFO_H
