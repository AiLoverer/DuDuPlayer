#ifndef CMODELONLINEMUSICHISTORY_H
#define CMODELONLINEMUSICHISTORY_H

#include <QAbstractListModel>
#include "../../framework/dudu.h"

namespace QTDUDU {

    class CModelOnlineMusicHistoryPrivate;
    class CModelOnlineMusicHistory : public QAbstractListModel
    {
        Q_OBJECT
    public:
        CModelOnlineMusicHistory(QObject *parent = 0);
        ~CModelOnlineMusicHistory();

        int rowCount(const QModelIndex& parent) const;

        QVariant data(const QModelIndex& index, int role) const;

        QHash<int, QByteArray> roleNames() const;

    private:
        CModelOnlineMusicHistoryPrivate* m_dPtr;
    signals:

    public slots:
        void slotForOnlineMusicHistory(const QVector<HData_OnlineMusicTopnameMusicData>& data);

    };
}


#endif // CMODELONLINEMUSICHISTORY_H
