#include "serverws.h"
#include "QtWebSockets/qwebsocketserver.h"
#include "QtWebSockets/qwebsocket.h"
#include <QtCore/QDebug>


ServerWS::ServerWS(quint16 port, bool debug, QObject *parent) : QObject(parent),
    m_pWebSocketServer( new QWebSocketServer(QStringLiteral("Servidor Mon"), QWebSocketServer::NonSecureMode, this)),
    m_debug(debug)
{
    //crear host
    QString ip = "";
    const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
    for (const QHostAddress &address: QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost)
            ip = address.toString();
            //qDebug() << "Direccion: " << address.toString();
    }
    //QHostAddress::Any
    if(m_pWebSocketServer->listen(QHostAddress(ip), port)){
        if(m_debug)
            qDebug() << "[ServerWS] Servidor Mon" << port;
        connect(m_pWebSocketServer, &QWebSocketServer::newConnection, this, &ServerWS::onNewConnection);
        connect(m_pWebSocketServer, &QWebSocketServer::closed, this, &ServerWS::closed);
    }
}

ServerWS::~ServerWS(){
    m_pWebSocketServer->close();
    qDeleteAll(m_clients.begin(), m_clients.end());
}

void ServerWS::onNewConnection()
{
    QWebSocket *pSocket = m_pWebSocketServer->nextPendingConnection();

    connect(pSocket, &QWebSocket::textMessageReceived, this, &ServerWS::processTextMessage);
    connect(pSocket, &QWebSocket::binaryMessageReceived, this, &ServerWS::processBinaryMessage);
    connect(pSocket, &QWebSocket::disconnected, this, &ServerWS::socketDisconnected);

    m_clients << pSocket;
}

//! [processTextMessage]
void ServerWS::processTextMessage(QString message)
{
    //QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (m_debug)
        qDebug() << "[ServerWS] Message received:" << message;
    emit enviaComando(message);
    /*if (pClient) {
        pClient->sendTextMessage(message);
    }*/
}
//! [processTextMessage]

//! [processBinaryMessage]
void ServerWS::processBinaryMessage(QByteArray message)
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (m_debug)
        qDebug() << "[ServerWS] Binary Message received:" << message;
    if (pClient) {
        pClient->sendBinaryMessage(message);
    }
}
//! [processBinaryMessage]

//! [socketDisconnected]
void ServerWS::socketDisconnected()
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (m_debug)
        qDebug() << "[ServerWS] socketDisconnected:" << pClient;
    if (pClient) {
        m_clients.removeAll(pClient);
        pClient->deleteLater();
    }
}
//! [socketDisconnected]
