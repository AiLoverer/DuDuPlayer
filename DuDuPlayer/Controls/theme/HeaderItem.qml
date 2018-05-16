import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

Rectangle{
    id:layout
    property color backGroundColor: "transparent"
    property color borderColor: "#a0a0a0"
    property int borderWidth: 1
    property string title: ""
    property Component content

    color: backGroundColor
    border.color: borderColor
    border.width: borderWidth

    implicitHeight: 25+contentLoader.height+8+borderWidth*2
    implicitWidth: contentLoader.width+8+borderWidth*2
    ColumnLayout{
        anchors.fill: parent
        spacing: 0
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
            id:contentRectangle
            Layout.fillHeight: true
            Layout.fillWidth: true
            color: "transparent"
            Loader{
                id:contentLoader
                anchors.margins: 4
                anchors.centerIn: parent
                sourceComponent: content
            }
        }
    }

}
