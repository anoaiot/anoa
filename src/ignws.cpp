#include <QtWebSockets/QWebSocketServer>
#include "ignws.h"
#include "ignwstrans.h"

QT_BEGIN_NAMESPACE

ignws::ignws(QWebSocketServer *server, QObject *parent)
    : QObject(parent)
    , m_server(server)
{
    connect(server, &QWebSocketServer::newConnection,
            this, &ignws::handleNewConnection);

}

void ignws::handleNewConnection()
{
    qDebug()<< "Handle new connection...";
    emit clientConnected(new ignwstrans(m_server->nextPendingConnection()));
}

QT_END_NAMESPACE
