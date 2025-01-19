#include "widget.h"
#include "ui_widget.h"
#include "cal.h"
#include <QFont>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 去掉最大化和最小化按钮
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint & ~Qt::WindowMinimizeButtonHint);

    // this->setMaximumSize(200, 285);
    // this->setMinimumSize(200, 285);

    // 设置标题
    this->setWindowTitle("计算器");

    // 设置字体 ，这些都是可以用代码设置，也可以在ui设计里面设置
    QFont f("微软雅黑", 12);
    ui->mainlineEdit->setFont(f);

    // 按钮上放图片
    // QIcon icon("D:\\qt_test\\calculator\\back.png");
    // ui->delButton->setIcon(icon);
    ui->delButton->setText("Back");
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_oneButton_clicked()
{
    expresion += "1";
    ui->mainlineEdit->setText(expresion);
}

void Widget::on_twoButton_clicked()
{
    expresion += "2";
    ui->mainlineEdit->setText(expresion);
}

void Widget::on_threeButton_clicked()
{
    expresion += "3";
    ui->mainlineEdit->setText(expresion);
}

void Widget::on_foruButton_clicked()
{
    expresion += "4";
    ui->mainlineEdit->setText(expresion);
}

void Widget::on_fiveButton_clicked()
{
    expresion += "5";
    ui->mainlineEdit->setText(expresion);
}

void Widget::on_sixButton_clicked()
{
    expresion += "6";
    ui->mainlineEdit->setText(expresion);
}

void Widget::on_sevenButton_clicked()
{
    expresion += "7";
    ui->mainlineEdit->setText(expresion);
}

void Widget::on_eightButton_clicked()
{
    expresion += "8";
    ui->mainlineEdit->setText(expresion);
}

void Widget::on_nineButton_clicked()
{
    expresion += "9";
    ui->mainlineEdit->setText(expresion);
}

void Widget::on_leftButton_clicked()
{
    expresion += "(";
    ui->mainlineEdit->setText(expresion);
}

void Widget::on_rightButton_clicked()
{
    expresion += ")";
    ui->mainlineEdit->setText(expresion);
}

void Widget::on_clearButton_clicked()
{
    expresion = "";
    ui->mainlineEdit->setText(expresion);
}

void Widget::on_addButton_clicked()
{
    expresion += "+";
    ui->mainlineEdit->setText(expresion);
}

void Widget::on_subButton_clicked()
{
    expresion += "-";
    ui->mainlineEdit->setText(expresion);
}

void Widget::on_multiButton_clicked()
{
    expresion += "*";
    ui->mainlineEdit->setText(expresion);
}

void Widget::on_divButton_clicked()
{
    expresion += "/";
    ui->mainlineEdit->setText(expresion);
}

void Widget::on_delButton_clicked()
{
    expresion.removeLast();
    ui->mainlineEdit->setText(expresion);
}

void Widget::on_equalButton_clicked()
{
    expresion = ui->mainlineEdit->text(); // 接受键盘输入的文字
    // 计算结果
    Cal cal;
    std::string exp = expresion.toStdString();
    int result = cal.CalExpression(exp);
    QString qstr = QString::number(result);
    ui->mainlineEdit->setText(qstr);
    expresion = qstr;
}
