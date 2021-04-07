#ifndef UIEVENTOS_H
#define UIEVENTOS_H

#include <QWidget>
#include <QFont>
#include <QTableWidget>
#include "monitor.h"
#include <QPainter>
#include <QStyleOption>
#include <QHeaderView>
#include <QSizePolicy>

class UiEventos : public QWidget
{
    Q_OBJECT
public:
    explicit UiEventos(QWidget *parent = nullptr, Monitor *monitor = nullptr);
    Monitor *monitor;
    QFont *fuente;
    QTableWidget *tableView;
    int numero_eventos;
    int numero_scrolls;
    int contador_scrolls;
    int numero_eventos_mostrados;
    int numero_mas_eventos;

    virtual void paintEvent(QPaintEvent *event);
    void bajar();
    void subir();
    void obtener_numero_scrolls();
    void cargar_datos();

signals:

};

#endif // UIEVENTOS_H

