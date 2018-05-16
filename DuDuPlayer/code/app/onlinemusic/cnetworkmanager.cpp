#include "cnetworkmanager.h"

namespace QTDUDU {
    CNetworkManager* CNetworkManager::m_pInstance = NULL;
    CNetworkManager::CNetworkManager(QObject *parent)
        : QObject(parent)
        ,m_isRequest(false)
        ,m_hasSort(false)
        ,m_nameIndex(0)
        ,m_IDIndex(0)
    {
        m_networkAccess = new QNetworkAccessManager(this);
        connect(m_networkAccess, SIGNAL(finished(QNetworkReply*)), this, SLOT(downloadFinished(QNetworkReply*)));
        connect(this,SIGNAL(requestOccur()),this,SLOT(previousFinished()));
        //connect(CService::media(), SIGNAL(sigDeviceStateChange(DeviceStateChange)),
        // this, SLOT(slotForUSBDeviceChanged(DeviceStateChange)));
        // connect(CService::carLife(), SIGNAL(sigDeviceStatusChanged(QString,QString,QString)),
        //this, SLOT(slotForCarLifeDeviceChanged(QString,QString,QString)));
        connect(&m_tm,SIGNAL(timeout()),this,SLOT(handleTimeOut()));
    }

    CNetworkManager *CNetworkManager::getInstance()
    {
        if(m_pInstance == NULL)
        {
            m_pInstance = new CNetworkManager();
        }
        return m_pInstance;
    }

    void CNetworkManager::getData(UINT type)
    {
#ifdef Q_OS_QNX
    char* path;
    if(setenv("SOCK","/alt",1) == 0)
    {
        if((path = getenv("SOCK")) != NULL)
        {
            LOGI("**********SOCK=%s*************\n", path);
        }
        else
        {
            LOGI("set sock failed!\n");
        }
    }
#endif
    if (!m_isRequest)
    {
       //LOGI("-------------accessNetWork()---------");
       accessNewWork(type);
    }
    else
    {
        //LOGI("-------------mWaitList.push_back---------");
        m_waitList.push_back(type);
    }
    }

    void CNetworkManager::addParam(QString key, QString val)
    {
        if (m_hasSort)
        {
            m_paramMap.clear();
            m_hasSort = false;
        }

        m_paramMap.insertMulti(key,val);
    }

    void CNetworkManager::createSign(bool special)
    {
        m_paramMap.insert("clientType","0");
        QString keyval = sortHash(special);
        m_hasSort = true;
        QString openid = m_strOpenId;
        QString shaobj = openid.append(keyval).append(m_strOpenKey);

        //qDebug()<<"sha object="<<shaobj;
        //LOGI("--yelo--: sha object is %s", const_cast<char*>(qPrintable(shaobj)));

        QByteArray byteArray;
        byteArray = QCryptographicHash::hash(shaobj.toUtf8(), QCryptographicHash::Sha1);
        m_strSign.append(byteArray.toHex());

        //qDebug()<<"sign="<<m_strSign;
        //LOGI("--yelo--: sign is %s", const_cast<char*>(qPrintable(m_strSign)));
    }

    QString CNetworkManager::sortHash(bool specail)
    {
        QString keyval;
        QList<QString> keyList;

        if (specail)
        {
            keyList = m_specialMap.keys();
        }
        else
        {
            keyList = m_paramMap.keys();
        }

        qSort(keyList);

        if (specail)
        {
            for (int i=0; i<keyList.size(); i++)
            {
                keyval+=keyList[i]+m_specialMap[keyList[i]];
            }

            m_specialMap.clear();
        }
        else
        {
            for (int i=0; i<keyList.size(); i++)
            {
                keyval+=keyList[i]+m_paramMap[keyList[i]];
            }
        }

        qDebug()<<"sort result="<<keyval;
        return keyval;
    }

