#include "musicinformation.h"

MusicInformation::MusicInformation()
{}

QString MusicInformation::getMusicName() const
{
    return musicName;
}

void MusicInformation::setMusicName(const QString &newMusicName)
{
    musicName = newMusicName;
}

QString MusicInformation::getAlbumName() const
{
    return albumName;
}

void MusicInformation::setAlbumName(const QString &newAlbumName)
{
    albumName = newAlbumName;
}

qint32 MusicInformation::getMusicDuration() const
{
    return musicDuration;
}

void MusicInformation::setMusicDuration(qint32 newMusicDuration)
{
    musicDuration = newMusicDuration;
}

QString MusicInformation::getMusicPath() const
{
    return musicPath;
}

void MusicInformation::setMusicPath(const QString &newMusicPath)
{
    musicPath = newMusicPath;
}

QString MusicInformation::getMusicMp3() const
{
    return musicMp3;
}

void MusicInformation::setMusicMp3(const QString &newMusicMp3)
{
    musicMp3 = newMusicMp3;
}

QString MusicInformation::getMusicLyric() const
{
    return musicLyric;
}

void MusicInformation::setMusicLyric(const QString &newMusicLyric)
{
    musicLyric = newMusicLyric;
}

QString MusicInformation::getAlbumImage() const
{
    return albumImage;
}

void MusicInformation::setAlbumImage(const QString &newAlbumImage)
{
    albumImage = newAlbumImage;
}
