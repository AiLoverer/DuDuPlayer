import QtQuick 2.5



Rectangle {
    id: root;

    property color pressedColor : "#ff9400";
    property color normalColor : "transparent";
    property int nCollectDataSize: 0;
    property int nHistoryDataSize: 0;


    property bool bShowCollect: true;
    signal clickedOneKeyClean();

    anchors.fill: parent;
    width: 1280;
    height: 625;
    color: "transparent";
    clip: true;

    ListModel{
        id: titleTabModel;

        ListElement{
            name: qsTr("收藏");

        }
        ListElement{
            name: qsTr("历史");

        }
    }
    Rectangle{
        id: titleRect;
        anchors.left: parent.left;
        anchors.top: parent.top;
        anchors.right: parent.right;
        height: 90;
        color: "transparent";

        // 一键清除按钮
        Rectangle{
            id: oneKeyClearAllRect;

            anchors.right: parent.right;
            anchors.rightMargin: 108;
            anchors.verticalCenter: titleRect.verticalCenter;
            height: 80;
            width: 164;
            color: "transparent";
            radius: 8;

            Text{
                text: qsTr("一键清除");
                color: "white";
                font.pixelSize: 24;
                anchors.verticalCenter: parent.verticalCenter;
                anchors.left: oneKeyClearAllRect.left;
                font.bold: true;
            }

            Image{
                anchors.right: parent.right;
                anchors.verticalCenter: parent.verticalCenter;
                width: 44;
                height: 44;
                source: "qrc:/images/icon-delete.png";
            }
            MouseArea{
                anchors.fill: parent;
                onPressed: {
                    oneKeyClearAllRect.color = pressedColor;
                }
                onReleased:
                {
                    oneKeyClearAllRect.color = normalColor;
                }

                onClicked: {
                    root.clickedOneKeyClean();
                }
            }

        }

        // 历史
        Rectangle{
            id: historyBtnRect;

            anchors.right: oneKeyClearAllRect.left;
            anchors.rightMargin: 164;
            anchors.top: parent.top;
            height:90;
            width: 164;
            color: "transparent";

            Image{
                id: imgHistort;
                anchors.left: parent.left;
                width: 44;
                height: 44;
                anchors.verticalCenter: parent.verticalCenter;
                source: bShowCollect === true ?"qrc:/images/icon-history.png" : "qrc:/images/icon-history-click.png";
            }

            Text{
                id: txtHistory;

                anchors.right: parent.right;
                anchors.verticalCenter: parent.verticalCenter;
                text: qsTr("历史");
                color: bShowCollect === true? "white" : pressedColor;
                font.pixelSize: 36;
                font.bold: true;

            }
            //  选中状态的高亮下划线
            Rectangle{
                anchors.horizontalCenter: parent.horizontalCenter;
                anchors.bottom: parent.bottom;
                width: 150;
                height: 3;
                color: "#ff9400";
                visible: !bShowCollect;
            }

            MouseArea{
                anchors.fill: parent;
                onClicked: {
                    console.log("clicked history button ...");
                    bShowCollect = false;
                    if(nHistoryDataSize <= 0 )
                    {
                        clearnTip.visible = true;
                        view.visible = false;
                    }
                    else
                    {
                        clearnTip.visible = false;
                        view.visible = true;
                    }
                }
            }

        }

        // 收藏
        Rectangle{
            id: collectBtnRect;

            anchors.right: historyBtnRect.left;
            anchors.rightMargin: 164;
            anchors.top: parent.top;
            height:90;
            width: 164;
            color: "transparent";

            Image{
                id: imgCollect;
                anchors.left: parent.left;
                width: 44;
                height: 44;
                anchors.verticalCenter: parent.verticalCenter;
                source: bShowCollect === true ? "qrc:/images/icon-col-click.png":"qrc:/images/icon-col.png";
            }

            Text{
                id: txtCollect;

                anchors.right: parent.right;
                anchors.verticalCenter: parent.verticalCenter;
                text: qsTr("收藏");
                color: bShowCollect === true? pressedColor : "white" ;
                font.pixelSize: 36;
                font.bold: true;

            }
            //  选中状态的高亮下划线
            Rectangle{
                anchors.horizontalCenter: parent.horizontalCenter;
                anchors.bottom: parent.bottom;
                width: 150;
                height: 3;
                color: "#ff9400";
                visible: bShowCollect;
            }

            MouseArea{
                anchors.fill: parent;
                onClicked: {
                    console.log("clicked collect button ...");
                    bShowCollect = true;
                    if(nCollectDataSize <= 0 )
                    {
                        clearnTip.visible = true;
                        view.visible = false;
                    }
                    else
                    {
                        clearnTip.visible = false;
                        view.visible = true;
                    }
                }
            }

        }
        Rectangle{//  下划线
            width: root.width;
            height:2;
            color: "#ff9400";
            opacity:0.1;
            anchors.bottom: parent.bottom;
        }

    }

    Component{
        id: collectDelegate;
        Rectangle{
            id: mainItem
            width: parent.width;
            height: 80
            color: ListView.isCurrentItem ? "#ff9400": "transparent";
            radius: 10;
            Image{
                id: imgSong;
                source: "qrc:/images/icon-music.png";
                width: 48;
                height: 48;
                anchors.verticalCenter: mainItem.verticalCenter;
                anchors.left: mainItem.left;
                anchors.leftMargin: 78;


            }
            Text{
                id: songNameText;
                text: songname;
                font.pixelSize: 36;
                color: "white";
                anchors.left: imgSong.right;
                anchors.leftMargin: 35;
                anchors.right: btnDeleteRect.left;
                anchors.rightMargin: 10;
                anchors.verticalCenter: mainItem.verticalCenter;
                font.bold: true;
                elide: Text.ElideRight;
            }
            Rectangle{
                id: btnDeleteRect;
                anchors.right: parent.right;
                anchors.rightMargin: 108;
                width: 44;
                height: 44;
                anchors.verticalCenter: mainItem.verticalCenter;
                color: "transparent";

                Image {
                    id: imgDelete;
                    source: "qrc:/images/icon-delete.png"
                }
                MouseArea{
                    anchors.fill: parent;
                    onClicked: {
                        console.log("clicked delete button of songs ... " + index);
                        mainItem.ListView.view.currentIndex = index;
                        if(personalCenterRect.bShowCollect)
                        {
                            JCNet_AppOnlineMusic.deleteCollectMusic(index);
                        }
                        else
                        {
                            JCNet_AppOnlineMusic.deleteHistoryMusic(index);
                        }
                    }
                }
            }
            MouseArea{
                //anchors.fill: parent;
                anchors.left: parent.left;
                anchors.top: parent.top;
                anchors.right: btnDeleteRect.left;
                anchors.bottom: parent.bottom;
                onClicked: {
                     mainItem.ListView.view.currentIndex = index;
                }
            }

        }
    }

    // 中央区域
    Rectangle{
        id: mainRect;
        anchors.left: parent.left;
        anchors.top: titleRect.bottom;
        anchors.topMargin: 2;
        anchors.right: parent.right;
        anchors.bottom: parent.bottom;
        color: "transparent"

        Text {
            id: clearnTip;
            font.pixelSize: 48;
            font.bold: true;
            color: "white";

            anchors.verticalCenter: parent.verticalCenter;
            anchors.horizontalCenter: parent.horizontalCenter;

            visible: false;
            text: bShowCollect === true? qsTr("暂无收藏内容") : qsTr("暂无历史内容");

        }

        ListView{
            id: view;
            model: personalCenterRect.bShowCollect === true ? modelOnlineMusicCollect : modelOnlineMusicHistory;
            delegate: collectDelegate
            orientation: ListView.Vertical;
            anchors.fill: parent;
            clip: true;

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

            height: 374;
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

    Component.onCompleted: {
        view.currentIndex = 0;
    }
    Connections {
        target: JCNet_AppOnlineMusic;

        onSigQMLHistoryDataChanged: {
            console.log("onSigQMLHistoryDataChanged..." + nSize);
            nHistoryDataSize = nSize;
            if(!bShowCollect)
            {
                if(nSize <= 0 )
                {
                    clearnTip.visible = true;
                    view.visible = false;
                }
                else
                {
                    clearnTip.visible = false;
                    view.visible = true;
                }
            }
        }
        onSigQMLCollectDataChanged: {
            console.log("onSigQMLCollectDataChanged..."  + nSize);
           nCollectDataSize = nSize;
            if(bShowCollect)
            {
                if(nSize <= 0 )
                {
                    clearnTip.visible = true;
                    view.visible = false;
                }
                else
                {
                    clearnTip.visible = false;
                    view.visible = true;
                }
            }
        }

    }

}

