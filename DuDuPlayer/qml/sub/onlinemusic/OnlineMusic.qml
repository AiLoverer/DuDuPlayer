import QtQuick 2.0
/***
* 在线音乐主界面
*/
Rectangle {
        id: root;

        width: 687;
        height: 517;
        color: "transparent";
        clip: true;

        property bool isPlaying: false;
        property int nCurSlectIndex:-1;
        property string strCurSlectType;
        property string strNewsType;
        property int nDeleteCount:0;
        property var mPopupCleanTip: null;
        property alias personCenterVisible: personalCenterRect.visible;
        property alias pageSearchVisible: searchPage.visible;
        property alias pageSearchListVisible: searchListPage.visible;
        property alias onlineMusicTypeListRectVisible: onlineMusicTypeListRect.visible;
        property alias pageSingerListVisible: pageSingerList.visible;
        property var handle: null;
        //  onlinemusic 分类列表界面
        Rectangle{
            id:onlineMusicTypeListRect;
            color: "transparent";
            anchors.fill: parent;

            ListModel{// onlinemusic 类型
                id:typeListModel;

                ListElement { styleType: qsTr("热门");}
                ListElement { styleType: qsTr("场景");}
                ListElement { styleType: qsTr("情感");}
                ListElement { styleType: qsTr("风格");}
                ListElement { styleType: qsTr("年代");}
                ListElement { styleType: qsTr("语种");}
            }

            // search button
            Rectangle{
                id: searchBtnRect;

                anchors.left: parent.left;
                anchors.leftMargin: 10;
                anchors.top: parent.top;
                anchors.topMargin: 10;
                height: 24;
                width: 24;
                radius: 4;
                color: "transparent";
                Image{
                    id: searchImg;
                    width: 24;
                    height: 24;
                    source: "qrc:/images/icon-search.png"
                }
                MouseArea{
                    x: 0;
                    y: 0;
                    anchors.fill: parent;

                    onClicked: {
                        console.log("clicked search ... ");
                        //thisScreen.showScreen(Screens.JNet_OnlineMusic_Search);

                       onlineMusicTypeListRect.visible = false;
                       searchPage.visible = true;
                    }
                    onPressed: {
                        searchBtnRect.color = "#ff9400";
                    }
                    onReleased: {
                        searchBtnRect.color = "transparent";
                    }
                }
            }

            //  表头（热门、场景、情感、风格、年代、语种）
            Rectangle{
                id:styleTitle;

                anchors.left: searchBtnRect.right;
                anchors.leftMargin: 10;
                anchors.top: parent.top;
                anchors.right: parent.right;
                height: 35;
                color: "transparent";

                Component{
                    id:titleComp;

                    Rectangle{
                        id:typeItem;
                        width: styleTitle.width / typeListModel.count;
                        height: 35;
                        color: "transparent";

                        Text {
                            id:typeText;
                            anchors.horizontalCenter: parent.horizontalCenter;
                            anchors.verticalCenter: parent.verticalCenter;

                            text: styleType;
                            font.pixelSize: 14;
                            color: typeItem.ListView.isCurrentItem   ?   "#ff9400":"#ffffff";
                        }

                        //  选中状态的高亮下划线
                        Rectangle{
                            anchors.horizontalCenter: parent.horizontalCenter;
                            anchors.bottom: parent.bottom;
                            width: 150;
                            height: 3;
                            color: "#ff9400";
                            visible: typeItem.ListView.isCurrentItem;
                        }

                        MouseArea{
                            anchors.fill: parent;

                            onClicked: {

                                console.log("clicked music title ...");
                                JCNet_AppOnlineMusic.setSelectIndex(index);//设置当前分类和显示界面的选中项
                            }
                        }
                    }
                }

                ListView {
                    id: listTab;
                    anchors.fill: parent;
                    orientation: ListView.Horizontal;
                    clip: true;
                    model: typeListModel;
                    delegate: titleComp;
                }

                Rectangle{//  下划线
                    width: root.width;
                    height:2;
                    color: "#ff9400";
                    opacity:0.1;
                    anchors.bottom: parent.bottom;
                }
            }

            VisualItemModel{
                id:pageModel;
                Loader {
                    id: pageHot

                    width: listPage.width;
                    height: listPage.height;
                    source: "qrc:/qml/sub/pageHot.qml";

                }

                Loader {
                    id: pageSence;
                    width: listPage.width;
                    height: listPage.height;
                    source: "qrc:/qml/sub/pageSence.qml";
                    onLoaded: {
                        item.listModel = modelOnlineMusicTypeSence;
                    }
                }
                Loader {
                    id: pageEmotion;
                    width: listPage.width;
                    height: listPage.height;
                    source: "qrc:/qml/sub/pageEmotion.qml";
                    onLoaded: {
                        item.listModel = modelOnlineMusicTypeEmotion;
                    }
                }

                Loader {
                    id: pageStyle;
                    width: listPage.width;
                    height: listPage.height;
                    source: "qrc:/qml/sub/pageStyle.qml";
                    onLoaded: {
                        item.listModel = modelOnlineMusicTypeStyle;
                    }
                }
                Loader {
                    id: pageYears;
                    width: listPage.width;
                    height: listPage.height;
                    source: "qrc:/qml/sub/pageYears.qml";
                    onLoaded: {
                        item.listModel = modelOnlineMusicTypeYears;
                    }
                }
                Loader {
                    id: pageLanguage;
                    width: listPage.width;
                    height: listPage.height;
                    source: "qrc:/qml/sub/pageLanguage.qml";
                    onLoaded: {
                        item.listModel = modelOnlineMusicTypeLanguage;
                    }
                }
            }
            Connections{
                target: pageHot.item;

                onSigChooseTopItem:{
                    console.log("onSigChooseTopItem: " + name);
                    if(name === qsTr("热门歌手榜"))
                    {
                        onlineMusicTypeListRect.visible = false;
                        pageSingerList.visible = true;
                    }
                    else
                    {
                        thisScreen.showScreen(Screens.JNet_OnlineMusic_PagePlay);
                    }
                    JCNet_AppOnlineMusic.getTopnameMusicData(name);
                }
            }


            // listView page
            ListView{
                id: listPage
                anchors.left: parent.left;
                anchors.right: parent.right;
                anchors.top: parent.top;
                anchors.topMargin: 35;
                anchors.bottom: parent.bottom;
                model: pageModel
                orientation: ListView.Horizontal

                //
                snapMode: ListView.SnapOneItem
                highlightRangeMode: ListView.StrictlyEnforceRange
                cacheBuffer: 3  // 缓存区域高度、宽度、元素个数？

                // page indicator
                Row {
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 5
                    z: 2

                    spacing: 20
                    Repeater {
                        opacity: 0.8
                        model: listPage.model.count
                        Rectangle {
                            width: 5; height: 5
                            radius: 3
                            color: listPage.currentIndex == index ? "white" : "grey"
                            MouseArea {
                                width: 20; height: 20
                                anchors.centerIn: parent
                                onClicked: listPage.currentIndex = index
                            }
                        }
                    }
                }
                onCurrentIndexChanged: {
                    //console.log("currentIndex is : " + currentIndex);
                    listTab.currentIndex = currentIndex;
                }

            }




         }
        // 热门歌手榜
        PageSingerList {
            id: pageSingerList;
            anchors.left: parent.left;
            anchors.right: parent.right;
            anchors.top: parent.top;
            anchors.bottom: parent.bottom;

            visible: false;
        }

        // 搜索界面
        PageSearch{
            id: searchPage;
            anchors.left: parent.left;
            anchors.top: parent.top;
            anchors.right: parent.right;
            anchors.bottom: parent.bottom;

            visible: false;

        }
        // 搜索列表
        PageSearchedList{
            id: searchListPage;

            anchors.left: parent.left;
            anchors.top: parent.top;
            anchors.right: parent.right;
            anchors.bottom: parent.bottom;
            visible: false;
        }

        // 个人中心
        PagePersonalCenter{
            id: personalCenterRect;

            anchors.left: root.left;
            anchors.top: root.top;
            anchors.right: root.right
            anchors.bottom: root.bottom;

            color: "transparent";

            visible: false;

            onClickedOneKeyClean: {
                var strShowText = "";
                if(bShowCollect)
                {
                    strShowText = qsTr("温馨提示\n\n\n确定要清空所有收藏音乐");
                }
                else
                {
                    strShowText = qsTr("温馨提示\n\n\n确定要清空所有历史记录");

                }

                //root.funcOneKeyClean(strShowText);
            }
        }

        /****以下是固定界面****/
        /*
        //  底部横线
        Rectangle{
            id: secondLineRect;
            anchors.left: parent.left;
            anchors.right: parent.right;
            anchors.top: parent.top;
            anchors.topMargin: parent.height - 103;
            width: parent.width;
            height: 3;
            color: "#ff9400";
            opacity:0.1;
        }

        BottomMusicControl{
            id: bottomMusicControlRect;
            anchors.left: parent.left;
            anchors.right: parent.right;
            anchors.top: secondLineRect.bottom;
            anchors.bottom: parent.bottom;
            onClickedPersonalCenter: {
                console.log("get clicked personal center signal ...");
                onlineMusicTypeListRect.visible = false;
                searchListPage.visible = false;
                searchPage.visible = false;
                if(startSlipTipTimer.running == true)
                {
                    startSlipTipTimer.stop();
                    nWaitTime = 4;
                }

                personalCenterRect.visible = true;
                //JCNet_AppOnlineMusic.enterPersonalCenter();

            }
        }
        */
        Component.onCompleted: {
            JCNet_AppOnlineMusic.getMusicTypeTag();
            JCNet_AppOnlineMusic.getMusicTypeTop();
        }


        Connections{
            target: JCNet_AppOnlineMusic;

            onSigQMLSetSelectIndex:{
                console.log("get onSigQmlSetSelectedIndex value is :" + nIndex);
                listTab.currentIndex    =   nIndex;  //分类的当前选中项
                listPage.contentX       =   nIndex * listPage.width; //强制页面跳转
            }
            onSigQMLSearchMusic:{
                if(bSuccess)
                {
                    console.log("search music success...");
                    searchListPage.visible = true;
                    searchPage.visible = false;
                }
                else
                {
                    console.log("search music faild...");
                    //root.funcPopupTipWnd(qsTr("未搜索到相关结果或网络连接异常"));

                }
            }
            onSigQMLGetMusicTypeTopDataComplete:{
                console.log("onSigQMLGetMusicTypeTopDataComplete...");
                //startSlipTipTimer.start();
            }
        }
        /*
        Connections{
            target: SettingInterface;

            onSigLanguageChange:{
                onInit();
            }

        }

        // 搜索提示弹出窗
        function funcPopupTipWnd(tips) {
            handle = thisScreen.mMainFrame.createPopup(Popups.Common, thisScreen.content);
            handle.setMessage(qsTr(tips));
            handle.mDelayClose = 2000;
            handle.mStyle = handle.sStyle_Btn_None;
            handle.show();
        }

        function    clickOnBack(){
            console.log("onlineMusic goback...");
            searchPage.visible = false;
            onlineMusicTypeListRect.visible = true;
        }

        function funcOneKeyClean(strShowText) {
            root.mPopupCleanTip = mMainFrame.createPopup(Popups.Common, thisScreen.content);
            root.mPopupCleanTip.setMessage(strShowText);
            root.mPopupCleanTip.setFontSize(40);
            root.mPopupCleanTip.show();
        }

        function onOk(pop) {
            if (pop === root.mPopupCleanTip) {
                root.mPopupCleanTip.close();
                root.mPopupCleanTip = null;
                if(personalCenterRect.bShowCollect)
                {
                    console.log("onlineMusic deleteAllCollectMusic...");
                    JCNet_AppOnlineMusic.deleteAllCollectMusic();
                }
                else
                {
                    console.log("onlineMusic deleteAllHistoryMusic...");
                    JCNet_AppOnlineMusic.deleteAllHistoryMusic();
                }
            }
        }

        function onCancel(pop) {
            if (pop === root.mPopupCleanTip) {
                root.mPopupCleanTip.close();
                root.mPopupCleanTip = null;
            }
        }
        */

    }
