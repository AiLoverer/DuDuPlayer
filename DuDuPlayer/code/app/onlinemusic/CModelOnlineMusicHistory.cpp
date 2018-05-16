#include "CModelOnlineMusicHistory.h"

namespace QTDUDU {

    class CModelOnlineMusicHistoryPrivate
    {
    public:
        CModelOnlineMusicHistoryPrivate(CModelOnlineMusicHistory* model):
            m_model(model)
        {
            m_roleNames.insert(Role_SongName, "songname");
            m_roleNames.insert(Role_SingerName, "singername");
            m_roleNames.insert(Role_SingerPicUrl, "singerpicurl");
            m_roleNames.insert(Role_Score, "score");
            m_roleNames.insert(Role_TopNo, "topno");
            m_roleNames.insert(Role_ExtraUrl, "extralUrl");
            m_roleNames.insert(Role_CacheID, "cacheId");
            m_roleNames.insert(Role_LyricUrl, "lyriUrl");
            m_roleNames.insert(Role_PlayUrl, "playUrl");
            m_roleNames.insert(Role_ExtraUrl, "extralUrl");
            m_roleNames.insert(Role_SongId, "songId");
            m_roleNames.insert(Role_SingerId, "singerId");


        }

        enum {
            Role_SongName = Qt::UserRole + 1,
            Role_SingerName,
            Role_SingerPicUrl,
            Role_Score,
            Role_TopNo,
            Role_ExtraUrl,
            Role_CacheID,
            Role_LyricUrl,
            Role_PlayUrl,
            Role_SongId,
            Role_SingerId
        };

        CModelOnlineMusicHistory*                       m_model;
        QHash<int, QByteArray>                          m_roleNames;
        QVector<HData_OnlineMusicTopnameMusicData>      m_datas;
    };

    CModelOnlineMusicHistory::CModelOnlineMusicHistory(QObject *parent) :
        QAbstractListModel(parent),
        m_dPtr(new CModelOnlineMusicHistoryPrivate(this))
    {
        qRegisterMetaType<QVector<HData_OnlineMusicTopnameMusicData>>("QVector<HData_OnlineMusicTopnameMusicData>");

        connect(CAppOnlineMusic::getInstance(), SIGNAL(sigForUpdateOnlineMusicHistoryData(QVector<HData_OnlineMusicTopnameMusicData>)),
        this, SLOT(slotForOnlineMusicHistory(QVector<HData_OnlineMusicTopnameMusicData>)));
    }

    CModelOnlineMusicHistory::~CModelOnlineMusicHistory()
    {
        if (NULL != m_dPtr) {
            delete m_dPtr;
            m_dPtr = NULL;
        }
    }

    int CModelOnlineMusicHistory::rowCount(const QModelIndex &parent) const
    {
        Q_UNUSED(parent)
        return m_dPtr->m_datas.size();
    }

    QVariant CModelOnlineMusicHistory::data(const QModelIndex &index, int role) const
    {
        if (index.row() < 0 || index.row() >= m_dPtr->m_datas.count())
        {
            return QVariant();
        }

        if (role == m_dPtr->Role_SongName) {
            return m_dPtr->m_datas.at(index.row()).strSongName;
        }
        else if (role == m_dPtr->Role_SingerName) {
            return m_dPtr->m_datas.at(index.row()).strSingerName;
        }
        else if (role == m_dPtr->Role_SingerPicUrl) {
            return m_dPtr->m_datas.at(index.row()).strSingerPicUrl;
        }
        else if (role == m_dPtr->Role_Score) {
            return m_dPtr->m_datas.at(index.row()).strScore;
        }
        else if (role == m_dPtr->Role_TopNo) {
            return m_dPtr->m_datas.at(index.row()).strTopNo;
        }
        else if (role == m_dPtr->Role_ExtraUrl) {
            return m_dPtr->m_datas.at(index.row()).strExtraUrl;
        }
        else if (role == m_dPtr->Role_CacheID) {
            return m_dPtr->m_datas.at(index.row()).strCacheID;
        }
        else if (role == m_dPtr->Role_LyricUrl) {
            return m_dPtr->m_datas.at(index.row()).strLyricUrl;
        }
        else if (role == m_dPtr->Role_PlayUrl) {
            return m_dPtr->m_datas.at(index.row()).strPlayUrl;
        }
        else if (role == m_dPtr->Role_SongId) {
            return m_dPtr->m_datas.at(index.row()).strSongID;
        }
        else if (role == m_dPtr->Role_SingerId) {
            return m_dPtr->m_datas.at(index.row()).strSingerID;
        }

        return QVariant();

    }

    QHash<int, QByteArray> CModelOnlineMusicHistory::roleNames() const
    {
        return m_dPtr->m_roleNames;
    }

    void CModelOnlineMusicHistory::slotForOnlineMusicHistory(const QVector<HData_OnlineMusicTopnameMusicData> &data)
    {
        beginResetModel();
        m_dPtr->m_datas = data;
        endResetModel();

        //qDebug()<<"slot For OnlineMusic TopName data size is : "<< data.size() ;
    }
}

