#include "controls_plugin.h"
#include "fusswindow.h"

#include <qqml.h>

void ControlsPlugin::registerTypes(const char *uri)
{
    // @uri XA.Controls
    qmlRegisterType<FussWindow>(uri, 1, 0, "FussWindow");    
}
