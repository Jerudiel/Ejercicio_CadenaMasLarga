#include "uicalibraciones.h"

UiCalibraciones::UiCalibraciones(Monitor * monitor, QWidget *parent) : QWidget(parent)
{
    try {
        this->monitor = monitor;
        setStyleSheet("QWidget{background-color: black; color:white;}"
                      "QPushButton{background-color: rgb(43,42,41);}"
                      "QTabBar::tab {color: white; background: black;} "
                      "QTabBar::tab:selected {color: black; background: grey;}"
                      "QLabel{color: white;}");
        btn = "QPushButton { border: 2px solid gray; border-radius: 5px; color: white;}";
        btnSeleccionado = "QPushButton { border: 4px solid rgb(255,112,61); border-radius: 5px; color: white;}";
        btnSeleccionadoWidget = "QPushButton { border: 1px solid rgb(255,112,61); border-radius: 5px; color: white;}"
                                "QPushButton:checked { background-color: green; border: 4px solid rgb(255,112,61);"
                                "border-radius: 5px; color: white;}";
        btnNoSeleccionadoWidget = "QPushButton { border: 2px solid rgb(255,112,61); border-radius: 5px; color: white;}"
                                  "QPushButton:checked { background-color: green; border: 1px solid green;"
                                  "border-radius: 5px; color: white;}";
        centralwidget = new QWidget(this);
        centralwidget->setObjectName("centralwidget");

        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setGeometry(QRect(0, 25, 1031, 601));
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");

        fuente = new QFont;
        fuente->setBold(true);
        fuente->setPointSize(18);

        tabWidget = new QTabWidget(horizontalLayoutWidget);
        tabWidget->setObjectName("tabWidget");

        /*tab_cal =  new QWidget;
        tab_cal->setObjectName("tab_cal");
        tabWidget->addTab(tab_cal, "");*/

        //aqui se van a agregar los 3 tabs
        /*tab_info_sistema = new UiInfoSistema(this, monitor);
        tab_info_sistema->setObjectName("tab_info_sistema");
        tabWidget->addTab(tab_info_sistema, "");*/
        //configModo = new UiConfigModo(tab_config); ???

        tab_sensores = new UiCalSensores(this, monitor);
        tab_sensores->setObjectName("tab_sensores");
        tabWidget->addTab(tab_sensores, "");

        tab_control = new UiCalControl(this, monitor);
        tab_control->setObjectName("tab_control");
        tabWidget->addTab(tab_control, "");

        tab_otros = new UiCalOtros(this, monitor);
        tab_otros->setObjectName("tab_otros");
        tabWidget->addTab(tab_otros, "");

        retranslateUi();
        tabWidget->setCurrentIndex(0);
        connect(tabWidget, SIGNAL(currentChanged(int)), this, SLOT(cambioTab(int)));
        llenarConfiguracion();

    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiCalibraciones::retranslateUi(){
    try {

        /*tabWidget->setTabText(tabWidget->indexOf(tab_info_sistema), "SISTEMA");
        tabWidget->setTabText(tabWidget->indexOf(tab_calibrar), "CALIBRAR");
        tabWidget->setTabText(tabWidget->indexOf(tab_datetime), "FECHA");*/
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}
