import QtQuick 2.0
import QtMultimedia 5.6
import "qrc:/qml/sub/video" as VideoPlayer
import "qrc:/qml/common" as Common
import "qrc:/qml/common/Function.js" as ComFunc
Rectangle {
    id: root;
    width: 687;
    height: 517;
    color: Qt.rgba( 40 /255, 40/255, 40/255, 0.5);
    clip: true;

    property int nSize: 32;
    property int nSpace: 10;

    property bool bPlaying: false;
    property string strDuration: "00:00"; // 单位s
    property string strPosition: "00:00"; // 单位s
    property int  nPosition: 0;
    property int  nDuration: 0

    // 播放器显示窗口
    Rectangle {
        id: videoPlayer;
        anchors.left: parent.left;
        anchors.top: parent.top;
        anchors.right: parent.right
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 60;
        //color: "transparent"
        color: Qt.rgba(54/255, 54/255, 54/255, 1.0);

        /* QML自带播放器来播放
        MediaPlayer {
            id: duduMediaPlayer;
            source: "D:/KuGou/MV/mv.mp4";

        }
        */

        VideoOutput {
            id: videoOutput;
            width: parent.width;
            height: parent.height;
            source: duduMediaPlayer;
        }
    }
    Connections {
        target: duduMediaPlayer;
        onSigPositionChanged: {
            //console.log("position:" + position);
            nPosition = position;
            strPosition = ComFunc.dateFormat(position / 1000);
            //console.log("position time" + strPosition);
        }
        onSigDurationChanged :{
            //console.log("duration:" + mediaPlayer.duration);
            nDuration = duration;
            strDuration = ComFunc.dateFormat(duration / 1000);
            //console.log("duration time" + strDuration);
        }
        onSigState: {
            console.log("state:" + state);
            /*
            enum State
            {
                StoppedState,
                PlayingState,
                PausedState
            };
            */
            if(state === 0 || state === 2)
            {
                bPlaying = false;
            }
            else if (state === 1)
            {
                bPlaying = true;
            }
        }

    }


    // 下面播放控制区域 height 60
    Rectangle {
        id: stateRect;
        anchors.left: parent.left;
        anchors.top: parent.top;
        anchors.topMargin: parent.height - 60;
        anchors.right: parent.right;
        anchors.bottom: parent.bottom;
        color: "transparent";

        // 进度条
        Rectangle{
            id: progressBar;
            anchors.left: parent.left;
            anchors.top: parent.top;
            anchors.right: parent.right;
            height: 10;
            color: "lightGray"
            Rectangle {
               anchors.left: parent.left;
               anchors.top: parent.top;
               anchors.bottom: parent.bottom;
               width: nDuration>0?parent.width*nPosition/nDuration : 0;
               color: "darkGreen";
            }
            MouseArea {
                property int pos
                anchors.fill: parent

                onClicked: {
                    if (duduMediaPlayer.seekable)
                    {
                        pos = nDuration * mouse.x / width;
                        duduMediaPlayer.setPosition(pos);

                    }
                }
            }

        }

        // 播放控制栏
        Rectangle {
            id: playBar
            anchors.left: parent.left;
            anchors.top: progressBar.bottom;
            anchors.right: parent.right;
            anchors.bottom: parent.bottom;
            color: "transparent";

            Common.PicButton {
                id: last;
                picSource: "qrc:/images/64last.png";
                picRadius: nSize / 2;
                width: nSize;
                height: nSize;
                anchors.left: parent.left;
                anchors.leftMargin: 20;
                anchors.verticalCenter: parent.verticalCenter;
            }

            Common.PicButton {
                id: playpause;
                picSource: bPlaying ? "qrc:/images/64pause.png" : "qrc:/images/64play.png";
                picRadius: nSize / 2;
                width: nSize;
                height: nSize;
                anchors.left: last.right;
                anchors.leftMargin: nSpace;
                anchors.verticalCenter: parent.verticalCenter;
                onClicked: {

                    bPlaying = !bPlaying;
                    if(bPlaying)
                    {
                        duduMediaPlayer.play();
                        console.log("qml clicked play");
                    }
                    else
                    {
                        duduMediaPlayer.pause();
                        console.log("qml clicked pause");
                    }
                }
            }
            Common.PicButton {
                id: next;
                picSource: "qrc:/images/64next.png";
                picRadius: nSize / 2;
                width: nSize;
                height: nSize;
                anchors.left: playpause.right;
                anchors.leftMargin: nSpace;
                anchors.verticalCenter: parent.verticalCenter;
            }

            // 时间
            Text {
                id: time;
                anchors.left: next.right;
                anchors.leftMargin: 20;
                anchors.verticalCenter: parent.verticalCenter;
                width: 70;
                font.pointSize: 12;
                color: Qt.rgba(127/255, 127/255, 127/255, 1.0);
                text: strPosition + "/" + strDuration;
            }

        }

    }

}
