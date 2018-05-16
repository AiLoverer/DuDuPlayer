#ifndef LOCALMUSIC_H
#define LOCALMUSIC_H
/***
 * 音乐播放控制 C++ code
 */
#include <QObject>
#include <QVector>
#include "../../framework/dudu.h"
namespace QTDUDU {
#ifdef OS_WIN
    #define MUSIC_PATH "d:/KuGou"
    #define MUSIC_LYRIC_PATH "d:/KuGou/Lyric"
#elif
    #define MUSIC_PATH "/fs/mmc1/appdata/HMI/"
#endif

    class LocalMusic : public QObject
    {
        Q_OBJECT
    public:
        Q_PROPERTY(int nplayIndex MEMBER m_nPlayIndex  NOTIFY nplayIndexChanged)
        Q_PROPERTY(QStringList lyrics MEMBER m_lstLyric NOTIFY lyricsChanged)
        Q_PROPERTY(QStringList times MEMBER m_lstTime NOTIFY timeChanged)
    public:
        Q_INVOKABLE void getMusicData();
        Q_INVOKABLE void playMusic(int nIndex);
        Q_INVOKABLE void pauseMusic();
        Q_INVOKABLE void nextMusic();
        Q_INVOKABLE void lastMusic();
        Q_INVOKABLE void setPlayPosition(int nPosition);
        Q_INVOKABLE int getIndexByTime(int mmTime); // 传入参数为时间，单位是毫秒
    protected:
        LocalMusic(QObject *parent = 0);
        ~LocalMusic();
    private:

        // 读取本地音频文件--所有歌曲路径
        bool readMusic(QString strPath, QString strFormat);

        // ***歌词相关***
        /* krc codec
        const int   Keys[16] =  {64, 71, 97, 119, 94, 50, 116, 71, 81, 54, 49, 45, 206, 210, 110, 105};

        typedef int  CONVERT_CODE;

        #define   CONVERT_SUCCESS       0x00
        #define   CONVERT_FILE_EMPTY    0x01
        #define   CONVERT_PARA_ERR      0x02
        #define   CONVERT_FORMAT_ERR    0x03
        #define   CONVERT_UNKNOWN       0x04
        */
        // UTF-8编码检测
        bool IsUTF8(const void* pBuffer, long size);
        // 破解krc文件
        //CONVERT_CODE  KrcDecode(QFile  &KrcFile, QFile  &LrcFile);
        //  加载歌词文件
        void    loadLyricFile(QString   strFileName);
    private:
        int m_nPlayIndex;
        // ***歌词相关***
        //  歌词对应的时间戳
        QStringList   m_lstTime;
        //  歌词
        QStringList  m_lstLyric;
        // 歌词路径
        QString     m_strlyricPath;
    public:
        static LocalMusic *getInstance();
        void deleteInstance();
        void getQMLMediaPlayer();
        void play(QString strSongPath);
    private:
        static LocalMusic* m_pInstance;
    private:
        QVector<MusicInfo> m_lstMusicInfo;
        QMediaPlayer*    m_pAudioPlayer;

    signals:

        void nplayIndexChanged();
        void lyricsChanged();
        void timeChanged();

        void sigForUpdateLocalMusicData(const QVector<MusicInfo>& data);
        void sigQMLPlay(QString strSongName, QString strSongPath, QString strSingerPic, int nIndex);
        void sigQMLPause();
        void sigQMLPlayIndexChanged(int nIndex);
        void sigQMLPositionChanged(long position);
        void sigQMLDurationChanged(long duration);

    public slots:
        void positionChanged(qint64 position);
        void durationChanged(qint64 duration);
    };

}

#endif // LOCALMUSIC_H
