#ifndef RECORD_H
#define RECORD_H

#include <QWidget>
#include <QStandardItemModel>

namespace Ui {
class Record;
}

class Record : public QWidget
{
    Q_OBJECT

public:
    explicit Record(QWidget *parent = nullptr);
    ~Record();

    void InitPage(QString condition = "");

private slots:
    void on_lineEdit_textChanged(const QString &arg1);

    void on_btn_return_book_clicked();

private:
    Ui::Record *ui;

    QStandardItemModel m_model;
};

#endif // RECORD_H
