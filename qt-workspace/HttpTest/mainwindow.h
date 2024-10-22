#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>

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
    void on_getButton_clicked();

    void on_postButton_clicked();

    void readData();

    void parseData();

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *networkManager;
};
#endif // MAINWINDOW_H
