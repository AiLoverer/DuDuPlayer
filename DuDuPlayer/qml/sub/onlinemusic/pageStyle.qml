import QtQuick 2.5


Rectangle {
    id: root;

    anchors.fill: parent;
    color: "transparent";
    clip: true;
    property alias listModel: item.model;

    Flickable {
        id: hotFlicker;

        anchors.fill: parent;
        clip: true;
        anchors.top: parent.top;
        anchors.topMargin: 34;
        anchors.left: parent.left;
        anchors.leftMargin: 50;
        anchors.right: parent.right;
        anchors.rightMargin: 50;

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
                model: listModel;
                delegate: PageItem{
                    setImg: picUrl;
                    setTxt: type;

                }

            }

        }

    }

}

