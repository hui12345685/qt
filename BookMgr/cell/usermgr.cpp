#include "usermgr.h"
#include "ui_usermgr.h"
#include "QFileDialog"
#include "lib/sqlmgr.h"
#include <QMessageBox>

UserMgr::UserMgr(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UserMgr)
{
    ui->setupUi(this);
    ui->tableView->setModel(&m_model);
    // 设置不可以编辑
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    // 设置按行选中
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    InitPage();
    /*for (int i = 0; i < 10; i++) {
        QList<QStandardItem*> items;
        items.append(new QStandardItem("1"));
        items.append(new QStandardItem("1年1班"));
        items.append(new QStandardItem("计算机系"));
        items.append(new QStandardItem("zhangsan"));
        items.append(new QStandardItem("123"));
        items.append(new QStandardItem("张三"));
        m_model.appendRow(items);
    }*/
}

UserMgr::~UserMgr()
{
    delete ui;
}

void UserMgr::InitPage(QString condition)
{
    // 查询数据并显示
    auto l = SqlMgr::GetInstance()->getUsers(condition);
    m_model.clear();
    m_model.setHorizontalHeaderLabels(QStringList{"用户id","年级","部门","权限","用户名","密码","昵称"});
    for (int i = 0 ;i < l.size(); i++) {
        QList<QStandardItem*> items;
        for (int j = 0; j < l[i].size(); j++) {
            items.append(new QStandardItem(l[i][j]));
        }
        m_model.appendRow(items);
    }
}

static QString ConvertToUtf8(QString strGbk) {
    // TODO
    return QString(strGbk);
}

// 导入用户
void UserMgr::on_btn_import_user_clicked()
{
    QString path = QFileDialog::getOpenFileName(nullptr, "输入文件路径");
    if (!path.isEmpty()) {
        QFile f(path);
        f.open(QFile::ReadOnly);
        QVector<QStringList> vecData;
        while (!f.atEnd()) {
            QString str = f.readLine();
            auto l = str.split(",");
            for (auto& it : l) {
                it = ConvertToUtf8(it);
            }
            if (l.size() != 6) {
                QMessageBox::information(nullptr, "信息", "导入失败");
                return;
            }
            l[l.size()-1] = l[l.size()-1].chopped(2);
            vecData.push_back(l);
        }

        if (!vecData.empty()) {
            SqlMgr::GetInstance()->AddUser(vecData);
        }

        InitPage();
    }
}

// 删除用户
void UserMgr::on_btn_delete_user_clicked()
{
    int r = ui->tableView->currentIndex().row();
    if (r < 0) {
        QMessageBox::information(nullptr, "信息", "无选中用户");
    } else {
        auto id = m_model.item(r, 0)->text();
        SqlMgr::GetInstance()->DelUser(id);
        InitPage();
    }
}

void UserMgr::on_le_search_text_textChanged(const QString &arg1)
{
    QString condition = QString("where username like '%%1%' or nickname like '%%1%'").arg(arg1);
    InitPage(condition);
}

