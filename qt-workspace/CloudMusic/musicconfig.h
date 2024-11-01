#ifndef MUSICCONFIG_H
#define MUSICCONFIG_H

#include <QObject>

class MusicConfig : public QObject
{
    Q_OBJECT
public:
    explicit MusicConfig(QObject *parent = nullptr, const QString &filename = "config.json");
    void save();
    void restore();

    QString getFilename() const;
    void setFilename(const QString &newFilename);

    QString getDownloadPath() const;
    void setDownloadPath(const QString &newDownloadPath);

    qint32 getVoiceSize() const;
    void setVoiceSize(qint32 newVoiceSize);

    bool getDownloadMusicFlag() const;
    void setDownloadMusicFlag(bool newDownloadMusicFlag);

    QString getServerIp() const;
    void setServerIp(const QString &newServerIp);

    QString getServerPort() const;
    void setServerPort(const QString &newServerPort);

    void setServerIpAndPort(const QString &newServerIp, const QString &newServerPort);
signals:

private:
    QString filename;
    QString downloadPath;
    qint32 voiceSize;
    bool downloadMusicFlag;
    QString serverIp;
    QString serverPort;

};

#endif // MUSICCONFIG_H
