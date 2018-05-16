import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Controls.Private 1.0
import QtQuick.Controls.Styles 1.2

ProgressBarStyle {
    background: Rectangle {
        radius: 2
        gradient: Gradient {
            GradientStop {color: "#bbb" ; position: 0}
            GradientStop {color: "#eee" ; position: 0.1}
            GradientStop {color: "#eee" ; position: 1}
        }
        border.color: "gray"
        border.width: 1
        implicitWidth: 200
        implicitHeight: 24
    }
}
