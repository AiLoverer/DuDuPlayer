import QtQuick 2.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3
/*******************************************************************************************************
* tabviewstyle
* Common control style
********************************************************************************************************/
TabViewStyle {
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
