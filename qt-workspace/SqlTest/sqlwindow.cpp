#include "sqlwindow.h"
#include "ui_sqlwindow.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QStringList>
#include <QSqlError>
#include "sqliteworker.h"
#include <QThread>
#include <QSqlDriver>
#include <QSqlQuery>
#include <QMessageBox>



SqlWindow::SqlWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SqlWindow)
{
    ui->setupUi(this);

    // QStringList drivers = QSqlDatabase::drivers();
    // foreach (QString driver, drivers) {
    //     qDebug() << driver;
    // }

    // sql 在哪个线程中创建,只能在哪个线程中使用!!!
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "sqlite-connection");
    db.setDatabaseName("/home/vito/Downloads/student.db");
    bool ok = db.open();
    if (!ok) {
        qDebug() << "Fail to open database student.db : " << db.lastError().text();
        return;
    }

    SqliteWorker *worker = new SqliteWorker;
    connect(this, &SqlWindow::startWork, worker, &SqliteWorker::doWork);

    QThread *thread = new QThread;
    connect(thread, &QThread::started, worker, &SqliteWorker::init);

    worker->moveToThread(thread);
    thread->start();

    qDebug() << "------------------------------------------------------------------";
    // queryModel = new QSqlQueryModel(this);
    // queryModel->setQuery("SELECT * FROM music", db);
    // ui->tableView->setModel(queryModel);

    qDebug() << "------------------------------------------------------------------";
    tableModel = new QSqlTableModel(this, db);
    ui->tableView->setModel(tableModel);
    tableModel->setTable("music");
    tableModel->setEditStrategy(QSqlTableModel::OnFieldChange);
    tableModel->select();

}

SqlWindow::~SqlWindow()
{
    // 只有这个对象为null才是 数据库没有被使用, 通过大括号,代码执行完毕后,自动销毁
    {
        QSqlDatabase db = QSqlDatabase::database("sqlite-connection");
        db.close();
    }
    QSqlDatabase::removeDatabase("sqlite-connection");

    delete ui;
}

void SqlWindow::on_pushButton_clicked()
{
    emit startWork();
}


void SqlWindow::on_pushButton_2_clicked()
{
    QSqlDatabase db = QSqlDatabase::database("sqlite-connection");
    bool ok = db.driver()->hasFeature(QSqlDriver::Transactions);
    qDebug() << "ok : " << ok;
    if (!ok) {
        return;
    }

    db.transaction();

    QSqlQuery query(db);


    MusicInfo info1("歌曲一", "album1", "歌曲一.mp3", "~歌曲一.mp3", "歌曲一.png");
    // MusicInfo info1("歌曲2", "album2", "歌曲2.mp3", "~歌曲2.mp3", "歌曲2.png");
    MusicInfo info2("歌曲2", "album2", "歌曲2.mp3", "~歌曲2.mp3", "歌曲2.png");

    query.prepare("insert into music values(?,?,?,?,?)");
    query.bindValue(0, info1.getName());
    query.bindValue(1, info1.getAlbum());
    query.bindValue(2, info1.getMp3Filename());
    query.bindValue(3, info1.getLyricFilename());
    query.bindValue(4, info1.getImgName());

    ok = query.exec();
    if (!ok) {
        qDebug() << "Fail to exec insert music, err: " << query.lastError().text();
        db.rollback();
        return;
    }


    query.bindValue(0, info2.getName());
    query.bindValue(1, info2.getAlbum());
    query.bindValue(2, info2.getMp3Filename());
    query.bindValue(3, info2.getLyricFilename());
    query.bindValue(4, info2.getImgName());

    ok = query.exec();
    if (!ok) {
        qDebug() << "Fail to exec insert music, err: " << query.lastError().text();
        db.rollback();
        return;
    }

    ok = db.commit();
    if (!ok) {
        db.rollback();
        return;
    }

    QSqlQuery query1(db);
    ok = query1.exec("select * from music");
    if (!ok) {
        qDebug() << "Fail to exec insert music, err: " << query1.lastError().text();
        return;
    }

    while(query1.next()) {
        qDebug() << "name = " << query1.value(0).toString()
                 << ";album = " << query1.value(1).toString()
                 << ";mp3Filename = " << query1.value(2).toString()
                 << ";lyricFilename = " << query1.value(3).toString()
                 << ";imgName = " << query1.value(4).toString();
    }
}




void SqlWindow::on_pushButton_3_clicked()
{
    // QSqlDatabase db = QSqlDatabase::database("sqlite-connection");
    // queryModel->setQuery("SELECT * FROM music", db);
    if (ui->lineEdit->text().isEmpty()) {
        tableModel->setTable("music");
        tableModel->select();
        return;
    }

    QString filter = QString("Name = '%1'").arg(ui->lineEdit->text());
    tableModel->setFilter(filter);
    tableModel->select();
}


void SqlWindow::on_pushButton_4_clicked()
{
    int curRow = ui->tableView->currentIndex().row();
    //删除行
    tableModel->removeRow(curRow);
    int ok = QMessageBox::warning(this, tr("删除当前行"), tr("你确定删除当前行吗?"), QMessageBox::Yes, QMessageBox::No);
    if (ok == QMessageBox::No) {
        tableModel->revertAll();
    } else {
        tableModel->submitAll();
    }
}




















