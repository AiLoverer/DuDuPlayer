import QtQuick 2.5


Rectangle {
    id: root;
    width: 448;
    height: 625;
    property var strCurrentSongId: "";
    signal clicked(int index);
    color: "transparent";

        Rectangle{
            id: vline;
            color: "#ff9400"
            width: 3;
            height: 625;
            opacity:0.1;

            anchors.left: parent.left;
            anchors.top: parent.top;
            anchors.bottom: parent.bottom;

        }

        Component{
            id: listelegate;
            Rectangle{
                id: mainItem
                width: parent.width;
                height: 91
                //color: "transparent";
                color: ListView.isCurrentItem ? "#ff9400" :  "transparent";
                radius: 10;
                Image{
                    id: imgSong;
                    source: "qrc:/icon-music.png";
                    width: 48;
                    height: 48;
                    anchors.verticalCenter: mainItem.verticalCenter;
                    anchors.left: mainItem.left;
                    anchors.leftMargin: 20;


                }
                Text{
                    id: songNameText;
                    text: songname;
                    width: 276;
                    font.pixelSize: 36;
                    color: "white";
                    anchors.left: imgSong.right;
                    anchors.leftMargin: 36;
                    anchors.verticalCenter: mainItem.verticalCenter;
                    font.bold: true;
                    elide: Text.ElideRight;
                }
                Rectangle{
                    id: lineRect;
                    width: 360;
                    height: 2;
                    color: mainItem.ListView.isCurrentItem ? "#ff9400" :  "#2d2d34";

                    anchors.bottom: parent.bottom;
                    anchors.left: imgSong.left;
                }

                MouseArea{
                    anchors.fill: parent;
                    onClicked: {
                        console.log("clicked list...index : " + index);
                        console.log("clicked list...name : " + songname);
                        mainItem.ListView.view.currentIndex = index;
                        strCurrentSongId = songId;
                        JCNet_AppOnlineMusic.playMusic(index);
                        root.clicked(index);

                    }
                    onPressed:{
                        //mainItem.color = pressedColor;
                    }
                    onReleased: {
                        //mainItem.color = normalColor;
                    }
                }

            }
        }
        ListView{
            id: view;
            model: modelOnlineMusicTypeTopName;
            delegate: listelegate
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
            view.currentIndex = 0;
        }
}

