#include "ignwstrans.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QtWebSockets/QWebSocket>

QT_BEGIN_NAMESPACE

ignwstrans::ignwstrans(QWebSocket *socket)
: QWebChannelAbstractTransport(socket)
, m_socket(socket)
{
    connect(socket, &QWebSocket::textMessageReceived,
            this, &ignwstrans::textMessageReceived);
}

ignwstrans::~ignwstrans(){}

void ignwstrans::sendMessage(const QJsonObject &message)
{
    QJsonDocument doc(message);
    m_socket->sendTextMessage(QString::fromUtf8(doc.toJson(QJsonDocument::Compact)));
}

void ignwstrans::textMessageReceived(const QString &messageData)
{
    QJsonParseError error;
    QJsonDocument message = QJsonDocument::fromJson(messageData.toUtf8(), &error);
    if (error.error) {
        qWarning() << "Failed to parse message:" << messageData
                   << "Error is:" << error.errorString();
        return;
    } else if (!message.isObject()) {
        qWarning() << "Received message: " << messageData;
        return;
    }
    emit messageReceived(message.object(), this);
}

QT_END_NAMESPACE
