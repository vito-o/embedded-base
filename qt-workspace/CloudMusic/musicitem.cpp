#include "musicitem.h"

MusicItem::MusicItem(const QString &filename, QObject *parent)
    : QObject{parent}
{
    image.load(filename);
    animation = new QPropertyAnimation(this, "angle");

    connect(animation, &QPropertyAnimation::finished, this, &MusicItem::finishedAnimation);
}

void MusicItem::updateImage(const QImage &image)
{
    this->image = image;
    this->update(boundingRect());
}

void MusicItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::SmoothPixmapTransform);
    painter->drawImage(boundingRect(), image);
}

QRectF MusicItem::boundingRect() const
{
    int width = image.width();
    int height = image.height();

    return QRectF(-width/2, -height/2, width, height);
}

void MusicItem::setRotationPoint(int x, int y)
{
    // 偏移坐标原点
    this->setTransformOriginPoint(x, y);
}

int MusicItem::width()
{
    return image.width();
}

int MusicItem::height()
{
    return image.height();
}

void MusicItem::startAnimation(int duration, int start, int end, int loopCount)
{
    if(animation->state() == QPropertyAnimation::Paused) {
        animation->resume();
        return;
    }

    animation->stop();
    animation->setDuration(duration);
    animation->setStartValue(start);
    animation->setEndValue(end);
    animation->setLoopCount(loopCount);
    animation->start();
}

void MusicItem::pauseAnimation()
{
    if (animation->state() == QPropertyAnimation::Running) {
        animation->pause();
    }
}

void MusicItem::resumeAnimation()
{
    if (animation->state() == QPropertyAnimation::Paused) {
        animation->resume();
    }
}

bool MusicItem::isFinished()
{
    return animation->state() == QPropertyAnimation::Stopped;
}
