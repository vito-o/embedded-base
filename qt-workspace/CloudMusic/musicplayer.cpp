#include "musicplayer.h"

MusicPlayer::MusicPlayer(QMediaPlayer *parent)
    : QMediaPlayer{parent}
{
    mediaPlayer = new QMediaPlayer(this);
    connect(this, &MusicPlayer::positionChanged, this, &MusicPlayer::queryPlayLryicLineByTime);

    musicSearch = new MusicSearch(this);
    connect(musicSearch, &MusicSearch::musicDataReady, this, [this]() {
        QList<MusicInformation> musicInfoList = musicSearch->readMusicData();
        for(MusicInformation musicInfo : musicInfoList) {
            emit musicInformationReady(musicInfo);
        }
    });

    musicLyric = new MusicLyric(this);
    connect(musicLyric, &MusicLyric::lyricReady, this, [this]() {
        emit musicLyricReady(musicLyric->getMusicLyricText());

        lyricTimeMap = musicLyric->getLyricTimeMap();
    });

    //设置通知间隔
    this->setNotifyInterval(200);

    musicAlbum = new MusicAlbum(this);
    connect(musicAlbum, &MusicAlbum::musicAlbumReady, this, &MusicPlayer::musicAlbumReady);
}

void MusicPlayer::searchMusic(const QString searchText)
{
    musicSearch->search(searchText);
}

void MusicPlayer::playMusic(const QStringList &urlList)
{
    QString mp3Url = urlList[0];
    QString lyricUrl = urlList[1];
    QString albumUrl = urlList[2];

    musicLyric->download(lyricUrl);
    musicAlbum->download(albumUrl);

    this->setMedia(QUrl(mp3Url));
    this->setVolume(10);
    this->play();
}

void MusicPlayer::queryPlayLryicLineByTime(qint64 time)
{
    auto it = lyricTimeMap.lowerBound(time);
    if (it != lyricTimeMap.end()) {
        int lineIndex = it.key() > time ? it.value() - 1 : it.value();
        emit playLyricLineChanged(lineIndex);
        // qDebug() << lineIndex;
    }
}
