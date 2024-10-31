#ifndef MUSICDOWNLOADSETWIDGET_H
#define MUSICDOWNLOADSETWIDGET_H

#include <QWidget>

namespace Ui {
class MusicDownloadSetWidget;
}

class MusicDownloadSetWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MusicDownloadSetWidget(QWidget *parent = nullptr);
    ~MusicDownloadSetWidget();

signals:
    void downloadPathChanged(QString downloadPath);
private slots:
    void on_downloadSearchButton_clicked();

private:
    Ui::MusicDownloadSetWidget *ui;
};

#endif // MUSICDOWNLOADSETWIDGET_H
