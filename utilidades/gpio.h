#ifndef GPIO_H
#define GPIO_H

#include <QObject>
#include <wiringPi.h>
/*extern "C" {
#include <wiringPi.h>
}*/

class Gpio : public QObject
{
    Q_OBJECT
public:
    explicit Gpio(QObject *parent = nullptr);
    void encender(int numero);
    void apagar(int numero);
    int IN[8];
    bool leer_pin();

signals:

};

#endif // GPIO_H
