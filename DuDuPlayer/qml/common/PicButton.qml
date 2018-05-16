import QtQuick 2.0
/***
* 设置一张图片
*/
Rectangle {
    id: root

    color: "transparent";
    property alias picSource: pic.source;
    property alias picRadius: root.radius;
    signal clicked;

    Image {
        id: pic
        anchors.fill: parent;
    }

    MouseArea {
        id: ma;
        anchors.fill: parent;
        onClicked: {
            root.clicked();
        }
        onPressed: {
            root.color = "green";
        }
        onReleased: {
            root.color = "transparent";
        }
    }

}
