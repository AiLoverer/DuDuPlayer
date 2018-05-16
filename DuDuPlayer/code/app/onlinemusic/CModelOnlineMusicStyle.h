#ifndef CMODELONLINEMUSICSTYLE_H
#define CMODELONLINEMUSICSTYLE_H

#include <QAbstractListModel>
#include "../../framework/dudu.h"

namespace QTDUDU {

    class CModelOnlineMusicStylePrivate;
    class CModelOnlineMusicStyle : public QAbstractListModel
    {
        Q_OBJECT
    public:
        CModelOnlineMusicStyle(QObject *parent = 0);
        ~CModelOnlineMusicStyle();

        int rowCount(const QModelIndex& parent) const;

        QVariant data(const QModelIndex& index, int role) const;

        QHash<int, QByteArray> roleNames() const;

    private:
        CModelOnlineMusicStylePrivate* m_dPtr;
    signals:

    public slots:
        void slotForOnlineMusicStyle(const QVector<HData_OnlineMusicType>& data);

    };
}


#endif // CMODELONLINEMUSICSTYLE_H
