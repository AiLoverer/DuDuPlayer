import QtQuick 2.0
import QtMultimedia 5.6
/***
* 视频播放界面
*/
Rectangle {
    id: root
    color: "transparent"

    MediaPlayer {
        id: meadiaPlayer;

    }

    VideoOutput {
        id: videoOutput;
        width: parent.width;
        height: parent.height;
        source: meadiaPlayer;
    }

}
