#ifndef TABLEMENU_H
#define TABLEMENU_H

#include <QWidget>
#include <QMenu>

class TableMenu : public QMenu
{
    Q_OBJECT
public:
    explicit TableMenu(QWidget *parent = nullptr);

    void removeMusic(void);
    void saveAsMusicMP3(void);
    void saveAsMusicLyric(void);
    void saveAsMusicAlbum(void);
    void deleteLocalMusic(const QString &filepath);

signals:
    void removeMusicReady(const QString &musicName, const QString &musicAlbum);

};

#endif // TABLEMENU_H
