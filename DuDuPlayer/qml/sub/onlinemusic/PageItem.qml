import QtQuick 2.5


Rectangle {
    id: root;

    property alias  setImg: itemImg.source;
    property alias setTxt: itemTxt.text;

    signal sigRelease(url src, string txt);

    width: 250;
    height: 160;

    Image {
        id: itemImg
        width: 250;
        height: 160;
        source: "qrc:/images/null.png";
    }

    Text{
        id: itemTxt;
        anchors.top: root.top;
        anchors.topMargin: 116;
        anchors.horizontalCenter: parent.horizontalCenter;
        font.pixelSize: 36;
        color: "white";
    }
    MouseArea {
        anchors.fill: parent;

        onReleased: {
            sigRelease(itemImg.source, itemTxt.text);
        }
    }

}

