#ifndef UICALSENSORES_H
#define UICALSENSORES_H

#include <QWidget>

#include "monitor.h"

class UiCalSensores : public QWidget
{
    Q_OBJECT
public:
    explicit UiCalSensores(QWidget *parent = nullptr, Monitor *monitor = nullptr);

signals:

};

#endif // UICALSENSORES_H
