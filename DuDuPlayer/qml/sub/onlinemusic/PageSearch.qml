import QtQuick 2.5
import "qrc:/qml/common" as Common
Rectangle {
    id: root;

    property color pressedColor : "#ff9400";
    property color normalColor : "transparent";

    anchors.fill: parent;
    width: 1280;
    height: 522;
    color: "transparent";
    clip: true;

    // static property
    property int sInputMethod_US_EN:		0;
    property int sInputMethod_ZH_CN:        1;
    property int sInputMethod_CityList:     2;
    //property int sInputMethod_Symbol:       3;
    property int sInputMethod_Count:        3;

    // writable property
    property int mInputMethod: sInputMethod_CityList;

    // signals
    signal inputCompleted(string text);

    onInputCompleted:
    {
       //console.log("onInputCompleted ： " + text);
        JCNet_AppOnlineMusic.searchMusicByKeyWords(text);
    }

    MouseArea {
        anchors.fill: parent;
        onClicked: {}
    }


    // 搜索输入框
    Rectangle{
        id: inputRect;
        color: "transparent";

        anchors.left: parent.left;
        anchors.leftMargin: 90;
        anchors.top: parent.top;
        anchors.topMargin: 24;
        anchors.right: parent.right;
        anchors.rightMargin: 298;
        border.color: Qt.rgba(190/255, 191/255, 195/255, 1.0);
        radius: 10;

        height: 70;


        TextInput {
            id: ti;

            anchors.fill: parent;
            text: qsTr("搜索歌曲名、歌手名、专辑名")
            font.family: "SimHei";
            font.pixelSize: 28;
            color: Qt.rgba( 166/255, 166/255, 169/255, 1.0 );
            maximumLength: 18;
            verticalAlignment: TextInput.AlignVCenter;
            autoScroll: false;

            focus: true;
            onVisibleChanged: {
                if(visible) {
                    focus = true;
                }
            }

            onFocusChanged: {
                if(ti.focus)
                {
                    ti.text = "";
                }
            }
        }
    }
    // 搜索按钮
    Rectangle{
        id: searchRect;
        anchors.left: inputRect.right;
        anchors.leftMargin: 38;
        anchors.top: inputRect.top;
        width: 170;
        height: 70;
        border.color: Qt.rgba(190/255, 191/255, 195/255, 1.0);
        radius: 10;
        color: "transparent";
        Text{
            id: searchTxt;

            color: "white";
            text: qsTr("搜索");
            font.pixelSize: 40;
            font.bold: true;
            anchors.centerIn: parent;

        }
        MouseArea{
            anchors.fill: parent;
            onPressed: {
                searchRect.color = pressedColor;
            }
            onReleased: {
                searchRect.color = normalColor;
            }
            onClicked: {
                //console.log("clicked search button ..." + ti.text);
                inputCompleted(ti.text);
            }
        }
    }
    // 虚拟键盘
    Common.KeyboardQWERTY{
       id: keyboardQwerty;

       z: 100;
       width: 1016
       height: 406;
       anchors.bottom: root.bottom;
       anchors.bottomMargin: 20;
       anchors.left: inputRect.left;
       anchors.top: inputRect.bottom;
       anchors.topMargin: 2;
       anchors.horizontalCenter: parent.horizontalCenter;
       onKeyClicked: {
            onKeyboardClicked(keycode, txt);
        }
    }
    Common.KeyboardSymbol {
        id: keyboardSymbol;
        anchors.top: inputRect.bottom;
        anchors.topMargin: 2;
        visible: false;
        onKeyClicked: {
            onKeyboardClicked(keycode, txt);
        }
    }
    function onKeyboardClicked(key, txt) {
        debug();
        if(isFuncKey(key)) {
            onInputFuncKey(key);
        }else if(isEngChar(key)) {
            onInputEngChar(key);
        } else if(isNumber(key)) {
            onInputSymbol(txt);
        } else{
            onInputSymbol(txt);
        }
    }

    function onInputFuncKey(key) {
        switch(key) {
        case Qt.Key_Backspace:
            ti.remove(ti.cursorPosition-1, ti.cursorPosition);
            if(ti.selectedText.length>0) {
                onSelectedTxtChange();
            }
            break;

        case Qt.Key_Control:
            switchInputMethod();
            break;

        case Qt.Key_Enter:
            onConfirm();
            break;

        case Qt.Key_Alt:
            keyboardQwerty.visible = !keyboardQwerty.visible;
            keyboardSymbol.visible = !keyboardSymbol.visible;
            break;

        case Qt.Key_Space:
            if(keyboardSymbol.mIsFull)
                onInputSymbol("　");
            else
                onInputSymbol(" ");
            break;
        }
    }

    function onInputEngChar(c) {
        ti.insert(ti.cursorPosition, String.fromCharCode(c));
        ti.cursorPosition += 1;
        if(mInputMethod != sInputMethod_US_EN) {
            if(ti.selectedText.length==0) {
                ti.select(ti.cursorPosition-1, ti.cursorPosition);
            } else {
                ti.select(ti.selectionStart, ti.cursorPosition);
            }
        }

        onSelectedTxtChange();
    }

    function onConfirm() {
        if(ti.selectedText.length > 0) {
            ti.deselect();
            onSelectedTxtChange();
        } else {
            inputCompleted(ti.text);
        }
    }

    function onSelectedTxtChange() {
        switch(mInputMethod) {
        case sInputMethod_CityList:
            if(ti.selectedText.length > 0)
                onInputCityList(ti.selectedText);
            break;

        case sInputMethod_ZH_CN:
            onInputSimplifiedChinese(ti.selectedText);
            break;
        }
    }

    function onInputSimplifiedChinese(spell) {
        delayTranslate.restart();
    }

    function onInputCityList(city) {
        //var cities = ChinaCityList.queryByPyFirstChar(city);
        //selectBar.setItems(cities);
    }

    function onInputNumber(n) {
        ti.insert(ti.cursorPosition, String.fromCharCode(n));
        ti.deselect();
    }

    function onInputSymbol(s) {
        //ti.insert(ti.cursorPosition, String.fromCharCode(s));
        ti.insert(ti.cursorPosition, s);
        ti.deselect();
        debug();
    }

    function isFuncKey(key) {
        var keys = [Qt.Key_CapsLock, Qt.Key_Backspace, Qt.Key_Shift, Qt.Key_Control, Qt.Key_Alt, Qt.Key_Enter, Qt.Key_Space];
        for(var i in keys) {
            if(keys[i] === key)
                return true;
        }
        return false;
    }

    function isChar(keycode) {
        return (keycode >= 0x20 && keycode <= 0x7e);
    }

    function isEngChar(keycode) {
        return (keycode >= 'a'.charCodeAt() && keycode <= 'z'.charCodeAt()) || (keycode >= 'A'.charCodeAt() && keycode <= 'Z'.charCodeAt());
    }

    function isNumber(keycode) {
        return keycode >= '0'.charCodeAt() && keycode <= '9'.charCodeAt();
    }

    function updateKeyboardStatus(inputMethod) {
        switch(inputMethod) {
        case sInputMethod_CityList:
        case sInputMethod_ZH_CN:
            keyboardQwerty.setInputStatus("拼音");
            break;

        case sInputMethod_US_EN:
            keyboardQwerty.setInputStatus("English");
            break;
        }
    }

    function switchInputMethod() {
        ++mInputMethod;
        if(mInputMethod === sInputMethod_Count) {
            mInputMethod = sInputMethod_US_EN;
        }

        keyboardSymbol.visible = false;
        keyboardQwerty.visible = true;
        keyboardSymbol.mIsFull = (mInputMethod == sInputMethod_ZH_CN);
        updateKeyboardStatus(mInputMethod);
        //console.log("mInputMethod: " + mInputMethod);
    }

    function debug() {
        //return;
        //console.log("debug info: ");
        //console.log("    cursorPosition: " + ti.cursorPosition);
        //console.log("    selectedText:   " + ti.selectedText);
        //console.log("    selectedLength:   " + ti.selectedText.length);
        //console.log("    selectionStart:   " + ti.selectionStart);
        //console.log("    ");
    }

    Component.onCompleted: {
        console.log("keyboard construedted");
    }

    Timer {
        id: delayTranslate;
        interval: 300;
        onTriggered: {
            var transRet = SougouSpeller.translate(ti.selectedText);
            var jsonArr = JSON.parse(transRet);
            //selectBar.clear();
            for(var i=0; i<jsonArr.length; ++i) {
                //console.log("translated item " + i + " :" + jsonArr[i].txt);
                //selectBar.addItem(jsonArr[i].txt, jsonArr[i].csl);
            }
        }
    }

}

