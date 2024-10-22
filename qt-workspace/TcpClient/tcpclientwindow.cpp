#include "tcpclientwindow.h"
#include "ui_tcpclientwindow.h"
#include <QHostAddress>
#include <QDateTime>

TcpClientWindow::TcpClientWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TcpClientWindow)
{
    ui->setupUi(this);
    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket, &QTcpSocket::readyRead, this, &TcpClientWindow::readData);

    ui->serverIPLineEdit->setText("192.168.239.1");
    ui->serverPortLineEdit->setText("8080");
}

TcpClientWindow::~TcpClientWindow()
{
    delete ui;
}

void TcpClientWindow::on_connectButton_clicked()
{
    QString serverIp = ui->serverIPLineEdit->text();
    QString serverPort = ui->serverPortLineEdit->text();

    if (serverIp.isEmpty() || serverPort.isEmpty()) {
        return;
    }
    if (tcpSocket->state() == QTcpSocket::UnconnectedState) {
        tcpSocket->connectToHost(QHostAddress(serverIp),serverPort.toUShort());
    }

}


void TcpClientWindow::on_sentButton_clicked()
{
    QString data = ui->sendTextEdit->toPlainText();
    tcpSocket->write(data.toUtf8());

    return;
}

void TcpClientWindow::readData()
{
    QString info = tcpSocket->readAll();
    QString dataTime = QDateTime::currentDateTime().toString("yyyy-MMM-dd hh:mm:ss");
    ui->recvTextEdit->setPlainText(dataTime + "\n" + info + "\n");
}

