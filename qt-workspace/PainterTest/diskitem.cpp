#include "diskitem.h"
#include <QPainter>

// 自定义图元
DiskItem::DiskItem(const QImage image, QObject *parent)
    : QObject{parent}
{
    this->image = image;
    animation = new QPropertyAnimation(this, "angle", this);
    animation->setDuration(30000);
    animation->setStartValue(0);
    animation->setEndValue(360);
    animation->setLoopCount(-1);
    animation->start();
}

void DiskItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::SmoothPixmapTransform);
    painter->drawImage(boundingRect(), image);
}

QRectF DiskItem::boundingRect() const
{
    int width = image.width();
    int height = image.height();
    return QRectF(-width/2,-height/2, width, height);
}

QImage DiskItem::getImage() const
{
    return image;
}

void DiskItem::setImage(const QImage &newImage)
{
    image = newImage;
}

void DiskItem::start()
{
    animation->start();
}

void DiskItem::stop()
{
    animation->stop();
}

void DiskItem::pause()
{
    animation->pause();
}
