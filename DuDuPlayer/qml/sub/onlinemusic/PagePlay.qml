import QtQuick 2.5
import QtQuick.Layouts 1.3

 Rectangle {
        id: root;

        width: 1280;
        height: 625;
        color: "transparent";
        clip: true;

        Rectangle{
            id: imgSongRect;

            anchors.left: parent.left;
            anchors.leftMargin: pagelist.visible ? 80 : 238;
            anchors.top: parent.top;
            anchors.topMargin: 50;
            width: 320;
            height: 320;
            color: "transparent";
            Image {
                id: imgSong;
                source: picUrl;

                anchors.fill: parent;
            }
        }

        // 歌名
        Text {
            id: txtSongName;
            text: songName;
            font.pixelSize: 40;
            font.family: "SimHei";
            color: "#ff9400";
            anchors.left: imgSongRect.right;
            anchors.leftMargin: 66;
            anchors.top: parent.top;
            anchors.topMargin: 160;
            width: pagelist.visible ? 350 : 400;
            elide: Text.ElideRight;
        }
        // 歌手名
        Text {
            id: txtSingerName;
            text: singerName;
            font.pixelSize: 36;
            font.family: "SimHei";
            color: "#33ffffff";
            anchors.left: txtSongName.left;
            anchors.top: txtSongName.bottom;
            anchors.topMargin: 26;
            width: pagelist.visible ? 350: 400;
            height: 40;
            elide: Text.ElideRight;
        }

        RowLayout{
                id: rectBottom;

                anchors.bottom: parent.bottom;
                anchors.bottomMargin: 35;
                anchors.left: parent.left;
                anchors.leftMargin: pagelist.visible ? 216 : 446;

                spacing: 48;

                Rectangle{
                    id: lastBtnRect;

                    width: 66;
                    height: 66;
                    color: "transparent";
                    radius: lastBtnRect.width/2;

                    Image {
                        id: imgLastBtn;
                        anchors.fill: parent;
                        source: "qrc:/images/last.png"
                    }
                    MouseArea{
                        anchors.fill: parent;
                        onPressed: {
                            lastBtnRect.color = pressedColor;
                        }
                        onReleased: {
                            lastBtnRect.color = normalColor;
                        }
                        onClicked: {
                            //console.log("clicked last ...");
                            JCNet_AppOnlineMusic.previous();
                        }
                    }
                }

                Rectangle{
                    id: playBtnRect;

                    color: "transparent";
                    width: 66;
                    height: 66;
                    radius: playBtnRect.width/2;

                    Image {
                        id: imgPlayBtn;
                        anchors.fill: parent;
                        source: bPlayingMusic ? "qrc:/imagesstop.png" : "qrc:/images/play.png"
                    }
                    MouseArea{
                        anchors.fill: parent;
                        onPressed: {
                            playBtnRect.color = pressedColor;
                        }
                        onReleased: {
                            playBtnRect.color = normalColor;
                        }
                        onClicked: {
                            if(bPlayingMusic)
                            {
                                JCNet_AppOnlineMusic.pause();
                            }
                            else
                            {
                                JCNet_AppOnlineMusic.resume();
                            }
                        }
                    }
                }
                Rectangle{
                    id: nextBtnRect;

                    color: "transparent";
                    width: 66;
                    height: 66;
                    radius: nextBtnRect.width/2;

                    Image {
                        id: imgNextBtn;
                        anchors.fill: parent;
                        source: "qrc:/images/next.png"
                    }
                    MouseArea{
                        anchors.fill: parent;
                        onPressed: {
                            nextBtnRect.color = pressedColor;
                        }
                        onReleased: {
                            nextBtnRect.color = normalColor;
                        }
                        onClicked: {
                            //console.log("clicked next ...");
                            JCNet_AppOnlineMusic.next();
                        }
                    }
                }
                Rectangle{
                    id: listBtnRect;

                    color: "transparent";
                    width: 66;
                    height: 66;
                    radius: listBtnRect.width/2;

                    Image {
                        id: imgListBtn;
                        anchors.fill: parent;
                        source: "qrc:/images/list.png"
                    }
                    MouseArea{
                        anchors.fill: parent;
                        onPressed: {
                            listBtnRect.color = pressedColor;
                        }
                        onReleased: {
                            listBtnRect.color = normalColor;
                        }
                        onClicked: {
                            //console.log("clicked next ...");
                            pagelist.visible = !pagelist.visible;
                        }
                    }
                }

            }
        // 进度条
        ProgressBar{
            id: playProgress;

            isTime: true;
            minVal:0;
            maxVal: 0;
            curVal:0;
            width: pagelist.visible ? 760 : 900;
            anchors.bottom: parent.bottom;
            anchors.bottomMargin: 140;
            anchors.left: parent.left;
            anchors.leftMargin: pagelist.visible ? 32 : 190;

            onProgressBarPressed: {

            }
            onProgressBarReleased: {
            }
        }

        // 收藏按钮
        Rectangle
        {
            id: btnCollectRect;
            color: "transparent";

            width: 56;
            height: 52;

            anchors.top: parent.top;
            anchors.topMargin: 32;
            anchors.right: pagelist.visible ? pagelist.left : parent.right;
            anchors.rightMargin: pagelist.visible ? 20 : 130;

            Image {
                id: imgCollect
                source: if(bCollect)
                        {
                            return "qrc:/images/icon-col-click.png"
                        }
                        else
                        {
                            return "qrc:/images/icon-col.png";
                        }


            }
            MouseArea{

               anchors.fill: parent;

               onPressed: {
               }
               onReleased: {
               }

               onClicked: {
                    //console.log("clicked collect button ...");
                   JCNet_AppOnlineMusic.collectMusic(nCurrentMusicIndex);
               }
            }
        }

        // PageList
        PageList{
            id: pagelist;
            anchors.top: parent.top;
            anchors.right: parent.right;
            anchors.bottom: parent.bottom;

            visible: false;
            onClicked: {
                //console.log("pagelist：index" + index);
                nCurrentMusicIndex = index;
            }
        }

        Connections{
            target: JCNet_AppOnlineMusic;
            onSigQMLMusicPlayingInfo:{
              if(strSingerPicUrl !== qsTr(""))
              {
                    imgSong.source = strSingerPicUrl;
              }
              txtSongName.text = strSongName;
              txtSingerName.text = strSingerName;
              bPlayingMusic = bPlaying;
              //console.log("strSongName" + strSongName);
              //console.log("strSingerName" + strSingerName);

            }
            onSigQMLbCollected:{
                //console.log("onSigQMLbCollected : " + bCollected);
                if(strSongId === pagelist.strCurrentSongId)
                {
                     bCollect = bCollected;
                }
            }
            onSigQMLCurrentMusicIndexChanged:{
               // console.log("onSigQMLCurrentMusicIndexChanged : " + nIndex);
                nCurrentMusicIndex = nIndex;
            }
        }
    }
