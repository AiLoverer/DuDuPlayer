import QtQuick 2.6
import QtQuick.Window 2.2
import "qrc:/qml/" as HomePage
/***
* 主页
*/
/*
// 这个采用QuickView 来显示无边框拖动
Rectangle {
    visible: true
    width: 1247
    height: 733

    //灰色0.9透明度
    color:Qt.rgba(0.5,0.5,0.5,0.9)
    MouseArea {
        id: dragRegion
        anchors.fill: parent
        property point clickPos: "0,0"
        onPressed: {
            clickPos  = Qt.point(mouse.x,mouse.y)
            }
        onPositionChanged: {
        //鼠标偏移量
        var delta = Qt.point(mouse.x-clickPos.x, mouse.y-clickPos.y)
        //如果mainwindow继承自QWidget,用setPos
        mainwindow.setX(mainwindow.x+delta.x)
        mainwindow.setY(mainwindow.y+delta.y)
        }
    }

    HomePage.Home {
        id: homePage
        anchors.verticalCenter:  parent.verticalCenter;
        anchors.horizontalCenter: parent.horizontalCenter;
    }

}
*/
// 还是采用 QQmlApplicationEngine 来处理无边框拖动
Window {
    objectName: "rootObject";
    visible: true
    width: 1247
    height: 733
    flags: Qt.FramelessWindowHint;

    //灰色0.9透明度
    //color:Qt.rgba(0.5,0.5,0.5,0.9)
    color: "transparent";
    id: root;
    MouseArea {
        id: dragRegion
        anchors.fill: parent
        property point clickPos: "0,0"
        onPressed: {
            clickPos  = Qt.point(mouse.x,mouse.y)
            }
        onPositionChanged: {
        //鼠标偏移量
        var delta = Qt.point(mouse.x-clickPos.x, mouse.y-clickPos.y)
        //如果mainwindow继承自QWidget,用setPos
        root.x = (root.x+delta.x)
        root.y = (root.y+delta.y)
        }
    }
//    MouseArea { //为窗口添加鼠标事件
//       property int xMouse //存储鼠标x坐标
//       property int yMouse //存储鼠标y坐标
//       anchors.fill: parent
//       acceptedButtons: Qt.LeftButton //只处理鼠标左键
//       drag.filterChildren: true
//       onPressed: { //接收鼠标按下事件
//           xMouse = mouse.x
//           yMouse = mouse.y
//       }
//       onPositionChanged: { //鼠标按下后改变位置
//           root.x = root.x + (mouse.x - xMouse)
//           root.y = root.y + (mouse.y - yMouse)
//       }
//   }

    HomePage.Home {
        id: homePage
        anchors.verticalCenter:  parent.verticalCenter;
        anchors.horizontalCenter: parent.horizontalCenter;
        mainFrame: root;
    }

}

