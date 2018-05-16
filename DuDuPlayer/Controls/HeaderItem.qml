import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Controls.Private 1.0
import QtQuick.Layouts 1.1

Rectangle{
    property color backGround: "transparent"
    property color borderColor: "#a0a0a0"
    property int borderWidth: 1
    property string title: ""

    anchors.fill: parent
    color: backGround
    border.color: borderColor
    border.width: borderWidth
    ColumnLayout{
        anchors.fill: parent
        Rectangle{
            Layout.fillWidth: true
            Layout.preferredHeight: 24
            height: 24
            color: "transparent"
            Text {
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 4
                verticalAlignment: Text.AlignVCenter
                text: title
            }
        }
        Rectangle{
            Layout.fillWidth: true
            Layout.preferredHeight: 1
            height: 1
            color: borderColor
        }
        Rectangle{
            Layout.fillHeight: true
            Layout.fillWidth: true
            color: "transparent"
            ContentItem{}
        }
    }

}
