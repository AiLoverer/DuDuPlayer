#ifndef COMMONDATA_H
#define COMMONDATA_H
/**
 * 公共协议定义区域
 */
#include <QObject>

namespace QTDUDU {

    /***********************
     * online music
    ***********************/
    class HData_OnlineMusicType
    {
    public:

        QString strType;
        QString strName;
        QString strPicUrl;
    };
    class HData_OnlineMusicTopnameMusicData
    {
    public:
        HData_OnlineMusicTopnameMusicData()
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
        QString strSingerPicUrl;
        QString strPlayUrl;
        QString strLyricUrl;
        QString strTopNo;
        QString strExtraUrl;
        QString strScore;
        QString strCacheID;
    };

    // 音乐协议
    class MusicInfo {
    public:
        MusicInfo(){
            strSongName     = "";
            strSongPath     = "";
            strLyricPath    = "";
        }
        QString strSongName;    // 歌名
        QString strSongPath;    // 歌路径
        QString strLyricPath;   // 歌词路径
    };

    class CData_Weather
    {
    public:
        QString province;
        QString city;
        QString area;
        QString latitude;
        QString longitude;
        QString startTime;
        QString pageNo;
        QString pageSize;
    };

    class CData_RadioList
    {
    public:
        QString pageNo;
        QString pageSize;
        QString updateTime;
    };

    class CData_SearchRadio
    {
    public:
        QString radioName;
        QString pageNo;
        QString pageSize;
    };

    class CData_GetLocalRadio
    {
    public:
        QString limit;
        QString updateTime;
    };

    class CData_DemondPro
    {
    public:
        QString question;
        QString pageNo;
        QString pageSize;
    };

    class CData_ProgramList
    {
    public:
        QString radioName;
        QString radioID;
    };

    class CData_Program
    {
    public:
        QString radioID;
    };

    class CData_Ranking
    {
    public:
        QString pageNo;
        QString pageSize;
    };

    class CData_TypeList
    {
    public:
        QString type;
        QString pageSize;
        QString pageNo;
    };

    class CData_WeatherIndex
    {
    public:
        QString province;
        QString city;
        QString area;
        QString latitude;
        QString longitude;
        QString type;
    };

    class CData_AirQuality
    {
    public:
        QString province;
        QString city;
        QString area;
    };

    class CData_News
    {
    public:
        QString type;
        QString time;
        QString pageNo;
        QString pageSize;
    };

    class CData_NewsDetail
    {
    public:
        QString id;
    };

    class CData_SearchMusic
    {
    public:
        QString rawtext;
        QString words;
        QString singerNames;
        QString songName;
        QString tags;
        QString albumName;
        QString radioName;
        QString pageNo;
        QString pageSize;
    };

    class CData_GetMusicType
    {
    public:
        QString type;
    };

    class CData_TopnameMusic
    {
    public:
        QString topName;
        QString pageNo;
        QString pageSize;
    };

    class CData_GetSingerList
    {
    public:
        QString singerType;
        QString pageNo;
        QString pageSize;
    };

    class CData_GetMusicDetail
    {
    public:
        QString songIds;
        QString songName;
        QString singerName;
    };

    class CData_SearchAlbum
    {
    public:
        QString words;
        QString pageNo;
        QString pageSize;
    };

    class CData_SearchAlbumID
    {
    public:
        QString albumId;
        QString albumName;
        QString singerName;
        QString pageNo;
        QString pageSize;
    };

    class CData_SearchSingerID
    {
    public:
        QString singerId;
        QString singerName;
        QString pageNo;
        QString pageSize;
    };

    class CData_GetPlayUrl
    {
    public:
        QString songIds;
        QString songNames;
        QString singerNames;
    };

    class CData_SearchHot
    {
    public:
        QString pageNo;
        QString pageSize;
    };

    class CData_GetProTypeList
    {
    public:
        QString pageNo;
        QString pageSize;
    };

    class CData_GetProList
    {
    public:
        QString typeId;
        QString typeName;
        QString pageNo;
        QString pageSize;
    };

    class CData_GetAlbumDetail
    {
    public:
        QString albumId;
    };

    class CData_GetAlbumList
    {
    public:
        QString albumId;
        QString pageNo;
        QString pageSize;
    };

    class CData_GetTrackDetail
    {
    public:
        QString trackId;
    };

    class CData_GetAllAlbumList
    {
    public:
        QString pageNo;
        QString pageSize;
    };

    class CData_TrackQuery
    {
    public:
        QString question;
        QString pageNo;
        QString pageSize;
    };

    class CData_AlbumTop
    {
    public:
        QString pageNo;
        QString pageSize;
    };

    class CData_LastTrackList
    {
    public:
        QString albumId;
        QString trackId;
        QString pId;
        QString count;
    };

    class CData_SearchProg
    {
    public:
        QString rawtext;
        QString words;
        QString host;
        QString album;
        QString tag;
        QString programName;
        QString pageSize;
        QString pageNo;
    };
    }

#endif // COMMONDATA_H
