import QtQuick 2.0
import QtQuick.Controls 1.4
import "qrc:/qml/sub" as Sub
/***
* 左边主区域
*/

Rectangle {

    id: leftMain;
    color: Qt.rgba(51/255, 51/255, 51/255, 0.5);

    /*
    // 测试TreeView来显示列表，后续优化会用该控件。
    Sub.TreeViewTest {
        id: playList;
        anchors.left: parent.left;
        anchors.top: parent.top;
        anchors.bottom: parent.bottom;
        width: 310;
        model: lstModelMusic;

    }
    */

    // 本地音乐标题栏
    Sub.LeftMainTitleBar {
        id: localMusicTitleBar;
        anchors.left: parent.left;
        anchors.top: parent.top;
        anchors.right: parent.right;
        height: 40;
    }

    //  本地音乐列表
    Sub.LocalMusicList {
        id: localMusic;
        anchors.left: parent.left;
        anchors.top: localMusicTitleBar.bottom;
        anchors.right: parent.right;
        anchors.bottom: parent.bottom;
    }
}
