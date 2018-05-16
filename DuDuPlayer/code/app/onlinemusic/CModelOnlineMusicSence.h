#ifndef CMODELONLINEMUSICSENCE_H
#define CMODELONLINEMUSICSENCE_H

#include <QAbstractListModel>
#include "../../framework/dudu.h"

namespace QTDUDU {

    class CModelOnlineMusicSencePrivate;
    class CModelOnlineMusicSence : public QAbstractListModel
    {
        Q_OBJECT
    public:
        CModelOnlineMusicSence(QObject *parent = 0);
        ~CModelOnlineMusicSence();

        int rowCount(const QModelIndex& parent) const;

        QVariant data(const QModelIndex& index, int role) const;

        QHash<int, QByteArray> roleNames() const;

    private:
        CModelOnlineMusicSencePrivate* m_dPtr;
    signals:

    public slots:
        void slotForOnlineMusicSence(const QVector<HData_OnlineMusicType>& data);

    };
}


#endif // CMODELONLINEMUSICSENCE_H
