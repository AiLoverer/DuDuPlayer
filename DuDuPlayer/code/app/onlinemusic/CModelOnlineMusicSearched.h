#ifndef CMODELONLINEMUSICSEARCHED_H
#define CMODELONLINEMUSICSEARCHED_H

#include <QAbstractListModel>
#include "../../framework/dudu.h"

namespace QTDUDU {

    class CModelOnlineMusicSearchedPrivate;
    class CModelOnlineMusicSearched : public QAbstractListModel
    {
        Q_OBJECT
    public:
        CModelOnlineMusicSearched(QObject *parent = 0);
        ~CModelOnlineMusicSearched();

        int rowCount(const QModelIndex& parent) const;

        QVariant data(const QModelIndex& index, int role) const;

        QHash<int, QByteArray> roleNames() const;

    private:
        CModelOnlineMusicSearchedPrivate* m_dPtr;
    signals:

    public slots:
        void slotForOnlineMusicSearched(const QVector<HData_OnlineMusicTopnameMusicData>& data);

    };
}


#endif // CMODELONLINEMUSICSEARCHED_H
