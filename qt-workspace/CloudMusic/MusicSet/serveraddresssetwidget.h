#ifndef SERVERADDRESSSETWIDGET_H
#define SERVERADDRESSSETWIDGET_H

#include <QWidget>

namespace Ui {
class ServerAddressSetWidget;
}

class ServerAddressSetWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ServerAddressSetWidget(QWidget *parent = nullptr);
    ~ServerAddressSetWidget();
    void setServerAddress(QString ip, QString port);

signals:
    void serverAddressChanged(QString ip, QString port);
private slots:
    void on_SAResetButton_clicked();

    void on_SAConfirmButton_clicked();

private:
    Ui::ServerAddressSetWidget *ui;
};

#endif // SERVERADDRESSSETWIDGET_H
