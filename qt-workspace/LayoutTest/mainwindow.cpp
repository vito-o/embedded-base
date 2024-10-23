#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_11_clicked()
{
    int currentIndex = ui->stackedWidget->currentIndex();
    if (currentIndex) {
        ui->stackedWidget->setCurrentIndex(currentIndex-1);
    }
}


void MainWindow::on_pushButton_12_clicked()
{
    int currentIndex = ui->stackedWidget->currentIndex();
    if (currentIndex < ui->stackedWidget->count()) {
        ui->stackedWidget->setCurrentIndex(currentIndex+1);
    }
}

