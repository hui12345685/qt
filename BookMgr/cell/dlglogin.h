#ifndef DLGLOGIN_H
#define DLGLOGIN_H

#include <QDialog>

namespace Ui {
class DlgLogin;
}

class DlgLogin : public QDialog
{
    Q_OBJECT

public:
    explicit DlgLogin(QWidget *parent = nullptr);
    ~DlgLogin();

private slots:
    void on_btn_login_clicked();

    void on_btn_exit_clicked();

protected:
    // 重写keyPressEvent避免按回车执行退出对话框
    void keyPressEvent(QKeyEvent *event) override;
private:
    Ui::DlgLogin *ui;
};

#endif // DLGLOGIN_H
