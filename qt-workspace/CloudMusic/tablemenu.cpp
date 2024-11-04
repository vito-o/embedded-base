#include "tablemenu.h"
#include <QDebug>
#include <QTableWidget>
#include <QFileInfo>
#include <QDir>
#include <QFileDialog>
#include <QtConcurrent/QtConcurrent>

TableMenu::TableMenu(QWidget *parent)
    : QMenu{parent}
{
    this->addAction("另存歌词", this, &TableMenu::saveAsMusicLyric);
    this->addAction("另存歌曲", this, &TableMenu::saveAsMusicMP3);
    this->addAction("另存专辑图片", this, &TableMenu::saveAsMusicAlbum);
    this->addAction("删除", this, &TableMenu::removeMusic);
}

void TableMenu::removeMusic()
{
    QTableWidget *musicTable = (QTableWidget *) this->parent();
    while(musicTable->selectedItems().count() > 0) {
        int row = musicTable->selectedItems()[0]->row();
        QString musicName = musicTable->item(row, 3)->text();
        QString musicAlbum = musicTable->item(row, 4)->text();
        QString musicPath = musicTable->item(row, 0)->text();

        //界面删除
        musicTable->removeRow(row);
        //本地删除
        // deleteLocalMusic(musicPath);
        QtConcurrent::run(this, &TableMenu::deleteLocalMusic, musicPath);
        //数据库删除
        emit removeMusicReady(musicName, musicAlbum);

    }
    // qDebug() << "removeMusic";
}

void TableMenu::saveAsMusicMP3()
{
    // qDebug() << "saveAsMusicMP3";

    QString saveAsPath = QFileDialog::getExistingDirectory(
        this,
        tr("选择下载的路径"),
        ".",
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
        );

    if (saveAsPath.isEmpty()) {
        return;
    }

    QTableWidget *musicTable = (QTableWidget *) this->parent();
    int row = musicTable->currentRow();
    if (row >= 0) {
        QString musicName = musicTable->item(row, 3)->text();
        QString musicPath = musicTable->item(row, 0)->text();
        // QFile::copy(musicPath, saveAsPath + "/" + musicName + ".mp3");

        QtConcurrent::run(QFile::copy, musicPath, saveAsPath + "/" + musicName + ".mp3");
    }
}

void TableMenu::saveAsMusicLyric()
{
    // qDebug() << "saveAsMusicLyric";
    QString saveAsPath = QFileDialog::getExistingDirectory(
        this,
        tr("选择下载的路径"),
        ".",
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
        );

    if (saveAsPath.isEmpty()) {
        return;
    }

    QTableWidget *musicTable = (QTableWidget *) this->parent();
    int row = musicTable->currentRow();
    if (row >= 0) {
        QString musicName = musicTable->item(row, 3)->text();
        QString lyricPath = musicTable->item(row, 1)->text();
        // QFile::copy(lyricPath, saveAsPath + "/" + musicName + ".txt");
        QtConcurrent::run(QFile::copy, lyricPath, saveAsPath + "/" + musicName + ".txt");
    }
}

void TableMenu::saveAsMusicAlbum()
{
    // qDebug() << "saveAsMusicAlbum";
    QString saveAsPath = QFileDialog::getExistingDirectory(
        this,
        tr("选择下载的路径"),
        ".",
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
        );

    if (saveAsPath.isEmpty()) {
        return;
    }

    QTableWidget *musicTable = (QTableWidget *) this->parent();
    int row = musicTable->currentRow();
    if (row >= 0) {
        QString musicName = musicTable->item(row, 3)->text();
        QString albumPath = musicTable->item(row, 2)->text();
        // QFile::copy(albumPath, saveAsPath + "/" + musicName + ".jpg");
        QtConcurrent::run(QFile::copy, albumPath, saveAsPath + "/" + musicName + ".jpg");
    }
}

void TableMenu::deleteLocalMusic(const QString &filepath)
{
    QFileInfo fileInfo(filepath);
    QDir fileDir = fileInfo.absoluteDir();
    bool ok = fileDir.removeRecursively();
    if (!ok) {
        qDebug() << "Fail to remove dir: " << fileDir.absolutePath();
    }
}
