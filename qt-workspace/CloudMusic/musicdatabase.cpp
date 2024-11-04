#include "musicdatabase.h"
#include <QThread>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>

MusicDatabase::MusicDatabase(QObject *parent, const QString &filename)
    : QObject{parent}
{
    QThread *thread = new QThread;

    connect(thread, &QThread::started, this, [filename, this](){
        QSqlDatabase musicDB = QSqlDatabase::addDatabase("QSQLITE", "music-database") ;
        musicDB.setDatabaseName(filename);
        bool ok = musicDB.open();
        if (!ok) {
            qDebug() << "Fail to open : " << filename << ", err: " << musicDB.lastError().text();
            return;
        }

        this->createMusicTable();
        this->queryMusic();
    });

    this->moveToThread(thread);
    thread->start();
}

void MusicDatabase::createMusicTable()
{
    QSqlDatabase musicDB = QSqlDatabase::database("music-database");
    QSqlQuery query(musicDB);

    // query.exec("DROP TABLE IF EXISTS music");

    bool ok = query.exec("create table if not exists music (MP3Path, LyricPath, AlbumPath, MusicName, AlbumName, MusicTime)");
    if (!ok) {
        qDebug() << "Fail to create music table, err: " << query.lastError().text();
        return;
    }
}

void MusicDatabase::recordMusic(const QStringList &musicInfo)
{
    if (isExistsMusic(musicInfo[3], musicInfo[4])) {
        qDebug() << "record is exists";
        return;
    }

    QSqlDatabase musicDB = QSqlDatabase::database("music-database");
    QSqlQuery query(musicDB);

    query.prepare("insert into music values (?,?,?,?,?,?)");
    query.bindValue(0, musicInfo[0]);
    query.bindValue(1, musicInfo[1]);
    query.bindValue(2, musicInfo[2]);
    query.bindValue(3, musicInfo[3]);
    query.bindValue(4, musicInfo[4]);
    query.bindValue(5, musicInfo[5]);

    bool ok = query.exec();
    if (!ok) {
        qDebug() << "Fail to insert music table, err: " << query.lastError().text();
        return;
    }

    emit musicReady(musicInfo);
}

bool MusicDatabase::isExistsMusic(const QString &MusicName, const QString &AlbumName)
{
    QSqlDatabase musicDB = QSqlDatabase::database("music-database");
    QSqlQuery query(musicDB);

    query.prepare("select * from music where MusicName = ? and AlbumName = ?");
    query.bindValue(0, MusicName);
    query.bindValue(1, AlbumName);

    bool ok = query.exec();
    if (!ok) {
        qDebug() << "Fail to select music table, err: " << query.lastError().text();
        return false;
    }

    return query.next();
}

void MusicDatabase::queryMusic()
{
    QSqlDatabase musicDB = QSqlDatabase::database("music-database");
    QSqlQuery query(musicDB);

    bool ok = query.exec("select * from music");
    if (!ok) {
        qDebug() << "Fail to select music table, err: " << query.lastError().text();
        return;
    }

    while(query.next()) {
        QString mp3Path = query.value(0).toString();
        QString lyricPath = query.value(1).toString();
        QString albumPath = query.value(2).toString();
        QString musicName = query.value(3).toString();
        QString albumName = query.value(4).toString();
        QString musicTime = query.value(5).toString();

        QStringList musicInfo;
        musicInfo << mp3Path << lyricPath << albumPath << musicName << albumName << musicTime;

        emit musicReady(musicInfo);
    }
}

void MusicDatabase::removeMusic(const QString &musicName, const QString &musicAlbum)
{
    QSqlDatabase musicDB = QSqlDatabase::database("music-database");
    QSqlQuery query(musicDB);

    query.prepare("delete from music where MusicName = ? and AlbumName = ?");
    query.bindValue(0, musicName);
    query.bindValue(1, musicAlbum);


    bool ok = query.exec();
    if (!ok) {
        qDebug() << "Fail to delete music table, err: " << query.lastError().text();
        return;
    }
}




















