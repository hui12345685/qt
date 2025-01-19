#ifndef CELLMAIN_H
#define CELLMAIN_H

#include <QMainWindow>
#include "usermgr.h"
#include "bookmgr.h"
#include "record.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class CellMain;
}
QT_END_NAMESPACE

class CellMain : public QMainWindow
{
    Q_OBJECT

public:
    CellMain(QWidget *parent = nullptr);
    ~CellMain();

    void InitPage();

    void dealMenu();
private:
    Ui::CellMain *ui;

    BookMgr* m_book_mgr;
    UserMgr* m_user_mgr;
    Record* m_record;
};
#endif // CELLMAIN_H
