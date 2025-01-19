#ifndef SQLMGR_H
#define SQLMGR_H

#include <QString>
#include <QSqlDatabase>

class SqlMgr
{

public:
    static SqlMgr* GetInstance(){
        static SqlMgr sql_mgr;
        return &sql_mgr;
    }

    void Init();

    // 登录
    bool Login(QString& user, QString& passwd, int& userId);
    // 获取所有用户
    QVector<QStringList> getUsers(QString condition = "");
    // 添加用户
    bool AddUser(QVector<QStringList>);
    // 删除用户
    bool DelUser(QString strId);

    // 根据id获取图书
    QStringList GetBook(QString bookid);

    // 获取所有的图书
    QVector<QStringList> getBooks(QString condition = "");

    // 增加图书
    bool AddBook(QStringList);

    // 修改图书
    bool UpdateBook(QStringList);

    // 删除图书
    bool DelBook(QString strId);

    // 图书归还
    bool ReturnBook(QString strUserId, QString strBookId);

    // 图书借阅
    bool BorrowBook(QString strUserId, QString strBookId);

    // 获取借阅记录
    QVector<QStringList> getRecords(QString condition = "");

    // 清空借阅记录
    void ClearRecord();

private:
    SqlMgr();
    ~SqlMgr();
    SqlMgr(const SqlMgr&);
    SqlMgr& operator= (const SqlMgr&);

    QSqlDatabase m_db;
    QVector<QStringList> QueryExec(QString sql);
};

#endif // SQLMGR_H
