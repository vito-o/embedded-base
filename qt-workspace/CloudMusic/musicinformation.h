#ifndef MUSICINFORMATION_H
#define MUSICINFORMATION_H

#include <QObject>

class MusicInformation
{

public:
    MusicInformation();

    QString getMusicName() const;
    void setMusicName(const QString &newMusicName);

    QString getAlbumName() const;
    void setAlbumName(const QString &newAlbumName);

    qint32 getMusicDuration() const;
    void setMusicDuration(qint32 newMusicDuration);

    QString getMusicPath() const;
    void setMusicPath(const QString &newMusicPath);

    QString getMusicMp3() const;
    void setMusicMp3(const QString &newMusicMp3);

    QString getMusicLyric() const;
    void setMusicLyric(const QString &newMusicLyric);

    QString getAlbumImage() const;
    void setAlbumImage(const QString &newAlbumImage);

private:
    QString musicName;
    QString albumName;
    qint32 musicDuration;
    QString musicPath;
    QString musicMp3;
    QString musicLyric;
    QString albumImage;
};

#endif // MUSICINFORMATION_H
