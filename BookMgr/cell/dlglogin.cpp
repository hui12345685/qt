#include "dlglogin.h"
#include "ui_dlglogin.h"
#include "lib/sqlmgr.h"

#include <QMessageBox>
#include <QKeyEvent>

DlgLogin::DlgLogin(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DlgLogin)
{
    ui->setupUi(this);
    // 设置在用户名和密码编辑框里面输入回车都是调用登录按钮的功能
    // connect(ui->le_user_name ,SIGNAL(returnPressed()), ui->btn_login, SIGNAL(clicked()), Qt::UniqueConnection);
    // connect(ui->le_passwd ,SIGNAL(returnPressed()), ui->btn_login, SIGNAL(clicked()), Qt::UniqueConnection);

    // 设置光标默认选中的位置
    ui->le_user_name->setFocus();
}

DlgLogin::~DlgLogin()
{
    delete ui;
}

void DlgLogin::on_btn_login_clicked()
{
    int bookid;
    QString name = ui->le_user_name->text();
    QString passwd = ui->le_passwd->text();
    bool ret = SqlMgr::GetInstance()->Login(name, passwd, bookid);
    if (ret) {
        setResult(1);
        hide();
    } else {
        QMessageBox::information(nullptr, "信息", "用户名或者密码错误");
    }
}

void DlgLogin::on_btn_exit_clicked()
{
    setResult(0);
    hide();
}

// 重写keyPressEvent避免按回车执行退出对话框
void DlgLogin::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Return) {
        // 如果是回车键，不调用基类的处理函数，避免关闭对话框
        on_btn_login_clicked();
    } else {
        QDialog::keyPressEvent(event); // 对其他按键做默认处理
    }
}
