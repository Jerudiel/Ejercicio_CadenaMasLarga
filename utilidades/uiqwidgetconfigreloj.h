#ifndef UIQWIDGETCONFIGRELOJ_H
#define UIQWIDGETCONFIGRELOJ_H

#include <QWidget>
#include <QString>
#include <QGridLayout>
#include <QPushButton>
#include <QFont>
#include <QLineEdit>
#include <QLabel>
#include <QStyleOption>
#include <QPainter>

class UiQWidgetConfigReloj : public QWidget
{
    Q_OBJECT
public:
    explicit UiQWidgetConfigReloj(QWidget *parent = nullptr);
    QString btn;
    QString btnBlue;
    QString btnSeleccionado;
    QGridLayout *gridLayout;
    QPushButton *btnMasHora;
    QFont *fuente;
    QPushButton *btnMasMinuto;
    QLineEdit *lineEditHora;
    QLabel *label_puntos;
    QLineEdit *lineEditMinuto;
    QPushButton *btnModoHorario;
    QPushButton *btnMenosHora;
    QPushButton *btnMenosMinuto;

    virtual void paintEvent(QPaintEvent *event);


signals:

};

#endif // UIQWIDGETCONFIGRELOJ_H
