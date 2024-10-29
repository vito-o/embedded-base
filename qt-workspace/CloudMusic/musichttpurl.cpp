#include "musichttpurl.h"

MusicHttpUrl *MusicHttpUrl::musicHttpUrl = nullptr;

MusicHttpUrl::MusicHttpUrl(QObject *parent)
    : QObject{parent}
{
    baseHttpUrl = "http://localhost:8000";
}

void MusicHttpUrl::setServerAddress(const QString &ip, const QString &port)
{
    baseHttpUrl = QString("http://%1:%2").arg(ip).arg(port);
}

MusicHttpUrl *MusicHttpUrl::getMusicHttpUrlObject()
{
    if (!musicHttpUrl) {
        musicHttpUrl = new MusicHttpUrl;
    }
    return musicHttpUrl;
}

QString MusicHttpUrl::getMusicSearchUrl(const QString &music)
{
    QString httpUrl = QString("%1/music/%2/music.json").arg(baseHttpUrl).arg(music);
    return httpUrl;
}

QString MusicHttpUrl::getMusicMP3Url(const MusicInformation &musicInfo)
{
    QString mp3Url = QString("%1/music/%2/%3").arg(baseHttpUrl).arg(musicInfo.getMusicPath()).arg(musicInfo.getMusicMp3());
    return mp3Url;
}

QString MusicHttpUrl::getMusicAlbumUrl(const MusicInformation &musicInfo)
{
    QString albumUrl = QString("%1/music/%2/%3").arg(baseHttpUrl).arg(musicInfo.getMusicPath()).arg(musicInfo.getAlbumImage());
    return albumUrl;
}

QString MusicHttpUrl::getMusicLyricUrl(const MusicInformation &musicInfo)
{
    QString lyricUrl = QString("%1/music/%2/%3").arg(baseHttpUrl).arg(musicInfo.getMusicPath()).arg(musicInfo.getMusicLyric());
    return lyricUrl;
}
