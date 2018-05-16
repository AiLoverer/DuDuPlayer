#ifndef CMODELONLINEMUSICTYPE_H
#define CMODELONLINEMUSICTYPE_H
#include <QAbstractListModel>
#include "../../framework/dudu.h"

namespace QTDUDU {
    class CModelOnlineMusicTypePrivate;
    class CModelOnlineMusicType : public QAbstractListModel
    {
        Q_OBJECT
    public:
        CModelOnlineMusicType(QObject *parent = 0);
        ~CModelOnlineMusicType();

        int rowCount(const QModelIndex& parent) const;

        QVariant data(const QModelIndex& index, int role) const;

        QHash<int, QByteArray> roleNames() const;

    private:
        CModelOnlineMusicTypePrivate* m_dPtr;
    signals:

    public slots:
        void slotForOnlineMusicType(const QVector<HData_OnlineMusicType>& data);

    };

}


#endif // CMODELONLINEMUSICTYPE_H
