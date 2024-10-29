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
    initMusicTable(ui->networkMusicTable);
    initMusicLyricTextEdit();

    musicPlayer = new MusicPlayer;
    connect(musicPlayer, &MusicPlayer::musicInformationReady, this, &MainWindow::insertNetworkMusicTable);
    connect(musicPlayer, &MusicPlayer::durationChanged, this, &MainWindow::updateMusicDisplayDuration);
    connect(musicPlayer, &MusicPlayer::durationChanged, this, &MainWindow::updateMusicSliderRange);
    connect(musicPlayer, &MusicPlayer::positionChanged, this, &MainWindow::updateMusicPlayPosition);
    connect(musicPlayer, &MusicPlayer::musicLyricReady, this, &MainWindow::updateMusicDisplayLyric);
    connect(musicPlayer, &MusicPlayer::playLyricLineChanged, this, &MainWindow::selectPlayLyricByLine);

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
    urlList << mp3Url << lyricUrl << albumUrl;
    musicPlayer->playMusic(urlList);
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
