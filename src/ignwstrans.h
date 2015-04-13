#ifndef IGNWSTRANS_H
#define IGNWSTRANS_H

#include <QtWebChannel/QWebChannelAbstractTransport>

QT_BEGIN_NAMESPACE

class QWebSocket;
class ignwstrans : public QWebChannelAbstractTransport
{
    Q_OBJECT
public:
    explicit ignwstrans(QWebSocket *socket);
    virtual ~ignwstrans();

    void sendMessage(const QJsonObject &message) Q_DECL_OVERRIDE;

private Q_SLOTS:
    void textMessageReceived(const QString &message);

private:
    QWebSocket *m_socket;
};

QT_END_NAMESPACE

#endif // IGNWSTRANS_H
