#include "consultasdb.h"

ConsultasDb::ConsultasDb(QSettings *config)
{
    int port = config->value("database/port", "5432").toString().toInt();
    QString name_db = config->value("database/name", "ventiladordb").toString();
    QString user_db = config->value("database/user", "pi").toString();
    QString pass_db = config->value("database/pass", "123456789").toString();
    QString numserie = config->value("database/numserie", "740000/20").toString();

    //prueba para obtener desde aqui el md5
    qDebug() << "[DB POS] port: " << port;
    qDebug() << "[DB POS] name_db: " << name_db;
    qDebug() << "[DB POS] user_db: " << user_db;
    qDebug() << "[DB POS] pass_db: " << pass_db;
    qDebug() << "[DB POS] numserie: " << numserie;

    //macadres
    //foreach(QNetworkInterface interface, QNetworkInterface::allInterfaces())
    //{
    //    qDebug() << "[DB POS] Interface:"+interface.hardwareAddress();
    //}

    //hacer todo por comandos linux!

    //QString mac = "dc:a6:32:5b:4a:58";
    //QString trama = "*" + mac + "&" + numserie + "?";
    //QString md5 = QString(QCryptographicHash::hash((trama.toUtf8()),QCryptographicHash::Md5));

    //qDebug() << "[DB POS] MD5: " << md5;

    baseDatos = QSqlDatabase::addDatabase("QPSQL");
    baseDatos.setHostName("localhost");
    baseDatos.setPort(port);
    baseDatos.setDatabaseName(name_db);
    baseDatos.setUserName(user_db);
    baseDatos.setPassword(pass_db); //320b5784b0ee
    if(!baseDatos.open())
    {
        qDebug()<<"[DB] Error en la conexion de la base de datos postgres";
    }
    else
    {
        qDebug()<<"[DB] Conexion con la base de datos realizada postgres";
    }
}

ConsultasDb::~ConsultasDb()
{
    baseDatos.close();
}

QString ConsultasDb::consulta(QString query){
    //1 checar que esté conectada la db
    if(baseDatos.isOpen()){
        //2 preparar la consulta
        baseDatos.transaction();
        QSqlQuery consul;
        consul.prepare(query + ";");
        //qDebug() << "query consulta: " << query + ";";
        //3 ejecutar la consulta
        bool resultado = consul.exec();
        //3.1 revisar que no haya error, en caso de que si, hacer rollback
        if(consul.lastError().type() != QSqlError::NoError || !resultado){
            qDebug() << "[DB] consulta Error: " << consul.lastError(); //.text();
            baseDatos.rollback();
            return "";
        }
        //4 obtener los resultados de la consulta
        baseDatos.commit();
        QString salida = "result?";
        QStringList *lista_filas = new QStringList;
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
        //acomodar el resultado como más convenga, en este caso, en QString
        QString filas = lista_filas->join("|");
        return salida + filas;
    }
    else{
        return "";
    }
}

