#ifndef LOCALMUSICMODEL_H
#define LOCALMUSICMODEL_H
#include <QAbstractListModel>
#include "../../framework/dudu.h"
namespace QTDUDU {

    class LocalMusicModelPrivate;
    class LocalMusicModel : public QAbstractListModel
    {
        Q_OBJECT
    public:
        LocalMusicModel(QObject *parent = 0);
        ~LocalMusicModel();

        int rowCount(const QModelIndex& parent) const;

        QVariant data(const QModelIndex& index, int role) const;

        QHash<int, QByteArray> roleNames() const;
    private:
        LocalMusicModelPrivate* m_dPtr;

    public slots:
        void slotForLocalMusic(const QVector<MusicInfo>& data);
    };
}
#endif // LOCALMUSICMODEL_H
