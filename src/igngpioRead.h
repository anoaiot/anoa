#ifndef IGNGPIOREAD_H
#define IGNGPIOREAD_H

#include <QObject>
#include "ignfs.h"

class igngpioRead : public QObject
{
    Q_OBJECT
public:
    explicit igngpioRead(const int &pin, QObject *parent = 0);
    ignfs fs;
    QString GPIO_VAL;
signals:
    void stream(const QString &value);
public slots:
};

#endif // IGNGPIOREAD_H
