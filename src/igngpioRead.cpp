#include "igngpioRead.h"

igngpioRead::igngpioRead(const QString &pin, QObject *parent) : QObject(parent){
    interval = new QTimer(this);
    GPIO_VAL = "/sys/class/gpio/gpio"+pin+"/value";
    connect(interval,SIGNAL(timeout()),this,SLOT(read()));
    interval->start(500);
}

void igngpioRead::read(){
    QFileInfo file(GPIO_VAL);
    if(file.exists()){
        emit stream(fs.fileRead(GPIO_VAL));
    }
    if(!interval->isActive()){
        interval->start(500);
    }
}
