#include "musiclyric.h"
#include <QDebug>

MusicLyric::MusicLyric(QObject *parent)
    : QObject{parent}
{
    musicHttp = new MusicHttp("lyric.txt", this);
    connect(musicHttp, &MusicHttp::readyRead, this, &MusicLyric::parseLyric);
}

void MusicLyric::download(const QString &httpUrl)
{
    musicHttp->get(httpUrl);
}

void MusicLyric::parseLyric()
{
    QByteArray data = musicHttp->readAll();

    musicLyricText.clear();
    lyricTimeMap.clear();
    qint32 lineIndex = 0;

    QStringList lyricList = QString(data).split("\r\n");
    foreach(QString lineLyric, lyricList) {
        if (lineLyric.isEmpty()) {
            continue;
        }
        parseLineLyric(lineLyric, lineIndex++);
    }

    if (musicLyricText.isEmpty() || lyricTimeMap.isEmpty()) {
        return;
    }

    qint64 lastTime = lyricTimeMap.lastKey();
    qint32 lastLine = lyricTimeMap[lyricTimeMap.lastKey()];
    lyricTimeMap.insert(lastTime + 60*1000, lastLine+1);

    emit lyricReady();
}

void MusicLyric::parseLineLyric(const QString &lyric, const qint32 lineIndex)
{
    QStringList lyricList = lyric.split(']');
    if (lyricList.size() != 2) {
        return;
    }
    QString lyricTime = lyricList[0].remove('[');
    QString lyricText = lyricList[1];
    // qDebug() << lyricTime << " : " << lyricText;

    musicLyricText = musicLyricText + lyricText + "\n";

    QTime time = QTime::fromString(lyricTime, "m:s.z");
    qint32 lyricTimeMsec = time.minute() * 60 * 1000 + time.second() * 1000 + time.msec();
    lyricTimeMap.insert(lyricTimeMsec, lineIndex);
}

QString MusicLyric::getMusicLyricText() const
{
    return musicLyricText;
}

QMap<qint64, qint32> MusicLyric::getLyricTimeMap() const
{
    return lyricTimeMap;
}
