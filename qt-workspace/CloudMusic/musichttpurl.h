#ifndef MUSICHTTPURL_H
#define MUSICHTTPURL_H

#include <QObject>
#include "musicinformation.h"

class MusicHttpUrl : public QObject
{
    Q_OBJECT
public:
    explicit MusicHttpUrl(QObject *parent = nullptr);
    void setServerAddress(const QString &ip, const QString &port);
    static MusicHttpUrl *getMusicHttpUrlObject();

    QString getMusicSearchUrl(const QString &music);
    QString getMusicMP3Url(const MusicInformation &musicInfo);
    QString getMusicAlbumUrl(const MusicInformation &musicInfo);
    QString getMusicLyricUrl(const MusicInformation &musicInfo);

signals:

private:
    QString baseHttpUrl;
    static MusicHttpUrl *musicHttpUrl;
};

#endif // MUSICHTTPURL_H
