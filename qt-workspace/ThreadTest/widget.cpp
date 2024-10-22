#include "widget.h"
#include "ui_widget.h"
#include "mythread.h"
#include <QDebug>
#include "worker.h"
#include "task.h"
#include <QThreadPool>
#include <QtConcurrent>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //-----------------------------------------
    // MyThread *myThread = new MyThread;
    // myThread->start();

    // // 在Qt中一个对象的槽函数在被信号触发调用的时候，槽函数在哪个线程中执行取决于它的对象属于哪个线程
    // //QThread::currentThread();
    // qDebug() << "main thread object:       " << this->thread();

    // QObject *object = new QObject;
    // qDebug() << "object in thread:         " << object->thread();

    // MyThread *myThread1 = new MyThread;
    // qDebug() << "myThread object in thread:" << myThread1->thread();
    //-----------------------------------------
    // Worker *worker = new Worker;
    // QThread *thread = new QThread;
    // connect(this, &Widget::startWork, worker, &Worker::doWork);
    // worker->moveToThread(thread); // 将对象移动到thread线程中
    // thread->start();
    // qDebug() << "main thread object:       " << this->thread();
    //-----------------------------------------
    // 使用线程池 运行执行方法
    // Task *task = new Task[3];
    // for (int i = 0; i < 3; i++) {T
    //     QThreadPool::globalInstance()->start(&task[i]);
    // }
    //-----------------------------------------
    //-----------------------------------------
    // QFuture<int> future = QtConcurrent::run(this, &Widget::calcSum, 10);
    // future.waitForFinished();
    // qDebug() << future.result();
    //-----------------------------------------
    // watcher = new QFutureWatcher<int>;
    // connect(watcher, &QFutureWatcher<int>::finished, this, &Widget::handleResult);
    // QFuture<int> future = QtConcurrent::run(this, &Widget::calcSum, 10);
    // watcher->setFuture(future);
    //-----------------------------------------
    //-----------------------------------------

}

Widget::~Widget()
{
    delete ui;
}

int Widget::calcSum(int n)
{
    int sum = 0;

    qDebug() << QThread::currentThread();
    for(int i = 0; i < n; i++) {
        sum += 1;
        QThread::sleep(1);
        qDebug() << "sum : " << sum;
    }

    return sum;
}

void Widget::on_pushButton_clicked()
{
    emit startWork();
}

void Widget::handleResult()
{
    qDebug() << "Result : " << watcher->result();
}

