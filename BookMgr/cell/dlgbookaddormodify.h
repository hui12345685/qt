#ifndef DLGBOOKADDORMODIFY_H
#define DLGBOOKADDORMODIFY_H

#include <QDialog>

namespace Ui {
class DlgBookAddOrModify;
}

class DlgBookAddOrModify : public QDialog
{
    Q_OBJECT

public:
    explicit DlgBookAddOrModify(QWidget *parent = nullptr);
    ~DlgBookAddOrModify();

    void SetType(int type);

private slots:
    void on_btn_ok_clicked();

    void on_btn_cancel_clicked();

private:
    Ui::DlgBookAddOrModify *ui;
    int m_id;
};

#endif // DLGBOOKADDORMODIFY_H
