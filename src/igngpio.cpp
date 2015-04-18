#include "igngpio.h"
#include "QDebug"

igngpio::igngpio(QObject *parent) :
    QObject(parent),
    m_gpio_read(0)
{
    GPIO_DIR = "/sys/class/gpio/";
    GPIO_EXPORT = "/sys/class/gpio/export";
    GPIO_UNEXPORT = "/sys/class/gpio/export";
    GPIO_MAP_DIR = "/etc/ignsdk/board/";
    GPIO_SET_MAP = false;
}

bool igngpio::board(const QString name){
    QVariantMap pathConfig = fs.info(GPIO_MAP_DIR+name+".json").toMap();
    if(pathConfig["exists"].toBool()){
        QFile config_file(GPIO_MAP_DIR+name+".json");
        QByteArray config;
        if(config_file.open(QIODevice::ReadOnly)){
            config = config_file.readAll();
            QJsonParseError *err = new QJsonParseError();
            QJsonDocument ignjson = QJsonDocument::fromJson(config, err);

            if (err->error != 0) {
              qDebug() << err->errorString();
              exit (1);
            }

            QJsonObject Object = ignjson.object();
            GPIO_MAP = Object.toVariantMap();
            GPIO_SET_MAP = true;
        }
        return true;
    }
    return false;
}

bool igngpio::pin(const int &pin){
    if(GPIO_SET_MAP && GPIO_MAP[QString::number(pin)].toString() != ""){
        GPIO_PIN = QString(GPIO_MAP[QString::number(pin)].toString());
    }
    else{
        GPIO_PIN = QString::number(pin);
    }
    return fs.fileWrite(GPIO_EXPORT,GPIO_PIN);
}

bool igngpio::mode(const QString &mode){
    if(mode == "in" || mode == "out"){
        return fs.fileWrite(GPIO_DIR+"gpio"+GPIO_PIN+"/direction",mode);
    }
    return false;
}

bool igngpio::write(const int &in){
    return fs.fileWrite(GPIO_DIR+"gpio"+GPIO_PIN+"/value",QString::number(in));
}

QObject *igngpio::read(const int &pin){
    m_gpio_read = new igngpioRead;
    m_gpio_read->read(pin);
    return m_gpio_read;
}

void igngpio::unset(const int &pin){
    GPIO_PIN = "";
    GPIO_SET_MAP = false;
    fs.fileWrite(GPIO_UNEXPORT,QString::number(pin));
}
