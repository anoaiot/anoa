#include <QCoreApplication>
#include <QtWebSockets/QWebSocketServer>
#include <QCommandLineParser>
#include <QWebChannel>
#include <QFileInfo>
#include "ignws.h"
#include "ignwstrans.h"
#include "ignserial.h"
#include "ignnetwork.h"
#include "ignfs.h"
#include "ignsql.h"
#include "igngpio.h"
#include "igngpioRead.h"
#include "ignprocess.h"
#include "ignsystem.h"
#include "version.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QWebSocketServer server(QStringLiteral("IGNSDK API"), QWebSocketServer::NonSecureMode);
    int port = 6969;
    QHostAddress host,publichost;
    QHostAddress localhost = QHostAddress::LocalHost;

    Q_FOREACH(QHostAddress address, QNetworkInterface::allAddresses()) {
      if (!address.isLoopback() && (address.protocol() == QAbstractSocket::IPv4Protocol)) {
         publichost = address;
         break;
       }
    }

    QCommandLineParser cmd_parser;
    cmd_parser.setApplicationDescription("IGOS Nusantara Software Development Kit For IoT");
    QCommandLineOption cmd_version(QStringList() << "v" << "version", "Show version");
    cmd_parser.addOption(cmd_version);
    QCommandLineOption cmd_port(QStringList() << "p" << "port", "Setup websocket port","port");
    cmd_parser.addOption(cmd_port);
    QCommandLineOption cmd_target(QStringList() << "t" << "target", "Set IP target","all, public, set ip address");
    cmd_parser.addOption(cmd_target);
    QCommandLineOption cmd_node(QStringList() << "n" << "nodejs", "Execute nodejs script","nodejs script");
    cmd_parser.addOption(cmd_node);
    cmd_parser.addHelpOption();
    cmd_parser.process(a);

    if (cmd_parser.isSet(cmd_version)) {
        printf("IGNSDK IoT version %s (%s). Compiled on %s %s. Maintained by %s.\n", IGNSDK_VERSION, IGNSDK_CODENAME, __DATE__, __TIME__, IGNSDK_MAINTAINER);
        exit(0);
    }

    if(cmd_parser.isSet(cmd_port)){
        port = cmd_parser.value(cmd_port).toInt();
    }

    if(cmd_parser.isSet(cmd_target)){
        QString opt = cmd_parser.value(cmd_target).toUtf8();
        if(opt == "all"){
            host = QHostAddress("0.0.0.0");
        }
        else if(opt == "public"){
            host = publichost;
        }
        else{
            host = opt;
        }
    }

    if(host.toString().isEmpty()){
        host = localhost;
    }

    if (!server.listen(host, port)) {
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

    ignsql sql;
    channel.registerObject(QStringLiteral("sql"), &sql);

    igngpio gpio;
    channel.registerObject(QStringLiteral("gpio"), &gpio);

    ignsystem sys;
    channel.registerObject(QStringLiteral("sys"), &sys);

    qDebug() << "Server ON : " << host.toString() << "Port :" << port;

    ignprocess proc;
    QList<QString> list;
    QString NODE_PATH;
    list << "/usr/bin/node" << "/usr/bin/nodejs" << "/usr/local/bin/node" << "/usr/local/bin/nodejs";
    if(cmd_parser.isSet(cmd_node)){
        QString script = cmd_parser.value(cmd_node).toUtf8();
        Q_FOREACH(QString path, list){
            QFileInfo node(path);
            if(node.exists()){
                NODE_PATH = path;
                break;
            }
        }

        if(NODE_PATH.isEmpty()){
            qDebug() << "node.js not found!";
        }
        else{
            qDebug() << "Nodejs script : " << script;
            proc.nodeExec(NODE_PATH+" "+script);
        }
    }

    return a.exec();
}
