import QtQuick 2.0
/***
* 标题栏
* 属于LeftMain的标题栏
*/
Rectangle {
    id: root;
    color: Qt.rgba(161/255, 45/255, 18/255, 1.0); // 后续会做皮肤 统一赋值

    property int nSpace: 60;
    // 音乐
    Image {
        id: imgMusic;
        source: "qrc:/images/128music.png"
        anchors.left: parent.left;
        anchors.leftMargin: 25;
        anchors.verticalCenter: parent.verticalCenter;
        width: 24;
        height: 24;
    }
    // 云
    Image {
        id: imgCloud;
        source: "qrc:/images/128cloud.png"
        anchors.left: imgMusic.left;
        anchors.leftMargin: nSpace;
        anchors.verticalCenter: parent.verticalCenter;
        width: 24;
        height: 24;
    }
    // 电台
    Image {
        id: imgRadio;
        source: "qrc:/images/128radiotower.png"
        anchors.left: imgCloud.left;
        anchors.leftMargin: nSpace;
        anchors.verticalCenter: parent.verticalCenter;
        width: 24;
        height: 24;
    }
    // 手机
    Image {
        id: imgPhone;
        source: "qrc:/images/128smartphone.png"
        anchors.left: imgRadio.left;
        anchors.leftMargin: nSpace;
        anchors.verticalCenter: parent.verticalCenter;
        width: 24;
        height: 24;
    }
    // 下载
    Image {
        id: imgDownload;
        source: "qrc:/images/128download.png"
        anchors.left: imgPhone.left;
        anchors.leftMargin: nSpace;
        anchors.verticalCenter: parent.verticalCenter;
        width: 24;
        height: 24;
    }

}
