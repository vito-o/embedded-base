#ifndef VOICESETWIDGET_H
#define VOICESETWIDGET_H

#include <QWidget>

namespace Ui {
class VoiceSetWidget;
}

class VoiceSetWidget : public QWidget
{
    Q_OBJECT

public:
    explicit VoiceSetWidget(QWidget *parent = nullptr);
    ~VoiceSetWidget();

signals:
    void voiceChanged(int voice);

private slots:
    void on_voiceSlider_sliderMoved(int position);

private:
    Ui::VoiceSetWidget *ui;
};

#endif // VOICESETWIDGET_H
