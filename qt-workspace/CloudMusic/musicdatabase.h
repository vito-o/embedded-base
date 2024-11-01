#ifndef MUSICDATABASE_H
#define MUSICDATABASE_H

#include <QObject>

class MusicDatabase : public QObject
{
    Q_OBJECT
public:
    explicit MusicDatabase(QObject *parent = nullptr, const QString &filename = "music.db");
    void createMusicTable();
    bool isExistsMusic(const QString &MusicName, const QString &AlbumName);
signals:
    void musicReady(const QStringList &musicInfo);

public slots:
    void recordMusic(const QStringList &musicInfo);
    void queryMusic();
signals:
};

#endif // MUSICDATABASE_H
