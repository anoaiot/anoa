//ibnu.yahya@toroo.org
#ifndef IGNFS_H
#define IGNFS_H

#include <QObject>
#include <QSize>
#include <QtWidgets/QApplication>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QTreeView>
#include <QDirIterator>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>
#include <QDateTime>
#include "ignjson.h"

class ignfs : public QObject
{
    Q_OBJECT

public:
    ignfs(QObject *parent = 0);
    ignjson *json;

signals:

public slots:
    bool rm(const QString& path);
    QString appPath();
    QString homePath();
    bool fileWrite(const QString& path, const QString& data);
    QString fileRead(const QString& path);
    bool mkdir(const QString& path);
    bool copy(const QString &src, const QString &des);
    QStringList list(const QString &path);
    QVariant info(const QString &path);
};

#endif // IGNFS_H
