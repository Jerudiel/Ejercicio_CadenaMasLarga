#ifndef UICALOTROS_H
#define UICALOTROS_H

#include <QWidget>

#include "monitor.h"

class UiCalOtros : public QWidget
{
    Q_OBJECT
public:
    explicit UiCalOtros(QWidget *parent = nullptr, Monitor *monitor = nullptr);

signals:

};

#endif // UICALOTROS_H
