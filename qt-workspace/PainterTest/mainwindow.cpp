#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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

    QImage image(":/picture/1.png");
    if (image.isNull()) {
        qDebug() << "img is not loaded";
    }

    image = changeImageToARGB32(image);
    image = makeCircleImage(image);
    image = makeDiskImage(image);

    QPainter painter(this);
    QRect rect = image.rect();
    rect.moveCenter(this->rect().center());
    painter.drawImage(rect, image);
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






















