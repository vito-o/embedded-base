#include "musicdownload.h"
#include <QThread>
#include <QDebug>
#include <QEventLoop>
#include <QTimer>
#include <QDir>

QMutex MusicDownload::lock;

MusicDownload::MusicDownload(QObject *parent)
    : QObject{parent}
{
    downloadPath = QDir::currentPath();

    musicHttp = new MusicHttp("", this);
    connect(this, &MusicDownload::start, this, &MusicDownload::downloadMusic);

    QThread *thread = new QThread;
    this->moveToThread(thread);
    thread->start();
}

void MusicDownload::addMusicToQueue(const QStringList &musicInfo)
{
    QMutexLocker mutexLocker(&lock);
    musicQueue.enqueue(musicInfo);
}

QStringList MusicDownload::removeMusicFromQueue()
{
    QMutexLocker mutexLocker(&lock);
    return musicQueue.dequeue();
}

bool MusicDownload::isEmptyMusicQueue()
{
    QMutexLocker mutexLocker(&lock);
    return musicQueue.isEmpty();
}

void MusicDownload::download(const QStringList &musicInfo)
{
    /*
     * mp3Url albumUrl lyricUrl musicName albumName
     * 1.添加到队列
     * 2.让下载线程从队列获取歌曲信息,然后下载
     */
    addMusicToQueue(musicInfo);
    if (!bushState) {
        emit start();
    }
}

void MusicDownload::downloadMusic()
{
    bushState = true;
    while(!isEmptyMusicQueue()) {
        QStringList musicInfo = removeMusicFromQueue();

        // 以歌曲的名称在下载路径下创建一个子文件夹,如果已经存在则不创建直接使用
        QDir downloadDir(downloadPath);
        if (!downloadDir.exists(musicInfo[3])) {
            downloadDir.mkdir(musicInfo[3]);
        }

        QString musicDownloadPath = downloadDir.absoluteFilePath(musicInfo[3]);

        bool ok = blockDownload(musicInfo[0], musicDownloadPath + "/" +"music.mp3");
        if (!ok) {
            qDebug() << "Fail to download music.mp3, httpUrl: " << musicInfo[0];
            continue;
        }
        ok = blockDownload(musicInfo[1], musicDownloadPath + "/" +"lyric.txt");
        if (!ok) {
            qDebug() << "Fail to download lyric.txt, lyricUrl: " << musicInfo[1];
            continue;
        }
        ok = blockDownload(musicInfo[2], musicDownloadPath + "/" +"album.jpg");
        if (!ok) {
            qDebug() << "Fail to download album.png, albumUrl: " << musicInfo[2];
            continue;
        }

        musicInfo[0] = musicDownloadPath + "/" +"music.mp3";
        musicInfo[1] = musicDownloadPath + "/" +"lyric.txt";
        musicInfo[2] = musicDownloadPath + "/" +"album.jpg";
        emit musicDownloadReady(musicInfo);
    }
    bushState = false;
}

void MusicDownload::updateDownloadPath(const QString downloadPath)
{
    this->downloadPath = downloadPath;
}

//阻塞(同步)方式下载
bool MusicDownload::blockDownload(const QString &httpUrl, const QString &filename, qint32 timeout)
{
    bool result = true;
    musicHttp->setFilename(filename);
    musicHttp->get(httpUrl);

    QEventLoop loop;
    connect(musicHttp, &MusicHttp::readyRead, &loop, &QEventLoop::quit); // 下载成功
    connect(musicHttp, &MusicHttp::error, &loop, &QEventLoop::quit); // 下载产生错误
    if (timeout > 0) {
        QTimer::singleShot(timeout, this, [&loop, &result](){
            loop.quit();
            result = false;
        });
    }
    loop.exec();

    return !musicHttp->isError() && result;
}

QString MusicDownload::getDownloadPath() const
{
    return downloadPath;
}

void MusicDownload::setDownloadPath(const QString &newDownloadPath)
{
    downloadPath = newDownloadPath;
}


