import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import QtGraphicalEffects 1.0//需要安装QtGraphicalEffects模块
import QtQuick.Controls.Styles 1.2
import QtQuick.Controls.Private 1.0

Item {
    anchors.fill: parent
    implicitWidth: 480
    implicitHeight: 320
    RectangularGlow {
        id: fusswin_effect
        anchors.fill: fusswin_layout
        glowRadius: 3
        spread: 0.05
        color: "#969696"
        cornerRadius:5
    }
    Rectangle{
        id: fusswin_layout
        anchors.fill: parent
        anchors.margins: fuss_win.shadowThick
        color: "#f2f2f2"
        border.color: "#a0a0a0"
        border.width: 1
        ColumnLayout
        {
            spacing: 0
            anchors.fill: parent
            Item {
                id: fusswin_titleBar
                height: 30
                Layout.fillWidth: true
                RowLayout{
                    spacing: 0
                    anchors.fill: parent
                    Item {
                        id: fusswin_logItem
                        Layout.preferredWidth: 20
                        Layout.fillHeight: true
                        Image {
                            id: fusswin_logIamge
                            objectName: "fusswin_logIamge"
                            anchors.verticalCenter: parent.verticalCenter
                            height: 16
                            width:16
                            source: ""
                        }
                    }
                    Item{
                        id:fusswin_titleItem
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        Text{
                            anchors.verticalCenter: parent.verticalCenter
                            text:fuss_win.title
                            color: "#202020"
                        }
                    }
                    Item{
                        id:fusswin_buttonsItem
                        Layout.preferredWidth: (120-(fuss_win.showTitleMenu?0:30)-(fuss_win.showMaxButton?0:30))
                        Layout.fillHeight: true
                        property string transparentBlueColor: "#0000a0e9"
                        property string blueColor: "#ff00a0e9"
                        RowLayout{
                            anchors.fill: parent
                            spacing: 0
                            Button{
                                id:fusswin_menuButton
                                objectName: "fusswin_menuButton"
                                text: qsTr("")
                                scale: 1
                                visible: fuss_win.showTitleMenu
                                anchors.top:parent.top
                                style: ButtonStyle{
                                    background: Rectangle {
                                        implicitWidth: 30
                                        implicitHeight: 24
                                        color: (control.hovered||control.pressed) ? "#ff00a0e9" : "#0000a0e9";
                                        Text{
                                            anchors.centerIn: parent
                                            width: 10
                                            height: 10
                                            text:"▼"
                                            color: (control.hovered||control.pressed) ? "white" : "#AAA";
                                        }
                                    }
                                }
                            }

                            Rectangle{
                                id:fusswin_miniButton
                                width: 30
                                height: 24
                                anchors.top:parent.top
                                color: "#0000a0e9"
                                PropertyAnimation{
                                    id:colorAnimation_enterMiniButton;
                                    target: fusswin_miniButton;
                                    property: "color";
                                    from:fusswin_buttonsItem.transparentBlueColor;
                                    to: fusswin_buttonsItem.blueColor;
                                    duration: 200
                                }
                                PropertyAnimation{
                                    id:fusswincolorAnimation_leaveMiniButton;
                                    target: fusswin_miniButton;
                                    property: "color";
                                    from:fusswin_buttonsItem.blueColor;
                                    to: fusswin_buttonsItem.transparentBlueColor;
                                    duration: 200
                                }
                                Rectangle {
                                    id:fusswin_miniButtonCenter
                                    width:12
                                    height:2
                                    anchors.centerIn: parent
                                    anchors.verticalCenterOffset: 4
                                    color: "#AAA"
                                }
                                MouseArea{
                                    anchors.fill: parent
                                    hoverEnabled: true
                                    onEntered:{
                                        colorAnimation_enterMiniButton.start();
                                        fusswin_miniButtonCenter.color="white";
                                    }
                                    onExited: {
                                        fusswincolorAnimation_leaveMiniButton.start();
                                        fusswin_miniButtonCenter.color="#AAA";
                                    }
                                    onClicked:{
                                        fuss_win.showMinimized();
                                    }
                                }
                            }
                            Rectangle{
                                id:fusswin_maxButton
                                width: 30
                                height: 24
                                visible: fuss_win.showMaxButton
                                anchors.top:parent.top
                                color: "#0000a0e9"
                                PropertyAnimation{
                                    id:colorAnimation_enterMaxButton;
                                    target: fusswin_maxButton;
                                    property: "color";
                                    from:fusswin_buttonsItem.transparentBlueColor;
                                    to: fusswin_buttonsItem.blueColor;
                                    duration: 200
                                }
                                PropertyAnimation{
                                    id:colorAnimation_leaveMaxButton;
                                    target: fusswin_maxButton;
                                    property: "color";
                                    from:fusswin_buttonsItem.blueColor;
                                    to: fusswin_buttonsItem.transparentBlueColor;
                                    duration: 200
                                }
                                Rectangle {
                                    id:maxButtonMaxCenter
                                    width:10
                                    height:10
                                    anchors.centerIn: parent
                                    anchors.verticalCenterOffset: -2
                                    anchors.horizontalCenterOffset: 2
                                    visible:fuss_win.shadowThick===0//最大化时才显示
                                    color: "transparent"
                                    border.color: "#AAA"
                                    border.width: 2
                                }
                                Rectangle {
                                    id:maxButtonnNormalCenter
                                    width:10
                                    height:10
                                    anchors.centerIn: parent
                                    anchors.verticalCenterOffset: (fuss_win.shadowThick>0?0:2)
                                    anchors.horizontalCenterOffset: (fuss_win.shadowThick>0?0:-2)
                                    color:fusswin_layout.color
                                    border.color: "#AAA"
                                    border.width: 2
                                }
                                MouseArea{
                                    anchors.fill: parent
                                    hoverEnabled: true
                                    onEntered:{
                                        colorAnimation_enterMaxButton.start();
                                        maxButtonnNormalCenter.border.color = "white";
                                        maxButtonMaxCenter.border.color = "white";
                                        maxButtonnNormalCenter.color = fusswin_buttonsItem.blueColor;
                                    }
                                    onExited: {
                                        colorAnimation_leaveMaxButton.start();
                                        maxButtonnNormalCenter.border.color = "#AAA";
                                        maxButtonMaxCenter.border.color = "#AAA";
                                        maxButtonnNormalCenter.color = fusswin_layout.color;
                                    }
                                    onClicked:{
                                        if(fuss_win.shadowThick>0)
                                        {
                                            fuss_win.shadowThick = 0;
                                            fuss_win.showMaximized();
                                        }
                                        else
                                        {
                                            fuss_win.shadowThick = 5;
                                            fuss_win.showNormal();
                                        }
                                    }
                                }
                            }
                            Rectangle{
                                id:fusswin_closeButton
                                width: 30
                                height: 24
                                anchors.top:parent.top
                                color: "#00f53a48"
                                PropertyAnimation{
                                    id:colorAnimation_enterCloseButton;
                                    target: fusswin_closeButton;
                                    property: "color";
                                    from:"#00f53a48";
                                    to: "#fff53a48";
                                    duration: 200
                                }
                                PropertyAnimation{
                                    id:colorAnimation_leaveCloseButton;
                                    target: fusswin_closeButton;
                                    property: "color";
                                    from:"#fff53a48";
                                    to: "#00f53a48";
                                    duration: 200
                                }
                                Rectangle{
                                    id:closeButtonCenter1
                                    height: 14
                                    width: 2
                                    anchors.centerIn: parent
                                    color: "#AAA"
                                    rotation: 45
                                }
                                Rectangle{
                                    id:closeButtonCenter2
                                    height: 14
                                    width: 2
                                    anchors.centerIn: parent
                                    color: "#AAA"
                                    rotation: -45
                                }
                                MouseArea{
                                    anchors.fill: parent
                                    hoverEnabled: true
                                    onEntered:{
                                        colorAnimation_enterCloseButton.start();
                                        closeButtonCenter1.color = "white";
                                        closeButtonCenter2.color = "white";
                                    }
                                    onExited: {
                                        colorAnimation_leaveCloseButton.start();
                                        closeButtonCenter1.color = "#AAA";
                                        closeButtonCenter2.color = "#AAA";
                                    }
                                    onClicked:{
                                        fuss_win.close();
                                    }
                                }
                            }
                        }
                    }
                }
            }
            Rectangle{
                id:titleSplitLine
                height: 1
                Layout.fillWidth: true
                color: fusswin_layout.border.color
            }

            Item {
                Layout.fillHeight: true
                Layout.fillWidth: true
                Item
                {
                    id: fusswin_clientContent
                    objectName: "fusswin_clientContent"
                    anchors.fill: parent
                }
            }
        }
    }
}

