#include "cnetworkonlineserver.h"

namespace QTDUDU {

    CNetworkOnlineServer* CNetworkOnlineServer::m_pInstance = NULL;

    CNetworkOnlineServer::CNetworkOnlineServer(QObject *parent)
        :QObject(parent)
    {
        m_pNetWorkManager = CNetworkManager::getInstance();
        m_pNetWorkManager->setOpenId("jianghuai");
        m_pNetWorkManager->setOpenKey("d9b5be90369b4a3292a82dfb629f1d31");
        m_pNetWorkManager->setPrefix("http://autodev.openspeech.cn/api/v2/");

        connect(m_pNetWorkManager,SIGNAL(dataReady(UINT,QString)),this,SLOT(onSigDataReady(UINT,QString)));
        connect(m_pNetWorkManager,SIGNAL(downloadError()),this,SLOT(onSigDownloadError()));
    }

    CNetworkOnlineServer *CNetworkOnlineServer::getInstance()
    {
        if (m_pInstance == NULL)
        {
            m_pInstance = new CNetworkOnlineServer();
        }
        return m_pInstance;
    }

    void CNetworkOnlineServer::searchWeather(CData_Weather& data)
    {
        if (!(data.area.isEmpty()))
        {
            m_pNetWorkManager->addParam("area",data.area);
        }
        if (!(data.city.isEmpty()))
        {
            m_pNetWorkManager->addParam("city",data.city);
        }
        if (!(data.latitude.isEmpty()))
        {
            m_pNetWorkManager->addParam("latitude",data.latitude);
        }
        if (!(data.longitude.isEmpty()))
        {
            m_pNetWorkManager->addParam("longitude",data.longitude);
        }
        if (!(data.pageNo.isEmpty()))
        {
            m_pNetWorkManager->addParam("pageNo",data.pageNo);
        }
        if (!(data.pageSize.isEmpty()))
        {
            m_pNetWorkManager->addParam("pageSize",data.pageSize);
        }
        if (!(data.province.isEmpty()))
        {
            m_pNetWorkManager->addParam("province",data.province);
        }
        if (!(data.startTime.isEmpty()))
        {
            m_pNetWorkManager->addParam("startTime",data.startTime);
        }

        m_pNetWorkManager->getData(71);
    }

    void CNetworkOnlineServer::getRadioList(CData_RadioList& data)
    {
        if (!(data.pageNo.isEmpty()))
        {
            m_pNetWorkManager->addParam("pageNo",data.pageNo);
        }
        if (!(data.pageSize.isEmpty()))
        {
            m_pNetWorkManager->addParam("pageSize",data.pageSize);
        }
        if (!(data.updateTime.isEmpty()))
        {
            m_pNetWorkManager->addParam("updateTime",data.updateTime);
        }

        m_pNetWorkManager->getData(11);
    }

    void CNetworkOnlineServer::searchWeatherIndex(CData_WeatherIndex &data)
    {
        if (!(data.area.isEmpty()))
        {
            m_pNetWorkManager->addParam("area",data.area);
        }
        if (!(data.city.isEmpty()))
        {
            m_pNetWorkManager->addParam("city",data.city);
        }
        if (!(data.latitude.isEmpty()))
        {
            m_pNetWorkManager->addParam("latitude",data.latitude);
        }
        if (!(data.longitude.isEmpty()))
        {
            m_pNetWorkManager->addParam("longitude",data.longitude);
        }
        if (!(data.province.isEmpty()))
        {
            m_pNetWorkManager->addParam("province",data.province);
        }
        if (!(data.type.isEmpty()))
        {
            m_pNetWorkManager->addParam("type",data.type);
        }
        m_pNetWorkManager->getData(72);
    }

    void CNetworkOnlineServer::getAirQuality(CData_AirQuality &data)
    {
        if (!(data.area.isEmpty()))
        {
            m_pNetWorkManager->addParam("area",data.area);
        }
        if (!(data.city.isEmpty()))
        {
            m_pNetWorkManager->addParam("city",data.city);
        }
        if (!(data.province.isEmpty()))
        {
            m_pNetWorkManager->addParam("province",data.province);
        }
        m_pNetWorkManager->getData(73);
    }

