#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFutureWatcher>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    int calcSum(int n);

private:
    Ui::Widget *ui;
    QFutureWatcher<int> *watcher;

signals:
    void startWork(void);
private slots:
    void on_pushButton_clicked();
    void handleResult();
};
#endif // WIDGET_H
