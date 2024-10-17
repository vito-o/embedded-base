#include "signalslot.h"
#include "QDebug"

SignalSlot::SignalSlot(QObject *parent)
    : QObject{parent}
{}

void SignalSlot::testSlot()
{
    qDebug() << "SignalSlot::testSlot()";
}
