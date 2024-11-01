#include "musicdownloadsetwidget.h"
#include "ui_musicdownloadsetwidget.h"
#include <QFileDialog>

MusicDownloadSetWidget::MusicDownloadSetWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MusicDownloadSetWidget)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_StyledBackground, true);
    setWindowFlag(Qt::Window);
}

MusicDownloadSetWidget::~MusicDownloadSetWidget()
{
    delete ui;
}

void MusicDownloadSetWidget::setDownloadPath(QString downloadPath)
{
    ui->downloadLineEdit->setText(downloadPath);
    emit downloadPathChanged(downloadPath);
}

void MusicDownloadSetWidget::on_downloadSearchButton_clicked()
{
    QString downloadPath = QFileDialog::getExistingDirectory(
        this,
        tr("选择下载的路径"),
        ".",
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
    );

    if (downloadPath.isEmpty()) {
        return;
    }

    ui->downloadLineEdit->setText(downloadPath);

    emit downloadPathChanged(downloadPath);
}

