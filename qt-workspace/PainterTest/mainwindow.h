#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QPaintEvent>
#include <QImage>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    virtual void paintEvent(QPaintEvent *event);
    QImage changeImageToARGB32(const QImage &image);
    QImage makeCircleImage(const QImage &image);
    QImage makeDiskImage(const QImage &image);


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
