#include "widgetsignobarconfig.h"

#include <QPixmap>
#include <QStyleOption>
#include <QPainter>

WidgetSignoBarConfig::WidgetSignoBarConfig(QWidget *parent, QString nombre) : QWidget(parent)
{
    try {
        this->nombre = nombre;
        setStyleSheet("background-color: black;");
        boxLayout =  new QVBoxLayout(this);
        boxLayout->setContentsMargins(3,3,3,3);
        boxLayout->setSpacing(3);
        boxLayout->setObjectName("boxLayout");
        label_title =  new QLabel(this);
        fuente = new QFont;
        fuente->setPointSize(12);
        fuente->setBold(true);
        fuente->setWeight(75);
        label_title->setFont(*fuente);
        label_title->setAlignment(Qt::AlignCenter);
        label_title->setObjectName("label_title");
        label_title->setStyleSheet("color: white;");
        boxLayout->addWidget(label_title);

        horizontalLayout =  new QHBoxLayout;
        //Ajuste de posicion horizontal
        horizontalLayout->setContentsMargins(20,0,5,0);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName("horizontalLayout");
        //crear bar
        bar = new QRoundProgressBarAlarm(this);
        bar->setObjectName("bar");
        bar->setBarStyle(QRoundProgressBarAlarm::BarStyle::StyleLine);
        //p1 = QPalette()
        //p1.setColor(QPalette.Base, self.colordona)
        //self.bar.setPalette(p1)
        bar->setOutlinePenWidth(15);
        bar->setDataPenWidth(10);
        bar->setRange(0, 100);
        bar->setValue(100);
        bar->setStyleSheet("font-style:bold; font-weight: bold;");
        bar->update();

        verticalLayout = new QVBoxLayout(bar);
        verticalLayout->setContentsMargins(5,5,5,5);
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout->addWidget(bar);
        boxLayout->addLayout(horizontalLayout);

        boxLayout->setStretch(0,1);
        boxLayout->setStretch(1,3);

        retranslateUi();
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void WidgetSignoBarConfig::retranslateUi()
{
    try {
        label_title->setText(nombre);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void WidgetSignoBarConfig::activo()
{
    try {
        bar->setActive();
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void WidgetSignoBarConfig::inactivo()
{
    try {
        bar->setInactive();
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}
