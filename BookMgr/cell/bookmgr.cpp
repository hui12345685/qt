#include "bookmgr.h"
#include "ui_bookmgr.h"
#include "lib/sqlmgr.h"
#include "dlgbookaddormodify.h"
#include <QMessageBox>
#include "dlgbookborrowreturn.h"

BookMgr::BookMgr(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::BookMgr)
{
    ui->setupUi(this);

    ui->tableView->setModel(&m_model);
    // 设置不可以编辑
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    // 设置按行选中
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
}

BookMgr::~BookMgr()
{
    delete ui;
}

void BookMgr::InitPage(QString condition)
{
    auto l = SqlMgr::GetInstance()->getBooks(condition);

    m_model.clear();
    m_model.setHorizontalHeaderLabels(QStringList{"图书id","书名","数量","类型1","类型2","类型3","价格"});
    for (int i = 0 ;i < l.size(); i++) {
        QList<QStandardItem*> items;
        for (int j = 0; j < l[i].size(); j++) {
            items.append(new QStandardItem(l[i][j]));
        }
        m_model.appendRow(items);
    }
}

void BookMgr::on_btn_add_book_clicked()
{
    DlgBookAddOrModify dlg;
    dlg.exec();
    InitPage();
}

void BookMgr::on_btn_modify_book_clicked()
{
    int r = ui->tableView->currentIndex().row();
    if (r < 0) {
        QMessageBox::information(nullptr, "信息", "无选中图书");
    } else {
        auto id = m_model.item(r, 0)->text();
        DlgBookAddOrModify dlg;
        dlg.SetType(id.toInt());
        dlg.exec();
        InitPage();
    }
}

void BookMgr::on_btn_delete_book_clicked()
{
    int r = ui->tableView->currentIndex().row();
    if (r < 0) {
        QMessageBox::information(nullptr, "信息", "无选中图书");
    } else {
        auto id = m_model.item(r, 0)->text();
        bool ret = SqlMgr::GetInstance()->DelBook(id);
        QMessageBox::information(nullptr, "信息", ret ? "删除成功" : "删除失败");
        InitPage();
    }
}

void BookMgr::on_btn_brorow_book_clicked()
{
    int r = ui->tableView->currentIndex().row();
    if (r < 0) {
        QMessageBox::information(nullptr, "信息", "无选中借阅的图书");
    } else {
        auto cnt = m_model.item(r, 2)->text();
        if (cnt.toInt() <= 0) {
            // 库层不足
            QMessageBox::information(nullptr, "信息", "借阅失败库存不足");
            return;
        }
        auto id = m_model.item(r, 0)->text();
        auto name = m_model.item(r, 1)->text();
        DlgBookBorrowReturn dlg;
        dlg.SetBookId(id.toInt());
        dlg.SetBookName(name);
        dlg.setWindowTitle("图书借阅");
        int ret = dlg.exec();
        if (-1 == ret) {
            return; // 退出
        }
        QMessageBox::information(nullptr, "信息", ret ? "借阅成功" : "借阅失败");
        if (ret) {
            InitPage();
        }
    }
}

void BookMgr::on_le_search_book_textChanged(const QString &arg1)
{
    QString condition =
        QString("where bookname like '%%1%' or type1 like '%%1%' or type2 like '%%1%' or type3 like '%%1%'").
                        arg(arg1);
    InitPage(condition);
}
