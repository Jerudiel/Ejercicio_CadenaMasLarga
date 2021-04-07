#include "uimodopcpap.h"

UiModoPCPAP::UiModoPCPAP() : QWidget()
{
    try {
        btn = "QPushButton { border: 2px solid gray; border-radius: 5px; color: white; background-color: rgb(43,42,41);}";
        btnSeleccionado = "QPushButton { border: 4px solid rgb(255,112,61); border-radius: 5px; color: white; background-color: rgb(43,42,41);}";

        pcpap_cpap = new WidgetParametro(this, "CPAP", "cmH2O", 20.0, 0, "1", 0, 0, 0, false);
        pcpap_cpap->setObjectName("pcpap_cpap");
        pcpap_cpap->setGeometry(QRect(10, 0, 150, 140));

        pcpap_ps = new WidgetParametro(this, "PS", "cmH2O", 30.0, 0, "1", 0, 1, 0, false);
        pcpap_ps->setObjectName("pcpap_ps");
        pcpap_ps->setGeometry(QRect(170, 0, 150, 140));

        pcpap_oxi = new WidgetParametro(this, "OXÍGENO", "%", 100.0, 0, "1", 0, 2, 0, true);
        pcpap_oxi->setObjectName("pcpap_oxi");
        pcpap_oxi->setGeometry(QRect(310, 0, 150, 140));
        pcpap_oxi->set_lim_inf(21);

        TriggerBox = new QGroupBox(this);
        TriggerBox->setGeometry(QRect(10, 150, 300, 250));
        TriggerBox->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        fuente = new QFont;
        fuente->setPointSize(14);
        fuente->setBold(true);
        fuente->setWeight(75);
        TriggerBox->setFont(*fuente);
        TriggerBox->setObjectName("TriggerBox");
        TriggerBox->setStyleSheet("QGroupBox:title {color: white; top: -12px;"
                                  "left: 5px;}"
                                  "QGroupBox { border: 1px solid white; margin-top: 0.5em; border-radius: 5px;}");
        switchTrigger = new MySwitch(TriggerBox, "FLUJO", "PRESIÓN");
        switchTrigger->ponerGeometry(QRect(150, 20, 150, 50));
        switchTrigger->ponerChecked(true);

        conte_trigger = new QStackedWidget(TriggerBox);
        conte_trigger->setGeometry(QRect(75, 75, 150, 140));
        conte_trigger->setObjectName("conte_trigger");

        trigger_p = new WidgetParametro(TriggerBox, "P disparo", "cmH2O", 30.0, 0, "1", 0, 7, 0, false );
        trigger_p->setObjectName("trigger_p");
        trigger_p->setGeometry(QRect(0, 0, 150, 140));
        conte_trigger->addWidget(trigger_p);
        conte_trigger->setCurrentWidget(trigger_p);

        trigger_f = new WidgetParametro(TriggerBox, "Disp. flujo", "l/min", 20.0, 0, "1", 0, 8, 0, false );
        trigger_f->setObjectName("trigger_f");
        trigger_f->setGeometry(QRect(0, 0, 150, 140));
        conte_trigger->addWidget(trigger_f);

        pcpap_apnea = new WidgetParametro(this, "APNEA", "seg", 30.0, 0, "1", 0, 6, 0, false);
        pcpap_apnea->setObjectName("pcpap_apnea");
        pcpap_apnea->setGeometry(QRect(500, 0, 150, 140));

        RespaldoApnea = new QGroupBox(this);
        RespaldoApnea->setGeometry(QRect(340, 150, 375, 250));
        RespaldoApnea->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        fuente = new QFont;
        fuente->setPointSize(14);
        fuente->setBold(true);
        fuente->setWeight(75);
        RespaldoApnea->setFont(*fuente);
        RespaldoApnea->setObjectName("RespaldoApnea");
        RespaldoApnea->setStyleSheet("QGroupBox:title {color: white; top: -12px;"
                                  "left: 5px;}"
                                  "QGroupBox { border: 1px solid white; margin-top: 0.5em; border-radius: 5px;}");

        respaldo_fr = new WidgetParametro(RespaldoApnea,"Fr", "/min", 60.0, 0, "1", 0, 7, 0, false);
        respaldo_fr->setObjectName("respaldo_fr");
        respaldo_fr->setGeometry(QRect(0, 75, 150, 140));

        respaldo_pinsp = new WidgetParametro(RespaldoApnea, "Pinsp", "cmH2O", 30.0, 0, "1", 0, 8, 0, false);
        respaldo_pinsp->setObjectName("respaldo_pinsp");
        respaldo_pinsp->setGeometry(QRect(110, 75, 150, 140));

        respaldo_tinsp = new WidgetParametro(RespaldoApnea, "Tinsp", "seg", 10.0, 0, "0.1", 0, 9, 1, false);
        respaldo_tinsp->setObjectName("respaldo_tinsp");
        respaldo_tinsp->setGeometry(QRect(220, 75, 150, 140));

        labelIE = new QLabel(this);
        labelIE->setGeometry(QRect(750, 5, 250, 50));
        fuente->setPointSize(12);
        fuente->setBold(true);
        fuente->setWeight(75);
        labelIE->setFont(*fuente);
        labelIE->setAlignment(Qt::AlignCenter);
        labelIE->setObjectName("labelIE");

        labelTE = new QLabel(this);
        labelTE->setGeometry(QRect(750, 55, 250, 50));
        labelTE->setFont(*fuente);
        labelTE->setAlignment(Qt::AlignCenter);
        labelTE->setObjectName("labelTE");

        labelTI = new QLabel(this);
        labelTI->setGeometry(QRect(750, 105, 250, 50));
        labelTI->setFont(*fuente);
        labelTI->setAlignment(Qt::AlignCenter);
        labelTI->setObjectName("labelTI");

        btnguardarCambios = new QPushButton(this);
        fuente->setPointSize(14);
        btnguardarCambios->setFont(*fuente);
        btnguardarCambios->setGeometry(QRect(750, 200, 250, 50));
        btnguardarCambios->setObjectName("btnguardarCambios");
        btnguardarCambios->setStyleSheet(btn);

        labelInfo = new QLabel(this);
        labelInfo->setGeometry(QRect(750, 250, 250, 100));
        labelInfo->setFont(*fuente);
        labelInfo->setAlignment(Qt::AlignCenter);
        labelInfo->setObjectName("labelInfo");

        elemento_seleccionado = 0;
        min_te_min = 0.4;
        min_ti = 0.4;

        ti = 0;
        te_min = 0.4;
        ti_min = 0.4;
        tp_min = 0;
        pi_max = 0;
        ti_max = 0;
        vt_max = 0;
        flujo_max = 0;
        tp_max = 0;
        fr_max = 0;

        retranslateUi();

        timerMensaje = new QTimer;
        timerMensaje->setSingleShot(true);
        connect(timerMensaje, SIGNAL(timeout()), this, SLOT(outTimer()));
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiModoPCPAP::retranslateUi(){
    try {
        btnguardarCambios->setText("GUARDAR CAMBIOS");
        TriggerBox->setTitle("Trigger");
        RespaldoApnea->setTitle("Respaldo Apnea");
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiModoPCPAP::paintEvent(QPaintEvent* /*event*/)
{
    try {
        QStyleOption * opt = new QStyleOption;
        opt->initFrom(this);
        QPainter * p = new QPainter(this);
        this->style()->drawPrimitive(QStyle::PE_Widget, opt, p, this);
        p->end();
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

int UiModoPCPAP::get_elemento_seleccionado(){
    try {
        return elemento_seleccionado;
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return 0;
    }
}

void UiModoPCPAP::set_trigger(QString estado){
    try {
        if(estado == "0"){
            switchTrigger->ponerChecked(false);
        }
        else{
            switchTrigger->ponerChecked(true);
        }
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiModoPCPAP::update_trigger(){
    try {
        if(switchTrigger->estaChecked()){
            conte_trigger->setCurrentWidget(trigger_f);
        }
        else{
            conte_trigger->setCurrentWidget(trigger_p);
        }
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiModoPCPAP::set_elemento_seleccionado(int elemento){
    try {
        elemento_seleccionado = elemento;
        if(elemento_seleccionado == 0){
            pcpap_cpap->activo();
        }
        else if(elemento_seleccionado == 1){
            pcpap_ps->activo();
        }
        else if(elemento_seleccionado == 2){
            pcpap_oxi->activo();
        }
        else if(elemento_seleccionado == 3){
            pcpap_apnea->activo();
        }
        else if(elemento_seleccionado == 4){
            estado_switch(true);
        }
        else if(elemento_seleccionado == 5){
            trigger_activo();
        }
        else if(elemento_seleccionado == 6){
            respaldo_fr->activo();
        }
        else if(elemento_seleccionado == 7){
            respaldo_pinsp->activo();
        }
        else if(elemento_seleccionado == 8){
            respaldo_tinsp->activo();
        }
        else if(elemento_seleccionado == 9){
            boton_activado();
        }
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiModoPCPAP::boton_activado(){
    try {
        btnguardarCambios->setStyleSheet(btnSeleccionado);
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiModoPCPAP::boton_inactivado(){
    try {
        btnguardarCambios->setStyleSheet(btn);
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiModoPCPAP::trigger_inactivo(){
    try {
        if(switchTrigger->estaChecked()){
            trigger_f->inactivo();
        }
        else{
            trigger_p->inactivo();
        }
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiModoPCPAP::trigger_activo(){
    try {
        if(switchTrigger->estaChecked()){
            trigger_f->activo();
        }
        else{
            trigger_p->activo();
        }
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiModoPCPAP::estado_switch(bool estado){
    try {
        switchTrigger->switchSel(estado);
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiModoPCPAP::mover_izquierda(){
    try {
        if(elemento_seleccionado == 0){
            elemento_seleccionado = 3;
            pcpap_cpap->inactivo();
            pcpap_apnea->activo();
        }
        else if(elemento_seleccionado == 1){
            elemento_seleccionado = 0;
            pcpap_ps->inactivo();
            pcpap_cpap->activo();
        }
        else if(elemento_seleccionado == 2){
            elemento_seleccionado = 1;
            pcpap_oxi->inactivo();
            pcpap_ps->activo();
        }
        else if(elemento_seleccionado == 3){
            elemento_seleccionado = 2;
            pcpap_apnea->inactivo();
            pcpap_oxi->activo();
        }
        else if(elemento_seleccionado == 4){
            elemento_seleccionado = 9;
            estado_switch(false);
            boton_activado();
        }
        else if(elemento_seleccionado == 5){
            elemento_seleccionado = 9;
            trigger_inactivo();
            boton_activado();
        }
        else if(elemento_seleccionado == 6){
            elemento_seleccionado = 5;
            respaldo_fr->inactivo();
            trigger_activo();
        }
        else if(elemento_seleccionado == 7){
            elemento_seleccionado = 6;
            respaldo_pinsp->inactivo();
            respaldo_fr->activo();
        }
        else if(elemento_seleccionado == 8){
            elemento_seleccionado = 7;
            respaldo_tinsp->inactivo();
            respaldo_pinsp->activo();
        }
        else if(elemento_seleccionado == 9){
            elemento_seleccionado = 8;
            boton_inactivado();
            respaldo_tinsp->activo();
        }
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiModoPCPAP::mover_derecha(){
    try {
        if(elemento_seleccionado == 0){
            elemento_seleccionado = 1;
            pcpap_cpap->inactivo();
            pcpap_ps->activo();
        }
        else if(elemento_seleccionado == 1){
            elemento_seleccionado = 2;
            pcpap_ps->inactivo();
            pcpap_oxi->activo();
        }
        else if(elemento_seleccionado == 2){
            elemento_seleccionado = 3;
            pcpap_oxi->inactivo();
            pcpap_apnea->activo();
        }
        else if(elemento_seleccionado == 3){
            elemento_seleccionado = 9;
            pcpap_apnea->inactivo();
            boton_activado();
        }
        else if(elemento_seleccionado == 4){
            elemento_seleccionado = 6;
            estado_switch(false);
            respaldo_fr->activo();
        }
        else if(elemento_seleccionado == 5){
            elemento_seleccionado = 6;
            trigger_inactivo();
            respaldo_fr->activo();
        }
        else if(elemento_seleccionado == 6){
            elemento_seleccionado = 7;
            respaldo_fr->inactivo();
            respaldo_pinsp->activo();
        }
        else if(elemento_seleccionado == 7){
            elemento_seleccionado = 8;
            respaldo_pinsp->inactivo();
            respaldo_tinsp->activo();
        }
        else if(elemento_seleccionado == 8){
            elemento_seleccionado = 9;
            respaldo_tinsp->inactivo();
            boton_activado();
        }
        else if(elemento_seleccionado == 9){
            elemento_seleccionado = 4;
            boton_inactivado();
            estado_switch(true);
        }
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

int UiModoPCPAP::mover_arriba(){
    try {
        if(elemento_seleccionado == 0){
            elemento_seleccionado = -1;
            pcpap_cpap->inactivo();
        }
        else if(elemento_seleccionado == 1){
            elemento_seleccionado = -2;
            pcpap_ps->inactivo();
        }
        else if(elemento_seleccionado == 2){
            elemento_seleccionado = -3;
            pcpap_oxi->inactivo();
        }
        else if(elemento_seleccionado == 3){
            elemento_seleccionado = -4;
            pcpap_apnea->inactivo();
        }
        else if(elemento_seleccionado == 4){
            elemento_seleccionado = 2;
            estado_switch(false);
            pcpap_oxi->activo();
        }
        else if(elemento_seleccionado == 5){
            elemento_seleccionado = 4;
            trigger_inactivo();
            estado_switch(true);
        }
        else if(elemento_seleccionado == 6){
            elemento_seleccionado = 3;
            respaldo_fr->inactivo();
            pcpap_apnea->activo();
        }
        else if(elemento_seleccionado == 7){
            elemento_seleccionado = 3;
            respaldo_pinsp->inactivo();
            pcpap_apnea->activo();
        }
        else if(elemento_seleccionado == 8){
            elemento_seleccionado = 3;
            respaldo_tinsp->inactivo();
            pcpap_apnea->activo();
        }
        else if(elemento_seleccionado == 9){
            elemento_seleccionado = -6;
            boton_inactivado();
        }
        return elemento_seleccionado;
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return 0;
    }
}

int UiModoPCPAP::mover_abajo(){
    try {
        if(elemento_seleccionado == 0){
            elemento_seleccionado = 4;
            pcpap_cpap->inactivo();
            estado_switch(true);
        }
        else if(elemento_seleccionado == 1){
            elemento_seleccionado = 4;
            pcpap_ps->inactivo();
            estado_switch(true);
        }
        else if(elemento_seleccionado == 2){
            elemento_seleccionado = 4;
            pcpap_oxi->inactivo();
            estado_switch(true);
        }
        else if(elemento_seleccionado == 3){
            elemento_seleccionado = 7;
            pcpap_apnea->inactivo();
            respaldo_pinsp->activo();
        }
        else if(elemento_seleccionado == 4){
            elemento_seleccionado = 5;
            estado_switch(false);
            trigger_activo();
        }
        else if(elemento_seleccionado == 5){
            elemento_seleccionado = -2;
            trigger_inactivo();
        }
        else if(elemento_seleccionado == 6){
            elemento_seleccionado = -4;
            respaldo_fr->inactivo();
        }
        else if(elemento_seleccionado == 7){
            elemento_seleccionado = -4;
            respaldo_pinsp->inactivo();
        }
        else if(elemento_seleccionado == 8){
            elemento_seleccionado = -5;
            respaldo_tinsp->inactivo();
        }
        else if(elemento_seleccionado == 9){
            elemento_seleccionado = -6;
            boton_inactivado();
        }
        return elemento_seleccionado;
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return 0;
    }
}

void UiModoPCPAP::sumar(){
    try {
        //qDebug() << "sumar - pcpap: " + QString::number(elemento_seleccionado);
        //qDebug() << "sumar - pcpap - switch: " + QString::number(switchTrigger->estaChecked());
        if(elemento_seleccionado == 0){
            pcpap_cpap->sumar();
        }
        else if(elemento_seleccionado == 1){
            pcpap_ps->sumar();
        }
        else if(elemento_seleccionado == 2){
            pcpap_oxi->sumar();
        }
        else if(elemento_seleccionado == 3){
            pcpap_apnea->sumar();
        }
        else if(elemento_seleccionado == 5){
            if(switchTrigger->estaChecked()){
                trigger_f->sumar();
            }
            else{
                trigger_p->sumar();
            }
        }
        else if(elemento_seleccionado == 6){
            respaldo_fr->sumar();
            recalcular_ti();
        }
        else if(elemento_seleccionado == 7){
            respaldo_pinsp->sumar();
        }
        else if(elemento_seleccionado == 8){
            respaldo_tinsp->sumar();
        }
        obtener_info_adicional();
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiModoPCPAP::restar(){
    try {
        if(elemento_seleccionado == 0){
            pcpap_cpap->restar();
        }
        else if(elemento_seleccionado == 1){
            pcpap_ps->restar();
        }
        else if(elemento_seleccionado == 2){
            pcpap_oxi->restar();
        }
        else if(elemento_seleccionado == 3){
            pcpap_apnea->restar();
        }
        else if(elemento_seleccionado == 5){
            if(switchTrigger->estaChecked()){
                trigger_f->restar();
            }
            else{
                trigger_p->restar();
            }
        }
        else if(elemento_seleccionado == 6){
            respaldo_fr->restar();
            recalcular_ti();
        }
        else if(elemento_seleccionado == 7){
            respaldo_pinsp->restar();
        }
        else if(elemento_seleccionado == 8){
            respaldo_tinsp->restar();
        }
        obtener_info_adicional();
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiModoPCPAP::switch_trigger(){
    try {
        if(switchTrigger->estaChecked()){
            switchTrigger->ponerChecked(false);
        }
        else{
            switchTrigger->ponerChecked(true);
        }
        switchTrigger->actualizar();
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiModoPCPAP::cambiaTipoTrigger(){
    try {
        if(switchTrigger->estaChecked()){
            conte_trigger->setCurrentWidget(trigger_f);
        }
        else{
            conte_trigger->setCurrentWidget(trigger_p);
        }
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiModoPCPAP::cambiaPerilla(){
    try {
        float peri = 0;
        if(elemento_seleccionado == 0){
            peri = pcpap_cpap->cambiar_perilla();
        }
        else if(elemento_seleccionado == 1){
            peri = pcpap_ps->cambiar_perilla();
        }
        else if(elemento_seleccionado == 2){
            peri = pcpap_oxi->cambiar_perilla();
        }
        else if(elemento_seleccionado == 3){
            peri = pcpap_apnea->cambiar_perilla();
        }
        else if(elemento_seleccionado == 5){
            if(switchTrigger->estaChecked()){
                peri = trigger_f->cambiar_perilla();
            }
            else{
                peri = trigger_p->cambiar_perilla();
            }
        }
        else if(elemento_seleccionado == 6){
            peri = respaldo_fr->cambiar_perilla();
        }
        else if(elemento_seleccionado == 7){
            peri = respaldo_pinsp->cambiar_perilla();
        }
        else if(elemento_seleccionado == 8){
            peri = respaldo_tinsp->cambiar_perilla();
        }
        mostrar_mensaje("Perilla: " + QString::number(peri,'f',1)); //falta mensaje como argumento
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiModoPCPAP::cargar_valores(QStringList lista_valores){
    try {
        pcpap_cpap->set_valor(lista_valores.at(1));
        pcpap_ps->set_valor(lista_valores.at(2));
        pcpap_oxi->set_valor(lista_valores.at(3));
        pcpap_apnea->set_valor(lista_valores.at(4));
        set_trigger(lista_valores.at(5));
        update_trigger();
        trigger_f->set_valor(lista_valores.at(6));
        trigger_p->set_valor(lista_valores.at(7));
        respaldo_fr->set_valor(lista_valores.at(8));
        respaldo_pinsp->set_valor(lista_valores.at(9));
        respaldo_tinsp->set_valor(lista_valores.at(10));
        recalcular_ti();
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

QStringList UiModoPCPAP::obtener_valores(){
    try {
        QStringList *param_list = new QStringList;
        param_list->append(QString::number(pcpap_cpap->get_valor()));
        param_list->append(QString::number(pcpap_ps->get_valor()));
        param_list->append(QString::number(pcpap_oxi->get_valor()));
        param_list->append(QString::number(pcpap_apnea->get_valor()));
        if(switchTrigger->estaChecked()){
           param_list->append("1");
        }
        else{
            param_list->append("0");
        }
        param_list->append(QString::number(trigger_f->get_valor()));
        param_list->append(QString::number(trigger_p->get_valor()));
        param_list->append(QString::number(respaldo_fr->get_valor()));
        param_list->append(QString::number(respaldo_pinsp->get_valor()));
        param_list->append(QString::number(respaldo_tinsp->get_valor()));
        return *param_list;
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return QStringList();
    }
}

void UiModoPCPAP::recalcular_ti(){
    try {
        float ti_max = (60.0/respaldo_fr->get_valor()) - min_te_min;
        respaldo_tinsp->set_lim_sup((QString::number(ti_max,'f',1).toFloat()));
        respaldo_tinsp->set_lim_inf(min_ti);
        if(respaldo_tinsp->get_valor() > ti_max){
            respaldo_tinsp->set_valor((QString::number(ti_max,'f',1)));
        }
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiModoPCPAP::obtener_info_adicional(){
    try {
        float periodo = 60.0/respaldo_fr->get_valor();
        float ti = respaldo_tinsp->get_valor();
        float te = periodo - ti;
        float relacion = te/ti;
        if(relacion >= 1){
            labelIE->setText("Relación I:E 1:" + QString::number(relacion,'f',1));
        }
        else{
            float val_i = 1/ relacion;
            labelIE->setText("Relación I:E " + QString::number(val_i,'f',1) + ":1");
        }
        labelTE->setText("TE " + QString::number(te,'f',1) + "seg");
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiModoPCPAP::mostrar_mensaje(QString mensaje){
    try {
        labelInfo->setText(mensaje);
        timerMensaje->start(5000);
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiModoPCPAP::outTimer(){
    try {
        labelInfo->setText("");
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}
