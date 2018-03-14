#include "widget.h"
#include "ui_widget.h"
#include <QApplication>
#include <QDateTime>
#include "capturescreen.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget(){

}

void Widget::on_pushButton_clicked()
{
    CaptureScreen * cp = new CaptureScreen();
    connect(cp, SIGNAL(signalCompleteCapture(QPixmap)),
            this, SLOT(onCompleteCapture(QPixmap)));
    cp->show();
}

void Widget::onCompleteCapture(QPixmap captureImage){
    ui->label->setPixmap(captureImage);
    captureImage.save(tr("/home/kyo/Pictures/snapshot-%1.png").arg(QDateTime::currentDateTime().toTime_t()));
}

