import QtQuick 2.6
/***
* icon + text button
*/
Rectangle {
    id: bkgrd
    implicitHeight: 50;
    implicitWidth: 120;
    color: "transparent";
    radius: 6;

    property alias iconSource: icon.source;
    property alias iconWidth: icon.width;
    property alias iconHeight: icon.height;
    property alias textColor: btnText.color;
    property alias textFont: btnText.font;
    property alias text: btnText.text;
    property bool bHovered: false;
    signal clicked;

    Image {
        id: icon
        anchors.verticalCenter: parent.verticalCenter;
    }
    Text {
        id: btnText;
        anchors.left: icon.right;
        anchors.verticalCenter: parent.verticalCenter;
        anchors.margins: 4;
        color: ma.pressed ? "blue" : (parent.bHovered ? "#0000a0" : "white");
    }
    MouseArea {
        id: ma;
        anchors.fill: parent;
        hoverEnabled: true;
        onEnabledChanged: {
            bkgrd.bHovered = true;
        }
        onExited: {
            bkgrd.bHovered = false;
        }
        onClicked: {
            bkgrd.bHovered = false;
            bkgrd.clicked();
        }
    }
}
