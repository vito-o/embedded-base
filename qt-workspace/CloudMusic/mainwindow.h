#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include "musicplayer.h"
#include "musicscene.h"
#include "voicesetwidget.h"
#include "musicdownloadsetwidget.h"
#include "serveraddresssetwidget.h"
#include "musichttpurl.h"
#include "musicconfig.h"
#include "musicdownload.h"
#include "musicdatabase.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void initMusicTable(QTableWidget *tableWidget);
    void initMusicConfig(MusicConfig *musicConfig);

    void updateMusicDisplayDuration(qint64 duration);
    void updateMusicSliderRange(qint64 duration);
    void updateMusicPlayPosition(qint64 position);
    void updateLyricTableButtonStyle();
    void initMusicLyricTextEdit();
    bool eventFilter(QObject *watched, QEvent *event);
    void playMusic(const QStringList &urlList);
    void playTableMusic(QTableWidget *musicTable, int row);

private slots:
    void on_searchlineEdit_returnPressed();
    void on_networkMusicTable_cellDoubleClicked(int row, int column);
    void insertNetworkMusicTable(const MusicInformation &musicInfo);
    void insertLocalMusicTable(const QStringList &musicInfo);
    void on_musicPlaySlider_sliderMoved(int position);
    void updateMusicDisplayLyric(const QString &musicLyricText);
    void on_musicLyricTableButton_clicked();
    void selectPlayLyricByLine(int lineIndex);
    void handlePlayerState(QMediaPlayer::State state);

    void on_playButton_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_nextButton_clicked();

    void on_prevButton_clicked();

    void on_randomButton_clicked();
    void handlePlayerMediaStatus(QMediaPlayer::MediaStatus status);

    void on_voiceSetAction_triggered();

    void on_musicDownloadSetAction_triggered();

    void on_serverAddressSetAction_triggered();

private:
    Ui::MainWindow *ui;
    MusicPlayer *musicPlayer;
    MusicScene *musicScene;
    QTableWidget *musicTable;
    VoiceSetWidget *voiceSet;
    MusicDownloadSetWidget *downloadSet;
    ServerAddressSetWidget *serverAddressSet;
    MusicConfig *musicConfig;
    MusicDownload *musicDownload;
    MusicDatabase *musicDatabase;
};
#endif // MAINWINDOW_H
