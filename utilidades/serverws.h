#ifndef SERVERWS_H
#define SERVERWS_H

#include <QObject>
#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QByteArray>
#include <QNetworkInterface>

QT_FORWARD_DECLARE_CLASS(QWebSocketServer)
QT_FORWARD_DECLARE_CLASS(QWebSocket)

class ServerWS : public QObject
{
    Q_OBJECT
public:
    explicit ServerWS(quint16 port, bool debug = false, QObject *parent = nullptr);
    ~ServerWS();

Q_SIGNALS:
    void closed();
signals:
    void enviaComando(QString comando);

private Q_SLOTS:
    void onNewConnection();
    void processTextMessage(QString message);
    void processBinaryMessage(QByteArray message);
    void socketDisconnected();

private:
    QWebSocketServer *m_pWebSocketServer;
    QList<QWebSocket *> m_clients;
    bool m_debug;

};

#endif // SERVERWS_H
