//ibnu.yahya@toroo.org
#include "ignfs.h"
#include <QDebug>

ignfs::ignfs(QObject *parent) :
    QObject(parent)
{

}

bool ignfs::fileRemove(const QString &path){
    QFile file(path);
    return file.remove();
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

bool ignfs::dir(const QString &opt, const QString &path){
    QDir dir;
    if(opt == "create"){
        return dir.mkdir(path);
    }
    else if(opt == "remove"){
        return dir.rmdir(path);
    }
    else{
        return false;
    }
}

bool ignfs::isExist(const QString &path)
{
    return QFile::exists(path);
}

bool ignfs::isDirectory(const QString &path)
{
    return QFileInfo(path).isDir();
}

bool ignfs::isFile(const QString &path)
{
    return QFileInfo(path).isFile();
}

bool ignfs::isAbsolute(const QString &path)
{
   return QFileInfo(path).isAbsolute();
}

bool ignfs::isExecutable(const QString &path)
{
   return QFileInfo(path).isExecutable();
}

bool ignfs::isSymlink(const QString &path)
{
   return QFileInfo(path).isSymLink();
}

bool ignfs::isReadable(const QString &path)
{
   return QFileInfo(path).isReadable();
}

bool ignfs::isWritable(const QString &path)
{
   return QFileInfo(path).isWritable();
}

bool ignfs::copy(const QString &src, const QString &des){
    if(QFile::exists(des)){
        QFile::remove(des);
    }
    return QFile::copy(src,des);
}

QString ignfs::openFileDialog(){
    QFileDialog *fd = new QFileDialog;
    int result = fd->exec();
    if (result)
    {
        QString directory = fd->selectedFiles()[0];
        return directory;
    }
    else {
        return "";
    }
}

QString ignfs::openDirDialog(){
    QFileDialog *fd = new QFileDialog;
#ifdef Linux
    QTreeView *tree = fd->findChild <QTreeView*>();
    tree->setRootIsDecorated(true);
    tree->setItemsExpandable(true);
#endif
    fd->setFileMode(QFileDialog::Directory);
    fd->setOption(QFileDialog::ShowDirsOnly);
    fd->setViewMode(QFileDialog::Detail);
    int result = fd->exec();
    QString directory;
    if (result)
    {
        directory = fd->selectedFiles()[0];
        return directory;
    }
    else {
        return "";
    }
}

QString ignfs::saveFileDialog(){
    QFileDialog *fd = new QFileDialog;
    QString directory = fd->getSaveFileName();
    return directory;
}

QString ignfs::saveFileDialog(const QVariant &config){
    QVariantMap conf = json->jsonParser(config).toVariantMap();
    QString title = "Save File",
            path = this->homePath(),
            ext = "";
    if(conf["title"].toString() != ""){
        title = conf["title"].toString();
    }

    if(conf["path"].toString() != ""){
        path = conf["path"].toString();
    }

    if(conf["type"].toString() != ""){
        ext = conf["type"].toString();
    }

    QFileDialog *fd = new QFileDialog;
    QWidget *widget = new QWidget();
    QString directory = fd->getSaveFileName(widget, title,path,ext);
    return directory;
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
