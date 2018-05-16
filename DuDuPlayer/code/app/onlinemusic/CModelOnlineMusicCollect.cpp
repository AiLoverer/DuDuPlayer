#include "CModelOnlineMusicCollect.h"

namespace QTDUDU {

    class CModelOnlineMusicCollectPrivate
    {
    public:
        CModelOnlineMusicCollectPrivate(CModelOnlineMusicCollect* model):
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

        CModelOnlineMusicCollect*                       m_model;
        QHash<int, QByteArray>                          m_roleNames;
        QVector<HData_OnlineMusicTopnameMusicData>      m_datas;
    };

    CModelOnlineMusicCollect::CModelOnlineMusicCollect(QObject *parent) :
        QAbstractListModel(parent),
        m_dPtr(new CModelOnlineMusicCollectPrivate(this))
    {
        qRegisterMetaType<QVector<HData_OnlineMusicTopnameMusicData>>("QVector<HData_OnlineMusicTopnameMusicData>");

        connect(CAppOnlineMusic::getInstance(), SIGNAL(sigForUpdateOnlineMusicCollectData(QVector<HData_OnlineMusicTopnameMusicData>)),
        this, SLOT(slotForOnlineMusicCollect(QVector<HData_OnlineMusicTopnameMusicData>)));
    }

    CModelOnlineMusicCollect::~CModelOnlineMusicCollect()
    {
        if (NULL != m_dPtr) {
            delete m_dPtr;
            m_dPtr = NULL;
        }
    }

    int CModelOnlineMusicCollect::rowCount(const QModelIndex &parent) const
    {
        Q_UNUSED(parent)
        return m_dPtr->m_datas.size();
    }

    QVariant CModelOnlineMusicCollect::data(const QModelIndex &index, int role) const
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

    QHash<int, QByteArray> CModelOnlineMusicCollect::roleNames() const
    {
        return m_dPtr->m_roleNames;
    }

    void CModelOnlineMusicCollect::slotForOnlineMusicCollect(const QVector<HData_OnlineMusicTopnameMusicData> &data)
    {
        beginResetModel();
        m_dPtr->m_datas = data;
        endResetModel();

        //qDebug()<<"slotForOnlineMusicCollect data size is : "<< data.size() ;
    }
}