    QString CNetworkManager::createOnlineMusicUrlString(UINT apitype)
    {
        QString apiAddress;

        switch(apitype)
        {
        case 11: //获取网络电台列表
            apiAddress = "radio/lists?";
            break;
        case 12:
        {
            QString tmp = "radio/";
            QString name = m_paramMap["radioName"];
            apiAddress = tmp.append(name).append("/search?");
            break;
        }
        case 13:
            apiAddress = "radio/stationlists?";
            break;
        case 14:
            apiAddress = "radio/trackquery?";
            break;
        case 15:
        {
            QString tmp = "radio/";
            QList<QString> keylist = m_paramMap.keys();
            QList<QString> vallist = m_paramMap.values();
            QString name;
            QString id;
            for (int i=0;i<keylist.size();i++)
            {
                if(keylist[i]=="clientType")
                {
                    keylist.removeAt(i);
                    vallist.removeAt(i);
                }
            }

            if (keylist.size()==2)
            {
                name = m_paramMap["radioName"];
                id = m_paramMap["radioID"];
                apiAddress = tmp.append(name).append("/").append(id).append("/program?");
            }
            else if(m_IDIndex == 0)
            {
                m_IDIndex = keylist.size()/2;
            }

            if(m_IDIndex > 0)
            {
                name = vallist[m_nameIndex];
                id = vallist[m_IDIndex];
                apiAddress = tmp.append(name).append("/").append(id).append("/program?");

                m_specialMap.insert(keylist[m_nameIndex],vallist[m_nameIndex]);
                m_specialMap.insert(keylist[m_IDIndex],vallist[m_IDIndex]);
                m_specialMap.insert("clientType","0");
                createSign(true);

                QString urlstring = m_strPrefix;
                QString paramString;
                paramString = keylist[m_nameIndex].append("=").append(vallist[m_nameIndex]).append("&").append(keylist[m_IDIndex]).append("=")
                        .append(vallist[m_IDIndex]).append("&").append("clientType=0&");
                urlstring.append(apiAddress).append(paramString).append("openId=").append(m_strOpenId).append("&")
                        .append("sign=").append(m_strSign);

                m_nameIndex++;
                m_IDIndex++;
                return urlstring;
            }

            break;
        }
        case 16:
        {
            QString tmp = "radio/living/";
            QString id = m_paramMap["radioID"];
            apiAddress = tmp.append(id).append("/program?");
            break;
        }
        case 17:
            apiAddress = "radio/ranking?";
            break;
        case 18:
            apiAddress = "radio/living?";
            break;
        case 211:
        case 212:
        case 213:
        case 214:
        {
            QString tmp = "music/";
            QList<QString> keylist = m_paramMap.keys();
            QList<QString> vallist = m_paramMap.values();
            QString type;
            for (int i=0;i<keylist.size();i++)
            {
                if(keylist[i]=="clientType")
                {
                    keylist.removeAt(i);
                    vallist.removeAt(i);
                }
            }

            if (keylist.size()==1)
            {
                type = m_paramMap["type"];
                apiAddress = tmp.append(type).append("/lists?");
            }
            else
            {
                type = vallist[m_nameIndex];
                apiAddress = tmp.append(type).append("/lists?");

                m_specialMap.insert(keylist[m_nameIndex],vallist[m_nameIndex]);
                m_specialMap.insert("clientType","0");
                createSign(true);

                QString urlstring = m_strPrefix;
                QString paramString;
                paramString = keylist[m_nameIndex].append("=").append(vallist[m_nameIndex]).append("&").append("clientType=0&");
                urlstring.append(apiAddress).append(paramString).append("openId=").append(m_strOpenId).append("&")
                        .append("sign=").append(m_strSign);

                m_nameIndex++;
                return urlstring;
            }
            break;
        }
        case 22:
            apiAddress = "music/songs/?";
            break;
        case 23:
        {
            QString tmp = "music/top/";
            QString topname = m_paramMap["topName"];
            apiAddress = tmp.append(topname).append("?");
            break;
        }
        case 24:
            apiAddress = "music/singers?";
            break;
        case 25:
            apiAddress = "music/detail?";
            break;
        case 26:
            apiAddress = "music/albums/?";
            break;
        case 27:
        {
            QString tmp = "music/album/";
            QString id = m_paramMap["albumId"];
            apiAddress = tmp.append(id).append("/songs?");
            break;
        }
        case 28:
        {
            QString tmp = "music/singers/";
            QString id = m_paramMap["singerId"];
            apiAddress = tmp.append(id).append("/songs?");
            break;
        }
        case 29:
            apiAddress = "music/songs/playurl?";
            break;
        case 210:
            apiAddress = "music/song/hotwords?";
            break;
        case 31:
            apiAddress = "news/types?";
            break;
        case 320:
        case 321:
        case 322:
        case 323:
        case 324:
        case 325:
        case 326:
            apiAddress = "news?";
            break;
        case 33:
        {
            QString tmp = "news/";
            QString id = m_paramMap["id"];
            apiAddress = tmp.append(id).append("?");
            break;
        }
        case 71: //天气
           apiAddress = "weather?" ;
           break;
        case 72:
            apiAddress = "weather/index/all?";
            break;
        case 73:
            apiAddress = "weather/airquality?";
            break;
        case 141:
            apiAddress = "programe/type?";
            break;
        case 142:
        {
            QString tmp = "programe/type/";
            QString id = m_paramMap["typeId"];
            apiAddress = tmp.append(id).append("/album?");
            break;
        }
        case 143:
        {
            QString tmp = "programe/album/";
            QString id = m_paramMap["albumId"];
            apiAddress = tmp.append(id).append("/detail?");
            break;
        }
        case 144:
        {
            QString tmp = "programe/album/";
            QString id = m_paramMap["albumId"];
            apiAddress = tmp.append(id).append("/track?");
            break;
        }
        case 145:
        {
            QString tmp = "programe/track/";
            QString id = m_paramMap["trackId"];
            apiAddress = tmp.append(id).append("/detail?");
            break;
        }
        case 146:
            apiAddress = "programe?";
            break;
        case 147:
            apiAddress = "radio/trackquery?";
            break;
        case 148:
            apiAddress = "programe/top/album?";
            break;
        case 149:
            apiAddress = "programe/last?";
            break;
        case 1410:
            apiAddress = "programe/search?";
            break;
        }

        //http://autoapi.openspeech.cn/api/v2/radio/lists?updateTime=12345&openId=jianghuai&clientType=0&
        //sign=b3d3755b366fcb8b02055f9597191b7827da1dfa
        createSign();
        QString paramString;
        QString prekey="";
        QHashIterator<QString, QString> i(m_paramMap);
        while(i.hasNext())
        {
            i.next();
            QString key = i.key();
            QString tmp = key;
            QString value = i.value();
            if (key!=prekey)
                paramString += key.append("=").append(value).append("&");

            prekey = tmp;
        }

        QString urlstring = m_strPrefix;
        urlstring.append(apiAddress).append(paramString).append("openId=").append(m_strOpenId).append("&").append("sign=").append(m_strSign);

        return urlstring;
    }

