#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QRect>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // qDebug() << "------------------------------------------------";
    QGraphicsScene *scene = new QGraphicsScene(this);
    int width = ui->graphicsView->width();
    int height = ui->graphicsView->height();
    QRect sceneRect(-width/2, -height/2, width, height);
    scene->setSceneRect(sceneRect);

    ui->graphicsView->setScene(scene);
    // qDebug() << "------------------------------------------------";
    // QGraphicsEllipseItem *item = new QGraphicsEllipseItem;

    // QPen pen = item->pen();
    // pen.setWidth(5);;
    // pen.setColor(Qt::red);
    // item->setPen(pen);

    // QBrush brush = item->brush();
    // brush.setStyle(Qt::SolidPattern);
    // brush.setColor(Qt::yellow);
    // item->setBrush(brush);

    // item->setRect(QRect(-100, -50, 200, 100));
    // item->setFlags(QGraphicsItem::ItemIsMovable);
    // scene->addItem(item);
    // item->setPos(0, 0);
    // qDebug() << "------------------------------------------------";

    QImage image(":/picture/1.png");
    if (image.isNull()) {
        qDebug() << "img is not loaded";
    }

    image = changeImageToARGB32(image);
    image = makeCircleImage(image);
    image = makeDiskImage(image);


    diskItem = new DiskItem(image);
    scene->addItem(diskItem);
    diskItem->setPos(0, 0);
    diskItem->setFlags(QGraphicsItem::ItemIsMovable);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    // QPainter painter(this);

    // QPen pen = painter.pen();
    // pen.setColor(Qt::red);
    // pen.setWidth(10);
    // painter.setPen(pen);

    // QBrush brush = painter.brush();
    // brush.setStyle(Qt::SolidPattern);
    // brush.setColor(Qt::green);
    // painter.setBrush(brush);

    // painter.drawRect(10, 20, 100, 150);

    // qDebug() << "------------------------------------------------";

    // QImage image(":/picture/1.png");
    // if (image.isNull()) {
    //     qDebug() << "img is not loaded";
    // }

    // image = changeImageToARGB32(image);
    // image = makeCircleImage(image);
    // image = makeDiskImage(image);

    // QPainter painter(this);
    // QRect rect = image.rect();
    // rect.moveCenter(this->rect().center());
    // painter.drawImage(rect, image);

    // qDebug() << "------------------------------------------------";
}

QImage MainWindow::changeImageToARGB32(const QImage &image)
{
    QImage circleImage(":/picture/default.png");
    QImage albumImage = image.scaled(circleImage.size(), Qt::KeepAspectRatio);
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

QImage MainWindow::makeCircleImage(const QImage &image)
{
    QImage destImage = image;
    QImage srcImage(":/picture/default.png");
    QPainter painter(&destImage);
    painter.setCompositionMode(QPainter::CompositionMode_DestinationIn);
    painter.drawImage(destImage.rect(), srcImage);
    painter.end();
    return destImage;
}

QImage MainWindow::makeDiskImage(const QImage &image)
{
    QImage albumImage = image;
    QImage diskImage(":/picture/disk-background.png");

    QPainter painter(&diskImage);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);

    QPoint centerPoint = diskImage.rect().center();
    QRect rect = albumImage.rect();
    rect.moveCenter(centerPoint);

    painter.drawImage(rect, albumImage);
    painter.end();

    return diskImage;
}























void MainWindow::on_pushButton_clicked()
{
    this->diskItem->start();
}


void MainWindow::on_pushButton_2_clicked()
{
    this->diskItem->stop();
}


void MainWindow::on_pushButton_3_clicked()
{
    this->diskItem->pause();
}

