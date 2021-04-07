#include "widgetgraficalazo.h"

WidgetGraficaLazo::WidgetGraficaLazo(QWidget *parent, QString nombre, QString tituloy, float min_y, float max_y, QString titulox, float min_x, float max_x,QBrush color_linea, int tiempo) : QWidget(parent)
{
    grafica = new QCustomPlot(this);
    grafica->setObjectName(nombre);
    //grafica->resize(850,135);
    grafica->setGeometry(QRect(0,0, 425, 375));
    grafica->setBackground(Qt::black);
    grafica->yAxis->setLabel(tituloy); //titulo en eje y
    grafica->yAxis->setRange(min_y, max_y); //rango en eje y
    grafica->yAxis->setLabelColor(QColor(Qt::white));
    grafica->yAxis->setTickLabelColor(QColor(Qt::white));
    grafica->yAxis->grid()->setPen(QPen(Qt::white, Qt::SolidLine));
    //grafica->xAxis->setVisible(false); //ocultar eje x
    //grafica->xAxis->grid()->setVisible(false); //ocultar el gri del eje x
    grafica->xAxis->setLabel(titulox); //titulo en eje y
    grafica->xAxis->setRange(min_x, max_x); //rango en eje y
    grafica->xAxis->setLabelColor(QColor(Qt::white));
    grafica->xAxis->setTickLabelColor(QColor(Qt::white));
    grafica->xAxis->grid()->setPen(QPen(Qt::white, Qt::SolidLine));
    //
    graficaCurva = new QCPCurve(grafica->xAxis, grafica->yAxis);
    graficaCurva->setPen(QPen(color_linea,3));
    //

    ///////////////grafica->addGraph();
    ///////////////grafica->graph(0)->setPen(QPen(color_linea, 3));

    //connect(hiloPanel,SIGNAL(graficaDato(const QString)),SLOT(grafica(const QString)));
    //el método graficaDato es de la clase hiloPanel y no necesariamente es una función,
    //como se muestra abajo,
    //emit graficaDato(strTemp);

    //connect(parent,SIGNAL(graficaDato(const QString)),SLOT(graficar(const QString)));

    //connect(this,SIGNAL(notificaDatoNuevo(QString)),this,SLOT(actualiza(QString)));

    indiceXDato = 0;

    timerActualiza = new QTimer;
    timerActualiza->setInterval(tiempo);
    connect(timerActualiza, SIGNAL(timeout()), this, SLOT(replot()));
}

void WidgetGraficaLazo::replot(){
    //grafica->xAxis->setRange(indiceXDato - MAX_PUNTOS, indiceXDato);

    ////////////grafica->graph(0)->setData(eje_x, eje_y);

    graficaCurva->setData(eje_x, eje_y);
    ///graficaCurva->data()->set(eje_curva_x, true);

    grafica->replot();
}

void WidgetGraficaLazo::limpiar(){
    eje_x.clear();
    eje_y.clear();
    ///eje_curva_x.clear();
    //grafica->graph(0)->data().data()->clear();
    graficaCurva->data().data()->clear();
    ///indiceXDato = 0;
}

void WidgetGraficaLazo::graficar(QString datox, QString datoy){
    if(indiceXDato == 0){
        if(!timerActualiza->isActive()){
            timerActualiza->start();
        }
    }

    //grafica->graph(0)->addData(datox.toDouble(), datoy.toDouble());
    //indiceXDato++;

    eje_x.append(datox.toFloat());
    eje_y.append(datoy.toFloat());
    ///eje_curva_x.append(QCPCurveData(indiceXDato, datox.toFloat(), datoy.toFloat()));

    indiceXDato++;
}
