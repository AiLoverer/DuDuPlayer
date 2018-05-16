import QtQuick 2.5

Rectangle {
	id: btn;
	property color borderColor: "#eeeeee";
	//property alias   borderWidth: btn.border.width;
	property color textColor : "#ffffff";
	property color disabledBorderColor : "#666666";
	property color disabledTextColor : "#666666";
	property color normalColor : "transparent";
	property color disabledColor : "transparent";
	property color pressedColor : "#ff9400";
	property alias text: txt.text;
	property alias textSize: txt.font.pixelSize;
	property bool selected: false;
	property alias iconSource: icon.source;
	//property color
	width: 100
	height: 62

	signal pressed();
	signal released();
	signal canceled();
	signal clicked();

	color: enabled ? (selected ? pressedColor : normalColor) : disabledColor;
	radius: 8;
	border.width: 1;
	border.color: enabled ? borderColor : disabledBorderColor;

    MouseArea {
		anchors.fill: parent;
        visible: btn.enabled;
		onPressed: {
			parent.color = pressedColor;
			btn.pressed();
		}

		onReleased: {
			refresh();
			btn.released();
		}

		onCanceled: {
			refresh();
			btn.canceled();
		}

		onClicked: {
			refresh();
			btn.clicked();
		}
	}

	Text {
		id: txt;
		anchors.fill: parent;
		verticalAlignment: Text.AlignVCenter;
		horizontalAlignment: Text.AlignHCenter;
		anchors.verticalCenter: parent.verticalCenter;
        font.pixelSize: 40;
		font.family: "Simhei";
		color: btn.enabled ? textColor : disabledTextColor;
	}

	Image {
		id: icon;
		source: "";
		anchors.centerIn: parent;
	}

	function refresh() {
		color = enabled ? (selected ? pressedColor : normalColor) : disabledColor;
	}

	onSelectedChanged: {
		refresh();
	}
}
