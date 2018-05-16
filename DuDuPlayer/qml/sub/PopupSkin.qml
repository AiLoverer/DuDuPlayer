import QtQuick 2.3
//import QtQuick.Dialogs 1.2
import QtQuick.Window 2.2
//import QtQuick.Controls 2.1
import QtQuick.Controls 1.4
//import QtGraphicalEffects 1.0
//import Qt3D.Render 2.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3
import "qrc:/qml/commom" as Common


/***
* 皮肤主题窗口
* 弹出皮肤选择窗口
*/
Window {
    visible: true;
    width: 560
    height: 450
    flags: Qt.FramelessWindowHint;
    modality: Qt.ApplicationModal;

    //灰色0.9透明度
    color:Qt.rgba(0.5,0.5,0.5,0.9)
    //color: "transparent";
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
    // 标题栏
    Rectangle{
        id: titleRect;
        anchors.left: parent.left;
        anchors.top: parent.top;
        anchors.right: parent.right;
        height: 40;
        color: Qt.rgba(161/255, 45/255, 18/255, 1.0); // 后续会做皮肤 统一赋值

        // 标题
        Text {
            id: title;
            anchors.left: parent.left;
            anchors.leftMargin: 10;
            anchors.verticalCenter: parent.verticalCenter;
            text: qsTr("主题皮肤设置和窗口调整");
            color: "white";
            font.pointSize: 10;
            font.bold: true;
        }

        // 取消关闭按钮
        Rectangle {
            id: cancelRect;

            anchors.right: parent.right;
            anchors.verticalCenter: parent.verticalCenter;
            color: "transparent";

            width: 24;
            height: 24;
            Image {
                id: cancelImg
                anchors.fill: parent;
                source: "qrc:/images/cancel.png";
            }
            MouseArea {
                id: ms;
                anchors.fill: parent;

                onClicked: {
                    root.close();
                }
            }
        }
        // 以下是主界面区域
        TabView{
            id: mainUI;
            anchors.left:  parent.left;
            anchors.top: titleRect.bottom;
            anchors.right: parent.right;
           // anchors.bottom: parent.bottom;
            Tab {
              title: qsTr("推荐");
              Rectangle { color: "red" }
            }
            Tab {
              title: qsTr("纯色");
              Rectangle { color: "blue" }
            }
            Tab {
              title: qsTr("我的");
              Rectangle { color: "green" }
            }
            style: TabViewStyle {
                tab: Item{
                    implicitWidth: Math.max(text.width + 8, 80);
                    implicitHeight: 48;
                    Rectangle {
                        width: (styleData.index < control.count - 1) ? (parent.width - 2) : parent.width;
                        height: parent.height - 4;
                        anchors.top: parent.top;
                        anchors.left: parent.left;
                        anchors.leftMargin: 1;
                        visible: styleData.selected;
                        gradient: Gradient {
                            GradientStop{position: 0.0; color: "#606060";}
                            GradientStop{position: 0.5; color: "#c0c0c0";}
                            GradientStop{position: 1.0; color: "#a0a0a0";}
                        }
                    }
                    Rectangle {
                        width: 2;
                        height: parent.height - 4;
                        anchors.top: parent.top;
                        anchors.right: parent.right;
                        visible: styleData.index < control.count - 1;
                        gradient: Gradient {
                            GradientStop{position: 0.0; color: "#404040";}
                            GradientStop{position: 0.5; color: "#707070";}
                            GradientStop{position: 1.0; color: "#404040";}
                        }
                    }
                    RowLayout {
                        implicitWidth: Math.max(text.width, 72);
                        height: 48;
                        anchors.centerIn: parent;
                        z: 1;
            //                        Image{
            //                            width: 48;
            //                            height: 48;
            //                            source: warnrect.icons[styleData.index%3];
            //                        }
                        Text {
                            id: text;
                            text: styleData.title;
                            font.pointSize: 20;
                            color: styleData.selected ? "blue" : (styleData.hovered ? "green" : "white");
                        }
                    }
                }
                tabBar: Rectangle {
                    height: 56;
                    gradient: Gradient {
                        GradientStop{position: 0.0; color: "#484848";}
                        GradientStop{position: 0.3; color: "#787878";}
                        GradientStop{position: 1.0; color: "#a0a0a0";}
                    }
                    Rectangle {
                        width: parent.width;
                        height: 4;
                        anchors.bottom: parent.bottom;
                        border.width: 2;
                        border.color: "#c7c7c7";
                    }
                }
            }

        }
    }

}


