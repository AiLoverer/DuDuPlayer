#include "CModelOnlineMusicSearched.h"

namespace QTDUDU {

    class CModelOnlineMusicSearchedPrivate
    {
    public:
        CModelOnlineMusicSearchedPrivate(CModelOnlineMusicSearched* model):
            m_model(model)
        {
            m_roleNames.insert(Role_SongName, "songname");
            m_roleNames.insert(Role_SingerName, "singername");
            m_roleNames.insert(Role_SingerPicUrl, "singerpicurl");
            m_roleNames.insert(Role_Score, "score");
            m_roleNames.insert(Role_TopNo, "topno");

        }

        enum {
            Role_SongName = Qt::UserRole + 1,
            Role_SingerName,
            Role_SingerPicUrl,
            Role_Score,
            Role_TopNo,
        };

        CModelOnlineMusicSearched*                      m_model;
        QHash<int, QByteArray>                          m_roleNames;
        QVector<HData_OnlineMusicTopnameMusicData>      m_datas;
    };

    CModelOnlineMusicSearched::CModelOnlineMusicSearched(QObject *parent) :
        QAbstractListModel(parent),
        m_dPtr(new CModelOnlineMusicSearchedPrivate(this))
    {
        qRegisterMetaType<QVector<HData_OnlineMusicTopnameMusicData>>("QVector<HData_OnlineMusicTopnameMusicData>");

        connect(CAppOnlineMusic::getInstance(), SIGNAL(sigForUpdateOnlineMusicSearchedMusicData(QVector<HData_OnlineMusicTopnameMusicData>)),
        this, SLOT(slotForOnlineMusicSearched(QVector<HData_OnlineMusicTopnameMusicData>)));
    }

    CModelOnlineMusicSearched::~CModelOnlineMusicSearched()
    {
        if (NULL != m_dPtr) {
            delete m_dPtr;
            m_dPtr = NULL;
        }
    }

    int CModelOnlineMusicSearched::rowCount(const QModelIndex &parent) const
    {
        Q_UNUSED(parent)
        return m_dPtr->m_datas.size();
    }

    QVariant CModelOnlineMusicSearched::data(const QModelIndex &index, int role) const
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

        return QVariant();

    }

    QHash<int, QByteArray> CModelOnlineMusicSearched::roleNames() const
    {
        return m_dPtr->m_roleNames;
    }

    void CModelOnlineMusicSearched::slotForOnlineMusicSearched(const QVector<HData_OnlineMusicTopnameMusicData> &data)
    {
        beginResetModel();
        m_dPtr->m_datas = data;
        endResetModel();

        //qDebug()<<"slot For OnlineMusic Searched data size is : "<< data.size() ;
    }
}

