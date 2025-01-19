#include "cellmain.h"

#include <QApplication>
#include "dlglogin.h"
#include "lib/sqlmgr.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SqlMgr::GetInstance()->Init();
    DlgLogin dlg;
    int ret = dlg.exec();
    if (1 == ret) {
        CellMain w;
        w.show();
        return a.exec();
    }
    if (0 == ret) {
        exit(0);
        return 0;
    }
    return 0;
}
