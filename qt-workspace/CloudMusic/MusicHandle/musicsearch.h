#ifndef MUSICSEARCH_H
#define MUSICSEARCH_H

#include <QObject>
#include "musichttp.h"
#include "musicinformation.h"
#include "musichttpurl.h"

class MusicSearch : public QObject
{
    Q_OBJECT
public:
    explicit MusicSearch(QObject *parent = nullptr);
    void search(const QString &music);
    QList<MusicInformation> parseMusicJsonData(const QByteArray &jsonData);
    QList<MusicInformation> readMusicData();

public slots:
    void handleData(void);

signals:
    void musicDataReady(void);
private:
    MusicHttp *http;
    QList<MusicInformation> musicInfoList;

};

#endif // MUSICSEARCH_H