void ConsultasDb::vaciar_tabla(QString query){
    try {
        if(baseDatos.isOpen()){
            baseDatos.transaction();
            QSqlQuery consul;
            consul.prepare(query);
            bool resultado = consul.exec();
            if (consul.lastError().type() != QSqlError::NoError || !resultado)
            {
                qDebug() << "[DB] vaciar_tabla Error: " << consul.lastError(); //.text();
                baseDatos.rollback();
            }
            baseDatos.commit();
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

bool ConsultasDb::inserta_tabla(QString query){
    try {
        if(baseDatos.isOpen()){
            //qDebug() << "[DB] inserta tabla query: " << query;
            baseDatos.transaction();
            QSqlQuery consul;
            consul.prepare(query);
            bool resultado = consul.exec();
            if (consul.lastError().type() != QSqlError::NoError || !resultado)
            {
                qDebug() << "[DB] inserta_tabla Error: " << consul.lastError(); //.text();
                baseDatos.rollback();
            }
            baseDatos.commit();
            return resultado;
        }
        else{
            return false;
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return false;
    }
}

QString ConsultasDb::buscar_ult_config(QString nombreTabla){
    try {
        QString quer = "SELECT * FROM public.\"Config_Ultima_" + nombreTabla + "\"";
        QString resultados = consulta(quer);
        QStringList res_list = resultados.split("?");
        //qDebug() << "buscar_ult_config: " + QString::number(res_list.count());
        if(res_list.contains("result")){
            return res_list.at(1);
        }
        else{
            //qDebug() << "[DB] buscar_ult_config vacia";
            return "";
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return "";
    }
}

QString ConsultasDb::cargar_config_default(QString nombreTabla){
    try {
        QString quer = "SELECT * FROM public.\"Config_Default_" + nombreTabla + "\"";
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

QString ConsultasDb::buscar_id_config_ultima_param(){
    try {
        QString quer = "SELECT id FROM public.\"Config_Ultima_Param\"";
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

QString ConsultasDb::buscar_id_config_ultima(QString nombreTabla){
    try {
        QString quer = "SELECT id FROM public.\"Config_Ultima_" + nombreTabla + "\"";
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

void ConsultasDb::reiniciar_valores(QString nombreTabla){
    try {
        QString quer = "DELETE FROM public.\"Config_Ultima_" + nombreTabla + "\"";
        vaciar_tabla(quer);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
    }
}

bool ConsultasDb::guardar_config_ultima_PCMV(QString pinsp, QString ipap, QString peep, QString fr, QString tinsp, QString tincr, QString oxigeno, QString mod_trigger, QString trigger_flujo, QString trigger_presion){
    try {
        QString id_config_ultima = buscar_id_config_ultima("PCMV");
        if(id_config_ultima != ""){
            QString update_query = "UPDATE public.\"Config_Ultima_PCMV\" SET pinsp = " + pinsp + ", ipap = " + ipap + ", peep = " +
                    peep + ", fr = " + fr + ", tinsp = " + tinsp + ", tincr = " + tincr + ", oxigeno = " +
                    oxigeno + ", mod_trigger = " + mod_trigger + ", trigger_flujo = " + trigger_flujo +
                    ", trigger_presion = " + trigger_presion + " WHERE id = " + id_config_ultima;
            QString resultados = consulta(update_query);
            if(resultados.at(1) != ""){
                return true;
            }
            else{
                qDebug("[DB] False guardar_config_ultima_PCMV");
                return false;
            }
        }
        else{
            QString query_insert = "INSERT INTO public.\"Config_Ultima_PCMV \"(pinsp, ipap, peep, fr, tinsp, tincr, oxigeno,"
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

bool ConsultasDb::guardar_config_ultima_VCMV(QString vtinsp, QString peep, QString fr, QString tinsp, QString meseta, QString patron, QString oxigeno, QString mod_trigger, QString trigger_flujo, QString trigger_presion){
    try {
        QString id_config_ultima = buscar_id_config_ultima("VCMV");
        if(id_config_ultima != ""){
            QString update_query = "UPDATE public.\"Config_Ultima_VCMV\" SET vtinsp = " + vtinsp + ", peep = " + peep + ", fr = " +
                                   fr + ", tinsp = " + tinsp + ", meseta = " + meseta + ", patron = " + patron + ", oxigeno = " +
                                   oxigeno + ", mod_trigger = " + mod_trigger + ", trigger_flujo = " + trigger_flujo +
                                   ", trigger_presion = " + trigger_presion + " WHERE id = " + id_config_ultima;
            //qDebug() << "guardar_config_ultima_VCMV - query: " + update_query;
            QString resultados = consulta(update_query);
            qDebug() << "[DB] guardar_config_ultima_VCMV - resultado: " + resultados;
            if(resultados.at(1) != ""){
                return true;
            }
            else{
                //qDebug("False guardar_config_ultima_VCMV");
                return false;
            }
        }
        else{
            QString query_insert = "INSERT INTO public.\"Config_Ultima_VCMV\"(vtinsp, peep, fr, tinsp, meseta, patron, oxigeno,"
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

bool ConsultasDb::guardar_config_ultima_VSIMV(QString vtinsp, QString psoporte, QString peep, QString fr, QString tinsp, QString tincr, QString meseta, QString ets, QString patron,QString oxigeno, QString mod_trigger, QString trigger_flujo, QString trigger_presion){
    try {
        QString id_config_ultima = buscar_id_config_ultima("VSIMV");
        if(id_config_ultima != ""){
            QString update_query = "UPDATE public.\"Config_Ultima_VSIMV\" SET vtinsp = " + vtinsp + ", psoporte = " + psoporte + ", peep = " + peep + ", fr = " +
                                    fr + ", tinsp = " + tinsp + ", tincr = " + tincr + ", meseta = " + meseta + ", ets = " + ets + ", patron = " + patron + ", oxigeno = " +
                                    oxigeno + ", mod_trigger = " + mod_trigger + ", trigger_flujo = " + trigger_flujo +
                                    ", trigger_presion = " + trigger_presion + " WHERE id = " + id_config_ultima;
            QString resultados = consulta(update_query);
            if(resultados.at(1) != ""){
                return true;
            }
            else{
                qDebug("[DB] False guardar_config_ultima_VSIMV");
                return false;
            }
        }
        else{
            QString query_insert = "INSERT INTO public.\"Config_Ultima_VSIMV\"(vtinsp, psoporte, peep, fr, tinsp, tincr, meseta, ets, patron, oxigeno,"
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

bool ConsultasDb::guardar_config_ultima_PSIMV(QString pinsp, QString psoporte, QString peep, QString fr, QString tinsp, QString tincr, QString oxigeno, QString ets, QString mod_trigger, QString trigger_flujo, QString trigger_presion){
    try {
        QString id_config_ultima = buscar_id_config_ultima("PSIMV");
        if(id_config_ultima != ""){
            QString update_query = "UPDATE public.\"Config_Ultima_PSIMV\" SET pinsp = " + pinsp + ", psoporte = " + psoporte + ", peep = " + peep + ", fr = " +
                    fr + ", tinsp = " + tinsp + ", tincr = " + tincr + ", oxigeno = " + oxigeno + ", ets = " +
                    ets + ", mod_trigger = " + mod_trigger + ", trigger_flujo = " + trigger_flujo +
                    ", trigger_presion = " + trigger_presion + " WHERE id = " + id_config_ultima;
            QString resultados = consulta(update_query);
            if(resultados.at(1) != ""){
                return true;
            }
            else{
                qDebug("[DB] False guardar_config_ultima_PSIMV");
                return false;
            }
        }
        else{
            QString query_insert = "INSERT INTO public.\"Config_Ultima_PSIMV\"(pinsp, psoporte, peep, fr, tinsp, tincr, oxigeno, ets,"
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

bool ConsultasDb::guardar_config_ultima_PCPAP(QString cpap, QString ps, QString oxigeno, QString apnea, QString mod_trigger, QString trigger_flujo, QString trigger_presion, QString frecuencia, QString pinsp, QString tinsp){
    try {
        QString id_config_ultima = buscar_id_config_ultima("PCPAP");
        if(id_config_ultima != ""){
            QString update_query = "UPDATE public.\"Config_Ultima_PCPAP\" SET cpap = " + cpap + ", ps = " + ps + ", oxigeno = " + oxigeno + ", apnea = " +
                                    apnea + ", mod_trigger = " + mod_trigger + ", trigger_flujo = " + trigger_flujo + ", trigger_presion = " +
                                    trigger_presion + ", frecuencia = " + frecuencia + ", pinsp = " + pinsp + ", tinsp = " + tinsp +
                                    " WHERE id = " + id_config_ultima;
            QString resultados = consulta(update_query);
            if(resultados.at(1) != ""){
                return true;
            }
            else{
                qDebug("[DB] False guardar_config_ultima_PCPAP");
                return false;
            }
        }
        else{
            QString query_insert = "INSERT INTO public.\"Config_Ultima_PCPAP\"(cpap, ps, oxigeno, apnea, mod_trigger, trigger_flujo, "
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

bool ConsultasDb::guardar_config_ultima_VCPAP(QString cpap, QString ps, QString oxigeno, QString apnea, QString mod_trigger, QString trigger_flujo, QString trigger_presion, QString frecuencia, QString vtidal, QString flujo){
    try {
        QString id_config_ultima = buscar_id_config_ultima("VCPAP");
        if(id_config_ultima != ""){
            QString update_query = "UPDATE public.\"Config_Ultima_VCPAP\" SET cpap = " + cpap + ", ps = " + ps + ", oxigeno = " + oxigeno + ", apnea = " +
                                    apnea + ", mod_trigger = " + mod_trigger + ", trigger_flujo = " + trigger_flujo + ", trigger_presion = " +
                                    trigger_presion + ", frecuencia = " + frecuencia + ", vtidal = " + vtidal + ", flujo = " + flujo +
                                    " WHERE id = " + id_config_ultima;
            QString resultados = consulta(update_query);
            if(resultados.at(1) != ""){
                return true;
            }
            else{
                qDebug("[DB] False guardar_config_ultima_VCPAP");
                return false;
            }
        }
        else{
            QString query_insert = "INSERT INTO public.\"Config_Ultima_VCPAP\"(cpap, ps, oxigeno, apnea, mod_trigger, trigger_flujo, "
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

QString ConsultasDb::cargar_config_default_alarm(){
    try {
        QString quer = "SELECT * FROM public.\"Config_Default_Alarm\"";
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

QString ConsultasDb::buscar_id_config_ultima_alarm(){
    try {
        QString quer = "SELECT id FROM public.\"Config_Ultima_Alarm\"";
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

QString ConsultasDb::buscar_ult_config_alarm(){
    try {
        QString quer = "SELECT * FROM public.\"Config_Ultima_Alarm\"";
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

bool ConsultasDb::guardar_config_ultima_alarm(QString pre_max, QString pre_min, QString volm_max, QString volm_min, QString fre_max, QString fre_min, QString vole_max, QString vole_min, QString edo_apre, QString edo_avolm, QString edo_afre, QString edo_avole, QString t_apnea){
    try {
        QString id_config_ultima = buscar_id_config_ultima_alarm();
        if(id_config_ultima != ""){
            QString update_query = "UPDATE public.\"Config_Ultima_Alarm\" SET pre_max = "+pre_max+" , pre_min = "+pre_min +" , volm_max = " +
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
                qDebug("[DB] False guardar_config_ultima_alarm");
                return false;
            }
        }
        else{
            QString query_insert = "INSERT INTO public.\"Config_Ultima_Alarm\"(pre_max, pre_min, volm_max, volm_min, fre_max, fre_min, "
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

QString ConsultasDb::leer_modo(){
    try {
        QString quer = "SELECT * FROM public.\"Modo_Config\"";
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

QString ConsultasDb::obtener_id_modo(){
    try {
        QString quer = "SELECT id FROM public.\"Modo_Config\"";
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

bool ConsultasDb::actualizar_modo(int modo){
    try {
        QString id_modo = obtener_id_modo();
        if(id_modo != ""){
            QString update_query = "UPDATE public.\"Modo_Config\" SET modo = " + QString::number(modo) + " WHERE id = " + id_modo;
            QString resultados = consulta(update_query);
            if(resultados.at(1) != ""){
                return true;
            }
            else{
                qDebug("[DB] False actualizar_modo");
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

QString ConsultasDb::obtener_id_giro(){
    try {
        QString quer = "SELECT id FROM public.\"Modo_Giro\"";
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

QString ConsultasDb::leer_sentido_giro(){
    try {
        QString quer = "SELECT * FROM public.\"Modo_Giro\"";
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

bool ConsultasDb::cambiar_sentido_giro(QString sentido){
    try {
        QString id_giro = obtener_id_giro();
        if(id_giro != ""){
            QString update_query = "UPDATE public.\"Modo_Giro\" SET sentido = " + sentido + " WHERE id = " + id_giro;
            QString resultados = consulta(update_query);
            if(resultados.at(1) != ""){
                return true;
            }
            else{
                qDebug("[DB] False cambiar_sentido_giro");
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

QString ConsultasDb::obtener_id_tipo_sensor(){
    try {
        QString quer = "SELECT id FROM public.\"Tipo_Sensor\"";
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

QString ConsultasDb::leer_tipo_sensor(){
    try {
        QString quer = "SELECT * FROM public.\"Tipo_Sensor\"";
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

bool ConsultasDb::cambiar_tipo_sensor(QString sentido){
    try {
        QString id_giro = obtener_id_tipo_sensor();
        if(id_giro != ""){
            QString update_query = "UPDATE public.\"Tipo_Sensor\" SET tipo = " + sentido + " WHERE id = " + id_giro;
            //qDebug() << "query - cambiar_tipo_sensor " + update_query;
            QString resultados = consulta(update_query);
            if(resultados.at(1) != ""){
                return true;
            }
            else{
                qDebug("[DB] False cambiar_tipo_sensor");
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

QString ConsultasDb::obtener_id_calibracion(){
    try {
        QString quer = "SELECT id FROM public.\"Calibracion\"";
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

QString ConsultasDb::leer_calibracion(){
    try {
        QString quer = "SELECT * FROM public.\"Calibracion\"";
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

bool ConsultasDb::guarda_cali(QString b1, QString b2, QString b3, QString b4, QString b5, QString b6, QString b7, QString b8, QString b9){
    try {
        QString id_cali = obtener_id_calibracion();
        if(id_cali != ""){
            QString update_query = "UPDATE public.\"Calibracion\" SET f1 = " + b1 + ", f2 = " + b2 + ", f3 = " + b3 +
                    ", f4 = " + b4 + ", f5 = " + b5 + ", f6 = " + b6 + ", f7 = " + b7 + ", f8 = " + b8 + ", f9 = " + b9 + " WHERE id = " + id_cali;
            QString resultados = consulta(update_query);
            if(resultados.at(1) != ""){
                return true;
            }
            else{
                qDebug("[DB] False guarda_cali");
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

QString ConsultasDb::obtener_id_offsets(){
    try {
        QString quer = "SELECT id FROM public.\"Offsets\"";
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

QString ConsultasDb::leer_offsets(){
    try {
        QString quer = "SELECT * FROM public.\"Offsets\"";
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

bool ConsultasDb::guarda_offsets(QString b1, QString b2, QString b3, QString b4, QString b5, QString b6, QString b7, QString b8){
    try {
        QString id_cali = obtener_id_offsets();
        if(id_cali != ""){
            QString update_query = "UPDATE public.\"Offsets\" SET of_peep = " + b1 + ", of_pip = " + b2 + ", of_cpeep = " + b3 +
                                    ", of_cpip = " + b4 + ", of_pre = " + b5 + ", of_bat = " + b6 + ", g_bat = " + b7 +  ", valvula = " + b8 +" WHERE id = " + id_cali;
            QString resultados = consulta(update_query);
            if(resultados.at(1) != ""){
                return true;
            }
            else{
                qDebug("[DB] False guarda_cali");
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

QString ConsultasDb::obtener_id_altura(){
    try {
        QString quer = "SELECT id FROM public.\"Altura\"";
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

QString ConsultasDb::leer_altura(){
    try {
        QString quer = "SELECT * FROM public.\"Altura\"";
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

bool ConsultasDb::guarda_altura(QString b1){
    try {
        QString id_cali = obtener_id_altura();
        if(id_cali != ""){
            QString update_query = "UPDATE public.\"Altura\" SET altura = " + b1 + " WHERE id = " + id_cali;
            QString resultados = consulta(update_query);
            if(resultados.at(1) != ""){
                return true;
            }
            else{
                qDebug("[DB] False guarda_cali");
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

bool ConsultasDb::guarda_cali_flujo(QString flujo){
    try {
        QString id_cali = obtener_id_calibracion();
        if(id_cali != ""){
            QString update_query = "UPDATE public.\"Calibracion\" SET flujo = " + flujo + " WHERE id = " + id_cali;
            QString resultados = consulta(update_query);
            if(resultados.at(1) != ""){
                return true;
            }
            else{
                qDebug("[DB] False guarda_cali");
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

bool ConsultasDb::guarda_cali_presion(QString presion){
    try {
        QString id_cali = obtener_id_calibracion();
        if(id_cali != ""){
            QString update_query = "UPDATE public.\"Calibracion\" SET presion = " + presion + " WHERE id = " + id_cali;
            QString resultados = consulta(update_query);
            if(resultados.at(1) != ""){
                return true;
            }
            else{
                qDebug("[DB] False guarda_cali");
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

QStringList ConsultasDb::obtener_eventos(){
    try {
        if(baseDatos.isOpen()){
            QString quer = "SELECT tipo, modo, descripcion, fecha, hora FROM public.\"eventos\" ORDER BY date(fecha), date(hora) DESC";
            baseDatos.transaction();
            QSqlQuery consul;
            consul.prepare(quer);
            bool resultado = consul.exec();
            if (consul.lastError().type() != QSqlError::NoError || !resultado)
                {
                    qDebug() << "[DB] obtener_eventos Error: "<< consul.lastError(); //.text();
                    baseDatos.rollback();
                }
            baseDatos.commit();
            //
            QString salida = "result?";
            QStringList *lista_filas = new QStringList;
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

QStringList ConsultasDb::borrar_eventos(){
    try {
        if(baseDatos.isOpen()){
            QString quer = "DELETE FROM public.\"eventos\" WHERE fecha <= CURRENT_DATE - integer '7'";
            baseDatos.transaction();
            QSqlQuery consul;
            consul.prepare(quer);
            bool resultado = consul.exec();
            if (consul.lastError().type() != QSqlError::NoError || !resultado)
            {
                qDebug() << "[DB] borrar_eventos Error: " << consul.lastError(); //.text();
                baseDatos.rollback();
            }
            baseDatos.commit();
            //
            QString salida = "result?";
            QStringList *lista_filas = new QStringList;
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

bool ConsultasDb::borrar_evento(QString id){
    try {
        QString update_query = "DELETE FROM public.\"eventos\" WHERE ID = " + id;
        QString resultados = consulta(update_query);
        if(resultados.at(1) != ""){
            return true;
        }
        else{
            qDebug("[DB] False borrar_evento");
            return false;
        }
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return false;
    }
}

bool ConsultasDb::agregar_evento(QString tipo, QString modo, QString descripcion){
    try {
        QString query_insert = "INSERT INTO public.\"eventos\"(tipo, modo, descripcion, fecha, hora) VALUES ('"+ tipo +"' , '" + modo +"' , '" +
                                descripcion +"' ,date(CURRENT_DATE),CAST(CURRENT_TIME(0) as time))";
        return inserta_tabla(query_insert);
    }  catch (std::exception &e) {
        qWarning("Error %s desde la funcion %s", e.what(), Q_FUNC_INFO );
        return false;
    }
}

QString ConsultasDb::numero_serie(){
    try {
        QString quer = "SELECT numero_serie FROM public.\"NumSerie\" WHERE id = 1";
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

QString ConsultasDb::leer_teclado(){
    try {
        QString quer = "SELECT * FROM public.\"teclado\"";
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

bool ConsultasDb::guarda_teclado(QString pres, QString solt){
    try {
        QString id_cali = obtener_id_teclado();
        if(id_cali != ""){
            QString update_query = "UPDATE public.\"teclado\" SET presionar = " + pres + ", soltar = " + solt + " WHERE id = " + id_cali;
            QString resultados = consulta(update_query);
            if(resultados.at(1) != ""){
                return true;
            }
            else{
                qDebug("[DB] False guarda_cali");
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

QString ConsultasDb::obtener_id_teclado(){
    try {
        QString quer = "SELECT id FROM public.\"teclado\"";
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

QString ConsultasDb::leer_fio2(){
    try {
        QString quer = "SELECT * FROM public.\"fio2\"";
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

bool ConsultasDb::guarda_fio2(QString porce_cambio, QString ls_aire, QString li_aire, QString ls_o2, QString li_o2){
    try {
        QString id_fio2 = obtener_id_fio2();
        //qDebug() << "id fio2: " + id_fio2;
        if(id_fio2 != ""){
            QString update_query = "UPDATE public.\"fio2\" SET porce_cambio = " + porce_cambio + ", ls_aire = " + ls_aire +  ", li_aire = " + li_aire + ", ls_o2 = " + ls_o2 + ", li_o2 = " + li_o2 + " WHERE id = " + id_fio2;
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

QString ConsultasDb::obtener_id_fio2(){
    try {
        QString quer = "SELECT id FROM public.\"fio2\"";
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

QString ConsultasDb::obtener_id_com_pip(){
    try {
        QString quer = "SELECT id FROM public.\"com_pip\"";
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

QString ConsultasDb::leer_com_pip(){
    try {
        QString quer = "SELECT * FROM public.\"com_pip\"";
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

bool ConsultasDb::guarda_com_pip(QString b1){
    try {
        QString id_com_pip = obtener_id_com_pip();
        if(id_com_pip != ""){
            QString update_query = "UPDATE public.\"com_pip\" SET compensacion = " + b1 + " WHERE id = " + id_com_pip;
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

QStringList ConsultasDb::obtener_ultimo_evento(){
    try {
        if(baseDatos.isOpen()){
            QString quer = "SELECT fecha,hora FROM public.\"eventos\" ORDER BY id DESC LIMIT 1";
            baseDatos.transaction();
            QSqlQuery consul;
            consul.prepare(quer);
            bool resultado = consul.exec();
            if (consul.lastError().type() != QSqlError::NoError || !resultado)
            {
                qDebug() << consul.lastError().text();
                baseDatos.rollback();
            }
            baseDatos.commit();
            //
            QString salida = "result?";
            QStringList *lista_filas = new QStringList;
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

