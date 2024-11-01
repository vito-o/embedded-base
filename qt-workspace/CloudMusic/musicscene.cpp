#include "musicscene.h"
#include <QDebug>

MusicScene::MusicScene(QObject *parent)
    : QObject{parent}
{
    // timer = new QTimer(this);
    // //设置setimeout 只执行一次
    // timer->setSingleShot(true);
    // connect(timer, &QTimer::timeout, this, [this]() {
    //     diskItem->startAnimation(60*1000, 0, 360);
    // });

    scene = new QGraphicsScene(this);
    diskItem = new MusicItem(":/images/default-background.png", this);
    needleItem = new MusicItem(":/images/zhen1.png", this);
    qreal x = - 3.0/8 * needleItem->width();
    qreal y = - needleItem->height() / 2;
    needleItem->setRotationPoint(x, y);// 设置坐标原点

    scene->addItem(diskItem);
    scene->addItem(needleItem);

    connect(needleItem, &MusicItem::finishedAnimation, [this]() {
        diskItem->startAnimation(60*1000, 0, 360);
    });
}

QGraphicsScene *MusicScene::getScene() const
{
    return scene;
}

void MusicScene::setMusicSceneRect(const QRectF &rect) const
{
    qreal width = rect.width();
    qreal height = rect.height();
    QRectF sceneRect(-width/2, -height/2, width, height);

    scene->setSceneRect(sceneRect);
    diskItem->setPos(0, 0);

    qreal needlePosX = -width/3 + needleItem->width()/2;
    qreal needlePosY = -height/3.3 + needleItem->height()/2;
    needleItem->setPos(needlePosX + 10, needlePosY + 10);
}

void MusicScene::startAnimation()
{
    diskItem->pauseAnimation();
    needleItem->startAnimation(3 * 1000, 0, 20, 1);
}

void MusicScene::stopAnimation()
{
    diskItem->pauseAnimation();
    needleItem->pauseAnimation();
}

// 重新恢复
void MusicScene::resumeAnimation()
{
    needleItem->resumeAnimation();
    if (needleItem->isFinished()) {
        diskItem->resumeAnimation();
    }
}

void MusicScene::updateDiskImage(const QImage &image)
{
    diskItem->updateImage(image);
}
