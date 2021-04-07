#ifndef WIDGETSIGNO3_H
#define WIDGETSIGNO3_H

#include <QWidget>

#include <QLabel>
#include <QVBoxLayout>

class WidgetSigno3 : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetSigno3(QWidget *parent = nullptr, QString nombre = "nombre", QString nombrewidget = "nombrewidget", QString unidad = "unidad", QString color = "White", int largo = 167, int alto = 94, QString icono = "icono.png");
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
    QLabel * label_val_inf;
    QLabel * label_val_prog;
    QLabel * label_val_sup;


    void retranslate_ui();
    void setValorProg(QString inf="",QString prog="",QString sup="");
    virtual void paintEvent(QPaintEvent *event);
    void verificar_color(QString color="Gray");


signals:

};

#endif // WIDGETSIGNO3_H

