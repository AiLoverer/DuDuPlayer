import QtQuick 2.0
import "qrc:/qml/sub/" as Sub
import "qrc:/qml/sub/onlinemusic/" as SubOnline
/***
* 右边主区域
*/
Rectangle {
    id: root;
    color: Qt.rgba(51/255, 51/255, 51/255, 0.3);

    property int nCurShowIndex: 0;
    Sub.RightMainTitlebar {
        id: rightMainTitleBar;
        anchors.left: parent.left;
        anchors.top: parent.top;
        anchors.right: parent.right;
        height: 40;
        onSelectTab: {
            if(number === nCurShowIndex)
            {
                return;
            }
            showTab(nCurShowIndex, false);
            showTab(number,true);
            nCurShowIndex = number;
        }
    }
    Sub.PageOnlineMusic {
        id: onlineMusic;
        anchors.left: parent.left;
        anchors.top: rightMainTitleBar.bottom;
        anchors.right: parent.right;
        anchors.bottom: parent.bottom;
        visible: true;
    }
    Sub.PageRadio {
        id: radio;
        anchors.left: parent.left;
        anchors.top: rightMainTitleBar.bottom;
        anchors.right: parent.right;
        anchors.bottom: parent.bottom;
        visible: false;
    }
    Sub.PageSongList {
        id: songlist;
        anchors.left: parent.left;
        anchors.top: rightMainTitleBar.bottom;
        anchors.right: parent.right;
        anchors.bottom: parent.bottom;
        visible: false;
    }
    Sub.PageMV {
        id: mv;
        anchors.left: parent.left;
        anchors.top: rightMainTitleBar.bottom;
        anchors.right: parent.right;
        anchors.bottom: parent.bottom;
        visible: false;
    }
    Sub.PageLive {
        id: live;
        anchors.left: parent.left;
        anchors.top: rightMainTitleBar.bottom;
        anchors.right: parent.right;
        anchors.bottom: parent.bottom;
        visible: false;
    }
    Sub.PageKTV {
        id: ktv;
        anchors.left: parent.left;
        anchors.top: rightMainTitleBar.bottom;
        anchors.right: parent.right;
        anchors.bottom: parent.bottom;
        visible: false;
    }
    Sub.PageLyric {
        id: lyric;
        anchors.left: parent.left;
        anchors.top: rightMainTitleBar.bottom;
        anchors.right: parent.right;
        anchors.bottom: parent.bottom;
        visible: false;
    }
    function showTab(number, visibl)
    {
       switch (number)
       {
       case 0:
           onlineMusic.visible = visibl;
           break;
       case 1:
           radio.visible = visibl;
           break;
       case 2:
           songlist.visible = visibl;
           break;
       case 3:
           mv.visible = visibl;
           break;
       case 4:
           live.visible = visibl;
           break;
       case 5:
           ktv.visible = visibl;
           break;
       case 6:
           lyric.visible = visibl;
           break;
       }
    }
    Component.onCompleted: {
        nCurShowIndex = 0;
        showTab(0, true);
        //console.log("component completed ...");
    }
}
