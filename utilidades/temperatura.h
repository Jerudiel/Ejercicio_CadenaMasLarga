#ifndef TEMPERATURA_H
#define TEMPERATURA_H

#include <QWidget>
#include "monitor.h"
#include <QPushButton>
#include <QIcon>
#include <QLabel>
#include <QFont>
#include <QTimer>
#include <QDir>
#include <QProcess>
#include <QThread>

class Temperatura : public QWidget
{
    Q_OBJECT
public:
    explicit Temperatura(QWidget *parent = nullptr, Monitor *monitor = nullptr);
    Monitor *monitor;
    QString estiloBT;
    QPushButton *temperatura;
    QIcon *iconTemp1;
    QIcon *iconTemp2;
    QIcon *iconTemp3;
    QLabel *label;
    QFont *fuente;
    QTimer *monTimer;
    QString tt;
    bool toogle;

    QString obtenTemp();
    int tempAnt;
public slots:
    void run();

signals:

};

#endif // TEMPERATURA_H
