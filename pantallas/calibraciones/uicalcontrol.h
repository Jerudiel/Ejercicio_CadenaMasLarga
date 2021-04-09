#ifndef UICALCONTROL_H
#define UICALCONTROL_H

#include <QWidget>

#include "monitor.h"

class UiCalControl : public QWidget
{
    Q_OBJECT
public:
    explicit UiCalControl(QWidget *parent = nullptr, Monitor *monitor = nullptr);

signals:

};

#endif // UICALCONTROL_H
