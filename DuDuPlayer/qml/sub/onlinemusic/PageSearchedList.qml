import QtQuick 2.5

Rectangle {
    id: root;
    width: 1280;
    height: 625;
    color: "transparent";

        Text{
            id: txtSearched;

            anchors.left: parent.left;
            anchors.leftMargin: 34;
            anchors.top: parent.top;
            anchors.topMargin: 24;
            font.pixelSize: 36;
            font.family: "Simhei";
            color: "white";
            text: qsTr("搜索结果");

        }

        Rectangle{
            id: hsecondline;
            color: "#ff9400"
            height: 3;
            opacity:0.1;

            anchors.left: parent.left;
            anchors.top: txtSearched.bottom;
            anchors.topMargin: 24;
            anchors.right: parent.right;

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
                    source: "qrc:/images/icon-music.png";
                    width: 48;
                    height: 48;
                    anchors.verticalCenter: mainItem.verticalCenter;
                    anchors.left: mainItem.left;
                    anchors.leftMargin:  78;

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
                    color: mainItem.ListView.isCurrentItem ?"#ff9400" : "#2d2d34";

                    anchors.bottom: parent.bottom;
                    anchors.left: imgSong.left;
                    anchors.right: parent.right;
                    anchors.rightMargin: 78;
                }

                MouseArea{
                    anchors.fill: parent;
                    onClicked: {
                        //console.log("clicked list...index : " + index);
                        //console.log("clicked list...name : " + songname);
                        mainItem.ListView.view.currentIndex = index;
                        JCNet_AppOnlineMusic.playMusic(index);

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
            model: modelOnlineMusicTypeSearched;
            delegate: listelegate
            orientation: ListView.Vertical;
            anchors.left: parent.left;
            anchors.top: hsecondline.bottom;
            anchors.topMargin: 2;
            anchors.right: parent.right;
            anchors.bottom: parent.bottom;
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

            height: 500;
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

}

