import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Controls.Private 1.0

Style {
    id: buttonstyle

    /*! The \l {QtQuick.Controls::}{Button} attached to this style. */
    readonly property Button control: __control

    /*! The padding between the background and the label components. */
    padding {
        top: 4
        left: 8
        right:  control.menu !== null ? Math.round(TextSingleton.implicitHeight * 0.5) : 8
        bottom: 4
    }

    /*! This defines the background of the button. */
    property Component background: Item {
        property bool down: control.pressed || (control.checkable && control.checked)
        implicitWidth: Math.round(TextSingleton.implicitHeight * 4.5)
        implicitHeight: Math.max(25, Math.round(TextSingleton.implicitHeight * 1.2))
        Rectangle {
            anchors.fill: parent
            border.width: control.activeFocus ? 2 : 1
            border.color: "#888"
            radius: TextSingleton.implicitHeight * 0.16
            gradient: Gradient {
                GradientStop {
                    position: 0 ;
                    color: {
                        if(control.pressed)
                            return "#f0f0f0";
                        return control.hovered ? "#fff" : "#f0f0f0";
                    }
                }
                GradientStop {
                    position: 1 ;
                    color: {
                        if(control.pressed)
                            return "#c0c0c0";
                        return control.hovered ? "#eee" : "#e0e0e0"
                    }
                }
            }
        }
        Text {
            id: imageItem
            visible: control.menu !== null
            text:"▼"
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: padding.right
            opacity: control.enabled ? 0.6 : 0.5
            color: (control.hovered||control.pressed) ? "#AAA" : "#BBB";
        }
    }

    /*! This defines the label of the button.  */
    property Component label: Item {
        implicitWidth: row.implicitWidth
        implicitHeight: row.implicitHeight
        baselineOffset: row.y + text.y + text.baselineOffset
        Row {
            id: row
            anchors.centerIn: parent
            spacing: 2
            Image {
                source: control.iconSource
                anchors.verticalCenter: parent.verticalCenter
            }
            Text {
                id: text
                renderType: Text.NativeRendering
                anchors.verticalCenter: parent.verticalCenter
                text: control.text
                color: SystemPaletteSingleton.buttonText(control.enabled)
            }
        }
    }

    /*! \internal */
    property Component panel: Item {
        anchors.fill: parent
        implicitWidth: Math.max(labelLoader.implicitWidth + padding.left + padding.right, backgroundLoader.implicitWidth)
        implicitHeight: Math.max(labelLoader.implicitHeight + padding.top + padding.bottom, backgroundLoader.implicitHeight)
        baselineOffset: labelLoader.item ? padding.top + labelLoader.item.baselineOffset : 0

        Loader {
            id: backgroundLoader
            anchors.fill: parent
            sourceComponent: background
        }

        Loader {
            id: labelLoader
            sourceComponent: label
            anchors.fill: parent
            anchors.leftMargin: padding.left
            anchors.topMargin: padding.top
            anchors.rightMargin: padding.right
            anchors.bottomMargin: padding.bottom
        }
    }


}
