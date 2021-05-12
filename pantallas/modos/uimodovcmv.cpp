#include "uimodovcmv.h"

UiModoVCMV::UiModoVCMV() : QWidget()
{
    try {
        btn = "QPushButton { border: 2px solid gray; border-radius: 5px; color: white; background-color: rgb(43,42,41);}";
        btnSeleccionado = "QPushButton { border: 4px solid rgb(255,112,61); border-radius: 5px; color: white; background-color: rgb(43,42,41);}";

        vcmv_vtinsp = new WidgetParametro(this, "VTinsp", "ml", 2000.0, 0, "10", 0, 0, 0, false);
        vcmv_vtinsp->setObjectName("vcmv_vtinsp");
        vcmv_vtinsp->setGeometry(QRect(50, 0, 150, 140));
        vcmv_vtinsp->set_lim_inf(100);

        vcmv_peep = new WidgetParametro(this, "PEEP", "cmH2O", 30.0, 0, "1", 0, 1, 0, true);
        vcmv_peep->setObjectName("vcmv_peep");
        vcmv_peep->setGeometry(QRect(50, 150, 150, 140));

        vcmv_fr = new WidgetParametro(this, "Fr", "/min", 60.0, 0, "1", 0, 2, 0, false);
        vcmv_fr->setObjectName("vcmv_fr");
        vcmv_fr->setGeometry(QRect(50, 290, 150, 140));
        vcmv_fr->set_lim_inf(2);

        vcmv_flujo = new WidgetParametro(this, "Flujo", "l/min", 100.0, 0, "1", 0, 3, 0, false);
        vcmv_flujo->setObjectName("vcmv_flujo");
        vcmv_flujo->setGeometry(QRect(250, 0, 150, 140));
        vcmv_flujo->set_lim_inf(10);
        vcmv_flujo->set_lim_sup(100);

        vcmv_meseta = new WidgetParametro(this, "Meseta", "seg", 10.0, 0.0, "0.1", 0, 4, 1, false);
        vcmv_meseta->setObjectName("vcmv_meseta");
        vcmv_meseta->setGeometry(QRect(250, 150, 150, 140));

        vcmv_oxi = new WidgetParametro(this, "Oxígeno", "%", 100.0, 0, "1", 0, 6, 0, false);
        vcmv_oxi->setObjectName("vcmv_oxi");
        vcmv_oxi->setGeometry(QRect(250, 290, 150, 140));
        vcmv_oxi->set_lim_inf(21);

        TriggerBox = new QGroupBox(this);
        TriggerBox->setGeometry(QRect(430, 75, 300, 250));
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
        btnguardarCambios->setGeometry(QRect(750, 200, 250, 50));
        btnguardarCambios->setObjectName("btnguardarCambios");
        btnguardarCambios->setStyleSheet(btn);

        labelInfo = new QLabel(this);
        labelInfo->setGeometry(QRect(750, 250, 250, 100));
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

void UiModoVCMV::retranslateUi(){
    try {
        btnguardarCambios->setText("GUARDAR CAMBIOS");
        TriggerBox->setTitle("Trigger");
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiModoVCMV::paintEvent(QPaintEvent* /*event*/)
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

int UiModoVCMV::get_elemento_seleccionado(){
    try {
        return elemento_seleccionado;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return 0;
    }
}

void UiModoVCMV::set_trigger(QString estado){
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

void UiModoVCMV::update_trigger(){
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

void UiModoVCMV::set_elemento_seleccionado(int elemento){
    try {
        elemento_seleccionado = elemento;
        if(elemento_seleccionado == 0){
            vcmv_vtinsp->activo();
        }
        else if(elemento_seleccionado == 1){
            vcmv_peep->activo();
        }
        else if(elemento_seleccionado == 2){
            vcmv_fr->activo();
        }
        else if(elemento_seleccionado == 3){
            vcmv_flujo->activo();
        }
        else if(elemento_seleccionado == 4){
            vcmv_meseta->activo();
        }
        else if(elemento_seleccionado == 5){
            vcmv_oxi->activo();
        }
        else if(elemento_seleccionado == 6){
            estado_switch(true);
        }
        else if(elemento_seleccionado == 7){
            trigger_activo();
        }
        else if(elemento_seleccionado == 8){
            boton_activado();
        }
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiModoVCMV::boton_activado(){
    try {
        btnguardarCambios->setStyleSheet(btnSeleccionado);
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiModoVCMV::boton_inactivado(){
    try {
        btnguardarCambios->setStyleSheet(btn);
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiModoVCMV::trigger_inactivo(){
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

void UiModoVCMV::trigger_activo(){
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

void UiModoVCMV::estado_switch(bool estado){
    try {
        switchTrigger->switchSel(estado);
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiModoVCMV::mover_izquierda(){
    try {
        if(elemento_seleccionado == 0){
            elemento_seleccionado = 6;
            vcmv_vtinsp->inactivo();
            estado_switch(true);
        }
        else if(elemento_seleccionado == 1){
            elemento_seleccionado = 8;
            vcmv_peep->inactivo();
            boton_activado();
        }
        else if(elemento_seleccionado == 2){
            elemento_seleccionado = 8;
            vcmv_fr->inactivo();
            boton_activado();
        }
        else if(elemento_seleccionado == 3){
            elemento_seleccionado = 0;
            vcmv_flujo->inactivo();
            vcmv_vtinsp->activo();
        }
        else if(elemento_seleccionado == 4){
            elemento_seleccionado = 1;
            vcmv_meseta->inactivo();
            vcmv_peep->activo();
        }
        else if(elemento_seleccionado == 5){
            elemento_seleccionado = 2;
            vcmv_oxi->inactivo();
            vcmv_fr->activo();
        }
        else if(elemento_seleccionado == 6){
            elemento_seleccionado = 3;
            estado_switch(false);
            vcmv_flujo->activo();
        }
        else if(elemento_seleccionado == 7){
            elemento_seleccionado = 4;
            trigger_inactivo();
            vcmv_meseta->activo();
        }
        else if(elemento_seleccionado == 8){
            elemento_seleccionado = 7;
            boton_inactivado();
            trigger_activo();
        }
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiModoVCMV::mover_derecha(){
    try {
        if(elemento_seleccionado == 0){
            elemento_seleccionado = 3;
            vcmv_vtinsp->inactivo();
            vcmv_flujo->activo();
        }
        else if(elemento_seleccionado == 1){
            elemento_seleccionado = 4;
            vcmv_peep->inactivo();
            vcmv_meseta->activo();
        }
        else if(elemento_seleccionado == 2){
            elemento_seleccionado = 5;
            vcmv_fr->inactivo();
            vcmv_oxi->activo();
        }
        else if(elemento_seleccionado == 3){
            elemento_seleccionado = 6;
            vcmv_flujo->inactivo();
            estado_switch(true);
        }
        else if(elemento_seleccionado == 4){
            elemento_seleccionado = 7;
            vcmv_meseta->inactivo();
            trigger_activo();
        }
        else if(elemento_seleccionado == 5){
            elemento_seleccionado = 7;
            vcmv_oxi->inactivo();
            trigger_activo();
        }
        else if(elemento_seleccionado == 6){
            elemento_seleccionado = 8;
            estado_switch(false);
            boton_activado();
        }
        else if(elemento_seleccionado == 7){
            elemento_seleccionado = 8;
            trigger_inactivo();
            boton_activado();
        }
        else if(elemento_seleccionado == 8){
            elemento_seleccionado = 1;
            boton_inactivado();
            vcmv_peep->activo();
        }
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

int UiModoVCMV::mover_arriba(){
    try {
        if(elemento_seleccionado == 0){
            elemento_seleccionado = -1;
            vcmv_vtinsp->inactivo();
        }
        else if(elemento_seleccionado == 1){
            elemento_seleccionado = 0;
            vcmv_peep->inactivo();
            vcmv_vtinsp->activo();
        }
        else if(elemento_seleccionado == 2){
            elemento_seleccionado = 1;
            vcmv_fr->inactivo();
            vcmv_peep->activo();
        }
        else if(elemento_seleccionado == 3){
            elemento_seleccionado = -3;
            vcmv_flujo->inactivo();
        }
        else if(elemento_seleccionado == 4){
            elemento_seleccionado = 3;
            vcmv_meseta->inactivo();
            vcmv_flujo->activo();
        }
        else if(elemento_seleccionado == 5){
            elemento_seleccionado = 4;
            vcmv_oxi->inactivo();
            vcmv_meseta->activo();
        }
        else if(elemento_seleccionado == 6){
            elemento_seleccionado = -4;
            estado_switch(false);
        }
        else if(elemento_seleccionado == 7){
            elemento_seleccionado = 6;
            trigger_inactivo();
            estado_switch(true);
        }
        else if(elemento_seleccionado == 8){
            elemento_seleccionado = -6;
            boton_inactivado();
        }
        return elemento_seleccionado;
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return 0;
    }
}

int UiModoVCMV::mover_abajo(){
    try {
        if(elemento_seleccionado == 0){
            elemento_seleccionado = 1;
            vcmv_vtinsp->inactivo();
            vcmv_peep->activo();
        }
        else if(elemento_seleccionado == 1){
            elemento_seleccionado = 2;
            vcmv_peep->inactivo();
            vcmv_fr->activo();
        }
        else if(elemento_seleccionado == 2){
            elemento_seleccionado = -1;
            vcmv_fr->inactivo();
        }
        else if(elemento_seleccionado == 3){
            elemento_seleccionado = 4;
            vcmv_flujo->inactivo();
            vcmv_meseta->activo();
        }
        else if(elemento_seleccionado == 4){
            elemento_seleccionado = 5;
            vcmv_meseta->inactivo();
            vcmv_oxi->activo();
        }
        else if(elemento_seleccionado == 5){
            elemento_seleccionado = -3;
            vcmv_oxi->inactivo();
        }
        else if(elemento_seleccionado == 6){
            elemento_seleccionado = 7;
            estado_switch(false);
            trigger_activo();
        }
        else if(elemento_seleccionado == 7){
            elemento_seleccionado = -4;
            trigger_inactivo();
        }
        else if(elemento_seleccionado == 8){
            elemento_seleccionado = -6;
            boton_inactivado();
        }
        return elemento_seleccionado;
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return 0;
    }
}

void UiModoVCMV::sumar(){
    try {
//        qDebug() << "sumar - vcmv: " + QString::number(elemento_seleccionado);
//        qDebug() << "sumar - vcmv - switch: " + QString::number(switchTrigger->estaChecked());
        if(elemento_seleccionado == 0){
            if(vcmv_vtinsp->sumar()){
                if(buscar_limites()){
                      recalcular_tp_max();
                }
                else{
                    vcmv_vtinsp->restar();
                }
            }
        }
        else if(elemento_seleccionado == 1){
            vcmv_peep->sumar();
        }
        else if(elemento_seleccionado == 2){
            if(vcmv_fr->sumar()){
                if(buscar_limites()){
                    recalcular_tp_max();
                    recalcular_vt_max();
                }
                else{
                    vcmv_fr->restar();
                }
            }
        }
        else if(elemento_seleccionado == 3){
            if(vcmv_flujo->sumar()){
                if(buscar_limites()){
                    recalcular_tp_max();
                    recalcular_vt_max();
                }
                else{
                    vcmv_flujo->restar();
                }
            }
        }
        else if(elemento_seleccionado == 4){
            if(vcmv_meseta->sumar()){
                if(buscar_limites()){
                    recalcular_vt_max();
                }
                else{
                    vcmv_meseta->restar();
                }
            }
        }
        else if(elemento_seleccionado == 5){
            vcmv_oxi->sumar();
        }
        else if(elemento_seleccionado == 7){
            if(switchTrigger->estaChecked()){
                trigger_f->sumar();
            }
            else{
                trigger_p->sumar();
            }
        }
        obtener_info_adicional();
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiModoVCMV::restar(){
    try {
        if(elemento_seleccionado == 0){
            if(vcmv_vtinsp->restar()){
                if(buscar_limites()){
                      recalcular_tp_max();
                }
                else{
                    vcmv_vtinsp->sumar();
                }
            }
        }
        else if(elemento_seleccionado == 1){
            vcmv_peep->restar();
        }
        else if(elemento_seleccionado == 2){
            if(vcmv_fr->restar()){
                if(buscar_limites()){
                    recalcular_tp_max();
                    recalcular_vt_max();
                }
                else{
                    vcmv_fr->sumar();
                }
            }
        }
        else if(elemento_seleccionado == 3){
            if(vcmv_flujo->restar()){
                if(buscar_limites()){
                    recalcular_tp_max();
                    recalcular_vt_max();
                }
                else{
                    vcmv_flujo->sumar();
                }
            }
        }
        else if(elemento_seleccionado == 4){
            if(vcmv_meseta->restar()){
                if(buscar_limites()){
                    recalcular_vt_max();
                }
                else{
                    vcmv_meseta->sumar();
                }
            }
        }
        else if(elemento_seleccionado == 5){
            vcmv_oxi->restar();
        }
        else if(elemento_seleccionado == 7){
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

void UiModoVCMV::switch_trigger(){
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

void UiModoVCMV::cambiaTipoTrigger(){
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

void UiModoVCMV::cambiaPerilla(){
    try {
        float peri = 0;
        if(elemento_seleccionado == 0){
            peri = vcmv_vtinsp->cambiar_perilla();
        }
        else if(elemento_seleccionado == 1){
            peri = vcmv_peep->cambiar_perilla();
        }
        else if(elemento_seleccionado == 2){
            peri = vcmv_fr->cambiar_perilla();
        }
        else if(elemento_seleccionado == 3){
            peri = vcmv_flujo->cambiar_perilla();
        }
        else if(elemento_seleccionado == 4){
            peri = vcmv_meseta->cambiar_perilla();
        }
        else if(elemento_seleccionado == 5){
            peri = vcmv_oxi->cambiar_perilla();
        }
        else if(elemento_seleccionado == 7){
            if(switchTrigger->estaChecked()){
                peri = trigger_f->cambiar_perilla();
            }
            else{
                peri = trigger_p->cambiar_perilla();
            }
        }
        mostrar_mensaje("Perilla: " + QString::number(peri,'f',1)); //falta mensaje como argumento
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiModoVCMV::cargar_valores(QStringList lista_valores){
    try {
        vcmv_vtinsp->set_valor(lista_valores.at(1));
        vcmv_peep->set_valor(lista_valores.at(2));
        vcmv_fr->set_valor(lista_valores.at(3));
        vcmv_flujo->set_valor(lista_valores.at(4));
        vcmv_meseta->set_valor(lista_valores.at(5));
        vcmv_oxi->set_valor(lista_valores.at(7));
        set_trigger(lista_valores.at(8));
        update_trigger();
        trigger_f->set_valor(lista_valores.at(9));
        trigger_p->set_valor(lista_valores.at(10));
        recalcular_vt_max();
        recalcular_tp_max();
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

QStringList UiModoVCMV::obtener_valores(){
    try {
        QStringList *param_list = new QStringList;
        param_list->append(QString::number(vcmv_vtinsp->get_valor()));
        param_list->append(QString::number(vcmv_peep->get_valor()));
        param_list->append(QString::number(vcmv_fr->get_valor()));
        param_list->append(QString::number(vcmv_flujo->get_valor()));
        param_list->append(QString::number(vcmv_meseta->get_valor()));
        param_list->append("0");
        param_list->append(QString::number(vcmv_oxi->get_valor()));
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

void UiModoVCMV::recalcular_tp_max(){
    try {
        float periodo = 60.0/vcmv_fr->get_valor();
        float TI = periodo - te_min;
        float pi = ((vcmv_vtinsp->get_valor()/1000) / vcmv_flujo->get_valor())*60;
        tp_min = QString::number(TI - pi,'f',1).toFloat();
        vcmv_meseta->set_lim_sup(tp_min);
        if(vcmv_meseta->get_valor() > tp_min){
            vcmv_meseta->set_valor(QString::number(tp_min,'f',1));
        }
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

bool UiModoVCMV::buscar_limites(){
    try {
        float vol_l = vcmv_vtinsp->get_valor()/1000;
        if(vol_l < 0){
            return false;
        }
        float flujo = vcmv_flujo->get_valor();
        if(flujo < 0){
            return false;
        }
        float pi = (vol_l/flujo)*60;
        if(pi <0){
            return false;
        }
        float tp = vcmv_meseta->get_valor();
        if(tp < 0){
            return false;
        }
        float ti = QString::number(pi + tp,'f',1).toFloat();
        if(ti < 0){
            return false;
        }
        labelTI->setText("TI: " + QString::number(ti) + " seg");
        float periodo = 60 / vcmv_fr->get_valor();
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

void UiModoVCMV::recalcular_vt_max(){
    try {
        float periodo = 60.0/vcmv_fr->get_valor();
        float ti_max_ = periodo - te_min;
        float pi_max_ = ti_max_ -vcmv_meseta->get_valor();
        vt_max = static_cast<int>(((vcmv_flujo->get_valor() * pi_max_) / 60.0)* 1000);
        vcmv_vtinsp->set_lim_sup(vt_max);
        if(vcmv_vtinsp->get_valor() > vt_max){
            vcmv_vtinsp->set_valor(QString::number(vt_max,'f',1));
        }
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiModoVCMV::obtener_info_adicional(){
    try {
        float vol_l = vcmv_vtinsp->get_valor() / 1000.0;
        float flujo = vcmv_flujo->get_valor();
        float pi = (vol_l/flujo)*60;
        float tp = vcmv_meseta->get_valor();
        float ti_ = QString::number(pi+tp,'f',1).toFloat();
        float ti_nor = pi + tp;
        labelTI->setText("TI: " + QString::number(ti_) + " seg");
        float periodo = 60 / vcmv_fr->get_valor();
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

void UiModoVCMV::mostrar_mensaje(QString mensaje){
    try {
        labelInfo->setText(mensaje);
        timerMensaje->start(5000);
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiModoVCMV::outTimer(){
    try {
        labelInfo->setText("");
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}
