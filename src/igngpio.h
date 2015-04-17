#ifndef IGNGPIO_H
#define IGNGPIO_H

#include <QObject>
#include <QVariantMap>
#include <QVariant>
#include "ignfs.h"

class igngpio : public QObject
{
    Q_OBJECT
public:
    explicit igngpio(QObject *parent = 0);
    QString GPIO_PIN;
    QVariantMap GPIO_MAP;
    QString GPIO_MAP_DIR;
    bool GPIO_SET_MAP;
    QString GPIO_DIR;
    QString GPIO_EXPORT;
    ignfs fs;
signals:

public slots:
    bool board(const QString name);
    bool pin(const int &pin);
    bool mode(const QString &mode);
    bool write(const int &in);
};

#endif // IGNGPIO_H
