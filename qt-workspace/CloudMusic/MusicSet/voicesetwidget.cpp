#include "voicesetwidget.h"
#include "ui_voicesetwidget.h"

VoiceSetWidget::VoiceSetWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::VoiceSetWidget)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_StyledBackground, true);
    setWindowFlag(Qt::Window);

    int initVolume = 10;
    ui->voiceLabel->setText(QString::number(initVolume));
    ui->voiceSlider->setValue(initVolume);
}

VoiceSetWidget::~VoiceSetWidget()
{
    delete ui;
}

void VoiceSetWidget::on_voiceSlider_sliderMoved(int position)
{
    ui->voiceLabel->setText(QString::number(position));

    emit voiceChanged(position);
}

