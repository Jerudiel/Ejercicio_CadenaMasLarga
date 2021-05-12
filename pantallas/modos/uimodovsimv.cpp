#include "uimodovsimv.h"

UiModoVSIMV::UiModoVSIMV() : QWidget()
{
    try {
        btn = "QPushButton { border: 2px solid gray; border-radius: 5px; color: white; background-color: rgb(43,42,41);}";
        btnSeleccionado = "QPushButton { border: 4px solid rgb(255,112,61); border-radius: 5px; color: white; background-color: rgb(43,42,41);}";

        vsimv_vtinsp = new WidgetParametro(this, "VTinsp", "ml", 2000.0, 0, "10", 0, 0, 0, false);
        vsimv_vtinsp->setObjectName("vsimv_vtinsp");
        vsimv_vtinsp->setGeometry(QRect(50, 0, 150, 140));
        vsimv_vtinsp->set_lim_inf(100);

        vsimv_psoporte = new WidgetParametro(this, "PSoporte", "cmH2O", 20.0, 0, "1", 0, 1, 0, false);
        vsimv_psoporte->setObjectName("vsimv_psoporte");
        vsimv_psoporte->setGeometry(QRect(50, 150, 150, 140));

        vsimv_peep = new WidgetParametro(this, "PEEP", "cmH2O", 30.0, 0, "1", 0, 2, 0, true);
        vsimv_peep->setObjectName("vsimv_peep");
        vsimv_peep->setGeometry(QRect(50, 290, 150, 140));

        vsimv_fr = new WidgetParametro(this, "Fr", "/min", 60.0, 0, "1", 0, 3, 0, false);
        vsimv_fr->setObjectName("vsimv_fr");
        vsimv_fr->setGeometry(QRect(250, 0, 150, 140));
        vsimv_fr->set_lim_inf(2);

        vsimv_flujo = new WidgetParametro(this, "Flujo", "l/min", 100.0, 0, "1", 0, 4, 0, false);
        vsimv_flujo->setObjectName("vsimv_flujo");
        vsimv_flujo->setGeometry(QRect(250, 150, 150, 140));
        vsimv_flujo->set_lim_inf(10);
        vsimv_flujo->set_lim_sup(100);

        vsimv_meseta = new WidgetParametro(this, "Meseta", "seg", 10.0, 0, "0.1", 0, 6, 1, false);
        vsimv_meseta->setObjectName("vsimv_meseta");
        vsimv_meseta->setGeometry(QRect(420, 0, 150, 140));

        vsimv_oxi = new WidgetParametro(this,"Oxígeno", "%", 100.0, 0, "1", 0, 7, 0, false);
        vsimv_oxi->setObjectName("vsimv_oxi");
        vsimv_oxi->setGeometry(QRect(580, 0, 150, 140));
        vsimv_oxi->set_lim_inf(21);

        TriggerBox = new QGroupBox(this);
        TriggerBox->setGeometry(QRect(450, 150, 300, 250));
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
        labelTI->setObjectName("labelPF");

        btnguardarCambios = new QPushButton(this);
        fuente->setPointSize(14);
        btnguardarCambios->setFont(*fuente);
        btnguardarCambios->setGeometry(QRect(755, 200, 250, 50));
        btnguardarCambios->setObjectName("btnguardarCambios");
        btnguardarCambios->setStyleSheet(btn);

        labelInfo = new QLabel(this);
        labelInfo->setGeometry(QRect(755, 250, 250, 100));
        labelInfo->setFont(*fuente);
        labelInfo->setAlignment(Qt::AlignCenter);
        labelInfo->setObjectName("labelInfo");

        elemento_seleccionado = 0;
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
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiModoVSIMV::retranslateUi(){
    try {
        btnguardarCambios->setText("GUARDAR CAMBIOS");
        TriggerBox->setTitle("Trigger");
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiModoVSIMV::paintEvent(QPaintEvent* /*event*/)
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

int UiModoVSIMV::get_elemento_seleccionado(){
    try {
        return elemento_seleccionado;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return 0;
    }
}

void UiModoVSIMV::set_trigger(QString estado){
    try {
        if(estado == "0"){
            switchTrigger->ponerChecked(false);
        }
        else{
            switchTrigger->ponerChecked(true);
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiModoVSIMV::update_trigger(){
    try {
        if(switchTrigger->estaChecked()){
            conte_trigger->setCurrentWidget(trigger_f);
        }
        else{
            conte_trigger->setCurrentWidget(trigger_p);
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiModoVSIMV::set_elemento_seleccionado(int elemento){
    try {
        elemento_seleccionado = elemento;
        if(elemento_seleccionado == 0){
            vsimv_vtinsp->activo();
        }
        else if(elemento_seleccionado == 1){
            vsimv_psoporte->activo();
        }
        else if(elemento_seleccionado == 2){
            vsimv_peep->activo();
        }
        else if(elemento_seleccionado == 3){
            vsimv_fr->activo();
        }
        else if(elemento_seleccionado == 4){
            vsimv_flujo->activo();
        }
        else if(elemento_seleccionado == 5){
            vsimv_meseta->activo();
        }
        else if(elemento_seleccionado == 6){
            vsimv_oxi->activo();
        }
        else if(elemento_seleccionado == 7){
            estado_switch(true);
        }
        else if(elemento_seleccionado == 8){
            trigger_activo();
        }
        else if(elemento_seleccionado == 9){
            boton_activado();
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiModoVSIMV::boton_activado(){
    try {
        btnguardarCambios->setStyleSheet(btnSeleccionado);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiModoVSIMV::boton_inactivado(){
    try {
        btnguardarCambios->setStyleSheet(btn);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiModoVSIMV::trigger_inactivo(){
    try {
        if(switchTrigger->estaChecked()){
            trigger_f->inactivo();
        }
        else{
            trigger_p->inactivo();
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiModoVSIMV::trigger_activo(){
    try {
        if(switchTrigger->estaChecked()){
            trigger_f->activo();
        }
        else{
            trigger_p->activo();
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiModoVSIMV::estado_switch(bool estado){
    try {
        switchTrigger->switchSel(estado);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiModoVSIMV::mover_izquierda(){
    try {
        if(elemento_seleccionado == 0){
            elemento_seleccionado = 6;
            vsimv_vtinsp->inactivo();
            vsimv_oxi->activo();
        }
        else if(elemento_seleccionado == 1){
            elemento_seleccionado = 9;
            vsimv_psoporte->inactivo();
            boton_activado();
        }
        else if(elemento_seleccionado == 2){
            elemento_seleccionado = 9;
            vsimv_peep->inactivo();
            boton_activado();
        }
        else if(elemento_seleccionado == 3){
            elemento_seleccionado = 0;
            vsimv_fr->inactivo();
            vsimv_vtinsp->activo();
        }
        else if(elemento_seleccionado == 4){
            elemento_seleccionado = 1;
            vsimv_flujo->inactivo();
            vsimv_psoporte->activo();
        }
        else if(elemento_seleccionado == 5){
            elemento_seleccionado = 3;
            vsimv_meseta->inactivo();
            vsimv_fr->activo();
        }
        else if(elemento_seleccionado == 6){
            elemento_seleccionado = 5;
            vsimv_oxi->inactivo();
            vsimv_meseta->activo();
        }
        else if(elemento_seleccionado == 7){
            elemento_seleccionado = 4;
            estado_switch(false);
            vsimv_flujo->activo();
        }
        else if(elemento_seleccionado == 8){
            elemento_seleccionado = 4;
            trigger_inactivo();
            vsimv_flujo->activo();
        }
        else if(elemento_seleccionado == 9){
            elemento_seleccionado = 7;
            boton_inactivado();
            estado_switch(true);
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiModoVSIMV::mover_derecha(){
    try {
        if(elemento_seleccionado == 0){
            elemento_seleccionado = 3;
            vsimv_vtinsp->inactivo();
            vsimv_fr->activo();
        }
        else if(elemento_seleccionado == 1){
            elemento_seleccionado = 4;
            vsimv_psoporte->inactivo();
            vsimv_flujo->activo();
        }
        else if(elemento_seleccionado == 2){
            elemento_seleccionado = 4;
            vsimv_peep->inactivo();
            vsimv_flujo->activo();
        }
        else if(elemento_seleccionado == 3){
            elemento_seleccionado = 5;
            vsimv_fr->inactivo();
            vsimv_meseta->activo();
        }
        else if(elemento_seleccionado == 4){
            elemento_seleccionado = 7;
            vsimv_flujo->inactivo();
            estado_switch(true);
        }
        else if(elemento_seleccionado == 5){
            elemento_seleccionado = 6;
            vsimv_meseta->inactivo();
            vsimv_oxi->activo();
        }
        else if(elemento_seleccionado == 6){
            elemento_seleccionado = 0;
            vsimv_oxi->inactivo();
            vsimv_vtinsp->activo();
        }
        else if(elemento_seleccionado == 7){
            elemento_seleccionado = 9;
            estado_switch(false);
            boton_activado();
        }
        else if(elemento_seleccionado == 8){
            elemento_seleccionado = 9;
            trigger_inactivo();
            boton_activado();
        }
        else if(elemento_seleccionado == 9){
            elemento_seleccionado = 1;
            boton_inactivado();
            vsimv_psoporte->activo();
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

int UiModoVSIMV::mover_arriba(){
    try {
        if(elemento_seleccionado == 0){
            elemento_seleccionado = -1;
            vsimv_vtinsp->inactivo();
        }
        else if(elemento_seleccionado == 1){
            elemento_seleccionado = 0;
            vsimv_psoporte->inactivo();
            vsimv_vtinsp->activo();
        }
        else if(elemento_seleccionado == 2){
            elemento_seleccionado = 1;
            vsimv_peep->inactivo();
            vsimv_psoporte->activo();
        }
        else if(elemento_seleccionado == 3){
            elemento_seleccionado = -3;
            vsimv_fr->inactivo();
        }
        else if(elemento_seleccionado == 4){
            elemento_seleccionado = 3;
            vsimv_flujo->inactivo();
            vsimv_fr->activo();
        }
        else if(elemento_seleccionado == 5){
            elemento_seleccionado = -4;
            vsimv_meseta->inactivo();
        }
        else if(elemento_seleccionado == 6){
            elemento_seleccionado = -5;
            vsimv_oxi->inactivo();
        }
        else if(elemento_seleccionado == 7){
            elemento_seleccionado = 6;
            estado_switch(false);
            vsimv_oxi->activo();
        }
        else if(elemento_seleccionado == 8){
            elemento_seleccionado = 7;
            trigger_inactivo();
            estado_switch(true);
        }
        else if(elemento_seleccionado == 9){
            elemento_seleccionado = -6;
            boton_inactivado();
        }
        return elemento_seleccionado;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return 0;
    }
}

int UiModoVSIMV::mover_abajo(){
    try {
        if(elemento_seleccionado == 0){
            elemento_seleccionado = 1;
            vsimv_vtinsp->inactivo();
            vsimv_psoporte->activo();
        }
        else if(elemento_seleccionado == 1){
            elemento_seleccionado = 2;
            vsimv_psoporte->inactivo();
            vsimv_peep->activo();
        }
        else if(elemento_seleccionado == 2){
            elemento_seleccionado = -1;
            vsimv_peep->inactivo();
        }
        else if(elemento_seleccionado == 3){
            elemento_seleccionado = 4;
            vsimv_fr->inactivo();
            vsimv_flujo->activo();
        }
        else if(elemento_seleccionado == 4){
            elemento_seleccionado = -3;
            vsimv_flujo->inactivo();
        }
        else if(elemento_seleccionado == 5){
            elemento_seleccionado = 7;
            vsimv_meseta->inactivo();
            estado_switch(true);
        }
        else if(elemento_seleccionado == 6){
            elemento_seleccionado = 7;
            vsimv_oxi->inactivo();
            estado_switch(true);
        }
        else if(elemento_seleccionado == 7){
            elemento_seleccionado = 8;
            estado_switch(false);
            trigger_activo();
        }
        else if(elemento_seleccionado == 8){
            elemento_seleccionado = -4;
            trigger_inactivo();
        }
        else if(elemento_seleccionado == 9){
            elemento_seleccionado = -6;
            boton_inactivado();
        }
        return elemento_seleccionado;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return 0;
    }
}

void UiModoVSIMV::sumar(){
    try {
        //qDebug() << "sumar - vsimv: " + QString::number(elemento_seleccionado);
        //qDebug() << "sumar - vsimv - switch: " + QString::number(switchTrigger->estaChecked());
        if(elemento_seleccionado == 0){
            if(vsimv_vtinsp->sumar()){
                if(buscar_limites()){
                      recalcular_tp_max();
                }
                else{
                    vsimv_vtinsp->restar();
                }
            }
        }
        else if(elemento_seleccionado == 1){
            vsimv_psoporte->sumar();
        }
        else if(elemento_seleccionado == 2){
            vsimv_peep->sumar();
        }
        else if(elemento_seleccionado == 3){
            if(vsimv_fr->sumar()){
                if(buscar_limites()){
                    recalcular_tp_max();
                    recalcular_vt_max();
                }
                else{
                    vsimv_fr->restar();
                }
            }
        }
        else if(elemento_seleccionado == 4){
            if(vsimv_flujo->sumar()){
                if(buscar_limites()){
                    recalcular_vt_max();
                }
                else{
                    vsimv_flujo->restar();
                }
            }
        }
        else if(elemento_seleccionado == 5){
            if(vsimv_meseta->sumar()){
                if(buscar_limites()){
                    recalcular_vt_max();
                }
                else{
                    vsimv_meseta->restar();
                }
            }
        }
        else if(elemento_seleccionado == 6){
            vsimv_oxi->sumar();
        }
        else if(elemento_seleccionado == 8){
            if(switchTrigger->estaChecked()){
                trigger_f->sumar();
            }
            else{
                trigger_p->sumar();
            }
        }
        obtener_info_adicional();
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiModoVSIMV::restar(){
    try {
        if(elemento_seleccionado == 0){
            if(vsimv_vtinsp->restar()){
                if(buscar_limites()){
                      recalcular_tp_max();
                }
                else{
                    vsimv_vtinsp->sumar();
                }
            }
        }
        else if(elemento_seleccionado == 1){
            vsimv_psoporte->restar();
        }
        else if(elemento_seleccionado == 2){
            vsimv_peep->restar();
        }
        else if(elemento_seleccionado == 3){
            if(vsimv_fr->restar()){
                if(buscar_limites()){
                    recalcular_tp_max();
                    recalcular_vt_max();
                }
                else{
                    vsimv_fr->sumar();
                }
            }
        }
        else if(elemento_seleccionado == 4){
            if(vsimv_flujo->restar()){
                if(buscar_limites()){
                    recalcular_vt_max();
                }
                else{
                    vsimv_flujo->sumar();
                }
            }
        }
        else if(elemento_seleccionado == 5){
            if(vsimv_meseta->restar()){
                if(buscar_limites()){
                    recalcular_vt_max();
                }
                else{
                    vsimv_meseta->sumar();
                }
            }
        }
        else if(elemento_seleccionado == 6){
            vsimv_oxi->restar();
        }
        else if(elemento_seleccionado == 8){
            if(switchTrigger->estaChecked()){
                trigger_f->restar();
            }
            else{
                trigger_p->restar();
            }
        }
        obtener_info_adicional();
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiModoVSIMV::switch_trigger(){
    try {
        if(switchTrigger->estaChecked()){
            switchTrigger->ponerChecked(false);
        }
        else{
            switchTrigger->ponerChecked(true);
        }
        switchTrigger->actualizar();
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiModoVSIMV::cambiaTipoTrigger(){
    try {
        if(switchTrigger->estaChecked()){
            conte_trigger->setCurrentWidget(trigger_f);
        }
        else{
            conte_trigger->setCurrentWidget(trigger_p);
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiModoVSIMV::cambiaPerilla(){
    try {
        float peri = 0;
        if(elemento_seleccionado == 0){
            peri = vsimv_vtinsp->cambiar_perilla();
        }
        else if(elemento_seleccionado == 1){
            peri = vsimv_psoporte->cambiar_perilla();
        }
        else if(elemento_seleccionado == 2){
            peri = vsimv_peep->cambiar_perilla();
        }
        else if(elemento_seleccionado == 3){
            peri = vsimv_fr->cambiar_perilla();
        }
        else if(elemento_seleccionado == 4){
            peri = vsimv_flujo->cambiar_perilla();
        }
        else if(elemento_seleccionado == 5){
            peri = vsimv_meseta->cambiar_perilla();
        }
        else if(elemento_seleccionado == 6){
            peri = vsimv_oxi->cambiar_perilla();
        }
        else if(elemento_seleccionado == 8){
            if(switchTrigger->estaChecked()){
                peri = trigger_f->cambiar_perilla();
            }
            else{
                peri = trigger_p->cambiar_perilla();
            }
        }
        mostrar_mensaje("Perilla: " + QString::number(peri,'f',1)); //falta mensaje como argumento
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiModoVSIMV::cargar_valores(QStringList lista_valores){
    try {
        vsimv_vtinsp->set_valor(lista_valores.at(1));
        vsimv_psoporte->set_valor(lista_valores.at(2));
        vsimv_peep->set_valor(lista_valores.at(3));
        vsimv_fr->set_valor(lista_valores.at(4));
        vsimv_flujo->set_valor(lista_valores.at(5));
        vsimv_meseta->set_valor(lista_valores.at(7));
        vsimv_oxi->set_valor(lista_valores.at(10));
        set_trigger(lista_valores.at(11));
        update_trigger();
        trigger_f->set_valor(lista_valores.at(12));
        trigger_p->set_valor(lista_valores.at(13));
        recalcular_vt_max();
        recalcular_tp_max();
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

QStringList UiModoVSIMV::obtener_valores(){
    try {
        QStringList *param_list = new QStringList;
        param_list->append(QString::number(vsimv_vtinsp->get_valor()));
        param_list->append(QString::number(vsimv_psoporte->get_valor()));
        param_list->append(QString::number(vsimv_peep->get_valor()));
        param_list->append(QString::number(vsimv_fr->get_valor()));
        param_list->append(QString::number(vsimv_flujo->get_valor()));
        param_list->append("0.2");
        param_list->append(QString::number(vsimv_meseta->get_valor()));
        param_list->append("15");
        param_list->append("0");
        param_list->append(QString::number(vsimv_oxi->get_valor()));
        if(switchTrigger->estaChecked()){
           param_list->append("1");
        }
        else{
            param_list->append("0");
        }
        param_list->append(QString::number(trigger_f->get_valor()));
        param_list->append(QString::number(trigger_p->get_valor()));
        return *param_list;
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return QStringList();
    }
}

void UiModoVSIMV::recalcular_tp_max(){
    try {
        float periodo = 60.0/vsimv_fr->get_valor();
        float TI = periodo - te_min;
        float pi = ((vsimv_vtinsp->get_valor()/1000) / vsimv_flujo->get_valor())*60;
        tp_min = QString::number(TI - pi,'f',1).toFloat();
        vsimv_meseta->set_lim_sup(tp_min);
        if(vsimv_meseta->get_valor() > tp_min){
            vsimv_meseta->set_valor(QString::number(tp_min,'f',1));
        }
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

bool UiModoVSIMV::buscar_limites(){
    try {
        float vol_l = vsimv_vtinsp->get_valor()/1000;
        if(vol_l < 0){
            return false;
        }
        float flujo = vsimv_flujo->get_valor();
        if(flujo < 0){
            return false;
        }
        float pi = (vol_l/flujo)*60;
        if(pi <0){
            return false;
        }
        float tp = vsimv_meseta->get_valor();
        if(tp < 0){
            return false;
        }
        float ti = QString::number(pi + tp,'f',1).toFloat();
        if(ti < 0){
            return false;
        }
        labelTI->setText("TI: " + QString::number(ti) + " seg");
        float periodo = 60 / vsimv_fr->get_valor();
        if(periodo <0){
            return false;
        }
        float te = QString::number(periodo - ti,'f',1).toFloat();
        if(te < 0){
            return false;
        }
        labelTE->setText("TE: " + QString::number(te) + " seg");
        float relacion = te/ti;
        if(relacion < 0){
            return false;
        }
        if(relacion >= 1){
            labelIE->setText("Relación I:E 1:" + QString::number(relacion,'f',1));
        }
        else{
            float val_i = 1 / relacion;
            labelIE->setText("Relación I:E " + QString::number(val_i,'f',1) + ":1");
        }
        return true;
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return false;
    }
}

void UiModoVSIMV::recalcular_vt_max(){
    try {
        //qDebug() << "recalcular_vt_max";
        float periodo = 60.0/vsimv_fr->get_valor();
        //qDebug() << "recalcular_vt_max-periodo: " + QString::number(periodo,'f',1);
        float ti_max_ = periodo - te_min;
        //qDebug() << "recalcular_vt_max-ti_max_: " + QString::number(ti_max_,'f',1);
        float pi_max_ = ti_max_ - vsimv_meseta->get_valor();
        //qDebug() << "recalcular_vt_max-pi_max_: " + QString::number(pi_max_,'f',1);
        vt_max = static_cast<int>(((vsimv_flujo->get_valor() * pi_max_) / 60.0)* 1000);
        //qDebug() << "recalcular_vt_max-vt_max: " + QString::number(vt_max,'f',1);
        vsimv_vtinsp->set_lim_sup(vt_max);
        if(vsimv_vtinsp->get_valor() > vt_max){
            vsimv_vtinsp->set_valor(QString::number(vt_max,'f',1));
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiModoVSIMV::obtener_info_adicional(){
    try {
        float vol_l = vsimv_vtinsp->get_valor() / 1000.0;
        float flujo = vsimv_flujo->get_valor();
        float pi = (vol_l/flujo)*60;
        float tp = vsimv_meseta->get_valor();
        float ti_ = QString::number(pi+tp,'f',1).toFloat();
        float ti_nor = pi + tp;
        labelTI->setText("TI: " + QString::number(ti_) + " seg");
        float periodo = 60 / vsimv_fr->get_valor();
        float te_ = QString::number(periodo - ti_nor,'f',1).toFloat();
        labelTE->setText("TE: " + QString::number(te_) + " seg");

        float relacion = te_/ti_;
        if(relacion >= 1){
            labelIE->setText("Relación I:E 1:" + QString::number(relacion,'f',1));
        }
        else{
            float val_i = 1/ relacion;
            labelIE->setText("Relación I:E " + QString::number(val_i,'f',1) + ":1");
        }
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiModoVSIMV::mostrar_mensaje(QString mensaje){
    try {
        labelInfo->setText(mensaje);
        timerMensaje->start(5000);
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiModoVSIMV::outTimer(){
    try {
        labelInfo->setText("");
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}
