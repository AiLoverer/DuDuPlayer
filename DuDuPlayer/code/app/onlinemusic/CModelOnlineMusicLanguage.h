#ifndef CMODELONLINEMUSICLANGUAGE_H
#define CMODELONLINEMUSICLANGUAGE_H

#include <QAbstractListModel>
#include "../../framework/dudu.h"

namespace QTDUDU {

    class CModelOnlineMusicLanguagePrivate;
    class CModelOnlineMusicLanguage : public QAbstractListModel
    {
        Q_OBJECT
    public:
        CModelOnlineMusicLanguage(QObject *parent = 0);
        ~CModelOnlineMusicLanguage();

        int rowCount(const QModelIndex& parent) const;

        QVariant data(const QModelIndex& index, int role) const;

        QHash<int, QByteArray> roleNames() const;

    private:
        CModelOnlineMusicLanguagePrivate* m_dPtr;
    signals:

    public slots:
        void slotForOnlineMusicLanguage(const QVector<HData_OnlineMusicType>& data);

    };
}


#endif // CMODELONLINEMUSICLANGUAGE_H
