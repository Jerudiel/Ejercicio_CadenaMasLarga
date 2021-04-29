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
#include <QMap>
#include <QScrollArea>
#include <QVBoxLayout>
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

    QScrollArea *scroll;
    QLabel *lblDebug;
    QVBoxLayout *vBoxLay;

    QTimer *timerConfigKey;
    int contConfigKey;
    QTimer *timerGetMode;
    int contGetMode;
    QTimer *timerConfigGlobal;
    int contConfigGlobal;

    int elementSel;
    int lastElementSel;
    bool isFirstTimeSel;
    int mode;
    bool state;

    bool wasAGetMode;

    QMap<QString, int> *mapKey;

    QString advert;
    QString tempAdvert;

    void get_mode();
    void get_config_global();

    void show_message(QString message);
    QTimer *timerMessage;

    virtual void paintEvent(QPaintEvent *event);

    bool are_ints();

    void set_checked_button(int index, bool state);

    QTimer *timerNewDataKeyboard;
    QString dataKeyboard;
    QLabel *lblDataKeyboard;

public slots:
    //void set_config_key();
    void get_config_key(int element);
    void check_config_key();
    void check_mode();
    void check_config_global();
    void out();
    void set_mode();
    void apply();
    void eraseMessage();
    void check_new_data_keyboard();
signals:

};

#endif // UICALTECLADO_H
