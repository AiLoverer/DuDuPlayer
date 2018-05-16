#include "localmusicmodel.h"
#include "../../framework/dudu.h"
namespace QTDUDU {
    class LocalMusicModelPrivate
    {
    public:
        LocalMusicModelPrivate(LocalMusicModel* model):
            m_model(model)
        {
            m_roleNames.insert(Role_SongName, "songname");
            m_roleNames.insert(Role_HasDownload, "hasDownload");
            m_roleNames.insert(Role_HasMV, "hasMV");
            m_roleNames.insert(Role_HasCollected, "hasCollected");

        }

        enum {
            Role_SongName = Qt::UserRole + 1,
            Role_HasDownload,
            Role_HasMV,
            Role_HasCollected
        };

        LocalMusicModel*                m_model;
        QHash<int, QByteArray>          m_roleNames;
        QVector<MusicInfo>              m_datas;
    };

    LocalMusicModel::LocalMusicModel(QObject *parent) :
        QAbstractListModel(parent),
        m_dPtr(new LocalMusicModelPrivate(this))
    {
        qRegisterMetaType<QVector<MusicInfo>>("QVector<MusicInfo>");

        connect(LocalMusic::getInstance(), SIGNAL(sigForUpdateLocalMusicData(QVector<MusicInfo>)),
        this, SLOT(slotForLocalMusic(QVector<MusicInfo>)));
    }

    LocalMusicModel::~LocalMusicModel()
    {
        if (NULL != m_dPtr) {
            delete m_dPtr;
            m_dPtr = NULL;
        }
    }

    int LocalMusicModel::rowCount(const QModelIndex &parent) const
    {
        Q_UNUSED(parent)
        return m_dPtr->m_datas.size();
    }

    QVariant LocalMusicModel::data(const QModelIndex &index, int role) const
    {
        if (index.row() < 0 || index.row() >= m_dPtr->m_datas.count())
        {
            return QVariant();
        }

        if (role == m_dPtr->Role_SongName) {
            return m_dPtr->m_datas.at(index.row()).strSongName;
        }
        return QVariant();

    }

    QHash<int, QByteArray> LocalMusicModel::roleNames() const
    {
        return m_dPtr->m_roleNames;
    }

    void LocalMusicModel::slotForLocalMusic(const QVector<MusicInfo> &data)
    {
        beginResetModel();
        m_dPtr->m_datas = data;
        endResetModel();

        qDebug()<<"slotForLocalMusic data size is : "<< data.size() ;
    }

}

