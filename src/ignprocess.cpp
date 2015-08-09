#include "ignprocess.h"
#include "QDebug"

ignprocess::ignprocess(QObject *parent) :
    QObject(parent)
{

}

void ignprocess::exec(const QString &cli){
    proc.setProcessChannelMode(QProcess::MergedChannels);
    connect( &proc, SIGNAL(readyReadStandardOutput()), this, SLOT( _out()) );
    connect( &proc, SIGNAL(readyReadStandardError()), this, SLOT( _out()) );
    //proc.start(cli,QStringList(), QIODevice::ReadWrite | QIODevice::Text );
    proc.start(cli,QIODevice::ReadWrite | QIODevice::Text );
}

void ignprocess::nodeExec(const QString &cli){
    proc.setReadChannelMode(QProcess::MergedChannels);
    connect( &proc, SIGNAL(readyReadStandardOutput()), this, SLOT( nodeOut()) );
    connect( &proc, SIGNAL(readyReadStandardError()), this, SLOT( nodeOut()) );
    proc.start(cli);
}

void ignprocess::_out(){
    emit this->out(proc.readAllStandardOutput(),proc.readAllStandardError());
}

void ignprocess::nodeOut(){
    QString out(proc.readAllStandardOutput());
    QString err(proc.readAllStandardError());

    if(!out.isEmpty()){
        qDebug() << out;
    }
    if(!err.isEmpty()){
        qWarning() << QString("%1 : %2").arg("Error",err);
    }
}

void ignprocess::kill(){
    this->proc.kill();
}

int ignprocess::pid(){
    return this->proc.pid();
}

void ignprocess::write(const QString &str){
    QByteArray data(str.toStdString().c_str());
    qDebug() << "Write " << this->proc.write(data) << "byte data";
}
