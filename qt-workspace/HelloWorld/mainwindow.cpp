#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "signalslot.h"
#include <QThread>
#include <QTimer>
#include <QDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton->setText("hells world");

    // 事件过滤器 第一步
    // 给自己的对象指定一个事件过滤器
    ui->pushButton->installEventFilter(this);


    // 信号与槽连接
    // 手动连接
    // 方式一
    connect(this, SIGNAL(mySignal_1()), this, SLOT(mySlot_1()));
    connect(this, SIGNAL(mySignal_2(int)), this, SLOT(mySlot_2(int)));
    // 方式二
    connect(this, &MainWindow::mySignal_1, this, &MainWindow::mySlot_1);
    connect(this, &MainWindow::mySignal_2, this, &MainWindow::mySlot_2);
    // 给按钮添加信号与槽(两个对象，信号与槽)
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::mySlot_1);

    // 信号发送
    emit mySignal_1();
    emit mySignal_2(100);


    // 两个对象信号与槽通信(自定义信号)
    SignalSlot *ssObject = new SignalSlot;
    connect(this, &MainWindow::mySignal_1, ssObject, &SignalSlot::testSlot);

}

MainWindow::~MainWindow()
{
    delete ui;
}


// 事件过滤器 第二步
/*
    场景：将所有发向obj的事件先经过制定的过滤函数处理一下，然后再发往obj
    返回true表示事件已经处理，无需再传递给obj对象了
    返回false则正常传递到obj对象
*/
bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == ui->pushButton) {
        if (event->type() == QEvent::MouseButtonPress) {
            qDebug() << "mouse button press";
            return true;
        }
    }
}

void MainWindow::mySlot_1()
{
    qDebug() << "call myslot_1";
}

void MainWindow::mySlot_2(int data)
{
    qDebug() << "call myslot_2" << data;
}

// 信号与槽连接
// 自动连接
//on打头，pushButton对象名称，clicked信号名
void MainWindow::on_pushButton_clicked()
{
    qDebug() << "call on_pushButton_clicked()";

    emit mySignal_1();
}


void MainWindow::on_pushButton_2_clicked()
{
    qDebug() << "sleep 3 s";
    // QThread::sleep(3); // 卡界面
    QEventLoop loopObject;
    QTimer::singleShot(5*1000, &loopObject, &QEventLoop::quit);
    loopObject.exec();
    qDebug() << "ok";
}


void MainWindow::on_pushButton_3_clicked()
{
    QDialog dialog;
    dialog.show();
    // 事件循环 更像是，通过事件循环的持续调用机制，阻止这个方法执行完毕后销毁方法内对象。然后通过设置事件循环结束信号，进而完成执行该方法
    QEventLoop loopObject;
    connect(&dialog, &QDialog::finished, &loopObject, &QEventLoop::quit);
    loopObject.exec();
}

