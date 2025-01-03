#ifndef MUSICLYRIC_H
#define MUSICLYRIC_H

#include <QObject>
#include "musichttp.h"

class MusicLyric : public QObject
{
    Q_OBJECT
public:
    explicit MusicLyric(QObject *parent = nullptr);
    void download(const QString &httpUrl);
    void parseLineLyric(const QString &lyric, const qint32 lineIndex);

    QString getMusicLyricText() const;
    QMap<qint64, qint32> getLyricTimeMap() const;

    void parseLocalLyric(const QString &filename);
    void parseLyric(const QByteArray &data);
signals:
    void lyricReady(void);


public slots:
    void parseNetworkLyric(void);

private:
    MusicHttp *musicHttp;
    QString musicLyricText;
    QMap<qint64, qint32> lyricTimeMap;
};

#endif // MUSICLYRIC_H
