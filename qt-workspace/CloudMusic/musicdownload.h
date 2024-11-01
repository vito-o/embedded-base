#ifndef MUSICDOWNLOAD_H
#define MUSICDOWNLOAD_H

#include <QObject>
#include "musichttp.h"
#include <QQueue>
#include <QMutex>

class MusicDownload : public QObject
{
    Q_OBJECT
public:
    explicit MusicDownload(QObject *parent = nullptr);

    void download(const QStringList &musicInfo);
    void addMusicToQueue(const QStringList &musicInfo);
    QStringList removeMusicFromQueue();
    bool isEmptyMusicQueue();
    bool blockDownload(const QString &httpUrl, const QString &filename, qint32 timeout = -1);
    QString getDownloadPath() const;
    void setDownloadPath(const QString &newDownloadPath);

signals:
    void start();
    void musicDownloadReady(const QStringList &musicInfo);

public slots:
    void downloadMusic();
    void updateDownloadPath(const QString downloadPath);


private:
    bool bushState{false};
    MusicHttp *musicHttp;
    QQueue<QStringList> musicQueue;
    static QMutex lock;
    QString downloadPath;
};

#endif // MUSICDOWNLOAD_H
