#ifndef DUDUMEDIAPLAYER_H
#define DUDUMEDIAPLAYER_H

#include <QObject>
#include "../../framework/dudu.h"

namespace QTDUDU {

    class DuDuMediaPlayer : public QMediaPlayer
    {
        Q_OBJECT
    public:
        Q_PROPERTY(QAbstractVideoSurface* videoSurface READ getVideoSurface WRITE setVideoSurface )
        Q_INVOKABLE void play();
        Q_INVOKABLE void pause();
        Q_INVOKABLE void setPosition(int position);
    public:
        explicit DuDuMediaPlayer(QObject *parent = 0, Flags flags = 0);
        static DuDuMediaPlayer *getInstance();

    private:
        DuDuMediaPlayer();
        ~DuDuMediaPlayer();
    private:
        QAbstractVideoSurface* m_surface;
        static DuDuMediaPlayer* m_pInstance;
        void VideoAvailableChanged(bool bavaliable);
    signals:
        void sigPositionChanged(int position);
        void sigDurationChanged(int duration);
        void sigState(int state);
    public slots:
        void setVideoSurface(QAbstractVideoSurface* surface);
        QAbstractVideoSurface* getVideoSurface();
        void slotForPositionChanged(qint64 position);
        void slotForDurationChanged(qint64 duration);
        void slotMetaDataAvailableChanged(bool available);
        void slotForState(QMediaPlayer::State state);


    };

}


#endif // DUDUMEDIAPLAYER_H
