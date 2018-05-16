import QtQuick 2.0
import QtQuick 2.0
import "qrc:/qml/common/"   as Common
/***
* 标题栏
* 属于RightMain的标题栏
*/
Rectangle {
    id: root;

    color: Qt.rgba(161/255, 45/255, 18/255, 1.0); // 后续会做皮肤 统一赋值

    property int nSpace: 40;
    property var curSelectedBtn: musiclibrary;

    // 0： 乐库 1:电台 2: 歌单 3： MV 4： 直播 5： KTV 6： 歌词
    signal selectTab(int number);
    // 乐库
    Common.TextButton {
        id: musiclibrary
        text: qsTr("乐库");
        textFontSize: 14;
        textColor: "white";
        bSelected: true;
        bold: true;
        width: 56;
        height: 24;
        anchors.left: parent.left;
        anchors.verticalCenter: parent.verticalCenter;
        anchors.leftMargin: 30;
        MouseArea {
            anchors.fill: parent;
            onClicked: {
                if(!musiclibrary.bSelected)
                {
                   musiclibrary.bSelected = true;
                   curSelectedBtn.bSelected = false;
                   curSelectedBtn = musiclibrary;
                }
                root.selectTab(0);
            }
        }
    }
    // 电台
    Common.TextButton {
        id: musicRadio;
        text: qsTr("电台");
        textFontSize: 14;
        textColor: "white";
        bold: true;
        width: 56;
        height: 24;
        anchors.left: musiclibrary.right;
        anchors.verticalCenter: parent.verticalCenter;
        anchors.leftMargin: nSpace;

        MouseArea {
            anchors.fill: parent;
            onClicked: {
                if(!musicRadio.bSelected)
                {
                   musicRadio.bSelected = true;
                   curSelectedBtn.bSelected = false;
                   curSelectedBtn = musicRadio;
                }
                 root.selectTab(1);
            }
        }
    }
    // 歌单
    Common.TextButton {
        id: musicList;
        text: qsTr("歌单");
        textFontSize: 14;
        textColor: "white";
        bold: true;
        width: 56;
        height: 24;
        anchors.left: musicRadio.right;
        anchors.verticalCenter: parent.verticalCenter;
        anchors.leftMargin: nSpace;

        MouseArea {
            anchors.fill: parent;
            onClicked: {
                if(!musicList.bSelected)
                {
                   musicList.bSelected = true;
                   curSelectedBtn.bSelected = false;
                   curSelectedBtn = musicList;
                }
                 root.selectTab(2);
            }
        }
    }
    // MV
    Common.TextButton {
        id: musicMV;
        text: qsTr("MV");
        textFontSize: 14;
        textColor: "white";
        bold: true;
        width: 56;
        height: 24;
        anchors.left: musicList.right;
        anchors.verticalCenter: parent.verticalCenter;
        anchors.leftMargin: nSpace;

        MouseArea {
            anchors.fill: parent;
            onClicked: {
                if(!musicMV.bSelected)
                {
                   musicMV.bSelected = true;
                   curSelectedBtn.bSelected = false;
                   curSelectedBtn = musicMV;
                }
                 root.selectTab(3);
            }
        }
    }
    // 直播
    Common.TextButton {
        id: musicLive;
        text: qsTr("直播");
        textFontSize: 14;
        textColor: "white";
        bold: true;
        width: 56;
        height: 24;
        anchors.left: musicMV.right;
        anchors.verticalCenter: parent.verticalCenter;
        anchors.leftMargin: nSpace;

        MouseArea {
            anchors.fill: parent;
            onClicked: {
                if(!musicLive.bSelected)
                {
                   musicLive.bSelected = true;
                   curSelectedBtn.bSelected = false;
                   curSelectedBtn = musicLive;
                }
                 root.selectTab(4);
            }
        }
    }
    // KTV
    Common.TextButton {
        id: musicKTV;
        text: qsTr("KTV");
        textFontSize: 14;
        textColor: "white";
        bold: true;
        width: 56;
        height: 24;
        anchors.left: musicLive.right;
        anchors.verticalCenter: parent.verticalCenter;
        anchors.leftMargin: nSpace;

        MouseArea {
            anchors.fill: parent;
            onClicked: {
                if(!musicKTV.bSelected)
                {
                   musicKTV.bSelected = true;
                   curSelectedBtn.bSelected = false;
                   curSelectedBtn = musicKTV;
                }
                 root.selectTab(5);
            }
        }
    }
    // 歌词
    Common.TextButton {
        id: musicLyric;
        text: qsTr("歌词");
        textFontSize: 14;
        textColor: "white";
        bold: true;
        width: 56;
        height: 24;
        anchors.left: musicKTV.right;
        anchors.verticalCenter: parent.verticalCenter;
        anchors.leftMargin: nSpace;

        MouseArea {
            anchors.fill: parent;
            onClicked: {
                if(!musicLyric.bSelected)
                {
                   musicLyric.bSelected = true;
                   curSelectedBtn.bSelected = false;
                   curSelectedBtn = musicLyric;
                }
                 root.selectTab(6);
            }
        }
    }
}
