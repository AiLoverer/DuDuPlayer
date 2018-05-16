import QtQuick 2.0


Rectangle {
    id: lyricRect;
    width: 687;
    height: 517;
    color: "transparent";
    clip: true;

    property var m_indexTime: 0;
    property bool bNeedGetLycPos: false; //  在收到nowPlaying或者拖动进度条时，需要重新定位歌词

    Component {
        id: delegateComp;

        Rectangle {
            id: rectLyric;

            width: lyricRect.width;
            height: lyricRect.height / 10;
            color: "transparent";

            Text {
                id: txtLyric;

                anchors.horizontalCenter: parent.horizontalCenter

                text: qsTr(modelData);
                color: rectLyric.ListView.isCurrentItem ? "white" : "gray";
                scale: rectLyric.ListView.isCurrentItem ? 2.0 : 1.5;
                font.family: "微软雅黑";
                font.pixelSize: 15;
            }
        }
    }

    //  listView
    ListView {
        id: listViewLyric;

        model: CppLocalMusic.lyrics;
        delegate: delegateComp;
        //preferredHighlightBegin:0.5;
        //preferredHighlightEnd: 0.5;
        contentY:getlyricContentY();

        function    getlyricContentY()
        {
            if(listViewLyric.currentIndex   <= 3)
            {
                return 0;
            }
            else
            {
                return  lyricRect.height/10*3/2   * (listViewLyric.currentIndex - 4);
            }

        }

        anchors.fill: parent;

        spacing: 10;

        Behavior on contentY {
            NumberAnimation { duration: 1000; }
        }
    }

    Connections {
        target: CppLocalMusic;



        onLyricsChanged:{
            //  切歌
            bNeedGetLycPos  =   true;

            listViewLyric.currentIndex  =   0;
            m_indexTime =   0;
        }
        onSigQMLPositionChanged: {
            //console.log(" qml sig PositonChanged: " + position);
            var time    =   position * 1000;

            if(bNeedGetLycPos   === true)
            {
                m_indexTime =   CppLocalMusic.getIndexByTime(time);
                bNeedGetLycPos  =   false;
                listViewLyric.incrementCurrentIndex();
                //listViewLyric.contentY  =   lyricRect.height/10*3/2   * (listViewLyric.currentIndex - 4)
                listViewLyric.currentIndex  =   m_indexTime +   1;
                m_indexTime++;
            }
            else
            {
                if(time+800 >= CppLocalMusic.times[m_indexTime])
                {
                    listViewLyric.incrementCurrentIndex();
                    //listViewLyric.contentY  =   lyricRect.height/10*3/2   * (listViewLyric.currentIndex - 4)
                    m_indexTime++;
                }
            }
        }
    }
}
