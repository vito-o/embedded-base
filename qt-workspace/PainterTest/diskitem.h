#ifndef DISKITEM_H
#define DISKITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QImage>
#include <QPropertyAnimation>

class DiskItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_PROPERTY(qreal angle READ rotation WRITE setRotation)
public:
    explicit DiskItem(const QImage image, QObject *parent = nullptr);
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
    virtual QRectF boundingRect() const;

    QImage getImage() const;
    void setImage(const QImage &newImage);
    void start();
    void stop();
    void pause();

signals:

private:
    QImage image;
    QPropertyAnimation *animation;
};

#endif // DISKITEM_H
