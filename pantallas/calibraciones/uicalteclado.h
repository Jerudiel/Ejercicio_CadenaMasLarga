#ifndef UICALTECLADO_H
#define UICALTECLADO_H

#include <QWidget>

#include "monitor.h"
#include <QFont>
#include <QVector>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTimer>
#include <QStyleOption>
#include <QPainter>
#include <QDir>
#include "utilidades/myswitch.h"

class UiCalTeclado : public QWidget
{
    Q_OBJECT
public:
    explicit UiCalTeclado(QWidget *parent = nullptr, Monitor *monitor = nullptr);
    Monitor *monitor;
    QFont * font;

    QString styleButton;

    QPushButton *btnOk;
    QPushButton *btnCan;
    QPushButton *btnPlay;
    QPushButton *btnSetAlarm;
    QPushButton *btnMon;
    QPushButton *btnCon;
    QPushButton *btnAlarm;
    QPushButton *btnDesAlarm;
    QPushButton *btnUp;
    QPushButton *btnDown;
    QPushButton *btnLeft;
    QPushButton *btnRight;

    MySwitch *switchMode;
    QLabel *lblPush;
    QLabel *lblRelease;
    QLineEdit *lEPush;
    QLineEdit *lERelease;

    QPushButton *btnOut;
    QPushButton *btnApply;
    QLabel *lblDebug;

    QTimer *timerConfigKey;
    int contConfigKey;
    QTimer *timerGetMode;
    int contGetMode;

    int elementSel;
    int mode;
    bool state;

    QString advert;
    QString tempAdvert;

    void get_mode();

    virtual void paintEvent(QPaintEvent *event);

public slots:
    //void set_config_key();
    void get_config_key(int element);
    void check_config_key();
    void check_mode();
    void out();
    void set_mode();
    void apply();
signals:

};

#endif // UICALTECLADO_H
