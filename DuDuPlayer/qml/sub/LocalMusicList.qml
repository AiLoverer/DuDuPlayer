import QtQuick 2.0
import QtQuick.Layouts 1.3
import "qrc:/qml/common" as Common
import "qrc:/qml/common/Function.js" as ComFunc
/***
* 本地音乐播放列表
* 属于LeftMain子页面
*/
Rectangle {
    id: root;

    color: "white";

    property string strCurPosition: "00:00";
    property string strTotalPosition: "00:00";
    Component {
        id: listDelegate;
        Rectangle {
            id: mainItem;

            width: parent.width;
            height: ListView.isCurrentItem ?  60 :40;
            color: ListView.isCurrentItem ?  Qt.rgba(240/255, 240/255, 240/255, 1.0) :  "transparent";
            clip: true;
            // 歌曲图片
            Image{
                id: imgSong;
                source: "qrc:/images/music24.png";
                width: view.currentIndex === index? 55: 24;
                height: view.currentIndex === index? 55 : 24;
                anchors.verticalCenter: mainItem.verticalCenter;
                anchors.left: mainItem.left;
                anchors.leftMargin: 8;

            }
            // 歌名
            Text{
                id: songNameText;
                text: songname;
                width: 180;
                font.pixelSize: 12;
                color: "black";
                anchors.left: imgSong.right;
                anchors.leftMargin: 8;
                anchors.top: parent.top;
                anchors.topMargin: view.currentIndex === index? 10 : 13;
                font.bold: true;
                elide: Text.ElideRight;
            }
            // 时间
            Text {
                id: time;
                text: strCurPosition;
                color: "black";
                width: 50;
                anchors.left: imgSong.right;
                anchors.leftMargin: 8;
                anchors.top: songNameText.bottom;
                anchors.topMargin: 2;
                font.pointSize: 12;
                visible: view.currentIndex === index;
                font.bold: true;
            }

            Row {
                id: layerRect;

                width: 100;
                anchors.right: parent.right;
                anchors.top: parent.top;
                anchors.topMargin: view.currentIndex===index ? 40 : 15;

                spacing: 8;

                // MV
                Common.PicButton {
                    id: imgMV;
                    width: 16;
                    height: 16;
                    picSource: "qrc:/images/film16.png";
                    anchors.verticalCenter: parent.verticalCenter;
                }
                // 下载
                Common.PicButton {
                    id: imgDownload;
                    width: 16;
                    height: 16;
                    picSource: "qrc:/images/download16.png";
                    anchors.verticalCenter: parent.verticalCenter;
                }
                // 收藏
                Common.PicButton {
                    id: imgCollect;
                    width: 16;
                    height: 16;
                    picSource: "qrc:/images/collect24.png";
                    anchors.verticalCenter: parent.verticalCenter;
                }

                // 更多
                Common.PicButton {
                    id: imgMore;
                    width: 16;
                    height: 16;
                    picSource: "qrc:/images/more16.png";
                    anchors.verticalCenter: parent.verticalCenter;
                }

            }



            Rectangle{
                id: lineRect;
                width: 360;
                height: 1;
                color: mainItem.ListView.isCurrentItem ? "#ff9400" :  "#2d2d34";
                anchors.bottom: parent.bottom;
                anchors.left: parent.left;
            }
            MouseArea {
                anchors.fill: parent;
                onClicked: {
                    console.log("clicked list...index : " + index);
                    console.log("clicked list...name : " + songname);
                    mainItem.ListView.view.currentIndex = index;
                    //JCNet_AppOnlineMusic.playMusic(index);

                }
                onPressed:{
                    //mainItem.color = pressedColor;
                }
                onReleased: {
                    //mainItem.color = normalColor;
                }
                onDoubleClicked: {
                    mainItem.ListView.view.currentIndex = index;
                    CppLocalMusic.playMusic(index);
                }
            }
        }

    }

    ListView {
        id: view;
        model: localMusicModel;
        delegate: listDelegate
        orientation: ListView.Vertical;
        anchors.fill: parent;
        clip: true;
        //highlight: Rectangle { color: "#ff9400" }

        onContentYChanged: {
            if (view.contentY < 0) {
                button.y = 0;
                return;
            }

            button.y = view.contentY * (rectLine0.height-button.height) / (view.contentHeight-view.height) > (rectLine0.height - button.height) ?
                        (rectLine0.height - button.height) :
                        view.contentY * (rectLine0.height-button.height) / (view.contentHeight-view.height);
        }

    }
    // 竖直滚动条
    Rectangle {
        id: rectLine0;

        height: 540;
        width: 2;
        color: Qt.rgba(39/255, 41/255, 47/255, 1.0);
        anchors.right: parent.right;
        anchors.rightMargin: 36;
        anchors.top: parent.top;
        anchors.topMargin: 30;
        visible: view.contentHeight>view.height ? true : false;

        // 按钮
        Rectangle {
            id: button;

            x: -4;
            width: 9;
            height: 95;
            radius: 4;
            color: Qt.rgba(1.0, 148/255, 0, 1.0);

            // 鼠标区域
            MouseArea {
                id: mouseArea

                anchors.fill: button;
                drag.target: button;
                drag.axis: Drag.YAxis;
                drag.minimumY: 0;
                drag.maximumY: rectLine0.height - button.height;

                // 拖动
                onMouseYChanged: {
                    view.contentY = button.y * (view.contentHeight-view.height) / (rectLine0.height-button.height);
                }
            }
        }
    }// Rectangle-rectLine0

    Component.onCompleted: {
        view.currentIndex = -1;
        CppLocalMusic.getMusicData();
    }

    /**************************************************************************************************************
    * 以下是信号处理 C++
    * 上一曲/下一曲: 播放索引改变: onSigQMLPlayIndexChanged
    ***************************************************************************************************************/
    Connections {
        target: CppLocalMusic;
        onSigQMLPlayIndexChanged: {
            console.log("play index changed !");
            view.currentIndex = nIndex;
        }
        onSigQMLPositionChanged: {
            //console.log(" qml sig PositonChanged: " + position);
            strCurPosition = ComFunc.dateFormat(position) + "/" + strTotalPosition;
        }
        onSigQMLDurationChanged: {
            // console.log(" qml sig DurationChanged: " + duration);
            strTotalPosition  = ComFunc.dateFormat(duration);
        }
    }

}
