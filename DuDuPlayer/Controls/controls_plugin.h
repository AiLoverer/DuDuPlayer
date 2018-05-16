#ifndef CONTROLS_PLUGIN_H
#define CONTROLS_PLUGIN_H

#include <QQmlExtensionPlugin>

class ControlsPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

public:
    void registerTypes(const char *uri);
};

#endif // CONTROLS_PLUGIN_H

