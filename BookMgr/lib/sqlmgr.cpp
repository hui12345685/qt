#include "sqlmgr.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDateTime>

/*
CREATE DATABASE book;
ALTER DATABASE book CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;

CREATE TABLE `book` (
  `bookid` int(11) NOT NULL AUTO_INCREMENT,
  `bookname` varchar(100) COLLATE utf8mb4_unicode_ci NOT NULL,
  `count` int(11) DEFAULT NULL,
  `type1` varchar(10) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `type2` varchar(10) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `type3` varchar(10) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `price` double DEFAULT NULL,
  PRIMARY KEY (`bookid`)
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

CREATE TABLE `user` (
  `userid` int(11) NOT NULL AUTO_INCREMENT,
  `grade` varchar(100) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `department` varchar(100) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `auth` varchar(100) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `nickname` varchar(100) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `passwd` varchar(100) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `username` varchar(100) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  PRIMARY KEY (`userid`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

CREATE TABLE `record` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `bookid` int(11) DEFAULT NULL,
  `userid` int(11) DEFAULT NULL,
  `start` date DEFAULT NULL,
  `end` date DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `bookid` (`bookid`),
  KEY `userid` (`userid`),
  CONSTRAINT `record_ibfk_1` FOREIGN KEY (`bookid`) REFERENCES `book` (`bookid`),
  CONSTRAINT `record_ibfk_2` FOREIGN KEY (`userid`) REFERENCES `user` (`userid`)
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=latin1;

insert into book values(NULL, '西游记', 10, '历史', '人文', '', 19.9);
insert into book values(NULL, 'c++程序设计', 10, '计算机', 'c++', '', 29.9);

insert into user values(NULL, '1年1班', "计算机系", '学生', '李四', '123456', 'lisi');
insert into user values(NULL, '1年1班', "计算机系", '学生', '王五', '123456', 'wangwu');

select id, bookid, book.bookname, userid, user.username, start, end from record join book using(bookid) join user using(userid)
 */

void SqlMgr::Init()
{
    // 加载mysql驱动这里挺麻烦的，需要源码编译生成qsqlmysql.dll，参考：https://blog.csdn.net/qq_43414873/article/details/135653232
    // 编译qsqlmysql.dll没有博客上写的那么顺利，遇到问题需要自己修改【如果是新环境可以自己试一下】
    // 编译完成之后需要将生成的lib copy到某个目录，最麻烦的是编译过程中可能会报错（搞了一上午才搞定）
    m_db = QSqlDatabase::addDatabase("QMYSQL");
    m_db.setHostName("127.0.0.1");
    m_db.setDatabaseName("book");
    m_db.setUserName("root");
    m_db.setPassword("root");
    qDebug() << m_db.open();
}

bool SqlMgr::Login(QString &user, QString &passwd, int& userId)
{
    QSqlQuery q(m_db);
    QString strsql = QString("select * from user where username='%1' and passwd='%2'").arg(user).arg(passwd);
    bool ret = q.exec(strsql);
    if (!ret) {
        qDebug() << "login fail:" << q.lastError().text();
        return ret;
    }

    ret = q.next();
    if (ret) {
        userId = q.value(0).toInt(); // 获取到userid
    }

    return ret;
}

QVector<QStringList> SqlMgr::getUsers(QString condition)
{
    QString strsql = QString("select * from user %1").arg(condition);
    return QueryExec(strsql);
}

bool SqlMgr::AddUser(QVector<QStringList> items)
{
    m_db.transaction();
    QSqlQuery q(m_db);
    for (int row  = 0; row < items.size(); row++) {
        QString strsql = QString("insert into user values (NULL, '%1', '%2', '%3', '%4', '%5', '%6')").
                         arg(items[row][0]).arg(items[row][1]).arg(items[row][2]).arg(items[row][3]).
                         arg(items[row][4]).arg(items[row][5]);
        bool ret = q.exec(strsql);
        if (!ret) {
            qDebug() << q.lastError().text();
        }
    }
    m_db.commit();
    return true;
}

bool SqlMgr::DelUser(QString strId)
{
    QSqlQuery q(m_db);
    QString strsql = QString("delete from user where userid='%1'").arg(strId);
    bool ret = q.exec(strsql);
    if (!ret) {
        qDebug() << q.lastError().text();
    }
    return ret;
}

QStringList SqlMgr::GetBook(QString bookid)
{
    QString strsql = QString("select * from book where bookid=%1").arg(bookid);
    QVector<QStringList> res = QueryExec(strsql);
    if (res.empty()) {
        return QStringList();
    }
    return res[0];
}

