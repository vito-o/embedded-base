#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
// 命名空间的声明，声明有一个命名空间叫Ui，里面有一个类叫MainWindow
// 命名空间的定义，要包含实现，所以这里不是定义
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    // 在qt中，如果你想定义signals或slots的时候，就需要这个Q_OBJECT
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool eventFilter(QObject *watched, QEvent *event);

// 信号的定义
signals:
    void mySignal_1(void);
    void mySignal_2(int data);

// 定义槽
public slots:
    void mySlot_1(void);
    void mySlot_2(int data);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
