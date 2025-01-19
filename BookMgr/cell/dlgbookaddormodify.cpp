#include "dlgbookaddormodify.h"
#include "ui_dlgbookaddormodify.h"
#include "lib/sqlmgr.h"
#include <QDebug>

DlgBookAddOrModify::DlgBookAddOrModify(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DlgBookAddOrModify)
    , m_id(-1)
{
    ui->setupUi(this);
}

DlgBookAddOrModify::~DlgBookAddOrModify()
{
    delete ui;
}

void DlgBookAddOrModify::SetType(int id)
{
    m_id = id;
    // 执行sql语句并显示到对应的控件上
    QStringList line = SqlMgr::GetInstance()->GetBook(QString::number(id));
    if (line.size() != 7) {
        return;
        qDebug() << line;
    }
    ui->le_name->setText(line[1]);
    ui->le_count->setText(line[2]);
    ui->le_price->setText(line[6]);
    ui->cb1->setCurrentText(line[3]);
    ui->cb2->setCurrentText(line[4]);
    ui->cb3->setCurrentText(line[5]);
}

void DlgBookAddOrModify::on_btn_ok_clicked()
{
    QStringList ls;
    ls << QString::number(m_id);
    ls << ui->le_name->text();
    ls << ui->le_count->text();
    ls << ui->le_price->text();
    ls << ui->cb1->currentText();
    ls << ui->cb2->currentText();
    ls << ui->cb3->currentText();
    if (-1 != m_id) {
        // 更新
        SqlMgr::GetInstance()->UpdateBook(ls);
    } else {
        // 添加
        SqlMgr::GetInstance()->AddBook(ls);
    }
    hide();
}

void DlgBookAddOrModify::on_btn_cancel_clicked()
{
    this->hide();
}
