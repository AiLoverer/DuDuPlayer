#include "dudumediaplayer.h"
namespace QTDUDU {

    DuDuMediaPlayer* DuDuMediaPlayer::m_pInstance = nullptr;

    void DuDuMediaPlayer::play()
    {
        qDebug()<<"play :..";
        QMediaPlayer ::setMedia(QUrl::fromLocalFile(QStringLiteral("D:/KuGou/MV/mv.mp4")));
        QMediaPlayer ::play();

    }

    void DuDuMediaPlayer::pause()
    {
        qDebug()<<"pause";
        QMediaPlayer ::pause();
    }

    void DuDuMediaPlayer::setPosition(int position)
    {
        QMediaPlayer::setPosition(position);
    }

    DuDuMediaPlayer::DuDuMediaPlayer(QObject *parent, Flags flags) : QMediaPlayer(parent, flags)
    {
        //connect(this, SIGNAL(videoAvailableChanged(bool)), this, SLOT(VideoAvailableChanged(bool)));
        connect(this, SIGNAL(metaDataAvailableChanged(bool)), this, SLOT(slotMetaDataAvailableChanged(bool)));
        connect(this, SIGNAL(positionChanged(qint64)), this, SLOT(slotForPositionChanged(qint64)));
        connect(this, SIGNAL(durationChanged(qint64)), this, SLOT(slotForDurationChanged(qint64)));
        connect(this, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(slotForState(QMediaPlayer::State)));
    }

    DuDuMediaPlayer *DuDuMediaPlayer::getInstance()
    {
        if(m_pInstance == nullptr)
        {
            m_pInstance = new DuDuMediaPlayer(0, 0);
        }
        return m_pInstance;
    }

    DuDuMediaPlayer::DuDuMediaPlayer()
    {

    }

    DuDuMediaPlayer::~DuDuMediaPlayer()
    {

    }

    void DuDuMediaPlayer::VideoAvailableChanged(bool bavaliable)
    {
        qDebug()<<"bavaliable :"<<bavaliable;
    }

    void DuDuMediaPlayer::setVideoSurface(QAbstractVideoSurface* surface)
    {
        m_surface = surface;
        setVideoOutput(m_surface);
    }

    QAbstractVideoSurface* DuDuMediaPlayer::getVideoSurface()
    {
        return m_surface;
    }

    void DuDuMediaPlayer::slotForPositionChanged(qint64 position)
    {
        //qDebug()<<"C++  position:"<<position;
        emit sigPositionChanged(position);
    }

    void DuDuMediaPlayer::slotForDurationChanged(qint64 duration)
    {
        //qDebug()<<"C++  duration:"<<duration;
        emit sigDurationChanged(duration);
    }

    void DuDuMediaPlayer::slotMetaDataAvailableChanged(bool available)
    {
        /*
        // 数据显示
        qDebug() << "OnMetaDataAvailableChanged";
        if(available){
            foreach(QString str,availableMetaData()){
                qDebug()<<str<<"   :"<<metaData(str).toString().toUtf8().data();
            }
            //playlist->setCurrentIndex(++count);
        }
        */
    }

    void DuDuMediaPlayer::slotForState(QMediaPlayer::State state)
    {
        emit sigState(static_cast<int>(state));
    }
}

