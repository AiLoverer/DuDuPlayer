#include "metadata.h"
#include "./dudu.h"

using namespace QTDUDU;

void registerQmlProperty(std::map<const char*, std::shared_ptr<QObject> >& properties, QQmlContext* contex, const char* name, QObject* object) {
	properties[name] = std::shared_ptr<QObject>(object);
	contex->setContextProperty(name, object);
}

void registerQmlClasses(QQmlContext* context) {
    //qmlRegisterType<DuDuMediaPlayer>("DuDuMediaPlayer", 1, 0, "DuDuMediaPlayer");
}

void registerCpp2Property(std::map<const char*, std::shared_ptr<QObject> >& properties, QQmlContext* ctx) {
	// 如果包含了vld头文件进行内存泄漏检测，或者是编译QNX版本则用上面的代码
	// 否则用下面的代码，这样可以在qt creator里面使用提示功能

    //registerQmlProperty(properties, ctx, "lstModelMusic", CListModelMusic::getInstance());

    registerQmlProperty(properties, ctx, "lstModelMusic",  new TreeModel());
    registerQmlProperty(properties, ctx, "localMusicModel", new LocalMusicModel());
    registerQmlProperty(properties, ctx, "CppLocalMusic", LocalMusic::getInstance());

    registerQmlProperty(properties, ctx, "JCNet_AppOnlineMusic", CAppOnlineMusic::getInstance());
    registerQmlProperty(properties, ctx, "modelOnlineMusicTypeHot", new CModelOnlineMusicType());
    registerQmlProperty(properties, ctx, "modelOnlineMusicTypeSence", new CModelOnlineMusicSence());
    registerQmlProperty(properties, ctx, "modelOnlineMusicTypeEmotion", new CModelOnlineMusicEmotion());
    registerQmlProperty(properties, ctx, "modelOnlineMusicTypeStyle", new CModelOnlineMusicStyle());
    registerQmlProperty(properties, ctx, "modelOnlineMusicTypeYears", new CModelOnlineMusicYears());
    registerQmlProperty(properties, ctx, "modelOnlineMusicTypeLanguage", new CModelOnlineMusicLanguage());
    registerQmlProperty(properties, ctx, "modelOnlineMusicTypeTopName", new CModelOnlineMusicTopName());
    registerQmlProperty(properties, ctx, "modelOnlineMusicTypeSearched", new CModelOnlineMusicSearched());
    registerQmlProperty(properties, ctx, "modelOnlineMusicHistory", new CModelOnlineMusicHistory());
    registerQmlProperty(properties, ctx, "modelOnlineMusicCollect", new CModelOnlineMusicCollect());
    registerQmlProperty(properties, ctx, "duduMediaPlayer", DuDuMediaPlayer::getInstance());

	if (0) {
        //ctx->setContextProperty("modelOnlineMusicTypeLanguage", new CModelOnlineMusicLanguage());

	}

    //ChinaCityList::getInstance()->init();
}

void regiserMetaData(std::map<const char*, std::shared_ptr<QObject> >& properties, QQmlContext* context) {
	registerQmlClasses(context);
	registerCpp2Property(properties, context);
}
