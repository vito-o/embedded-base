#include "sqlwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SqlWindow w;
    w.show();
    return a.exec();
}
