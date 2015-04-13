#ifndef IGNWSTRANSSERVER_H
#define IGNWSTRANSSERVER_H

#include <QObject>

QT_BEGIN_NAMESPACE

class QWebSocketServer;
class ignwstrans;

class ignws : public QObject
{
    Q_OBJECT

public:
    ignws(QWebSocketServer *server, QObject *parent = 0);

Q_SIGNALS:
    void clientConnected(ignwstrans* client);

private Q_SLOTS:
    void handleNewConnection();

private:
    QWebSocketServer *m_server;
};

QT_END_NAMESPACE

#endif // IGNWSTRANSSERVER_H
