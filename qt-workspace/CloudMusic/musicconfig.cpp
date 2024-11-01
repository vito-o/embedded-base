#include "musicconfig.h"
#include <QFile>
#include <QDir>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>

MusicConfig::MusicConfig(QObject *parent, const QString &filename)
    : QObject{parent}
{
    this->filename = filename;

    if(!QFile::exists(filename)) {
        this->downloadPath = QDir::currentPath();
        this->voiceSize = 10;
        this->serverIp = "192.168.239.1";
        this->serverPort = "8080";
        this->downloadMusicFlag = false;
        save();
    } else {
        restore();
    }
}

void MusicConfig::save()
{
    QJsonObject configObject;

    configObject["downloadPath"] = downloadPath;
    configObject["voiceSize"] = voiceSize;
    configObject["serverIp"] = serverIp;
    configObject["serverPort"] = serverPort;
    configObject["downloadMusicFlag"] = downloadMusicFlag;

    QJsonDocument configDoc(configObject);
    QByteArray configData = configDoc.toJson();

    QFile file(filename);
    bool ok = file.open(QFile::WriteOnly | QFile::Truncate);
    if (!ok) {
        qDebug() << "Fail to open :" << filename << ", err: " << file.errorString();
        return;
    }

    file.write(configData);
    file.close();
}

void MusicConfig::restore()
{
    QFile file(filename);
    bool ok = file.open(QFile::ReadOnly);
    if (!ok) {
        qDebug() << "Fail to open : " << filename << ", err: " << file.errorString();
        return;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument configDoc = QJsonDocument::fromJson(data);
    if (configDoc.isEmpty()) {
        qDebug() << "Fail to read json data";
        return;
    }

    QJsonObject configObject = configDoc.object();
    downloadPath = configObject["downloadPath"].toString();
    voiceSize = configObject["voiceSize"].toInt();
    serverIp = configObject["serverIp"].toString();
    serverPort = configObject["serverPort"].toString();
    downloadMusicFlag = configObject["downloadMusicFlag"].toBool();
}

QString MusicConfig::getFilename() const
{
    return filename;
}

void MusicConfig::setFilename(const QString &newFilename)
{
    filename = newFilename;
}

QString MusicConfig::getDownloadPath() const
{
    return downloadPath;
}

void MusicConfig::setDownloadPath(const QString &newDownloadPath)
{
    downloadPath = newDownloadPath;
    save();
}

qint32 MusicConfig::getVoiceSize() const
{
    return voiceSize;
}

void MusicConfig::setVoiceSize(int newVoiceSize)
{
    voiceSize = newVoiceSize;
    save();
}

bool MusicConfig::getDownloadMusicFlag() const
{
    return downloadMusicFlag;
}

void MusicConfig::setDownloadMusicFlag(bool newDownloadMusicFlag)
{
    downloadMusicFlag = newDownloadMusicFlag;
    save();
}

QString MusicConfig::getServerIp() const
{
    return serverIp;
}

void MusicConfig::setServerIp(const QString &newServerIp)
{
    serverIp = newServerIp;
    save();
}

QString MusicConfig::getServerPort() const
{
    return serverPort;
}

void MusicConfig::setServerPort(const QString &newServerPort)
{
    serverPort = newServerPort;
    save();
}

void MusicConfig::setServerIpAndPort(const QString &newServerIp, const QString &newServerPort){
    serverIp = newServerIp;
    serverPort = newServerPort;
    save();
}
