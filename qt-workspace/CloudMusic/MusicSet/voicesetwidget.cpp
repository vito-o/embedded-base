#include "voicesetwidget.h"
#include "ui_voicesetwidget.h"

VoiceSetWidget::VoiceSetWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::VoiceSetWidget)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_StyledBackground, true);
    setWindowFlag(Qt::Window);
}

VoiceSetWidget::~VoiceSetWidget()
{
    delete ui;
}

void VoiceSetWidget::setVoice(qint32 voice)
{
    ui->voiceLabel->setText(QString::number(voice));
    ui->voiceSlider->setValue(voice);
    emit voiceChanged(voice);
}

void VoiceSetWidget::on_voiceSlider_sliderMoved(int position)
{
    ui->voiceLabel->setText(QString::number(position));

    emit voiceChanged(position);
}

