#include "tcpserverwindow.h"
#include "ui_tcpserverwindow.h"
#include <QDebug>
#include <QHostAddress>
#include <QTcpSocket>

TcpServerWindow::TcpServerWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TcpServerWindow)
{
    ui->setupUi(this);
    tcpServer = new QTcpServer(this);

    ui->portLineEdit->setText("8080");

    connect(tcpServer, &QTcpServer::newConnection, this, &TcpServerWindow::acceptClientConnect);
}

TcpServerWindow::~TcpServerWindow()
{
    delete ui;
}

void TcpServerWindow::on_pushButton_clicked()
{
    QString port = ui->portLineEdit->text();
    qDebug() << port;
    if (port.isEmpty()) {
        return;
    }

    if (!tcpServer->isListening()) {
        bool ok = tcpServer->listen(QHostAddress::Any, port.toUShort());
        if (!ok) {
            qDebug() << "Fail to listen port: " << port << ", error: " << tcpServer->errorString();
        }
    }

}

void TcpServerWindow::acceptClientConnect()
{
    qDebug() << "client connect";
    QTcpSocket *tcpSocket = tcpServer->nextPendingConnection();
    // qDebug() << "client ip : " << tcpSocket->peerAddress().toString();
    // qDebug() << "client ip : " << QHostAddress(tcpSocket->peerAddress().toIPv4Address()).toString();
    // qDebug() << "client port : " << tcpSocket->peerPort();
    QString clientIp = QHostAddress(tcpSocket->peerAddress().toIPv4Address()).toString();
    quint16 clientPort = tcpSocket->peerPort();

    QString text= QString("new client(%1:%2) connect\n").arg(clientIp).arg(clientPort);
    ui->recvtextEdit->insertPlainText(text);

    connect(tcpSocket, &QTcpSocket::readyRead, this, &TcpServerWindow::displayClientData);
}

void TcpServerWindow::displayClientData()
{
    QTcpSocket *tcpSocket = (QTcpSocket *)this->sender(); // 获取发送对象的地址
    QByteArray data = tcpSocket->readAll();
    QString clientIp = QHostAddress(tcpSocket->peerAddress().toIPv4Address()).toString();
    quint16 clientPort = tcpSocket->peerPort();
    QString text= QString("client(%1:%2) data:%3\n").arg(clientIp).arg(clientPort).arg(QString::fromLocal8Bit(data));
    ui->recvtextEdit->insertPlainText(text);
}

