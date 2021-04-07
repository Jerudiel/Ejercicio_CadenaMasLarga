#ifndef MYSWITCH_H
#define MYSWITCH_H

#include <QWidget>
#include <QPushButton>
#include <QString>
#include <QColor>
#include <QLabel>
#include <QPainter>
#include <QPen>
#include <QDebug>

class MySwitch : public QPushButton
{
    Q_OBJECT
public:
    MySwitch(QWidget * parent = nullptr, QString on = "on", QString off = "off");
    bool seleccionado;
    QString on;
    QString off;
    QColor * bgcolor;

    void switchSel(bool estado);
    virtual void paintEvent(QPaintEvent *event);
    void ponerGeometry(QRect rectangulo);
    void ponerChecked(bool var);
    bool estaChecked();
    void actualizar();
};

#endif // MYSWITCH_H
