#include "pushbutton.h"
#include "QDebug"

PushButton::PushButton(QWidget *parent)
    : QPushButton{parent}
{

}

void PushButton::mousePressEvent(QMouseEvent *e)
{
    qDebug() << "mousePressEvent" ;
    // emit clicked();
    QPushButton::mousePressEvent(e);
    qDebug() << "---------------------------";
}
