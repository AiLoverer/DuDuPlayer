#include "CModelOnlineMusicSence.h"

namespace QTDUDU {

    class CModelOnlineMusicSencePrivate
    {
    public:
        CModelOnlineMusicSencePrivate(CModelOnlineMusicSence* model):
            m_model(model)
        {
            m_roleNames.insert(Role_Type, "type");
            m_roleNames.insert(Role_Url, "picUrl");
        }

        enum {
            Role_Type = Qt::UserRole + 1,
            Role_Url,
        };

        CModelOnlineMusicSence*              m_model;
        QHash<int, QByteArray>               m_roleNames;
        QVector<HData_OnlineMusicType>      m_datas;
    };


    CModelOnlineMusicSence::CModelOnlineMusicSence(QObject *parent) :
        QAbstractListModel(parent),
        m_dPtr(new CModelOnlineMusicSencePrivate(this))
    {
        qRegisterMetaType<QVector<HData_OnlineMusicType>>("QVector<HData_OnlineMusicType>");

        connect(CAppOnlineMusic::getInstance(), SIGNAL(sigForUpdateOnlineMusicSenceData(QVector<HData_OnlineMusicType>)),
        this, SLOT(slotForOnlineMusicSence(QVector<HData_OnlineMusicType>)));
    }

    CModelOnlineMusicSence::~CModelOnlineMusicSence()
    {
        if (NULL != m_dPtr) {
            delete m_dPtr;
            m_dPtr = NULL;
        }
    }

    int CModelOnlineMusicSence::rowCount(const QModelIndex &parent) const
    {
        Q_UNUSED(parent)
        return m_dPtr->m_datas.size();
    }

    QVariant CModelOnlineMusicSence::data(const QModelIndex &index, int role) const
    {
        if (index.row() < 0 || index.row() >= m_dPtr->m_datas.count())
        {
            return QVariant();
        }

        if (role == m_dPtr->Role_Type) {
            return m_dPtr->m_datas.at(index.row()).strType;
        }
        else if (role == m_dPtr->Role_Url) {
            return m_dPtr->m_datas.at(index.row()).strPicUrl;
        }

        return QVariant();

    }

    QHash<int, QByteArray> CModelOnlineMusicSence::roleNames() const
    {
        return m_dPtr->m_roleNames;
    }

    void CModelOnlineMusicSence::slotForOnlineMusicSence(const QVector<HData_OnlineMusicType> &data)
    {
        beginResetModel();
        m_dPtr->m_datas = data;
        endResetModel();

        //qDebug()<<"slot For OnlineMusic Sence data size is : "<< data.size() ;
    }
}

