import QtQuick 2.6
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import QtMultimedia 5.8
import "qrc:/qml/common" as Common
Rectangle {
    id: root;
    width: 1000;
    height: 60;
    color: Qt.rgba(161/255, 45/255, 18/255, 1.0); // 后续会做皮肤 统一赋值

    property int nSize: 16;

    property bool bPlaying: false;
    property int nPlayIndex: 0;

    // 播放类型
    Rectangle {
        id: musicStyleRect;
        color: Qt.rgba(128/255, 36/255, 14/255, 1.0);
        anchors.left:  parent.left;
        anchors.leftMargin: 40;
        anchors.top: parent.top;
        anchors.topMargin: 10;
        width: 40;
        height:20;
        radius: 5;

        Text {
            id: styleTxt;
            font.pixelSize: 12;
            color: "white";
            anchors.verticalCenter: parent.verticalCenter;
            anchors.horizontalCenter: parent.horizontalCenter;
            text: qsTr("标准");
        }
    }
    // 歌曲名字
    Rectangle {
        id: musicNameRect;
        color: "transparent"
        anchors.left:  musicStyleRect.right;
        anchors.leftMargin: 10;
        anchors.top: parent.top;
        anchors.topMargin: 20;
        width: 150;
        Text {
            id: musicName;
            anchors.verticalCenter: parent.verticalCenter;
            color: "white";
            text: qsTr("未知歌曲");
            font.pointSize: 10;
            font.bold: true;
            elide: Text.ElideRight;
        }
    }
    // 播放按钮
    Rectangle {
        id: playBtnRect;
        //anchors.verticalCenter: parent.verticalCenter;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.topMargin: 2;
        anchors.top: parent.top;
        width: 40;
        height: 40;
        color: "transparent";
        Image {
            id: playImg
            source: bPlaying === true ? "qrc:/images/stop.png" : "qrc:/images/play.png";
            width: 40;
            height: 40;
        }
        MouseArea {
            id: last;
            anchors.fill: parent;
            onPressed: {
                if(bPlaying)
                {
                    playImg.source = "qrc:/images/stop-click.png";
                }
                else
                {
                    playImg.source = "qrc:/images/play-click.png";
                }


            }
            onReleased: {
                if(bPlaying)
                {
                    playImg.source = "qrc:/images/stop.png";
                }
                else
                {
                    playImg.source = "qrc:/images/play.png";
                }
            }
            onClicked: {
                if(bPlaying)
                {
                    console.log("pause : " + bPlaying);
                    CppLocalMusic.pauseMusic();
                    bPlaying = false;
                    playImg.source = "qrc:/images/play.png";
                }
                else
                {
                    console.log("play : " + bPlaying);
                    CppLocalMusic.playMusic(nPlayIndex);
                    bPlaying = true;
                    playImg.source = "qrc:/images/stop.png";
                }

            }
        }
    }
    // 上一曲按钮
    Rectangle {
        id: lastBtnRect;
        anchors.rightMargin: 10;
        anchors.right: playBtnRect.left;
        anchors.verticalCenter: parent.verticalCenter;
        anchors.top: parent.top;
        anchors.topMargin: 6;
        color: "transparent";
        width: 32;
        height: 32;
        Image {
            id: lastImg
            source: "qrc:/images/last.png";
            width: 32;
            height: 32;
        }
        MouseArea {
            id: lastSong;
            anchors.fill: parent;

            onPressed: {
               lastImg.source = "qrc:/images/last-click.png";
            }
            onReleased: {
                lastImg.source = "qrc:/images/last.png";
            }

            onClicked: {
                CppLocalMusic.lastMusic();
            }
        }
    }
    // 下一曲
    Rectangle {
        id: nextBtnRect;
        anchors.rightMargin: 10;
        anchors.left: playBtnRect.right;
        anchors.leftMargin: 10;
        anchors.verticalCenter: parent.verticalCenter;
        anchors.top: parent.top;
        anchors.topMargin: 6;
        color: "transparent";
        width: 32;
        height: 32;
        Image {
            id: nextImg
            source: "qrc:/images/next.png";
            width: 32;
            height: 32;
        }
        MouseArea {
            id: nextSong;
            anchors.fill: parent;
            onPressed: {
               nextImg.source = "qrc:/images/next--click.png";
            }
            onReleased: {
                nextImg.source = "qrc:/images/next.png";
            }
            onClicked: {
                CppLocalMusic.nextMusic();
            }
        }
    }
    // 收藏
    Rectangle {
        id: collectRect;
        width: nSize;
        height: nSize;
        anchors.left: nextBtnRect.right;
        anchors.leftMargin: 160;
        anchors.top: parent.top;
        anchors.topMargin: 12;
        color: "transparent"
        Image {
            id: collectImg;
            source: "qrc:/images/collect24.png"
            width: nSize;
            height: nSize;
        }
    }
    // 下载
    Rectangle {
        id: downloadRect;
        width: nSize;
        height: nSize;
        anchors.left: collectRect.right;
        anchors.leftMargin: 10;
        anchors.top: parent.top;
        anchors.topMargin: 10;
        color: "transparent"
        Image {
            id: downloadImg;
            source: "qrc:/images/download16.png"
            width: nSize;
            height: nSize;
        }
    }
    // 更多
    Rectangle {
        id: moreRect;
        width: nSize;
        height: nSize;
        anchors.left: downloadRect.right;
        anchors.leftMargin: 10;
        anchors.top: parent.top;
        anchors.topMargin: 10;
        color: "transparent"
        Image {
            id: moreImg;
            source: "qrc:/images/more16.png"
            width: nSize;
            height: nSize;
        }
    }
    // 列表循环
    Rectangle {
        id: loopRect;
        width: nSize;
        height: nSize;
        anchors.left: moreRect.right;
        anchors.leftMargin: 10;
        anchors.top: parent.top;
        anchors.topMargin: 10;
        color: "transparent"
        Image {
            id: loopImg;
            source: "qrc:/images/loop24.png"
            width: nSize;
            height: nSize;
        }
    }
    // 声音
    Rectangle {
        id: soundRect;
        width: nSize;
        height: nSize;
        anchors.left: loopRect.right;
        anchors.leftMargin: 10;
        anchors.top: parent.top;
        anchors.topMargin: 10;
        color: "transparent"
        Image {
            id: soundImg;
            source: "qrc:/images/sound-on.png"
            width: nSize;
            height: nSize;
        }
    }
    // 音效
    Rectangle {
        id: soundEffectsRect;
        width: 40;
        height: 24;
        anchors.left: loopRect.right;
        anchors.leftMargin: 10;
        anchors.top: parent.top;
        anchors.topMargin: 8;
        color: Qt.rgba(128/255, 36/255, 14/255, 1.0);
        radius: 5;

        Rectangle {
            id: circle;
            anchors.left: parent.left;
            anchors.leftMargin: 3;
            anchors.verticalCenter: parent.verticalCenter;
            width: 4;
            height: 4;
            radius: 2;
            color: "white";
        }

        Text {
            id: effects;
            color: "white";
            font.pointSize: 10;
            anchors.left:  circle.right;
            anchors.leftMargin: 3;
            anchors.top: parent.top;
            anchors.topMargin: 6;
            anchors.verticalCenter: parent.verticalCenter;
            width: 24;
            height: 24;
            text: qsTr("音效");
        }
    }
    // 词
    Rectangle {
        id: lyricRect;
        width: nSize;
        height: nSize;
        anchors.left: soundEffectsRect.right;
        anchors.leftMargin: 10;
        anchors.top: parent.top;
        anchors.topMargin: 10;
        color: "transparent"
        Text {
            id: lyricText;
            color: "white";
            font.pointSize: 14;
            anchors.verticalCenter: parent.verticalCenter;
            text: qsTr("词")
            font.bold: true;
        }
    }
    // 评论
    Rectangle {
        id: commentRect;
        width: nSize;
        height: nSize;
        anchors.left: lyricRect.right;
        anchors.leftMargin: 10;
        anchors.top: parent.top;
        anchors.topMargin: 10;
        color: "transparent";
        Image {
            id: commentImg;
            source: "qrc:/images/comment.png";
            width: nSize;
            height: nSize;
        }
    }

    Common.PlayProgressBar {
        id: progressbar;
        isTime: true;
        minVal: 0;
        maxVal: 0;
        curVal: 0;
        width: 870;
        height: 20;
        anchors.left: parent.left;
        anchors.bottom: parent.bottom;
        anchors.horizontalCenter: parent.horizontalCenter;
        onProgressBarPressed: {

        }
        onProgressBarReleased: {

        }
        onProgressBarDraged: {
            console.log("Drag position is " + position);
            CppLocalMusic.setPlayPosition(position);
        }

    }
    /**************************************************************************************************************
    * 以下是播放信号处理 C++
    ***************************************************************************************************************/

    Connections {
        target: CppLocalMusic;

        onSigQMLPlay: {
            bPlaying = true;
            console.log("play: " + strSongName + "; " + strSongPath + "; " + strSingerPic + "; " + nIndex);
            nPlayIndex = nIndex;
            //audioPlayer.source = strSongPath;
            //audioPlayer.play();
            console.log("play status :" + bPlaying);
            musicName.text = strSongName;

        }
        onSigQMLPause: {
            bPlaying = false;
            console.log("receive pause signal");
            //audioPlayer.pause();
            console.log("play status :" + bPlaying);
        }
        onSigQMLPositionChanged: {
            //console.log(" qml sig PositonChanged: " + position);
            progressbar.curVal  = position;
        }
        onSigQMLDurationChanged: {
            // console.log(" qml sig DurationChanged: " + duration);
            progressbar.enabled = true;
            progressbar.maxVal = duration;
            progressbar.minVal = 0;
            progressbar.curVal = 0;
        }
    }
    /**************************************************************************************************************
    * 以下是播放器 QML 自带播放器操作 C++
    ***************************************************************************************************************/
    /*
    MediaPlayer {
        id: audioPlayer;
        objectName: "audioPlayerObject";
    }
    Component.onCompleted: {
        console.log("audioPlayer: " + audioPlayer);
    }
    */
}
