#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QNetworkReply>
#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    networkManager = new QNetworkAccessManager(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::readData()
{
    QNetworkReply *reply = (QNetworkReply *) this->sender();
    QByteArray data = reply->readAll();

    QFile file("/home/vito/Downloads/tsconfig.json");
    bool ok = file.open(QFile::WriteOnly|QFile::Append);
    if (!ok) {
        qDebug() << "Fail to open: " << file.errorString();
        return;
    }

    file.write(data);
    file.close();
}

void MainWindow::parseData()
{
    QFile file("/home/vito/Downloads/tsconfig.json");
    bool ok = file.open(QFile::ReadOnly);
    if (!ok) {
        qDebug() << "Fail to open: " << file.errorString();
        return;
    }
    QByteArray data = file.readAll();
    file.close();

    qDebug() << data;

    QJsonParseError jsonError;
    QJsonDocument document = QJsonDocument::fromJson(data, &jsonError);
    if (document.isEmpty()) {
        qDebug() << "Fail to json document : " << jsonError.errorString();
        return;
    }

    QJsonObject jsonObject = document.object();
    QJsonArray jsonArray = jsonObject["references"].toArray();

    for(int i = 0; i < jsonArray.size(); i++) {
        QJsonObject object = jsonArray[i].toObject();
        QString key = object["path"].toString();
        QString value = object["path"].toString();

        qDebug() << "key: " + key;
        qDebug() << object.keys();
    }



}

void MainWindow::on_getButton_clicked()
{
    QFile::remove("/home/vito/Downloads/tsconfig.json");

    QString httpUrl = "http://192.168.239.1:8000/tsconfig.json";
    QUrl url(httpUrl);
    QNetworkRequest request(url);
    QNetworkReply *reply = networkManager->get(request);
    connect(reply, &QNetworkReply::readyRead, this, &MainWindow::readData);
    connect(reply, &QNetworkReply::finished, reply, &QNetworkReply::deleteLater);//销毁对象
    connect(reply, &QNetworkReply::finished, this, &MainWindow::parseData);
}


void MainWindow::on_postButton_clicked()
{
    QString httpUrl = "http://192.168.239.1:8080";
    QUrl url(httpUrl);
    QNetworkRequest request(url);

    QByteArray data = QString("中国").toLocal8Bit();
    networkManager->post(request, data);
}



