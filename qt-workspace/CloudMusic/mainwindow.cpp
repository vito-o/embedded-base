#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QList>
#include <QTime>
#include <QTextBlock>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // this->resize(945, 760);

    voiceSet = new VoiceSetWidget(this);
    downloadSet = new MusicDownloadSetWidget(this);
    serverAddressSet = new ServerAddressSetWidget(this);
    connect(serverAddressSet, &ServerAddressSetWidget::serverAddressChanged, MusicHttpUrl::getMusicHttpUrlObject(), &MusicHttpUrl::setServerAddress);


    // 添加时间过滤器对象
    ui->graphicsView->installEventFilter(this);

    ui->tabWidget->setCurrentIndex(1);
    musicTable = ui->networkMusicTable;
    initMusicTable(ui->networkMusicTable);

    initMusicLyricTextEdit();

    musicPlayer = new MusicPlayer;
    connect(musicPlayer, &MusicPlayer::musicInformationReady, this, &MainWindow::insertNetworkMusicTable);
    connect(musicPlayer, &MusicPlayer::durationChanged, this, &MainWindow::updateMusicDisplayDuration);
    connect(musicPlayer, &MusicPlayer::durationChanged, this, &MainWindow::updateMusicSliderRange);
    connect(musicPlayer, &MusicPlayer::positionChanged, this, &MainWindow::updateMusicPlayPosition);
    connect(musicPlayer, &MusicPlayer::musicLyricReady, this, &MainWindow::updateMusicDisplayLyric);
    connect(musicPlayer, &MusicPlayer::playLyricLineChanged, this, &MainWindow::selectPlayLyricByLine);
    connect(musicPlayer, &MusicPlayer::stateChanged, this, &MainWindow::handlePlayerState);
    connect(musicPlayer, &MusicPlayer::mediaStatusChanged, this, &MainWindow::handlePlayerMediaStatus);

    connect(voiceSet, &VoiceSetWidget::voiceChanged, musicPlayer, &MusicPlayer::setVolume);

    musicScene = new MusicScene(this);
    ui->graphicsView->setScene(musicScene->getScene());
    connect(musicPlayer, &MusicPlayer::musicAlbumReady, musicScene, &MusicScene::updateDiskImage);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::insertNetworkMusicTable(const MusicInformation &musicInfo)
{
    int lineNumber = ui->networkMusicTable->rowCount();
    ui->networkMusicTable->insertRow(lineNumber);

    QString mp3Url = MusicHttpUrl::getMusicHttpUrlObject()->getMusicMP3Url(musicInfo);
    ui->networkMusicTable->setItem(lineNumber, 0, new QTableWidgetItem(mp3Url));

    QString lyricUrl = MusicHttpUrl::getMusicHttpUrlObject()->getMusicLyricUrl(musicInfo);
    ui->networkMusicTable->setItem(lineNumber, 1, new QTableWidgetItem(lyricUrl));

    QString albumUrl = MusicHttpUrl::getMusicHttpUrlObject()->getMusicAlbumUrl(musicInfo);
    ui->networkMusicTable->setItem(lineNumber, 2, new QTableWidgetItem(albumUrl));

    ui->networkMusicTable->setItem(lineNumber, 3, new QTableWidgetItem(musicInfo.getMusicName()));
    ui->networkMusicTable->setItem(lineNumber, 4, new QTableWidgetItem(musicInfo.getAlbumName()));

    QTime time = QTime::fromMSecsSinceStartOfDay(musicInfo.getMusicDuration() * 1000);
    ui->networkMusicTable->setItem(lineNumber, 5, new QTableWidgetItem(time.toString("mm:ss")));
}

void MainWindow::initMusicTable(QTableWidget *tableWidget)
{
    tableWidget->hideColumn(0);
    tableWidget->hideColumn(1);
    tableWidget->hideColumn(2);
    tableWidget->horizontalHeader()->setFixedHeight(30);
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::updateMusicDisplayDuration(qint64 duration)
{
    QTime time = QTime::fromMSecsSinceStartOfDay(duration);
    ui->musicDurationLabel->setText(time.toString("mm:ss"));
}

void MainWindow::updateMusicSliderRange(qint64 duration)
{
    ui->musicPlaySlider->setMinimum(0);
    ui->musicPlaySlider->setMaximum(duration);
}

void MainWindow::updateMusicPlayPosition(qint64 position)
{
    ui->musicPlaySlider->setValue(position);

    QTime time = QTime::fromMSecsSinceStartOfDay(position);
    ui->playTimeLabel->setText(time.toString("mm:ss"));
}

void MainWindow::on_searchlineEdit_returnPressed()
{
    QString searchText = ui->searchlineEdit->text();
    if (searchText.isEmpty()) {
        return;
    }

    ui->networkMusicTable->setRowCount(0);
    ui->networkMusicTable->clearContents();

    musicPlayer->searchMusic(searchText);
}


void MainWindow::on_networkMusicTable_cellDoubleClicked(int row, int column)
{
    Q_UNUSED(column);

    QString mp3Url = ui->networkMusicTable->item(row, 0)->text();
    QString lyricUrl = ui->networkMusicTable->item(row, 1)->text();
    QString albumUrl = ui->networkMusicTable->item(row, 2)->text();

    QStringList urlList;

    playMusic(urlList << mp3Url << lyricUrl << albumUrl);
}

void MainWindow::playMusic(const QStringList &urlList)
{
    musicPlayer->playMusic(urlList);
    musicScene->startAnimation();
}

void MainWindow::on_musicPlaySlider_sliderMoved(int position)
{
    musicPlayer->setPosition(position);
}

void MainWindow::updateMusicDisplayLyric(const QString &musicLyricText)
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->lyricTextEdit->setText(musicLyricText);

    updateLyricTableButtonStyle();
}


