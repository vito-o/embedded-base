#include "serveraddresssetwidget.h"
#include "ui_serveraddresssetwidget.h"
#include <QDebug>
#include <QHostAddress>
#include <QMessageBox>

ServerAddressSetWidget::ServerAddressSetWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ServerAddressSetWidget)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_StyledBackground, true);
    setWindowFlag(Qt::Window);

    ui->ipLineEdit->setText("192.168.239.1");
    ui->portLineEdit->setText("8080");
}

ServerAddressSetWidget::~ServerAddressSetWidget()
{
    delete ui;
}

void ServerAddressSetWidget::on_SAResetButton_clicked()
{
    ui->ipLineEdit->clear();
    ui->portLineEdit->clear();
}


void ServerAddressSetWidget::on_SAConfirmButton_clicked()
{
    QString ip = ui->ipLineEdit->text();
    QString port = ui->portLineEdit->text();

    if(ip.isEmpty() || port.isEmpty()) {
        QMessageBox::warning(this, "ip或port不能为空", "Invalid ip address: "+ip + " Invalid port address: "+port);
        return;
    }

    QStringList ipDataList = ip.split('.');
    if (ipDataList.size() != 4) {
        // qDebug() << "Invalid ip address: " << ip;
        QMessageBox::warning(this, "ip地址错误", "Invalid ip address: "+ip);
        return;
    }

    if(QHostAddress(ip).isNull()) {
        QMessageBox::warning(this, "ip地址错误", "Invalid ip address: "+ip);
        return;
    }

    bool ok;
    port.toUShort(&ok);
    if (!ok) {
        // qDebug() << "Invalid port: " << port;
        QMessageBox::warning(this, "port错误", "Invalid port address: "+port);
        return;
    }

    emit serverAddressChanged(ip, port);

    // this->hide();
}

