#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "musicsearch.h"
#include "musichttpurl.h"
#include "musicinformation.h"

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

private slots:
    void on_searchlineEdit_returnPressed();

private:
    Ui::MainWindow *ui;
    MusicSearch *musicSearch;
};
#endif // MAINWINDOW_H
