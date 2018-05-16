import QtQuick 2.5
Rectangle {
    id: root;

    width: 1280;
    height: 625;
    color: "transparent";
    clip: true;
    property alias listModel: item.model;

    Component{
        id: listDelegate;
        Rectangle {
            id: root;

            property alias  setImg: itemImg.source;
            property alias setTxt: itemTxt.text;

            signal sigRelease(url src, string txt);

            width: 250;
            height: 290;
            color: "transparent";

            Image {
                id: itemImg
                width: 250;
                height: 250;
                source: singerpicurl != ""  ?  singerpicurl : "qrc:/images/null.png";
            }

            Text{
                id: itemTxt;
                anchors.top: itemImg.bottom;
                anchors.topMargin: 4;
                anchors.horizontalCenter: parent.horizontalCenter;
                font.pixelSize: 36;
                color: "white";
                text: singername;
            }
            MouseArea {
                anchors.fill: parent;

                onReleased: {
                    sigRelease(itemImg.source, itemTxt.text);
                }
            }

        }
    }


    Flickable {
        id: hotFlicker;

        anchors.fill: parent;
        clip: true;
        anchors.top: parent.top;
        anchors.topMargin: 34;
        anchors.left: parent.left;
        anchors.leftMargin: 158;
        anchors.right: parent.right;
        anchors.rightMargin: 158;

        contentWidth: hotGrid.width;
        contentHeight: hotGrid.height;
        boundsBehavior: Flickable.StopAtBounds;

        Grid {
            id: hotGrid;

            columns: 2;
            columnSpacing: 107;
            rowSpacing: 30;
            anchors.horizontalCenter: parent.horizontalCenter;
            Repeater {
                id: item
                model: modelOnlineMusicTypeTopName;
                delegate: listDelegate;
            }

        }

    }

}

