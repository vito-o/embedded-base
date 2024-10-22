#ifndef MUSICINFO_H
#define MUSICINFO_H

#include <QObject>
#include <QDebug>

class MusicInfo : public QObject
{
public:
    // explicit SqliteWorker(QObject *parent = nullptr);
    MusicInfo() {}
    MusicInfo(QString name, QString album, QString mp3Filename, QString lyricFilename, QString imgName) {
        this->name = name;
        this->album = album;
        this->mp3Filename = mp3Filename;
        this->lyricFilename = lyricFilename;
        this->imgName = imgName;
    }

    QString getName() const{
        return name;
    }
    QString getAlbum() const{
        return album;
    }
    QString getMp3Filename() const{
        return mp3Filename;
    }
    QString getLyricFilename() const{
        return lyricFilename;
    }
    QString getImgName() const{
        return imgName;
    }

    void setName(QString name) {
        this->name = name;
    }
    void setAlbum(QString album) {
        this->album = album;
    }
    void setMp3Filename(QString mp3Filename) {
        this->mp3Filename = mp3Filename;
    }
    void setLyricFilename(QString lyricFilename) {
        this->lyricFilename = lyricFilename;
    }
    void setImgName(QString imgName) {
        this->imgName = imgName;
    }

    void print() {
        qDebug() << "name = " << name << ";album = " << album << ";mp3Filename = " << mp3Filename << ";lyricFilename = " << lyricFilename << ";imgName = " << imgName;
    }

private:
    QString name;
    QString album;
    QString mp3Filename;
    QString lyricFilename;
    QString imgName;

signals:

};

#endif // MUSICINFO_H