    QNetworkRequest CNetworkManager::createRequest(UINT apiType)
    {
        QString string = createOnlineMusicUrlString(apiType);
        qDebug()<<"url="<<string;
        m_strSign.clear();
        QUrl url(string);
        QNetworkRequest request(url);
        return request;
    }

    void CNetworkManager::accessNewWork(UINT apitype)
    {
        m_currentRequest = apitype;
        QNetworkRequest request = createRequest(apitype);
        m_networkAccess->get(request);
        m_isRequest = true;
        //启动超时定时，8s
       if (m_tm.isActive())
           m_tm.stop();
       m_tm.start(8000);
    }

    void CNetworkManager::downloadFinished(QNetworkReply *reply)
    {
        QString data;
        if (reply->error())
        {
           qDebug() << "download error: " << reply->errorString();
           //LOGI("-------------emit downloadError()---------");
           emit downloadError();
           m_waitList.clear();
           m_isRequest = false;
        }
        else
        {
            data = reply->readAll();
            emit dataReady(m_currentRequest,data);
            //LOGI("-------------dataReady---------%s\n", const_cast<char*>(qPrintable(data)));

            if (m_waitList.size() > 0)
            {
                //LOGI("------------- emit requestOccur()---------");
                emit requestOccur();
            }
            else
            {
                //LOGI("------------- isRequest = false---------");
                m_isRequest = false;
                m_paramMap.clear();
                m_specialMap.clear();
                m_nameIndex = 0;
                m_IDIndex = 0;
            }
        }

        reply->deleteLater();
    }

    void CNetworkManager::previousFinished()
    {
        m_currentRequest = m_waitList.first();
        QNetworkRequest request = createRequest(m_currentRequest);
        m_networkAccess->get(request);
        m_waitList.pop_front();
    }

    void CNetworkManager::handleTimeOut()
    {
        m_isRequest = false;
        m_waitList.clear();
        m_tm.stop();
    }
}

