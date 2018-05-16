import QtQuick 2.4
import QtQuick.Layouts 1.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

/***
* 测试treeview
*/
Rectangle {
    id: root

    property var ctrl
    property var model

    x:100
    y:50
    TreeView {
        id:view
        width: 500
        anchors.fill: parent;
        TableViewColumn {
            title: "Name"
            role: "name"
            width: 250
        }
        TableViewColumn {
            title: "Simplify"
            role: "simplify"
            width: 50
        }
        model: root.model
        itemDelegate: Item {
               Text {
                   anchors.verticalCenter: parent.verticalCenter
                   color: "black"
                   elide: styleData.elideMode
                   text: styleData.value
                   font.pixelSize: 12;
                   font.bold: true;
               }
        }
        headerDelegate: Rectangle{
            id: head;
            width: 100;
            height: 40;
            color: styleData.pressed ?"red" : "gray";
            Text{
                anchors.verticalCenter: parent.verticalCenter
                color: styleData.pressed ? "blue" : "green";
                text: styleData.value
                font.pixelSize: 20;
                font.bold: true;
            }
        }

        rowDelegate: Rectangle {
            id: rowRect;
            //color: "transparent"
            width: 250;
            height: 40;
            Text{
                anchors.verticalCenter: parent.verticalCenter
                color: styleData.pressed ? "blue" : "green";
                font.pixelSize: 14;
                font.bold: true;
            }
            Rectangle{
                id:line
                width: 250;
                height: 1;
                color: "gray";

            }
        }

        property bool isCollapse: true
        onClicked: {
            console.log("onClicked:", index)
            console.log("isExpanded:",isExpanded(index))
            //isExpanded(index)
            /*if (isCollapse)
            {
                console.log("expand")
                emit: view.expand(index);
                isCollapse = false;
            }
            else
            {
                console.log("collapse")
                emit: view.collapse(index);
                isCollapse = true;
            }
            if (isExpanded(index))
            {
                collapse(index);
            }
            else
            {
                expand(index);
            }*/
        }
        onDoubleClicked: {
            if (isExpanded(index))
            {
                collapse(index);
            }
            else
            {
                expand(index);
            }
        }
    }

//    Rectangle {
//        width: 50
//        height: 50
//        color: "red"
//        anchors.top: view.bottom
//        anchors.topMargin: 50
//        Button {
//            anchors.fill: parent
//            text: qsTr("Add")
//            style: ButtonStyle{
//                background: Rectangle{
//                    anchors.fill: parent
//                    color: "transparent"
//                }
//                label: Label{
//                    anchors.centerIn: parent
//                    text: control.text
//                    font.pixelSize: 20
//                }
//            }
//            onClicked: {
//                //addDataClicked(QModelIndex index)
//                root.ctrl.addDataClicked(view.currentIndex);
//            }
//        }
//    }
}

