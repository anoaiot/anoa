#include "igngpio.h"
#include "QDebug"

igngpio::igngpio(QObject *parent) :
    QObject(parent),
    m_gpio_read(0)
{
    GPIO_DIR = "/sys/class/gpio/";
    GPIO_EXPORT = "/sys/class/gpio/export";
    GPIO_UNEXPORT = "/sys/class/gpio/unexport";
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

QString igngpio::PIN(const int &pin){
    if(GPIO_SET_MAP && GPIO_MAP[QString::number(pin)].toString() != ""){
        GPIO_PIN = QString(GPIO_MAP[QString::number(pin)].toString());
        return GPIO_PIN;
    }
    GPIO_PIN = QString::number(pin);
    return GPIO_PIN;
}

bool igngpio::set(const int &pin){
    QString PIN = this->PIN(pin);
    return fs.fileWrite(GPIO_EXPORT,PIN);
}

bool igngpio::mode(const QString &mode){
    if(mode == "in" || mode == "out"){
        return fs.fileWrite(GPIO_DIR+"gpio"+GPIO_PIN+"/direction",mode);
    }
    return false;
}

bool igngpio::write(const int &pin,const int &in){
    QString PIN = this->PIN(pin);
    if(in == 1 || in == 0){
        return fs.fileWrite(GPIO_DIR+"gpio"+PIN+"/value",QString::number(in));
    }
    return false;
}

QObject *igngpio::read(const int &pin){
    QString PIN = this->PIN(pin);
    m_gpio_read = new igngpioRead(PIN);
    return m_gpio_read;
}

void igngpio::unset(const int &pin){
    QString PIN = this->PIN(pin);
    GPIO_PIN = "";
    GPIO_SET_MAP = false;
    fs.fileWrite(GPIO_UNEXPORT,PIN);
}
