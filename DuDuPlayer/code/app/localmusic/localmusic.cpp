#include "localmusic.h"
#include "../../framework/dudu.h"

//extern QQmlApplicationEngine* g_pEngine;
namespace QTDUDU {

LocalMusic* LocalMusic::m_pInstance = NULL;
void LocalMusic::getMusicData()
{
    if(m_lstMusicInfo.size() > 0)
    {
        emit sigForUpdateLocalMusicData(m_lstMusicInfo);
    }
}

void LocalMusic::playMusic(int nIndex)
{
    if(m_lstMusicInfo.size() <= 0 || nIndex > m_lstMusicInfo.size())
    {
        return ;
    }
    MusicInfo musicInfo;
    musicInfo = m_lstMusicInfo.at(nIndex);
    m_nPlayIndex = nIndex;
    loadLyricFile(musicInfo.strLyricPath);
    play(musicInfo.strSongPath);
    emit sigQMLPlay(musicInfo.strSongName, musicInfo.strSongPath, "", m_nPlayIndex);
    emit sigQMLPlayIndexChanged(m_nPlayIndex);

}

void LocalMusic::pauseMusic()
{
    m_pAudioPlayer->pause();
    emit sigQMLPause();
}

void LocalMusic::nextMusic()
{
    if(m_nPlayIndex + 1 > m_lstMusicInfo.size())
    {
         return;
    }
    MusicInfo musicInfo;
    m_nPlayIndex++;
    musicInfo = m_lstMusicInfo.at(m_nPlayIndex);
    play(musicInfo.strSongPath);
    emit sigQMLPlay(musicInfo.strSongName, musicInfo.strSongPath, "", m_nPlayIndex);
    emit sigQMLPlayIndexChanged(m_nPlayIndex);

}

void LocalMusic::lastMusic()
{
    if(m_nPlayIndex - 1 < 0)
    {
         return;
    }
    MusicInfo musicInfo;
    m_nPlayIndex--;
    musicInfo = m_lstMusicInfo.at(m_nPlayIndex);
    play(musicInfo.strSongPath);
    emit sigQMLPlay(musicInfo.strSongName, musicInfo.strSongPath, "", m_nPlayIndex);
    emit sigQMLPlayIndexChanged(m_nPlayIndex);
}

void LocalMusic::setPlayPosition(int nPosition)
{
    m_pAudioPlayer->setPosition(nPosition * 1000);
}

int LocalMusic::getIndexByTime(int mmTime)
{
    if(m_lstTime.size() ==  0)
    {
        return 0;
    }

    //  与第一个时间点比较
    QString strTimeTemp    =   m_lstTime[0];
    if(mmTime    <   strTimeTemp.toInt())
    {
        return 0;
    }

    for(int i = 1; i < m_lstTime.size(); i++)
    {
        QString&    strTime    =   m_lstTime[i];
        int time    =   strTime.toInt();

        if(mmTime    <   time)
        {
            if(mmTime >  m_lstTime[i-1].toInt())
            {
                return i-1;
            }
        }
    }

    return 0;
}

LocalMusic::LocalMusic(QObject *parent) : QObject(parent)
{
    m_strlyricPath = "";
    m_pAudioPlayer = new QMediaPlayer();
    m_nPlayIndex = 0;
    readMusic(MUSIC_PATH, "*.mp3");
    connect(m_pAudioPlayer, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    connect(m_pAudioPlayer, SIGNAL(durationChanged(qint64)), this, SLOT(durationChanged(qint64)));
}

LocalMusic::~LocalMusic()
{
    if(m_pAudioPlayer != NULL)
    {
        delete m_pAudioPlayer;
        m_pAudioPlayer = NULL;
    }
}

    /*
     * 函  数: readMusic
     * 功  能: 读取特定格式的文件
     * 参  数: QString strPath   文件夹路径
     *        QString strFormat 文件格式 mp3/PNG/MPS/AVI...
     * 返回值: 类型 bool
     *        如果函数执行成功, 返回true 否则false;
     */
    bool LocalMusic::readMusic(QString strPath, QString strFormat)
    {
        m_lstMusicInfo.clear();
        // 自动扫描文件
        QDir            dir(strPath);
        QStringList     listSong;       // 保存歌曲名list
        QFileInfoList   fileInfoList;   // 文件信息list
        QFileInfo       fileInfo;       // 单个文件信息
        QString         strSongName;    // 歌名

        listSong << strFormat;
        dir.setNameFilters(listSong);
        fileInfoList = dir.entryInfoList(); // 列出所有符合条件的文件信息
        int nIndex = 0;
        while(nIndex < fileInfoList.length())
        {
            fileInfo        = fileInfoList.at(nIndex);  // 取出nIndex位置文件信息
            strSongName     = fileInfo.fileName();      // 歌曲路径
            nIndex++;
            MusicInfo musicInfo;

            QString strName = strSongName;
            int nPos = strName.lastIndexOf(".");
            QString name = strName.left(nPos);

            musicInfo.strSongName   = name;
            musicInfo.strSongPath   = fileInfo.filePath();
            musicInfo.strLyricPath  = strPath + "/Lyric/" + name + ".lrc";
            //qDebug()<<"lyric path" << musicInfo.strLyricPath ;
            //qDebug()<<"song name" << musicInfo.strSongName;
            //qDebug()<<"song path" << fileInfo.filePath();
            m_lstMusicInfo.append(musicInfo);
        }
        if(m_lstMusicInfo.size() <= 0)
        {
            return false;
        }
        else
        {
            qDebug()<<"send music data : "<< m_lstMusicInfo.size();
            //emit sigForUpdateLocalMusicData(m_lstMusicInfo);
            return true;
        }
    }
    /*
     * 函  数: IsUTF8
     * 功  能: 判断文件是否是UTF-8编码
     * 参  数: const void *pBuffer   要判断的文件二进制数据
     *        long size   二进制文件长度
     * 返回值: 类型 bool
     *        如果函数执行成功, 返回true 否则false;
     */
    bool LocalMusic::IsUTF8(const void *pBuffer, long size)
    {
        bool IsUTF8 = true;
        unsigned char* start = (unsigned char*)pBuffer;
        unsigned char* end = (unsigned char*)pBuffer + size;
        while (start < end)
        {
            if (*start < 0x80) // (10000000): 值小于0x80的为ASCII字符
            {
               start++;
            }
            else if (*start < (0xC0)) // (11000000): 值介于0x80与0xC0之间的为无效UTF-8字符
            {
               IsUTF8 = false;
               break;
            }
            else if (*start < (0xE0)) // (11100000): 此范围内为2字节UTF-8字符
            {
               if (start >= end - 1)
                   break;
               if ((start[1] & (0xC0)) != 0x80)
               {
                   IsUTF8 = false;
                   break;
               }
               start += 2;
            }
            else if (*start < (0xF0)) // (11110000): 此范围内为3字节UTF-8字符
            {
               if (start >= end - 2)
                   break;
               if ((start[1] & (0xC0)) != 0x80 || (start[2] & (0xC0)) != 0x80)
               {
                   IsUTF8 = false;
                   break;
               }
               start += 3;
            }
            else
            {
               IsUTF8 = false;
               break;
            }
       }
        return IsUTF8;
    }

    void LocalMusic::loadLyricFile(QString strFileName)
    {
        qDebug()<< "strFileName"<<strFileName;
        //  清除历史数据
        m_lstLyric.clear();
        m_lstTime.clear();

        emit lyricsChanged();
        emit timeChanged();

        //  歌词第一行置为空
        m_lstLyric.append("");

        QString temp = "";
        if(strFileName.isEmpty())
        {
            //qDebug()<< "not find lyric file";
            temp = QString(tr("未发现歌词文件！"));
            m_lstLyric<<""<<""<<temp<<""<<"";
            m_lstLyric.append("");
            m_lstLyric.append("");

            emit lyricsChanged();
            emit timeChanged();
            return;
        }
        //strFileName = tr("D:/KuGou/Lyric/路童 王锋英 - 故乡故乡.lrc");
        int nIndex = strFileName.lastIndexOf(".");
        QString strSuffix = strFileName.mid(nIndex, 4);
        if(strSuffix.compare(".lrc") != 0)
        {
            //qDebug()<< "lyric file is not lrc file";
            temp = QString(tr("歌词文件格式不支持！"));
            m_lstLyric<<""<<""<<temp<<""<<"";
            m_lstLyric.append("");
            m_lstLyric.append("");

            emit lyricsChanged();
            emit timeChanged();
            return;
        }

        QFile file(strFileName);
        //QFile file("D:/KuGou/Lyric/路童 王锋英 - 故乡故乡.lrc");
        if(file.open(QIODevice::ReadOnly))
        {
            //qDebug()<< "open file 1";
            /*
            字节	编码格式
            00 00 FE FF	UTF-32，big-endian
            FF FE 00 00	UTF-32，小端
            FE FF       UTF-16，big-endian
            FF FE       UTF-16，little-endian
            EF BB BF	UTF-8
            */
            //QTextCodec *codec = QTextCodec::codecForLocale();
            //temp = codec->toUnicode(file.readAll());

            QByteArray codeBuffer = file.readAll();
            QString codeType = "utf-8";
            if(IsUTF8(codeBuffer.data(), codeBuffer.size()))
            {
                if(codeBuffer[0] > 0xEF)
                {
                   if(codeBuffer[0] == 0xEF && codeBuffer[1] == 0xBB)
                   {
                       codeType = "utf-8";
                   }
                   else if(codeBuffer[0] == 0xFE && codeBuffer[1] == 0xFF)
                   {
                       codeType = "utf-16";
                   }
                   else if(codeBuffer[0] == 0xFF && codeBuffer[1] == 0xFE)
                   {
                       codeType = "utf-32";
                   }
                   else
                   {
                       codeType = "utf-8";
                   }
                }
                else
                {
                    codeType = "utf-8";
                }
            }
            else
            {
                codeType = "gb2312";
            }


            /* 遍历支持的编码格式
            QList<QByteArray> listCodec = QTextCodec::availableCodecs();
            for(int n = 0; n < listCodec.size(); ++n)
            {
                QString str = listCodec.at(n);
                QTextCodec *codec = QTextCodec::codecForName(listCodec.at(n));
                if(codec != NULL)
                {
                    QTextCodec::setCodecForLocale(codec );
                    temp = codec->toUnicode(file.readAll());
                    break;
                }
            }
            */
            //qDebug()<< "lyric file codec is "<< codeType;
            QTextCodec *codec = QTextCodec::codecForName(codeType.toLatin1().data());
            QTextCodec::setCodecForLocale(codec );
            temp = codec->toUnicode(codeBuffer);

            QList<QString> tempList;
            tempList = temp.split("\n");

            for(int i=0;i<tempList.size();i++)
            {
                QString temps = tempList.at(i);

                if(temps.size()<2)
                {
                    continue;
                }

                if(temps.at(1).digitValue() >= 0)
                {
                    uint count6 = temps.at(1).digitValue() * 10 * 60 * 1000;
                    uint count5 = temps.at(2).digitValue() * 60 * 1000;
                    uint count4 = temps.at(4).digitValue() * 10 * 1000;
                    uint count3 = temps.at(5).digitValue() * 1000;
                    uint count2 = temps.at(7).digitValue() * 100;
                    uint count1 = temps.at(8).digitValue() * 10;

                    uint sum = count1 + count2 + count3 + count4 + count5 + count6;
                    temps.remove(0,10);

                    //  如果只有时间，没有歌词，显示空行
                    m_lstLyric.append(temps);
                    m_lstTime.append(QString::number(sum));
                }
            }

            if(m_lstLyric.size()    ==  1)
            {
                //qDebug()<< "lyric file codec can not recognise";
                temp = QString(tr("歌词编码格式不能识别！"));

                m_lstLyric<<""<<temp<<""<<"";
            }
        }
        else
        {
            //qDebug()<< "lyric file open failed";
            temp = QString(tr("歌词文件打开失败！"));
            m_lstLyric<<""<<""<<temp<<""<<"";
        }

        file.close();
        m_lstLyric.append("");
        m_lstLyric.append("");

        emit lyricsChanged();
        emit timeChanged();

        // 恢复编码格式
        QTextCodec *codec = QTextCodec::codecForName("utf-8");
        QTextCodec::setCodecForLocale(codec );
        return;
    }

    LocalMusic *LocalMusic::getInstance()
    {
        if(m_pInstance == NULL)
        {
            m_pInstance = new LocalMusic();
        }
        return m_pInstance;
    }

    void LocalMusic::deleteInstance()
    {
        if(m_pInstance != NULL)
        {
            delete m_pInstance;
            m_pInstance = NULL;
        }
    }
    /*
     * 函  数: getQMLMediaPlayer
     * 功  能: C++调用QML中MediaPlayer对象 然后获取文件所有信息
     * 参  数: 无
     * 返回值: 无
     */
    void LocalMusic::getQMLMediaPlayer()
    {
/*
        if(g_pEngine != NULL)
        {
            QObject* root = NULL;

            QList<QObject*> rootObjects = g_pEngine->rootObjects();
            int nCount = rootObjects.size();
            qDebug()<<"g_pEngine is not NULL" << "nCount :" + nCount;
            for(int n = 0; n < nCount; ++n)
            {
                qDebug()<<"n: " + n;
                if(rootObjects.at(n)->objectName() == "rootObject")
                {
                    qDebug()<<"Find rootObject : n " + n;
                    root = rootObjects.at(n);
                    break;
                }
            }
            if(root == NULL)
            {
                qDebug()<<"Not find rootObject";
                return ;
            }
            QObject *qmlMediaPlayer = NULL; // The QML MediaPlayer object
            qmlMediaPlayer = root->findChild<QObject*>("audioPlayerObject");
            if(qmlMediaPlayer)
            {
                qDebug()<<"Start find QMediaPlayer and QMediaMetaData";
                QMediaPlayer *pPlayer = qvariant_cast<QMediaPlayer *>(qmlMediaPlayer->property("mediaObject"));
                if(pPlayer->isMetaDataAvailable())
                {
                    QString strTitle = pPlayer->metaData(QMediaMetaData::Title).toString();
                    qDebug()<<"title : "<< strTitle;
                }
                else
                {
                    qDebug()<<"QMediaPlayer is not avaliable";
                }

            }
            else
            {
                qDebug()<<"audioPlayerObject is not avaliable";
            }

        }
        else
        {
            qDebug()<<"g_pEngine is  NULL";
        }
        */

    }

    void LocalMusic::play(QString strSongPath)
    {
        m_pAudioPlayer->setMedia(QUrl::fromLocalFile(strSongPath));
        m_pAudioPlayer->play();
    }

    void LocalMusic::positionChanged(qint64 position)
    {
       // qDebug()<<"positionChanged :"<< position / 1000;
        emit sigQMLPositionChanged(position / 1000);
    }

    void LocalMusic::durationChanged(qint64 duration)
    {
        //qDebug()<<"durationChanged :"<< duration / 1000;
        emit sigQMLDurationChanged(duration / 1000);
    }

}

