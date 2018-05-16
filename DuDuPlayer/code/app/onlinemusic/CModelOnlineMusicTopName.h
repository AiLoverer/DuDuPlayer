#ifndef CMODELONLINEMUSICTOPNAME_H
#define CMODELONLINEMUSICTOPNAME_H

#include <QAbstractListModel>
#include "../../framework/dudu.h"

namespace QTDUDU {

    class CModelOnlineMusicTopNamePrivate;
    class CModelOnlineMusicTopName : public QAbstractListModel
    {
        Q_OBJECT
    public:
        CModelOnlineMusicTopName(QObject *parent = 0);
        ~CModelOnlineMusicTopName();

        int rowCount(const QModelIndex& parent) const;

        QVariant data(const QModelIndex& index, int role) const;

        QHash<int, QByteArray> roleNames() const;

    private:
        CModelOnlineMusicTopNamePrivate* m_dPtr;
    signals:

    public slots:
        void slotForOnlineMusicTopName(const QVector<HData_OnlineMusicTopnameMusicData>& data);

    };
}


#endif // CMODELONLINEMUSICTOPNAME_H
