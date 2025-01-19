#include "dlgbookborrowreturn.h"
#include "record.h"
#include "ui_record.h"
#include "lib/sqlmgr.h"

#include <QMessageBox>

Record::Record(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Record)
{
    ui->setupUi(this);
    ui->tableView->setModel(&m_model);
    // 设置不可以编辑
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    // 设置按行选中
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
}

Record::~Record()
{
    delete ui;
}

void Record::InitPage(QString condition)
{
    auto l = SqlMgr::GetInstance()->getRecords(condition);

    m_model.clear();
    m_model.setHorizontalHeaderLabels(QStringList{"记录id","图书id","图书名称","用户id","用户名称","开始时间","结束时间"});
    for (int i = 0 ;i < l.size(); i++) {
        QList<QStandardItem*> items;
        for (int j = 0; j < l[i].size(); j++) {
            items.append(new QStandardItem(l[i][j]));
        }
        m_model.appendRow(items);
    }
}

void Record::on_lineEdit_textChanged(const QString &arg1)
{
    QString condition = QString("where bookname like '%%1%'").arg(arg1);
    InitPage(condition);
}

void Record::on_btn_return_book_clicked()
{
    int r = ui->tableView->currentIndex().row();
    if (r < 0) {
        QMessageBox::information(nullptr, "信息", "无选中归还的图书");
    } else {
        auto recordid = m_model.item(r, 0)->text();
        auto bookid = m_model.item(r, 1)->text();
        auto bookname = m_model.item(r, 2)->text();
        //bool ret = SqlMgr::GetInstance()->BorrowBook(id);
        DlgBookBorrowReturn dlg;
        dlg.setWindowTitle("图书归还");
        dlg.SetRecordId(recordid.toInt());
        dlg.SetBookId(bookid.toInt());
        dlg.SetBookName(bookname);
        dlg.SetType(true);
        int ret = dlg.exec();
        if (-1 == ret) {
            return; // 退出
        }
        QMessageBox::information(nullptr, "信息", ret ? "归还成功" : "归还失败");
        InitPage();
    }
}

