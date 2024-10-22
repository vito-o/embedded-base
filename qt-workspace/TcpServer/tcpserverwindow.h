#ifndef TCPSERVERWINDOW_H
#define TCPSERVERWINDOW_H

#include <QMainWindow>
#include <QTcpServer>

QT_BEGIN_NAMESPACE
namespace Ui {
class TcpServerWindow;
}
QT_END_NAMESPACE

class TcpServerWindow : public QMainWindow
{
    Q_OBJECT

public:
    TcpServerWindow(QWidget *parent = nullptr);
    ~TcpServerWindow();

private slots:
    void on_pushButton_clicked();
    void acceptClientConnect();
    void displayClientData();

private:
    Ui::TcpServerWindow *ui;
    QTcpServer *tcpServer;
    // QTcpSocket *tcpSocket;
};
#endif // TCPSERVERWINDOW_H
