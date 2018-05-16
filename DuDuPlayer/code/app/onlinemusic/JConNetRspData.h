/*
 *  此文件定义从网络中返回的数据类型
*/

#ifndef JCONNETRSPDATA_H
#define JCONNETRSPDATA_H

#include <QObject>

namespace QTDUDU {

    // 天气信息数据
    class CWeatherInfo
    {
    public:
        QString strProvice;
        QString strCity;
        QString strLastUpdateTime;
        QString strDate;
        QString strWeather;
        QString strTemp;
        QString strHumidity;
        QString strWind;
        QString strPM25;
        QString strLow;
        QString strHigh;
        QString strAirQuality;
        QString strWindLevel;
        QString strWeatherType;
    };

    class CRspWeatherInfo
    {
    public:
        QVector<CWeatherInfo> lstWeatherInfo;
        QString strTotal;
        QString strSourceName;
        QString strLogoUrl;
    };



    // 天气指数数据
    class CWeatherIndex
    {
    public:
        QString strProvince;
        QString strCity;
        QString strArea;
        QString strDate;
        QString strCode;
        QString strType;
        QString strLevel;
        QString strDesp;
    };

    class CRspWeatherIndex
    {
    public:
        QVector<CWeatherIndex> lstWeatherIndex;
        QString strSourceName;
        QString strLogoUrl;
    };


    // 空气质量数据
    class CAreaAirquality
    {
    public:
        QString strPositionName;
        QString strPM25;
        QString strPM10;
        QString strPublishDateTimeLong;
        QString strPublishDateTime;
        QString strArea;
        QString strAQI;
        QString strIsGlobal;
        QString strPM25Day;
        QString strCO;
        QString strNO2;
        QString strSO2;
        QString strQuality;
    };

    class CRspAreaAirquality
    {
    public:
        QVector<CAreaAirquality> lstAreaAirquality;
        QString strSourceName;
        QString strLogoUrl;
    };

    /**********************************
     *          网络电台
    ***********************************/

    // 网络电台列表
    class CRadio
    {
    public:
        QString radioName;
        QString id;
        QString radioId;
        QString radioUrl;
        QString flag;
        QString type;
        QString radioTag;
        QString isCollected;
    };

    class CRspRadioList
    {
    public:
        QVector<CRadio> dataList;
        QString total;
        ulong   updateTime;
    };

    // 网络电台
    class CNetRadio
    {
    public:
        QString radioName;
        QString radioId;
        QString radioType;
        QString radioUrl;
        QString isCollected;
    };

    class CRspNetRadioList
    {
    public:
        QVector<CNetRadio> radioList;
        QString total;
    };

    // 本地电台列表
    class CLocalRadio
    {
    public:
        QString region;
        QString shortName;
        QString stationName;
        QString fm;
        QString am;
        QString sendRegion;
        QString orgName;
        QString type;
    };

    class CRspLocalRadioList
    {
    public:
        QVector<CLocalRadio> dataList;
        QString total;
        ulong   updateTime;
    };

    // 网络点播节目
    class CSingerInfo
    {
    public:
        QString singerName;
        QString singerId;
        QString signerPic;
    };

    class CMusicInfo
    {
    public:
        QString songName;
        QString songId;
        QString singerName;
        QVector<CSingerInfo> singerInfoList;
        QString singerId;
        QString playUrl;
        QString cacheId;
    };

    class CRspDemandProgram
    {
    public:
        QVector<CMusicInfo> programInfoList;
        QString total;
    };

    // 网络直播节目单
    class CProgramInfo
    {
    public:
        QString programName;
        QString time;
    };

    class CRspLiveProgramList
    {
    public:
        QVector<CProgramInfo> programInfoList;
        QString livingProgram;
        QString radioName;
        QString radioId;
    };

    // 当前直播节目
    class CRspLivingProgram
    {
    public:
        QString livingProgram;
    };

    // 网络电台排行榜
    class CRankRadioInfo
    {
    public:
        QString radioName;
        QString radioId;
        QString hot;
        QString url;
        QString radioTag;
    };

    class CRspRadioRank
    {
    public:
        QVector<CRankRadioInfo> radioList;
        QString lastModified;
    };

    // 网络电台类型列表
    class CTypeRadioInfo
    {
    public:
        QString radioName;
        QString radioId;
        QString url;
        QString radioTag;
    };

    class CRspRadioTypeList
    {
    public:
        QVector<CTypeRadioInfo> radioList;
        QString lastModified;
    };

    // 场景下的子目录 针对"场景"/“情感...”数据结构
    class CRspSubTypeInfo
    {
    public:
        QString strType;
        QString strPicUrl;
    };

    // OnlineMusic musicType
    class CRspOnlineMusicTypeInfo
    {
    public:
        CRspOnlineMusicTypeInfo()
        {
            strType     = "";
            strName     = "";
            strPicUrl   = "";
        }

        QString strType;
        QString strName;
        QString strPicUrl;

        QVector<CRspSubTypeInfo> subTypeInfoList;  //针对"场景"/“情感...”数据结构
    };
    class CRspOnlineMusicTypeVector
    {
    public:
        QVector<CRspOnlineMusicTypeInfo> onlineMusicList;
    };

    class CRspOnlineMusicTopnameMusicSingerInfo
    {
      public:
        QString strSingerName;
        QString strSingerID;
    };
    class CRspOnlineMusicTopnameMusicData
    {

    public:
        CRspOnlineMusicTopnameMusicData()
        {
            strSongName         = "";
            strSongID           = "";
            strSingerName       = "";
            strSingerID         = "";
            strSingerPicUrl     = "";
            strPlayUrl          = "";
            strLyricUrl         = "";
            strTopNo            = "";
            strExtraUrl         = "";
            strScore            = "";
            strCacheID          = "";

        }
        QString strSongName;
        QString strSongID;
        QString strSingerName;
        QString strSingerID;
        QVector<CRspOnlineMusicTopnameMusicSingerInfo> ol_topnamemusicsingerlist;
        QString strSingerPicUrl;
        QString strPlayUrl;
        QString strLyricUrl;
        QString strTopNo;
        QString strExtraUrl;
        QString strScore;
        QString strCacheID;
    };
    // onlinemusic TopnameMusicData
    class CRspOnlineMusicTopnameMusicDataVector
    {
    public:
        QVector<CRspOnlineMusicTopnameMusicData> ol_topnamemusicdatalist;
        int nTotal;
    };



}

#endif // JCONNETRSPDATA_H