    void CNetworkOnlineServer::getNewsType()
    {
        m_pNetWorkManager->getData(31);
    }

    void CNetworkOnlineServer::searchNews_0(CData_News &data)
    {
        if (!(data.pageNo.isEmpty()))
        {
            m_pNetWorkManager->addParam("pageNo",data.pageNo);
        }
        if(!(data.pageSize.isEmpty()))
        {
            m_pNetWorkManager->addParam("pageSize",data.pageSize);
        }
        if(!(data.time.isEmpty()))
        {
            m_pNetWorkManager->addParam("time",data.time);
        }
        if(!(data.type.isEmpty()))
        {
            m_pNetWorkManager->addParam("type",data.type);
        }
        m_pNetWorkManager->getData(320);
    }

    void CNetworkOnlineServer::searchNews_1(CData_News &data)
    {
        if (!(data.pageNo.isEmpty()))
        {
            m_pNetWorkManager->addParam("pageNo",data.pageNo);
        }
        if(!(data.pageSize.isEmpty()))
        {
            m_pNetWorkManager->addParam("pageSize",data.pageSize);
        }
        if(!(data.time.isEmpty()))
        {
            m_pNetWorkManager->addParam("time",data.time);
        }
        if(!(data.type.isEmpty()))
        {
            m_pNetWorkManager->addParam("type",data.type);
        }
        m_pNetWorkManager->getData(321);
    }

    void CNetworkOnlineServer::searchNews_2(CData_News &data)
    {
        if (!(data.pageNo.isEmpty()))
        {
            m_pNetWorkManager->addParam("pageNo",data.pageNo);
        }
        if(!(data.pageSize.isEmpty()))
        {
            m_pNetWorkManager->addParam("pageSize",data.pageSize);
        }
        if(!(data.time.isEmpty()))
        {
            m_pNetWorkManager->addParam("time",data.time);
        }
        if(!(data.type.isEmpty()))
        {
            m_pNetWorkManager->addParam("type",data.type);
        }
        m_pNetWorkManager->getData(322);
    }

    void CNetworkOnlineServer::searchNews_3(CData_News &data)
    {
        if (!(data.pageNo.isEmpty()))
        {
            m_pNetWorkManager->addParam("pageNo",data.pageNo);
        }
        if(!(data.pageSize.isEmpty()))
        {
            m_pNetWorkManager->addParam("pageSize",data.pageSize);
        }
        if(!(data.time.isEmpty()))
        {
            m_pNetWorkManager->addParam("time",data.time);
        }
        if(!(data.type.isEmpty()))
        {
            m_pNetWorkManager->addParam("type",data.type);
        }
        m_pNetWorkManager->getData(323);
    }

    void CNetworkOnlineServer::searchNews_4(CData_News &data)
    {
        if (!(data.pageNo.isEmpty()))
        {
            m_pNetWorkManager->addParam("pageNo",data.pageNo);
        }
        if(!(data.pageSize.isEmpty()))
        {
            m_pNetWorkManager->addParam("pageSize",data.pageSize);
        }
        if(!(data.time.isEmpty()))
        {
            m_pNetWorkManager->addParam("time",data.time);
        }
        if(!(data.type.isEmpty()))
        {
            m_pNetWorkManager->addParam("type",data.type);
        }
        m_pNetWorkManager->getData(324);
    }

    void CNetworkOnlineServer::searchNews_5(CData_News &data)
    {
        if (!(data.pageNo.isEmpty()))
        {
            m_pNetWorkManager->addParam("pageNo",data.pageNo);
        }
        if(!(data.pageSize.isEmpty()))
        {
            m_pNetWorkManager->addParam("pageSize",data.pageSize);
        }
        if(!(data.time.isEmpty()))
        {
            m_pNetWorkManager->addParam("time",data.time);
        }
        if(!(data.type.isEmpty()))
        {
            m_pNetWorkManager->addParam("type",data.type);
        }
        m_pNetWorkManager->getData(325);
    }

