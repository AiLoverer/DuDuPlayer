TEMPLATE = app

QT += qml quick
QT += core
QT += sql
QT += multimedia
QT += widgets
QT += 3drender

CONFIG += c++11


SOURCES += main.cpp \
    code/playlist/TreeItem.cpp \
    code/playlist/TreeModel.cpp \
    code/framework/metadata.cpp \
    code/logic/clogic.cpp \
    code/app/localmusic/localmusic.cpp \
    code/app/localmusic/localmusicmodel.cpp \
    code/app/onlinemusic/CAppOnlineMusic.cpp \
    code/app/onlinemusic/CModelOnlineMusicCollect.cpp \
    code/app/onlinemusic/CModelOnlineMusicEmotion.cpp \
    code/app/onlinemusic/CModelOnlineMusicHistory.cpp \
    code/app/onlinemusic/CModelOnlineMusicLanguage.cpp \
    code/app/onlinemusic/CModelOnlineMusicSearched.cpp \
    code/app/onlinemusic/CModelOnlineMusicSence.cpp \
    code/app/onlinemusic/CModelOnlineMusicStyle.cpp \
    code/app/onlinemusic/CModelOnlineMusicTopName.cpp \
    code/app/onlinemusic/CModelOnlineMusicType.cpp \
    code/app/onlinemusic/CModelOnlineMusicYears.cpp \
    code/app/onlinemusic/cnetworkmanager.cpp \
    code/app/onlinemusic/cnetworkonlineserver.cpp \
    code/framework/CAppDataBase.cpp \
    code/framework/jsoncpp/CJSONUtils.cpp \
    code/framework/jsoncpp/src/json_reader.cpp \
    code/framework/jsoncpp/src/json_value.cpp \
    code/framework/jsoncpp/src/json_writer.cpp \
    code/app/video/dudumediaplayer.cpp

RESOURCES += qml.qrc

win32 {
    TARGET_PLATFORM = win32
    DEFINES += OS_WIN
}
qnx {
}
# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    code/playlist/TreeItem.h \
    code/playlist/TreeModel.h \
    code/framework/metadata.h \
    code/framework/dudu.h \
    code/framework/qtdudu.h \
    code/framework/TypeDefine.h \
    code/logic/clogic.h \
    code/framework/commondata.h \
    code/app/localmusic/localmusic.h \
    code/app/localmusic/localmusicmodel.h \
    code/app/onlinemusic/CAppOnlineMusic.h \
    code/app/onlinemusic/CModelOnlineMusicCollect.h \
    code/app/onlinemusic/CModelOnlineMusicEmotion.h \
    code/app/onlinemusic/CModelOnlineMusicHistory.h \
    code/app/onlinemusic/CModelOnlineMusicLanguage.h \
    code/app/onlinemusic/CModelOnlineMusicSearched.h \
    code/app/onlinemusic/CModelOnlineMusicSence.h \
    code/app/onlinemusic/CModelOnlineMusicStyle.h \
    code/app/onlinemusic/CModelOnlineMusicTopName.h \
    code/app/onlinemusic/CModelOnlineMusicType.h \
    code/app/onlinemusic/CModelOnlineMusicYears.h \
    code/app/onlinemusic/cnetworkmanager.h \
    code/app/onlinemusic/cnetworkonlineserver.h \
    code/framework/CAppDataBase.h \
    code/app/onlinemusic/JConNetRspData.h \
    code/framework/JsonLite.h \
    code/framework/jsoncpp/CJSONUtils.h \
    code/framework/jsoncpp/src/json_batchallocator.h \
    code/framework/jsoncpp/src/json_tool.h \
    code/framework/jsoncpp/json/assertions.h \
    code/framework/jsoncpp/json/autolink.h \
    code/framework/jsoncpp/json/config.h \
    code/framework/jsoncpp/json/features.h \
    code/framework/jsoncpp/json/forwards.h \
    code/framework/jsoncpp/json/json.h \
    code/framework/jsoncpp/json/reader.h \
    code/framework/jsoncpp/json/value.h \
    code/framework/jsoncpp/json/version.h \
    code/framework/jsoncpp/json/writer.h \
    code/app/video/dudumediaplayer.h
