#ifndef IGNGPIOREAD_H
#define IGNGPIOREAD_H

#include <QObject>
#include <QTimer>
#include "ignfs.h"

class igngpioRead : public QObject
{
    Q_OBJECT
public:
    igngpioRead(const QString &pin,QObject *parent = 0);
    ignfs fs;
    QString GPIO_VAL;
    QTimer *interval;
signals:
    void stream(const QString &value);
public slots:
    void read();
};

#endif // IGNGPIOREAD_H
