#ifndef UDPWINDOW_H
#define UDPWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>

QT_BEGIN_NAMESPACE
namespace Ui {
class UdpWindow;
}
QT_END_NAMESPACE

class UdpWindow : public QMainWindow
{
    Q_OBJECT

public:
    UdpWindow(QWidget *parent = nullptr);
    ~UdpWindow();

private slots:
    void on_sentButton_clicked();
    void readData();

private:
    Ui::UdpWindow *ui;
    QUdpSocket *udpSocket;
};
#endif // UDPWINDOW_H
