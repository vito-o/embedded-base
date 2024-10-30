#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include "musicplayer.h"
#include "musicscene.h"

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
    void updateMusicDisplayDuration(qint64 duration);
    void updateMusicSliderRange(qint64 duration);
    void updateMusicPlayPosition(qint64 position);
    void updateLyricTableButtonStyle();
    void initMusicLyricTextEdit();
    bool eventFilter(QObject *watched, QEvent *event);

private slots:
    void on_searchlineEdit_returnPressed();
    void on_networkMusicTable_cellDoubleClicked(int row, int column);
    void insertNetworkMusicTable(const MusicInformation &musicInfo);
    void on_musicPlaySlider_sliderMoved(int position);
    void updateMusicDisplayLyric(const QString &musicLyricText);
    void on_musicLyricTableButton_clicked();
    void selectPlayLyricByLine(int lineIndex);
    void handlePlayerState(QMediaPlayer::State state);

    void on_playButton_clicked();

private:
    Ui::MainWindow *ui;
    MusicPlayer *musicPlayer;
    MusicScene *musicScene;

};
#endif // MAINWINDOW_H
