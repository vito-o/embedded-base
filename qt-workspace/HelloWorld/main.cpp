#include "mainwindow.h"

#include <QApplication>

/*
 * QApplication: 类它包含主事件循环， 用来处理来自窗口系统和其他资源的事件
 * MainWindow：自定义的类，创建对象w时调用MainWindow的构造函数，构造函数里面把界面上需要用到的对象进行创建，并且用MainWindow创建的对象作为他们的父对象
 * 显示MainWIndow对象，此时那些以Mainindow对象作父对象的子对象也一起显示出来
 *
 * 开启事件循环，捕获事件，如：键盘、鼠标等事件
 */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    // a.exec(); 是个死循环，不会退出， 它在里面做一些事件循环，
    return a.exec();
}
