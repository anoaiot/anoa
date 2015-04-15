#include <QCoreApplication>
#include <QtWebSockets/QWebSocketServer>
#include <QCommandLineParser>
#include <QWebChannel>
#include "ignws.h"
#include "ignwstrans.h"
#include "ignserial.h"
#include "ignnetwork.h"
#include "ignfs.h"
#include "version.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QWebSocketServer server(QStringLiteral("IGNSDK API"), QWebSocketServer::NonSecureMode);
    int port = 6969;

    QCommandLineParser cmd_parser;
    cmd_parser.setApplicationDescription("IGOS Nusantara Software Development Kit For IoT");
    QCommandLineOption cmd_version(QStringList() << "v" << "version", "Show version");
    cmd_parser.addOption(cmd_version);
    QCommandLineOption cmd_ws(QStringList() << "s" << "websocket", "Setup websocket port","port");
    cmd_parser.addOption(cmd_ws);
    cmd_parser.addHelpOption();
    cmd_parser.process(a);

    if (cmd_parser.isSet(cmd_version)) {
        printf("IGNSDK IoT version %s (%s). Compiled on %s %s. Maintained by %s.\n", IGNSDK_VERSION, IGNSDK_CODENAME, __DATE__, __TIME__, IGNSDK_MAINTAINER);
        exit(0);
    }

    if(cmd_parser.isSet(cmd_ws)){
        port = cmd_parser.value(cmd_ws).toInt();
    }
    if (!server.listen(QHostAddress::LocalHost, port)) {
        qFatal("Failed to open web socket server.");
        return 1;
    }
    ignws clientWrapper(&server);

    QWebChannel channel;
    QObject::connect(&clientWrapper, &ignws::clientConnected,
                     &channel, &QWebChannel::connectTo);

    ignserial serial;
    channel.registerObject(QStringLiteral("serial"), &serial);

    ignnetwork net;
    channel.registerObject(QStringLiteral("net"), &net);

    ignfs fs;
    channel.registerObject(QStringLiteral("fs"), &fs);

    qDebug() << "Server ON : " << net.myIP() << "Port :" << port;

    return a.exec();
}
