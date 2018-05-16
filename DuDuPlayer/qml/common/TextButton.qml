import QtQuick 2.0

/***
* text button
* 选中标记
*/
Rectangle {
    id: bkgrd
    //implicitHeight: 50;
    //implicitWidth: 120;
    color: bSelected ? Qt.rgba(128/255, 36/255, 14/255, 1.0) : "transparent";
    radius: width / 3;

    property alias textColor: btnText.color;
    property alias text: btnText.text;
    property alias textFontSize: btnText.font.pointSize;
    property alias bold: btnText.font.bold;
    property bool bHovered: false;
    property bool bSelected: false;
    signal clicked;

    Text {
        id: btnText;
        anchors.verticalCenter: parent.verticalCenter;
        anchors.horizontalCenter: parent.horizontalCenter;
        color: ma.pressed ? "blue" : (parent.bHovered ? "#0000a0" : "white");
        font.pointSize: 12;
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
