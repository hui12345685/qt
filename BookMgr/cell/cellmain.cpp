#include "cellmain.h"
#include "ui_cellmain.h"
#include <QPushButton>
#include <QDebug>

CellMain::CellMain(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CellMain)
    , m_book_mgr(nullptr)
    , m_user_mgr(nullptr)
    , m_record(nullptr)
{
    ui->setupUi(this);

    InitPage();
}

CellMain::~CellMain()
{
    delete ui;
}

void CellMain::InitPage()
{
    m_user_mgr = new UserMgr();
    m_book_mgr = new BookMgr();
    m_record = new Record();
    ui->stackedWidget->addWidget(m_user_mgr);
    ui->stackedWidget->addWidget(m_book_mgr);
    ui->stackedWidget->addWidget(m_record);
    ui->stackedWidget->setCurrentIndex(0);

    // 几个界面切换可以使用按钮对应的槽函数，也可以玩点高级的
    auto chd = ui->tools->children();
    for (auto it : chd) {
        if (it->objectName().contains("btn")) {
            connect(static_cast<QPushButton*>(it), &QPushButton::clicked, this, &CellMain::dealMenu);
        }
    }
    m_user_mgr->InitPage();
}

void CellMain::dealMenu() {
    qDebug() << sender()->objectName();
    auto str = sender()->objectName();
    if ("btn_user_mgr" == str) {
        ui->stackedWidget->setCurrentIndex(0);
        m_user_mgr->InitPage();
    } else if ("btn_book_mgr" == str) {
        ui->stackedWidget->setCurrentIndex(1);
        m_book_mgr->InitPage();
    } else if ("btn_history" == str) {
        ui->stackedWidget->setCurrentIndex(2);
        m_record->InitPage();
    }/* else {
        qDebug() << "unkown object" << sender()->objectName();
    }*/
}
