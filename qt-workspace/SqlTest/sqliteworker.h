#ifndef SQLITEWORKER_H
#define SQLITEWORKER_H

#include <QObject>
#include "musicinfo.h"

class SqliteWorker : public QObject
{
    Q_OBJECT
public:
    explicit SqliteWorker(QObject *parent = nullptr);

    void createStudentTable(void);
    void insertMusicIfNotExist(const MusicInfo &info);
    bool isExistMusic(const QString &music, const QString &album);
    void queryMusic();
    void updateMusicDownloadPath();
    void removeMusic(const QString &name, const QString &album);

signals:


public slots:
    void doWork();
    void init();
};

#endif // SQLITEWORKER_H
