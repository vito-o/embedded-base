#ifndef MUSICHTTP_H
#define MUSICHTTP_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

class MusicHttp : public QObject
{
    Q_OBJECT
public:
    explicit MusicHttp(const QString filename, QObject *parent = nullptr);
    bool get(const QString &httpUrl);
    enum MusicHttpState {
        MusicHttpErrorState,
        MusicHttpSuccessState
    };
    bool isError();
    QByteArray readAll(void);

    QString getFilename() const;
    void setFilename(const QString &newFilename);

signals:
    void readyRead();
    void error();

public slots:
    void writeData();
    void handleFinished();
    void handleError(QNetworkReply::NetworkError code);

private:
    QString filename;
    QNetworkAccessManager *networkManager;
    enum MusicHttpState state;
};

#endif // MUSICHTTP_H
