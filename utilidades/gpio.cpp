#include "gpio.h"

Gpio::Gpio(QObject *parent) : QObject(parent)
{
    wiringPiSetupGpio();
    pinMode(10, INPUT);
    pullUpDnControl(10, PUD_OFF);
}

void Gpio::encender(int numero){
    digitalWrite(IN[numero], HIGH);
}

void Gpio::apagar(int numero){
    digitalWrite(IN[numero], LOW);
}

bool Gpio::leer_pin(){
    int temp = digitalRead(10);
    if(temp == 1){
        return true;
    }
    return false;
}
