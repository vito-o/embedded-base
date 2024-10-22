#ifndef SQLWINDOW_H
#define SQLWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>
#include <QSqlTableModel>

QT_BEGIN_NAMESPACE
namespace Ui {
class SqlWindow;
}
QT_END_NAMESPACE

class SqlWindow : public QMainWindow
{
    Q_OBJECT

public:
    SqlWindow(QWidget *parent = nullptr);
    ~SqlWindow();

signals:
    void startWork();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::SqlWindow *ui;
    QSqlQueryModel *queryModel;
    QSqlTableModel *tableModel;
};
#endif // SQLWINDOW_H
