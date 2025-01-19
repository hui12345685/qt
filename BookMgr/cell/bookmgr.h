#ifndef BOOKMGR_H
#define BOOKMGR_H

#include <QWidget>
#include <QStandardItemModel>

namespace Ui {
class BookMgr;
}

class BookMgr : public QWidget
{
    Q_OBJECT

public:
    explicit BookMgr(QWidget *parent = nullptr);
    ~BookMgr();

    void InitPage(QString condition = "");

private slots:
    void on_btn_add_book_clicked();

    void on_btn_modify_book_clicked();

    void on_btn_delete_book_clicked();

    void on_btn_brorow_book_clicked();

    void on_le_search_book_textChanged(const QString &arg1);

private:
    Ui::BookMgr *ui;

    QStandardItemModel m_model;
};

#endif // BOOKMGR_H
