#include "widgetgrafica.h"

WidgetGrafica::WidgetGrafica(QWidget *parent, QString nombre, QString tituloy, float min, float max, QBrush color_linea, int tiempo, bool promediador, int orden) : QWidget(parent)
{
    grafica = new QCustomPlot(this);
    grafica->setObjectName(nombre);
    //grafica->resize(850,135);
    grafica->setGeometry(QRect(0,0, 850, 135));
    grafica->setBackground(Qt::black);
    grafica->yAxis->setLabel(tituloy); //titulo en eje y
    grafica->yAxis->setRange(min, max); //rango en eje y
    grafica->yAxis->setLabelColor(QColor(Qt::white));
    grafica->yAxis->setTickLabelColor(QColor(Qt::white));
    grafica->yAxis->grid()->setPen(QPen(Qt::white, 0.5, Qt::DotLine)); // , Qt::SolidLine
    grafica->xAxis->setVisible(false); //ocultar eje x
    grafica->xAxis->grid()->setVisible(false); //ocultar el gri del eje x
    grafica->addGraph();
    grafica->graph(0)->setPen(QPen(color_linea, 3));

    this->tiempo = tiempo;
    this->promediador = promediador;
    this->orden = orden;

    // nuevo grafica 04-03
    grafica->addGraph();
    grafica->graph(1)->setPen(QPen(color_linea, 3));
    grafica->xAxis->setRange(0,MAX_PUNTOS-1);
    //grafica->axisRect()->setAutoMargins(QCP::msNone);
    //grafica->axisRect()->setMargins(QMargins(0,0,0,0));
    //

    //connect(hiloPanel,SIGNAL(graficaDato(const QString)),SLOT(grafica(const QString)));
    //el método graficaDato es de la clase hiloPanel y no necesariamente es una función,
    //como se muestra abajo,
    //emit graficaDato(strTemp);

    //connect(parent,SIGNAL(graficaDato(const QString)),SLOT(graficar(const QString)));

    //connect(this,SIGNAL(notificaDatoNuevo(QString)),this,SLOT(actualiza(QString)));

    /*indiceXDato = 0;

    timerActualiza = new QTimer;
    timerActualiza->setInterval(tiempo);
    connect(timerActualiza, SIGNAL(timeout()), this, SLOT(replot()));

    contador = 0;
    base = QVector<double>(MAX_PUNTOS);*/

    //jeru 04-03
    listaDatos = QStringList();
    indiceXDato = 0;
    contador = 0;
    contReplot = 0;
    datos_eliminar = 2;
    contador_datos = 0;
    llenado = false;

    //promediador
    contador_promediador = 0;
    lista_promediador = new QStringList;
    promediador_listo = false;
}

void WidgetGrafica::replot(){
    grafica->xAxis->setRange(indiceXDato - MAX_PUNTOS, indiceXDato);
    grafica->replot();

}

void WidgetGrafica::actualiza(QString datos){
    try {
        listaDatos.append(datos);
    }  catch ( const std::exception& e) {
        qDebug() << "Excepcion en actualiza()" << e.what();
    }

}

void WidgetGrafica::graficar(QString dato){
    /*if(indiceXDato == 0){
        timerActualiza->start();
    }

    grafica->graph(0)->addData(indiceXDato, dato.toDouble());
    indiceXDato++;*/

    //jeru 04-03
    if(indiceXDato == 0){
        qDebug() << "inicia timer";
        indiceXDato = 1;
        startTimer(tiempo); //50
    }

    //aqui viene lo del promediador
    float data = 0;
    if(promediador){
        //checar el orden
        if(contador_promediador < orden){
            lista_promediador->append(dato);
            contador_promediador++;
        }
        else{
            promediador_listo = true;
            lista_promediador->pop_front();
            lista_promediador->append(dato);
        }

        if(promediador_listo){
            float suma = 0;
            for(int j=0; j < lista_promediador->size(); j++){
                suma += lista_promediador->at(j).toFloat();
            }
            data = suma / orden;
        }
        else{
            data = dato.toFloat();
        }
    }
    else{
        data = dato.toFloat();
    }


    if(contador_datos > MAX_PUNTOS -1){
        grafica->graph(0)->data()->clear();
        grafica->graph(1)->setData(indicesY, datos_backup);
        datos_backup.clear();
        contador_datos = 0;
        llenado = true;
    }

    if(!llenado){
        indicesY.append(contador_datos);
    }

    datos_backup.append(data);

    grafica->graph(1)->data()->removeBefore(contador_datos+datos_eliminar);
    grafica->graph(0)->addData(contador_datos, data);
    contador_datos++;
}

void WidgetGrafica::limpiar_promediador(){
    lista_promediador->clear();
    contador_promediador = 0;
    promediador_listo = false;
}

void WidgetGrafica::timerEvent(QTimerEvent( *event)){
    grafica->replot();
}