void MainWindow::on_musicLyricTableButton_clicked()
{
    int currentIndex = ui->stackedWidget->currentIndex();
    ui->stackedWidget->setCurrentIndex(!currentIndex);
    updateLyricTableButtonStyle();
}

void MainWindow::selectPlayLyricByLine(int lineIndex)
{
    QTextDocument *doc = ui->lyricTextEdit->document();
    qint32 pos = doc->findBlockByLineNumber(lineIndex).position();
    QTextCursor cursor = ui->lyricTextEdit->textCursor();
    cursor.setPosition(pos, QTextCursor::MoveAnchor);
    cursor.movePosition(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);
    ui->lyricTextEdit->setTextCursor(cursor);
}

void MainWindow::handlePlayerState(QMediaPlayer::State state)
{
    if (state == QMediaPlayer::PlayingState) {
        ui->playButton->setProperty("state", "playing");
    } else {
        ui->playButton->setProperty("state", "noPlaying");
        musicScene->stopAnimation();
    }
    ui->playButton->style()->unpolish(ui->playButton);
    ui->playButton->style()->polish(ui->playButton);
    ui->playButton->update();
}

void MainWindow::updateLyricTableButtonStyle() {
    if (ui->stackedWidget->currentIndex() == 0) {
        ui->musicLyricTableButton->setProperty("displayMode", "musicTableMode");
    } else {
        ui->musicLyricTableButton->setProperty("displayMode", "musicLyricMode");
    }

    ui->musicLyricTableButton->style()->unpolish(ui->musicLyricTableButton);
    ui->musicLyricTableButton->style()->polish(ui->musicLyricTableButton);
    ui->musicLyricTableButton->update();
}

void MainWindow::initMusicLyricTextEdit()
{
    ui->stackedWidget->setCurrentIndex(1);

    QPalette palette = ui->lyricTextEdit->palette();
    palette.setColor(QPalette::Highlight, QColor(Qt::transparent));
    palette.setColor(QPalette::HighlightedText, QColor(Qt::red));
    ui->lyricTextEdit->setPalette(palette);
    QTextDocument *doc = ui->lyricTextEdit->document();
    doc->setDefaultTextOption(QTextOption(Qt::AlignHCenter));

    ui->stackedWidget->setCurrentIndex(0);
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == ui->graphicsView) {
        if (event->type() == QEvent::Resize) {
            QRect rect = ui->graphicsView->rect();
            musicScene->setMusicSceneRect(rect);
        }
    }
    return QMainWindow::eventFilter(watched, event);
}



void MainWindow::playTableMusic(QTableWidget *musicTable, int row)
{
    musicTable->selectRow(row);

    QString mp3Url = musicTable->item(row, 0)->text();
    QString lyricUrl = musicTable->item(row, 1)->text();
    QString albumUrl = musicTable->item(row, 2)->text();

    playMusic(QStringList() << mp3Url << lyricUrl << albumUrl);
}

void MainWindow::on_playButton_clicked()
{
    if (musicPlayer->mediaStatus() == QMediaPlayer::NoMedia) {
        return;
    }

    if (musicPlayer->state() == QMediaPlayer::PlayingState) {
        musicPlayer->pause();
    } else {
        if (musicPlayer->state() == QMediaPlayer::PausedState) {
            musicScene->resumeAnimation();
        } else {
            musicScene->startAnimation();
        }
        musicPlayer->play();
    }
}


void MainWindow::on_tabWidget_currentChanged(int index)
{
    if (index == 0) {
        musicTable = ui->localMusicTable;
    } else {
        musicTable = ui->networkMusicTable;
    }

    initMusicTable(musicTable);
}


void MainWindow::on_nextButton_clicked()
{
    int totalRow = musicTable->rowCount();
    if (!totalRow) {
        return ;
    }

    int row;
    int currentRow = musicTable->currentRow();
    if (currentRow < totalRow - 1) {
        row = currentRow + 1;
    } else {
        row = 0;
    }

    playTableMusic(musicTable, row);
}


void MainWindow::on_prevButton_clicked()
{
    int totalRow = musicTable->rowCount();
    if (!totalRow) {
        return ;
    }

    int row;
    int currentRow = musicTable->currentRow();
    if (currentRow > 0) {
        row = currentRow - 1;
    } else {
        row = totalRow - 1;
    }

    playTableMusic(musicTable, row);
}


void MainWindow::on_randomButton_clicked()
{
    bool rand = ui->randomButton->property("rand").toBool();
    if (!rand) {
        ui->randomButton->setProperty("rand", "true");
    } else {
        ui->randomButton->setProperty("rand", "false");
    }
    ui->randomButton->style()->unpolish(ui->randomButton);
    ui->randomButton->style()->polish(ui->randomButton);
    ui->randomButton->update();

    // int row;
    //
    // if (!totalRow) {
    //     return ;
    // }
    // int currentRow = musicTable->currentRow();

    // row = randomInteger(0, totalRow-1);

    // playTableMusic(musicTable, row);
}

void MainWindow::handlePlayerMediaStatus(QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::EndOfMedia) {
        bool rand = ui->randomButton->property("rand").toBool();
        if (rand) {
            int totalRow = musicTable->rowCount();
            if (!totalRow) {
                return ;
            }
            int row = qrand() % totalRow;
            playTableMusic(musicTable, row);
        }
    }
}


void MainWindow::on_voiceSetAction_triggered()
{
    voiceSet->show();
}


void MainWindow::on_musicDownloadSetAction_triggered()
{
    downloadSet->show();
}


void MainWindow::on_serverAddressSetAction_triggered()
{
    serverAddressSet->show();
}

