#ifndef MUSICSCENE_H
#define MUSICSCENE_H

#include <QObject>
#include <QTimer>
#include <QGraphicsScene>
#include "musicitem.h"

class MusicScene : public QObject
{
    Q_OBJECT
public:
    explicit MusicScene(QObject *parent = nullptr);

    QGraphicsScene *getScene() const;
    void setMusicSceneRect(const QRectF &rect) const;
    void startAnimation(void);
    void stopAnimation(void);
    void resumeAnimation(void);

signals:

public slots:
    void updateDiskImage(const QImage &image);

private:
    // QTimer *timer;
    MusicItem *diskItem;
    MusicItem *needleItem;
    QGraphicsScene *scene;
};

#endif // MUSICSCENE_H
