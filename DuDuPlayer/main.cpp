#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QColor>
#include <QQmlContext>
#include "./code/framework/metadata.h"
#include "./code/framework/dudu.h"

using namespace QTDUDU;

//QQmlApplicationEngine* g_pEngine = NULL;

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // 注册Logic
    Clogic::registerAll();

    QQmlApplicationEngine engine ;
    //g_pEngine = &engine;
    std::map<const char*, std::shared_ptr<QObject> > properties;
    regiserMetaData(properties, engine.rootContext());
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));



    /*
    // 无边框 背景透明
    QQuickView view;
    view.setFlags(Qt::FramelessWindowHint);
    view.setColor(QColor(Qt::transparent));

    std::map<const char*, std::shared_ptr<QObject> > properties;
    regiserMetaData(properties, view.rootContext());

    view.setSource(QUrl(QStringLiteral("qrc:/main.qml")));
    view.show();
    // 将view设置成main.qml属性
    view.rootContext()->setContextProperty("mainwindow", &view);

    // 查找MediaPlayer
    QObject* player = view.findChild<QObject*>("audioPlayer");
    if(player)
    {

    }
    */


    return app.exec();
}
