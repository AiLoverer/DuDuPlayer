import QtQuick 2.5

Rectangle {
	width: 1280;
	height: 400;
	color: "#151723";

	signal keyClicked(int keycode, string txt);
    property string mImageDir: "qrc:/images/";

	property bool mIsFull: false; // true: 全角, false: 半角
	property bool mIsShowExtended: false;

	ListModel {
		id: modelRow0;
		ListElement {w: 94; h: 78; txt: "1"; e: true; s: false; keycode: Qt.Key_1; iconSrc: "";}
		ListElement {w: 94; h: 78; txt: "2"; e: true; s: false; keycode: Qt.Key_2; iconSrc: "";}
		ListElement {w: 94; h: 78; txt: "3"; e: true; s: false; keycode: Qt.Key_3; iconSrc: "";}
		ListElement {w: 94; h: 78; txt: "4"; e: true; s: false; keycode: Qt.Key_4; iconSrc: "";}
		ListElement {w: 94; h: 78; txt: "5"; e: true; s: false; keycode: Qt.Key_5; iconSrc: "";}
		ListElement {w: 94; h: 78; txt: "6"; e: true; s: false; keycode: Qt.Key_6; iconSrc: "";}
		ListElement {w: 94; h: 78; txt: "7"; e: true; s: false; keycode: Qt.Key_7; iconSrc: "";}
		ListElement {w: 94; h: 78; txt: "8"; e: true; s: false; keycode: Qt.Key_8; iconSrc: "";}
		ListElement {w: 94; h: 78; txt: "9"; e: true; s: false; keycode: Qt.Key_9; iconSrc: "";}
		ListElement {w: 94; h: 78; txt: "0"; e: true; s: false; keycode: Qt.Key_0; iconSrc: "";}
	}

	ListModel {
		id: modelRow1;
		ListElement {w: 94; h: 78; txt: "-"; e: true; s: false; keycode: Qt.Key_Plus; iconSrc: "";}
		ListElement {w: 94; h: 78; txt: "/"; e: true; s: false; keycode: Qt.Key_Slash; iconSrc: "";}
		ListElement {w: 94; h: 78; txt: ":"; e: true; s: false; keycode: Qt.Key_Colon; iconSrc: "";}
		ListElement {w: 94; h: 78; txt: ";"; e: true; s: false; keycode: Qt.Key_Semicolon; iconSrc: "";}
		ListElement {w: 94; h: 78; txt: "("; e: true; s: false; keycode: Qt.Key_BracketLeft; iconSrc: "";}
		ListElement {w: 94; h: 78; txt: ")"; e: true; s: false; keycode: Qt.Key_BracketRight; iconSrc: "";}
		ListElement {w: 94; h: 78; txt: "¥"; e: true; s: false; keycode: Qt.Key_Dollar; iconSrc: "";}
		ListElement {w: 94; h: 78; txt: "“"; e: true; s: false; keycode: Qt.Key_QuoteLeft; iconSrc: "";}
		ListElement {w: 94; h: 78; txt: "”"; e: true; s: false; keycode: Qt.Key_QuoteLeft; iconSrc: "";}
	}

	ListModel {
		id: modelRow2;
		ListElement {w: 94; h: 78; txt: "#+="; e: true; s: false; keycode: Qt.Key_Shift; iconSrc: "";}
		ListElement {w: 94; h: 78; txt: "。"; e: true; s: false; keycode: Qt.Key_Period; iconSrc: "";}
		ListElement {w: 94; h: 78; txt: "，"; e: true; s: false; keycode: Qt.Key_Comma; iconSrc: "";}
		ListElement {w: 94; h: 78; txt: "、"; e: true; s: false; keycode: Qt.Key_Comma; iconSrc: "";}
		ListElement {w: 94; h: 78; txt: "？"; e: true; s: false; keycode: Qt.Key_Question; iconSrc: "";}
		ListElement {w: 94; h: 78; txt: "！"; e: true; s: false; keycode: Qt.Key_Exclam; iconSrc: "";}
		ListElement {w: 94; h: 78; txt: "@"; e: true; s: false; keycode: Qt.Key_At; iconSrc: "";}
		ListElement {w: 94; h: 78; txt: "."; e: true; s: false; keycode: Qt.Key_Period; iconSrc: "";}
		//ListElement {w: 202; h: 78; e: true; s: false; txt: ""; keycode: Qt.Key_Backspace; iconSrc: "../../resource/images/keyboard/btn-delete.png";}
        ListElement {w: 202; h: 78; e: true; s: false; txt: ""; keycode: Qt.Key_Backspace; iconSrc: "qrc:/images/btn-delete.png";}
	}

	ListModel {
		id: modelRow3;
//		ListElement {w: 148; h: 78; e: true; s: false; txt: ""; keycode: Qt.Key_Control; iconSrc: "../../resource/images/keyboard/icon-net.png";}
        ListElement {w: 148; h: 78; e: true; s: false; txt: ""; keycode: Qt.Key_Control; iconSrc: "qrc:/images/icon-net.png";}
		ListElement {w: 148; h: 78; e: true; s: false; txt: "ABC"; keycode: Qt.Key_Alt; iconSrc: "";}
		ListElement {w: 472; h: 78; e: true; s: false; txt: "Space"; keycode: Qt.Key_Space; iconSrc: "";}
		ListElement {w: 258; h: 78; e: true; s: false; txt: "Enter"; keycode: Qt.Key_Enter; iconSrc: "";}
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

	function _keyClicked(key, txt) {
		var processed = false;
		switch(key) {
		case Qt.Key_Shift:
			mIsShowExtended = !mIsShowExtended;
			processed = true;
			break;
		}

		if(!processed) {
			keyClicked(key, txt);
		}
	}

	function refresh() {
		var symbolHalf_Base_Row0 = ["1", "2", "3", "4", "5", "6", "7", "8", "9", "0"];
		var symbolHalf_Base_Row1 = ["-", "/", ":", ";", "(", ")", "¥", "&", "\""];
		var symbolHalf_Base_Row2 = ["#+=", ".", ",", "?", "!", "'", "@", "…", ""];
		var symbolHalf_Ext_Row0 = ["[", "]", "{", "}", "#", "%", "^", "*", "+", "="];
		var symbolHalf_Ext_Row1 = ["_", "\\", "|", "~", "<", ">", "$", "€", "£"];
		var symbolHalf_Ext_Row2 = ["123", ".", ",", "?", "!", "'", "•", "‥", ""];

		var symbolFull_Base_Row0 = ["１", "２", "３", "４", "５", "６", "７", "８", "９", "０"];
		var symbolFull_Base_Row1 = ["－", "／", "：", "；", "（", "）", "¥", "“", "”"];
		var symbolFull_Base_Row2 = ["#+=", "。", "，", "、", "？", "！", "＠", "·", ""];
		var symbolFull_Ext_Row0 = ["【", "】", "｛", "｝", "＃", "%", "∧", "·", "＋", "＝"];
		var symbolFull_Ext_Row1 = ["＿", "￣", "＼", "｜", "～", "《", "》", "$", "＆"];
		var symbolFull_Ext_Row2 = ["123", "…", "，", "？", "！", "‘", "’", ".", ""];

		var models = [modelRow0, modelRow1, modelRow2];
		var symbolHalf_Base = [symbolHalf_Base_Row0, symbolHalf_Base_Row1, symbolHalf_Base_Row2];
		var symbolHalf_Ext = [symbolHalf_Ext_Row0, symbolHalf_Ext_Row1, symbolHalf_Ext_Row2];
		var symbolFull_Base = [symbolFull_Base_Row0, symbolFull_Base_Row1, symbolFull_Base_Row2];
		var symbolFull_Ext = [symbolFull_Ext_Row0, symbolFull_Ext_Row1, symbolFull_Ext_Row2];
		var symbols = null;
		if(mIsFull && !mIsShowExtended)
			symbols = symbolFull_Base;
		else if(mIsFull && mIsShowExtended)
			symbols = symbolFull_Ext;
		else if(!mIsFull && !mIsShowExtended)
			symbols = symbolHalf_Base;
		else
			symbols = symbolHalf_Ext;
		for(var i in models) {
			for(var j in symbols[i]) {
				models[i].get(j).txt = symbols[i][j];
			}
		}
	}
    function setKeyEnable(row, col, enable) {
        var models=[modelRow0, modelRow1, modelRow2, modelRow3];
        models[row].get(col).e = enable;
    }
    function setOKKeyStatus(enable) {
        setKeyEnable(3, 3, enable);
    }
	onMIsFullChanged: {
		refresh();
	}

	onMIsShowExtendedChanged: {
		refresh();
	}

	Component.onCompleted: {
        mIsFull = false;
		refresh();
	}
}
