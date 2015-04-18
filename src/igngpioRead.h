#ifndef IGNGPIOREAD_H
#define IGNGPIOREAD_H

#include <QObject>
#include "ignfs.h"

class igngpioRead : public QObject
{
    Q_OBJECT
public:
    igngpioRead(QObject *parent = 0);
    ignfs fs;
    QString GPIO_VAL;
signals:
    void stream(const QString &value);
public slots:
    void read(const int &pin);
};

#endif // IGNGPIOREAD_H
