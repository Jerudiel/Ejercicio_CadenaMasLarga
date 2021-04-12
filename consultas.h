#ifndef CONSULTAS_H
#define CONSULTAS_H

#include <QtSql/QtSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlDriver>

class Consultas
{
public:
    Consultas();
    QString conn_string;
    QSqlDatabase conn;
    QSqlQuery consultas;

    bool conecta();
    void cerrar();
    int consulta_count(QString);
    QString consulta(QString query);
    void vaciar_tabla(QString query);
    bool inserta_tabla(QString query);
    QString buscar_ult_config(QString nombreTabla);
    QString cargar_config_default(QString nombreTabla);
    QString buscar_id_config_ultima_param();
    QString buscar_id_config_ultima(QString nombreTabla);
    void reiniciar_valores(QString nombreTabla);
    bool guardar_config_ultima_PCMV(QString pinsp, QString ipap, QString peep, QString fr, QString tinsp, QString tincr, QString oxigeno, QString mod_trigger, QString trigger_flujo, QString trigger_presion);
    bool guardar_config_ultima_VCMV(QString vtinsp, QString peep, QString fr, QString tinsp, QString meseta, QString patron, QString oxigeno, QString mod_trigger, QString trigger_flujo, QString trigger_presion);
    bool guardar_config_ultima_VSIMV(QString vtinsp, QString psoporte, QString peep, QString fr, QString tinsp, QString tincr, QString meseta, QString ets, QString patron, QString oxigeno, QString mod_trigger, QString trigger_flujo, QString trigger_presion);
    bool guardar_config_ultima_PSIMV(QString pinsp, QString psoporte, QString peep, QString fr, QString tinsp, QString tincr, QString oxigeno, QString ets, QString mod_trigger, QString trigger_flujo, QString trigger_presion);
    bool guardar_config_ultima_PCPAP(QString cpap, QString ps, QString oxigeno, QString apnea, QString mod_trigger, QString trigger_flujo, QString trigger_presion, QString frecuencia, QString pinsp, QString tinsp);
    bool guardar_config_ultima_VCPAP(QString cpap, QString ps, QString oxigeno, QString apnea, QString mod_trigger, QString trigger_flujo, QString trigger_presion, QString frecuencia, QString vtidal, QString flujo);
    QString cargar_config_default_alarm();
    QString buscar_id_config_ultima_alarm();
    QString buscar_ult_config_alarm();
    bool guardar_config_ultima_alarm(QString pre_max, QString pre_min, QString volm_max, QString volm_min, QString fre_max, QString fre_min, QString vole_max, QString vole_min, QString edo_apre, QString edo_avolm, QString edo_afre, QString edo_avole, QString t_apnea);
    QString leer_modo();
    QString obtener_id_modo();
    bool actualizar_modo(int modo);
    QString obtener_id_giro();
    QString leer_sentido_giro();
    bool cambiar_sentido_giro(QString sentido);
    QString obtener_id_tipo_sensor();
    QString leer_tipo_sensor();
    bool cambiar_tipo_sensor(QString sentido);
    QString obtener_id_calibracion();
    QString leer_calibracion();
    bool guarda_cali(QString b1, QString b2, QString b3, QString b4, QString b5, QString b6, QString b7);
    QString obtener_id_offsets();
    QString leer_offsets();
    bool guarda_offsets(QString b1, QString b2, QString b3, QString b4, QString b5, QString b6, QString b7);
    QString obtener_id_altura();
    QString leer_altura();
    bool guarda_altura(QString b1);
    bool guarda_cali_flujo(QString flujo);
    bool guarda_cali_presion(QString presion);
    QStringList obtener_eventos();
    QStringList obtener_eventos_para_borrar();
    bool borrar_evento(QString id);
    bool agregar_evento(QString tipo, QString modo, QString descripcion);
    QString numero_serie();
    bool guarda_teclado(QString pres, QString solt);
    QString leer_teclado();
    QString obtener_id_teclado();
    bool guarda_fio2(QString porce_cambio, QString ls_aire, QString li_aire, QString ls_o2, QString li_o2);
    QString leer_fio2();
    QString obtener_id_fio2();
    QString obtener_id_com_pip();
    QString leer_com_pip();
    bool guarda_com_pip(QString b1);



};

#endif // CONSULTAS_H



