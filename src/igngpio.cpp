#include "igngpio.h"
#include "QDebug"

igngpio::igngpio(QObject *parent) : QObject(parent)
{
    GPIO_DIR = "/sys/class/gpio/";
    GPIO_EXPORT = "/sys/class/gpio/export";
}

bool igngpio::pin(const int &pin){
    GPIO_PIN = QString::number(pin);
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
