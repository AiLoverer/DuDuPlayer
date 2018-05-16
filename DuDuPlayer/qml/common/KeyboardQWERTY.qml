import QtQuick 2.5

Rectangle {
    width: 1280;
	height: 400;
	color: "#151723";
	property bool capsLocked: false;

	signal keyClicked(int keycode, string txt);

	ListModel {
		id: modelRow0;
        ListElement {w: 94; h: 78; txt: "Q"; e: true; s: false; keycode: Qt.Key_Q; iconSrc: "";}
        ListElement {w: 94; h: 78; txt: "W"; e: true; s: false; keycode: Qt.Key_W; iconSrc: "";}
        ListElement {w: 94; h: 78; txt: "E"; e: true; s: false; keycode: Qt.Key_E; iconSrc: "";}
        ListElement {w: 94; h: 78; txt: "R"; e: true; s: false; keycode: Qt.Key_R; iconSrc: "";}
        ListElement {w: 94; h: 78; txt: "T"; e: true; s: false; keycode: Qt.Key_T; iconSrc: "";}
        ListElement {w: 94; h: 78; txt: "Y"; e: true; s: false; keycode: Qt.Key_Y; iconSrc: "";}
        ListElement {w: 94; h: 78; txt: "U"; e: true; s: false; keycode: Qt.Key_U; iconSrc: "";}
        ListElement {w: 94; h: 78; txt: "I"; e: true; s: false; keycode: Qt.Key_I; iconSrc: "";}
        ListElement {w: 94; h: 78; txt: "O"; e: true; s: false; keycode: Qt.Key_O; iconSrc: "";}
        ListElement {w: 94; h: 78; txt: "P"; e: true; s: false; keycode: Qt.Key_P; iconSrc: "";}
	}
	ListModel {
		id: modelRow1;
        ListElement {w: 94; h: 78; txt: "A"; e: true; s: false; keycode: Qt.Key_A; iconSrc: "";}
        ListElement {w: 94; h: 78; txt: "S"; e: true; s: false; keycode: Qt.Key_S; iconSrc: "";}
        ListElement {w: 94; h: 78; txt: "D"; e: true; s: false; keycode: Qt.Key_D; iconSrc: "";}
        ListElement {w: 94; h: 78; txt: "F"; e: true; s: false; keycode: Qt.Key_F; iconSrc: "";}
        ListElement {w: 94; h: 78; txt: "G"; e: true; s: false; keycode: Qt.Key_G; iconSrc: "";}
        ListElement {w: 94; h: 78; txt: "H"; e: true; s: false; keycode: Qt.Key_H; iconSrc: "";}
        ListElement {w: 94; h: 78; txt: "J"; e: true; s: false; keycode: Qt.Key_J; iconSrc: "";}
        ListElement {w: 94; h: 78; txt: "K"; e: true; s: false; keycode: Qt.Key_K; iconSrc: "";}
        ListElement {w: 94; h: 78; txt: "L"; e: true; s: false; keycode: Qt.Key_L; iconSrc: "";}
	}
	ListModel {
		id: modelRow2;
//		ListElement {w: 94; h: 78; e: true; s: false; txt: ""; keycode: Qt.Key_CapsLock; iconSrc: "../../resource/images/keyboard/icon-up.png";}
        ListElement {w: 94; h: 78; e: true; s: false; txt: ""; keycode: Qt.Key_CapsLock; iconSrc: "qrc:/images/icon-up.png";}
        ListElement {w: 94;  h: 78; e: true; s: false; txt: "Z"; keycode: Qt.Key_Z; iconSrc: "";}
        ListElement {w: 94;  h: 78; e: true; s: false; txt: "X"; keycode: Qt.Key_X; iconSrc: "";}
        ListElement {w: 94;  h: 78; e: true; s: false; txt: "C"; keycode: Qt.Key_C; iconSrc: "";}
        ListElement {w: 94;  h: 78; e: true; s: false; txt: "V"; keycode: Qt.Key_V; iconSrc: "";}
        ListElement {w: 94;  h: 78; e: true; s: false; txt: "B"; keycode: Qt.Key_B; iconSrc: "";}
        ListElement {w: 94;  h: 78; e: true; s: false; txt: "N"; keycode: Qt.Key_N; iconSrc: "";}
        ListElement {w: 94;  h: 78; e: true; s: false; txt: "M"; keycode: Qt.Key_M; iconSrc: "";}
//		ListElement {w: 202; h: 78; e: true; s: false; txt: ""; keycode: Qt.Key_Backspace; iconSrc: "../../resource/images/keyboard/btn-delete.png";}
        ListElement {w: 202; h: 78; e: true; s: false; txt: ""; keycode: Qt.Key_Backspace; iconSrc: "qrc:/images/btn-delete.png";}
	}
	ListModel {
		id: modelRow3;
//		ListElement {w: 148; h: 78; e: true; s: false; txt: ""; keycode: Qt.Key_Control; iconSrc: "../../resource/images/keyboard/icon-net.png";}
        ListElement {w: 148; h: 78; e: true; s: false; txt: ""; keycode: Qt.Key_Control; iconSrc: "qrc:/images/icon-net.png";}
		ListElement {w: 148; h: 78; e: true; s: false; txt: "\".,123"; keycode: Qt.Key_Alt; iconSrc: "";}
		ListElement {w: 472; h: 78; e: true; s: false; txt: "Space"; keycode: Qt.Key_Space; iconSrc: "";}
		ListElement {w: 258; h: 78; e: true; s: false; txt: "OK"; keycode: Qt.Key_Enter; iconSrc: "";}
	}

	Component {
		id: keyboardBtn;
		ColorButton {
			width: w;
			height: h;
			text: txt;
			enabled: e;
			selected: s;
			onClicked: _keyClicked(keycode, txt);
			iconSource: iconSrc;
			borderColor: "#aaaaaa";
			normalColor: "#30000000";
		}
	}

	Item {
		y: 100;
        width: 1280;
        height: 360;
		anchors.top: parent.top;
        anchors.topMargin: 16;
		anchors.horizontalCenter: parent.horizontalCenter;

		ListView {
			id: row0;
            width: 1066;
            height: 78;
            spacing: 14;
			interactive: false;
			anchors.top: parent.top;
			anchors.horizontalCenter: parent.horizontalCenter;
			orientation: ListView.Horizontal;
			delegate: keyboardBtn;
			model: modelRow0;
		}
		ListView {
			id: row1;
            width: 958;
            height: 78;
            spacing: 14;
			interactive: false;
			anchors.top: row0.bottom;
            anchors.topMargin: 16;
			anchors.horizontalCenter: parent.horizontalCenter;
			orientation: ListView.Horizontal;
			delegate: keyboardBtn;
			model: modelRow1;
		}
		ListView {
			id: row2;
            width: 1066;
            height: 78;
            spacing: 14;
			anchors.top: row1.bottom;
            anchors.topMargin: 16;
			anchors.horizontalCenter: parent.horizontalCenter;
			orientation: ListView.Horizontal;
			interactive: false;
			delegate: keyboardBtn;
			model: modelRow2;
		}
		ListView {
			id: row3;
            width: 1066;
            height: 78;
            spacing: 14;
			anchors.top: row2.bottom;
            anchors.topMargin: 16;
			interactive: false;
			anchors.horizontalCenter: parent.horizontalCenter;
			orientation: ListView.Horizontal;
			delegate: keyboardBtn;
			model: modelRow3;
		}
	}

	function refresh() {
		var row0TxtUpper=["Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P"];
		var row0TxtLower=["q", "w", "e", "r", "t", "y", "u", "i", "o", "p"];
		var row1TxtUpper=["A", "S", "D", "F", "G", "H", "J", "K", "L"];
		var row1TxtLower=["a", "s", "d", "f", "g", "h", "j", "k", "l"];
		var row2TxtUpper=["", "Z", "X", "C", "V", "B", "N", "M", ""];
		var row2TxtLower=["", "z", "x", "c", "v", "b", "n", "m", ""];
		var models=[modelRow0, modelRow1, modelRow2];
		var upperModelTxt = [row0TxtUpper, row1TxtUpper, row2TxtUpper];
		var lowerModelTxt = [row0TxtLower, row1TxtLower, row2TxtLower];
		var i=0,j=0;
		var txtModels = capsLocked ? upperModelTxt : lowerModelTxt;
		//var txtModel = null;

		modelRow2.get(0).s = capsLocked;
		for(i=0; i< models.length;++i) {
			for(j=0; j < models[i].count; ++j) {
				models[i].get(j).txt = txtModels[i][j];
			}
		}
	}

	function _keyClicked(keycode, txt) {
		switch(keycode) {
		case Qt.Key_CapsLock:
			capsLocked = !capsLocked;
			refresh();
			break;
		}

		if(keycode >= 'A'.charCodeAt() && keycode <= 'Z'.charCodeAt()) {
			if(!capsLocked) {
				keycode -= 'A'.charCodeAt() - 'a'.charCodeAt();
			}
		}

		keyClicked(keycode, txt);
        //console.log("keycode: " + keycode);
	}

	function setKeyCaption(row, col, caption) {
		var models=[modelRow0, modelRow1, modelRow2, modelRow3];
		models[row].get(col).txt = caption;
	}

	function setInputStatus(status) {
		setKeyCaption(3, 2, status);
	}

    function setKeyEnable(row, col, enable) {
        var models=[modelRow0, modelRow1, modelRow2, modelRow3];
        models[row].get(col).e = enable;
    }
    function setOKKeyStatus(enable) {
        setKeyEnable(3, 3, enable);
    }

	Component.onCompleted: {
		refresh();
	}
}
