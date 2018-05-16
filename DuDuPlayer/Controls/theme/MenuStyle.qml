import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Controls 1.2
import QtQuick.Controls.Private 1.0

Style {
    id:styleRoot
    property color __backgroundColor:"#f2f2f2"
    property color __borderColor:"#a0a0a0"
    property color __selectedBackgroundColor:"#ff00a0e9"
    padding {top: 1;bottom: 1;left: 1;right: 1;}
    property int submenuOverlap: 1
    property int submenuPopupDelay: 200
    function formatMnemonic(text, underline) {
        return underline ? StyleHelpers.stylizeMnemonics(text) : StyleHelpers.removeMnemonics(text)
    }
    property Component frame: Rectangle {
        color: styleRoot.__backgroundColor
        border { width: 1; color: styleRoot.__borderColor }
        anchors.topMargin: 2
    }
    property alias itemDelegate:internalMenuItem
    MenuItemSubControls {
        id: internalMenuItem
        background: Rectangle {
            visible: styleData.selected && styleData.enabled
            gradient: Gradient {
                id: selectedGradient
                GradientStop { color: Qt.lighter(__selectedBackgroundColor, 1.3); position: -0.2 }
                GradientStop { color: __selectedBackgroundColor; position: 1.4 }
            }
            border.width: 1
            border.color: Qt.darker(__selectedBackgroundColor, 1)
        }
        label: Text {
            text: formatMnemonic(styleData.text, styleData.underlineMnemonic)
            color: __currentTextColor
            font.pixelSize: __labelFontPixelSize
            renderType: Text.NativeRendering
            verticalAlignment: Text.AlignVCenter
        }
        submenuIndicator: Text {
            text: __mirrored ? "\u25c2" : "\u25b8" // BLACK LEFT/RIGHT-POINTING SMALL TRIANGLE
            font.pixelSize: __labelFontPixelSize
            color: __currentTextColor
            style: styleData.selected ? Text.Normal : Text.Raised
            styleColor: Qt.lighter(color, 4)
            renderType: Text.NativeRendering
        }
        shortcut: Text {
            text: styleData.shortcut
            font.pixelSize: __labelFontPixelSize * 0.9
            color: __currentTextColor
            renderType: Text.NativeRendering
        }
        checkmarkIndicator: Loader {
            sourceComponent: nonExclusiveCheckMark
            Component {
                id: nonExclusiveCheckMark
                Rectangle {
                    color: (styleData.selected && styleData.enabled)?"transparent":"#ddd"
                    anchors.fill: parent
                    Canvas {
                        visible: styleData.checked
                        anchors.centerIn: parent
                        width: 16
                        height: 16
                        onPaint: {
                            var ctx = getContext("2d");
                            ctx.lineWidth = 2;
                            ctx.strokeStyle = "#333";
                            ctx.moveTo(2,10);
                            ctx.lineTo(8,16);
                            ctx.moveTo(8,16);
                            ctx.lineTo(16,2);
                            ctx.stroke();
                        }
                    }
                }
            }
        }
    }

    property Component separator: Item {
        Rectangle {
            width: parent.width - 2
            height: 1
            x: 1
            anchors.verticalCenter: parent.verticalCenter
            color: "darkgray"
        }
    }
    property string __menuItemType: "menuitem"
    property int __maxPopupHeight: 600
    property color __labelColor: "#111"
    property color __selectedLabelColor: "white"
    property color __disabledLabelColor: "gray"
    readonly property bool __mirrored: Qt.application.layoutDirection === Qt.RightToLeft
    readonly property real __labelFontPixelSize: TextSingleton.font.pixelSize
    property int __leftLabelMargin: 28
    property int __rightLabelMargin: 12
    property int __minRightLabelSpacing: 28
    property Component __scrollerStyle: null
    property Component menuItemPanel: Item {
        id: panel
        property QtObject __styleData: styleData
        property color currentTextColor: !styleData.enabled ? __disabledLabelColor :
                                         styleData.selected ? __selectedLabelColor : __labelColor
        implicitWidth: Math.max((parent ? parent.width : 0),
                                Math.round(__leftLabelMargin + (labelLoader.width>100?labelLoader.width:100) + __rightLabelMargin +
                                           (rightIndicatorLoader.active ? __minRightLabelSpacing + rightIndicatorLoader.width : 0)))
        implicitHeight:Math.round(styleData.isSeparator ? __labelFontPixelSize / 2 :
                      !!styleData.scrollerDirection ? __labelFontPixelSize * 0.75 : labelLoader.height + 12)
        Loader {
            property alias styleData: panel.__styleData
            property alias __currentTextColor: panel.currentTextColor
            anchors.fill: parent
            sourceComponent: itemDelegate.background
        }

        Loader {
            property alias styleData: panel.__styleData
            property alias __currentTextColor: panel.currentTextColor
            anchors.fill: parent
            sourceComponent: separator
            active: styleData.type === MenuItemType.Separator
        }

        Loader {
            property alias styleData: panel.__styleData
            property alias __currentTextColor: panel.currentTextColor
            active: __menuItemType === "menuitem"
            height: parent.height
            width: 24
            sourceComponent: itemDelegate.checkmarkIndicator
        }
        Loader {
            id: labelLoader
            readonly property real offset: __menuItemType === "menuitem" ? __leftLabelMargin : 6
            property alias styleData: panel.__styleData
            property alias __currentTextColor: panel.currentTextColor
            x: __mirrored ? parent.width - width - offset : offset
            y: 6
            active: styleData.type !== MenuItemType.Separator
            sourceComponent: itemDelegate.label
            baselineOffset: item ? item.baselineOffset : 0.0
        }
        Loader {
            id: rightIndicatorLoader
            property alias styleData: panel.__styleData
            property alias __currentTextColor: panel.currentTextColor
            active: styleData.type === MenuItemType.Menu || styleData.shortcut !== ""
            sourceComponent: styleData.type === MenuItemType.Menu ? itemDelegate.submenuIndicator : itemDelegate.shortcut
            LayoutMirroring.enabled: __mirrored
            baselineOffset: item ? item.baselineOffset : 0.0
            anchors {
                right: parent.right
                rightMargin: 6
                baseline: !styleData.isSubmenu ? labelLoader.baseline : undefined
            }
        }
    }
}
