#ifndef IGNGPIO_H
#define IGNGPIO_H

#include <QObject>
#include "ignfs.h"

class igngpio : public QObject
{
    Q_OBJECT
public:
    explicit igngpio(QObject *parent = 0);
    QString GPIO_PIN;
    QString GPIO_DIR;
    QString GPIO_EXPORT;
    ignfs fs;
signals:

public slots:
    bool pin(const int &pin);
    bool mode(const QString &mode);
    bool write(const int &in);
};

#endif // IGNGPIO_H
