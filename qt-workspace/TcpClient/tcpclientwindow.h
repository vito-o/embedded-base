#ifndef TCPCLIENTWINDOW_H
#define TCPCLIENTWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui {
class TcpClientWindow;
}
QT_END_NAMESPACE

class TcpClientWindow : public QMainWindow
{
    Q_OBJECT

public:
    TcpClientWindow(QWidget *parent = nullptr);
    ~TcpClientWindow();

signals:


private slots:
    void on_connectButton_clicked();

    void on_sentButton_clicked();

    void readData();

private:
    Ui::TcpClientWindow *ui;
    QTcpSocket *tcpSocket;
};
#endif // TCPCLIENTWINDOW_H
