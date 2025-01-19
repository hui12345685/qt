#ifndef USERMGR_H
#define USERMGR_H

#include <QWidget>
#include <QStandardItemModel>

namespace Ui {
class UserMgr;
}

class UserMgr : public QWidget
{
    Q_OBJECT

public:
    explicit UserMgr(QWidget *parent = nullptr);
    ~UserMgr();

    void InitPage(QString condition = "");

private slots:
    void on_btn_import_user_clicked();
    void on_btn_delete_user_clicked();
    void on_le_search_text_textChanged(const QString &arg1);

private:
    Ui::UserMgr *ui;
    QStandardItemModel m_model;
};

#endif // USERMGR_H
