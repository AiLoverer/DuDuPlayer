#ifndef CMODELONLINEMUSICCOLLECT_H
#define CMODELONLINEMUSICCOLLECT_H

#include <QAbstractListModel>
#include "../../framework/dudu.h"

namespace QTDUDU {

    class CModelOnlineMusicCollectPrivate;
    class CModelOnlineMusicCollect : public QAbstractListModel
    {
        Q_OBJECT
    public:
        CModelOnlineMusicCollect(QObject *parent = 0);
        ~CModelOnlineMusicCollect();

        int rowCount(const QModelIndex& parent) const;

        QVariant data(const QModelIndex& index, int role) const;

        QHash<int, QByteArray> roleNames() const;

    private:
        CModelOnlineMusicCollectPrivate* m_dPtr;
    signals:

    public slots:
        void slotForOnlineMusicCollect(const QVector<HData_OnlineMusicTopnameMusicData>& data);

    };
}


#endif // CMODELONLINEMUSICCOLLECT_H
