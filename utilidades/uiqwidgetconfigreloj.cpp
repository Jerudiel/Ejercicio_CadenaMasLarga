#include "uiqwidgetconfigreloj.h"

UiQWidgetConfigReloj::UiQWidgetConfigReloj(QWidget *parent) : QWidget(parent)
{
    try {
        btn = "QPushButton { border: 2px solid gray; border-radius: 5px; color: white;}";
        btnBlue = "QPushButton { border: 2px solid gray; border-radius: 5px; color: rgb(0, 102, 204);}";
        btnSeleccionado = "QPushButton { border: 4px solid rgb(255,112,61); border-radius: 5px; color: white;}";

        gridLayout = new QGridLayout(this);
        gridLayout->setObjectName("gridLayout");

        btnMasHora = new QPushButton(this);
        btnMasHora->setStyleSheet(btn);
        btnMasHora->setObjectName("btnMasHora");
        btnMasHora->setIcon(QIcon("graficos/124arriba.png"));
        btnMasHora->setIconSize(QSize(24,24));
        gridLayout->addWidget(btnMasHora, 0, 0, 1, 1);

        fuente = new QFont;
        fuente->setPointSize(18);
        fuente->setBold(true);
        fuente->setWeight(75);

        btnMasMinuto = new QPushButton(this);
        btnMasMinuto->setStyleSheet(btn);
        btnMasMinuto->setObjectName("btnMasMinuto");
        btnMasMinuto->setIcon(QIcon("graficos/124arriba.png"));
        btnMasMinuto->setIconSize(QSize(24,24));
        gridLayout->addWidget(btnMasMinuto, 0, 2, 1, 1);

        lineEditHora = new QLineEdit(this);
        lineEditHora->setAlignment(Qt::AlignCenter);
        lineEditHora->setObjectName("lineEditHora");
        lineEditHora->setFont(*fuente);
        gridLayout->addWidget(lineEditHora, 1, 0, 1, 1);

        label_puntos = new QLabel(this);
        label_puntos->setFont(*fuente);
        label_puntos->setObjectName("label_puntos");
        label_puntos->setText(":");
        label_puntos->setAlignment(Qt::AlignCenter);
        label_puntos->setStyleSheet("color: white;");
        gridLayout->addWidget(label_puntos, 1, 1, 1, 1);

        lineEditMinuto = new QLineEdit(this);
        lineEditMinuto->setAlignment(Qt::AlignCenter);
        lineEditMinuto->setObjectName("lineEditMinuto");
        lineEditMinuto->setFont(*fuente);
        gridLayout->addWidget(lineEditMinuto, 1, 2, 1, 1);

        btnModoHorario = new QPushButton(this);
        btnModoHorario->setObjectName("btnModoHorario");
        btnModoHorario->setText("AM");
        btnModoHorario->setFont(*fuente);
        btnModoHorario->setStyleSheet(btn);
        btnModoHorario->setCheckable(true);
        btnModoHorario->setChecked(false);
        gridLayout->addWidget(btnModoHorario, 1, 3, 1, 1);

        btnMenosHora = new QPushButton(this);
        btnMenosHora->setObjectName("btnMenosHora");
        btnMenosHora->setIcon(QIcon("graficos/124abajo.png"));
        btnMenosHora->setIconSize(QSize(24,24));
        btnMenosHora->setStyleSheet(btn);
        gridLayout->addWidget(btnMenosHora, 2, 0, 1, 1);

        btnMenosMinuto = new QPushButton(this);
        btnMenosMinuto->setObjectName("btnMenosMinuto");
        btnMenosMinuto->setIcon(QIcon("graficos/124abajo.png"));
        btnMenosMinuto->setIconSize(QSize(24,24));
        btnMenosMinuto->setStyleSheet(btn);
        gridLayout->addWidget(btnMenosMinuto, 2, 2, 1, 1);

        gridLayout->setRowStretch(0,1);
        gridLayout->setRowStretch(1,1);
        gridLayout->setRowStretch(2,1);

        gridLayout->setColumnStretch(0,2);
        gridLayout->setColumnStretch(1,1);
        gridLayout->setColumnStretch(2,2);
        gridLayout->setColumnStretch(3,2);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

void UiQWidgetConfigReloj::paintEvent(QPaintEvent* /*event*/)
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
