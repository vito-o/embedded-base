#include "musicalbum.h"
#include <QPainter>

MusicAlbum::MusicAlbum(QObject *parent)
    : QObject{parent}
{
    musicHttp = new MusicHttp("img.jpg", this);
    connect(musicHttp, &MusicHttp::readyRead, this, &MusicAlbum::handleData);
}

void MusicAlbum::download(const QString &httpUrl)
{
    // qDebug() << "httpUrl:" << httpUrl;
    musicHttp->get(httpUrl);
}

void MusicAlbum::handleData()
{
    QByteArray data = musicHttp->readAll();
    if (data.isEmpty()) {
        return;
    }
    QImage image;
    if (image.loadFromData(data)) {
        image = makeDiskImage(image);
        emit musicAlbumReady(image);
    }
}

void MusicAlbum::handleLocalData(const QString &filename)
{
    QImage image = makeDiskImage(QImage(filename));
    emit musicAlbumReady(image);
}

QImage MusicAlbum::changeImageToARGB32(const QImage &image)
{
    QImage circleImage(":/images/default.png");
    QImage albumImage = image.scaled(circleImage.size(), Qt::KeepAspectRatio);
    // 制作空图片
    QImage fixedImage(circleImage.size(), QImage::Format_ARGB32_Premultiplied);

    //画家把空图片作为画板
    QPainter painter(&fixedImage);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect(fixedImage.rect(), Qt::transparent);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.drawImage(fixedImage.rect(), albumImage);
    painter.end();

    return fixedImage;
}

QImage MusicAlbum::makeCircleImage(const QImage &image)
{
    QImage destImage = image;
    QImage srcImage(":/images/default.png");
    QPainter painter(&destImage);
    painter.setCompositionMode(QPainter::CompositionMode_DestinationIn);
    painter.drawImage(destImage.rect(), srcImage);
    painter.end();

    return destImage;
}

QImage MusicAlbum::makeDiskImage(const QImage &image)
{
    QImage imageARGB32 = changeImageToARGB32(image);
    QImage circleImage = makeCircleImage(imageARGB32);
    QImage diskImage(":/images/default-background.png");
    QPainter painter(&diskImage);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    QRect rect = circleImage.rect();
    QPoint point = diskImage.rect().center();
    rect.moveCenter(point);
    painter.drawImage(rect, circleImage);
    return diskImage;
}






