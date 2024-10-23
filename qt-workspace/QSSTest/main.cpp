#include "mainwindow.h"

#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile file(":/images/style.qss");
    bool ok = file.open(QFile::ReadOnly);
    if (ok) {
        QString style = QLatin1String(file.readAll());
        qApp->setStyleSheet(style);
    }
    file.close();


    MainWindow w;
    w.show();
    return a.exec();
}