    void CNetworkOnlineServer::searchNews_6(CData_News &data)
    {
        if (!(data.pageNo.isEmpty()))
        {
            m_pNetWorkManager->addParam("pageNo",data.pageNo);
        }
        if(!(data.pageSize.isEmpty()))
        {
            m_pNetWorkManager->addParam("pageSize",data.pageSize);
        }
        if(!(data.time.isEmpty()))
        {
            m_pNetWorkManager->addParam("time",data.time);
        }
        if(!(data.type.isEmpty()))
        {
            m_pNetWorkManager->addParam("type",data.type);
        }
        m_pNetWorkManager->getData(326);
    }

    void CNetworkOnlineServer::searchNewsDetail(CData_NewsDetail &data)
    {
        if(!(data.id.isEmpty()))
        {
            m_pNetWorkManager->addParam("id",data.id);
        }
        m_pNetWorkManager->getData(33);
    }

    void CNetworkOnlineServer::searchNetworkRadio(CData_SearchRadio &data)
    {
        if (!(data.pageNo.isEmpty()))
        {
            m_pNetWorkManager->addParam("pageNo",data.pageNo);
        }
        if (!(data.pageSize.isEmpty()))
        {
            m_pNetWorkManager->addParam("pageSize",data.pageSize);
        }
        if (!(data.radioName.isEmpty()))
        {
            m_pNetWorkManager->addParam("radioName",data.radioName);
        }
        m_pNetWorkManager->getData(12);
    }

    void CNetworkOnlineServer::getLocalRadioList(CData_GetLocalRadio &data)
    {
        if (!(data.limit.isEmpty()))
        {
            m_pNetWorkManager->addParam("limit",data.limit);
        }
        if (!(data.updateTime.isEmpty()))
        {
            m_pNetWorkManager->addParam("updateTime",data.updateTime);
        }

        m_pNetWorkManager->getData(13);
    }

    void CNetworkOnlineServer::searchDemondProg(CData_DemondPro &data)
    {
        if (!(data.pageNo.isEmpty()))
        {
            m_pNetWorkManager->addParam("pageNo",data.pageNo);
        }
        if (!(data.pageSize.isEmpty()))
        {
            m_pNetWorkManager->addParam("pageSize",data.pageSize);
        }
        if (!(data.question.isEmpty()))
        {
            m_pNetWorkManager->addParam("question",data.question);
        }
        m_pNetWorkManager->getData(14);
    }

    void CNetworkOnlineServer::getProgList(CData_ProgramList &data)
    {
        if (!(data.radioID.isEmpty()))
        {
            m_pNetWorkManager->addParam("radioID",data.radioID);
        }
        if (!(data.radioName.isEmpty()))
        {
            m_pNetWorkManager->addParam("radioName",data.radioName);
        }

        m_pNetWorkManager->getData(15);
    }

    void CNetworkOnlineServer::getProg(CData_Program &data)
    {
        if (!(data.radioID.isEmpty()))
        {
            m_pNetWorkManager->addParam("radioID",data.radioID);
        }

        m_pNetWorkManager->getData(16);
    }

    void CNetworkOnlineServer::getRanking(CData_Ranking &data)
    {
        if (!(data.pageNo.isEmpty()))
        {
            m_pNetWorkManager->addParam("pageNo",data.pageNo);
        }
        if (!(data.pageSize.isEmpty()))
        {
            m_pNetWorkManager->addParam("pageSize",data.pageSize);
        }

        m_pNetWorkManager->getData(17);
    }

    void CNetworkOnlineServer::getRadioTypeList(CData_TypeList &data)
    {
        if (!(data.pageNo.isEmpty()))
        {
            m_pNetWorkManager->addParam("pageNo",data.pageNo);
        }
        if (!(data.pageSize.isEmpty()))
        {
            m_pNetWorkManager->addParam("pageSize",data.pageSize);
        }
        if (!(data.type.isEmpty()))
        {
            m_pNetWorkManager->addParam("type",data.type);
        }
        m_pNetWorkManager->getData(18);
    }

