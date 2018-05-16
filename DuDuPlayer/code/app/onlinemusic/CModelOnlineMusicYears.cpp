#include "CModelOnlineMusicYears.h"

namespace QTDUDU {

    class CModelOnlineMusicYearsPrivate
    {
    public:
        CModelOnlineMusicYearsPrivate(CModelOnlineMusicYears* model):
            m_model(model)
        {
            m_roleNames.insert(Role_Type, "type");
            m_roleNames.insert(Role_Url, "picUrl");
        }

        enum {
            Role_Type = Qt::UserRole + 1,
            Role_Url,
        };

        CModelOnlineMusicYears*              m_model;
        QHash<int, QByteArray>               m_roleNames;
        QVector<HData_OnlineMusicType>       m_datas;
    };


    CModelOnlineMusicYears::CModelOnlineMusicYears(QObject *parent) :
        QAbstractListModel(parent),
        m_dPtr(new CModelOnlineMusicYearsPrivate(this))
    {
        qRegisterMetaType<QVector<HData_OnlineMusicType>>("QVector<HData_OnlineMusicType>");

        connect(CAppOnlineMusic::getInstance(), SIGNAL(sigForUpdateOnlineMusicYearsData(QVector<HData_OnlineMusicType>)),
        this, SLOT(slotForOnlineMusicYears(QVector<HData_OnlineMusicType>)));
    }

    CModelOnlineMusicYears::~CModelOnlineMusicYears()
    {
        if (NULL != m_dPtr) {
            delete m_dPtr;
            m_dPtr = NULL;
        }
    }

    int CModelOnlineMusicYears::rowCount(const QModelIndex &parent) const
    {
        Q_UNUSED(parent)
        return m_dPtr->m_datas.size();
    }

    QVariant CModelOnlineMusicYears::data(const QModelIndex &index, int role) const
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

    QHash<int, QByteArray> CModelOnlineMusicYears::roleNames() const
    {
        return m_dPtr->m_roleNames;
    }

    void CModelOnlineMusicYears::slotForOnlineMusicYears(const QVector<HData_OnlineMusicType> &data)
    {
        beginResetModel();
        m_dPtr->m_datas = data;
        endResetModel();

        //qDebug()<<"slot For OnlineMusic Years data size is : "<< data.size() ;
    }
}

