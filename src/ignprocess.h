#ifndef IGNPROCESS_H
#define IGNPROCESS_H

#include <QObject>
#include <QProcess>

class ignprocess : public QObject
{
    Q_OBJECT
public:
    explicit ignprocess(QObject *parent = 0);
    QProcess proc;

signals:
    void out(const QString& out,const QString& err);

public slots:
    void exec(const QString& cli);
    void nodeExec(const QString& cli);
    void _out();
    void nodeOut();
    void kill();
    void write(const QString &str);
    int pid();
};

#endif // IGNPROCESS_H