    void CNetworkOnlineServer::getMusicTop(CData_GetMusicType &data)
    {
        if (!(data.type.isEmpty()))
        {
            m_pNetWorkManager->addParam("type",data.type);
        }
        m_pNetWorkManager->getData(211);
    }

    void CNetworkOnlineServer::getMusicSinger(CData_GetMusicType &data)
    {
        if (!(data.type.isEmpty()))
        {
            m_pNetWorkManager->addParam("type",data.type);
        }
        m_pNetWorkManager->getData(212);
    }

    void CNetworkOnlineServer::getMusicTag(CData_GetMusicType &data)
    {
        if (!(data.type.isEmpty()))
        {
            m_pNetWorkManager->addParam("type",data.type);
        }
        m_pNetWorkManager->getData(213);
    }

    void CNetworkOnlineServer::getMusicRadio(CData_GetMusicType &data)
    {
        if (!(data.type.isEmpty()))
        {
            m_pNetWorkManager->addParam("type",data.type);
        }
        m_pNetWorkManager->getData(214);
    }

    void CNetworkOnlineServer::searchMusic(CData_SearchMusic &data)
    {
        if (!(data.rawtext.isEmpty()))
        {
            m_pNetWorkManager->addParam("rawtext",data.rawtext);
        }
        if (!(data.words.isEmpty()))
        {
            m_pNetWorkManager->addParam("words",data.words);
        }
        if (!(data.singerNames.isEmpty()))
        {
            m_pNetWorkManager->addParam("singerNames",data.singerNames);
        }
        if (!(data.songName.isEmpty()))
        {
            m_pNetWorkManager->addParam("songName",data.songName);
        }
        if (!(data.tags.isEmpty()))
        {
            m_pNetWorkManager->addParam("tags",data.tags);
        }
        if (!(data.albumName.isEmpty()))
        {
            m_pNetWorkManager->addParam("albumName",data.albumName);
        }
        if (!(data.radioName.isEmpty()))
        {
            m_pNetWorkManager->addParam("radioName",data.radioName);
        }
        if (!(data.pageNo.isEmpty()))
        {
            m_pNetWorkManager->addParam("pageNo",data.pageNo);
        }
        if (!(data.pageSize.isEmpty()))
        {
            m_pNetWorkManager->addParam("pageSize",data.pageSize);
        }
        m_pNetWorkManager->getData(22);
    }

    void CNetworkOnlineServer::getTopMusic(CData_TopnameMusic &data)
    {
        if (!(data.topName.isEmpty()))
        {
            m_pNetWorkManager->addParam("topName",data.topName);
        }
        if (!(data.pageNo.isEmpty()))
        {
            m_pNetWorkManager->addParam("pageNo",data.pageNo);
        }
        if (!(data.pageSize.isEmpty()))
        {
            m_pNetWorkManager->addParam("pageSize",data.pageSize);
        }
        m_pNetWorkManager->getData(23);
    }

    void CNetworkOnlineServer::getSingerList(CData_GetSingerList &data)
    {
        if (!(data.singerType.isEmpty()))
        {
            m_pNetWorkManager->addParam("singerType",data.singerType);
        }
        if (!(data.pageNo.isEmpty()))
        {
            m_pNetWorkManager->addParam("pageNo",data.pageNo);
        }
        if (!(data.pageSize.isEmpty()))
        {
            m_pNetWorkManager->addParam("pageSize",data.pageSize);
        }
        m_pNetWorkManager->getData(24);
    }

    void CNetworkOnlineServer::getMusicDetail(CData_GetMusicDetail &data)
    {
        if (!(data.songIds.isEmpty()))
        {
            m_pNetWorkManager->addParam("songIds",data.songIds);
        }
        if (!(data.songName.isEmpty()))
        {
            m_pNetWorkManager->addParam("songName",data.songName);
        }
        if (!(data.singerName.isEmpty()))
        {
            m_pNetWorkManager->addParam("singerName",data.singerName);
        }
        m_pNetWorkManager->getData(25);
    }

