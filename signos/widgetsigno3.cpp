#include "widgetsigno3.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFont>
#include <QSizePolicy>
#include <QPixmap>
#include <QStyleOption>
#include <QPainter>


WidgetSigno3::WidgetSigno3(QWidget *parent, QString nombre, QString nombrewidget, QString unidad, QString color, int largo, int alto, QString icono) : QWidget(parent)
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

        horLayoutProg = new QHBoxLayout;
        horLayoutProg->setObjectName("horLayoutProg");

        fuente->setPointSize(12);
        label_val_inf = new QLabel(this);
        label_val_inf->setObjectName("label_val_inf");
        label_val_inf->setStyleSheet("color: red; background-color: black;");
        label_val_inf->setText("");
        horLayoutProg->addWidget(label_val_inf, 1,  Qt::AlignCenter);

        label_val_prog = new QLabel(this);
        label_val_prog->setObjectName("label_val_prog");
        label_val_prog->setStyleSheet("color: white; background-color: black;");
        label_val_prog->setText("");
        horLayoutProg->addWidget(label_val_prog, 1, Qt::AlignCenter);

        label_val_sup = new QLabel(this);
        label_val_sup->setObjectName("label_val_sup");
        label_val_sup->setStyleSheet("color: red; background-color: black;");
        label_val_sup->setText("");
        horLayoutProg->addWidget(label_val_sup, 1, Qt::AlignCenter);

        horLayoutProg->setStretch(0,1);
        horLayoutProg->setStretch(1,1);
        horLayoutProg->setStretch(2,1);

        verticalLayout->addLayout(horLayoutVal);
        verticalLayout->addLayout(horLayoutProg);
        verticalLayout->setStretch(0,2);
        verticalLayout->setStretch(1,3);
        verticalLayout->setStretch(2,1);

        //falta esto
        //self.valorProg = 0
        retranslate_ui();
        //QtCore.QMetaObject.connectSlotsByName(self)

        //quitar despues
        //setValorProg("0","1","2");
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void WidgetSigno3::retranslate_ui()
{
    try {
        label_nombre->setText(nombre);
        label_uni->setText(unidad);
        label_valor->setText("0");
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void WidgetSigno3::setValorProg(QString inf,QString prog,QString sup)
{
    try {
        label_val_inf->setText(inf);
        label_val_prog->setText(prog);
        label_val_sup->setText(sup);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void WidgetSigno3::verificar_color(QString color)
{
    try {
         color = color.toUpper();
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }

}

void WidgetSigno3::paintEvent(QPaintEvent* /*event*/)
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