QVector<QStringList> SqlMgr::getBooks(QString condition)
{
    QString strsql = QString("select * from book %1").arg(condition);
    return QueryExec(strsql);
}

bool SqlMgr::AddBook(QStringList line)
{
    if (line.isEmpty()) {
        return false;
    }

    QSqlQuery q(m_db);
    QString strsql = QString("insert into book "
                             "values (NULL, '%1',%2,'%3','%4','%5',%6)")
                         .arg(line[1]).arg(line[3])
                         .arg(line[4]).arg(line[5])
                         .arg(line[6]).arg(line[2]); // 应为db里面顺序没对上，所以这里不是按顺序的
    bool ret = q.exec(strsql);
    if (!ret) {
        qDebug() << q.lastError().text();
    }
    return ret;
}

bool SqlMgr::UpdateBook(QStringList line)
{
    if (line.size() != 7) {
        return false;
    }
    QSqlQuery q(m_db);
    QString strsql = QString("update book "
                             "set bookname='%1',count=%2,price=%3,type1='%4',type2='%5',type3='%6' "
                             "where bookid=%7")
                         .arg(line[1]).arg(line[2])
                         .arg(line[3]).arg(line[4])
                         .arg(line[5]).arg(line[6]).arg(line[0]);
    bool ret = q.exec(strsql);
    if (!ret) {
        qDebug() << q.lastError().text();
    }
    return ret;
}

bool SqlMgr::DelBook(QString strId)
{
    QSqlQuery q(m_db);
    QString strsql = QString("delete from book where bookid='%1'").arg(strId);
    bool ret = q.exec(strsql);
    if (!ret) {
        qDebug() << q.lastError().text();
    }
    return ret;
}

bool SqlMgr::ReturnBook(QString strBookId, QString strRecordId)
{
    QSqlQuery q(m_db);
    QString strsql = QString("update book set count=count+1 where bookid=%1;").arg(strBookId);
    bool ret = q.exec(strsql);
    if (!ret) {
        qDebug() << q.lastError().text();
        return ret;
    }

    strsql = QString("delete from record where id=%1").arg(strRecordId);
    ret = q.exec(strsql);
    if (!ret) {
        qDebug() << q.lastError().text();
    }
    return ret;
}

bool SqlMgr::BorrowBook(QString strUserId, QString strBookId)
{
    // 两条sql需要分两次执行
    QSqlQuery q(m_db);
    QString strsql = QString("update book set count=count-1 where bookid=%1;").arg(strBookId);
    bool ret = q.exec(strsql);
    if (!ret) {
        qDebug() << q.lastError().text();
        return ret;
    }

    QDate currentDate = QDate::currentDate();
    QString strCurDate = currentDate.toString("yyyy-MM-dd");
    QDate returnDate = QDate::currentDate().addDays(30);
    QString strReturnDate = returnDate.toString("yyyy-MM-dd");
    strsql = QString("insert into record values (null, %1, %2, '%3', '%4')")
                 .arg(strBookId).arg(strUserId)
                 .arg(strCurDate)
                 .arg(strReturnDate);
    ret = q.exec(strsql);
    if (!ret) {
        qDebug() << q.lastError().text();
    }
    return ret;
}

QVector<QStringList> SqlMgr::getRecords(QString condition)
{
    QString strsql = QString("select id, bookid, book.bookname, userid, user.username, start, end from record %1"
                             " join book using(bookid) join user using(userid) ").arg(condition);
    return QueryExec(strsql);
}

void SqlMgr::ClearRecord()
{
    /*QSqlQuery q(m_db);
    QString strsql = QString("delete from book;");
    bool ret = q.exec(strsql);
    if (!ret) {
        qDebug() << q.lastError().text();
    }*/
}

SqlMgr::SqlMgr() {}

SqlMgr::~SqlMgr() {}

QVector<QStringList> SqlMgr::QueryExec(QString strsql)
{
    QSqlQuery q(m_db);
    QVector<QStringList> vec;
    bool ret = q.exec(strsql);
    if (!ret) {
        qDebug() << q.lastError().text();
    } else {
        int cols = q.record().count(); // 列
        QStringList line;
        while (q.next()) {
            line.clear();
            for (int i = 0; i < cols; i++) {
                line << q.value(i).toString();
            }
            vec.push_back(line);
        }
    }
    return vec;
}

