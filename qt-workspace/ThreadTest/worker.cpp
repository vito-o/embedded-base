#include "worker.h"
#include <QDebug>
#include <QThread>

Worker::Worker(QObject *parent)
    : QObject{parent}
{

}

void Worker::doWork(void)
{
    qDebug() << "doWork thread object:     " << this->thread();
    for (int i = 0; i < 5; i++) {
        qDebug() << "do work";
        QThread::sleep(1);
    }
}
