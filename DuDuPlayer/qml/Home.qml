import QtQuick 2.0

/***
* 主页
*/
Rectangle {
    id: home
    width: 1000;
    height: 700;
    color:Qt.rgba(0.1, 0.1, 0.1,0.1)
    radius: 10;
    property var mainFrame;
    Image {
        id: bkImg;
        anchors.fill : parent;
        source: "qrc:/images/dudu.jpg";
    }

    TitleBar {
        id: titlebar;
        anchors.left: parent.left;
        anchors.top: parent.top;
        anchors.right: parent.right;
        height: 50;
        mainFrame: root.mainFrame;
    }
    LeftMain {
        id: leftMain;
        anchors.left: parent.left;
        anchors.top: titlebar.bottom;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 60;
        width: 310;
    }
    RightMain {
        id: rightMain;
        anchors.left: leftMain.right;
        anchors.leftMargin: 3;
        anchors.right: parent.right;
        anchors.top: titlebar.bottom;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 60;
    }
    MusicMediaPlayerBar {
        id: mediaPlayer;
        anchors.left: parent.left;
        anchors.bottom: parent.bottom;
        anchors.right: parent.right;
        height: 60;
    }

}
