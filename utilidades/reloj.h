#ifndef RELOJ_H
#define RELOJ_H

#include <QWidget>
#include <QLabel>
#include <QThread>
#include <QDate>
#include <QDateTime>
#include <QTimer>

/*class MyHilo:QThread
{
    Q_OBJECT
public:
    MyHilo(QLabel * label):label_(label){}
    void run(){
      while(true){
          QDateTime dateTime = QDateTime::currentDateTime();
          QString dateTimeString = dateTime.toString("hh:mm:ss MM-dd/MM/yy"); //yyyy-MM-dd hh:mm:ss.zzz
          if(label_ != nullptr){
              label_->setText(dateTimeString);
          }
      }
    };
private:
    QLabel * label_;
};*/

class Reloj: QWidget
{
    Q_OBJECT
public:
    Reloj();
    QLabel * label_fechahora;
    QTimer * timer_hora;
    void asignaLabel(QLabel *label_fechahora);
    void start();
public slots:
    void update();
};

#endif // RELOJ_H
