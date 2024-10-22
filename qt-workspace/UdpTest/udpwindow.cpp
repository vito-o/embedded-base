#include "udpwindow.h"
#include "ui_udpwindow.h"
#include <QDebug>
#include <QDateTime>

UdpWindow::UdpWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::UdpWindow)
{
    ui->setupUi(this);
    udpSocket = new QUdpSocket(this);

    bool ok = udpSocket->bind(QHostAddress::Any);
    if (!ok) {
        qDebug() << "Fail to bind : " << udpSocket->errorString();
        return;
    }

    ui->peerIPLineEdit->setText("192.168.239.1");
    ui->peerPortLineEdit->setText("8080");

    connect(udpSocket, &QUdpSocket::readyRead, this, &UdpWindow::readData);
}

UdpWindow::~UdpWindow()
{
    delete ui;
}

void UdpWindow::on_sentButton_clicked()
{
    QString peerIp = ui->peerIPLineEdit->text();
    QString peerPort = ui->peerPortLineEdit->text();

    if (peerIp.isEmpty() || peerPort.isEmpty()) {
        return;
    }

    QString data = ui->sendTextEdit->toPlainText();
    qDebug() << data << peerIp << peerPort;
    udpSocket->writeDatagram(data.toLocal8Bit(), QHostAddress(peerIp), peerPort.toUShort());
}

void UdpWindow::readData()
{
    qDebug() << "readData ~~";
    QByteArray data;
    data.resize(udpSocket->pendingDatagramSize());
    QHostAddress peerAddress;
    quint16 peerPort;
    udpSocket->readDatagram(data.data(), data.size(), &peerAddress, &peerPort);

    QString dateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    QString text = QString("[%1]:(%2:%3)%4")
                    .arg(dateTime)
                       .arg(QHostAddress(peerAddress.toIPv4Address()).toString())
                    .arg(peerPort)
                    .arg(QString::fromLocal8Bit(data) + "\n");
    qDebug() << "~~~" << dateTime;
    ui->recvTextEdit->insertPlainText(text);
}

