#include "dlgbookborrowreturn.h"
#include "ui_dlgbookborrowreturn.h"

#include "lib/sqlmgr.h"

DlgBookBorrowReturn::DlgBookBorrowReturn(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DlgBookBorrowReturn)
    , m_bookid(-1)
    , m_recordid(-1)
    , m_isReturn(false)
{
    ui->setupUi(this);
}

DlgBookBorrowReturn::~DlgBookBorrowReturn()
{
    delete ui;
}

void DlgBookBorrowReturn::SetBookId(int bookid)
{
    m_bookid = bookid;
}

void DlgBookBorrowReturn::SetRecordId(int recordid)
{
    m_recordid = recordid;
}

void DlgBookBorrowReturn::SetType(bool isReturn)
{
    m_isReturn = isReturn;
    if (m_isReturn) {
        ui->btn_borrow_return->setText("归还");
    }
}

void DlgBookBorrowReturn::SetBookName(QString bookname)
{
    m_bookname = bookname;
    ui->lb_name->setText(bookname);
}

void DlgBookBorrowReturn::on_btn_canc_clicked()
{
    this->done(-1);
}

void DlgBookBorrowReturn::on_btn_borrow_return_clicked()
{
    // 判断用户名密码是否正确
    auto strUserName = ui->le_username->text();
    auto strPasswd = ui->le_passwd->text();
    int userId = -1;
    auto ok = SqlMgr::GetInstance()->Login(strUserName, strPasswd, userId);
    if (!ok) {
        this->done(0);
        return ;
    }

    if (m_isReturn) {
        // 归还
        SqlMgr::GetInstance()->ReturnBook(QString::number(m_bookid), QString::number(m_recordid));
    } else {
        // 借阅
        // 图书库层减1,并生成一条借阅记录
        SqlMgr::GetInstance()->BorrowBook(QString::number(userId), QString::number(m_bookid));
    }
    this->done(1);
}
