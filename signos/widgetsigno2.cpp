#include "widgetsigno2.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFont>
#include <QSizePolicy>
#include <QPixmap>
#include <QStyleOption>
#include <QPainter>

WidgetSigno2::WidgetSigno2(QWidget *parent, QString nombre, QString nombrewidget, QString unidad, QString color, int largo, int alto, QString icono) : QWidget(parent)
{
    try {
        colores = {"Aqua", "Black", "Blue", "Black", "Brown", "Coral", "Cyan", "DarkBlue", "DarkGreen", "Gray",
                                  "Green", "Indigo", "Maroon", "Navy", "Orange", "Red", "Violet", "Yellow", "White"};
        this->nombre = nombre;
        this->nombrewidget = nombrewidget;
        this->unidad = unidad;
        this->color = color;
        this->largo = largo;
        this->alto = alto;
        this->nombre_icon = icono;
        setObjectName(this->nombrewidget);
        resize(this->largo, this->alto);

        verticalLayout = new QVBoxLayout(this);
        verticalLayout->setContentsMargins(2,2,3,3);
        verticalLayout->setSpacing(2);
        verticalLayout->setObjectName("verticalLayout");

        horLayoutTitle = new QHBoxLayout;
        horLayoutTitle->setObjectName("horLayoutTitle");

        label_nombre =  new QLabel(this); //QLabel * label_nombre =  new QLabel(this);

        fuente = new QFont;
        fuente->setPointSize(17);
        fuente->setBold(true);
        fuente->setWeight(75);

        label_nombre->setFont(*fuente);
        label_nombre->setStyleSheet("background-color: " + this->color + ";\n"
                                    "color: black;\n"
                                    "border: 2px solid " + this->color + ";\n"
                                    "border-top-right-radius: 2Px; "
                                    "border-bottom-right-radius: 2Px; "
                                    "border-bottom-left-radius: 2Px;");
        label_nombre->setAlignment(Qt::AlignLeading | Qt::AlignLeft | Qt::AlignVCenter);
        label_nombre->setObjectName("label_nombre");

        horLayoutTitle->addWidget(label_nombre);

        label_uni = new QLabel(this);
        label_uni->setObjectName("label_uni");
        label_uni->setStyleSheet("color: " + this->color + ";");

        fuente->setPointSize(11);

        label_uni->setFont(*fuente);

        horLayoutTitle->addWidget(label_uni);
        horLayoutTitle->setStretch(0,5);
        horLayoutTitle->setStretch(1,3);

        verticalLayout->addLayout(horLayoutTitle);

        horLayoutVal = new QHBoxLayout;
        horLayoutVal->setObjectName("horLayoutVal");

        label_icon = new QLabel(this);
        label_icon->setText("");
        //size policy
        sp_retain = new QSizePolicy;
        sp_retain->setRetainSizeWhenHidden(true);
        label_icon->setSizePolicy(*sp_retain);
        //icono
        label_icon->setPixmap(QPixmap(this->nombre_icon));
        label_icon->setScaledContents(false);
        label_icon->setObjectName("label_icon");
        label_icon->hide();
        horLayoutVal->addWidget(label_icon, Qt::AlignTop); //alignment=

        label_valor =  new QLabel(this);
        fuente->setPointSize(18);
        fuente->setBold(true);
        fuente->setWeight(75);
        label_valor->setFont(*fuente);
        label_valor->setAlignment(Qt::AlignCenter);
        label_valor->setStyleSheet("color: " + this->color + ";");
        horLayoutVal->addWidget(label_valor);
        horLayoutVal->setStretch(0,1);
        horLayoutVal->setStretch(1,3);

        label_valorP = new QLabel(this);
        fuente->setPointSize(10);
        fuente->setBold(true);
        fuente->setWeight(75);
        label_valorP->setFont(*fuente);
        label_valorP->setAlignment(Qt::AlignCenter);
        label_valorP->setObjectName("label_valorP");
        label_val_inf->setStyleSheet("color: yellow;");
        label_val_inf->setText("");

        verticalLayout->addLayout(horLayoutVal);
        verticalLayout->setStretch(0,1);
        verticalLayout->setStretch(1,2);
        verticalLayout->addWidget(label_valorP);
        valorProg = 0;

        //falta esto
        //self.valorProg = 0
        retranslate_ui();
        //QtCore.QMetaObject.connectSlotsByName(self)
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void WidgetSigno2::retranslate_ui()
{
    try {
        label_nombre->setText(nombre);
        label_uni->setText(unidad);
        label_valor->setText("0");
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void WidgetSigno2::setValorProg(float valor)
{
    try {
        valorProg = valor;
        label_valorP->setText(QString::number(valorProg));
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void WidgetSigno2::verificar_color(QString color)
{
    try {
    color = color.toUpper();
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void WidgetSigno2::paintEvent(QPaintEvent* /*event*/)
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
