#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStyle>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    play = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    play = !play;
    if (play) {
        ui->pushButton_2->setProperty("mode", "play");
    } else {
        ui->pushButton_2->setProperty("mode", "pause");
    }
    ui->pushButton_2->style()->unpolish(ui->pushButton_2);
    ui->pushButton_2->style()->polish(ui->pushButton_2);
    ui->pushButton_2->update();

}

