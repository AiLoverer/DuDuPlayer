//#if 0
#ifndef CAPPDATABASE_H
#define CAPPDATABASE_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QVector>
#include <QVariant>

/************************************************************************************************
 * (1) 使用说明 ： .pro 添加： QT       += sql
 * (2) 不是线程安全 后续增加
*************************************************************************************************/

/**********参考语句********************************************************************************
QString create_sql      = "CREATE TABLE IF NOT EXISTS  history (songid INTEGER PRIMARY KEY AUTOINCREMENT,"
                          "songname VARCHAR(30) NOT NULL,"
                          "singername VARCHAR(30) NULL,"
                          "singerid VARCHAR(10) NULL,"
                          "singerpicurl TEXT NULL,"
                          "playurl TEXT NULL,"
                          "topno TEXT NULL,"
                          "extraurl TEXT NULL,"
                          "score TEXT NULL,"
                          "cacheid TEXT NULL)";
QString select_max_sql  = "select max(score) from history";
QString insert_sql      = "insert into history values (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
QString update_sql      = "update history set songname = :songname where songid = :songid";
QString select_sql      = "select songid, songname, singername, singerid, singerpicurl from history";
QString select_all_sql  = "select * from history";
QString delete_sql      = "delete from history where id = ?";
QString clear_sql       = "delete from history";
****************************************************************************************************/

/****************************************************************************************************
 * 使用例子 测试通过
 ****************************************************************************************************/

/*
QString create_sql = "CREATE TABLE IF NOT EXISTS  history (songid TEXT PRIMARY KEY,"\
                      "songname TEXT NOT NULL,"\
                      "singername TEXT NULL,"\
                      "singerid TEXT NULL,"\
                      "singerpicurl TEXT NULL,"\
                      "playurl TEXT NULL,"\
                      "topno TEXT NULL,"\
                      "extraurl TEXT NULL,"\
                      "score TEXT NULL,"\
                      "cacheid TEXT NULL)";
// 初始化
CAppDataBase db;
db.init("onelinemusic");

// 建表
db.createTable(create_sql);

// 插入
QString insert_sql = "insert into history values (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
QVector<QString> sqlListData;
sqlListData.append("1002");
sqlListData.append("忘情水");
sqlListData.append("刘德华");
sqlListData.append("10086");
sqlListData.append("pic.png");
sqlListData.append("http://wang.mp3");
sqlListData.append("11");
sqlListData.append("http://wangqingshui.mp3");
sqlListData.append("5");
sqlListData.append("11111");
db.insert(insert_sql, sqlListData);

// 更新
QString update_sql = "update history set songname = :songname where songid = '1002'";
QVector<QString> sqlUpdateData;
sqlUpdateData.append("薛之谦");
db.update(update_sql, sqlUpdateData);

// 查询
QString select_sql = "select songid, songname, singername, singerid, singerpicurl from history";
QSqlQuery query = db.select(select_sql);

while(query.next())
{
    QString songid          = query.value(0).toString();
    QString songname        = query.value(1).toString();
    QString singername      = query.value(2).toString();
    QString singerid        = query.value(3).toString();
    QString singerpicurl    = query.value(4).toString();
    qDebug()<<"songid: "<<songid <<"songname :"<<songname << "singername :"<<singername<<"singerid"<<singerid<<"singerpicurl :"<<singerpicurl;
}

// 删除
QString delete_sql      = "delete from history where songid = '1002'";
db.deleteData(delete_sql);
db.close();

*/
namespace QTDUDU {

#ifdef OS_WIN
#define DB_FILE_PATH "./hmi.db"
#else
#define DB_FILE_PATH "/fs/mmc1/appdata/HMI/hmi.db"
#endif
    class CAppDataBase : public QObject
    {
        Q_OBJECT

    public:

    public:
        CAppDataBase();
        ~CAppDataBase();

//        static CAppDataBase *m_pInstance;


    private:
        QSqlDatabase m_db;
        QSqlQuery    m_query;

//        static CAppDataBase *getInstance();
//        void deleteInstance();
    public:
        QSqlDatabase& DB() { return m_db; }
        QSqlQuery& Query() { return m_query; }
    public:

        // 初始化数据库
        bool init( QString connectName, QString dbName = DB_FILE_PATH, QString dbType = "QSQLITE" );
        // 远程服务设置
        void setServer( QString hostName = "localhost",int port = 8086,  QString usrName = "root", QString userPwd = "123456" );
        // 创建表
        bool createTable(QString create_sql);
        // 插入数据
        bool insert(QString insert_sql, QVector<QString> listData);
        // 更新数据
        bool update(QString update_sql, QVector<QString> listData);
        // 查询数据
        bool select(QString select_sql);
        // 删除数据
        bool deleteData(QString delete_sql);
        // 关闭数据库
        void close();
        // 反初始化
        void unInit();

    };

}


#endif // CAPPDATABASE_H
//#endif
