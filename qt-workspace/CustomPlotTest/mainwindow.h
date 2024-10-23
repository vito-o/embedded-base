#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"

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

public slots:
    void updatePlot();

private:
    Ui::MainWindow *ui;
    QVector<qreal> m_key;
    QVector<qreal> m_data1;
    QVector<qreal> m_data2;
};
#endif // MAINWINDOW_H
