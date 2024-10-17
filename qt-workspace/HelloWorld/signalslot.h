#ifndef SIGNALSLOT_H
#define SIGNALSLOT_H

#include <QObject>
// 自定义信号必须继承 QObject
class SignalSlot : public QObject
{
    Q_OBJECT // 这里不能缺少
public:
    explicit SignalSlot(QObject *parent = nullptr);

signals:
    void testSignal(void);

public slots:
    void testSlot(void);

};

#endif // SIGNALSLOT_H
