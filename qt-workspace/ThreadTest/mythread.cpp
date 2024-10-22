#include "mythread.h"
#include <QDebug>

MyThread::MyThread(QObject *parent)
    : QThread{parent}
{
    QObject *object = new QObject;
    qDebug() << "MyThread !~ object in thread:" << object->thread();
}

void MyThread::run()
{
    // QObject *object = new QObject;
    // qDebug() << "MyThread ~ object in thread:" << object->thread();

    while(1) {
        qDebug() << "hello world";
        QThread::sleep(1);
    }
}


