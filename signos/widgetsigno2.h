#ifndef WIDGETSIGNO2_H
#define WIDGETSIGNO2_H

#include <QWidget>

#include <QLabel>
#include <QVBoxLayout>

class WidgetSigno2 : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetSigno2(QWidget *parent = nullptr, QString nombre = "nombre", QString nombrewidget = "nombrewidget", QString unidad = "unidad", QString color = "White", int largo = 167, int alto = 94, QString icono = "icono.png");
    QString nombre;
    QString nombrewidget;
    QString unidad;
    QString color;
    int largo;
    int alto;
    QString nombre_icon;

    QList<QString> colores;
    QVBoxLayout * verticalLayout;
    QHBoxLayout * horLayoutTitle;
    QLabel * label_nombre;
    QFont * fuente;
    QLabel * label_uni;
    QHBoxLayout * horLayoutVal;
    QLabel * label_icon;
    QSizePolicy * sp_retain;
    QLabel * label_valor;
    QHBoxLayout * horLayoutProg;
    QLabel * label_valorP;
    QLabel * label_val_inf;
    QLabel * label_val_prog;
    QLabel * label_val_sup;

    float valorProg;

    void retranslate_ui();
    void setValorProg(float valor);
    virtual void paintEvent(QPaintEvent *event);
    void verificar_color(QString color="Gray");
signals:

};

#endif // WIDGETSIGNO2_H
