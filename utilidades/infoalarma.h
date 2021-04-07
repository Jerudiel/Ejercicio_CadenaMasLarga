#ifndef INFOALARMA_H
#define INFOALARMA_H

#include <QWidget>
#include <QLabel>
#include <QFont>


class InfoAlarma : public QWidget
{
    Q_OBJECT
public:
    explicit InfoAlarma(QWidget *parent = nullptr);
    QWidget *padre;
    QFont * fuente;
    QLabel *tiempo;
    QLabel *icono;

    void muestra();
    void oculta();
    void actualiza(QString valor);
    void retranslateUi();

signals:

};

#endif // INFOALARMA_H
