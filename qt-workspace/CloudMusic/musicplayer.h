#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <QObject>
#include <QMediaPlayer>
#include "musicsearch.h"
#include "musicinformation.h"
#include "musichttpurl.h"
#include "musiclyric.h"

class MusicPlayer : public QMediaPlayer
{
    Q_OBJECT
public:
    explicit MusicPlayer(QMediaPlayer *parent = nullptr);
    void searchMusic(const QString searchText);
    void playMusic(const QStringList &urlList);

signals:
    void musicInformationReady(const MusicInformation &musicInfo);
    void musicLyricReady(const QString musicLyricText);
    void playLyricLineChanged(int lineIndex);

public slots:
    void queryPlayLryicLineByTime(qint64 time);

private:
    MusicSearch *musicSearch;
    QMediaPlayer *mediaPlayer;
    MusicLyric *musicLyric;
    QMap<qint64, qint32> lyricTimeMap;
};

#endif // MUSICPLAYER_H
