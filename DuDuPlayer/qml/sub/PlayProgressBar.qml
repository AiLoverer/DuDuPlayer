import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3

RowLayout {
	//  对外属性
	property int maxVal: 100;
	property int minVal: 0;
    property int curVal:(maxVal+minVal)/2;
	property int oldVal: (maxVal+minVal)/2;
    property bool isTime: false;
	property bool showButton: true;
	property alias showLeftText: leftTextRect.visible;
	property alias showRightText: rightTextRect.visible;
	property color backColor:"transparent";
	property bool showPercent: false;
	property bool isPressed: false;
    property int progressbarHeight: 20;
    property int textFontPointSize: 16;
    property bool bFontBold: true;

	// blue bar use this schema
	/*property color lineColor:"#cc191a1c";
	property color lineSelectedColor:"#cc1597d7";
	property color lineBorderColor: "#333335"
	property color lineSelectedBorderColor: "#31d6f0";
	property color btnColor: "#ff35bff8";
	property color btnBorderColor: "#ffedf1f6";
	property color disabledBackColor:"#0d101e";
	property color disabledLineColor:"#191a1c";
	property color disabledLineSelectedColor:"#757575";
	property color disabledSelectedBorderColor: "gray";
	property color disabledBtnColor: "#35bff8";*/

	//property color lineColor:"#cc191a1c";
	property color lineColor:"#7a7a78";
    property color lineSelectedColor:"white";
	//property color lineBorderColor: "#333335"
	property color lineBorderColor: lineColor;
    property color lineSelectedBorderColor: "white";
    property color btnColor: "white";
	property color btnBorderColor: "#ffedf1f6";
	property color disabledBackColor:"#0d101e";
	property color disabledLineColor:"#191a1c";
	property color disabledLineSelectedColor:"#757575";
	property color disabledSelectedBorderColor: "gray";
	property color disabledBtnColor: "gray";

	// private property
	property int hMouseOffset: 30;

    //  对外信号
	signal progressDataChange();
	signal progressBarPressed();
	signal progressBarReleased();
	signal progressBarCanceled();
    signal progressBarDraged(int position)

    id:progressBar;

	width: 400;
    height: progressbarHeight;
	spacing: progressBtn.width/2;
    Rectangle{//当前值
		id:leftTextRect;
        color:backColor;
        width:isTime===true?60:40;
        height: progressBar.height;
        anchors.right: progressLine.left;
        anchors.verticalCenter: parent.verticalCenter;

        Text {
            id: leftTxt;
            text:getCurText(curVal);
			anchors.verticalCenter: parent.verticalCenter;
			anchors.left: parent.left;
            anchors.leftMargin: isTime&&curVal>=3600 ? -40:0;
            //font.family: Theme.fontFamily;
            font.pixelSize: textFontPointSize;
			color: "white";
            font.bold: bFontBold;
        }

		onVisibleChanged: {
			updateProgress();
		}
    }

	Rectangle{
		id:progressLine;
//		anchors.left: leftTextRect.right;
//		anchors.right: rightTextRect.left;
		anchors.margins: progressBtn.width/2;
		Layout.fillWidth: true;
		Layout.minimumWidth: 50;
		anchors.leftMargin: 30;
		anchors.rightMargin: 30;
		anchors.horizontalCenter: parent.horizontalCenter;
		anchors.verticalCenter: progressBar.verticalCenter;
		//width: progressBar.width- (showLeftText ? leftTextRect.width : 0) - (showRightText ? rightTextRect.width : 0) - progressBtn.width;
		height: showButton ? 4 : 12;
		radius: height/2;
		border.width: 1;
		border.color: lineBorderColor;
		color: progressBar.enabled ? lineColor : disabledLineColor;


		onWidthChanged: {
			//outputDebugInfo();
			updateProgress();
		}

        MouseArea{
//			x:-hMouseOffset;
//			y:-30;
//			width: parent.width + 2*hMouseOffset;
//            height: 60+parent.height;
            width: progressBar.width;
            height: progressBar.hMouseOffset;
            x: 0;
            y: 0;
			visible: progressBar.enabled;

			onPositionChanged: {
				onUserSelect(mouse.x-hMouseOffset);
				if(oldVal != curVal) {
					oldVal = curVal;
					progressBar.progressDataChange();
				} 
			}

			onPressed: {
				console.log("progress pressed");
				isPressed = true;
				onUserSelect(mouse.x-hMouseOffset);
				progressBar.progressBarPressed();
			}

			onReleased: {
				//console.log("progress on Released");
				isPressed = false;
				progressBar.progressBarReleased();
			}

			onCanceled: {
				//console.log("progress canceled");
				isPressed = false;
				progressBar.progressBarReleased();
				progressBar.progressBarCanceled();
			}

			onClicked: {
				//console.log("progress on onClicked");
				onUserSelect(mouse.x-hMouseOffset);
//				progressBar.progressDataChange();
//				progressBar.progressBarReleased();
			}
		}

		Rectangle{//已完成进度
			id:selectLine;
			x:0;
			y:0;
			width:progressBtn.x+progressBtn.width/2;
			height: parent.height;
			radius: parent.radius;
			border.width: 1;
			border.color: progressBar.enabled ? lineSelectedBorderColor: disabledSelectedBorderColor;
			color: progressBar.enabled ? lineSelectedColor : disabledLineSelectedColor;
		}

		Rectangle{//进度条的按钮
			id:progressBtn;
            width:progressbarHeight;
            height: progressbarHeight;
			radius:width/2;
			x:0;
			y:progressLine.height/2-width/2;
			color: "transparent";
			visible: showButton;
			border.width: 3;
			border.color: progressBar.enabled ? btnColor : disabledBtnColor;

			Rectangle {
				x: 9;
				y: 9;

				width: parent.width - x*2;
				height: parent.height - y*2;
				radius: Math.min(width, height)/2;
				color: progressBar.enabled ? btnColor : disabledBtnColor;
				//border.width: 1;
				//border.color: "#0d557f";
			}
		}

		Text {
            font.pixelSize: textFontPointSize;
            //font.family: Theme.fontFamily;
			color: "#ff9400";
			text: Math.floor((curVal-minVal)/(maxVal - minVal)*100) + "%";
			visible: showPercent;
			anchors.horizontalCenter: progressBtn.horizontalCenter;
			anchors.bottom: progressBtn.top;
			anchors.bottomMargin: 5;
            font.bold: bFontBold;
		}
	}

    Rectangle{//最大值
        id:rightTextRect;
        x:progressBar.width-width;
        y:0;
        color:backColor;
        width:isTime===true?60:40;
        height: progressBar.height;
        anchors.left: progressLine.right;
        //anchors.leftMargin: progressBtn.width/2;
		anchors.verticalCenter: progressLine.verticalCenter;
		onVisibleChanged: {
			updateProgress();
		}

        Text {
            id: rightTxt;
			text:getCurText(maxVal);
			anchors.verticalCenter: parent.verticalCenter;
			anchors.right: parent.right;
            anchors.rightMargin: isTime && maxVal>=3600 ? -40:0;
            //font.family: Theme.fontFamily;
            font.pixelSize: textFontPointSize;
			color: "white";
            font.bold: bFontBold;
        }
	}

	onEnabledChanged: {
		refresh();
    }
	
	onCurValChanged: {
		if(curVal > maxVal)
			curVal = maxVal;
		else if(curVal < minVal)
            curVal = minVal;
        updateProgress();
	}

    function getCurText(nSeconds){
        var timeTxt="";

        if(isTime===false)
        {
            timeTxt =   nSeconds;
            return timeTxt;
        }
        else
        {
            var hour    =   Math.floor(nSeconds/3600);
            if(hour!==0)
            {
                if(hour<10)
                {
                    timeTxt =   "0"+hour+":";
                }
                else
                {
                    timeTxt =   hour+":";
                }
            }

            var minute  =   Math.floor((nSeconds%3600)/60);
            if(minute<10)
            {
                minute  =   "0"+minute;
            }
            timeTxt =   timeTxt+minute;

            var second  =   (nSeconds%3600)%60;
            if(second<10)
            {
                second  =   "0"+second;
            }
            timeTxt =   timeTxt+":"+second;

            return  timeTxt;
        }

	}

	function updateProgress() {
		selectLine.width = (maxVal <= minVal) ? 0 : progressLine.width*(curVal-minVal)/(maxVal-minVal);
		progressBtn.x = selectLine.x + selectLine.width - progressBtn.width/2;
        leftTxt.text = getCurText(curVal);
    }

	function refresh() {
		selectLine.color = enabled ? lineSelectedColor : disabledLineSelectedColor;
		//progressBtn.color = progressBar.enabled ? btnColor : disabledBtnColor;
		//progressBtn.border.color= btnBorderColor;
		selectLine.border.color= enabled ? lineSelectedBorderColor: disabledSelectedBorderColor;
	}

	function onUserSelect(mousex) {
		var progress = (minVal >= maxVal) ? 0 : mousex / progressLine.width;
		curVal = progress*(maxVal-minVal)+minVal;
        progressBarDraged(curVal);
		refresh();
	}

	function outputDebugInfo() {
		console.log("    maxVal: " + maxVal);
		console.log("    minVal: " + minVal);
		console.log("    progressLine.width: " + progressLine.width);
		console.log("    curVal: " + curVal);
		console.log("    selectLine.width: " + selectLine.width);
	}

	Component.onCompleted: {
		//updateProgress();
		refresh();
    }
}
