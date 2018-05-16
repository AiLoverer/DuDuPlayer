#ifndef CAPPONLINEMUSIC_H
#define CAPPONLINEMUSIC_H

#include <QObject>
#include "../../framework/dudu.h"

namespace QTDUDU {

    #define ONLINEMUSIC_TYPE_TOP                    "top"
    #define ONLINEMUSIC_TYPE_SINGERTYPENAME         "singerTypeName"
    #define ONLINEMUSIC_TYPE_TAG                    "tag"
    #define ONLINEMUSIC_TYPE_RADIO                  "radio"

typedef enum _MusicMode{
    TYPE_TOPMUSIC,
    TYPE_SEARCHMUSIC,
}MusicMode;


    class CAppOnlineMusic : public QObject
    {
        Q_OBJECT

    public:
        // "play" "pause"
        Q_PROPERTY(bool playState MEMBER m_bPlaying  NOTIFY playStateChanged)
        Q_PROPERTY(QString songName MEMBER m_strSongName  NOTIFY songNameChanged)
        Q_PROPERTY(QString singerName MEMBER m_strSingerName NOTIFY singerNameChanged)
        Q_PROPERTY(QString singerPicUrl MEMBER m_strSingerPicUrl NOTIFY singerPicUrlChanged)
        Q_PROPERTY(bool bCollected MEMBER m_bCollected NOTIFY bCollectedChanged)

        // get online music data
        Q_INVOKABLE void getHotData();          // hot
        // set select Tab index
        Q_INVOKABLE void setSelectIndex(int nIndex);
        Q_INVOKABLE void getTopnameMusicData(QString strTopName);
        Q_INVOKABLE void getMusicTypeTop();
        Q_INVOKABLE void getMusicTypeTag();
        Q_INVOKABLE void playMusic(int nIndex);
        Q_INVOKABLE void play();
        Q_INVOKABLE void pause();
        Q_INVOKABLE void resume();
        Q_INVOKABLE void stop();
        Q_INVOKABLE void next();
        Q_INVOKABLE void previous();
        Q_INVOKABLE void searchMusicByKeyWords(QString strKey);
        Q_INVOKABLE void searchMusicDetailDataBySongName(QString strSongName);
        Q_INVOKABLE void searchMusicAlbumDataByAlbumName(QString strAlbumName);
        Q_INVOKABLE void collectMusic(int nIndex);
        Q_INVOKABLE void enterPersonalCenter();
        Q_INVOKABLE void deleteCollectMusic(int nIndex);
        Q_INVOKABLE void deleteHistoryMusic(int nIndex);
        Q_INVOKABLE void deleteAllCollectMusic();
        Q_INVOKABLE void deleteAllHistoryMusic();

    private:
        CAppOnlineMusic();
        ~CAppOnlineMusic();
        static CAppOnlineMusic *m_pInstance;

        // online music top type list data
        QVector<HData_OnlineMusicType> m_onlineMusicTopTypeList;
        QVector<HData_OnlineMusicType> m_onlineMusicSingerTypeList;

        QVector<HData_OnlineMusicType> m_onlineMusicSenceTypeList;
        QVector<HData_OnlineMusicType> m_onlineMusicEmotionTypeList;
        QVector<HData_OnlineMusicType> m_onlineMusicStyleTypeList;
        QVector<HData_OnlineMusicType> m_onlineMusicYearsTypeList;
        QVector<HData_OnlineMusicType> m_onlineMusicLanguageTypeList;

        QVector<HData_OnlineMusicTopnameMusicData> m_onlineMusicTopnameMusicData;
        QVector<HData_OnlineMusicTopnameMusicData> m_onlineMusicHistoryData;
        QVector<HData_OnlineMusicTopnameMusicData> m_onlineMusicCollectyData;

    private:
        bool                m_bCollected;
        bool                m_bPlaying;
        QString             m_strSongName;
        QString             m_strSingerName;
        QString             m_strSingerPicUrl;
        int                 m_nCurrentMusicIndex;
        int                 m_nCurrentSearchedMusicIndex;
        MusicMode           m_musicMode;
        CAppDataBase        m_db;
    private:

        void filterDataForOnlineMusicTopType(CRspOnlineMusicTypeVector& data);
        void filterDataForOnlineMusicSingerType(CRspOnlineMusicTypeVector& data);
        void filterDataForOnlineMusicTagType(CRspOnlineMusicTypeVector& data);
        void filterDataForOnlineMusicRadioType(CRspOnlineMusicTypeVector& data);
        void filterDataForOnlineMusicTopnameMusicData(CRspOnlineMusicTopnameMusicDataVector& data);

        void searchSingerList();
        void selectMusicIsCollected(QString strSongId);

    public:
        static CAppOnlineMusic * getInstance();
        static void deleteInstance();
        bool isPlaying();
    signals:

        void bCollectedChanged();
        void playStateChanged();
        void songNameChanged();
        void singerNameChanged();
        void singerPicUrlChanged();
        void sigQMLMusicPlayingInfo(QString strSongName, QString strSingerName, QString strSingerPicUrl, bool bPlaying);
        void sigQMLSearchMusic(bool bSuccess);

        void sigQMLbCollected(QString strSongId, bool bCollected);
        void sigQMLCollectDataChanged(int nSize);
        void sigQMLHistoryDataChanged(int nSize);
        void sigQMLGetMusicTypeTopDataComplete();
        void sigQMLSetSelectIndex(int nIndex);
        void sigQMLCurrentMusicIndexChanged(int nIndex);

        void sigForUpdateOnlineMusicTopTypeData(const QVector<HData_OnlineMusicType>& data);
        void sigForUpdateOnlineMusicSingerTypeData(const QVector<HData_OnlineMusicType>& data);
        void sigForUpdateOnlineMusicSenceData(const QVector<HData_OnlineMusicType>& data);
        void sigForUpdateOnlineMusicEmotionData(const QVector<HData_OnlineMusicType>& data);
        void sigForUpdateOnlineMusicStyleData(const QVector<HData_OnlineMusicType>& data);\
        void sigForUpdateOnlineMusicYearsData(const QVector<HData_OnlineMusicType>& data);
        void sigForUpdateOnlineMusicLanguageData(const QVector<HData_OnlineMusicType>& data);
        void sigForUpdateOnlineMusicTopnameMusicData(const QVector<HData_OnlineMusicTopnameMusicData>& data);
        void sigForUpdateOnlineMusicSearchedMusicData(const QVector<HData_OnlineMusicTopnameMusicData>& data);
        void sigForUpdateOnlineMusicHistoryData(const QVector<HData_OnlineMusicTopnameMusicData>& data);
        void sigForUpdateOnlineMusicCollectData(const QVector<HData_OnlineMusicTopnameMusicData>& data);

    public slots:

        void slotForRspPlayOnlineMusic(int code, const QString& description);
        void slotForRspPauseOnlineMusic(int code, const QString& description);
        void slotForRspResumeOnlineMusic(int code, const QString& description);
        void slotForRspStopOnlineMusic(int code, const QString& description);


        void slotForRspGetOnlineMusicTopType(QString& data);
        void slotForRspGetOnlineMusicTag(QString& data);
        void slotForRspGetOnlineMusicSingerTypeName(QString& data);
        void slotForRspGetOnlineMusicRadio(QString& data);
        void slotForRspGetOnlineMusicTopnameMusicData(QString& data);
    };

}


#endif // CAPPONLINEMUSIC_H
