#include "task.h"
#include <QDebug>
#include <QThread>

Task::Task()
{
    this->setAutoDelete(false);
}

// task需要实现run方法
void Task::run()
{
    qDebug() << "run : " << QThread::currentThread();
    for(int i = 0; i < 5; i++)
    {
        qDebug() << "run : " << QThread::currentThread() << ":" << i;
        QThread::sleep(1);
    }
}
