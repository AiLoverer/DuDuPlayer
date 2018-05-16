#ifndef CNETWORKONLINESERVER_H
#define CNETWORKONLINESERVER_H
#include <QObject>
#include "../../framework/dudu.h"\

namespace QTDUDU {

    class CNetworkManager;
    class CNetworkOnlineServer : public QObject{
        Q_OBJECT
    private:
        CNetworkOnlineServer(QObject *parent=0);
    public:
        static CNetworkOnlineServer* getInstance();
        void searchWeather(CData_Weather& data);
        void getRadioList(CData_RadioList& data);
        void searchWeatherIndex(CData_WeatherIndex& data);
        void getAirQuality(CData_AirQuality& data);
        void getNewsType();
        void searchNews_0(CData_News& data);
        void searchNews_1(CData_News& data);
        void searchNews_2(CData_News& data);
        void searchNews_3(CData_News& data);
        void searchNews_4(CData_News& data);
        void searchNews_5(CData_News& data);
        void searchNews_6(CData_News& data);
        void searchNewsDetail(CData_NewsDetail& data);
        void searchNetworkRadio(CData_SearchRadio& data);
        void getLocalRadioList(CData_GetLocalRadio& data);
        void searchDemondProg(CData_DemondPro& data);
        void getProgList(CData_ProgramList& data);
        void getProg(CData_Program& data);
        void getRanking(CData_Ranking& data);
        void getRadioTypeList(CData_TypeList& data);
        //void getMusicType(CData_GetMusicType& data);
        void getMusicTop(CData_GetMusicType& data);
        void getMusicSinger(CData_GetMusicType& data);
        void getMusicTag(CData_GetMusicType& data);
        void getMusicRadio(CData_GetMusicType& data);
        void searchMusic(CData_SearchMusic& data);
        void getTopMusic(CData_TopnameMusic& data);
        void getSingerList(CData_GetSingerList& data);
        void getMusicDetail(CData_GetMusicDetail& data);
        void searchAlbum(CData_SearchAlbum& data);
        void searchAlbumID(CData_SearchAlbumID& data);
        void searchSingerID(CData_SearchSingerID& data);
        void getPlayUrl(CData_GetPlayUrl& data);
        void searchHot(CData_SearchHot& data);
        void getProgTypeList(CData_GetProTypeList& data);
        void getAlbumListByTypeID(CData_GetProList& data);
        void getAlbumDetailByAlbumID(CData_GetAlbumDetail& data);
        void getAlbumProgListByAlbumID(CData_GetAlbumList& data);
        void getTrackDetailByTrackID(CData_GetTrackDetail& data);
        void getAllAlbumList(CData_GetAllAlbumList& data);
        void trackQuery(CData_TrackQuery& data);
        void getAlbumTop(CData_AlbumTop& data);
        void getLastProg(CData_LastTrackList& data);
        void searchProg(CData_SearchProg& data);

    signals:
        void sigSearchWeather(QString data);
        void sigGetRadioList(QString data);
        void sigSearchWeatherIndex(QString data);
        void sigGetAirQuality(QString data);
        void sigDownLoadError();
        void sigGetNewsType(QString data);
        void sigSearchNews_0(QString data);
        void sigSearchNews_1(QString data);
        void sigSearchNews_2(QString data);
        void sigSearchNews_3(QString data);
        void sigSearchNews_4(QString data);
        void sigSearchNews_5(QString data);
        void sigSearchNews_6(QString data);
        void sigSearchNewsDetail(QString data);
        void sigSearchNetworkRadio(QString& data);
        void sigGetLocalRadioList(QString& data);
        void sigSearchDemondProg(QString& data);
        void sigGetProgList(QString& data);
        void sigGetProg(QString& data);
        void sigGetRanking(QString& data);
        void sigGetRadioTypeList(QString& data);
        //void sigGetMusicType(QString& data);
        void sigGetMusicTop(QString& data);
        void sigGetMusicSinger(QString& data);
        void sigGetMusicTag(QString& data);
        void sigGetMusicRadio(QString& data);
        void sigSearchMusic(QString& data);
        void sigGetTopMusic(QString& data);
        void sigGetSingerList(QString& data);
        void sigGetMusicDetail(QString& data);
        void sigSearchAlbum(QString& data);
        void sigSearchAlbumID(QString& data);
        void sigSearchSingerID(QString& data);
        void sigGetPlayUrl(QString& data);
        void sigSearchHot(QString& data);
        void sigGetProgTypeList(QString& data);
        void sigGetAlbumListByTypeID(QString& data);
        void sigGetAlbumDetailByAlbumID(QString& data);
        void sigGetAlbumProgListByAlbumID(QString& data);
        void sigGetTrackDetailByTrackID(QString& data);
        void sigGetAllAlbumList(QString& data);
        void sigTrackQuery(QString& data);
        void sigGetAlbumTop(QString& data);
        void sigGetLastProg(QString& data);
        void sigSearchProg(QString& data);

    public slots:
        void onSigDataReady(UINT type,QString data);
        void onSigDownloadError();

    private:
        static CNetworkOnlineServer* m_pInstance;
        CNetworkManager* m_pNetWorkManager;
    };

}


#endif // CNETWORKONLINESERVER_H
