#include "igngpioRead.h"
#include <QThread>

igngpioRead::igngpioRead(QObject *parent) : QObject(parent){}

void igngpioRead::read(const int &pin){
    GPIO_VAL = "/sys/class/gpio/gpio"+QString::number(pin)+"/value";
    QFileInfo file(GPIO_VAL);
    if(file.exists()){
        while(true){
            emit stream(fs.fileRead(GPIO_VAL));
            QThread::sleep(500);
        }
    }
}
