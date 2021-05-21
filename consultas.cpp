#include "consultas.h"

Consultas::Consultas()
{
    try {
        conn_string = "ventilador2.db";
        conn = QSqlDatabase::addDatabase("QSQLITE");
        conn.setDatabaseName(conn_string);

        /*state = conn.open(); //conecta();
        if(!state){
            qDebug() << "[DB] Error al abrir" + conn_string.toLatin1();
        }
        else{
            qDebug() << "[DB] Conexion  con: " + conn_string.toLatin1();
        }*/
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );

    }
}

bool Consultas::conecta(){
    try {
        //return state;
        if(!conn.open()){
            qDebug() << "[DB] Error al abrir" + conn_string.toLatin1();
            return false;
        }
        else{
            //qDebug() << "[DB] Conexion  con: " + conn_string.toLatin1();
            return true;
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return false;
    }
}

void Consultas::cerrar(){
    try {
        conn.close();
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

/*int Consultas::consulta_count(QString){
    try {

    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}*/

QString Consultas::consulta(QString query){
    try {
        if(conecta()){
            QSqlDatabase::database().transaction();
            QSqlQuery consul;
            //qDebug() << "consulta query: " + query;
            consul.prepare(query);
            consul.exec();
            QSqlDatabase::database().commit();
            //crear
            QString salida = "result?";
            QStringList *lista_filas = new QStringList;
            //qDebug() << "consulta: " + QString::number(consul.boundValues().count());
            //if(consul.boundValues().count()){
                while(consul.next()){
                    //aqui estoy recorriendo filas
                    //convertir los valores de resultado en una QStringList
                    QSqlRecord record = consul.record();
                    QStringList tmp;
                    for(int i=0; i < record.count(); i++)
                    {
                        tmp.append(record.value(i).toString());
                    }
                    //convertir la QStringLsit en un QString
                    QString fila = tmp.join(",");
                    //Agregar  el QString a la QStringList lista_filas
                    lista_filas->append(fila);
                }
                QString filas = lista_filas->join("|");
                cerrar();
                return salida + filas;
            //}
            /*else{
                return "null";
            }*/
        }
        else{
            return "";
        }

    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

void Consultas::vaciar_tabla(QString query){
    try {
        if(conecta()){
            QSqlDatabase::database().transaction();
            QSqlQuery consul;
            consul.exec(query);
            QSqlDatabase::database().commit();
            cerrar();
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

bool Consultas::inserta_tabla(QString query){
    try {
        if(conecta()){
            QSqlDatabase::database().transaction();
            QSqlQuery consul;
            consul.exec(query);
            bool respuesta = QSqlDatabase::database().commit();
            cerrar();
            return respuesta;
        }
        else{
            return false;
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return false;
    }
}

QString Consultas::buscar_ult_config(QString nombreTabla){
    try {
        QString quer = "SELECT * FROM Config_Ultima_" + nombreTabla;
        QString resultados = consulta(quer);
        QStringList res_list = resultados.split("?");
        //qDebug() << "buscar_ult_config: " + QString::number(res_list.count());
        if(res_list.contains("result")){
            return res_list.at(1);
        }
        else{
            qDebug() << "buscar_ult_config vacia";
            return "";
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

QString Consultas::cargar_config_default(QString nombreTabla){
    try {
        QString quer = "SELECT * FROM Config_Default_" + nombreTabla;
        QString resultados = consulta(quer);
        QStringList res_list = resultados.split("?");
        if(res_list.contains("result")){
            return res_list.at(1);
        }
        else{
            return "";
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

QString Consultas::buscar_id_config_ultima_param(){
    try {
        QString quer = "SELECT id FROM Config_Ultima_Param";
        QString resultados = consulta(quer);
        QStringList res_list = resultados.split("?");
        if(res_list.contains("result")){
            return res_list.at(1);
        }
        else{
            return "";
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

QString Consultas::buscar_id_config_ultima(QString nombreTabla){
    try {
        QString quer = "SELECT id FROM Config_Ultima_" + nombreTabla;
        QString resultados = consulta(quer);
        QStringList res_list = resultados.split("?");
        if(res_list.contains("result")){
            return res_list.at(1);
        }
        else{
            return "";
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

void Consultas::reiniciar_valores(QString nombreTabla){
    try {
        QString quer = "DELETE FROM Config_Ultima_" + nombreTabla;
        vaciar_tabla(quer);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

bool Consultas::guardar_config_ultima_PCMV(QString pinsp, QString ipap, QString peep, QString fr, QString tinsp, QString tincr, QString oxigeno, QString mod_trigger, QString trigger_flujo, QString trigger_presion){
    try {
        QString id_config_ultima = buscar_id_config_ultima("PCMV");
        if(id_config_ultima != ""){
            QString update_query = "UPDATE Config_Ultima_PCMV SET pinsp = " + pinsp + ", ipap = " + ipap + ", peep = " +
                    peep + ", fr = " + fr + ", tinsp = " + tinsp + ", tincr = " + tincr + ", oxigeno = " +
                    oxigeno + ", mod_trigger = " + mod_trigger + ", trigger_flujo = " + trigger_flujo +
                    ", trigger_presion = " + trigger_presion + " WHERE id = " + id_config_ultima;
            QString resultados = consulta(update_query);
            if(resultados.at(1) != ""){
                return true;
            }
            else{
                qDebug("False guardar_config_ultima_PCMV");
                return false;
            }
        }
        else{
            QString query_insert = "INSERT INTO Config_Ultima_PCMV(pinsp, ipap, peep, fr, tinsp, tincr, oxigeno,"
                                   " mod_trigger, trigger_flujo, trigger_presion) VALUES(" + pinsp + "," + ipap + "," +
                                   peep + "," + fr + "," + tinsp + "," + tincr + "," + oxigeno + "," + mod_trigger + "," +
                                   trigger_flujo + "," + trigger_presion + ")";
            return inserta_tabla(query_insert);
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return false;
    }
}

bool Consultas::guardar_config_ultima_VCMV(QString vtinsp, QString peep, QString fr, QString tinsp, QString meseta, QString patron, QString oxigeno, QString mod_trigger, QString trigger_flujo, QString trigger_presion){
    try {
        QString id_config_ultima = buscar_id_config_ultima("VCMV");
        if(id_config_ultima != ""){
            QString update_query = "UPDATE Config_Ultima_VCMV SET vtinsp = " + vtinsp + ", peep = " + peep + ", fr = " +
                                   fr + ", tinsp = " + tinsp + ", meseta = " + meseta + ", patron = " + patron + ", oxigeno = " +
                                   oxigeno + ", mod_trigger = " + mod_trigger + ", trigger_flujo = " + trigger_flujo +
                                   ", trigger_presion = " + trigger_presion + " WHERE id = " + id_config_ultima;
            //qDebug() << "guardar_config_ultima_VCMV - query: " + update_query;
            QString resultados = consulta(update_query);
            //qDebug() << "guardar_config_ultima_VCMV - resultado: " + resultados;
            if(resultados.at(1) != ""){
                return true;
            }
            else{
                qDebug("False guardar_config_ultima_VCMV");
                return false;
            }
        }
        else{
            QString query_insert = "INSERT INTO Config_Ultima_VCMV(vtinsp, peep, fr, tinsp, meseta, patron, oxigeno,"
                                   " mod_trigger, trigger_flujo, trigger_presion) VALUES(" + vtinsp + "," + peep + "," +
                                   fr + "," + tinsp + "," + meseta + "," + patron + "," + oxigeno + "," + mod_trigger + "," +
                                   trigger_flujo + "," + trigger_presion + ")";
            return inserta_tabla(query_insert);
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return false;
    }
}

bool Consultas::guardar_config_ultima_VSIMV(QString vtinsp, QString psoporte, QString peep, QString fr, QString tinsp, QString tincr, QString meseta, QString ets, QString patron,QString oxigeno, QString mod_trigger, QString trigger_flujo, QString trigger_presion){
    try {
        QString id_config_ultima = buscar_id_config_ultima("VSIMV");
        if(id_config_ultima != ""){
            QString update_query = "UPDATE Config_Ultima_VSIMV SET vtinsp = " + vtinsp + ", psoporte = " + psoporte + ", peep = " + peep + ", fr = " +
                                    fr + ", tinsp = " + tinsp + ", tincr = " + tincr + ", meseta = " + meseta + ", ets = " + ets + ", patron = " + patron + ", oxigeno = " +
                                    oxigeno + ", mod_trigger = " + mod_trigger + ", trigger_flujo = " + trigger_flujo +
                                    ", trigger_presion = " + trigger_presion + " WHERE id = " + id_config_ultima;
            QString resultados = consulta(update_query);
            if(resultados.at(1) != ""){
                return true;
            }
            else{
                qDebug("False guardar_config_ultima_VSIMV");
                return false;
            }
        }
        else{
            QString query_insert = "INSERT INTO Config_Ultima_VSIMV(vtinsp, psoporte, peep, fr, tinsp, tincr, meseta, ets, patron, oxigeno,"
                                   " mod_trigger, trigger_flujo, trigger_presion) VALUES(" + vtinsp + "," + psoporte + "," + peep + "," +
                                   fr + "," + tinsp + "," + tincr + ","+ meseta + "," + ets + "," + patron + "," + oxigeno + "," + mod_trigger + "," +
                                   trigger_flujo + "," + trigger_presion + ")";
            return inserta_tabla(query_insert);
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return false;
    }
}

bool Consultas::guardar_config_ultima_PSIMV(QString pinsp, QString psoporte, QString peep, QString fr, QString tinsp, QString tincr, QString oxigeno, QString ets, QString mod_trigger, QString trigger_flujo, QString trigger_presion){
    try {
        QString id_config_ultima = buscar_id_config_ultima("PSIMV");
        if(id_config_ultima != ""){
            QString update_query = "UPDATE Config_Ultima_PSIMV SET pinsp = " + pinsp + ", psoporte = " + psoporte + ", peep = " + peep + ", fr = " +
                    fr + ", tinsp = " + tinsp + ", tincr = " + tincr + ", oxigeno = " + oxigeno + ", ets = " +
                    ets + ", mod_trigger = " + mod_trigger + ", trigger_flujo = " + trigger_flujo +
                    ", trigger_presion = " + trigger_presion + " WHERE id = " + id_config_ultima;
            QString resultados = consulta(update_query);
            if(resultados.at(1) != ""){
                return true;
            }
            else{
                qDebug("False guardar_config_ultima_PSIMV");
                return false;
            }
        }
        else{
            QString query_insert = "INSERT INTO Config_Ultima_PSIMV(pinsp, psoporte, peep, fr, tinsp, tincr, oxigeno, ets,"
                                   " mod_trigger, trigger_flujo, trigger_presion) VALUES(" + pinsp + "," + psoporte + "," + peep + "," +
                                   fr + "," + tinsp + "," + tincr + ","+ oxigeno + "," + ets + "," + mod_trigger + "," +
                                   trigger_flujo + "," + trigger_presion + ")";
            return inserta_tabla(query_insert);
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return false;
    }
}

bool Consultas::guardar_config_ultima_PCPAP(QString cpap, QString ps, QString oxigeno, QString apnea, QString mod_trigger, QString trigger_flujo, QString trigger_presion, QString frecuencia, QString pinsp, QString tinsp){
    try {
        QString id_config_ultima = buscar_id_config_ultima("PCPAP");
        if(id_config_ultima != ""){
            QString update_query = "UPDATE Config_Ultima_PCPAP SET cpap = " + cpap + ", ps = " + ps + ", oxigeno = " + oxigeno + ", apnea = " +
                                    apnea + ", mod_trigger = " + mod_trigger + ", trigger_flujo = " + trigger_flujo + ", trigger_presion = " +
                                    trigger_presion + ", frecuencia = " + frecuencia + ", pinsp = " + pinsp + ", tinsp = " + tinsp +
                                    " WHERE id = " + id_config_ultima;
            QString resultados = consulta(update_query);
            if(resultados.at(1) != ""){
                return true;
            }
            else{
                qDebug("False guardar_config_ultima_PCPAP");
                return false;
            }
        }
        else{
            QString query_insert = "INSERT INTO Config_Ultima_PCPAP(cpap, ps, oxigeno, apnea, mod_trigger, trigger_flujo, "
                                   "trigger_presion, frecuencia, pinsp, tinsp) VALUES(" + cpap + "," + ps + "," + oxigeno + "," +
                                   apnea + "," + mod_trigger + "," + trigger_flujo + "," + trigger_presion + "," + frecuencia + "," + pinsp + "," +
                                   tinsp + ")";
            return inserta_tabla(query_insert);
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return false;
    }
}

bool Consultas::guardar_config_ultima_VCPAP(QString cpap, QString ps, QString oxigeno, QString apnea, QString mod_trigger, QString trigger_flujo, QString trigger_presion, QString frecuencia, QString vtidal, QString flujo){
    try {
        QString id_config_ultima = buscar_id_config_ultima("VCPAP");
        if(id_config_ultima != ""){
            QString update_query = "UPDATE Config_Ultima_VCPAP SET cpap = " + cpap + ", ps = " + ps + ", oxigeno = " + oxigeno + ", apnea = " +
                                    apnea + ", mod_trigger = " + mod_trigger + ", trigger_flujo = " + trigger_flujo + ", trigger_presion = " +
                                    trigger_presion + ", frecuencia = " + frecuencia + ", vtidal = " + vtidal + ", flujo = " + flujo +
                                    " WHERE id = " + id_config_ultima;
            QString resultados = consulta(update_query);
            if(resultados.at(1) != ""){
                return true;
            }
            else{
                qDebug("False guardar_config_ultima_VCPAP");
                return false;
            }
        }
        else{
            QString query_insert = "INSERT INTO Config_Ultima_VCPAP(cpap, ps, oxigeno, apnea, mod_trigger, trigger_flujo, "
                                   "trigger_presion, frecuencia, vtidal, flujo) VALUES(" + cpap + "," + ps + "," + oxigeno + "," +
                                   apnea + "," + mod_trigger + "," + trigger_flujo + "," + trigger_presion + "," + frecuencia + "," + vtidal + "," +
                                   flujo + ")";
            return inserta_tabla(query_insert);
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return false;
    }
}

QString Consultas::cargar_config_default_alarm(){
    try {
        QString quer = "SELECT * FROM Config_Default_Alarm";
        QString resultados = consulta(quer);
        QStringList res_list = resultados.split("?");
        if(res_list.contains("result")){
            return res_list.at(1);
        }
        else{
            return "";
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

QString Consultas::buscar_id_config_ultima_alarm(){
    try {
        QString quer = "SELECT id FROM Config_Ultima_Alarm";
        QString resultados = consulta(quer);
        QStringList res_list = resultados.split("?");
        if(res_list.contains("result")){
            return res_list.at(1);
        }
        else{
            return "";
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

QString Consultas::buscar_ult_config_alarm(){
    try {
        QString quer = "SELECT * FROM Config_Ultima_Alarm";
        QString resultados = consulta(quer);
        QStringList res_list = resultados.split("?");
        if(res_list.contains("result")){
            return res_list.at(1);
        }
        else{
            return "";
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

bool Consultas::guardar_config_ultima_alarm(QString pre_max, QString pre_min, QString volm_max, QString volm_min, QString fre_max, QString fre_min, QString vole_max, QString vole_min, QString edo_apre, QString edo_avolm, QString edo_afre, QString edo_avole, QString t_apnea){
    try {
        QString id_config_ultima = buscar_id_config_ultima_alarm();
        if(id_config_ultima != ""){
            QString update_query = "UPDATE Config_Ultima_Alarm SET pre_max = "+pre_max+" , pre_min = "+pre_min +" , volm_max = " +
                                    volm_max +" , volm_min = "+ volm_min+ " , fre_max = " +fre_max+ " , fre_min = "+
                                    fre_min+ " , vole_max = "+ vole_max + " , vole_min = "+vole_min+ " , edo_apre = "+
                                    edo_apre+ " , edo_avolm = "+edo_avolm+ " , edo_afre = "+ edo_avolm + " , edo_afre = "+
                                    edo_afre+ " , edo_avole = "+edo_avole+ " , t_apnea = "+t_apnea+ " WHERE id = "+id_config_ultima;
            //qDebug() << "guardar_config_ultima_alarm-update_query: " + update_query;
            QString resultados = consulta(update_query);
            //qDebug() << "guardar_config_ultima_alarm-resultados: " + resultados;
            if(resultados.at(1) != ""){
                return true;
            }
            else{
                qDebug("False guardar_config_ultima_alarm");
                return false;
            }
        }
        else{
            QString query_insert = "INSERT INTO Config_Ultima_Alarm(pre_max, pre_min, volm_max, volm_min, fre_max, fre_min, "
                                "vole_max, vole_min, edo_apre, edo_avolm, edo_afre, edo_avole, t_apnea) VALUES ("+pre_max+" , " +
                                pre_min+" , "+volm_max+ " , "+ volm_min+ " , "+fre_max+ " , "+
                                fre_min+" , "+ vole_max+ " , "+ vole_min+ " , "+ edo_apre+ " , " +
                                edo_avolm+ " , "+edo_afre + " , "+ edo_avole+ " , "+ t_apnea+ " ) ";
            return inserta_tabla(query_insert);
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return false;
    }
}

QString Consultas::leer_modo(){
    try {
        QString quer = "SELECT * FROM Modo_Config";
        QString resultados = consulta(quer);
        QStringList res_list = resultados.split("?");
        if(res_list.contains("result")){
            return res_list.at(1);
        }
        else{
            return "";
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

QString Consultas::obtener_id_modo(){
    try {
        QString quer = "SELECT id FROM Modo_Config";
        QString resultados = consulta(quer);
        QStringList res_list = resultados.split("?");
        if(res_list.contains("result")){
            return res_list.at(1);
        }
        else{
            return "";
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

bool Consultas::actualizar_modo(int modo){
    try {
        QString id_modo = obtener_id_modo();
        if(id_modo != ""){
            QString update_query = "UPDATE Modo_Config SET modo = " + QString::number(modo) + " WHERE id = " + id_modo;
            QString resultados = consulta(update_query);
            if(resultados.at(1) != ""){
                return true;
            }
            else{
                qDebug("False actualizar_modo");
                return false;
            }
        }
        else{
            return false;
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return false;
    }
}

QString Consultas::obtener_id_giro(){
    try {
        QString quer = "SELECT id FROM Modo_Giro";
        QString resultados = consulta(quer);
        QStringList res_list = resultados.split("?");
        if(res_list.contains("result")){
            return res_list.at(1);
        }
        else{
            return "";
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

QString Consultas::leer_sentido_giro(){
    try {
        QString quer = "SELECT * FROM Modo_Giro";
        QString resultados = consulta(quer);
        QStringList res_list = resultados.split("?");
        if(res_list.contains("result")){
            return res_list.at(1);
        }
        else{
            return "";
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

bool Consultas::cambiar_sentido_giro(QString sentido){
    try {
        QString id_giro = obtener_id_giro();
        if(id_giro != ""){
            QString update_query = "UPDATE Modo_Giro SET sentido = " + sentido + " WHERE id = " + id_giro;
            QString resultados = consulta(update_query);
            if(resultados.at(1) != ""){
                return true;
            }
            else{
                qDebug("False cambiar_sentido_giro");
                return false;
            }
        }
        else{
            return false;
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return false;
    }
}

QString Consultas::obtener_id_tipo_sensor(){
    try {
        QString quer = "SELECT id FROM Tipo_Sensor";
        QString resultados = consulta(quer);
        QStringList res_list = resultados.split("?");
        if(res_list.contains("result")){
            return res_list.at(1);
        }
        else{
            return "";
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

QString Consultas::leer_tipo_sensor(){
    try {
        QString quer = "SELECT * FROM Tipo_Sensor";
        QString resultados = consulta(quer);
        QStringList res_list = resultados.split("?");
        if(res_list.contains("result")){
            return res_list.at(1);
        }
        else{
            return "";
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

bool Consultas::cambiar_tipo_sensor(QString sentido){
    try {
        QString id_giro = obtener_id_tipo_sensor();
        if(id_giro != ""){
            QString update_query = "UPDATE Tipo_Sensor SET tipo = " + sentido + " WHERE id = " + id_giro;
            qDebug() << "query - cambiar_tipo_sensor " + update_query;
            QString resultados = consulta(update_query);
            if(resultados.at(1) != ""){
                return true;
            }
            else{
                qDebug("False cambiar_tipo_sensor");
                return false;
            }
        }
        else{
            return false;
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return false;
    }
}

QString Consultas::obtener_id_calibracion(){
    try {
        QString quer = "SELECT id FROM Calibracion";
        QString resultados = consulta(quer);
        QStringList res_list = resultados.split("?");
        if(res_list.contains("result")){
            return res_list.at(1);
        }
        else{
            return "";
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

QString Consultas::leer_calibracion(){
    try {
        QString quer = "SELECT * FROM Calibracion";
        QString resultados = consulta(quer);
        QStringList res_list = resultados.split("?");
        if(res_list.contains("result")){
            return res_list.at(1);
        }
        else{
            return "";
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

bool Consultas::guarda_cali(QString b1, QString b2, QString b3, QString b4, QString b5, QString b6, QString b7, QString b8){
    try {
        QString id_cali = obtener_id_calibracion();
        if(id_cali != ""){
            QString update_query = "UPDATE Calibracion SET f1 = " + b1 + ", f2 = " + b2 + ", f3 = " + b3 +
                    ", f4 = " + b4 + ", f5 = " + b5 + ", f6 = " + b6 + ", f7 = " + b7 + ", f8 = " + b8 + " WHERE id = " + id_cali;
            QString resultados = consulta(update_query);
            if(resultados.at(1) != ""){
                return true;
            }
            else{
                qDebug("False guarda_cali");
                return false;
            }
        }
        else{
            return false;
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return false;
    }
}

QString Consultas::obtener_id_offsets(){
    try {
        QString quer = "SELECT id FROM Offsets";
        QString resultados = consulta(quer);
        QStringList res_list = resultados.split("?");
        if(res_list.contains("result")){
            return res_list.at(1);
        }
        else{
            return "";
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

QString Consultas::leer_offsets(){
    try {
        QString quer = "SELECT * FROM Offsets";
        QString resultados = consulta(quer);
        QStringList res_list = resultados.split("?");
        if(res_list.contains("result")){
            return res_list.at(1);
        }
        else{
            return "";
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

bool Consultas::guarda_offsets(QString b1, QString b2, QString b3, QString b4, QString b5, QString b6, QString b7, QString b8){
    try {
        QString id_cali = obtener_id_offsets();
        if(id_cali != ""){
            QString update_query = "UPDATE Offsets SET of_peep = " + b1 + ", of_pip = " + b2 + ", of_cpeep = " + b3 +
                                    ", of_cpip = " + b4 + ", of_pre = " + b5 + ", of_bat = " + b6 + ", g_bat = " + b7 +  ", valvula = " + b8 +" WHERE id = " + id_cali;
            QString resultados = consulta(update_query);
            if(resultados.at(1) != ""){
                return true;
            }
            else{
                qDebug("False guarda_cali");
                return false;
            }
        }
        else{
            return false;
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return false;
    }
}

QString Consultas::obtener_id_altura(){
    try {
        QString quer = "SELECT id FROM Altura";
        QString resultados = consulta(quer);
        QStringList res_list = resultados.split("?");
        if(res_list.contains("result")){
            return res_list.at(1);
        }
        else{
            return "";
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

QString Consultas::leer_altura(){
    try {
        QString quer = "SELECT * FROM Altura";
        QString resultados = consulta(quer);
        QStringList res_list = resultados.split("?");
        if(res_list.contains("result")){
            return res_list.at(1);
        }
        else{
            return "";
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

bool Consultas::guarda_altura(QString b1){
    try {
        QString id_cali = obtener_id_altura();
        if(id_cali != ""){
            QString update_query = "UPDATE Altura SET altura = " + b1 + " WHERE id = " + id_cali;
            QString resultados = consulta(update_query);
            if(resultados.at(1) != ""){
                return true;
            }
            else{
                qDebug("False guarda_cali");
                return false;
            }
        }
        else{
            return false;
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return false;
    }
}

bool Consultas::guarda_cali_flujo(QString flujo){
    try {
        QString id_cali = obtener_id_calibracion();
        if(id_cali != ""){
            QString update_query = "UPDATE Calibracion SET flujo = " + flujo + " WHERE id = " + id_cali;
            QString resultados = consulta(update_query);
            if(resultados.at(1) != ""){
                return true;
            }
            else{
                qDebug("False guarda_cali");
                return false;
            }
        }
        else{
            return false;
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return false;
    }
}

bool Consultas::guarda_cali_presion(QString presion){
    try {
        QString id_cali = obtener_id_calibracion();
        if(id_cali != ""){
            QString update_query = "UPDATE Calibracion SET presion = " + presion + " WHERE id = " + id_cali;
            QString resultados = consulta(update_query);
            if(resultados.at(1) != ""){
                return true;
            }
            else{
                qDebug("False guarda_cali");
                return false;
            }
        }
        else{
            return false;
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return false;
    }
}

QStringList Consultas::obtener_eventos(){
    try {
        if(conecta()){
            QString quer = "SELECT tipo, modo, descripcion, fecha, hora FROM eventos ORDER BY date(fecha), date(hora) DESC";
            QSqlDatabase::database().transaction();
            QSqlQuery consul;
            consul.prepare(quer);
            consul.exec();
            QSqlDatabase::database().commit();
            //
            QString salida = "result?";
            QStringList *lista_filas = new QStringList;
            //if(consul.boundValues().count()){
                while(consul.next()){
                    //aqui estoy recorriendo filas
                    //convertir los valores de resultado en una QStringList
                    QSqlRecord record = consul.record();
                    QStringList tmp;
                    for(int i=0; i < record.count(); i++)
                    {
                        tmp.append(record.value(i).toString());
                    }
                    //convertir la QStringLsit en un QString
                    QString fila = tmp.join(",");
                    //Agregar  el QString a la QStringList lista_filas
                    lista_filas->append(fila);
                }
            //}
            cerrar();
            return *lista_filas;
        }
        else{
            QStringList *lista_filas = new QStringList;
            return *lista_filas;
        }

    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        QStringList *lista_filas = new QStringList;
        return *lista_filas;
    }
}

QStringList Consultas::obtener_eventos_para_borrar(){
    try {
        if(conecta()){
            QString quer = "SELECT id, fecha FROM eventos";
            QSqlDatabase::database().transaction();
            QSqlQuery consul;
            consul.prepare(quer);
            consul.exec();
            QSqlDatabase::database().commit();
            //
            QString salida = "result?";
            QStringList *lista_filas = new QStringList;
            //if(consul.boundValues().count()){
                while(consul.next()){
                    //aqui estoy recorriendo filas
                    //convertir los valores de resultado en una QStringList
                    QSqlRecord record = consul.record();
                    QStringList tmp;
                    //qDebug() << "obtener_eventos_para_borrar, record.count: " + QString::number(record.count());
                    for(int i=0; i < record.count(); i++)
                    {
                        tmp.append(record.value(i).toString());
                    }
                    //convertir la QStringLsit en un QString
                    QString fila = tmp.join(",");
                    //Agregar  el QString a la QStringList lista_filas
                    lista_filas->append(fila);
                }
            //}
            cerrar();
            return *lista_filas;

        }
        else{
            QStringList *lista_filas = new QStringList;
            return *lista_filas;
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        QStringList *lista_filas = new QStringList;
        return *lista_filas;
    }
}

bool Consultas::borrar_evento(QString id){
    try {
        QString update_query = "DELETE FROM eventos WHERE ID = " + id;
        QString resultados = consulta(update_query);
        if(resultados.at(1) != ""){
            return true;
        }
        else{
            qDebug("False actualizar_modo");
            return false;
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return false;
    }
}

bool Consultas::agregar_evento(QString tipo, QString modo, QString descripcion){
    try {
        QString query_insert = "INSERT INTO eventos(tipo, modo, descripcion, fecha, hora) VALUES ('"+ tipo +"' , '" + modo +"' , '" +
                                descripcion +"' ,date('now'),time('now', 'localtime'))";
        return inserta_tabla(query_insert);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return false;
    }
}

QString Consultas::numero_serie(){
    try {
        QString quer = "SELECT numero_serie FROM NumSerie WHERE id = 1";
        QString resultados = consulta(quer);
        QStringList res_list = resultados.split("?");
        if(res_list.contains("result")){
            return res_list.at(1);
        }
        else{
            return "";
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

QString Consultas::leer_teclado(){
    try {
        QString quer = "SELECT * FROM teclado";
        QString resultados = consulta(quer);
        QStringList res_list = resultados.split("?");
        if(res_list.contains("result")){
            return res_list.at(1);
        }
        else{
            return "";
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

bool Consultas::guarda_teclado(QString pres, QString solt){
    try {
        QString id_cali = obtener_id_teclado();
        if(id_cali != ""){
            QString update_query = "UPDATE teclado SET presionar = " + pres + ", soltar = " + solt + " WHERE id = " + id_cali;
            QString resultados = consulta(update_query);
            if(resultados.at(1) != ""){
                return true;
            }
            else{
                qDebug("False guarda_cali");
                return false;
            }
        }
        else{
            return false;
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return false;
    }
}

QString Consultas::obtener_id_teclado(){
    try {
        QString quer = "SELECT id FROM teclado";
        QString resultados = consulta(quer);
        QStringList res_list = resultados.split("?");
        if(res_list.contains("result")){
            return res_list.at(1);
        }
        else{
            return "";
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

QString Consultas::leer_fio2(){
    try {
        QString quer = "SELECT * FROM fio2";
        QString resultados = consulta(quer);
        QStringList res_list = resultados.split("?");
        if(res_list.contains("result")){
            return res_list.at(1);
        }
        else{
            return "";
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

bool Consultas::guarda_fio2(QString porce_cambio, QString ls_aire, QString li_aire, QString ls_o2, QString li_o2){
    try {
        QString id_fio2 = obtener_id_fio2();
        //qDebug() << "id fio2: " + id_fio2;
        if(id_fio2 != ""){
            QString update_query = "UPDATE fio2 SET porce_cambio = " + porce_cambio + ", ls_aire = " + ls_aire +  ", li_aire = " + li_aire + ", ls_o2 = " + ls_o2 + ", li_o2 = " + li_o2 + " WHERE id = " + id_fio2;
            //qDebug() << "query fio2: " + update_query;
            QString resultados = consulta(update_query);
            if(resultados.at(1) != ""){
                return true;
            }
            else{
                qDebug("False guarda_fio2");
                return false;
            }
        }
        else{
            return false;
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return false;
    }
}

QString Consultas::obtener_id_fio2(){
    try {
        QString quer = "SELECT id FROM fio2";
        QString resultados = consulta(quer);
        QStringList res_list = resultados.split("?");
        if(res_list.contains("result")){
            return res_list.at(1);
        }
        else{
            return "";
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

QString Consultas::obtener_id_com_pip(){
    try {
        QString quer = "SELECT id FROM com_pip";
        QString resultados = consulta(quer);
        QStringList res_list = resultados.split("?");
        if(res_list.contains("result")){
            return res_list.at(1);
        }
        else{
            return "";
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

QString Consultas::leer_com_pip(){
    try {
        QString quer = "SELECT * FROM com_pip";
        QString resultados = consulta(quer);
        QStringList res_list = resultados.split("?");
        if(res_list.contains("result")){
            return res_list.at(1);
        }
        else{
            return "";
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

bool Consultas::guarda_com_pip(QString b1){
    try {
        QString id_com_pip = obtener_id_com_pip();
        if(id_com_pip != ""){
            QString update_query = "UPDATE com_pip SET compensacion = " + b1 + " WHERE id = " + id_com_pip;
            QString resultados = consulta(update_query);
            if(resultados.at(1) != ""){
                return true;
            }
            else{
                qDebug("False guarda_com_pip");
                return false;
            }
        }
        else{
            return false;
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return false;
    }
}
