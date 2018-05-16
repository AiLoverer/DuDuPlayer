import QtQuick 2.5

Rectangle {
    id: root;

    property string picPath: "qrc:/images/default.png";
    property string musicTxt: qsTr("最新歌曲榜");
    property bool bPlayingMusic: false;

    width: 1280;
    height: 100;
    color: "transparent";
    clip: true;
    signal clickedPersonalCenter();
    // Picture of music
    Rectangle{
        id: musicPicRect;

        color: "transparent";
        width: 80;
        height: 80;
        anchors.left: parent.left;
        anchors.leftMargin: 78;
        anchors.top: parent.top;
        anchors.topMargin: 10;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 10;

        Image {
            id: musicImg
            anchors.fill: parent;
            source: picPath;
        }
    }

    // style
    Text{
        id: musicText;

        anchors.left: musicPicRect.right;
        anchors.leftMargin: 45;
        anchors.top: parent.top;
        anchors.topMargin: 10;
        width: 400;
        height:40;

        horizontalAlignment: Text.AlignHCenter;
        verticalAlignment: Text.AlignVCenter;
        color: "white";
        font.pixelSize: 36;//Theme.fontSizeMedium;
        //font.family: Theme.fontFamily;
        text: musicTxt;
        elide: Text.ElideRight;

    }

    // music button - previous
    Rectangle{
        id: previousBtnRect;

        width: 66;
        height: 66;
        anchors.left: parent.left;
        anchors.leftMargin: 770;
        anchors.top: parent.top;
        anchors.topMargin: 17;
        color: "transparent";
        Image {
            id: previousImg;

            source: "qrc:/images/last.png"
        }
        MouseArea{
            anchors.fill: parent;
            onReleased: {
                previousImg.source = "qrc:/images/last.png"
            }

            onPressed: {
                previousImg.source = "qrc:/images/last-click.png"
            }

            onClicked: {
                JCNet_AppOnlineMusic.previous();
            }
        }
    }

    // music button - play
    Rectangle{
        id: playBtnRect;

        width: 66;
        height: 66;
        anchors.left: previousBtnRect.right;
        anchors.leftMargin: 58;
        anchors.top: parent.top;
        anchors.topMargin: 17;
        color: "transparent";
        Image {
            id: playImg;

            source: bPlayingMusic ? "qrc:/images/stop.png" :"qrc:/images/play.png"
        }
        MouseArea{
            anchors.fill: parent;
            onReleased: {
                if(bPlayingMusic)
                {
                    playImg.source = "qrc:/images/stop.png"
                }
                else
                {
                    playImg.source = "qrc:/images/play.png"
                }


            }

            onPressed: {
                if(bPlayingMusic)
                {
                   playImg.source = "qrc:/images/stop-click.png"
                }
                else
                {
                    playImg.source = "qrc:/images/play-click.png"
                }


            }
            onClicked: {
                if(bPlayingMusic)
                {
                    JCNet_AppOnlineMusic.pause();
                }
                else
                {
                    JCNet_AppOnlineMusic.play();
                }
            }
        }
    }

    // music button - next
    Rectangle{
        id: nextBtnRect;

        width: 66;
        height: 66;
        anchors.left: playBtnRect.right;
        anchors.leftMargin: 58;
        anchors.top: parent.top;
        anchors.topMargin: 17;
        color: "transparent";
        Image {
            id: nextImg;

            source: "qrc:/images/next.png"
        }
        MouseArea{
            anchors.fill: parent;
            onReleased: {
                nextImg.source = "qrc:/images/next.png"
            }

            onPressed: {
                nextImg.source = "qrc:/images/next--click.png"
            }

            onClicked: {
                JCNet_AppOnlineMusic.next();
            }
        }
    }

    Rectangle {
        id: partingLineRect;

        width: 3;
        height:65;
        color: "gray";
        anchors.left: nextBtnRect.right;
        anchors.leftMargin: 42;
        anchors.top: parent.top;
        anchors.topMargin: 17;
    }

    Rectangle {
        id: personCenterRect;

        anchors.left: partingLineRect.right;
        anchors.leftMargin: 52;
        anchors.top: parent.top;
        anchors.topMargin: 25;
        width: 50;
        height: 48;
        color: "transparent";

        Image {
            id: personCenterImg;

            anchors.fill: parent;
            source: "qrc:/images/icon-person-center.png"
        }

        MouseArea{
            anchors.fill: parent;
            onReleased: {
                personCenterImg.source = "qrc:/images/icon-person-center.png"
            }

            onPressed: {
                personCenterImg.source = "qrc:/images/icon-person-center-click.png"
            }

            onClicked: {
                console.log("clicked personal center")
                clickedPersonalCenter();
            }
        }
    }

    Connections{
        target: JCNet_AppOnlineMusic;
        onSigQMLMusicPlayingInfo:{
          if(strSingerPicUrl !== qsTr(""))
          {
              picPath = strSingerPicUrl;
          }
          musicText.text = strSongName;
          bPlayingMusic = bPlaying;
          console.log("strSongName" + strSongName);
          console.log("strSingerName" + strSingerName);

        }
    }
}


