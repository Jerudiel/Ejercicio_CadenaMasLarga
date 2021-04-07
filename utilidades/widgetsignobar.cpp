#include "widgetsignobar.h"

#include <QPixmap>
#include <QStyleOption>
#include <QPainter>

WidgetSignoBar::WidgetSignoBar(QWidget *parent, QString nombre, QString nombrewidget, QString unidad, float min, float max, float value, QString formato) : QWidget(parent)
{
    try {
        this->nombre = nombre;
        this->nombrewidget = nombrewidget;
        this->unidad = unidad;
        this->min = min;
        this->max = max;
        this->value = value;
        setObjectName(nombrewidget);
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
        bar = new QRoundProgressBar(this);
        bar->setObjectName("bar");
        bar->setBarStyle(QRoundProgressBar::BarStyle::StyleLine);
        QPalette *pi = new QPalette();
        pi->setColor(QPalette::Base,Qt::blue);
        bar->setPalette(*pi);
        bar->setOutlinePenWidth(5);
        bar->setDataPenWidth(5);
        if(formato == "F"){
            bar->setFormat("%v");
            bar->setDecimals(1);
        }
        else{
            bar->setFormat("%d");
        }
        bar->setUnit(unidad);
        bar->setRange(min, max);
        bar->setValue(value);
        bar->setStyleSheet("color: white;");
        bar->update();

        /*verticalLayout = new QVBoxLayout(bar);
        verticalLayout->setContentsMargins(5,5,5,5);
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName("verticalLayout");*/
        horizontalLayout->addWidget(bar);
        boxLayout->addLayout(horizontalLayout);

        horLayoutProg = new QHBoxLayout;
        horLayoutProg->setObjectName("horLayoutProg");

        fuente->setPointSize(12);
        label_val_inf =  new QLabel(this);
        label_val_inf->setFont(*fuente);
        label_val_inf->setObjectName("label_val_inf");
        label_val_inf->setStyleSheet("color: red; background-color: black;");
        label_val_inf->setText("-");
        horLayoutProg->addWidget(label_val_inf,1,Qt::AlignCenter);

        label_val_prog =  new QLabel(this);
        label_val_prog->setFont(*fuente);
        label_val_prog->setObjectName("label_val_prog");
        label_val_prog->setStyleSheet("color: white; background-color: black;");
        label_val_prog->setText("-");
        horLayoutProg->addWidget(label_val_prog,1,Qt::AlignCenter);

        label_val_sup =  new QLabel(this);
        label_val_sup->setFont(*fuente);
        label_val_sup->setObjectName("label_val_sup");
        label_val_sup->setStyleSheet("color: red; background-color: black;");
        label_val_sup->setText("-");
        horLayoutProg->addWidget(label_val_sup,1,Qt::AlignCenter);

        horLayoutProg->setStretch(0,1);
        horLayoutProg->setStretch(1,1);
        horLayoutProg->setStretch(2,1);
        boxLayout->addLayout(horLayoutProg);

        boxLayout->setStretch(0,1);
        boxLayout->setStretch(1,4);
        boxLayout->setStretch(2,1);

        QString ccs = "QWidget#"+ nombrewidget+" { border: 1px solid white;}";
        setStyleSheet(ccs);
        retranslateUi();
        valorProg = 0;
        //QtCore.QMetaObject.connectSlotsByName(self)
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void WidgetSignoBar::setValorProg(QString inf, QString prog, QString sup)
{
    try {
        label_val_inf->setText(inf);
        label_val_prog->setText(prog);
        label_val_sup->setText(sup);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void WidgetSignoBar::retranslateUi()
{
    try {
         label_title->setText(nombre);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void WidgetSignoBar::paintEvent(QPaintEvent* /*event*/)
{
    try {
        QStyleOption * opt = new QStyleOption;
        opt->initFrom(this);
        QPainter * p = new QPainter(this);
        this->style()->drawPrimitive(QStyle::PE_Widget, opt, p, this);
        p->end();
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

