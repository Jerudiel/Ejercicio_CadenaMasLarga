#include "uimodopcmv.h"

#include <QThread>

UiModoPCMV::UiModoPCMV() : QWidget()
{
    try {
        btn = "QPushButton { border: 2px solid gray; border-radius: 5px; color: white; background-color: rgb(43,42,41);}";
        btnSeleccionado = "QPushButton { border: 4px solid rgb(255,112,61); border-radius: 5px; color: white; background-color: rgb(43,42,41);}";

        pcmv_pinsp = new WidgetParametro(this, "Pinsp", "cmH2O", 150.0, 0 ,"1", 0, 0, 0, false);
        pcmv_pinsp->set_lim_inf(1);
        pcmv_pinsp->setObjectName("pcmv_pinsp");
        pcmv_pinsp->setGeometry(QRect(50,0,150,140));
        pcmv_pinsp->set_lim_inf(10);

        pcmv_oxi = new WidgetParametro(this, "Oxigeno", "%", 100.0, 0 ,"1", 0, 1, 0, false);
        pcmv_oxi->setObjectName("pcmv_oxi");
        pcmv_oxi->setGeometry(QRect(50,150,150,140));
        pcmv_oxi->set_lim_inf(21);

        pcmv_peep = new WidgetParametro(this, "PEEP", "cmH2O", 30, 0, "1", 0, 2, 0, true);
        pcmv_peep->setObjectName("pcmv_peep");
        pcmv_peep->setGeometry(QRect(50,290,150,140));

        pcmv_fr = new WidgetParametro(this, "Fr", "/min", 60.0, 0, "1", 0, 3, 0, false);
        pcmv_fr->setObjectName("pcmv_fr");
        pcmv_fr->setGeometry(QRect(250,0,150,140));
        pcmv_fr->set_lim_inf(2);

        pcmv_tinsp = new WidgetParametro(this, "Tinsp", "seg", 10.0, 0, "0.1", 0, 4, 1, false);
        pcmv_tinsp->set_lim_inf(0.3);
        pcmv_tinsp->setObjectName("pcmv_tinsp");
        pcmv_tinsp->setGeometry(QRect(250,150,150,140));

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

        labelPF = new QLabel(this);
        labelPF->setGeometry(QRect(750, 105, 250, 50));
        labelPF->setFont(*fuente);
        labelPF->setAlignment(Qt::AlignCenter);
        labelPF->setObjectName("labelPF");

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
        max_peep_mas_pip = 70; //180;
        min_te_min = 0.4;
        min_ti = 0.4;

        retranslateUi();

        timerMensaje = new QTimer;
        timerMensaje->setSingleShot(true);
        connect(timerMensaje, SIGNAL(timeout()), this, SLOT(outTimer()));
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiModoPCMV::retranslateUi(){
    try {
        btnguardarCambios->setText("GUARDAR CAMBIOS");
        TriggerBox->setTitle("Trigger");
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiModoPCMV::paintEvent(QPaintEvent* /*event*/)
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

int UiModoPCMV::get_elemento_seleccionado(){
    try {
        return elemento_seleccionado;
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return 0;
    }
}

void UiModoPCMV::set_trigger(QString estado){
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

void UiModoPCMV::update_trigger(){
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

void UiModoPCMV::set_elemento_seleccionado(int elemento){
    try {
        elemento_seleccionado = elemento;
        if(elemento_seleccionado == 0){
            pcmv_pinsp->activo();
        }
        else if(elemento_seleccionado == 1){
            pcmv_oxi->activo();
        }
        else if(elemento_seleccionado == 2){
            pcmv_peep->activo();
        }
        else if(elemento_seleccionado == 3){
            pcmv_fr->activo();
        }
        else if(elemento_seleccionado == 4){
            pcmv_tinsp->activo();
        }
        else if(elemento_seleccionado == 5){
            estado_switch(true);
        }
        else if(elemento_seleccionado == 6){
            trigger_activo();
        }
        else if(elemento_seleccionado == 7){
            boton_activado();
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiModoPCMV::boton_activado(){
    try {
        btnguardarCambios->setStyleSheet(btnSeleccionado);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiModoPCMV::boton_inactivado(){
    try {
        btnguardarCambios->setStyleSheet(btn);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiModoPCMV::trigger_inactivo(){
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

void UiModoPCMV::trigger_activo(){
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

void UiModoPCMV::estado_switch(bool estado){
    try {
        switchTrigger->switchSel(estado);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiModoPCMV::mover_izquierda(){
    try {
        if(elemento_seleccionado == 0){
            elemento_seleccionado = 5;
            pcmv_pinsp->inactivo();
            estado_switch(true);
        }
        else if(elemento_seleccionado == 1){
            elemento_seleccionado = 7;
            pcmv_oxi->inactivo();
            boton_activado();
        }
        else if(elemento_seleccionado == 2){
            elemento_seleccionado = 7;
            pcmv_peep->inactivo();
            boton_activado();
        }
        else if(elemento_seleccionado == 3){
            elemento_seleccionado = 0;
            pcmv_fr->inactivo();
            pcmv_pinsp->activo();
        }
        else if(elemento_seleccionado == 4){
            elemento_seleccionado = 1;
            pcmv_tinsp->inactivo();
            pcmv_oxi->activo();
        }
        else if(elemento_seleccionado == 5){
            elemento_seleccionado = 3;
            estado_switch(false);
            pcmv_fr->activo();
        }
        else if(elemento_seleccionado == 6){
            elemento_seleccionado = 4;
            trigger_inactivo();
            pcmv_tinsp->activo();
        }
        else if(elemento_seleccionado == 7){
            elemento_seleccionado = 6;
            boton_inactivado();
            trigger_activo();
        }
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiModoPCMV::mover_derecha(){
    try {
        if(elemento_seleccionado == 0){
            elemento_seleccionado = 3;
            pcmv_pinsp->inactivo();
            pcmv_fr->activo();
        }
        else if(elemento_seleccionado == 1){
            elemento_seleccionado = 4;
            pcmv_oxi->inactivo();
            pcmv_tinsp->activo();
        }
        else if(elemento_seleccionado == 2){
            elemento_seleccionado = 4;
            pcmv_peep->inactivo();
            pcmv_tinsp->activo();
        }
        else if(elemento_seleccionado == 3){
            elemento_seleccionado = 5;
            pcmv_fr->inactivo();
            estado_switch(true);
        }
        else if(elemento_seleccionado == 4){
            elemento_seleccionado = 6;
            pcmv_tinsp->inactivo();
            trigger_activo();
        }
        else if(elemento_seleccionado == 5){
            elemento_seleccionado = 7;
            estado_switch(false);
            boton_activado();
        }
        else if(elemento_seleccionado == 6){
            elemento_seleccionado = 7;
            trigger_inactivo();
            boton_activado();
        }
        else if(elemento_seleccionado == 7){
            elemento_seleccionado = 1;
            boton_inactivado();
            pcmv_oxi->activo();
        }
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

int UiModoPCMV::mover_arriba(){
    try {
        if(elemento_seleccionado == 0){
            elemento_seleccionado = -1;
            pcmv_pinsp->inactivo();
        }
        else if(elemento_seleccionado == 1){
            elemento_seleccionado = 0;
            pcmv_oxi->inactivo();
            pcmv_pinsp->activo();
        }
        else if(elemento_seleccionado == 2){
            elemento_seleccionado = 1;
            pcmv_peep->inactivo();
            pcmv_oxi->activo();
        }
        else if(elemento_seleccionado == 3){
            elemento_seleccionado = -3;
            pcmv_fr->inactivo();
        }
        else if(elemento_seleccionado == 4){
            elemento_seleccionado = 3;
            pcmv_tinsp->inactivo();
            pcmv_fr->activo();
        }
        else if(elemento_seleccionado == 5){
            elemento_seleccionado = -5;
            estado_switch(false);
        }
        else if(elemento_seleccionado == 6){
            elemento_seleccionado = 5;
            trigger_inactivo();
            estado_switch(true);
        }
        else if(elemento_seleccionado == 7){
            elemento_seleccionado = -6;
            boton_inactivado();
        }
        return elemento_seleccionado;
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return 0;
    }
}

int UiModoPCMV::mover_abajo(){
    try {
        if(elemento_seleccionado == 0){
            elemento_seleccionado = 1;
            pcmv_pinsp->inactivo();
            pcmv_oxi->activo();
        }
        else if(elemento_seleccionado == 1){
            elemento_seleccionado = 2;
            pcmv_oxi->inactivo();
            pcmv_peep->activo();
        }
        else if(elemento_seleccionado == 2){
            elemento_seleccionado = -1;
            pcmv_peep->inactivo();
        }
        else if(elemento_seleccionado == 3){
            elemento_seleccionado = 4;
            pcmv_fr->inactivo();
            pcmv_tinsp->activo();
        }
        else if(elemento_seleccionado == 4){
            elemento_seleccionado = -3;
            pcmv_tinsp->inactivo();
        }
        else if(elemento_seleccionado == 5){
            elemento_seleccionado = 6;
            estado_switch(false);
            trigger_activo();
        }
        else if(elemento_seleccionado == 6){
            elemento_seleccionado = -4;
            trigger_inactivo();
        }
        else if(elemento_seleccionado == 7){
            elemento_seleccionado = -6;
            boton_inactivado();
        }
        return elemento_seleccionado;
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return 0;
    }
}

void UiModoPCMV::sumar(){
    try {
        if(elemento_seleccionado == 0){
            if(obtener_max_peep_mas_pip()){
                pcmv_pinsp->sumar();
            }
        }
        else if(elemento_seleccionado == 1){
            pcmv_oxi->sumar();
        }
        else if(elemento_seleccionado == 2){
            if(obtener_max_peep_mas_pip()){
                pcmv_peep->sumar();
            }
        }
        else if(elemento_seleccionado == 3){
            pcmv_fr->sumar();
            recalcular_ti();
        }
        else if(elemento_seleccionado == 4){
            pcmv_tinsp->sumar();
        }
        else if(elemento_seleccionado == 6){
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

void UiModoPCMV::restar(){
    try {
        if(elemento_seleccionado == 0){
            pcmv_pinsp->restar();
        }
        else if(elemento_seleccionado == 1){
            pcmv_oxi->restar();
        }
        else if(elemento_seleccionado == 2){
            pcmv_peep->restar();
        }
        else if(elemento_seleccionado == 3){
            pcmv_fr->restar();
            recalcular_ti();
        }
        else if(elemento_seleccionado == 4){
            pcmv_tinsp->restar();
        }
        else if(elemento_seleccionado == 6){
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

void UiModoPCMV::switch_trigger(){
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

void UiModoPCMV::cambiaTipoTrigger(){
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

void UiModoPCMV::cambiaPerilla(){
    try {
        float peri = 0;
        if(elemento_seleccionado == 0){
            peri = pcmv_pinsp->cambiar_perilla();
        }
        else if(elemento_seleccionado == 1){
            peri = pcmv_oxi->cambiar_perilla();
        }
        else if(elemento_seleccionado == 2){
            peri = pcmv_peep->cambiar_perilla();
        }
        else if(elemento_seleccionado == 3){
            peri = pcmv_fr->cambiar_perilla();
        }
        else if(elemento_seleccionado == 4){
            peri = pcmv_tinsp->cambiar_perilla();
        }
        else if(elemento_seleccionado == 6){
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

void UiModoPCMV::cargar_valores(QStringList lista_valores){
    try {
        pcmv_pinsp->set_valor(lista_valores.at(1));
        pcmv_peep->set_valor(lista_valores.at(3));
        pcmv_fr->set_valor(lista_valores.at(4));
        pcmv_tinsp->set_valor(lista_valores.at(5));
        pcmv_oxi->set_valor(lista_valores.at(7));
        set_trigger(lista_valores.at(8));
        update_trigger();
        trigger_f->set_valor(lista_valores.at(9));
        trigger_p->set_valor(lista_valores.at(10));
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

QStringList UiModoPCMV::obtener_valores(){
    try {
        QStringList *param_list = new QStringList;
        param_list->append(QString::number(pcmv_pinsp->get_valor()));
        param_list->append("15");
        param_list->append(QString::number(pcmv_peep->get_valor()));
        param_list->append(QString::number(pcmv_fr->get_valor()));
        param_list->append(QString::number(pcmv_tinsp->get_valor()));
        param_list->append("0.2");
        param_list->append(QString::number(pcmv_oxi->get_valor()));
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

bool UiModoPCMV::obtener_max_peep_mas_pip(){
    try {
        if(pcmv_peep->get_valor() + pcmv_pinsp->get_valor() + 1 <= max_peep_mas_pip){
            return true;
        }
        else{
            return false;
        }
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return false;
    }
}

void UiModoPCMV::recalcular_ti(){
    try {
        float ti_max = (60.0/pcmv_fr->get_valor()) - min_te_min;
        pcmv_tinsp->set_lim_sup((QString::number(ti_max,'f',1).toFloat()));
        pcmv_tinsp->set_lim_inf(min_ti);
        if(pcmv_tinsp->get_valor() > ti_max){
            pcmv_tinsp->set_valor((QString::number(ti_max,'f',1)));
        }
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiModoPCMV::obtener_info_adicional(){
    try {
        float periodo = 60.0/pcmv_fr->get_valor();
        float ti = pcmv_tinsp->get_valor();
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
        float pf = pcmv_pinsp->get_valor() + pcmv_peep->get_valor();
        labelPF->setText("PF " + QString::number(pf,'f',1) + "cmH2O");
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiModoPCMV::mostrar_mensaje(QString mensaje){
    try {
        labelInfo->setText(mensaje);
        timerMensaje->start(5000);
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

void UiModoPCMV::outTimer(){
    try {
        labelInfo->setText("");
    } catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}
