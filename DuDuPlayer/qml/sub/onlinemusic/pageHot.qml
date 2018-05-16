import QtQuick 2.5

Rectangle {
    id: root;

    anchors.fill: parent;
    color: "transparent";
    clip: true;

    signal sigChooseTopItem(var name, var url);

    property int nSpace: 50
    Flickable {
        id: hotFlicker;

        anchors.fill: parent;
        clip: true;
        anchors.top: parent.top;
        anchors.topMargin: 34;
        anchors.left: parent.left;
        anchors.leftMargin: nSpace;
        anchors.right: parent.right;
        anchors.rightMargin: nSpace;
        contentWidth: hotGrid.width;
        contentHeight: hotGrid.height;
        boundsBehavior: Flickable.StopAtBounds;
        property int nIndex: 0
        Grid {
            id: hotGrid;

            columns: 2;
            columnSpacing: 107;
            rowSpacing: 30;

            Repeater {
                anchors.horizontalCenter: parent.horizontalCenter;
                model: modelOnlineMusicTypeHot;
                delegate: PageItem{
                    setImg: url;
                    setTxt: name;

                    onSigRelease: {
                        hotFlicker.nIndex = index;
                        root.sigChooseTopItem(name, url);
                    }

                }

            }

        }

        onNIndexChanged: {
            //console.log("------: " + nIndex);
        }


    }
    Component.onCompleted: {
        //console.log("qml getData ...");
        //JCNet_AppOnlineMusic.getHotData();
    }

}

