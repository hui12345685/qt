#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    picId = 2;

    QPixmap pix("E:\\Pictrue\\和老婆游北京\\1.jpg");
    ui->label->setPixmap(pix);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_startButton_clicked()
{
    myTimerId = this->startTimer(1000);
}

// 每秒执行一次
void Widget::timerEvent(QTimerEvent *event) {
    if (event->timerId() != myTimerId) {
        return;
    }

    QString path("E:\\Pictrue\\和老婆游北京\\");
    path += QString::number(picId);
    path += ".jpg";

    QPixmap pix(path);
    ui->label->setPixmap(pix);

    picId++;
    if (picId == 8) {
        picId = 1;
    }
}




void Widget::on_stopButton_clicked()
{
    this->killTimer(myTimerId);
}

