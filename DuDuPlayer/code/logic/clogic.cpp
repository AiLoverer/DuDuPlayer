#include "clogic.h"
#include "../framework/dudu.h"
namespace QTDUDU {
    Clogic::Clogic()
    {

    }

    void Clogic::registerAll()
    {
        LocalMusic::getInstance();
        DuDuMediaPlayer::getInstance();
    }

    void Clogic::unregisterAll()
    {

    }
}

