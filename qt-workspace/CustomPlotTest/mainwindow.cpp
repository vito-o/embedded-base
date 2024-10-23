#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>
#include <QDebug>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

#if 0
    ui->customPlot->setInteraction(QCP::iRangeDrag, true);
    ui->customPlot->setInteraction(QCP::iRangeZoom, true);
    ui->customPlot->yAxis->setTickLength(100);
    ui->customPlot->yAxis->setRange(-1, 1);
    ui->customPlot->xAxis->setRange(0, 100);
    ui->customPlot->xAxis->ticker()->setTickCount(10);

    QVector<double> x(101), y(101);

    for(int i = 0; i <= 100; i++) {
        x[i] = i;
        double degree = (double)i / 100 * 360;
        y[i] = qSin(qDegreesToRadians(degree));
    }

    QCPGraph *graph = ui->customPlot->addGraph();
    QPen pen = graph->pen();
    pen.setWidth(3);
    pen.setColor(Qt::red);
    graph->setPen(pen);

    graph->setData(x, y);
    ui->customPlot->replot();
#endif

    ui->customPlot->setInteraction(QCP::iRangeDrag, true);
    ui->customPlot->setInteraction(QCP::iRangeZoom, true);

    // x 轴设置为时间坐标轴
    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
    ui->customPlot->xAxis->setTicker(timeTicker);

    // 获取提前10秒的数据,100毫秒刷新一次
    qint64 now = QTime::currentTime().msecsSinceStartOfDay();
    now = now - 10 * 1000;
    qDebug() << QTime::fromMSecsSinceStartOfDay(now).toString();

    for (int i = 0; i <= 100; i++) {
        m_key.append((now + i * 100) / 1000.0);

        double degrees = (double)i / 50 * 360;
        m_data1.append(qSin(qDegreesToRadians(degrees)));
        m_data2.append(qCos(qDegreesToRadians(degrees)));
    }

    ui->customPlot->xAxis->setRange(m_key.front(), m_key.last());
    ui->customPlot->yAxis->setRange(-1, 1);

    QCPGraph *graph1 = ui->customPlot->addGraph();
    QCPGraph *graph2 = ui->customPlot->addGraph();
    graph1->setData(m_key, m_data1);
    graph2->setData(m_key, m_data2);

    QPen pen1 = graph1->pen();
    pen1.setWidth(3);
    pen1.setColor(Qt::red);
    graph1->setPen(pen1);

    QPen pen2 = graph2->pen();
    pen2.setWidth(3);
    pen2.setColor(Qt::blue);
    graph2->setPen(pen2);

    ui->customPlot->replot();

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updatePlot);
    timer->start(100);

}

void MainWindow::updatePlot()
{
    static qint32 cout = 0;
    qint64 now = QTime::currentTime().msecsSinceStartOfDay();
    m_key.removeFirst();
    m_key.append(now/1000.0);

    double degree = (double)cout / 50 * 360;

    m_data1.removeFirst();
    m_data1.append(qSin(qDegreesToRadians(degree)));

    m_data2.removeFirst();
    m_data2.append(qCos(qDegreesToRadians(degree)));

    QCPGraph *graph1 = ui->customPlot->graph(0);
    QCPGraph *graph2 = ui->customPlot->graph(1);
    graph1->setData(m_key, m_data1);
    graph2->setData(m_key, m_data2);
    ui->customPlot->xAxis->setRange(m_key.front(), m_key.last());

    ui->customPlot->replot();

    cout = (cout + 1) % 101;
}

MainWindow::~MainWindow()
{
    delete ui;
}
























