#ifndef CMODELONLINEMUSICEMOTION_H
#define CMODELONLINEMUSICEMOTION_H

#include <QAbstractListModel>
#include "../../framework/dudu.h"

namespace QTDUDU {

    class CModelOnlineMusicEmotionPrivate;
    class CModelOnlineMusicEmotion : public QAbstractListModel
    {
        Q_OBJECT
    public:
        CModelOnlineMusicEmotion(QObject *parent = 0);
        ~CModelOnlineMusicEmotion();

        int rowCount(const QModelIndex& parent) const;

        QVariant data(const QModelIndex& index, int role) const;

        QHash<int, QByteArray> roleNames() const;

    private:
        CModelOnlineMusicEmotionPrivate* m_dPtr;
    signals:

    public slots:
        void slotForOnlineMusicEmotion(const QVector<HData_OnlineMusicType>& data);

    };
}


#endif // CMODELONLINEMUSICEMOTION_H
