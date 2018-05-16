//#if 0
#include "CAppDataBase.h"
#include <QtDebug>
#include <QDebug>
#include <QSqlError>
//#include <QFile>
namespace QTDUDU {

//CAppDataBase* CAppDataBase::m_pInstance = NULL;
CAppDataBase::CAppDataBase()
{

}

CAppDataBase::~CAppDataBase()
{
    if(m_db.isOpen())
    {
        m_db.close();
    }
    m_db.removeDatabase(m_db.connectionName());
}

//CAppDataBase *CAppDataBase::getInstance()
//{
//    if(m_pInstance == NULL)
//    {
//        m_pInstance = new CAppDataBase();
//    }
//    return m_pInstance;
//}

//void CAppDataBase::deleteInstance()
//{
//    if(m_pInstance != NULL)
//    {
//        delete m_pInstance;
//        m_pInstance = NULL;
//    }
//}

bool CAppDataBase::init(QString connectName, QString dbName, QString dbType)
{
    qDebug() << "database init...";
    m_db = QSqlDatabase::addDatabase(dbType, connectName);
    m_db.setDatabaseName(dbName);
    if( !m_db.open())
    {
        qDebug() << "can not open database ..."<<m_db.lastError();
        return false;
    }
    else
    {
    }
    m_query = QSqlQuery(m_db);
    return true;
}

void CAppDataBase::setServer(QString hostName, int port, QString usrName, QString userPwd)
{
    m_db.setHostName(hostName);
    m_db.setUserName(usrName);
    m_db.setPassword(userPwd);
    m_db.setPort(port);

}
/*
// 创建table
QString create_sql = "CREATE TABLE IF NOT EXISTS  history (songid VARCHAR PRIMARY KEY AUTOINCREMENT,"
                      "songname VARCHAR(30) NOT NULL,"
                      "singername VARCHAR(30) NULL,"
                      "singerid VARCHAR(10) NULL,"
                      "singerpicurl TEXT NULL,"
                      "playurl TEXT NULL,"
                      "topno TEXT NULL,"
                      "extraurl TEXT NULL,"
                      "score TEXT NULL,"
                      "cacheid TEXT NULL)";
*/
bool CAppDataBase::createTable(QString create_sql)
{
    //bool bCreate = QFile::exists(m_db.databaseName());
   qDebug() << "database createTable...";
   //if (bCreate)
   {
       if(m_query.exec(create_sql))
       {
           qDebug()<<"create table success ...";
           return true;
       }
       else
       {
           qDebug()<<"create table failed ..."<< m_query.lastError();
           return false;
       }
   }
}

/***
 *  // 插入数据sql
    QString insert_sql = "insert into history values (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
    // 插入数据
    sql_query.prepare(insert_sql);
    sql_query.addBindValue(1001);
    sql_query.addBindValue("忘情水");
    sql_query.addBindValue("刘德华");
    sql_query.addBindValue("10086");
    sql_query.addBindValue("pic.png");
    sql_query.addBindValue("http://wang.mp3");
    sql_query.addBindValue("11");
    sql_query.addBindValue("http://wangqingshui.mp3");
    sql_query.addBindValue("5");
    sql_query.addBindValue("11111");
 */
bool CAppDataBase::insert(QString insert_sql, QVector<QString> listData)
{
    qDebug() << "database insert...";
    m_query.prepare(insert_sql);
    for (int n = 0; n < listData.size(); n++ )
    {
        QString strData = listData.at(n);
        //qDebug()<<"listData:"<<strData;
        m_query.bindValue(n, listData.at(n));
    }

    if(m_query.exec())
    {
        qDebug()<<"insert data success ...";
        return true;
    }
    else
    {
        qDebug()<<"insert data failed ..."<<m_query.lastError();
        return false;
    }
}

/***
 * 更新数据
 * QString update_sql = "update history set songname = :songname where songid = :songid";
 * 说明: 条件控制在外面设置
 */
bool CAppDataBase::update(QString update_sql, QVector<QString> listData)
{
    m_query.prepare(update_sql);

    for (int n = 0; n < listData.size(); n++ )
    {
        QString strData = listData.at(n);
        qDebug()<<"listData:"<<strData;
        m_query.bindValue(n, listData.at(n));
    }

    if(m_query.exec())
    {
        qDebug()<<"update data success ...";
        return true;
    }
    else
    {
        qDebug()<<"update data failed ..."<<m_query.lastError();
        return false;
    }
}
/***
 * 查询数据
 * QString select_sql = "select songid, songname, singername, singerid, singerpicurl from history";
   QString select_all_sql = "select * from history";
 * 说明: 条件控制在外面设置
 */
bool CAppDataBase::select(QString select_sql)
{
    if(m_query.exec(select_sql))
    {
        return true;

    }
    else
    {
        return false;
    }
}

/***
 * 删除数据
 */
bool CAppDataBase::deleteData(QString delete_sql)
{
    if(m_query.exec(delete_sql))
    {
        qDebug()<<"delete data success ...";
        return true;
    }
    else
    {
        qDebug()<<"delete data failed ..."<<m_query.lastError();
        return false;
    }
}
/***
 * 关闭数据库
 */
void CAppDataBase::close()
{
    if(m_db.isOpen())
    {
        m_db.close();
    }
}
/***
 * 反初始化
 */
void CAppDataBase::unInit()
{
    close();
}

}// QTDUDU
//#endif
