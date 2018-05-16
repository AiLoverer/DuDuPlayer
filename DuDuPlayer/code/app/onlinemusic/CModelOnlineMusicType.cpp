#include "CModelOnlineMusicType.h"

namespace QTDUDU {


    class CModelOnlineMusicTypePrivate
    {
    public:
        CModelOnlineMusicTypePrivate(CModelOnlineMusicType* model):
            m_model(model)
        {
            m_roleNames.insert(Role_Type, "type");
            m_roleNames.insert(Role_Name, "name");
            m_roleNames.insert(Role_Url, "url");
        }

        enum {
            Role_Type = Qt::UserRole + 1,
            Role_Name,
            Role_Url,
        };

        CModelOnlineMusicType*              m_model;
        QHash<int, QByteArray>              m_roleNames;
        QVector<HData_OnlineMusicType>      m_datas;
    };

    CModelOnlineMusicType::CModelOnlineMusicType(QObject *parent) :
        QAbstractListModel(parent),
        m_dPtr(new CModelOnlineMusicTypePrivate(this))
    {
        qRegisterMetaType<QVector<HData_OnlineMusicType>>("QVector<HData_OnlineMusicType>");

        connect(CAppOnlineMusic::getInstance(), SIGNAL(sigForUpdateOnlineMusicTopTypeData(QVector<HData_OnlineMusicType>)),
        this, SLOT(slotForOnlineMusicType(QVector<HData_OnlineMusicType>)));
    }

    CModelOnlineMusicType::~CModelOnlineMusicType()
    {
        if (NULL != m_dPtr) {
            delete m_dPtr;
            m_dPtr = NULL;
        }
    }

    int CModelOnlineMusicType::rowCount(const QModelIndex &parent) const
    {
        Q_UNUSED(parent)
        return m_dPtr->m_datas.size();
    }

    QVariant CModelOnlineMusicType::data(const QModelIndex &index, int role) const
    {
        if (index.row() < 0 || index.row() >= m_dPtr->m_datas.count())
        {
            return QVariant();
        }

        if (role == m_dPtr->Role_Type) {
            return m_dPtr->m_datas.at(index.row()).strType;
        }
        else if (role == m_dPtr->Role_Name) {
            return m_dPtr->m_datas.at(index.row()).strName;
        }
        else if (role == m_dPtr->Role_Url) {
            return m_dPtr->m_datas.at(index.row()).strPicUrl;
        }

        return QVariant();
    }

    QHash<int, QByteArray> CModelOnlineMusicType::roleNames() const
    {
        return m_dPtr->m_roleNames;
    }

    void CModelOnlineMusicType::slotForOnlineMusicType(const QVector<HData_OnlineMusicType> &data)
    {
        //qDebug()<<"in slotForOnlineMusicType";
        beginResetModel();
        m_dPtr->m_datas = data;
        endResetModel();
        //qDebug()<<"slot For OnlineMusic Type data size is : "<< data.size() ;
    }
}