    void CNetworkOnlineServer::searchAlbum(CData_SearchAlbum &data)
    {
        if (!(data.words.isEmpty()))
        {
            m_pNetWorkManager->addParam("words",data.words);
        }
        if (!(data.pageNo.isEmpty()))
        {
            m_pNetWorkManager->addParam("pageNo",data.pageNo);
        }
        if (!(data.pageSize.isEmpty()))
        {
            m_pNetWorkManager->addParam("pageSize",data.pageSize);
        }
        m_pNetWorkManager->getData(26);
    }

    void CNetworkOnlineServer::searchAlbumID(CData_SearchAlbumID &data)
    {
        if (!(data.albumId.isEmpty()))
        {
            m_pNetWorkManager->addParam("albumId",data.albumId);
        }
        if (!(data.albumName.isEmpty()))
        {
            m_pNetWorkManager->addParam("albumName",data.albumName);
        }
        if (!(data.singerName.isEmpty()))
        {
            m_pNetWorkManager->addParam("singerName",data.singerName);
        }
        if (!(data.pageNo.isEmpty()))
        {
            m_pNetWorkManager->addParam("pageNo",data.pageNo);
        }
        if (!(data.pageSize.isEmpty()))
        {
            m_pNetWorkManager->addParam("pageSize",data.pageSize);
        }
        m_pNetWorkManager->getData(27);
    }

    void CNetworkOnlineServer::searchSingerID(CData_SearchSingerID &data)
    {
        if (!(data.singerId.isEmpty()))
        {
            m_pNetWorkManager->addParam("singerId",data.singerId);
        }
        if (!(data.singerName.isEmpty()))
        {
            m_pNetWorkManager->addParam("singerName",data.singerName);
        }
        if (!(data.pageNo.isEmpty()))
        {
            m_pNetWorkManager->addParam("pageNo",data.pageNo);
        }
        if (!(data.pageSize.isEmpty()))
        {
            m_pNetWorkManager->addParam("pageSize",data.pageSize);
        }
        m_pNetWorkManager->getData(28);
    }

    void CNetworkOnlineServer::getPlayUrl(CData_GetPlayUrl &data)
    {
        if (!(data.songIds.isEmpty()))
        {
            m_pNetWorkManager->addParam("songIds",data.songIds);
        }
        if (!(data.songNames.isEmpty()))
        {
            m_pNetWorkManager->addParam("songNames",data.songNames);
        }
        if (!(data.singerNames.isEmpty()))
        {
            m_pNetWorkManager->addParam("singerNames",data.singerNames);
        }
        m_pNetWorkManager->getData(29);
    }

    void CNetworkOnlineServer::searchHot(CData_SearchHot &data)
    {
        if (!(data.pageNo.isEmpty()))
        {
            m_pNetWorkManager->addParam("pageNo",data.pageNo);
        }
        if (!(data.pageSize.isEmpty()))
        {
            m_pNetWorkManager->addParam("pageSize",data.pageSize);
        }
        m_pNetWorkManager->getData(210);
    }

    void CNetworkOnlineServer::getProgTypeList(CData_GetProTypeList &data)
    {
        if (!(data.pageNo.isEmpty()))
        {
            m_pNetWorkManager->addParam("pageNo",data.pageNo);
        }
        if (!(data.pageSize.isEmpty()))
        {
            m_pNetWorkManager->addParam("pageSize",data.pageSize);
        }
        m_pNetWorkManager->getData(141);
    }