//Popup {
//    property var subtext: ""
//    property var subtitle: ""
//    id: messsagebox2
//    x: 0
//    y: 0
//    padding: 0
//    background: Item{}
//    //是否使用popup背景
//    //              dim:false
//    width: 500
//    height: 500
//    modal: true
//    focus: true
//    closePolicy: Popup.NoAutoClose

//    MouseArea {
//        id: dragRegion
//        anchors.fill: parent
//        property point clickPos: "0,0"
//        onPressed: {
//            clickPos  = Qt.point(mouse.x,mouse.y)
//            }
//        onPositionChanged: {
//        //鼠标偏移量
//        var delta = Qt.point(mouse.x-clickPos.x, mouse.y-clickPos.y)
//        //如果mainwindow继承自QWidget,用setPos
//        messsagebox2.x = (messsagebox2.x+delta.x)
//        messsagebox2.y = (messsagebox2.y+delta.y)
//        }
//    }
//    Rectangle {
//        id: pp
//        width: parent.width*0.8
//        height: parent.height/2
//        anchors.centerIn: parent
//        color: "#35C47F"
//        radius: 5
//        clip: true
//        ScrollView {
//            id:flck
//            width: parent.width
//            height: parent.height -mok.height
//            Column{
//                id:col

//                Text{
//                    id:title
//                    text:subtitle
//                    font.pointSize: 24
//                    verticalAlignment: Text.AlignVCenter
//                    //padding: 15
//                    width: parent.width
//                    height: 40
//                    color: "#FAFCF7"
//                    wrapMode: Text.WrapAnywhere
//                    textFormat: Text.RichText
//                    BorderImage {
//                        id:closeimg
//                        source: ""
//                        width: 24; height: 24
//                        border.left: 1; border.top: 1
//                        border.right: 1; border.bottom: 1
//                        x:title.width - width - 5
//                        y:title.height/2 - height/2
//                        MouseArea{
//                            anchors.fill: parent
//                            onClicked: {
//                                messsagebox2.close();
//                            }
//                        }
//                        Timer{
//                            id:tttest
//                            running: messsagebox2.visible
//                            repeat: true
//                            interval: 2000
//                            triggeredOnStart: true//第一次先主动触发一次onTriggered
//                            onTriggered: {
//                                console.log("**one  time***")
//                                dh.restart()
//                                mok.width=Math.random()*mok.height*1.7+mok.height*1.5

//                            }
//                        }
//                        NumberAnimation {
//                            id:dh
//                            target: closeimg
//                            running: messsagebox2.visible
//                            property: "rotation"
//                            from:0
//                            to:360
//                            loops:1/*AnimatedSprite.Infinite*/
//                            duration: 500
//                            easing.type: Easing.InOutQuad
//                        }
//                    }
//                }
//                Rectangle{width: parent.width*0.75;height: 2;color: "#27AE61"}

//                //内容
//                Text{
//                    id: txt
//                    text: subtext
//                    font.pixelSize: 16
//                    font.bold: true
//                    //                    verticalAlignment: Text.AlignVCenter
//                    //                    horizontalAlignment: Text.AlignHCenter
//                    color: "#FAFCF7"
//                    width: flck.width
//                    wrapMode: Text.WrapAnywhere
//                    textFormat: Text.RichText
//                }

//            }

//        }

//        //确定按钮
//        Button{
//            id:mok
//            //居中
//            x:pp.width/2 -width/2
//            anchors.top: flck.bottom
//            width: height*1.5

//            height:60
//            text: "确定"
//            //Material.background:"#35C37F"
//            //Material.foreground:"#FAFCF7"
//            onClicked: {
//                messsagebox2.close();
//            }
//            Behavior on width {
//                NumberAnimation{ duration: 2000; easing.type: Easing.OutInBounce}
//            }


//        }



//        layer.enabled: true
//        layer.effect: DropShadow {
//            transparentBorder: true//绘制边框阴影
//            color: "#80000000";
//            radius: 30.0;
//            id:drop;

//            //cached: true;
//            horizontalOffset: 0;
//            verticalOffset: 0;
//            samples: 16;
//            smooth: true;
//        }
//    }
//    function msg(title , txt)
//    {
//        subtitle = title;
//        subtext = txt;
//        messsagebox2.open();
//    }



//}

// Dialog {
//     visible: true
//     title: "Blue sky dialog"
//     modality: Qt.WindowModal;
//     contentItem: Rectangle {
//         color: "lightskyblue"
//         implicitWidth: 400
//         implicitHeight: 100
//         Text {
//             text: "Hello blue sky!"
//             color: "navy"
//             anchors.centerIn: parent
//         }
//     }
// }
