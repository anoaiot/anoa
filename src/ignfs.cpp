//ibnu.yahya@toroo.org
#include "ignfs.h"
#include <QDebug>

ignfs::ignfs(QObject *parent) :
    QObject(parent)
{

}

bool ignfs::rm(const QString &path){
    QVariantMap info = this->info(path).toMap();
    QString absolutePath = info["absoluteFilePath"].toString();
    if(info["isFile"].toBool()){
        QFile file(absolutePath);
        return file.remove();
    }
    if(info["isDir"].toBool()){
        QDir dir;
        return dir.rmdir(absolutePath);
    }
    return false;
}

bool ignfs::mkdir(const QString &path){
    QDir dir;
    return dir.mkdir(path);
}

bool ignfs::fileWrite(const QString &path, const QString &data){
    QFile file(path);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream out(&file);
        out << data;
        file.close();
        return true;
    }
    else {
        return false;
    }
}

QString ignfs::fileRead(const QString &path){
    //QStringList fields;
    QFile file(path);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream out(&file);

        /*while(!out.atEnd()){
            fields.append(out.readLine());

        }*/
        QString data = out.readAll();
        /*foreach (const QString text, fields){
            qDebug() << text.toUtf8();
        }*/
        file.close();
        //return fields;
        return data;
    }
    else {
        qDebug()<< "Err : File not found";
        return "";
    }
}

QString ignfs::appPath(){
    return QApplication::applicationDirPath();
}

QString ignfs::homePath(){
    QString home = QDir::homePath();
    return home;
}

bool ignfs::copy(const QString &src, const QString &des){
    if(QFile::exists(des)){
        QFile::remove(des);
    }
    return QFile::copy(src,des);
}

QStringList ignfs::list(const QString &path){
    QDirIterator dirIt(path,QDirIterator::Subdirectories);
    QStringList list;
    while (dirIt.hasNext()) {
        dirIt.next();
        list.push_front(dirIt.filePath());
    }
    return list;
}

QVariant ignfs::info(const QString &path){
    QVariantMap map;
    QFileInfo info(path);
    QVariant size = info.size();
    QVariant absoluteFilePath = info.absoluteFilePath();
    QVariant baseName = info.baseName();
    QVariant isSymlink = info.isSymLink();
    QVariant isAbsolute = info.isAbsolute();
    QVariant isBundle = info.isBundle();
    QVariant isDir = info.isDir();
    QVariant isExecutable = info.isExecutable();
    QVariant isFile = info.isFile();
    QVariant isHidden = info.isHidden();
    QVariant isReadable = info.isReadable();
    QVariant isRelative = info.isRelative();
    QVariant isRoot = info.isRoot();
    QVariant isWritable = info.isWritable();
    QVariant bundleName = info.bundleName();
    QVariant exists = info.exists();
    QVariant fileName = info.fileName();
    QVariant filePath = info.filePath();
    QVariant group = info.group();
    QVariant lastModified = info.lastModified();
    QVariant lastRead = info.lastRead();
    map.insert("size",size);
    map.insert("absoluteFilePath",absoluteFilePath);
    map.insert("baseName",baseName);
    map.insert("isSymlink",isSymlink);
    map.insert("isAbsolute",isAbsolute);
    map.insert("isBundle",isBundle);
    map.insert("isDir",isDir);
    map.insert("isExecutable",isExecutable);
    map.insert("isFile",isFile);
    map.insert("isHidden",isHidden);
    map.insert("isReadable",isReadable);
    map.insert("isRelative",isRelative);
    map.insert("isRoot",isRoot);
    map.insert("isWritable",isWritable);
    map.insert("filePath",filePath);
    map.insert("bundleName",bundleName);
    map.insert("exists",exists);
    map.insert("fileName",fileName);
    map.insert("group",group);
    map.insert("lastModified",lastModified);
    map.insert("lastRead",lastRead);
    QJsonDocument json_enc = QJsonDocument::fromVariant(map);
    return json_enc.toVariant();
}