    void CNetworkOnlineServer::getAlbumListByTypeID(CData_GetProList &data)
    {
        if (!(data.typeId.isEmpty()))
        {
            m_pNetWorkManager->addParam("typeId",data.typeId);
        }
        if (!(data.typeName.isEmpty()))
        {
            m_pNetWorkManager->addParam("typeName",data.typeName);
        }
        if (!(data.pageNo.isEmpty()))
        {
            m_pNetWorkManager->addParam("pageNo",data.pageNo);
        }
        if (!(data.pageSize.isEmpty()))
        {
            m_pNetWorkManager->addParam("pageSize",data.pageSize);
        }
        m_pNetWorkManager->getData(142);
    }

    void CNetworkOnlineServer::getAlbumDetailByAlbumID(CData_GetAlbumDetail &data)
    {
        if (!(data.albumId.isEmpty()))
        {
            m_pNetWorkManager->addParam("albumId",data.albumId);
        }

        m_pNetWorkManager->getData(143);
    }

    void CNetworkOnlineServer::getAlbumProgListByAlbumID(CData_GetAlbumList &data)
    {
        if (!(data.albumId.isEmpty()))
        {
            m_pNetWorkManager->addParam("albumId",data.albumId);
        }
        if (!(data.pageNo.isEmpty()))
        {
            m_pNetWorkManager->addParam("pageNo",data.pageNo);
        }
        if (!(data.pageSize.isEmpty()))
        {
            m_pNetWorkManager->addParam("pageSize",data.pageSize);
        }
        m_pNetWorkManager->getData(144);
    }

    void CNetworkOnlineServer::getTrackDetailByTrackID(CData_GetTrackDetail &data)
    {
        if (!(data.trackId.isEmpty()))
        {
            m_pNetWorkManager->addParam("trackId",data.trackId);
        }

        m_pNetWorkManager->getData(145);
    }

    void CNetworkOnlineServer::getAllAlbumList(CData_GetAllAlbumList &data)
    {
        if (!(data.pageNo.isEmpty()))
        {
            m_pNetWorkManager->addParam("pageNo",data.pageNo);
        }
        if (!(data.pageSize.isEmpty()))
        {
            m_pNetWorkManager->addParam("pageSize",data.pageSize);
        }
        m_pNetWorkManager->getData(146);
    }

    void CNetworkOnlineServer::trackQuery(CData_TrackQuery &data)
    {
        if (!(data.question.isEmpty()))
        {
            m_pNetWorkManager->addParam("question",data.question);
        }
        if (!(data.pageNo.isEmpty()))
        {
            m_pNetWorkManager->addParam("pageNo",data.pageNo);
        }
        if (!(data.pageSize.isEmpty()))
        {
            m_pNetWorkManager->addParam("pageSize",data.pageSize);
        }
        m_pNetWorkManager->getData(147);
    }

    void CNetworkOnlineServer::getAlbumTop(CData_AlbumTop &data)
    {
        if (!(data.pageNo.isEmpty()))
        {
            m_pNetWorkManager->addParam("pageNo",data.pageNo);
        }
        if (!(data.pageSize.isEmpty()))
        {
            m_pNetWorkManager->addParam("pageSize",data.pageSize);
        }
        m_pNetWorkManager->getData(148);
    }

    void CNetworkOnlineServer::getLastProg(CData_LastTrackList &data)
    {
        if (!(data.albumId.isEmpty()))
        {
            m_pNetWorkManager->addParam("albumId",data.albumId);
        }
        if (!(data.trackId.isEmpty()))
        {
            m_pNetWorkManager->addParam("trackId",data.trackId);
        }
        if (!(data.pId.isEmpty()))
        {
            m_pNetWorkManager->addParam("pId",data.pId);
        }
        if (!(data.count.isEmpty()))
        {
            m_pNetWorkManager->addParam("count",data.count);
        }
        m_pNetWorkManager->getData(149);
    }

