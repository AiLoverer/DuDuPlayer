#ifndef CMODELONLINEMUSICYEARS_H
#define CMODELONLINEMUSICYEARS_H

#include <QAbstractListModel>
#include "../../framework/dudu.h"

namespace QTDUDU {

    class CModelOnlineMusicYearsPrivate;
    class CModelOnlineMusicYears : public QAbstractListModel
    {
        Q_OBJECT
    public:
        CModelOnlineMusicYears(QObject *parent = 0);
        ~CModelOnlineMusicYears();

        int rowCount(const QModelIndex& parent) const;

        QVariant data(const QModelIndex& index, int role) const;

        QHash<int, QByteArray> roleNames() const;

    private:
        CModelOnlineMusicYearsPrivate* m_dPtr;
    signals:

    public slots:
        void slotForOnlineMusicYears(const QVector<HData_OnlineMusicType>& data);

    };
}


#endif // CMODELONLINEMUSICYEARS_H
