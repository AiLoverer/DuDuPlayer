#ifndef CNETWORKMANAGER_H
#define CNETWORKMANAGER_H

#include <QObject>
#include "../../framework/dudu.h"
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QTimer>
namespace QTDUDU {
    class CNetworkManager : public QObject
    {
        Q_OBJECT
    protected:
        explicit CNetworkManager(QObject *parent = 0);
    public:
        static CNetworkManager* getInstance();

        void getData(UINT type);
        void addParam(QString key, QString val);
        void setOpenId(QString openid) {m_strOpenId = openid;}
        void setOpenKey(QString openkey)   {m_strOpenKey = openkey;}
        void setPrefix(QString prefix) {m_strPrefix = prefix;}
    private:
        static CNetworkManager* m_pInstance;

        void createSign(bool special=false);
        QString sortHash(bool specail=false);
        QString createOnlineMusicUrlString(UINT apitype);
        QNetworkRequest createRequest(UINT apiType);
        void accessNewWork(UINT apitype);
    private:
        // request参数值
        // http://autoapi.openspeech.cn/api/v2/music/songs/?words=刘德华&openid=123456&
        // clientType =4&sId=1001&sign=08a376375b1a5d84ce7ff0360a06095232ccbf82
        QString m_strOpenId; // 厂商唯一标识，用于标识厂商，后续增加定制需求所用
        QString m_strOpenKey;
        QString m_strSign; // 请求签名，对除sign外所有参数进行签名
        QString m_strPrefix;
        QHash<QString,QString> m_paramMap;
        QHash<QString,QString> m_specialMap;
        QNetworkAccessManager *m_networkAccess;
        UINT m_currentRequest;
        UINT m_nameIndex;
        UINT m_IDIndex;
        bool m_isRequest;
        bool m_hasSort;
        QVector<UINT> m_waitList;
        QTimer m_tm;

    signals:
        void dataReady(UINT type,QString data);
        void downloadError();
        void requestOccur();
    public slots:
        void downloadFinished(QNetworkReply *reply);
        void previousFinished();
        //void slotForUSBDeviceChanged(const DeviceStateChange& state);
        //void slotForCarLifeDeviceChanged(QString id, QString type, QString status);
        void handleTimeOut();
    };
}


#endif // CNETWORKMANAGER_H