    void CNetworkOnlineServer::searchProg(CData_SearchProg &data)
    {
        if (!(data.rawtext.isEmpty()))
        {
            m_pNetWorkManager->addParam("rawtext",data.rawtext);
        }
        if (!(data.words.isEmpty()))
        {
            m_pNetWorkManager->addParam("words",data.words);
        }
        if (!(data.host.isEmpty()))
        {
            m_pNetWorkManager->addParam("host",data.host);
        }
        if (!(data.album.isEmpty()))
        {
            m_pNetWorkManager->addParam("album",data.album);
        }
        if (!(data.tag.isEmpty()))
        {
            m_pNetWorkManager->addParam("tag",data.tag);
        }
        if (!(data.programName.isEmpty()))
        {
            m_pNetWorkManager->addParam("programName",data.programName);
        }
        if (!(data.pageSize.isEmpty()))
        {
            m_pNetWorkManager->addParam("pageSize",data.pageSize);
        }
        if (!(data.pageNo.isEmpty()))
        {
            m_pNetWorkManager->addParam("pageNo",data.pageNo);
        }

         m_pNetWorkManager->getData(1410);
    }

    void CNetworkOnlineServer::onSigDataReady(UINT type,QString data)
    {
        qDebug()<<"data="<<data;
        switch(type)
        {
        case 211:
            emit sigGetMusicTop(data);
            break;
        case 212:
            emit sigGetMusicSinger(data);
            break;
        case 213:
            emit sigGetMusicTag(data);
            break;
        case 214:
            emit sigGetMusicRadio(data);
            break;
        case 22:
            emit sigSearchMusic(data);
            break;
        case 23:
            emit sigGetTopMusic(data);
            break;
        case 24:
            emit sigGetSingerList(data);
            break;
        case 25:
            emit sigGetMusicDetail(data);
            break;
        case 26:
            emit sigSearchAlbum(data);
            break;
        case 27:
            emit sigSearchAlbumID(data);
            break;
        case 28:
            emit sigSearchSingerID(data);
            break;
        case 29:
            emit sigGetPlayUrl(data);
            break;
        case 210:
            emit sigSearchHot(data);
            break;
        case 31:
            emit sigGetNewsType(data);
            break;
        case 320:
            emit sigSearchNews_0(data);
            break;
        case 321:
            emit sigSearchNews_1(data);
            break;
        case 322:
            emit sigSearchNews_2(data);
            break;
        case 323:
            emit sigSearchNews_3(data);
            break;
        case 324:
            emit sigSearchNews_4(data);
            break;
        case 325:
            emit sigSearchNews_5(data);
            break;
        case 326:
            emit sigSearchNews_6(data);
            break;
        case 33:
            emit sigSearchNewsDetail(data);
            break;
        case 71:
            emit sigSearchWeather(data);
            break;
        case 72:
            emit sigSearchWeatherIndex(data);
            break;
        case 73:
            emit sigGetAirQuality(data);
            break;
        case 11:
            emit sigGetRadioList(data);
            break;
        case 12:
            emit sigSearchNetworkRadio(data);
            break;
        case 13:
            emit sigGetLocalRadioList(data);
            break;
        case 14:
            emit sigSearchDemondProg(data);
            break;
        case 15:
            emit sigGetProgList(data);
            break;
        case 16:
            emit sigGetProg(data);
            break;
        case 17:
            emit sigGetRanking(data);
            break;
        case 18:
            emit sigGetRadioTypeList(data);
            break;
        case 141:
            emit sigGetProgTypeList(data);
            break;
        case 142:
            emit sigGetAlbumListByTypeID(data);
            break;
        case 143:
            emit sigGetAlbumDetailByAlbumID(data);
            break;
        case 144:
            emit sigGetAlbumProgListByAlbumID(data);
            break;
        case 145:
            emit sigGetTrackDetailByTrackID(data);
            break;
        case 146:
            emit sigGetAllAlbumList(data);
            break;
        case 147:
            emit sigTrackQuery(data);
            break;
        case 148:
            emit sigGetAlbumTop(data);
            break;
        case 149:
            emit sigGetLastProg(data);
            break;
        case 1410:
            emit sigSearchProg(data);
            break;
        }
    }

    void CNetworkOnlineServer::onSigDownloadError()
    {
        emit sigDownLoadError();
    }
}


