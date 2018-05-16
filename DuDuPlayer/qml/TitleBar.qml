import QtQuick 2.0
import "qrc:/qml/common/"   as Common
import "qrc:/qml/sub/" as Sub

/***
* 标题栏
*/
Rectangle {
    id: titleBar;
    width: 1000;
    height: 50;
    color: "transparent";
    property var mainFrame;

    property alias userName: userName.text;
    property alias picSource: picHead.parent;

   // 用户头像
   Common.PicButton {
        id: picHead;
        width: 34;
        height: 34;
        picRadius: width / 2;
        picSource: "qrc:/images/icon-titlebar-person-default.png";
        anchors.left: parent.left;
        anchors.leftMargin: 10;
        anchors.verticalCenter: parent.verticalCenter;
   }

   // 用户名
   Text {
       id: userName;
       text: qsTr("duduMusic");
       color: "white";
       font.pixelSize: 18;
       anchors.left:  picHead.right;
       anchors.leftMargin: 10;
       anchors.verticalCenter: parent.verticalCenter;
       width: 100;
       elide: Text.ElideRight;
   }

   // VIP 等级
   Rectangle {
       id: vipRect;
       color: Qt.rgba(0.81, 0.81, 0.81, 0.9);
       width: 50;
       height: 18;
       anchors.left: userName.right;
       anchors.leftMargin: 5;
       anchors.verticalCenter: parent.verticalCenter;
       Text {
           id: vipTip;
           text: qsTr("豪华VIP");
           color: "red";
           font.pixelSize: 12;
           anchors.verticalCenter: parent.verticalCenter;
           anchors.horizontalCenter: parent.horizontalCenter;
       }
   }

   // 返回按钮
   Common.PicButton {
        id: backBtn;
        anchors.left: parent.left;
        anchors.leftMargin: 310;
        anchors.verticalCenter: parent.verticalCenter;
        width: 32;
        height: 32;
        picSource: "qrc:/images/anchor-left.png";
   }

   // 刷新按钮
   Common.PicButton {
        id: refreshBtn;
        anchors.left: backBtn.right;
        anchors.leftMargin: 10;
        anchors.verticalCenter: parent.verticalCenter;
        width: 32;
        height: 32;
        picSource: "qrc:/images/refresh.png";
   }
   // 搜索区域
   Rectangle {
       id: searchRect;
        width: 260;
        height: 28;
        color: "transparent";
        anchors.left: refreshBtn.right;
        anchors.leftMargin: 10;
        anchors.verticalCenter: parent.verticalCenter;
        Rectangle {
            id: searchBkgnd;
            anchors.fill: parent;
            radius: 14;
            color: Qt.rgba(213/255, 217/255, 227/255, 1.0);

            Image {
                id: searchImg
                source: "qrc:/images/search.png"
                anchors.top: parent.top;
                anchors.bottom: parent.bottom;
                anchors.right: parent.right;
                anchors.rightMargin: 14;
                width: 19;
                height: 19;
            }
            TextInput {
                id: searchInput;
                anchors.left: parent.right;
                anchors.leftMargin: 14;
                anchors.top: parent.top;
                anchors.bottom: parent.bottom;
                anchors.right: searchImg.left;
                anchors.rightMargin: 1;
            }
        }
   }

   // 关闭按钮
   Common.PicButton {
       id: closeBtn;
       width: 16;
       height: 16;
       picSource: "qrc:/images/close.png";
       anchors.right: parent.right;
       anchors.rightMargin: 5;
       anchors.verticalCenter: parent.verticalCenter;
       onClicked: {
            Qt.quit();
       }
   }

   // 最小化按钮
   Common.PicButton {
       id: maximizeBtn;
       width: 16;
       height: 16;
       picSource: "qrc:/images/maximize.png";
       anchors.right: closeBtn.left;
       anchors.rightMargin: 10;
       anchors.verticalCenter: parent.verticalCenter;
   }

   // 设置按钮
   Common.PicButton {
       id: settingBtn;
       width: 16;
       height: 16;
       picSource: "qrc:/images/options.png";
       anchors.right: maximizeBtn.left;
       anchors.rightMargin: 10;
       anchors.verticalCenter: parent.verticalCenter;
   }

   // 皮肤按钮
   Common.PicButton {
       id: skinBtn;
       width: 16;
       height: 16;
       picSource: "qrc:/images/skin.png";
       anchors.right: settingBtn.left;
       anchors.rightMargin: 10;
       anchors.verticalCenter: parent.verticalCenter;
       onClicked: {
           //skin.source = "qrc:/qml/sub/PopupSkin.qml";
           Qt.createComponent("qrc:/qml/sub/PopupSkin.qml", Component.PreferSynchronous).createObject(mainFrame, {});
           //gMessage("错误","<img align='middle' src='' width='24' height='24' \>账号密码长度不正确");

       }
   }

   // 游戏
   Common.PicButton {
       id: ganmeBtn;
       width: 16;
       height: 16;
       picSource: "qrc:/images/game.png";
       anchors.right: skinBtn.left;
       anchors.rightMargin: 10;
       anchors.verticalCenter: parent.verticalCenter;
   }

   /***************************************************************************************************
    * 动态加载组件
    ***************************************************************************************************/
   // skin
   Loader {
       id: skin;
        width: 600;
        height: 480;
   }
}
