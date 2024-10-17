#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include <QPushButton>

class PushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit PushButton(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *e);

signals:
};

#endif // PUSHBUTTON_H
