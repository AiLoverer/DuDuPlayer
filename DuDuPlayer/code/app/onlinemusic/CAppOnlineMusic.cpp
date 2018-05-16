#include "CAppOnlineMusic.h"
#define  TYPE_AUDIO    "audio"
namespace QTDUDU {

CAppOnlineMusic * CAppOnlineMusic::m_pInstance = NULL;

void CAppOnlineMusic::getHotData()
{
    emit sigForUpdateOnlineMusicTopTypeData(m_onlineMusicTopTypeList);
}

CAppOnlineMusic::CAppOnlineMusic()
{
  // connect( CService::media(), SIGNAL(rspPlayOnline(int,const QString&)), this, SLOT(slotForRspPlayOnlineMusic(int, const QString&)) );
  // connect( CService::media(), SIGNAL(rspPauseOnline(int,const QString&)), this, SLOT(slotForRspPauseOnlineMusic(int, const QString&)) );
  // connect( CService::media(), SIGNAL(rspResumeOnline(int,const QString&)), this, SLOT(slotForRspResumeOnlineMusic(int, const QString&)) );
  // connect( CService::media(), SIGNAL(rspStopOnline(int,const QString&)), this, SLOT(slotForRspStopOnlineMusic(int, const QString&)) );


   connect( CNetworkOnlineServer::getInstance(), SIGNAL(sigGetMusicTop(QString&)), this, SLOT(slotForRspGetOnlineMusicTopType(QString&)) );
   connect( CNetworkOnlineServer::getInstance(), SIGNAL(sigGetMusicSinger(QString&)), this, SLOT(slotForRspGetOnlineMusicSingerTypeName(QString&)) );
   connect( CNetworkOnlineServer::getInstance(), SIGNAL(sigGetMusicTag(QString&)), this, SLOT(slotForRspGetOnlineMusicTag(QString&)) );
   connect( CNetworkOnlineServer::getInstance(), SIGNAL(sigGetMusicRadio(QString&)), this, SLOT(slotForRspGetOnlineMusicRadio(QString&)) );
   connect( CNetworkOnlineServer::getInstance(), SIGNAL(sigGetTopMusic(QString&)), this, SLOT(slotForRspGetOnlineMusicTopnameMusicData(QString&)) );
   connect( CNetworkOnlineServer::getInstance(), SIGNAL(sigSearchMusic(QString&)), this, SLOT(slotForRspGetOnlineMusicTopnameMusicData(QString&)) );

   // get top
   /*
   //qDebug()<<"in getOnlineMusicType ...";
   CData_GetMusicType dataTop;
   dataTop.type = ONLINEMUSIC_TYPE_TOP;
   CData_GetMusicType dataSinger;
   dataSinger.type = ONLINEMUSIC_TYPE_SINGERTYPENAME;
   CData_GetMusicType dataTag;
   dataTag.type = ONLINEMUSIC_TYPE_TAG;
   CData_GetMusicType dataRadio;
   dataRadio.type = ONLINEMUSIC_TYPE_RADIO;
   */
   //CService::onlinemusic()->getMusicTop(dataTop);
   //CService::onlinemusic()->getMusicSinger(dataSinger);
   //CService::onlinemusic()->getMusicTag(dataTag);
   //CService::onlinemusic()->getMusicRadio(dataRadio);

   m_bCollected                 = false;
   m_bPlaying                   = false;
   m_nCurrentMusicIndex         = 0;
   m_nCurrentSearchedMusicIndex = 0;
   m_musicMode                  = TYPE_TOPMUSIC;

   // init database
   m_db.init("onlinemusic");
   QString create_table_history_sql = "CREATE TABLE IF NOT EXISTS  onlinemusic_history (songid TEXT PRIMARY KEY,"\
                         "songname TEXT NOT NULL,"\
                         "singername TEXT NULL,"\
                         "singerid TEXT NULL,"\
                         "singerpicurl TEXT NULL,"\
                         "playurl TEXT NULL,"\
                         "lyricUrl TEXT NULL,"\
                         "topno TEXT NULL,"\
                         "extraurl TEXT NULL,"\
                         "score TEXT NULL,"\
                         "cacheid TEXT NULL)";
   QString create_table_collect_sql = "CREATE TABLE IF NOT EXISTS  onlinemusic_collect (songid TEXT PRIMARY KEY,"\
                         "songname TEXT NOT NULL,"\
                         "singername TEXT NULL,"\
                         "singerid TEXT NULL,"\
                         "singerpicurl TEXT NULL,"\
                         "playurl TEXT NULL,"\
                         "lyricUrl TEXT NULL,"\
                         "topno TEXT NULL,"\
                         "extraurl TEXT NULL,"\
                         "score TEXT NULL,"\
                         "cacheid TEXT NULL)";
   // create table : history and collect
   m_db.createTable(create_table_history_sql);
   m_db.createTable(create_table_collect_sql);

}

CAppOnlineMusic::~CAppOnlineMusic()
{
    m_db.unInit();
}

void CAppOnlineMusic::filterDataForOnlineMusicTopType(CRspOnlineMusicTypeVector &data)
{
    //qDebug()<<"in filterDataForOnlineMusicTopType...";
    m_onlineMusicTopTypeList.clear();
    if(data.onlineMusicList.size() <= 0)
    {
        ////qDebug()<<"data is null";
        return;
    }
    for(int i = 0; i < data.onlineMusicList.size(); i++)
    {
        HData_OnlineMusicType info;
        info.strType    = data.onlineMusicList.at(i).strType;
        info.strName    = data.onlineMusicList.at(i).strName;
        info.strPicUrl  = data.onlineMusicList.at(i).strPicUrl;

        m_onlineMusicTopTypeList.append(info);
    }
    //qDebug()<<"filterDataForOnlineMusicTopType: music type list size : "<< m_onlineMusicTopTypeList.size();
    emit sigForUpdateOnlineMusicTopTypeData(m_onlineMusicTopTypeList);
    emit sigQMLGetMusicTypeTopDataComplete();
}

void CAppOnlineMusic::filterDataForOnlineMusicSingerType(CRspOnlineMusicTypeVector &data)
{
    //qDebug()<<"in filterDataForOnlineMusicTopType...";
    m_onlineMusicSingerTypeList.clear();
    if(data.onlineMusicList.size() <= 0)
    {
        //qDebug()<<"data is null";
        return;
    }
    for(int i = 0; i < data.onlineMusicList.size(); i++)
    {
        HData_OnlineMusicType info;
        info.strType    = data.onlineMusicList.at(i).strType;
        info.strPicUrl  = data.onlineMusicList.at(i).strPicUrl;

        m_onlineMusicSingerTypeList.append(info);
    }
    //qDebug()<<"filterDataForOnlineMusicTopType: music type list size : "<< m_onlineMusicTopTypeList.size();
    emit sigForUpdateOnlineMusicSingerTypeData(m_onlineMusicSingerTypeList);
}

void CAppOnlineMusic::filterDataForOnlineMusicTagType(CRspOnlineMusicTypeVector &data)
{
    m_onlineMusicSenceTypeList.clear();
    m_onlineMusicEmotionTypeList.clear();
    m_onlineMusicStyleTypeList.clear();
    m_onlineMusicYearsTypeList.clear();
    m_onlineMusicLanguageTypeList.clear();
    if(data.onlineMusicList.size() <= 0) return;

    //qDebug()<<"data.onlineMusicList.size()"<<data.onlineMusicList.size();
    for(int i = 0; i < data.onlineMusicList.size(); i++)
    {
        //qDebug()<<"data.onlineMusicList.at(i).strType:" << data.onlineMusicList.at(i).strType ;
        //qDebug()<<"data.onlineMusicList.at(i).subTypeInfoList.size()"<<data.onlineMusicList.at(i).subTypeInfoList.size();
        for(int j = 0; j < data.onlineMusicList.at(i).subTypeInfoList.size(); j++)
        {
            HData_OnlineMusicType info;
            info.strType    = data.onlineMusicList.at(i).subTypeInfoList.at(j).strType;
            info.strPicUrl  = data.onlineMusicList.at(i).subTypeInfoList.at(j).strPicUrl;
            //qDebug()<<"filterDataForOnlineMusicTagType: info.strType" << info.strType ;
            if(data.onlineMusicList.at(i).strType.compare("场景") == 0 )
            {
                m_onlineMusicSenceTypeList.append(info);
            }
            else if (data.onlineMusicList.at(i).strType.compare("情感") == 0)
            {
                m_onlineMusicEmotionTypeList.append(info);
            }
            else if(data.onlineMusicList.at(i).strType.compare("风格") == 0)
            {
                m_onlineMusicStyleTypeList.append(info);
            }
            else if(data.onlineMusicList.at(i).strType.compare("年代") == 0)
            {
                m_onlineMusicYearsTypeList.append(info);
            }
            else if (data.onlineMusicList.at(i).strType.compare("语种") == 0)
            {
                m_onlineMusicLanguageTypeList.append(info);
            }
        }

    }

    //qDebug()<<" sence list size :"<<m_onlineMusicSenceTypeList.size();
    //qDebug()<<" emotin list size :"<<m_onlineMusicEmotionTypeList.size();
    //qDebug()<<" singer list size :"<<m_onlineMusicStyleTypeList.size();
    //qDebug()<<" style list size :"<<m_onlineMusicYearsTypeList.size();
    //qDebug()<<" language list size :"<<m_onlineMusicLanguageTypeList.size();

    emit sigForUpdateOnlineMusicSenceData(m_onlineMusicSenceTypeList);
    emit sigForUpdateOnlineMusicEmotionData(m_onlineMusicEmotionTypeList);
    emit sigForUpdateOnlineMusicStyleData(m_onlineMusicStyleTypeList);
    emit sigForUpdateOnlineMusicYearsData(m_onlineMusicYearsTypeList);
    emit sigForUpdateOnlineMusicLanguageData(m_onlineMusicLanguageTypeList);
}

void CAppOnlineMusic::filterDataForOnlineMusicRadioType(CRspOnlineMusicTypeVector &data)
{
    //qDebug()<<"in filterDataForOnlineMusicRadioType";
    m_onlineMusicSenceTypeList.clear();
    m_onlineMusicEmotionTypeList.clear();
    m_onlineMusicStyleTypeList.clear();
    m_onlineMusicYearsTypeList.clear();
    m_onlineMusicLanguageTypeList.clear();
    if(data.onlineMusicList.size() <= 0) return;

    for(int i = 0; i < data.onlineMusicList.size(); i++)
    {

        for(int j = 0; j < data.onlineMusicList.at(i).subTypeInfoList.size(); j++)
        {
            HData_OnlineMusicType info;
            info.strType    = data.onlineMusicList.at(i).subTypeInfoList.at(j).strType;
            info.strPicUrl  = data.onlineMusicList.at(i).subTypeInfoList.at(j).strPicUrl;

            //qDebug()<<"info,strType : "<< info.strType;
            //qDebug()<<"info,strPicUrl : "<< info.strPicUrl;

            if(data.onlineMusicList.at(i).strType.compare("场景") == 0 )
            {
                m_onlineMusicSenceTypeList.append(info);
            }
            else if (data.onlineMusicList.at(i).strType.compare("情感") == 0)
            {
                m_onlineMusicEmotionTypeList.append(info);
            }
            else if(data.onlineMusicList.at(i).strType.compare("风格") == 0)
            {
                m_onlineMusicStyleTypeList.append(info);
            }
            else if(data.onlineMusicList.at(i).strType.compare("年代") == 0)
            {
                m_onlineMusicYearsTypeList.append(info);
            }
            else if (data.onlineMusicList.at(i).strType.compare("语种") == 0)
            {
                m_onlineMusicLanguageTypeList.append(info);
            }
        }
    }
    emit sigForUpdateOnlineMusicSenceData(m_onlineMusicSenceTypeList);
    emit sigForUpdateOnlineMusicEmotionData(m_onlineMusicEmotionTypeList);
    emit sigForUpdateOnlineMusicStyleData(m_onlineMusicStyleTypeList);
    emit sigForUpdateOnlineMusicYearsData(m_onlineMusicYearsTypeList);
    emit sigForUpdateOnlineMusicLanguageData(m_onlineMusicLanguageTypeList);
}

void CAppOnlineMusic::filterDataForOnlineMusicTopnameMusicData(CRspOnlineMusicTopnameMusicDataVector &data)
{
    m_onlineMusicTopnameMusicData.clear();
    for( int i = 0; i < data.ol_topnamemusicdatalist.size(); i++)
    {
        HData_OnlineMusicTopnameMusicData ol_topnameMusicData;
        ol_topnameMusicData.strSongName         = data.ol_topnamemusicdatalist.at(i).strSongName;
        ol_topnameMusicData.strSongID           = data.ol_topnamemusicdatalist.at(i).strSongID;
        ol_topnameMusicData.strSingerName       = data.ol_topnamemusicdatalist.at(i).strSingerName;
        ol_topnameMusicData.strSingerID         = data.ol_topnamemusicdatalist.at(i).strSingerID;
        ol_topnameMusicData.strSingerPicUrl     = data.ol_topnamemusicdatalist.at(i).strSingerPicUrl;
        ol_topnameMusicData.strLyricUrl         = data.ol_topnamemusicdatalist.at(i).strLyricUrl;
        ol_topnameMusicData.strPlayUrl          = data.ol_topnamemusicdatalist.at(i).strPlayUrl;
        ol_topnameMusicData.strExtraUrl          = data.ol_topnamemusicdatalist.at(i).strExtraUrl;
        ol_topnameMusicData.strScore            = data.ol_topnamemusicdatalist.at(i).strScore;
        ol_topnameMusicData.strCacheID          = data.ol_topnamemusicdatalist.at(i).strCacheID;
        ol_topnameMusicData.strTopNo            = data.ol_topnamemusicdatalist.at(i).strTopNo;
        m_onlineMusicTopnameMusicData.append(ol_topnameMusicData);
    }

    if(m_musicMode == TYPE_SEARCHMUSIC)
    {
        emit sigQMLSearchMusic(true);
        sigForUpdateOnlineMusicSearchedMusicData(m_onlineMusicTopnameMusicData);
    }
    else if(m_musicMode == TYPE_TOPMUSIC)
    {
        emit sigForUpdateOnlineMusicTopnameMusicData(m_onlineMusicTopnameMusicData);
    }
}

//void CAppOnlineMusic::filterDataForOnlineMusicSearchedMusicData(CRspOnlineMusicTopnameMusicDataVector &data)
//{
//    //qDebug()<<"filterDataForOnlineMusicSearchedMusicData";
//    m_onlineMusicSearchedMusicData.clear();
//    for( int i = 0; i < data.ol_topnamemusicdatalist.size(); i++)
//    {
//        HData_OnlineMusicTopnameMusicData ol_topnameMusicData;
//        ol_topnameMusicData.strSongName     = data.ol_topnamemusicdatalist.at(i).strSongName;
//        ol_topnameMusicData.strSongID     = data.ol_topnamemusicdatalist.at(i).strSongID;
//        ol_topnameMusicData.strSingerName     = data.ol_topnamemusicdatalist.at(i).strSingerName;
//        ol_topnameMusicData.strSingerID     = data.ol_topnamemusicdatalist.at(i).strSingerID;
//        ol_topnameMusicData.strSingerPicUrl     = data.ol_topnamemusicdatalist.at(i).strSingerPicUrl;
//        ol_topnameMusicData.strLyricUrl     = data.ol_topnamemusicdatalist.at(i).strLyricUrl;
//        ol_topnameMusicData.strPlayUrl     = data.ol_topnamemusicdatalist.at(i).strPlayUrl;
//        ol_topnameMusicData.strExtraUrl     = data.ol_topnamemusicdatalist.at(i).strExtraUrl;
//        ol_topnameMusicData.strScore     = data.ol_topnamemusicdatalist.at(i).strScore;
//        ol_topnameMusicData.strCacheID     = data.ol_topnamemusicdatalist.at(i).strCacheID;
//        ol_topnameMusicData.strTopNo     = data.ol_topnamemusicdatalist.at(i).strTopNo;
//        m_onlineMusicSearchedMusicData.append(ol_topnameMusicData);
//    }

//    emit sigForUpdateOnlineMusicSearchedMusicData(m_onlineMusicSearchedMusicData);
//    emit sigQMLSearchMusic(true);

//}

void CAppOnlineMusic::searchSingerList()
{

}

void CAppOnlineMusic::selectMusicIsCollected(QString strSongId)
{
    if(m_nCurrentMusicIndex < 0) return;

    //-----------------------------------------------------------------------------------------------
    // select music is collected from onlinemusic_collect table
    //-----------------------------------------------------------------------------------------------
    QString str = QString("select count(*) from onlinemusic_collect where songid = '%1'").arg(strSongId.toInt());
    if(m_db.Query().exec(str))
    {
       m_db.Query().next();
       int count = m_db.Query().value(0).toInt();
       if(count == 0)
       {
           m_bCollected = false;

       }
       else
       {
           m_bCollected = true;
       }
       emit sigQMLbCollected(strSongId, m_bCollected);
    }
}

CAppOnlineMusic *CAppOnlineMusic::getInstance()
{
    if ( m_pInstance == NULL )
    {
        m_pInstance = new CAppOnlineMusic;
    }
    return m_pInstance;
}

void CAppOnlineMusic::deleteInstance()
{
    if ( m_pInstance != NULL )
    {
        delete m_pInstance;
        m_pInstance = NULL;
    }
}

bool CAppOnlineMusic::isPlaying()
{
    return m_bPlaying;
}

void CAppOnlineMusic::pause()
{
    //CService::media()->PauseOnline(TYPE_AUDIO);
}

void CAppOnlineMusic::resume()
{
    //CService::media()->ResumeOnline(TYPE_AUDIO);
}

void CAppOnlineMusic::stop()
{
    //CService::media()->StopOnline(TYPE_AUDIO);
}

void CAppOnlineMusic::next()
{
    //qDebug()<<"next ...";
    if( m_nCurrentMusicIndex + 1 <=  m_onlineMusicTopnameMusicData.size() )
    {
        m_nCurrentMusicIndex++;
        playMusic(m_nCurrentMusicIndex);
    }
}

void CAppOnlineMusic::previous()
{
    if( m_nCurrentMusicIndex - 1 < m_onlineMusicTopnameMusicData.size()  &&  (m_nCurrentMusicIndex - 1) >= 0)
    {
        m_nCurrentMusicIndex--;
        playMusic(m_nCurrentMusicIndex);
    }
}

void CAppOnlineMusic::searchMusicByKeyWords(QString strKey)
{
    m_musicMode = TYPE_SEARCHMUSIC;
    m_nCurrentMusicIndex = 0;
    CData_SearchMusic data;
    data.words = strKey;
    CNetworkOnlineServer::getInstance()->searchMusic(data);

}

void CAppOnlineMusic::searchMusicDetailDataBySongName(QString strSongName)
{
    CData_GetMusicDetail data;
    data.songName = strSongName;
    CNetworkOnlineServer::getInstance()->getMusicDetail(data);

}

void CAppOnlineMusic::searchMusicAlbumDataByAlbumName(QString strAlbumName)
{
    CData_SearchAlbum data;
    data.words = strAlbumName;
    CNetworkOnlineServer::getInstance()->searchAlbum(data);

}

void CAppOnlineMusic::collectMusic(int nIndex)
{
    if(m_nCurrentMusicIndex < 0 || nIndex < 0) return;

    //-----------------------------------------------------------------------------------------------
    // add info to onlinemusic_collect table
    //-----------------------------------------------------------------------------------------------
    QString str = QString("select count(*) from onlinemusic_collect where songid = '%1'").arg(m_onlineMusicTopnameMusicData.at(m_nCurrentMusicIndex).strSongID);
    if(m_db.Query().exec(str))
    {
       m_db.Query().next();
       int count = m_db.Query().value(0).toInt();
       //qDebug()<<"collectMusic: ..." + count;
       if(count <= 0)
       {
           //qDebug()<<"collected...";
           QString insert_sql = "insert into onlinemusic_collect values (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
           QVector<QString> sqlListData;
           sqlListData.append(m_onlineMusicTopnameMusicData.at(m_nCurrentMusicIndex).strSongID);
           sqlListData.append(m_onlineMusicTopnameMusicData.at(m_nCurrentMusicIndex).strSongName);
           sqlListData.append(m_onlineMusicTopnameMusicData.at(m_nCurrentMusicIndex).strSingerName);
           sqlListData.append(m_onlineMusicTopnameMusicData.at(m_nCurrentMusicIndex).strSingerID);
           sqlListData.append(m_onlineMusicTopnameMusicData.at(m_nCurrentMusicIndex).strSingerPicUrl);
           sqlListData.append(m_onlineMusicTopnameMusicData.at(m_nCurrentMusicIndex).strPlayUrl);
           sqlListData.append(m_onlineMusicTopnameMusicData.at(m_nCurrentMusicIndex).strLyricUrl);
           sqlListData.append(m_onlineMusicTopnameMusicData.at(m_nCurrentMusicIndex).strTopNo);
           sqlListData.append(m_onlineMusicTopnameMusicData.at(m_nCurrentMusicIndex).strExtraUrl);
           sqlListData.append(m_onlineMusicTopnameMusicData.at(m_nCurrentMusicIndex).strScore);
           sqlListData.append(m_onlineMusicTopnameMusicData.at(m_nCurrentMusicIndex).strCacheID);
           if(m_db.insert(insert_sql, sqlListData))
           {
              m_bCollected = true;
              HData_OnlineMusicTopnameMusicData ol_CollectData;
              ol_CollectData.strSongID              = m_onlineMusicTopnameMusicData.at(m_nCurrentMusicIndex).strSongID;
              ol_CollectData.strSongName            = m_onlineMusicTopnameMusicData.at(m_nCurrentMusicIndex).strSongName;
              ol_CollectData.strSingerName          = m_onlineMusicTopnameMusicData.at(m_nCurrentMusicIndex).strSingerName;
              ol_CollectData.strSingerID            = m_onlineMusicTopnameMusicData.at(m_nCurrentMusicIndex).strSingerID;
              ol_CollectData.strSingerPicUrl        = m_onlineMusicTopnameMusicData.at(m_nCurrentMusicIndex).strSingerPicUrl;
              ol_CollectData.strPlayUrl             = m_onlineMusicTopnameMusicData.at(m_nCurrentMusicIndex).strPlayUrl;
              //ol_CollectData.strLyricUrl            = m_onlineMusicTopnameMusicData.at(m_nCurrentMusicIndex).strLyricUrl;
              //ol_CollectData.strTopNo               = m_onlineMusicTopnameMusicData.at(m_nCurrentMusicIndex).strTopNo;
              //ol_CollectData.strExtraUrl            = m_onlineMusicTopnameMusicData.at(m_nCurrentMusicIndex).strExtraUrl;
              //ol_CollectData.strScore               = m_onlineMusicTopnameMusicData.at(m_nCurrentMusicIndex).strScore;
              //ol_CollectData.strCacheID             = m_onlineMusicTopnameMusicData.at(m_nCurrentMusicIndex).strCacheID;
              m_onlineMusicCollectyData.append(ol_CollectData);
              emit sigForUpdateOnlineMusicCollectData(m_onlineMusicCollectyData);
              emit sigQMLCollectDataChanged(m_onlineMusicCollectyData.size());
           }
           else
           {
              //qDebug()<<" 收藏失败...";
           }

       }
       else
       {
           //qDebug()<<"discollect...";
            QString delete_sql      = QString("delete from onlinemusic_collect where songid = '%1'").arg(m_onlineMusicTopnameMusicData.at(m_nCurrentMusicIndex).strSongID);
            if(m_db.deleteData(delete_sql))
            {
                m_bCollected = false;
                m_onlineMusicCollectyData.removeAt(nIndex);
                emit sigForUpdateOnlineMusicCollectData(m_onlineMusicCollectyData);
                emit sigQMLCollectDataChanged(m_onlineMusicCollectyData.size());
            }
            else
            {
                //qDebug()<<"取消收藏失败...";
            }

       }
       emit sigQMLbCollected(m_onlineMusicTopnameMusicData.at(m_nCurrentMusicIndex).strSongID, m_bCollected);
    }
    else
    {

    }
}

void CAppOnlineMusic::enterPersonalCenter()
{
    m_onlineMusicCollectyData.clear();
    m_onlineMusicHistoryData.clear();
    // collect table
    QString select_collect_sql = QString("select songid, songname, singername, singerid, singerpicurl, playurl from onlinemusic_collect");
    if(m_db.select(select_collect_sql))
    {
        while(m_db.Query().next())
        {
            HData_OnlineMusicTopnameMusicData collectMusicData;
            collectMusicData.strSongID          = m_db.Query().value(0).toString();
            collectMusicData.strSongName        = m_db.Query().value(1).toString();
            collectMusicData.strSingerName      = m_db.Query().value(2).toString();
            collectMusicData.strSingerID        = m_db.Query().value(3).toString();
            collectMusicData.strSingerPicUrl    = m_db.Query().value(4).toString();
            collectMusicData.strPlayUrl         = m_db.Query().value(5).toString();
            m_onlineMusicCollectyData.append(collectMusicData);
        }

        emit sigForUpdateOnlineMusicCollectData(m_onlineMusicCollectyData);
        emit sigQMLCollectDataChanged(m_onlineMusicCollectyData.size());
    }

    // history table
    QString select_history_sql = QString("select songid, songname, singername, singerid, singerpicurl, playurl from onlinemusic_history");
    if(m_db.select(select_history_sql))
    {

        while(m_db.Query().next())
        {
            HData_OnlineMusicTopnameMusicData historyMusicData;
            historyMusicData.strSongID          = m_db.Query().value(0).toString();
            historyMusicData.strSongName        = m_db.Query().value(1).toString();
            historyMusicData.strSingerName      = m_db.Query().value(2).toString();
            historyMusicData.strSingerID        = m_db.Query().value(3).toString();
            historyMusicData.strSingerPicUrl    = m_db.Query().value(4).toString();
            historyMusicData.strPlayUrl         = m_db.Query().value(5).toString();
            m_onlineMusicHistoryData.append(historyMusicData);
        }
        emit sigForUpdateOnlineMusicHistoryData(m_onlineMusicHistoryData);
        emit sigQMLHistoryDataChanged(m_onlineMusicHistoryData.size());

    }


}

void CAppOnlineMusic::deleteCollectMusic(int nIndex)
{
    if(nIndex > m_onlineMusicCollectyData.size() || nIndex < 0) return;
    QString delete_sql      = QString("delete from onlinemusic_collect where songid = '%1'").arg(m_onlineMusicCollectyData.at(nIndex).strSongID);
    if(m_db.deleteData(delete_sql))
    {
        //qDebug()<<"m_onlineMusicCollectyData size :"<<m_onlineMusicCollectyData.size();
        m_onlineMusicCollectyData.removeAt(nIndex);
        //qDebug()<<"m_onlineMusicCollectyData size :"<<m_onlineMusicCollectyData.size();
        emit sigForUpdateOnlineMusicCollectData(m_onlineMusicCollectyData);
        emit sigQMLCollectDataChanged(m_onlineMusicCollectyData.size());
        emit sigQMLbCollected(m_onlineMusicCollectyData.at(nIndex).strSongID, false);
    }

}

void CAppOnlineMusic::deleteHistoryMusic(int nIndex)
{
    if(nIndex > m_onlineMusicHistoryData.size() || nIndex < 0) return;
    QString delete_sql      = QString("delete from onlinemusic_history where songid = '%1'").arg(m_onlineMusicHistoryData.at(nIndex).strSongID);
    if(m_db.deleteData(delete_sql))
    {
        //qDebug()<<"m_onlineMusicHistoryData size :"<<m_onlineMusicHistoryData.size();
        m_onlineMusicHistoryData.removeAt(nIndex);
        //qDebug()<<"m_onlineMusicHistoryData size :"<<m_onlineMusicHistoryData.size();
        emit sigForUpdateOnlineMusicHistoryData(m_onlineMusicHistoryData);
        emit sigQMLHistoryDataChanged(m_onlineMusicHistoryData.size());
    }
}

void CAppOnlineMusic::deleteAllCollectMusic()
{
    QString delete_sql      = QString("delete from onlinemusic_collect");
    if(m_db.deleteData(delete_sql))
    {
        //qDebug()<<"m_onlineMusicCollectyData size :"<<m_onlineMusicCollectyData.size();
        m_onlineMusicCollectyData.clear();
        //qDebug()<<"m_onlineMusicCollectyData size :"<<m_onlineMusicCollectyData.size();
        emit sigForUpdateOnlineMusicCollectData(m_onlineMusicCollectyData);
        emit sigQMLCollectDataChanged(m_onlineMusicCollectyData.size());
    }
}

void CAppOnlineMusic::deleteAllHistoryMusic()
{
    QString delete_sql      = QString("delete from onlinemusic_history");
    if(m_db.deleteData(delete_sql))
    {
        //qDebug()<<"m_onlineMusicHistoryData size :"<<m_onlineMusicHistoryData.size();
        m_onlineMusicHistoryData.clear();
        //qDebug()<<"m_onlineMusicHistoryData size :"<<m_onlineMusicHistoryData.size();
        emit sigForUpdateOnlineMusicHistoryData(m_onlineMusicHistoryData);
        emit sigQMLHistoryDataChanged(m_onlineMusicHistoryData.size());
    }
}

void CAppOnlineMusic::slotForRspPlayOnlineMusic(int code, const QString &description)
{
    if(code == 0)
    {
        //qDebug()<<"get rspPlayOnline ...";
        m_bPlaying        = true;
        //qDebug()<<"songname : "<< m_strSongName;
        //qDebug()<<"m_strSingerName : "<< m_strSingerName;
    }
    else
    {
        m_bPlaying        = false;
        //qDebug()<<description;
    }
    emit sigQMLMusicPlayingInfo(m_strSongName, m_strSingerName, m_strSingerPicUrl, m_bPlaying);
    //qDebug()<<"get rspPlayOnline error ...";
}

void CAppOnlineMusic::slotForRspPauseOnlineMusic(int code, const QString &description)
{
    if(code == 0)
    {
        //qDebug()<<"get rspPauseOnline ...";
        //qDebug()<<description;
        m_bPlaying = false;
        emit sigQMLMusicPlayingInfo(m_strSongName, m_strSingerName, m_strSingerPicUrl, m_bPlaying);
    }
}

void CAppOnlineMusic::slotForRspResumeOnlineMusic(int code, const QString &description)
{
    if(code == 0)
    {
        //qDebug()<<"get rspResumeOnline ...";
        //qDebug()<<description;
        m_bPlaying = true;
        emit sigQMLMusicPlayingInfo(m_strSongName, m_strSingerName, m_strSingerPicUrl, m_bPlaying);
    }
}

void CAppOnlineMusic::slotForRspStopOnlineMusic(int code, const QString &description)
{
    //qDebug()<<"get rspStopOnline ...";
    if(code == 0)
    {
        //qDebug()<<description;
        m_bPlaying = false;
        emit sigQMLMusicPlayingInfo(m_strSongName, m_strSingerName, m_strSingerPicUrl, m_bPlaying);
    }
}

void CAppOnlineMusic::setSelectIndex(int nIndex)
{
    //qDebug()<<"set select index :"<<nIndex;
    emit sigQMLSetSelectIndex(nIndex);
}

void CAppOnlineMusic::getTopnameMusicData(QString strTopName)
{
    m_musicMode = TYPE_TOPMUSIC;
    m_nCurrentMusicIndex = 0;
    //qDebug()<<"top name is : "<< strTopName;
    CData_TopnameMusic data;
    data.topName = strTopName;
    CNetworkOnlineServer::getInstance()->getTopMusic(data);
}

void CAppOnlineMusic::getMusicTypeTop()
{
    CData_GetMusicType dataTop;
    dataTop.type = ONLINEMUSIC_TYPE_TOP;
    CNetworkOnlineServer::getInstance()->getMusicTop(dataTop);
}

void CAppOnlineMusic::getMusicTypeTag()
{
    CData_GetMusicType dataTag;
    dataTag.type = ONLINEMUSIC_TYPE_TAG;
    CNetworkOnlineServer::getInstance()->getMusicTag(dataTag);
}

void CAppOnlineMusic::playMusic(int nIndex)
{
    if(nIndex < 0 || nIndex > m_onlineMusicTopnameMusicData.size()) return;

    m_nCurrentMusicIndex = nIndex; // update index;

    QString strPlayUrl = m_onlineMusicTopnameMusicData.at(nIndex).strPlayUrl;
    //qDebug()<<"playMusic url : " << strPlayUrl;
    if(!strPlayUrl.isEmpty())
    {
        //CService::media()->PlayOnline(strPlayUrl, TYPE_AUDIO);

    }
    else
    {
        QString strExtraUrl = m_onlineMusicTopnameMusicData.at(nIndex).strExtraUrl;
        if(strExtraUrl.isEmpty()) return;
        //CService::media()->PlayOnline(strExtraUrl, TYPE_AUDIO);
    }
    m_strSongName       = m_onlineMusicTopnameMusicData.at(nIndex).strSongName;
    m_strSingerName     = m_onlineMusicTopnameMusicData.at(nIndex).strSingerName;
    m_strSingerPicUrl   = m_onlineMusicTopnameMusicData.at(nIndex).strSingerPicUrl;

    emit sigQMLMusicPlayingInfo(m_strSongName, m_strSingerName, m_strSingerPicUrl, true);
    emit sigQMLCurrentMusicIndexChanged(m_nCurrentMusicIndex);
    selectMusicIsCollected(m_onlineMusicTopnameMusicData.at(nIndex).strSongID);

    //-----------------------------------------------------------------------------------------------
    // add info to onlinemusic_history table
    //-----------------------------------------------------------------------------------------------
    QString str = QString("select count(*) from onlinemusic_history where songid = '%1'").arg(m_onlineMusicTopnameMusicData.at(nIndex).strSongID);
    if(m_db.select(str))
    {
       m_db.Query().next();
       int count = m_db.Query().value(0).toInt();
       if(count == 0)
       {
           //qDebug()<<"falied...";
           QString insert_sql = "insert into onlinemusic_history values (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
           QVector<QString> sqlListData;
           sqlListData.append(m_onlineMusicTopnameMusicData.at(nIndex).strSongID);
           sqlListData.append(m_onlineMusicTopnameMusicData.at(nIndex).strSongName);
           sqlListData.append(m_onlineMusicTopnameMusicData.at(nIndex).strSingerName);
           sqlListData.append(m_onlineMusicTopnameMusicData.at(nIndex).strSingerID);
           sqlListData.append(m_onlineMusicTopnameMusicData.at(nIndex).strSingerPicUrl);
           sqlListData.append(m_onlineMusicTopnameMusicData.at(nIndex).strPlayUrl);
           sqlListData.append(m_onlineMusicTopnameMusicData.at(nIndex).strLyricUrl);
           sqlListData.append(m_onlineMusicTopnameMusicData.at(nIndex).strTopNo);
           sqlListData.append(m_onlineMusicTopnameMusicData.at(nIndex).strExtraUrl);
           sqlListData.append(m_onlineMusicTopnameMusicData.at(nIndex).strScore);
           sqlListData.append(m_onlineMusicTopnameMusicData.at(nIndex).strCacheID);
           m_db.insert(insert_sql, sqlListData);
       }
    }
    else
    {

    }

}

void CAppOnlineMusic::play()
{
    if (m_onlineMusicTopnameMusicData.size() > 0)
    {
        playMusic(m_nCurrentMusicIndex);
    }
}

void CAppOnlineMusic::slotForRspGetOnlineMusicTopType(QString &data)
{
    //qDebug()<<"go in slotForRspGetOnlineMusicType ";
    JsonLite root(data);
    if(root.getIntValue("code") == 0)
    {
        JsonLite jsonData(root.getJsonValue("data"));
        if(!jsonData.isValid())
        {
            return;
        }
        CRspOnlineMusicTypeVector list;
        QVector<JsonLite> arrJson;
        jsonData.getJsonArrayValue("typeInfoList", arrJson);
        for( int i= 0; i < arrJson.size(); i++)
        {
            CRspOnlineMusicTypeInfo info;
            info.strType = arrJson.at(i).getStrValue("type");
            info.strName = arrJson.at(i).getStrValue("name");
            info.strPicUrl = arrJson.at(i).getStrValue("picUrl");

            list.onlineMusicList.append(info);

            //qDebug()<< "name is : "<< info.strName;
        }

        filterDataForOnlineMusicTopType(list);
        //qDebug()<<"OnlineMusic get music type (top) size is : "<< list.onlineMusicList.size();

    }
}

void CAppOnlineMusic::slotForRspGetOnlineMusicTag(QString &data)
{
    //qDebug()<<" get signal tag";

    JsonLite root(data);
    if( root.getIntValue("code") == 0)
    {
        JsonLite jsonData(root.getJsonValue("data"));
        if(!jsonData.isValid()) return;

        CRspOnlineMusicTypeVector list;
        QVector<JsonLite> jsonInfoList;
        jsonData.getJsonArrayValue("typeInfoList", jsonInfoList);
        for( int i = 0; i < jsonInfoList.size(); i++)
        {
            CRspOnlineMusicTypeInfo typeInfo;
            typeInfo.strType   = jsonInfoList.at(i).getStrValue("type");
            typeInfo.strPicUrl = jsonInfoList.at(i).getStrValue("picUrl");

            //qDebug()<< "typeInfo.strType" <<typeInfo.strType;

            QVector<JsonLite> jsonSubList;
            jsonInfoList.at(i).getJsonArrayValue("catagoryArray", jsonSubList);

            for(int j = 0; j < jsonSubList.size(); j++)
            {
                CRspSubTypeInfo subTypeInfo;
                subTypeInfo.strType   = jsonSubList.at(j).getStrValue("type");
                subTypeInfo.strPicUrl = jsonSubList.at(j).getStrValue("picUrl");
                typeInfo.subTypeInfoList.append(subTypeInfo);
                //qDebug()<< "subTypeInfo.strType" <<subTypeInfo.strType;
            }
            list.onlineMusicList.append(typeInfo);
        }
        filterDataForOnlineMusicTagType(list);
        //qDebug()<<"OnlineMusic get music type (tag) size is : "<< list.onlineMusicList.size();
    }


}

void CAppOnlineMusic::slotForRspGetOnlineMusicSingerTypeName(QString &data)
{
    //qDebug()<<" get signal SingerTypeNam";

    JsonLite root(data);
    if(root.getIntValue("code") == 0)
    {
        JsonLite jsonData(root.getJsonValue("data"));
        if(!jsonData.isValid())
        {
            return;
        }
        CRspOnlineMusicTypeVector list;
        QVector<JsonLite> arrJson;
        jsonData.getJsonArrayValue("typeInfoList", arrJson);
        for( int i= 0; i < arrJson.size(); i++)
        {
            CRspOnlineMusicTypeInfo info;
            info.strType = arrJson.at(i).getStrValue("type");
            info.strName = arrJson.at(i).getStrValue("name");
            info.strPicUrl = arrJson.at(i).getStrValue("picUrl");

            list.onlineMusicList.append(info);

            //qDebug()<< "name is : "<< info.strName;
        }

       filterDataForOnlineMusicSingerType(list);
        //qDebug()<<"OnlineMusic get music type (SingerTypeName) size is : "<< list.onlineMusicList.size();

    }
}

void CAppOnlineMusic::slotForRspGetOnlineMusicRadio(QString &data)
{
    //qDebug()<<" get signal Radio";

    JsonLite root(data);
    if( root.getIntValue("code") == 0)
    {
        JsonLite jsonData(root.getJsonValue("data"));
        if(!jsonData.isValid()) return;

        CRspOnlineMusicTypeVector list;
        QVector<JsonLite> jsonInfoList;
        jsonData.getJsonArrayValue("typeInfoList", jsonInfoList);
        for( int i = 0; i < jsonInfoList.size(); i++)
        {
            CRspOnlineMusicTypeInfo typeInfo;
            typeInfo.strType   = jsonInfoList.at(i).getStrValue("type");
            typeInfo.strPicUrl = jsonInfoList.at(i).getStrValue("picUrl");

            QVector<JsonLite> jsonSubList;
            jsonInfoList.at(i).getJsonArrayValue("catagoryArray", jsonSubList);

            for(int j = 0; j < jsonSubList.size(); j++)
            {
                CRspSubTypeInfo subTypeInfo;
                subTypeInfo.strType   = jsonSubList.at(j).getStrValue("type");
                subTypeInfo.strPicUrl = jsonSubList.at(j).getStrValue("picUrl");
                typeInfo.subTypeInfoList.append(subTypeInfo);
            }
            list.onlineMusicList.append(typeInfo);
        }
        filterDataForOnlineMusicRadioType(list);
        //qDebug()<<"OnlineMusic get music type (radio) size is : "<< list.onlineMusicList.size();
    }
}

void CAppOnlineMusic::slotForRspGetOnlineMusicTopnameMusicData(QString &data)
{
    //qDebug()<<" get signal top name music data ...";
    JsonLite root(data);
    if( root.getIntValue("code") == 0)
    {
        JsonLite jsondata(root.getJsonValue("data"));
        if( !jsondata.isValid() ) return;

        CRspOnlineMusicTopnameMusicDataVector topnameMusicDataList;
        topnameMusicDataList.nTotal = jsondata.getIntValue("total");
        if(topnameMusicDataList.nTotal <= 0) return;

        QVector<JsonLite> jsonMusicInfoList;
        jsondata.getJsonArrayValue("musicInfoList", jsonMusicInfoList);

        if(jsonMusicInfoList.size() <= 0) return;

        CRspOnlineMusicTopnameMusicData topnameMusicData;
        if(!jsonMusicInfoList.at(0).hasProperty("songId"))
        {
            //qDebug()<<"最新歌手榜...";
            for(int i = 0; i < jsonMusicInfoList.size(); i++)
            {

                topnameMusicData.strSongName        = "";
                topnameMusicData.strSongID          = "";
                topnameMusicData.strSingerName      = jsonMusicInfoList.at(i).getStrValue("singerName");
                topnameMusicData.strSingerID        = jsonMusicInfoList.at(i).getStrValue("singerId");
                topnameMusicData.strSingerPicUrl    = jsonMusicInfoList.at(i).getStrValue("singerPic");
                topnameMusicData.strExtraUrl        = jsonMusicInfoList.at(i).getStrValue("picMin");
                topnameMusicData.strScore           = jsonMusicInfoList.at(i).getStrValue("score");
                topnameMusicData.strCacheID         = "";
                topnameMusicData.strTopNo           = "";
                topnameMusicData.strPlayUrl         = "";
                topnameMusicData.strLyricUrl        = "";

                QVector<JsonLite> jsonSingerInfoList;
                jsonMusicInfoList.at(i).getJsonArrayValue("singerInfoList", jsonSingerInfoList);
                for( int j = 0; j < jsonSingerInfoList.size(); j++)
                {
                    CRspOnlineMusicTopnameMusicSingerInfo singerInfo;
                    singerInfo.strSingerName = jsonSingerInfoList.at(j).getStrValue("singerName");
                    singerInfo.strSingerID   = jsonSingerInfoList.at(j).getStrValue("singerId");
                    topnameMusicData.ol_topnamemusicsingerlist.append(singerInfo);
                }
                topnameMusicDataList.ol_topnamemusicdatalist.append(topnameMusicData);
                //qDebug()<<"singer name is  : " << topnameMusicData.strSingerName ;
            }
        }
        else
        {
            for(int i = 0; i < jsonMusicInfoList.size(); i++)
            {

                topnameMusicData.strSongName        = jsonMusicInfoList.at(i).getStrValue("songName");
                topnameMusicData.strSongID          = jsonMusicInfoList.at(i).getStrValue("songId");
                topnameMusicData.strSingerName      = jsonMusicInfoList.at(i).getStrValue("singerName");
                topnameMusicData.strSingerID        = jsonMusicInfoList.at(i).getStrValue("singerId");
                topnameMusicData.strSingerPicUrl    = jsonMusicInfoList.at(i).getStrValue("singerPic");
                topnameMusicData.strLyricUrl        = jsonMusicInfoList.at(i).getStrValue("lyricUrl");
                topnameMusicData.strPlayUrl         = jsonMusicInfoList.at(i).getStrValue("playUrl");
                topnameMusicData.strTopNo           = jsonMusicInfoList.at(i).getStrValue("topNo");
                topnameMusicData.strExtraUrl        = jsonMusicInfoList.at(i).getStrValue("extraUrl");
                topnameMusicData.strScore           = jsonMusicInfoList.at(i).getStrValue("score");
                topnameMusicData.strCacheID         = jsonMusicInfoList.at(i).getStrValue("cacheId");

                QVector<JsonLite> jsonSingerInfoList;
                jsonMusicInfoList.at(i).getJsonArrayValue("singerInfoList", jsonSingerInfoList);
                for( int j = 0; j < jsonSingerInfoList.size(); j++)
                {
                    CRspOnlineMusicTopnameMusicSingerInfo singerInfo;
                    singerInfo.strSingerName = jsonSingerInfoList.at(j).getStrValue("singerName");
                    singerInfo.strSingerID   = jsonSingerInfoList.at(j).getStrValue("singerId");
                    topnameMusicData.ol_topnamemusicsingerlist.append(singerInfo);
                }
                topnameMusicDataList.ol_topnamemusicdatalist.append(topnameMusicData);
                //qDebug()<<"song name is  : " << topnameMusicData.strSongName ;
            }
        }

        filterDataForOnlineMusicTopnameMusicData(topnameMusicDataList);
        //qDebug()<<"OnlineMusic get music type (radio) size is : "<< topnameMusicDataList.ol_topnamemusicdatalist.size();
    }
    else
    {
        if(m_musicMode == TYPE_SEARCHMUSIC)
        {
            emit sigQMLSearchMusic(false);
        }
    }
}
/*
void CAppOnlineMusic::slotForRspGetOnlineMusicSearchMusic(QString &data)
{
    //qDebug()<<"slot music search by key words ...";
    //qDebug()<<" get signal search music data ...";
    JsonLite root(data);
    if( root.getIntValue("code") == 0)
    {
        JsonLite jsondata(root.getJsonValue("data"));
        if( !jsondata.isValid() ) return;

        CRspOnlineMusicTopnameMusicDataVector topnameMusicDataList;
        topnameMusicDataList.nTotal = jsondata.getIntValue("total");
        if(topnameMusicDataList.nTotal <= 0) return;

        QVector<JsonLite> jsonMusicInfoList;
        jsondata.getJsonArrayValue("musicInfoList", jsonMusicInfoList);

        for(int i = 0; i < jsonMusicInfoList.size(); i++)
        {
            CRspOnlineMusicTopnameMusicData topnameMusicData;
            topnameMusicData.strSongName        = jsonMusicInfoList.at(i).getStrValue("songName");
            topnameMusicData.strSongID          = jsonMusicInfoList.at(i).getStrValue("songId");
            topnameMusicData.strSingerName      = jsonMusicInfoList.at(i).getStrValue("singerName");
            topnameMusicData.strSingerID        = jsonMusicInfoList.at(i).getStrValue("singerId");
            topnameMusicData.strSingerPicUrl    = jsonMusicInfoList.at(i).getStrValue("singerPic");
            topnameMusicData.strLyricUrl        = jsonMusicInfoList.at(i).getStrValue("lyricUrl");
            topnameMusicData.strPlayUrl         = jsonMusicInfoList.at(i).getStrValue("playUrl");
            topnameMusicData.strTopNo           = jsonMusicInfoList.at(i).getStrValue("topNo");
            topnameMusicData.strExtraUrl         = jsonMusicInfoList.at(i).getStrValue("extraUrl");
            topnameMusicData.strScore           = jsonMusicInfoList.at(i).getStrValue("score");
            topnameMusicData.strCacheID         = jsonMusicInfoList.at(i).getStrValue("cacheId");

            QVector<JsonLite> jsonSingerInfoList;
            jsonMusicInfoList.at(i).getJsonArrayValue("singerInfoList", jsonSingerInfoList);
            for( int j = 0; j < jsonSingerInfoList.size(); j++)
            {
                CRspOnlineMusicTopnameMusicSingerInfo singerInfo;
                singerInfo.strSingerName = jsonSingerInfoList.at(j).getStrValue("singerName");
                singerInfo.strSingerID   = jsonSingerInfoList.at(j).getStrValue("singerId");
                topnameMusicData.ol_topnamemusicsingerlist.append(singerInfo);
            }
            topnameMusicDataList.ol_topnamemusicdatalist.append(topnameMusicData);
            //qDebug()<<"song name is  : " << topnameMusicData.strSongName ;
        }
        filterDataForOnlineMusicSearchedMusicData(topnameMusicDataList);
        //qDebug()<<"OnlineMusic get music type (radio) size is : "<< topnameMusicDataList.ol_topnamemusicdatalist.size();
    }
    else{
        emit sigQMLSearchMusic(false);
    }
}
*/

}// QTDUDU

