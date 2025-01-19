#ifndef DLGBOOKBORROWRETURN_H
#define DLGBOOKBORROWRETURN_H

#include <QDialog>

namespace Ui {
class DlgBookBorrowReturn;
}

class DlgBookBorrowReturn : public QDialog
{
    Q_OBJECT

public:
    explicit DlgBookBorrowReturn(QWidget *parent = nullptr);
    ~DlgBookBorrowReturn();

    void SetBookId(int bookid);
    void SetRecordId(int recordid);
    void SetType(bool isReturn);
    void SetBookName(QString bookname);
private slots:
    void on_btn_canc_clicked();
    void on_btn_borrow_return_clicked();

private:
    Ui::DlgBookBorrowReturn *ui;
    int m_bookid;
    int m_recordid;
    bool m_isReturn;
    QString m_bookname;
};

#endif // DLGBOOKBORROWRETURN_H
