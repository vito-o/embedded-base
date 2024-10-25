#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QList>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // MusicHttp *musicHttp = new MusicHttp("music.json", this);
    // connect(musicHttp, &MusicHttp::readyRead, this, [musicHttp](){
    //     QByteArray data = musicHttp->readAll();
    //     qDebug() << data;
    // });

    // QString httpUrl = "http://192.168.239.1:8000/music.json";
    // musicHttp->get(httpUrl);

    musicSearch = new MusicSearch(this);
    connect(musicSearch, &MusicSearch::musicDataReady, this, [this]() {
        QList<MusicInformation> musicInfoList = musicSearch->readMusicData();
        MusicInformation musicInfo = musicInfoList[0];
        qDebug() << MusicHttpUrl::getMusicHttpUrlObject()->getMusicMP3Url(musicInfo);
        qDebug() << MusicHttpUrl::getMusicHttpUrlObject()->getMusicAlbumUrl(musicInfo);
        qDebug() << MusicHttpUrl::getMusicHttpUrlObject()->getMusicLyricUrl(musicInfo);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_searchlineEdit_returnPressed()
{
    QString searchText = ui->searchlineEdit->text();
    if (searchText.isEmpty()) {
        return;
    }
    qDebug() << searchText;
    musicSearch->search(searchText);
}

