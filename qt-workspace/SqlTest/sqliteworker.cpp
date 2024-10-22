#include "sqliteworker.h"

#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QStringList>

SqliteWorker::SqliteWorker(QObject *parent)
    : QObject{parent}
{}

void SqliteWorker::createStudentTable()
{
    QStringList sqlList;
    sqlList << "create table if not exists \
        music(NAME primary key, ALBUM, MP3FILENAME, lyricFilename, imgName)";
    sqlList << "create table if not exists \
        parm(ID primary key, DOWNLOADMUSICFLAG, DOWNLOADPATH)";

    QSqlDatabase db = QSqlDatabase::database("new-sqlite-connection");
    QSqlQuery query(db);

    query.exec("DROP TABLE IF EXISTS music");
    query.exec("DROP TABLE IF EXISTS parm");

    for(QString &sql:sqlList) {
        bool ok = query.exec(sql);
        if (!ok) {
            qDebug() << "Fail to exec " << sql << ", err: " << query.lastError().text();
            return;
        }
    }
}

void SqliteWorker::insertMusicIfNotExist(const MusicInfo &info)
{
    if (isExistMusic(info.getName(), info.getAlbum())) {
        qDebug() << "info is exist: name = " << info.getName() << " album = " << info.getAlbum();
        return;
    }

    QSqlDatabase db = QSqlDatabase::database("new-sqlite-connection");
    QSqlQuery query(db);

    query.prepare("insert into music values(?,?,?,?,?)");
    query.bindValue(0, info.getName());
    query.bindValue(1, info.getAlbum());
    query.bindValue(2, info.getMp3Filename());
    query.bindValue(3, info.getLyricFilename());
    query.bindValue(4, info.getImgName());

    bool ok = query.exec();
    if (!ok) {
        qDebug() << "Fail to exec insert music, err: " << query.lastError().text();
        return;
    }
}

bool SqliteWorker::isExistMusic(const QString &name, const QString &album)
{
    QSqlDatabase db = QSqlDatabase::database("new-sqlite-connection");
    QSqlQuery query(db);

    query.prepare("select * from music where name = ? and album = ?");
    query.bindValue(0, name);
    query.bindValue(1, album);

    bool ok = query.exec();
    if (!ok) {
        qDebug() << "Fail to exec select * from music, err: " << query.lastError().text();
    }

    return query.next();
}

void SqliteWorker::queryMusic()
{
    QSqlDatabase db = QSqlDatabase::database("new-sqlite-connection");
    QSqlQuery query(db);

    bool ok = query.exec("select * from music");
    if (!ok) {
        qDebug() << "Fail to exec insert music, err: " << query.lastError().text();
        return;
    }

    while(query.next()) {
        MusicInfo info;
        info.setName(query.value(0).toString());
        info.setAlbum(query.value(1).toString());
        info.setMp3Filename(query.value(2).toString());
        info.setLyricFilename(query.value(3).toString());
        info.setImgName(query.value(4).toString());

        info.print();
    }
}

void SqliteWorker::updateMusicDownloadPath()
{
    QSqlDatabase db = QSqlDatabase::database("new-sqlite-connection");
    QSqlQuery query(db);

    query.prepare("update music set lyricFilename = ? where ALBUM = ?");
    query.bindValue(0, "~~~歌曲一.mp3");
    query.bindValue(1, "album1");

    bool ok = query.exec();
    if (!ok) {
        qDebug() << "Fail to exec update music set lyricFilename, err:" << query.lastError().text();
        return;
    }
}

void SqliteWorker::removeMusic(const QString &name, const QString &album)
{
    QSqlDatabase db = QSqlDatabase::database("new-sqlite-connection");
    QSqlQuery query(db);

    query.prepare("delete from music where name = ? and album = ?");
    query.bindValue(0, name);
    query.bindValue(1, album);

    bool ok = query.exec();
    if (!ok) {
        qDebug() << "Fail to exec delete from music, err: " << query.lastError().text();
        return;
    }
}


void SqliteWorker::doWork()
{
    QSqlDatabase db = QSqlDatabase::database("new-sqlite-connection");
    qDebug() << "sql driver name : " << db.driverName();
}

void SqliteWorker::init()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "new-sqlite-connection");
    db.setDatabaseName("/home/vito/Downloads/student.db");
    bool ok = db.open();
    if (!ok) {
        qDebug() << "Fail to open database student.db : " << db.lastError().text();
        return;
    }

    this->createStudentTable();

    MusicInfo info1("歌曲一", "album1", "歌曲一.mp3", "~歌曲一.mp3", "歌曲一.png");
    this->insertMusicIfNotExist(info1);
    MusicInfo info2("歌曲er", "album2", "歌曲er.mp3", "~歌曲er.mp3", "歌曲er.png");
    this->insertMusicIfNotExist(info2);

    this->queryMusic();
    this->updateMusicDownloadPath();
    qDebug() << " ------------------------------------------- ";
    this->queryMusic();

    removeMusic("歌曲一", "album1");
    qDebug() << " ------------------------------------------- ";
    this->queryMusic();

}
