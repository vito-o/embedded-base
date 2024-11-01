#include "musichttp.h"
#include <QUrl>
#include <QFile>
#include <QDebug>

MusicHttp::MusicHttp(const QString filename, QObject *parent)
    : QObject{parent}
    , filename(filename)
{
    networkManager = new QNetworkAccessManager(this);
    //初始化请求状态
    state = MusicHttpState::MusicHttpSuccessState;
}

bool MusicHttp::get(const QString &httpUrl)
{
    if (QFile::exists(filename)) {
        QFile::remove(filename);
    }
    //每次请求前重置状态
    state = MusicHttpState::MusicHttpSuccessState;

    QUrl url(httpUrl);
    QNetworkRequest request(url);

    QNetworkReply *reply = networkManager->get(request);
    connect(reply, &QNetworkReply::readyRead, this, &MusicHttp::writeData);
    connect(reply, &QNetworkReply::finished, this, &MusicHttp::handleFinished);
    // connect(reply, &QNetworkReply::finished, &QNetworkReply::deleteLater);
    //这个这么写,主要是因为,信号和方法名相同,导致冲突,需要改变
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(handleError(QNetworkReply::NetworkError)));
}

bool MusicHttp::isError()
{
    return state == MusicHttpState::MusicHttpErrorState ? true : false;
}

QByteArray MusicHttp::readAll()
{
    QFile file(filename);
    bool ok = file.open(QFile::ReadOnly);
    if (!ok) {
        qDebug() << "Fail to open read: " << filename << ", err: " << file.errorString();
        return QByteArray();
    }

    QByteArray data = file.readAll();
    file.close();
    return data;
}

void MusicHttp::writeData()
{
    QNetworkReply *reply = (QNetworkReply *)this->sender();
    QByteArray data = reply->readAll();

    QFile file(filename);
    bool ok = file.open(QFile::Append | QFile::WriteOnly);
    if (!ok) {
        qDebug() << "Fail to open write: " << filename << ", err: " << file.errorString();
        return;
    }

    file.write(data);
    file.close();
}

void MusicHttp::handleFinished()
{
    QNetworkReply *reply = (QNetworkReply *)this->sender();
    if (reply->error() == QNetworkReply::NoError) {
        emit readyRead();
    }
    reply->deleteLater();
}

void MusicHttp::handleError(QNetworkReply::NetworkError code)
{
    qDebug() << "NetworkError, code: " << code;
    state = MusicHttpState::MusicHttpErrorState;

    emit error();
}

QString MusicHttp::getFilename() const
{
    return filename;
}

void MusicHttp::setFilename(const QString &newFilename)
{
    filename = newFilename;
}
